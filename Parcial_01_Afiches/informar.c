#include <stdio_ext.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utn.h"
#include "clientes.h"
#include "ventas.h"
#include "informar.h"

#define QTY_CLIENTES 10



/**
*\brief Lista todas las ventas a cobrar de cada cliente
*\param arrayClientes Es el array de cliente que recibe
*\param arrayVentas Es el array de ventas que recibe
*\param limiteClientes Es el tamaño del array uno
*\param limiteVentas Es el tamaño del array dos
*\return Retorna 0 si los arrays y los limites son validos sino retorna -1
*/

int informar_ClientesPendientes(Cliente arrayClientes[],
                                       int limiteClientes,
                                       Venta arrayVentas[],
                                       int limiteVentas,
                                       int contadorClientes,
                                       int contadorVentas)
{
    int retorno = 0;
    Cliente* clienteSeleccionado;
    int i;

    if(arrayClientes != NULL && arrayVentas != NULL && limiteClientes > 0 && limiteVentas > 0 && contadorClientes > 0 && contadorVentas > 0)
    {
            if(contadorClientes > 0 && contadorVentas > 0)
            {
                printf("\n--IMPRIMIR CLIENTES--\n");

                for(i=0;i<QTY_CLIENTES;i++)
                {
                    clienteSeleccionado = cliente_getByID(arrayClientes,limiteClientes,arrayClientes[i].id);

                    if(clienteSeleccionado != NULL)
                    {
                        cliente_mostrar(clienteSeleccionado);
                        printf("\n\n>>VENTAS A COBRAR<<\nID CLIENTE: %d",arrayClientes[i].id);
                        venta_mostrar(arrayVentas,limiteVentas,arrayClientes[i].id);
                    }
                }
                printf("\nIngrese cualquier tecla para continuar...");
                limpiarMemoria();
                getchar();
            }
                retorno = 0;
    }
        return retorno;
}
/**
*\brief Lista todas las ventas segun CUIT
*\param arrayClientes Es el array de cliente que recibe
*\param arrayVentas Es el array de ventas que recibe
*\param limiteClientes Es el tamaño del array uno
*\param limiteVentas Es el tamaño del array dos
*\return Retorna 0 si se encuentran los clientes sino retorna -1
*/

int informar_ventasPorCuit(Cliente arrayClientes[],
                                 Venta arrayVentas[],
                                int limiteClientes,
                                int limiteVentas)
{
    int retorno = -1;
    char cuitIngresado[13];
    Cliente* clienteSeleccionado;

    if(arrayClientes != NULL && arrayVentas != NULL && limiteClientes > 0 && limiteVentas > 0)
    {
        if(!input_getCuit(cuitIngresado,13,"\nIngrese numero de CUIT: ","Error.Numero invalido",2))//Se ingresa CUIT
        {
            clienteSeleccionado = informar_buscarClienteCuit(arrayClientes,limiteClientes,cuitIngresado);
            if( clienteSeleccionado != NULL)//Se busca ID cliente
            {
                cliente_mostrar(clienteSeleccionado);//Se muestran datos del cliente
                venta_mostrar(arrayVentas,limiteVentas,clienteSeleccionado->id);//Ventas a cobrar
                venta_cobradas(arrayVentas,limiteVentas,clienteSeleccionado->id);//Ventas cobradas
                retorno = 0;
            }
        }
    }

    return retorno;
}


/**
*\brief Lista todas las ventas segun CUIT y Zona
*\param arrayClientes Es el array de cliente que recibe
*\param arrayVentas Es el array de ventas que recibe
*\param limiteClientes Es el tamaño del array uno
*\param limiteVentas Es el tamaño del array dos
*\param opcion Es la opcion de zona a listar
*\return Retorna 0 si se encuentran los clientes sino retorna -1
*/

int informar_ventasPorCuitZona(Cliente arrayClientes[],
                                 Venta arrayVentas[],
                                int limiteClientes,
                                int limiteVentas,
                                int opcion)
{
    int retorno = -1;
    int i;
    char cuitIngresado[13];
    int idCliente;
    Cliente* clienteSeleccionado;


    if(arrayClientes != NULL && arrayVentas != NULL && limiteClientes > 0 && limiteVentas > 0)
    {
        if(!input_getCuit(cuitIngresado,13,"\nIngrese numero de CUIT: ","Error.Numero invalido",2))//Se ingresa CUIT
        {
            clienteSeleccionado = informar_buscarClienteCuit(arrayClientes,limiteClientes,cuitIngresado);//Se busca cliente

            if(clienteSeleccionado != NULL)
            {
                idCliente = clienteSeleccionado->id;

                switch(opcion)
                {
                    case 1 :
                        for(i=0;i<limiteVentas;i++)
                        {
                            if(arrayVentas[i].idCliente == idCliente &&
                               !strcmp(arrayVentas[i].zona,"CABA"))//Se buscan ventas del cliente en zona CABA
                            {
                                cliente_mostrar(clienteSeleccionado);
                                venta_mostrar(arrayVentas,limiteVentas,idCliente);
                                venta_cobradas(arrayVentas,limiteVentas,idCliente);
                            }
                        }
                    break;
                    case 2 :
                        for(i=0;i<limiteVentas;i++)
                        {
                            if(arrayVentas[i].idCliente == idCliente &&
                               !strcmp(arrayVentas[i].zona,"GBA OESTE"))//Se buscan ventas del cliente en zona GBA OESTE
                            {
                                cliente_mostrar(clienteSeleccionado);
                                venta_mostrar(arrayVentas,limiteVentas,idCliente);
                                venta_cobradas(arrayVentas,limiteVentas,idCliente);
                            }
                        }
                    break;
                    case 3 :
                        for(i=0;i<limiteVentas;i++)
                        {
                            if(arrayVentas[i].idCliente == idCliente &&
                               !strcmp(arrayVentas[i].zona,"GBA SUR"))//Se buscan ventas del cliente en zona GBA SUR
                            {
                                cliente_mostrar(clienteSeleccionado);
                                venta_mostrar(arrayVentas,limiteVentas,idCliente);
                                venta_cobradas(arrayVentas,limiteVentas,idCliente);
                            }
                        }
                    break;
                    default :
                        printf("\nOpcion invalida");
                }

                retorno = 0;
            }
        }
    }


    return retorno;
}


/**
*\brief Lista todas las ventas según status
*\param array Es el array de ventas que recibe
*\param size Es el tamaño del array
*\return Retorna 0 si el array es valido sino retorna -1
*/

int informar_statusVentas(Venta array[],
                                int size)
{
    int retorno = -1;
    int i;
    int opcion;

    if(array != NULL && size > 0)
    {
        input_getNumeros(&opcion,3,"\n1) PENDIENTE\n2) COBRADA\n","Opcion invalida",1,2,2);

        switch(opcion)
        {
            case 1 :
                 for(i=0;i<size;i++)
                {
                    if(!strcmp(array[i].status,STATUS_1))//Se buscan ventas A COBRAR
                    {
                        printf("\n\nID CLIENTE -- %d\n",array[i].idCliente);
                        printf("\nNOMBRE DE ARCHIVO-- %s",array[i].nombreAfiche);
                        printf("\nCANTIDAD DE AFICHES-- %d",array[i].cantidad);
                        printf("\nZONA-- %s",array[i].zona);
                        printf("\nSTATUS-- %s",array[i].status);
                    }
                }
            break;

            case 2 :

                for(i=0;i<size;i++)
                {

                    if(!strcmp(array[i].status,STATUS_2))//Se buscan ventas COBRADAS
                    {
                        printf("\nID CLIENTE -- %d",array[i].idCliente);
                        printf("\nID NOMBRE DE ARCHIVO-- %s",array[i].nombreAfiche);
                        printf("\nID CANTIDAD DE AFICHES-- %d",array[i].cantidad);
                        printf("\nID ZONA-- %s",array[i].zona);
                        printf("\nID STATUS-- %s",array[i].status);
                    }
                }
            break;

        }
        retorno = 0;
    }
    return retorno;
}


/**
*\brief Lista todas las ventas a cobrar que superan o no el promedio de afiches
*\param array Es el array de ventas que recibe
*\param size Es el tamaño del array
*\param calculo Es la opcion de calculo segun el case, 1 las que superan, 2 las que no superan
*\return Retorna 0 si el array existe sino retorna -1
*/

int informar_ventasPromedioAfiches(Venta array[],
                                int size,
                                int calculo)//OK
{
    int retorno = -1;
    int i;
    float promedio;

    informar_calculoPromedioCantidad(array,size,&promedio);

    if(array != NULL && size > 0)
    {

        switch(calculo)
        {
            case 1 : //Se buscan ventas A COBRAR que superen el PROMEDIO de cantidad de afiches
             for(i=0;i<size-1;i++)
            {
                if(!strcmp(array[i].status,STATUS_1) && array[i].cantidad > promedio)
                {

                     printf("\n%s",array[i].nombreAfiche);
                     printf("\n%s",array[i].zona);
                     printf("\n%d",array[i].cantidad);
                     printf("\n%d",array[i].idCliente);
                }
            }
            break;

            case 2 : //Se buscan ventas A COBRAR que NO superen el PROMEDIO de cantidad de afiches
            for(i=0;i<size-1;i++)
            {

                if(!strcmp(array[i].status,STATUS_1) && array[i].cantidad < promedio)
                {
                     printf("\n%s",array[i].nombreAfiche);
                     printf("\n%s",array[i].zona);
                     printf("\n%d",array[i].cantidad);
                     printf("\n%d",array[i].idCliente);
                }
            }
            break;
        }
        retorno = 0;
    }
    return retorno;
}


/**
*\brief Calcula la cantidad promedio de afiches de ventas a cobrar
*\param array Es el array de ventas que recibe
*\param size Es el tamaño del array
*\param promedio Es el puntero de la variable promedio para guardar el dato
*\return Retorna 0 si existe el array sino retorna -1
*/

int informar_calculoPromedioCantidad(Venta array[],
                                int size,
                                float* promedio)
{
    int retorno = -1;
    float cantidadTotal = 0;
    int contador = 0;
    int i;

    if(array != NULL && size > 0)
    {
        for(i=0;i<size;i++)
        {
            if(!strcmp(array[i].status,STATUS_1))//CON STATUS "A COBRAR"
            {
                cantidadTotal = cantidadTotal + array[i].cantidad;//Se suma la cantidad de afiches
                contador++;
            }
        }

        *promedio = cantidadTotal / contador;//Se calcula el promedio
        retorno = 0;
    }

    return retorno;
}


/**
*\brief Lista todas las ventas cobradas por zona
*\param array Es el array de ventas que recibe
*\param size Es el tamaño del array uno
*\param opcion Es la opcion de zona a listar
*\return Retorna 0 se muestra una de las listas sino retorna -1
*/

int informar_calculoZonaMenosVenta(Venta array[],
                                int size)
{
    int retorno = -1;
    int contadorVentasCapital = 0;
    int contadorVentasSur = 0;
    int contadorVentasOeste = 0;
    int i;

    if(array != NULL && size > 0)
    {
        for(i=0;i<size;i++)
        {
            if(!strcmp(array[i].status,STATUS_2) && !strcmp(array[i].zona,"CABA"))//CON STATUS "COBRADA"
            {
                contadorVentasCapital++;
            }
        }

        printf("\nTotal de ventas realizadas en CABA: %d",contadorVentasCapital);


        for(i=0;i<size;i++)
        {
            if(!strcmp(array[i].status,STATUS_2) && !strcmp(array[i].zona,"GBA SUR"))//CON STATUS "COBRADA"
            {
                contadorVentasSur++;

            }

        }

            printf("\nTotal de ventas realizadas en GBA SUR: %d",contadorVentasSur);

        for(i=0;i<size;i++)
        {
            if(!strcmp(array[i].status,STATUS_2) && !strcmp(array[i].zona,"GBA OESTE"))//CON STATUS "COBRADA"
            {
                contadorVentasOeste++;
            }
        }

        printf("\nTotal de ventas realizadas en GBA OESTE: %d",contadorVentasOeste);

        if(contadorVentasCapital < contadorVentasSur &&
        contadorVentasCapital < contadorVentasOeste)
        {
            printf("\nLa zona con menor cantidad de ventas es CABA");

        }
        else if(contadorVentasSur < contadorVentasOeste &&
                contadorVentasSur < contadorVentasCapital)
        {
            printf("\nLa zona con menor cantidad de ventas es GBA SUR");
        }
        else
        {
            printf("\nLa zona con menor cantidad de ventas es GBA OESTE");
        }



    }


    return retorno;
}


/**
*\brief Lista todas las ventas cobradas por zona
*\param array Es el array de ventas que recibe
*\param size Es el tamaño del array uno
*\param opcion Es la opcion de zona a listar
*\return Retorna 0 se muestra una de las listas sino retorna -1
*/

int informar_calculoVentasZona(Venta array[],
                                int size)
{
    int retorno = -1;
    int contadorVentasCapital = 0;
    int contadorVentasSur = 0;
    int contadorVentasOeste = 0;
    int i;

    if(array != NULL && size > 0)
    {

        for(i=0;i<size;i++)
        {
            if(!strcmp(array[i].status,STATUS_2) && !strcmp(array[i].zona,"CABA"))//CON STATUS "COBRADA"
            {
                printf("\nID CLIENTE -- %d",array[i].idCliente);
                printf("\nID NOMBRE DE ARCHIVO-- %s",array[i].nombreAfiche);
                printf("\nID CANTIDAD DE AFICHES-- %d",array[i].cantidad);
                printf("\nID ZONA-- %s",array[i].zona);
                printf("\nID STATUS-- %s",array[i].status);
                contadorVentasCapital++;
            }
        }

        printf("\nTotal de ventas realizadas en CABA: %d",contadorVentasCapital);

        for(i=0;i<size;i++)
        {
            if(!strcmp(array[i].status,STATUS_2) && !strcmp(array[i].zona,"GBA SUR"))//CON STATUS "COBRADA"
            {
                printf("\nID CLIENTE -- %d",array[i].idCliente);
                printf("\nID NOMBRE DE ARCHIVO-- %s",array[i].nombreAfiche);
                printf("\nID CANTIDAD DE AFICHES-- %d",array[i].cantidad);
                printf("\nID ZONA-- %s",array[i].zona);
                printf("\nID STATUS-- %s",array[i].status);
                contadorVentasSur++;

            }

        }

        printf("\nTotal de ventas realizadas en GBA SUR: %d",contadorVentasSur);

        for(i=0;i<size;i++)
        {
            if(!strcmp(array[i].status,STATUS_2) && !strcmp(array[i].zona,"GBA OESTE"))//CON STATUS "COBRADA"
            {
                printf("\nID CLIENTE -- %d",array[i].idCliente);
                printf("\nID NOMBRE DE ARCHIVO-- %s",array[i].nombreAfiche);
                printf("\nID CANTIDAD DE AFICHES-- %d",array[i].cantidad);
                printf("\nID ZONA-- %s",array[i].zona);
                printf("\nID STATUS-- %s",array[i].status);
                contadorVentasOeste++;
            }
        }

        printf("\nTotal de ventas realizadas en GBA OESTE: %d",contadorVentasOeste);


        if(contadorVentasCapital < contadorVentasSur &&
            contadorVentasCapital < contadorVentasOeste)
        {
            printf("\nLa zona con menor cantidad de ventas es CABA");

        }
        else if(contadorVentasSur < contadorVentasOeste &&
                contadorVentasSur < contadorVentasCapital)
        {
            printf("\nLa zona con menor cantidad de ventas es GBA SUR");
        }
        else
        {
            printf("\nLa zona con menor cantidad de ventas es GBA OESTE");
        }

    }

    return retorno;
}


/**
*\brief Lista todos los clientes por zona y total de ventas por zona
*\param arrayClientes Es el array de cliente que recibe
*\param arrayVentas Es el array de ventas que recibe
*\param limiteClientes Es el tamaño del array uno
*\param limiteVentas Es el tamaño del array dos
*\param opcion Es la opcion de zona a listar
*\return Retorna 0 si se encuentran los clientes sino retorna -1
*/

int informar_calculoClientesZona(Cliente arrayClientes[],
                                 Venta arrayVentas[],
                                int limiteClientes,
                                int limiteVentas,
                                int opcion)
{
    int retorno = -1;
    int contadorClientes = 0;
    int contadorVentas = 0;
    int totalVentas = 0;
    int flag = 0;
    int i;
    int j;

    if(arrayClientes != NULL &&
       arrayVentas != NULL &&
       limiteClientes > 0 &&
       limiteVentas > 0)
    {
        switch(opcion)
        {
            case 1 :
                contadorClientes = 0;

                for(i=0;i<limiteClientes;i++)//Recorro array clientes
                {
                    if(!arrayClientes[i].isEmpty)
                    {
                        contadorVentas = 0;

                        for(j=0;j<limiteVentas;j++)//Recorro array ventas
                        {
                            if(arrayVentas[j].idCliente == arrayClientes[i].id &&
                               !strcasecmp(arrayVentas[j].zona,"CABA"))//Si encuentra ventas del cliente a cobrar o cobradas entra
                            {
                                contadorVentas++;
                                totalVentas+=contadorVentas;
                                flag = 1;
                            }

                        }

                        if(flag == 1)
                        {
                            cliente_mostrar(arrayClientes+i);//Se muestra cliente de CABA
                            contadorClientes++;
                        }


                        printf("\nCLIENTE-> %s -- ZONA-> CABA -- VENTAS-> %d",arrayClientes[i].cuit,contadorVentas);

                    }

                }
                printf("\n\nTotal de clientes de CABA: %d",contadorClientes);//Total de clientes en CABA
                printf("\nTotal de ventas realizadas en CABA: %d",totalVentas);
                retorno = 0;
                break;
            case 2 :
                contadorClientes = 0;

                for(i=0;i<limiteClientes;i++)//Recorro array clientes
                {
                    if(!arrayClientes[i].isEmpty)
                    {
                        contadorVentas = 0;

                        for(j=0;j<limiteVentas;j++)//Recorro array ventas
                        {
                            if(arrayVentas[j].idCliente == arrayClientes[i].id &&
                               !strcasecmp(arrayVentas[j].zona,"GBA SUR"))//Si encuentra ventas del cliente a cobrar o cobradas entra
                            {
                                contadorVentas++;
                                totalVentas+=contadorVentas;
                                flag = 1;
                            }

                        }

                        if(flag == 1)
                        {
                            cliente_mostrar(arrayClientes+i);//Se muestra cliente de GBA SUR
                            contadorClientes++;
                        }


                        printf("\nCLIENTE-> %s -- ZONA-> GBA SUR -- VENTAS-> %d",arrayClientes[i].cuit,contadorVentas);

                    }

                }
                printf("\n\nTotal de clientes de GBA SUR: %d",contadorClientes);//Total de clientes en GBA SUR
                printf("\nTotal de ventas realizadas en GBA SUR: %d",totalVentas);
                retorno = 0;
                break;
            case 3 :
                contadorClientes = 0;

                for(i=0;i<limiteClientes;i++)//Recorro array clientes
                {
                    if(!arrayClientes[i].isEmpty)
                    {
                        contadorVentas = 0;

                        for(j=0;j<limiteVentas;j++)//Recorro array ventas
                        {
                            if(arrayVentas[j].idCliente == arrayClientes[i].id &&
                               !strcasecmp(arrayVentas[j].zona,"GBA OESTE"))//Si encuentra ventas del cliente a cobrar o cobradas entra
                            {
                                contadorVentas++;
                                totalVentas+=contadorVentas;
                                flag = 1;
                            }

                        }

                        if(flag == 1)
                        {
                            cliente_mostrar(arrayClientes+i);//Se muestra cliente de GBA OESTE
                            contadorClientes++;
                        }


                        printf("\nCLIENTE-> %s -- ZONA-> GBA OESTE -- VENTAS-> %d",arrayClientes[i].cuit,contadorVentas);

                    }

                }
                printf("\n\nTotal de clientes de GBA OESTE: %d",contadorClientes);//Total de clientes en GBA OESTE
                printf("\nTotal de ventas realizadas en GBA OESTE: %d",totalVentas);
                retorno = 0;
                break;
            default :
                {
                    printf("\nZona invalida");
                }

        }


    }

    return retorno;
}



/**
*\brief Lista cantidad de afiches vendidos por zona
*\param arrayClientes Es el array de cliente que recibe
*\param arrayVentas Es el array de ventas que recibe
*\param limiteClientes Es el tamaño del array uno
*\param limiteVentas Es el tamaño del array dos
*\param opcion Es la opcion de zona a listar
*\return Retorna 0 si se encuentran los clientes sino retorna -1
*/

int informar_calculoAfichesZona(Venta array[], int size)
{
    int retorno = -1;
    int acumAfiches = 0;
    int i;

    if(array != NULL &&
       size > 0)
    {


            for(i=0;i<size;i++)//Recorro array clientes
            {

                    if(strcasecmp(array[i].status,STATUS_2) &&
                       !strcasecmp(array[i].zona,"CABA"))//Ventas de CABA
                    {
                        acumAfiches+=array[i].cantidad;
                    }

            }
            printf("\nTotal de afiches de CABA: %d",acumAfiches);//Total de afiches en CABA


            acumAfiches = 0;

            for(i=0;i<size;i++)//Recorro array clientes
            {

                    if(strcasecmp(array[i].status,STATUS_2) &&
                       !strcasecmp(array[i].zona,"GBA SUR"))//Ventas de GBA SUR
                    {
                        acumAfiches+=array[i].cantidad;
                    }

            }
            printf("\nTotal de afiches de GBA SUR: %d",acumAfiches);//Total de afiches en GBA SUR


            acumAfiches = 0;

            for(i=0;i<size;i++)//Recorro array clientes
            {

                    if(strcasecmp(array[i].status,STATUS_2) &&
                       !strcasecmp(array[i].zona,"GBA OESTE"))//Ventas de GBA OESTE
                    {
                        acumAfiches+=array[i].cantidad;
                    }

            }
            printf("\nTotal de afiches de GBA OESTE: %d",acumAfiches);//Total de afiches en GBA OESTE

        retorno = 0;
    }



    return retorno;
}




/**
*\brief Lista los clientes con mas ventas
*\param arrayClientes Es el array de cliente que recibe
*\param arrayVentas Es el array de ventas que recibe
*\param limiteClientes Es el tamaño del array uno
*\param limiteVentas Es el tamaño del array dos
*\return Retorna 0 si existen los arrays y son validos los limites sino retorna -1
*/

int informar_clienteMasVentas(Cliente arrayClientes[],Venta arrayVentas[],
                                int limiteClientes,int limiteVentas)
{
    int retorno = -1;
    int i;
    int flag = 1;
    int contadorVentasUno = 0;
    int contadorVentasDos = 0;
    int contadorClientes = 0;
    int totalVentas;
    int mayorCantidad;
    Cliente arrayClientesVenta[limiteClientes];
    Venta* ventaSeleccionada;

    if(arrayClientes != NULL && arrayVentas != NULL && limiteClientes > 0 && limiteVentas > 0)
    {

        for(i=0;i<limiteClientes;i++)//Recorro array clientes
        {
            contadorVentasUno = 0;
            contadorVentasDos = 0;

            ventaSeleccionada = venta_getByID(arrayVentas,limiteVentas,arrayClientes[i].id);

            if(!arrayClientes[i].isEmpty && ventaSeleccionada != NULL)
            {
                contadorVentasUno = informar_calculoTotalVentas(arrayVentas,limiteVentas,arrayClientes[i].id,STATUS_1);
                contadorVentasDos = informar_calculoTotalVentas(arrayVentas,limiteVentas,arrayClientes[i].id,STATUS_2);
                totalVentas = contadorVentasUno + contadorVentasDos;
            }

            if(flag == 1 ||
               totalVentas > mayorCantidad ||
               totalVentas == mayorCantidad)//Guardo el dato de mayor cantidad de ventas
            {
                mayorCantidad = totalVentas;
                arrayClientesVenta[i] = arrayClientes[i];
                contadorClientes++;
                flag = 0;
            }
        }

        printf("\nCLIENTES CON MAYOR VENTA %d",contadorClientes);
        printf("\nMAYOR CANTIDAD DE VENTAS %d",mayorCantidad);

        for(i=0;i<contadorClientes-1;i++)//Muestro los datos de los clientes con mayor cantidad de ventas
        {
            if(arrayClientesVenta != NULL)
            {
                cliente_mostrar(arrayClientesVenta+i);
            }
        }
            retorno = 0;
    }

    return retorno;
}


/**
*\brief Lista los clientes con mas ventas pendientes
*\param arrayClientes Es el array de cliente que recibe
*\param arrayVentas Es el array de ventas que recibe
*\param limiteClientes Es el tamaño del array uno
*\param limiteVentas Es el tamaño del array dos
*\return Retorna 0 si existen los arrays y son validos los limites sino retorna -1
*/

int informar_clienteMasVentasPendientes(Cliente arrayClientes[],Venta arrayVentas[],
                                int limiteClientes,int limiteVentas)
{
    int retorno = -1;
    int i;
    int flag = 1;
    int contadorVentas = 0;
    int contadorClientes = 0;
    int mayorCantidad;
    Cliente arrayClientesVenta[limiteClientes];
    int arrayCantidad[limiteClientes];
    Venta* ventaSeleccionada;

    if(arrayClientes != NULL && arrayVentas != NULL && limiteClientes > 0 && limiteVentas > 0)
    {

        for(i=0;i<limiteClientes;i++)//Recorro array clientes
        {
            contadorVentas = 0;
            ventaSeleccionada = venta_getByID(arrayVentas,limiteVentas,arrayClientes[i].id);

            if(!arrayClientes[i].isEmpty && ventaSeleccionada != NULL)
            {
                contadorVentas = informar_calculoTotalVentas(arrayVentas,limiteVentas,arrayClientes[i].id,STATUS_1);
            }

            if(flag == 1 || contadorVentas > mayorCantidad || contadorVentas == mayorCantidad)//Guardo el dato de mayor cantidad de ventas
            {
                mayorCantidad = contadorVentas;
                arrayClientesVenta[i] = arrayClientes[i];
                arrayCantidad[i] = contadorVentas;
                contadorClientes++;

                flag = 0;
            }

        }


        for(i=0;i<contadorClientes;i++)//Muestro los datos de los clientes con mayor cantidad de ventas
        {
            if(arrayClientesVenta != NULL && arrayCantidad[i] == mayorCantidad)
            {
                cliente_mostrar(arrayClientesVenta+i);
            }
        }

        printf("\nCLIENTES CON MAYOR VENTA %d",contadorClientes);
        printf("\nMAYOR CANTIDAD DE VENTAS %d",mayorCantidad);


            retorno = 0;
    }

    return retorno;
}


/**
*\brief Calculo total de ventas por clientes
*\param arrayVentas Es el array de ventas que recibe
*\param limiteVentas Es el tamaño del array dos
*\param idIngresado Es el ID del cliente a comparar
*\param status Es el status de la venta
*\return Retorna 0 si existen los arrays y son validos los limites sino retorna -1
*/

int informar_calculoTotalVentas(Venta array[],int size,int idIngresado,char status[])
{
    int retorno = -1;
    int i;
    int contadorVentas = 0;
    Venta* ventaSeleccionada;

     for(i=0;i<size;i++)//Recorro array ventas
    {
        if(array[i].idCliente == idIngresado)//Busca las ventas relacionadas al cliente
        {
            ventaSeleccionada = venta_getByID(array,size,idIngresado);

            if(ventaSeleccionada != NULL && !strcmp(ventaSeleccionada->status,status))
            {
                contadorVentas++;//Sumo la venta cobrada del cliente
            }
        }
    }
    retorno = contadorVentas;

    return retorno;
}



/**
*\brief Calculo total de afiches por cliente
*\param arrayVentas Es el array de ventas que recibe
*\param limiteVentas Es el tamaño del array dos
*\param idIngresado Es el ID del cliente a comparar
*\param status Es el status de la venta
*\return Retorna 0 si existen los arrays y son validos los limites sino retorna -1
*/

int informar_calculoTotalAfiches(Venta array[],int size,int idIngresado,char status[])
{
    int retorno = -1;
    int i;
    int contadorAfiches = 0;
    Venta* ventaSeleccionada;

     for(i=0;i<size;i++)//Recorro array ventas
    {
        if(array[i].id == idIngresado)//Busca las ventas relacionadas al cliente
        {
            ventaSeleccionada = venta_getByID(array,size,idIngresado);

            if(ventaSeleccionada != NULL && !strcmp(ventaSeleccionada->status,status))
            {
                contadorAfiches++;//Sumo la venta cobrada del cliente
            }
        }
    }
    retorno = contadorAfiches;

    return retorno;
}



/**
*\brief Lista los clientes con mas ventas cobradas
*\param arrayClientes Es el array de cliente que recibe
*\param arrayVentas Es el array de ventas que recibe
*\param limiteClientes Es el tamaño del array uno
*\param limiteVentas Es el tamaño del array dos
*\return Retorna 0 si existen los arrays y son validos los limites sino retorna -1
*/

int informar_clienteMasVentasCobradas(Cliente arrayClientes[],Venta arrayVentas[],
                                int limiteClientes,int limiteVentas)//OK
{
    int retorno = -1;
    int i;


    int contadorVentas = 0;
    int contadorClientes = 0;
    int mayorCantidad = 0;
    Cliente* clienteSeleccionado;
    Venta* ventaSeleccionada;


    if(arrayClientes != NULL && arrayVentas != NULL && limiteClientes > 0 && limiteVentas > 0)//menor a 10
    {

        for(i=0;i<limiteClientes;i++)//Recorro array clientes
        {
            contadorVentas = 0;

            ventaSeleccionada = venta_getByID(arrayVentas,limiteVentas,arrayClientes[i].id);

            if(!arrayClientes[i].isEmpty && ventaSeleccionada != NULL)
            {
               contadorVentas = informar_calculoTotalVentas(arrayVentas,limiteVentas,arrayClientes[i].id,STATUS_2);
            }

            if(contadorVentas > mayorCantidad || contadorVentas > 0)//Guardo el dato de mayor cantidad de ventas
            {
                mayorCantidad = contadorVentas;
                clienteSeleccionado = &arrayClientes[i];
                contadorClientes++;
            }
        }

        contadorClientes = 0;


        if(clienteSeleccionado != NULL)
        {
            cliente_mostrar(clienteSeleccionado);
        }
        printf("\nCLIENTES CON MAYOR VENTA COBRADAS %d",contadorClientes);
        printf("\nMAYOR CANTIDAD DE VENTAS %d",mayorCantidad);

            retorno = 0;
    }
    return retorno;
}


/**
*\brief Lista los clientes con menos ventas pendientes
*\param arrayClientes Es el array de cliente que recibe
*\param arrayVentas Es el array de ventas que recibe
*\param limiteClientes Es el tamaño del array uno
*\param limiteVentas Es el tamaño del array dos
*\return Retorna 0 si existen los arrays y son validos los limites sino retorna -1
*/

int informar_clienteMenosVentasPendientes(Cliente arrayClientes[],Venta arrayVentas[],
                                int limiteClientes,int limiteVentas)//OK
{
    int retorno = -1;
    int i;
    int flag = 1;
    int contadorVentas = 0;
    int contadorClientes = 0;
    int menorCantidad;
    Cliente arrayClientesVenta[limiteClientes];

    if(arrayClientes != NULL && arrayVentas != NULL && limiteClientes > 0 && limiteVentas > 0)//menor a 10
    {

        for(i=0;i<limiteClientes;i++)//Recorro array clientes
        {
            contadorVentas = 0;

            if(!arrayClientes[i].isEmpty)
            {
              contadorVentas = informar_calculoTotalVentas(arrayVentas,limiteVentas,arrayClientes[i].id,STATUS_1);
            }

            if(flag == 1 ||
               contadorVentas < menorCantidad ||
               contadorVentas == menorCantidad)//Guardo el dato de la menor cantidad de ventas
            {
                menorCantidad = contadorVentas;
                arrayClientesVenta[i] = arrayClientes[i];
                contadorClientes++;
                flag = 0;
            }
        }

        printf("\nCLIENTES CON MENOS VENTA %d",contadorClientes);
        printf("\nMENOR CANTIDAD DE VENTAS %d",menorCantidad);
        for(i=0;i<contadorClientes;i++)//Muestro los datos de los clientes con menor cantidad de ventas
        {
            if(arrayClientesVenta != NULL)
            {
                cliente_mostrar(arrayClientesVenta+i);
            }
        }

            retorno = 0;
    }

    return retorno;
}


/**
*\brief Lista los clientes con menos ventas cobradas
*\param arrayClientes Es el array de cliente que recibe
*\param arrayVentas Es el array de ventas que recibe
*\param limiteClientes Es el tamaño del array uno
*\param limiteVentas Es el tamaño del array dos
*\return Retorna 0 si existen los arrays y son validos los limites sino retorna -1
*/

int informar_clienteMenosVentasCobradas(Cliente arrayClientes[],Venta arrayVentas[],
                                int limiteClientes,int limiteVentas)//OK
{
    int retorno = -1;
    int i;
    int flag = 1;
    int contadorVentas = 0;
    int contadorClientes = 0;
    int menorCantidad;
    Cliente arrayClientesVenta[limiteClientes];

    if(arrayClientes != NULL && arrayVentas != NULL && limiteClientes > 0 && limiteVentas > 0)//menor a 10
    {

        for(i=0;i<limiteClientes;i++)//Recorro array clientes
        {
            contadorVentas = 0;

            if(!arrayClientes[i].isEmpty)
            {
                contadorVentas = informar_calculoTotalVentas(arrayVentas,limiteVentas,arrayClientes[i].id,STATUS_2);
            }

            if(flag == 1 ||
               contadorVentas <  menorCantidad ||
               contadorVentas == menorCantidad)//Guardo el dato de menor cantidad de ventas
            {
                menorCantidad = contadorVentas;
                arrayClientesVenta[i] = arrayClientes[i];
                contadorClientes++;
                flag = 0;
            }
        }

        printf("\nCLIENTES CON MENOS VENTA %d",contadorClientes);
        printf("\nMENOR CANTIDAD DE VENTAS %d",menorCantidad);
        for(i=0;i<contadorClientes;i++)//Muestro los datos de los clientes con menor cantidad de ventas
        {
            if(arrayClientesVenta != NULL)
            {
                cliente_mostrar(arrayClientesVenta+i);
            }
        }

            retorno = 0;
    }

    return retorno;
}

/**
*\brief Lista los clientes con menos de mil afiches comprados
*\param arrayClientes Es el array de cliente que recibe
*\param arrayVentas Es el array de ventas que recibe
*\param limiteClientes Es el tamaño del array uno
*\param limiteVentas Es el tamaño del array dos
*\return Retorna 0 si existen los arrays y son validos los limites sino retorna -1
*/

int informar_clientesAfichesMenorMil(Cliente arrayClientes[],Venta arrayVentas[],
                                int limiteClientes,int limiteVentas)
{

    int retorno = -1;
    int i;
    int acumAfiches = 0;
    int contadorClientes = 0;
    Cliente* clienteSeleccionado;
    Venta* ventaSeleccionada;

    if(arrayClientes != NULL && arrayVentas != NULL && limiteClientes > 0 && limiteVentas > 0)//menor a 10
    {

        for(i=0;i<limiteClientes;i++)//Recorro array clientes
        {
            acumAfiches = 0;
            ventaSeleccionada = venta_getByID(arrayVentas,limiteVentas,arrayClientes[i].id);

            if(!arrayClientes[i].isEmpty && ventaSeleccionada != NULL)
            {
              acumAfiches = informar_calculoTotalAfiches(arrayVentas,limiteVentas,arrayClientes[i].id,STATUS_2);
            }

            if(acumAfiches < 1000)//Guardo el dato de mayor cantidad de afiches
            {
                clienteSeleccionado = &arrayClientes[i];
                contadorClientes++;
            }
        }

        printf("\nCLIENTES CON MENOS DE MIL AFICHES COMPRADOS %d",contadorClientes);
        if(clienteSeleccionado != NULL)
        {
            cliente_mostrar(clienteSeleccionado);
        }
         retorno = 0;

    }



    return retorno;
}



/**
*\brief Lista los clientes con mayor cantidad de afiches a cobrar
*\param arrayClientes Es el array de cliente que recibe
*\param arrayVentas Es el array de ventas que recibe
*\param limiteClientes Es el tamaño del array uno
*\param limiteVentas Es el tamaño del array dos
*\return Retorna 0 si existen los arrays y son validos los limites sino retorna -1
*/

int informar_clienteMasAfiches(Cliente arrayClientes[],Venta arrayVentas[],
                                int limiteClientes,int limiteVentas)
{

    int retorno = -1;
    int i;
    int flag = 1;
    int acumAfiches = 0;
    int contadorClientes = 0;
    int mayorCantidad;
    Cliente* clienteSeleccionado;
    Venta* ventaSeleccionada;

    if(arrayClientes != NULL && arrayVentas != NULL && limiteClientes > 0 && limiteVentas > 0)//menor a 10
    {

        for(i=0;i<limiteClientes;i++)//Recorro array clientes
        {
            acumAfiches = 0;

            ventaSeleccionada = venta_getByID(arrayVentas,limiteVentas,arrayClientes[i].id);

            if(!arrayClientes[i].isEmpty && ventaSeleccionada != NULL)
            {
                acumAfiches = informar_calculoTotalAfiches(arrayVentas,limiteVentas,arrayClientes[i].id,STATUS_1);
            }

            if(flag == 1 ||
               acumAfiches > mayorCantidad)//Guardo el dato de mayor cantidad de afiches
            {
                mayorCantidad = acumAfiches;
                clienteSeleccionado = &arrayClientes[i];
                contadorClientes++;
                flag = 0;
            }
        }

        printf("\nCLIENTES CON MAYOR CANTIDAD DE AFICHES A PAGAR %d",contadorClientes);
        printf("\nMAYOR CANTIDAD DE AFICHES %d",mayorCantidad);


        if(clienteSeleccionado != NULL)
        {
            cliente_mostrar(clienteSeleccionado);
        }
            retorno = 0;
    }

    return retorno;
}



/**
*\brief Lista los clientes con mayor cantidad de afiches a cobrar
*\param arrayClientes Es el array de cliente que recibe
*\param arrayVentas Es el array de ventas que recibe
*\param limiteClientes Es el tamaño del array uno
*\param limiteVentas Es el tamaño del array dos
*\return Retorna 0 si existen los arrays y son validos los limites sino retorna -1
*/

int informar_clienteMasAfichesPagados(Cliente arrayClientes[],Venta arrayVentas[],
                                int limiteClientes,int limiteVentas)
{

    int retorno = -1;
    int i;
    int flag = 1;
    int acumAfiches = 0;
    int contadorClientes = 0;
    int mayorCantidad;
    Cliente* clienteSeleccionado;


    if(arrayClientes != NULL && arrayVentas != NULL && limiteClientes > 0 && limiteVentas > 0)//menor a 10
    {

        for(i=0;i<limiteClientes;i++)//Recorro array clientes
        {
            acumAfiches = 0;

            if(!arrayClientes[i].isEmpty)
            {
                acumAfiches = informar_calculoTotalAfiches(arrayVentas,limiteVentas,arrayClientes[i].id,STATUS_1);
            }

            if(flag == 1 ||
               acumAfiches > mayorCantidad)//Guardo el dato de mayor cantidad de afiches
            {
                mayorCantidad = acumAfiches;
                clienteSeleccionado = &arrayClientes[i];

                flag = 0;
            }
        }

        printf("\nCLIENTE CON MAYOR CANTIDAD DE AFICHES PAGADOS %d",contadorClientes);

        if(clienteSeleccionado != NULL)
        {
            cliente_mostrar(clienteSeleccionado);
        }


            retorno = 0;
    }

    return retorno;
}




/**
*\brief Lista los clientes con menor cantidad de afiches
*\param arrayClientes Es el array de cliente que recibe
*\param arrayVentas Es el array de ventas que recibe
*\param limiteClientes Es el tamaño del array uno
*\param limiteVentas Es el tamaño del array dos
*\return Retorna 0 si existen los arrays y son validos los limites sino retorna -1
*/

int informar_clienteMenosAfiches(Cliente arrayClientes[],Venta arrayVentas[],
                                int limiteClientes,int limiteVentas)
{

    int retorno = -1;
    int i;
    int flag = 1;
    int acumAfiches = 0;
    int contadorClientes = 0;
    int menorCantidad;
    Cliente arrayClientesVenta[limiteClientes];

    if(arrayClientes != NULL && arrayVentas != NULL && limiteClientes > 0 && limiteVentas > 0)//menor a 10
    {

        for(i=0;i<limiteClientes;i++)//Recorro array clientes
        {
            acumAfiches = 0;

            if(!arrayClientes[i].isEmpty)
            {
                acumAfiches = informar_calculoTotalAfiches(arrayVentas,limiteVentas,arrayClientes[i].id,STATUS_1);
            }

            if(flag == 1 ||
               acumAfiches < menorCantidad ||
               acumAfiches == menorCantidad)//Guardo el dato de menor cantidad de ventas
            {
                menorCantidad = acumAfiches;
                arrayClientesVenta[i] = arrayClientes[i];
                contadorClientes++;
                flag = 0;
            }
        }

        printf("\nCLIENTES CON MENOR CANTIDAD DE AFICHES %d",contadorClientes);
        printf("\nMENOR CANTIDAD DE AFICHES %d",menorCantidad);

        for(i=0;i<contadorClientes;i++)//Muestro los datos de los clientes con mayor cantidad de ventas
        {
            if(arrayClientesVenta != NULL)
            {
                cliente_mostrar(arrayClientesVenta+i);
            }
        }
            retorno = 0;
    }

    return retorno;
}

/**
*\brief Cantidad promedio de afiches vendidos por clientes
*\param arrayClientes Es el array de cliente que recibe
*\param arrayVentas Es el array de ventas que recibe
*\param limiteClientes Es el tamaño del array uno
*\param limiteVentas Es el tamaño del array dos
*\return Retorna 0 si existen los arrays y son validos los limites sino retorna -1
*/

int informar_promedioAfichesClientes(Cliente arrayClientes[],Venta arrayVentas[],
                                int limiteClientes,int limiteVentas)
{
    int retorno = -1;
    int i;
    int acumAfiches = 0;
    int contadorClientes = 0;
    float promedioAfiches = 0;
    Venta* ventaSeleccionada;

    if(arrayClientes != NULL && arrayVentas != NULL && limiteClientes > 0 && limiteVentas > 0)//menor a 10
    {

        for(i=0;i<limiteClientes;i++)//Recorro array clientes
        {
            ventaSeleccionada = venta_getByID(arrayVentas,limiteVentas,arrayVentas[i].id);

            if(!arrayClientes[i].isEmpty && ventaSeleccionada != NULL)
            {
                acumAfiches += informar_calculoTotalAfiches(arrayVentas,limiteVentas,arrayClientes[i].id,STATUS_2);
                contadorClientes++;
            }


        }

        promedioAfiches = acumAfiches / contadorClientes;

        printf("\nPROMEDIO DE AFICHES VENDIDOS POR CLIENTES %.2f",promedioAfiches);

    }


    return retorno;

}



/**
*\brief Menu con opciones de informes
*\param arrayClientes Es el array de cliente que recibe
*\param limiteClientes Es el tamaño del array uno
*\param arrayVentas Es el array de ventas que recibe
*\param limiteVentas Es el tamaño del array dos
*\return Retorna 0 si existen los arrays y son validos los limites sino retorna -1
*/


int informar_menu(Cliente arrayClientes[],int limiteClientes,Venta arrayVentas[],int limiteVentas)
{
    int retorno = -1;
    int opcion;

    if(arrayClientes != NULL && limiteClientes > 0 && arrayVentas != NULL && limiteVentas > 0)
    {

        do
        {
            limpiarPantalla();
             printf("\n--INFORMES--\n");
            printf("\n1) CLIENTE CON MAS VENTAS A COBRAR\n2) CLIENTE CON MAS VENTAS COBRADAS");
            printf("\n3) CLIENTE CON MAS VENTAS\n4) CLIENTE CON MAYOR CANTIDAD DE AFICHES A COBRAR");
            printf("\n5) CLIENTE MAYOR CANTIDAD DE AFICHES COMPRADOS\n6) ZONA CON MENOS AFICHES VENDIDOS");
            printf("\n7) CLIENTE CON MENOS DE MIL AFICHES COMPRADOS\n8) CANTIDAD DE AFICHES VENDIDOS POR ZONA");
            printf("\n9) LISTADO DE VENTAS ORDENADO POR ZONA\n10) PROMEDIO DE AFICHES POR CLIENTES");
            printf("\n11) MENU PRINCIPAL");

        input_ScanInt("\n\nIngrese opcion: ",&opcion);


            switch(opcion)
            {
                case 1:
                    informar_clienteMasVentasPendientes(arrayClientes,arrayVentas,limiteClientes,limiteVentas);
                    printf("\nIngrese cualquier tecla para continuar...");
                    limpiarMemoria();
                    getchar();
                break;
                case 2:
                    informar_clienteMasVentasCobradas(arrayClientes,arrayVentas,limiteClientes,limiteVentas);
                    printf("\nIngrese cualquier tecla para continuar...");
                    limpiarMemoria();
                    getchar();
                break;
                case 3:
                    informar_clienteMasVentas(arrayClientes,arrayVentas,limiteClientes,limiteVentas);
                    printf("\nIngrese cualquier tecla para continuar...");
                    limpiarMemoria();
                    getchar();
                break;
                case 4:
                    informar_clienteMasAfiches(arrayClientes,arrayVentas,limiteClientes,limiteVentas);
                    printf("\nIngrese cualquier tecla para continuar...");
                    limpiarMemoria();
                    getchar();
                break;
                case 5:
                    informar_clienteMasAfichesPagados(arrayClientes,arrayVentas,limiteClientes,limiteVentas);
                    printf("\nIngrese cualquier tecla para continuar...");
                    limpiarMemoria();
                    getchar();
                break;
                case 6:
                    informar_calculoZonaMenosVenta(arrayVentas,limiteVentas);
                    printf("\nIngrese cualquier tecla para continuar...");
                    limpiarMemoria();
                    getchar();
                break;
                case 7 :
                    informar_clientesAfichesMenorMil(arrayClientes,arrayVentas,limiteClientes,limiteVentas);
                    printf("\nIngrese cualquier tecla para continuar...");
                    limpiarMemoria();
                    getchar();
                break;
                case 8:
                    informar_calculoAfichesZona(arrayVentas,limiteVentas);
                    printf("\nIngrese cualquier tecla para continuar...");
                    limpiarMemoria();
                    getchar();
                break;
                case 9:
                    venta_ordenar(arrayVentas,limiteVentas);
                    venta_listar(arrayVentas,limiteVentas);
                    printf("\nIngrese cualquier tecla para continuar...");
                    limpiarMemoria();
                    getchar();
                break;
                case 10:
                    informar_promedioAfichesClientes(arrayClientes,arrayVentas,limiteClientes,limiteVentas);
                    printf("\nIngrese cualquier tecla para continuar...");
                    limpiarMemoria();
                    getchar();
                break;
                 case 11:

                break;
                default :
                    printf("\nOpcion incorrecta");
                    printf("\nIngrese cualquier tecla para continuar...");
                    limpiarMemoria();
                    getchar();
            }


        }while(opcion != 11);

        retorno = 0;

    }


    return retorno;
}


Cliente* informar_buscarClienteCuit(Cliente array[],int size,char cuit[])
{
    Cliente* retorno = NULL;
    int i;

    for(i=0;i<size;i++)
    {
        if(!strcmp(array[i].cuit,cuit))
        {
            retorno = array+i;
            break;
        }
    }
    return retorno;
}


