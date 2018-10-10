#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utn.h"
#include "clientes.h"


//Funciones privadas



/**
*\brief Realiza el swap entre dos clientes
*\param valorA es el puntero del primer cliente
*\param valorB es el puntero del segundo cliente
*\return Retorna void
*/


static void swap(Cliente* valorA,Cliente* valorB)
{
    Cliente auxiliar;//TIPO pantalla
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


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
*\brief Busca el indice libre en un array
*\param array Es el array que reciba para recorrer
*\param size Es el tamaño del array
*\return Retorna el indice del lugar libre si no retorna -1
*/

int cliente_buscarIndiceLibre(Cliente array[],int size)
{
    int retorno = -1;
    int i;

    for(i=0;i < size; i++)
    {
        if(array[i].isEmpty)
        {
            retorno = i;
            break;
        }
    }
    return retorno;
}

/**
*\brief Inicializa todos los clientes de un array con un valor de vacio
*\param array Es el array que reciba para recorrer
*\param size Es el tamaño del array
*\param valor Es el valor con el cual cargara el campo de estado
*\return Retorna 0 si no retorna -1
*/

int cliente_init(Cliente array[],int size,int valor)
{
    int i;
    int retorno = -1;
    if(array != NULL && size > 0 && valor >= 0)
    {
        retorno = 0;
        for(i=0;i < size; i++)
        {
        array[i].isEmpty = valor;
        }

    }
    return retorno;
}

/**
*\brief Busca un cliente por ID dentro de un array de estructuras
*\param array Es el array que reciba para recorrer
*\param size Es el tamaño del array
*\param id Es el ID que recibe para buscar
*\return Retorna el puntero del cliente si no retorna NULL
*/

Cliente* cliente_getByID(Cliente* array,int size,int id)
{
    Cliente* retorno = NULL;
    int i;

    if(array != NULL && size > 0)
    {
        for(i=0;i<size;i++)
        {
           if(!array[i].isEmpty && array[i].id == id)
            {
                retorno = array+i;
                break;
            }
        }
    }
    return retorno;
}

/**
*\brief Realiza el alta de un cliente del array
*\param array Es el array que reciba para recorrer
*\param size Es el tamaño del array
*\param cliente Es el puntero de un cliente
*\return Retorna 0 si no retorna -1
*/

int cliente_alta(Cliente* array,int size,int* index)
{
    char auxNombre[50];
    char auxApellido[50];
    char auxCuit[15];
    //-----------
    int retorno = -1;
    int indice;

    indice = cliente_buscarIndiceLibre(array,size);

    if( !input_getLetras(auxNombre,50,"\nIngrese nombre: ","\nError,dato invalido.",2)&&
        !input_getLetras(auxApellido,50,"\nIngrese apellido: ","\nError,dato invalido.",2)&&
        !input_getCuit(auxCuit,15,"\nIngrese el CUIT: ","\nError,dato invalido.",2))
    {
        strncpy(array[indice].nombre,auxNombre,50);
        strncpy(array[indice].apellido,auxApellido,50);
        strncpy(array[indice].cuit,auxCuit,15);
        array[indice].isEmpty = 0;
        array[indice].id = generateID();//SE PASA ID ASIGNADO A LA ESTRUCTURA
        *index = indice;
        retorno = 0;
    }

    return retorno;
}

/**
*\brief Modifica los campos de un cliente del array
*\param array Es el puntero que recibe del cliente del array
*\param size Es el tamaño del array
*\return Retorna 0 si no retorna -1
*/

int cliente_modificar(Cliente* array)
{
    char auxNombre[50];
    char auxApellido[50];
    char auxCuit[15];

    int retorno = -1;

    if(array != NULL && array->isEmpty == 0)
    {

       if( !input_getLetras(auxNombre,50,"\nIngrese nombre: ","\nError,dato invalido.",2)&&
            !input_getLetras(auxApellido,50,"\nIngrese apellido: ","\nError,dato invalido.",2)&&
            !input_getCuit(auxCuit,14,"\nIngrese el CUIT: ","\nError,dato invalido.",2))
        {
            strncpy(array->nombre,auxNombre,50);
            strncpy(array->apellido,auxApellido,50);
            strncpy(array->cuit,auxCuit,14);
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
*\brief Elimina un cliente del array
*\param array Es el puntero que recibe del cliente del array
*\return Retorna 0 si no retorna -1
*/

int cliente_eliminar(Cliente* array)
{
    int retorno = -1;

    if(array != NULL)
    {
            array->isEmpty = 1;
            retorno = 0;
    }
    else
    {
        printf("\nCasillero vacio");
    }
    return retorno;
}

/**
*\brief Ordena todos los clientes de un array
*\param array Es el array que recibe para ordenar
*\param size Es el tamaño del array
*\return Retorna 0 si no retorna -1
*/

int cliente_ordenar(Cliente array[],int size)
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

                 if(array[i].apellido < array[i+1].apellido)//Ordena por apellido
                {
                     swap(array+i,array+j);
                     flag = 1;
                }
                else if(array[i].apellido == array[i+1].apellido &&
                strcmp(array[i].nombre,array[i+1].nombre) > 0)//Ordena por nombre
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
*\brief Muestra los datos de un cliente del array
*\param array Es el puntero que recibe del cliente del array
*\param idCliente es el ID del cliente
*\return Retorna 0 si no retorna -1
*/

int cliente_mostrar(Cliente* array)
{
    int retorno = -1;

    if(array != NULL)
    {
        printf("\n\nCLIENTE -- %s %s ",array->nombre,array->apellido);
        printf("\nCUIT -- %s",array->cuit);

        retorno = 0;
    }
    return retorno;
}

/**
*\brief Lista los datos de todos los clientes del array
*\param array Es el array que recibe para recorrer
*\param size Es el tamaño del array
*\return Retorna 0 si no retorna -1
*/

int cliente_listar(Cliente array[],int size)
{
    int retorno = -1;
    int i;

    if(array != NULL && size > 0)
    {
        for(i=0;i<size;i++)
        {
            if(!array[i].isEmpty)
            {
                    printf("\n\nNOMBRE -- %s ",array[i].nombre);
                    printf("\nAPELLIDO -- %s",array[i].apellido);
                    printf("\nCUIT -- %s",array[i].cuit);
                    printf("\nID -- %d",array[i].id);

                retorno = 0;
            }
        }
    }
    return retorno;
}

/**
*\brief Carga todos los campos de un cliente de un array
*\param array Es el array que recibe para cargar
*\param size Es el tamaño del array
*\param auxNombre Es el valor del campo nombre
*\param auxApellido Es el valor del campo apellido
*\param auxCuit Es el valor del campo cuit
*\return Retorna 0 si no retorna -1
*/



int cliente_ingresoForzado(Cliente array[],int size,char auxNombre[],char auxApellido[],char auxCuit[])
{
    int retorno = -1;
    int indice;

    if(array != NULL && size > 0)
    {
        retorno = 0;
        indice = cliente_buscarIndiceLibre(array,size);
        strncpy(array[indice].nombre,auxNombre,50);
        strncpy(array[indice].apellido,auxApellido,50);
        strncpy(array[indice].cuit,auxCuit,15);
        array[indice].isEmpty = 0;
        array[indice].id = generateID();
    }

    return retorno;
}


