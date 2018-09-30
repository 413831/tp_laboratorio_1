#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"

static void array_swap(int* elementoA,int* elementoB);
static int array_minimoDesde(  int* pArray, int limite,
                        int desde, int* pMinimo);

static void array_swap(int* elementoA,int* elementoB)
{
    int auxiliar;
    auxiliar = *elementoA;
    *elementoA = *elementoB;
    *elementoB = auxiliar;
}


void sort_Bubble(int* pArray,int size)
{
    int i;
    int j;

    for(i=0;i<size;i++)//Ordenamiento por metodo burbuja
    {
        for(j=i+1;j<size;j++)
        {
            if(pArray[i] > pArray[j])
            {
                array_swap(&pArray[i],&pArray[j]);
            }
        }
    }
}

int sort_Selection(int* pArray, int limite, int orden)
{
    int retorno=-1;
    int j;
    int i;
    int indiceMinimo;
    int auxiliarValorMinimo;

    if(pArray != NULL && limite > 0)
    {
        for(j=0;j<limite;j++)
        {

           for(i=j;i<limite;i++)
            {
                if(i == j || pArray[i] < auxiliarValorMinimo)
                {
                    auxiliarValorMinimo  = pArray[i];
                    indiceMinimo = i;
                }
            }
           array_minimoDesde(pArray,limite,j,&indiceMinimo);
           array_swap(&pArray[j],&pArray[indiceMinimo]);
           //array_swap(pArray+j,pArray+indiceMinimo);
        }
        retorno = 0;
    }
    return retorno;
}


int sort_Insertion(int* pArray, int limite, int orden)
{
    int retorno=-1;
    int j;
    int i;

    if(pArray != NULL && limite > 0)
    {

        for(j=0;j<limite;j++)
        {
            i = j+1;

                if(pArray[i] < pArray[j])
                {
                   array_swap(&pArray[j],&pArray[i]);
                }
        }
        retorno = 0;
    }
    return retorno;
}


static int array_minimoDesde(  int* pArray, int limite,
                        int desde, int* pMinimo)
{
    int retorno=-1;
    int i;
    int auxiliarValorMinimo;
    int auxiliarIndiceMinimo;

    if(pArray != NULL && limite > 0 && limite >= desde && pMinimo != NULL)
    {
        for(i=desde;i<limite;i++)
        {
            if(i == desde || pArray[i] < auxiliarValorMinimo)
            {
                auxiliarValorMinimo  = pArray[i];
                auxiliarIndiceMinimo = i;
            }
        }
        *pMinimo = auxiliarIndiceMinimo;
        retorno = 0;
    }
    return retorno;
}
