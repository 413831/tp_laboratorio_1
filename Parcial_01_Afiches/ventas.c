#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utn.h"
#include "ventas.h"

#define LENGHT_STAT 20

//Funciones privadas



/**
*\brief Realiza el swap entre dos ventas
*\param valorA es el puntero del primer venta
*\param valorB es el puntero del segundo venta
*\return Retorna void
*/


static void swap(Venta* valorA,Venta* valorB)
{
    Venta auxiliar;//TIPO pantalla
    auxiliar = *valorA;
    *valorA = *valorB;
    *valorB = auxiliar;
}

/**
*\brief Genera automáticamente un ID único
*\param void
*\return Retorna el número de ID
*/

static int generateID()
{
    static int id = 0;
    id++;
    return id;
}



//__________________

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
*\brief Busca el indice libre en un array
*\param array Es el array que reciba para recorrer
*\param size Es el tamaño del array
*\return Retorna el indice del lugar libre si no retorna -1
*/

int venta_buscarIndiceLibre(Venta array[],int size)
{
    int retorno = -1;
    int i;

    for(i=0;i < size; i++)
    {
        if(!strcmp(array[i].status,STATUS_0))
        {
            retorno = i;
            break;
        }
    }
    return retorno;
}

/**
*\brief Inicializa todos las ventas de un array con un status definido
*\param array Es el array que reciba para recorrer
*\param size Es el tamaño del array
*\param status Es el status con el que se inicializa el array
*\return Retorna 0 si no retorna -1
*/

int venta_init(Venta array[],int size,char status[])
{
    int i;
    int retorno = -1;
    if(array != NULL && size > 0 && status != NULL)
    {
        retorno = 0;
        for(i=0;i < size; i++)
        {
            strncpy(array[i].status,status,LENGHT_STAT);
        }

    }
    return retorno;
}

/**
*\brief Busca una venta por ID dentro de un array de estructuras
*\param array Es el array que reciba para recorrer
*\param size Es el tamaño del array
*\param id Es el ID que recibe para buscar
*\return Retorna el puntero de venta si no retorna NULL
*/

Venta* venta_getByID(Venta* array,int size,int id)
{
    Venta* retorno = NULL;
    int i;

    if(array != NULL && size > 0)
    {
        for(i=0;i<size;i++)
        {
           if(!strcmp(array[i].status,STATUS_1) && array[i].id == id)
            {
                retorno = array+i;
                break;
            }
        }
    }
    return retorno;
}

/**
*\brief Realiza el alta de un venta del array
*\param array Es el array que reciba para recorrer
*\param size Es el tamaño del array
*\param idIngresado Es el ID de cliente para cargar
*\return Retorna 0 si no retorna -1
*/

int venta_alta(Venta* array,int size,int idIngresado)
{
    char auxNombreAfiche[50];
    char auxZona[50];
    int auxCantidad;
    //-----------
    int retorno = -1;
    int indice;

    indice = venta_buscarIndiceLibre(array,size);

    if( !input_getAlfanumerico(auxNombreAfiche,50,"\nIngrese nombre de archivo: ","\nError,dato invalido.",2)&&
        !input_getLetras(auxZona,50,"\nIngrese ZONA (CABA - GBA SUR - GBA OESTE): ","\nError,dato invalido.",2)&&
        !venta_validarZona(auxZona) &&
        !input_getNumeros(&auxCantidad,7,"\nIngrese el cantidad: ","\nError,dato invalido.",0,10000,2))
    {
        strncpy(array[indice].nombreAfiche,auxNombreAfiche,50);
        strncpy(array[indice].zona,auxZona,50);
        array[indice].cantidad = auxCantidad;
        strncpy(array[indice].status,STATUS_1,LENGHT_STAT);
        array[indice].idCliente = idIngresado;
        array[indice].id = generateID();//SE PASA ID ASIGNADO A LA ESTRUCTURA

        retorno = 0;
    }
    return retorno;
}

/**
*\brief Modifica los campos de un venta del array
*\param array Es el puntero que recibe del venta del array
*\return Retorna 0 si no retorna -1
*/

int venta_modificar(Venta* array)
{
    char auxZona[50];
    int auxCantidad;

    int retorno = -1;

    if(array != NULL && !strcmp(array->status,STATUS_1))
    {
        if( !input_getLetras(auxZona,50,"\nIngrese ZONA (CABA - GBA SUR - GBA OESTE): ","\nError,dato invalido.",2)&&
            !venta_validarZona(auxZona) &&
            !input_getNumeros(&auxCantidad,7,"\nIngrese el cantidad: ","\nError,dato invalido.",0,10000,2))
        {
            strncpy(array->zona,auxZona,50);
            array->cantidad = auxCantidad;
            retorno = 0;
        }
    }
    else
    {
        printf("\nCasillero vacio");
    }
    return retorno;
}

/**
*\brief Cambia el status de una venta del array a cobrado
*\param array Es el puntero que recibe del venta del array
*\return Retorna 0 si no retorna -1
*/

int venta_baja(Venta* array)
{
    int retorno = -1;

    if(array != NULL)
    {
            strncpy(array->status,STATUS_2,LENGHT_STAT);
            retorno = 0;
    }
    else
    {
        printf("\nCasillero vacio");
    }
    return retorno;
}

/**
*\brief Elimina una venta del array a cobrado
*\param array Es el puntero que recibe del venta del array
*\return Retorna 0 si no retorna -1
*/

int venta_eliminar(Venta* array)
{
    int retorno = -1;

    if(array != NULL)
    {
            strncpy(array->status,STATUS_0,LENGHT_STAT);
            retorno = 0;
    }
    else
    {
        printf("\nCasillero vacio");
    }
    return retorno;
}


/**
*\brief Ordena todos los ventas de un array
*\param array Es el array que recibe para ordenar
*\param size Es el tamaño del array
*\return Retorna 0 si no retorna -1
*/

int venta_ordenar(Venta array[],int size)
{
    int retorno = -1;
    int i;
    int j;
    int flag = 1;

    if(array != NULL && size > 0)
    {
        while(flag)
        {
            flag = 0;

            for(i=0;i<size-1;i++)
            {
                j=i+1;

                 if(strcmp(array[i].zona,array[j].zona) > 0)//Ordena por zona
                {
                     swap(array+i,array+j);
                     flag = 1;
                }
                else if(!strcmp(array[i].zona,array[j].zona) &&
                array[i].cantidad > array[j].cantidad)//Ordena por cantidad
                {
                    swap(array+i,array+j);
                    flag = 1;
                }
            }
        }
        retorno = 0;
    }
    return retorno;
}



/**
*\brief Lista los datos de todos los ventas del array
*\param array Es el array que recibe para recorrer
*\param size Es el tamaño del array
*\return Retorna 0 si no retorna -1
*/

int venta_listar(Venta array[],int size)
{
    int retorno = -1;
    int i;

    if(array != NULL && size > 0)
    {
        for(i=0;i<size;i++)
        {
            if(!strcmp(array[i].status,STATUS_1))
            {
                printf("\n\nNOMBRE -- %s ",array[i].nombreAfiche);
                printf("\nZONA-- %s",array[i].zona);
                printf("\nCANTIDAD-- %d",array[i].cantidad);
                printf("\nID -- %d",array[i].id);

                retorno = 0;
            }
        }
    }
    return retorno;
}

/**
*\brief Muestra los datos de una venta a cobrar del array
*\param array Es el array que recibe para recorrer
*\param idIngresado Es el ID de cliente para buscar en el array
*\return Retorna 0 si no retorna -1
*/

int venta_mostrar(Venta array[],int size,int idIngresado)
{
    int retorno = -1;
    int i;
    int contadorVentas = 0;

    if(array != NULL && size > 0)
    {
        for(i=0;i<size;i++)
        {

            if(!strcmp(array[i].status,STATUS_1) && array[i].idCliente == idIngresado)
            {
                printf("\n\nNOMBRE ARCHIVO -- %s ",array[i].nombreAfiche);
                printf("\nZONA PUBLICACION-- %s",array[i].zona);
                printf("\nCANTIDAD DE DIAS DE PUBLICACION-- %d",array[i].cantidad);
                contadorVentas++;
                retorno = 0;
            }
        }
        printf("\n\nCANTIDAD DE VENTAS A COBRAR: %d",contadorVentas);
    }
    return retorno;
}

/**
*\brief Muestra los datos de una venta cobrada del array
*\param array Es el array que recibe para recorrer
*\param idIngresado Es el ID de cliente para buscar en el array
*\return Retorna 0 si no retorna -1
*/

int venta_cobradas(Venta array[],int size,int idIngresado)
{
    int retorno = -1;
    int i;
    int contadorVentas = 0;

    if(array != NULL && size > 0)
    {
        for(i=0;i<size;i++)
        {
            if(!strcmp(array[i].status,STATUS_2) && array[i].idCliente == idIngresado)
            {
                printf("\n\nNOMBRE ARCHIVO -- %s ",array[i].nombreAfiche);
                printf("\nZONA PUBLICACION-- %s",array[i].zona);
                printf("\nCANTIDAD DE DIAS DE PUBLICACION-- %d",array[i].cantidad);
                contadorVentas++;

                retorno = 0;
            }
        }
        printf("\n\nCANTIDAD DE VENTAS COBRADAS: %d",contadorVentas);
    }
    return retorno;
}


/**
*\brief Carga todos los campos de una venta de un array
*\param array Es el array que recibe para cargar
*\param size Es el tamaño del array
*\param uaxNombreArchivo Es el valor del campo nombreAfiche
*\param auxZona Es el valor del campo zona
*\param auxCantidad Es el valor del campo cantidad
*\param idCliente Es el valor del campo idCliente
*\return Retorna 0 si no retorna -1
*/



int venta_ingresoForzado(Venta array[],
                        int size,
                        char auxNombreArchivo[],
                        char auxZona[],
                        int auxCantidad,
                        int idCliente)
{
    int retorno = -1;
    int indice;

    if(array != NULL && size > 0)
    {
        retorno = 0;

        indice = venta_buscarIndiceLibre(array,size);

        strncpy(array[indice].nombreAfiche,auxNombreArchivo,50);
        strncpy(array[indice].zona,auxZona,50);
        array[indice].cantidad = auxCantidad;
        array[indice].idCliente = idCliente;
        strncpy(array[indice].status,STATUS_1,LENGHT_STAT);

        array[indice].id = generateID();//SE PASA ID ASIGNADO A LA ESTRUCTURA
    }
    return retorno;
}


int venta_validarZona(char zona[])
{
    int retorno = -1;

    if(!strcasecmp(zona,"CABA") ||
       !strcasecmp(zona,"GBA SUR") ||
       !strcasecmp(zona,"GBA OESTE"))
    {
        retorno = 0;
    }
    else
    {
        printf("\nError.Dato invalido)");
    }
    return retorno;
}
