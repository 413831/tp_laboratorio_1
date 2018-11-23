#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/elemento.h"
#include "../inc/LinkedList.h"
#include "../inc/utn.h"

#define BUFFER 4000

/////////////////////////////////////////////////STATIC/////////////////////////////////////////////////////////////////////

/**
*\brief Valida un campoUno del elemento
*\param name Es el string a validar
*\return Retorna 1 si es correcto sino retorna 0
*/
static int isValidCampoUno(char* campoUno)
{
    int retorno = 0;

    if(campoUno != NULL && validacionUno)
    {
        retorno = 1;
    }
    return retorno;
}

/**
*\brief Valida un campoDos del elemento
*\param name Es el string a validar
*\return Retorna 1 si es correcto sino retorna 0
*/
static int isValidCampoDos(char* campoDos)
{
    int retorno = 0;

    if(campoDos != NULL && validacionDos)
    {
        retorno = 1;
    }
    return retorno;
}

/**
*\brief Valida un campoTres del elemento
*\param name Es el string a validar
*\return Retorna 1 si es correcto sino retorna 0
*/
static int isValidCampoTres(char* campoTres)
{
    int retorno = 0;

    if(campoTres != NULL && validacionTres)
    {
        retorno = 1;
    }
    return retorno;
}

/**
*\brief Valida un campoCuatro del elemento
*\param name Es el string a validar
*\return Retorna 1 si es correcto sino retorna 0
*/
static int isValidCampoCuatro(char* campoCuatro)
{
    int retorno = 0;

    if(campoCuatro != NULL && validacionCuatro)
    {
        retorno = 1;
    }
    return retorno;
}

/**
*\brief Valida un campoCinco del elemento
*\param name Es el string a validar
*\return Retorna 1 si es correcto sino retorna 0
*/
static int isValidCampoCinco(char* campoCinco)
{
    int retorno = 0;

    if(campoCinco != NULL && validacionCinco)
    {
        retorno = 1;
    }
    return retorno;
}

///////////////////////////////////////////////////////////////

/**
*\brief Se realiza el alta de un elemento desde consola
*\param pLinkedList Es el array para ingresar elemento
*\return Retorna 0 si logra agregar elemento sino retorna -1
*/
int elemento_add(void* pLinkedList)
{
    int retorno = -1;
    char campoUno[BUFFER];
    char campoDos[BUFFER];
    char campoTres[BUFFER];
    char campoCuatro[BUFFER];
    char campoCinco[BUFFER];
    Elemento* this = NULL;

    if( !input("campoUno",bufferCampoUno,BUFFER,punteroValidacionUno) &&
        !input("campoDos",bufferCampoDos,BUFFER,punteroValidacionDos) &&
        !input("campoTres",bufferCampoTres,BUFFER,punteroValidacionTres) &&
        !input("campoCuatro",bufferCampoCuatro,BUFFER,punteroValidacionCuatro) &&
        !input("campoCinco",bufferCampoCinco,BUFFER,punteroValidacionCinco))
    {
        this = elemento_constructor(bufferCampoUno,bufferCampoDos,bufferCampoTres,bufferCampoCuatro,bufferCampoCinco);
        if(this != NULL)
        {
            elemento_show(this);
            ll_add(pLinkedList,this);
            retorno = 0;;
        }
    }
    return retorno;
}


/**
*\brief Se da de baja un elemento seteando el ID en valor especifico
*\param pArray Es el array para recorrer
*\return Retorna 0 si existe el ID sino retorna -1
*/
int elemento_remove(void* pLinkedList,void* pListInactives)
{
    int retorno = -1;
    int index;
    char bufferId[BUFFER];
    char option[2];
    Elemento* this = NULL;

    if(!input("ID",bufferId,BUFFER,validacionId))
    {
        this = elemento_getById(pLinkedList,atoi(bufferId));//Busco el elemento del Id ingresado
        if(this != NULL)
        {
            elemento_show(this);//Muestro datos del elemento
            input_getLetras(option,2,"\nATENCION!\nDesea dar de baja a empleado? S/N\n","\nError.Dato invalido",2);
            if(!strcasecmp("s",option))
            {
                index = ll_indexOf(pLinkedList,this);
                this = ll_pop(pLinkedList,index);//Se saca el elemento del LinkedList

                ll_add(pListInactives,this);//Se agrega el elemento a la otra LinkedList
                retorno = 0;
            }
        }
        else
        {
            printf("\nEl ID ingresado no existe");
        }
    }
    return retorno;
}

/**
*\brief Se modifica un campo del elemento
*\param this Es el elemento a modificar
*\param validacion Es el puntero a la funcion de validacion
*\param set Es el puntero a la funcion set del campo
*\return Retorna 0 si logra modificar campo sino retorna -1
*/
int elemento_modify(Elemento* this,
                        char* mensaje,
                        int (*validacion)(char*,int),
                        int (*set)(Elemento*,char*))
 {
    int retorno = -1;
    char buffer[BUFFER];

    if(this != NULL && mensaje != NULL && validacion != NULL && set != NULL)
    {
        input(mensaje,buffer,BUFFER,validacion);
        if(buffer != NULL)
        {
            (*set)(this,buffer);
            elemento_show(this);
            retorno = 0;
        }
    }
    else
    {
        printf("\nError");
    }
    return retorno;
}
/**
*\brief Se muestran los datos de todos los campos del elemento
*\param this Es el puntero al elemento
*\return Retorna 0 si el elemento es diferente a NULL sino retorna -1
*/
int elemento_show(void* this)
{
    int retorno = -1;

    if(this != NULL)
    {
        printf("\nCampoUno -- %s",elemento_getCampoUno(this);
        printf(" / CampoDos -- %s",elemento_getCampoDos(this);
        printf(" / CampoTres -- %s",elemento_getCampoTres(this);
        printf(" / CampoCuatro -- %s",elemento_getCampoCuatro(this);
        printf(" / CampoCinco -- %s",elemento_getCampoCinco(this);
        retorno = 0;
    }
    return retorno;
}
