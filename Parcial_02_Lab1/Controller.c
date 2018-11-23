#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "Controller.h"
#include "LinkedList.h"
#include "Venta.h"
#include "utn.h"
#include "parser.h"

#define BUFFER 4000
#define LEN_LL 6

extern int errno ;

/**
* \brief Muestra la fecha actual y el horario
* \param void
* \return Retorna fecha y hora en formato string sino retorna NULL
*/
static char* fecha()
{
    char* retorno = NULL;
    time_t rawtime;//Variable tipo time_t
    struct tm *info;//Tipo de dato tm para cargar fecha y hora

    time(&rawtime);//Se obtiene dia y hora actual
    info = localtime( &rawtime );//Se obtiene formato para fecha y hora
    retorno = asctime(info);

    // printf("%s", asctime(info));//Se muestra informacion
    return retorno;
}

/**
 * \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 * \param path Ruta del archivo para leer
 * \param pLinkedList Es el LinkedList
 * \return retorna 0 si el array no es null y el archivo existe sino retorna -1
 *
 */
int controller_loadFromText(char* path , LinkedList* pLinkedList)
{
    int retorno = -1;
    FILE* pFile = fopen(path,"r");

    if(pLinkedList != NULL && pFile != NULL)
    {
        if(!parser_VentaFromText(pFile,pLinkedList))
        {
            retorno = 0;
            fclose(pFile);
        }
    }
    return retorno;
}


/**
 * \brief Alta de empleados
 * \param pLinkedList Es el LinkedList donde se agregara el empleado
 * \return Retorna 0 si se logra hacer el alta sino retorna -1
 *
 */
int controller_addVenta(LinkedList* pLinkedList)
{
    int retorno = -1;
    limpiarPantalla();

    if(pLinkedList != NULL)
    {
        printf("<ALTA>");
        if(!venta_add(pLinkedList))
        {
            printf("\nAlta realizada.");
            retorno = 0;
        }
    }
    return retorno;
}



/**
 * \brief Listar empleados
 * \param pLinkedList Es la LinkedList de la cual se desea listar los elementos
 * \return retorna 0 si la LinkedList es diferente a NULL sino retorna -1
 *
 */
int controller_ListVenta(LinkedList* pLinkedList)
{
    int retorno = -1;
    int i;
    Venta* this;

    if(pLinkedList != NULL && !ll_isEmpty(pLinkedList))
    {
        retorno = 0;
        this = ll_get(pLinkedList,2);
       venta_show(this);

        printf("\nTotal ventas %d",ll_len(pLinkedList));
    }
    else
    {
        printf("\nLista inexistente");
    }
    return retorno;
}

/** \brief Genera una nueva lista a partir de la primer lista
 *          la nueva lista se guarda como archivo
 * \param listaPrincipal Es el array de LinkedList para utilizar listados
 * \return Retorna 0 si se logra editar sino retorna -1
 *
 */
int controller_generateNewList(LinkedList* listaPrincipal)
{
    int retorno = -1;
    int ventasMayor10k = 0;
    int ventasMayor20k  = 0;
    int cantidadLCD  = 0;
    int unidadesTotales  = 0;
    char stringAux[BUFFER];
    char informes[BUFFER];
    FILE* pFile = fopen("informes.txt","w");

    if(listaPrincipal != NULL && pFile != NULL)
    {
        printf("\nCONTROL");
        ventasMayor20k = ll_count(listaPrincipal,venta_seleccionarVenta20k);
        ventasMayor10k = ll_count(listaPrincipal,venta_seleccionarVenta10k);
        cantidadLCD = ll_count(listaPrincipal,venta_seleccionarLCD);
        unidadesTotales = ll_count(listaPrincipal,venta_unidades);

        printf("\nVentas + 20k %d",ventasMayor20k);
        printf("\nVentas + 10k %d",ventasMayor10k);
        printf("\nLCD totales %d",cantidadLCD);
        printf("\nUnidades totales %d",unidadesTotales);

        sprintf(stringAux,"\n*********************\nInforme de ventas\n******************");
        strcat(informes,stringAux);
        sprintf(stringAux,"\n- Cantidad de unidades vendidas totales: %d",unidadesTotales);
        strcat(informes,stringAux);
        sprintf(stringAux,"\n- Cantidad de ventas por un monto mayor a $10000: %d",ventasMayor10k);
        strcat(informes,stringAux);
        sprintf(stringAux,"\n- Cantidad de ventas por un monto mayor a $20000: %d",ventasMayor20k);
        strcat(informes,stringAux);
        sprintf(stringAux,"\n- Cantidad de TVs LCD vendidas: %d",cantidadLCD);
        strcat(informes,stringAux);
        sprintf(stringAux,"\n******************");
        strcat(informes,stringAux);

        if(informes != NULL)
        {
            fprintf(pFile,informes);
        }
        retorno = 0;
    }
    return retorno;
}


/**
 * \brief Ordenar empleados por criterio y orden
 * \param pLinkedList Es la LinkedList que se desea ordenar
 * \return retorna 0 si se logra ordenar sino retorna -1
 *
 */
int controller_sortVenta(LinkedList* pLinkedList)
{
    int retorno = -1;

    if(pLinkedList != NULL)
    {
        if(!venta_sort(pLinkedList))
        {
            retorno = 0;
        }
    }
    return retorno;
}


/**
 * \brief Guarda los datos de los empleados en archivo en la carpeta /files (modo texto).
 * \param path Ruta donde se guardara el archivo
 * \param pLinkedList Es la LinkedList con los elementos a guardar
 * \return Retorna 0 si se logra guardar sino retorna -1
 *
 */
int controller_saveAsText(char* path , LinkedList* pLinkedList)
{
    FILE* pArchivo = fopen(path,"w");
    int retorno = -1;

    printf("<GUARDAR TEXTO>");
    if(pArchivo != NULL && !parser_SaveToText(pArchivo,pLinkedList))
    {
        retorno = 0;
    }
    fclose(pArchivo);
    return retorno;
}

/**
 * \brief Guarda los datos de los empleados en archivo en la carpeta /files (modo binario).
 * \param path Ruta donde se guardara el archivo
 * \param pLinkedList Es la LinkedList con los elementos a guardar
 * \return Retorna 0 si se logra guardar sino retorna -1
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pLinkedList)
{
    FILE* pArchivo = fopen(path,"wb");
    int retorno = -1;

    if(pArchivo != NULL && !parser_SaveToBinary(pArchivo,pLinkedList))
    {
        retorno = 0;
    }
    fclose(pArchivo);
    return retorno;
}

/*
*
 * \brief Menu con opciones para trabajar con la LinkedList
 * \param void
 * \return Retorna 0 siempre

int controller_init()
{
    int option;
    int counter = 0;//variable de seguridad del len del linkedlist
    LinkedList* listaPrincipal[LEN_LL];//Array estatico que agrupa 6 linkedlist
    char nombreArchivo[BUFFER];//auxiliar para escribir nombre de archivo
    char path[BUFFER];//ruta para guardar el archivo. ../files/ Es la carpeta de archivos predeterminada

    ll_initLinkedList(listaPrincipal);

    /   lista[1] - listado s
    /   lista[2] - listado informes

    do
    {
        printf("%s\n>>>MENU PRINCIPAL<<<\n",fecha());
        printf("\n1) Abrir archivo\n2) Listar\n3) Generar informes\n4) Guardar\n5) Salir");
        input_getEnteros(&option,"\nIngrese opcion: ","\nDato invalido",2);

        switch(option)
        {
            case 1: //ABRIR ARCHIVO

                if(option == 1 && !controller_loadFromText("data.csv",listaPrincipal[1]))//Cargo el archivo
                {
                    printf("\nArchivo |%s| cargado.",nombreArchivo);
                    counter = ll_len(listaPrincipal[1]);
                }

                printf("\nTotal empleados: %d",ll_len(listaPrincipal[1]));

                break;
            case 2: //LISTAR
                if(counter > 0)
                {
                    limpiarPantalla();
                    printf("<LISTAR>");//Selecciono lista para mostrar
                    printf("\n1) Ventas\n2) Informes");
                    printf("\n3) Volver");
                    input_getEnteros(&option,"\nIngrese opcion: ","\nError",2);

                    if(option == 3)
                    {
                        break;
                    }
                    else if(option >= 1 && option <= 2 )
                    {
                        controller_ListVenta(listaPrincipal[1]);
                        controller_generateNewList(listaPrincipal);
                    }
                }
                else
                {
                    printf("\nNo hay datos cargados");
                }
                break;
             case 3 : //GENERAR LISTAS
                if(counter > 0)
                {
                    if(!controller_generateNewList(listaPrincipal))
                    {
                        printf("\nLista generada.");
                    }
                }
                else
                {
                    printf("\nNo hay datos cargados");
                }
                break;
            case 4: //GUARDAR ARCHIVO
                strcpy(path,"../files/");//Seteo el path predeterminado
                if(!input_getEnteros(&option,"\n1) Guardar modo texto\n2) Guardar en modo binario\n3) Volver\n>> ","\nError",2))
                {
                    if(option == 3){
                        break;
                    }

                    if(!input_getPath(nombreArchivo,BUFFER,"\nIngrese nombre de archivo: ","Nombre invalido",2))
                    {
                        strcat(path,nombreArchivo);//Union entre nombre de archivo y path
                        if(!controller_saveAsText("informes.txt",listaPrincipal[2]))//Cargo el archivo
                        {
                            printf("\nArchivo |%s| cargado.",nombreArchivo);
                            counter = ll_len(listaPrincipal[1]);
                        }
                        else if(option == 2 && !controller_saveAsBinary(path,listaPrincipal[1]))
                        {
                            printf("\nArchivo |%s| cargado.",nombreArchivo);
                            counter = ll_len(listaPrincipal[1]);
                        }
                    }
                    else
                    {
                        printf("\nArchivo inexistente.");
                    }
                    printf("\nTotal empleados: %d",ll_len(listaPrincipal[1]));
                }
                break;
            case 5 : //SALIR
                break;
            default :
                printf("\nOpcion incorrecta");
        }
        pause();
        limpiarPantalla();
    }while(option != 5);
    return 0;
}*/
