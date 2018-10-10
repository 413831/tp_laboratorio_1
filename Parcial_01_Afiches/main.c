#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
#include "ventas.h"
#include "utn.h"
#include "informar.h"

#define QTY_CLIENTES 10
#define QTY_VENTAS 10


void abmClientes(Cliente arrayUno[],int sizeUno,Venta arrayDos[],int sizeDos,int* counterClient);
void abmVentas(Cliente arrayUno[],int sizeUno,Venta arrayDos[],int sizeDos,int* counterSales);


int main()
{
    Cliente arrayClientes[QTY_CLIENTES];
    Venta arrayVentas[QTY_VENTAS];

    int opcion;
    int contadorClientes = 5;//CAMBIAR PARA HARDCODE
    int contadorVentas = 5;//CAMBIAR PARA HARDCODE



    cliente_init(arrayClientes,QTY_CLIENTES,1);
    venta_init(arrayVentas,QTY_VENTAS,STATUS_0);


    cliente_ingresoForzado(arrayClientes,QTY_CLIENTES,"AAA","Gomez","23-33444555-1");
    cliente_ingresoForzado(arrayClientes,QTY_CLIENTES,"BBB","Perez","23-11444555-3");
    cliente_ingresoForzado(arrayClientes,QTY_CLIENTES,"DDD","Moreira","25-66777888-9");
    cliente_ingresoForzado(arrayClientes,QTY_CLIENTES,"EEE","Gomez","22-11111111-2");
    cliente_ingresoForzado(arrayClientes,QTY_CLIENTES,"CCC","Gurruchaga","27-22123123-3");


    venta_ingresoForzado(arrayVentas,QTY_VENTAS,"archivo1.mpg","CABA",100,1);
    venta_ingresoForzado(arrayVentas,QTY_VENTAS,"VIDEO5.avi","CABA",100,1);
    venta_ingresoForzado(arrayVentas,QTY_VENTAS,"PROMO6.mp4","CABA",100,1);
    venta_ingresoForzado(arrayVentas,QTY_VENTAS,"VIDEO2.mpg","GBA OESTE",100,1);
    venta_ingresoForzado(arrayVentas,QTY_VENTAS,"VIDEO4.avi","GBA OESTE",2000,1);
    venta_ingresoForzado(arrayVentas,QTY_VENTAS,"archivo3.mpg","GBA SUR",1500,3);
    venta_ingresoForzado(arrayVentas,QTY_VENTAS,"promo1.avi","GBA SUR",100,3);
    venta_ingresoForzado(arrayVentas,QTY_VENTAS,"promo2.mp4","GBA SUR",100,3);
    venta_ingresoForzado(arrayVentas,QTY_VENTAS,"promo7.avi","GBA SUR",100,3);
    venta_ingresoForzado(arrayVentas,QTY_VENTAS,"promo8.avi","GBA SUR",100,3);


   do
   {
    limpiarPantalla();
       printf("\n<<<MENU>>>\n\n1) ABM CLIENTES\n2) ABM VENTAS\n3) LISTADO DE VENTAS\n4) INFORMES\n5) SALIR");
       input_ScanInt("\nIngrese opcion: ",&opcion);

       switch(opcion)
       {
            case 1 :
                abmClientes(arrayClientes,QTY_CLIENTES,arrayVentas,QTY_VENTAS,&contadorClientes);
                break;
            case 2 :
                if(contadorClientes > 0)
                {
                    abmVentas(arrayClientes,QTY_CLIENTES,arrayVentas,QTY_VENTAS,&contadorVentas);
                }
                else
                {
                    printf("\nNo hay clientes cargados");
                }
                break;

            case 3 :
                if(contadorClientes > 0 && contadorVentas > 0)
                {
                    informar_ClientesPendientes(arrayClientes,QTY_CLIENTES,
                                                arrayVentas,QTY_VENTAS,
                                                contadorClientes,contadorVentas);
                }
                else
                {
                    printf("\nNo hay datos cargados.");
                    printf("\nIngrese cualquier tecla para continuar...");
                    limpiarMemoria();
                    getchar();
                }

                  break;
            case 4 :
                if(contadorClientes > 0 && contadorVentas > 0)
                {

                    informar_menu(arrayClientes,QTY_CLIENTES,arrayVentas,QTY_VENTAS);
                }
                else
                {
                    printf("\nNo hay datos cargados.");
                    printf("\nIngrese cualquier tecla para continuar...");
                    limpiarMemoria();
                    getchar();
                }
                  break;
            case 5 :
                printf("\nCerrando...");
            break;
            default :
                printf("\nOpcion invalida.:P");
                printf("\nIngrese cualquier tecla para continuar...");
                limpiarMemoria();
                getchar();


        }

   }while(opcion != 5);

        return 0;

}




void abmClientes(Cliente arrayUno[],int sizeUno,Venta arrayDos[],int sizeDos,int* counterClient)
{
    Cliente* clienteSeleccionado;
    Venta* ventaSeleccionada;
    int opcion;
    int indice;
    int idIngresado;
    char respuesta[5];
    int contadorClientes;//CAMBIAR PARA HARDCODE

    contadorClientes = *counterClient;

    if(arrayUno != NULL && sizeUno > 0 && arrayDos != NULL && sizeDos > 0)
    {

        do
        {
            limpiarPantalla();
            printf("\n<<<MENU CLIENTES>>>\n\n1) ALTA CLIENTE\n2) MODIFICAR DATOS CLIENTES\n3) BAJA CLIENTE\n4) MENU PRINCIPAL");
            input_ScanInt("\nIngrese opcion: ",&opcion);

            switch(opcion)
           {
                case 1 :

                    printf("\n--ALTA CLIENTE--\n");
                    if(cliente_buscarIndiceLibre(arrayUno,sizeUno) >= 0)
                    {
                        if(!cliente_alta(arrayUno,sizeUno,&indice))
                        {
                            printf("\nID CLIENTE %d",arrayUno[indice].id);
                            contadorClientes++;

                            printf("\nALTA REALIZADA.");

                        }
                        printf("\nIngrese cualquier tecla para continuar...");
                        limpiarMemoria();
                        getchar();

                    }
                    else
                    {
                        printf("\nNo hay espacios libres.");
                        printf("\nIngrese cualquier tecla para continuar...");
                        limpiarMemoria();
                        getchar();
                    }
                break;

                case 2 :
                    if(contadorClientes > 0)
                    {
                        printf("\n--MODIFICAR DATOS CLIENTE--\n");
                        cliente_listar(arrayUno,sizeUno);
                        input_getNumeros(&idIngresado,5,"\nIngrese ID: ","Error",1,200,2);
                        clienteSeleccionado = cliente_getByID(arrayUno,sizeUno,idIngresado);

                        if(clienteSeleccionado != NULL)
                        {
                            if(!cliente_modificar(clienteSeleccionado))
                            {
                                printf("\nMODIFICACION REALIZADA.");
                            }

                            printf("\nIngrese cualquier tecla para continuar...");
                            limpiarMemoria();
                            getchar();
                        }
                        else
                        {
                            printf("\nCliente inexistente");
                             printf("\nIngrese cualquier tecla para continuar...");
                            limpiarMemoria();
                            getchar();
                        }

                    }
                    else
                    {
                        printf("\nNo hay datos cargados.");
                        printf("\nIngrese cualquier tecla para continuar...");
                        limpiarMemoria();
                        getchar();
                    }

                break;

                case 3 :
                    if(contadorClientes > 0)
                    {
                        cliente_listar(arrayUno,sizeUno);
                        input_getNumeros(&idIngresado,5,"\nIngrese ID: ","Error",1,200,2);
                        input_getLetras(respuesta,3,"\nEsta seguro de realizar la baja?","Error.Dato invalido",2);

                        if(!strcmp(respuesta,"si"))
                        {
                            printf("\n--BAJA DE CLIENTE--\n");

                            clienteSeleccionado = cliente_getByID(arrayUno,sizeUno,idIngresado);
                            if(clienteSeleccionado != NULL)
                            {
                                cliente_eliminar(clienteSeleccionado);

                                    do
                                    {
                                        ventaSeleccionada = venta_getByID(arrayDos,sizeDos,idIngresado);

                                       if(ventaSeleccionada != NULL)
                                       {
                                            venta_eliminar(ventaSeleccionada);//REVISAR CONTADOR VENTAS
                                       }

                                    } while(ventaSeleccionada != NULL);

                                contadorClientes--;

                                printf("\nBAJA REALIZADA.");
                                printf("\nIngrese cualquier tecla para continuar...");
                                limpiarMemoria();
                                getchar();
                            }
                            else
                            {
                                printf("\nCliente inexistente");
                                printf("\nIngrese cualquier tecla para continuar...");
                                limpiarMemoria();
                                getchar();
                            }

                        }
                        else if(!strcmp(respuesta,"no"))
                        {
                            break;
                        }
                        else
                        {
                            printf("Error.Opcion incorrecta");
                            printf("\nIngrese cualquier tecla para continuar...");
                            limpiarMemoria();
                            getchar();
                        }

                    }
                    else
                    {
                        printf("\nNo hay datos cargados.");
                        printf("\nIngrese cualquier tecla para continuar...");
                        limpiarMemoria();
                        getchar();
                    }

                break;
                case 4 :
                    *counterClient = contadorClientes;
                    break;

                default :
                    printf("\nOpcion invalida");

           }


        }while(opcion != 4);
    }


}

void abmVentas(Cliente arrayUno[],int sizeUno,Venta arrayDos[],int sizeDos,int* counterSales)
{
    Venta* ventaSeleccionada;
    Cliente* clienteSeleccionado;
    int opcion;
    int idIngresado;
    char respuesta[5];
    int contadorVentas = 5;

    contadorVentas = *counterSales;

    if(arrayUno != NULL && sizeUno > 0 && arrayDos != NULL && sizeDos > 0)
    {

        do
        {
            limpiarPantalla();
            printf("\n<<<MENU VENTAS>>>\n\n1) VENTA AFICHE\n2) EDITAR AFICHE\n3) COBRAR VENTA\n4) MENU PRINCIPAL");
            input_ScanInt("\nIngrese opcion: ",&opcion);

            switch(opcion)
           {

            case 1 :
                 printf("\n--ALTA VENTA--\n");
                if(venta_buscarIndiceLibre(arrayDos,sizeDos) >= 0 )
                {
                    cliente_listar(arrayUno,sizeUno);
                    input_getNumeros(&idIngresado,5,"\nIngrese ID de cliente: ","Error",1,200,2);
                    if(cliente_getByID(arrayUno,sizeUno,idIngresado) != NULL)
                    {
                        if(!venta_alta(arrayDos,sizeDos,idIngresado))
                        {
                            contadorVentas++;
                            printf("\nALTA REALIZADA.");
                        }
                        printf("\nIngrese cualquier tecla para continuar...");
                        limpiarMemoria();
                        getchar();
                    }
                    else
                    {
                        printf("\nEl ID no existe.");
                        printf("\nIngrese cualquier tecla para continuar...");
                        limpiarMemoria();
                        getchar();
                    }

                }
                else
                {
                    printf("\nNo hay espacios libres.");
                    printf("\nIngrese cualquier tecla para continuar...");
                    limpiarMemoria();
                    getchar();
                }
                break;
            case 2 :
                if(contadorVentas > 0)
                {
                    printf("\n--EDITAR VENTA--\n");
                    venta_listar(arrayDos,sizeDos);
                    input_getNumeros(&idIngresado,5,"\nIngrese ID de venta: ","Error",1,2000,2);
                    ventaSeleccionada = venta_getByID(arrayDos,sizeDos,idIngresado);
                    if(ventaSeleccionada != NULL)
                    {
                        if(!venta_modificar(ventaSeleccionada))
                        {
                            printf("\nMODIFICACION REALIZADA.");
                        }
                        printf("\nIngrese cualquier tecla para continuar...");
                        limpiarMemoria();
                        getchar();
                    }
                    else
                    {
                        printf("\nEl ID no existe.");
                         printf("\nIngrese cualquier tecla para continuar...");
                        limpiarMemoria();
                        getchar();
                    }

                }
                else
                {
                    printf("\nNo hay datos cargados.");
                    printf("\nIngrese cualquier tecla para continuar...");
                    limpiarMemoria();
                    getchar();
                }
                break;
            case 3 :
                if(contadorVentas > 0)
                {
                    printf("\n--COBRAR VENTA--\n");

                    venta_listar(arrayDos,sizeDos);
                    input_getNumeros(&idIngresado,5,"\nIngrese ID de venta: ","Error",1,200,2);
                    ventaSeleccionada = venta_getByID(arrayDos,sizeDos,idIngresado);
                    if(ventaSeleccionada != NULL)
                    {
                        clienteSeleccionado = cliente_getByID(arrayUno,sizeUno,ventaSeleccionada->idCliente);
                        cliente_mostrar(clienteSeleccionado);

                        input_getLetras(respuesta,3,"\nDesea cambiar el estado a cobrar?","Error.Dato invalido",2);
                        if(!strcmp(respuesta,"si"))
                        {
                            venta_baja(ventaSeleccionada);
                            contadorVentas--;
                            printf("\nBAJA REALIZADA.");
                            printf("\nIngrese cualquier tecla para continuar...");
                            limpiarMemoria();
                            getchar();
                        }
                        else if(!strcmp(respuesta,"no"))
                        {
                            break;
                        }
                        else
                        {
                            printf("Error.Opcion incorrecta");
                             printf("\nIngrese cualquier tecla para continuar...");
                            limpiarMemoria();
                            getchar();
                        }

                    }
                    else
                    {
                        printf("\nVenta inexistente.");
                         printf("\nIngrese cualquier tecla para continuar...");
                        limpiarMemoria();
                        getchar();
                    }

                }
                else
                {
                    printf("\nNo hay datos cargados.");
                    printf("\nIngrese cualquier tecla para continuar...");
                    limpiarMemoria();
                    getchar();
                }
                 break;
                case 4 :
                    *counterSales = contadorVentas;
                    break;

                default :
                    printf("\nOpcion invalida");

           }


        }while(opcion != 4);
    }
}
