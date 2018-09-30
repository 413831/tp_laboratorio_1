#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "pantalla.h"


static int generateID();
static int pantalla_buscarIndiceLibre(Pantalla array[],int size);
static void swap(Pantalla* valorA,Pantalla* valorB);

static void swap(Pantalla* valorA,Pantalla* valorB)
{
    Pantalla auxiliar;//TIPO pantalla
    auxiliar = *valorA;
    *valorA = *valorB;
    *valorB = auxiliar;
}


static int generateID()
{
    static int id = 0;
    id++;
    return id;
}

static int pantalla_buscarIndiceLibre(Pantalla array[],int size)
{
    int retorno = 1;
    int i;

    for(i=0;i < size; i++)
    {
        if(array[i].isEmpty == 1)
        {
            retorno = i;
            break;
        }
    }
    return retorno;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int pantalla_init(Pantalla array[],int size,int valor)
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

Pantalla* pantalla_getByID(Pantalla array[],int size,int id)
{
    Pantalla* retorno = NULL;
    int i;

    if(array != NULL && size > 0)
    {
        for(i=0;i<size;i++)
        {
           if(array[i].id == id)
            {
            retorno = array+i;
            break;
            }
        }
    }
    return retorno;
}

int pantalla_IDproducto(Pantalla array[],int size)
{
    int retorno = -1;
    int i;
    int auxID;

    input_ScanInt("\nINGRESE ID: ",&auxID);//SE PIDE ID A BUSCAR
    printf("\nID ingresado %d", auxID);

    for(i=0;i < size; i++)
    {
        if(array[i].id == auxID)//SE COMPARA ID A BUSCAR CONTRA TODO EL ARRAY
        {
            retorno = i;//SE PASA EL INDICE DEL ID BUSCADO
            break;
        }

    }
    return retorno;
}


int pantalla_alta(Pantalla array[],int size)
{
    char auxNombre[50];
    char auxDireccion[100];
    float auxPrecio;
    int auxTipo;
    int retorno = -1;
    int indice;

    indice = pantalla_buscarIndiceLibre(array,size);
    printf("\nINDICE VACIO %d",indice);

    if( !input_getAlfanumerico(auxNombre,50,"\n Ingrese el nombre de pantalla: ","\n Error,nombre invalido.")&&
        !input_getAlfanumerico(auxDireccion,100,"\n Ingrese direccion: ","\n Error,direccion invalida.")&&
        !input_getFloat(&auxPrecio,100,"\n Ingrese el precio: ","\n Error,precio invalido.",0,10000) &&
        !input_getNumeros(&auxTipo,100,"\n Ingrese el tipo: ","\n Error,dato invalido.",0,10000))
    {
        strncpy(array[indice].nombre,auxNombre,50);
        strncpy(array[indice].direccion,auxDireccion,100);
        array[indice].precio = auxPrecio;
        array[indice].tipo = auxTipo;
        array[indice].isEmpty = 0;
        array[indice].id = generateID();//SE PASA ID ASIGNADO A LA ESTRUCTURA
        retorno = 0;
    }

    return retorno;
}


int pantalla_modificar(Pantalla array[],int size)
{
    char auxNombre[50];
    char auxDireccion[100];
    float auxPrecio;
    int auxTipo;
    int retorno = -1;

    if(array->isEmpty == 0)
    {
        if( !input_getAlfanumerico(auxNombre,50,"\n Ingrese nombre de pantalla: ","\n Error,nombre invalido.")&&
            !input_getAlfanumerico(auxDireccion,100,"\n Ingrese direccion: ","\n Error,direccion invalida.")&&
            !input_getFloat(&auxPrecio,50,"\n Ingrese el precio: ","\n Error,precio invalido.",0,10000) &&
            !input_getNumeros(&auxTipo,50,"\n Ingrese el tipo: ","\n Error,dato invalido.",0,2))
        {
            strncpy(array->nombre,auxNombre,50);
            strncpy(array->direccion,auxDireccion,50);
            array->precio = auxPrecio;
            array->tipo = auxTipo;
            retorno = 0;
        }
    }
    else
    {
        printf("\nCasillero vacio");
    }
    return retorno;
}


int pantalla_eliminar(Pantalla array[],int size)
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

int pantalla_ordenarId(Pantalla array[],int size)
{
    int retorno = -1;
    int i;
    int j;
    Pantalla auxiliar;

    if(array != NULL && size > 0 && array->isEmpty == 0)
    {
        retorno = 0;

        for(i=0;i<size;i++)
        {
            j= i++;

            if(array[i].id > array[j].id)
            {
                auxiliar = array[i];
                array[i] = array[j];
                array[j] = auxiliar;
            }
        }

    }
    return retorno;
}

int pantalla_mostrar(Pantalla array[],int size)
{
    int retorno = -1;

    if(array != NULL && size > 0 )
    {
        printf("\n\nPRODUCTO -- %s",array->nombre);
        printf("\nDESCRIPCION -- %s",array->direccion);
        printf("\nPRECIO -- $%.2f",array->precio);

        if(array->tipo == 0)
        {
            printf("\nTIPO -- LCD");
        }
        else if(array->tipo == 1)
        {
            printf("\nTIPO -- LED");
        }
        printf("\nID -- %i",array->id);

        retorno = 0;
    }
    return retorno;
}


int pantalla_listar(Pantalla array[],int size)
{
    int retorno = -1;

    if(array != NULL && array->isEmpty == 0)
    {
        printf("\n\nPRODUCTO -- %s",array->nombre);
        printf("\nDESCRIPCION -- %s",array->direccion);
        printf("\nPRECIO -- $%.2f",array->precio);

        if(array->tipo == 0)
        {
            printf("\nTIPO -- LCD");
        }
        else if(array->tipo == 1)
        {
            printf("\nTIPO -- LED");
        }
        printf("\nID -- %i",array->id);

        retorno = 0;
    }
    return retorno;
}

int pantalla_ingresoForzado(Pantalla* array,int size,char* nombre,char*direccion,int tipo,float precio)
{
    int indice;
    indice = pantalla_buscarIndiceLibre(array,size);
    strncpy(array[indice].nombre,nombre,100);
    array[indice].tipo = tipo;
    strncpy(array[indice].direccion,direccion,100);
    array[indice].precio=precio;
    array[indice].id=generateID();
    array[indice].isEmpty=0;

    return 0;
}
