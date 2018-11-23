#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Venta.h"
#include "utn.h"
#include "parser.h"


/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param pFile Es el puntero a archivo para leer los datos
 * \param pLinkedListVenta Es la LinkedList donde se guardaran los datos
 * \return Retorna 0 si existe el archivo sino retorna -1
 *
 */
int parser_VentaFromText(FILE* pFile , LinkedList* pLinkedListVenta)
{
    int retorno = -1;
    char* bufferId;
    char* bufferFecha;
    char* bufferCodigo;
    char* bufferCantidad;
    char* bufferPrecio;
    char* bufferCuit;
    char bufferText[BUFFER];
    Venta* pVenta;

    if(pFile != NULL)
    {
        while(!feof(pFile))
        {
            fgets(bufferText,sizeof(bufferText),pFile);
            if(bufferText != NULL || strlen(bufferText) > 8)
            {
                bufferId = strtok(bufferText,",");
                printf("\nID %s",bufferId);

                bufferFecha = strtok(NULL,",");
                bufferCodigo = strtok(NULL,",");
                bufferCantidad = strtok(NULL,",");
                bufferPrecio = strtok(NULL,",");
                bufferCuit = strtok(NULL,"\n");

                pVenta = venta_constructor(atoi(bufferId),bufferFecha,bufferCodigo,atoi(bufferCantidad),atof(bufferPrecio),bufferCuit);
                if(pVenta != NULL)
                {
                    ll_add(pLinkedListVenta,pVenta);//Se agrega ELEMENTO a LINKED LIST
                    retorno = 0;
                }

            }
        }
    }
    return retorno;
}

/*
* \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param pFile Es el puntero a archivo para leer los datos
 * \param pLinkedListVenta Es la LinkedList donde se guardaran los datos
 * \return Retorna 0 si existe el archivo sino retorna -1
 *

int parser_VentaFromBinary(FILE* pFile , LinkedList* pLinkedListVenta)
{
    int retorno = -1;
    int cantidadLeida;
    Venta* pVenta;
    Venta* aux = venta_new();

    if(pFile != NULL)
    {
        while(!feof(pFile))
        {
            pVenta = venta_new();
            cantidadLeida = fread(pVenta,sizeof(Venta),1,pFile);
            if(pVenta != NULL && cantidadLeida == 1)
            {
                venta_setId(aux,"0");
                ll_add(pLinkedListVenta,pVenta);
                retorno = 0;
            }
        }
    }
    return retorno;
}*/

/** \brief Parsea los datos del linked list al archivo data.csv (modo texto).
 *
 * \param pFile Es el puntero a archivo para escribir los datos
 * \param pLinkedListVenta Es la LinkedList de donde se toman los datos
 * \return Retorna 0 si existe el archivo y el LinkedList sino retorna -1
 *
 */
int parser_SaveToText(FILE* pFile , LinkedList* pLinkedListVenta)
{
    int retorno = -1;
    Venta* auxVenta;
    int len;
    int index;
    int bufferId;
    char* bufferFecha;
    char* bufferCodigo;
    int bufferCantidad;
    float bufferPrecio;
    char* bufferCuit;

    if(pFile != NULL && pLinkedListVenta != NULL)
    {
        len = ll_len(pLinkedListVenta);

        for(index=0;index<len;index++)//Recorro todo el array hasta el LEN
        {
            auxVenta = ll_get(pLinkedListVenta,index);//Obtengo el elemento del array en posicion index

            bufferId = venta_getId(auxVenta);
            bufferFecha = venta_getFecha(auxVenta);
            bufferCodigo = venta_getCodigo(auxVenta);
            bufferCantidad = venta_getCantidad(auxVenta);
            bufferPrecio = venta_getPrecio(auxVenta);
            bufferCuit = venta_getCuit(auxVenta);

            fprintf(pFile,"%d,%s,%s,%d,%f,%s\n",bufferId,bufferFecha,bufferCodigo,bufferCantidad,bufferPrecio,bufferCuit);
            retorno = 0;
        }
    }
    return retorno;
}



/** \brief Parsea los datos del linked list al archivo data.csv (modo texto).
 *
 * \param pFile Es el puntero a archivo para escribir los datos
 * \param pLinkedListVenta Es la LinkedList de donde se toman los datos
 * \return Retorna 0 si existe el archivo y el LinkedList sino retorna -1
 *
 */
/*int parser_InformesText(FILE* pFile , LinkedList* pLinkedListVenta)
{
    int retorno = -1;
    Venta* auxVenta;
    int len;
    int index;
    int bufferId;


    if(pFile != NULL && pLinkedListVenta != NULL)
    {
        len = ll_len(pLinkedListVenta);

        for(index=0;index<len;index++)//Recorro todo el array hasta el LEN
        {
            auxVenta = ll_get(pLinkedListVenta,index);//Obtengo el elemento del array en posicion index


            sprintf(informes,...);
            fprintf(pFile,"%d,%s,%s,%d,%f,%s\n",bufferId,bufferFecha,bufferCodigo,bufferCantidad,bufferPrecio,bufferCuit);
            retorno = 0;
        }
    }
    return retorno;
}*/
/** \brief Parsea los datos del linked list al archivo data.bin (modo binario).
 *
 * \param pFile Es el puntero a archivo para escribir los datos
 * \param pLinkedListVenta Es la LinkedList de donde se toman los datos
 * \return Retorna 0 si existe el archivo y el LinkedList sino retorna -1
 *
 */
int parser_SaveToBinary(FILE* pFile , LinkedList* pLinkedListVenta)
{
    int retorno = -1;
    int i = 0;
    int len;
    Venta* auxVenta;

    if(pFile != NULL && pLinkedListVenta != NULL)
    {
        len = ll_len(pLinkedListVenta);
        while(i != len)
        {
            auxVenta = ll_get(pLinkedListVenta,i);
            if(auxVenta != NULL)
            {
                fwrite(auxVenta,sizeof(Venta),1,pFile);
            }
            retorno = 0;
            i++;
        }
    }
    return retorno;
}
