#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "utn.h"

/**
 * \brief Genera un número aleatorio
 * \param desde Número aleatorio mínimo
 * \param hasta Número aleatorio máximo
 * \param iniciar Indica si se trata del primer número solicitado 1 indica que si
 * \return retorna el número aleatorio generado
 */

char test_RandomInt(int desde , int hasta, int iniciar)
{
    if(iniciar)
        srand (time(NULL));
    return desde + (rand() % (hasta + 1 - desde)) ;
}

/**
 * \brief Verifica si el string recibido es de numeros enteros
 * \param array Es el array para validar su tipo
 * \return Retorna 1 si cumple el formato si no retorna 0
 */

int validacion_Int(char* array,int size)
{
    int retorno = 0;
    int i;
    int contadorNegativos = 0;

    if(array != NULL && size > 0)
    {

        for(i=0;i < size && array[i] != '\0';i++)
        {
            if((array[i] < '0') && (array[i] > '9'))
            {
                if(array[0] != '-' && contadorNegativos > 1)
                {
                    retorno = 0;
                    break;
                }
            }
            if(array[i] == '-')
            {
                contadorNegativos++;
            }
              retorno = 1;
        }

    }
    return retorno;
}

/**
 * \brief Verifica si el string recibido es de numeros tipo float
 * \param array Es el array para validar su tipo
 * \return Retorna 1 si cumple el formato si no retorna 0
 */

int validacion_Float(char* array,int size)
{
   int i=0;
   int retorno = 0;
   int contadorSimbolos = 0;
   int digitosIngresados;

   digitosIngresados = strlen(array)-1;

   if(array != NULL && size > 0)
   {

       for(i=0;i < size && array[i] != '\0';i++)
       {
            if(array[i] < '0' || array[i] > '9')
            {
                if(array[i] != '.' || array[0] == '.' || contadorSimbolos > 1 || array[digitosIngresados] == '.')
                {
                retorno = 0;
                break;
                }
            }

            if(array[i] == '.')
            {
                contadorSimbolos++;
            }
            retorno = 1;
       }

   }

   return retorno;
}


/**
 * \brief Verifica si el string recibido tiene solo letras
 * \param array Es el array para validar su tipo
 * \return Retorna 1 si cumple el formato si no retorna 0
 */

int validacion_Letras(char* array,int size)
{
    int retorno = 0;
    int i;
    int digitosIngresados;

    digitosIngresados = strlen(array);

    if(array != NULL)
    {

        for(i=0;i < digitosIngresados && array[i] != '\0';i++)
        {
            if((tolower(array[i]) < 'a' || tolower(array[i]) > 'z') && array[i]!= ' ')
            {
                retorno = 0;
                break;
            }
             retorno = 1;
        }

    }
    return retorno;
}

/**
 * \brief Verifica si el string recibido contiene solo letras y números
 * \param array Es el string para validar el tipo
 * \return Retorna 1 si cumple el formato si no retorna 0
 */

int validacion_AlfaNumerico(char array[],int size)
{
   int i=0;
   int retorno = 0;

   if(array != NULL && size > 0)
   {

       for(i=0;i<size && array[i] != '\0';i++)
       {
           if((tolower(array[i]) < 'a' ||
               tolower(array[i]) > 'z') &&
              (array[i] < '0' ||
               array[i] > '9') &&
              array[i] != ' ' &&
              array[i] != '.')
            {
                    printf("\nENTRO AL IF");
                    retorno = 0;
                    break;
            }
            retorno = 1;
       }
   }
   return retorno;
}

/**
 * \brief Verifica si el string recibido es un numero de telefono valido
 * \param array Es el string recibido para ser validado
 * \return Retorna 1 si cumple el formato si no retorna 0
 */

int validacion_Telefono(char* array,int size)
{
   int i=0;
   int retorno = 0;
   int contadorSimbolos = 0;
   int digitosIngresados;

   digitosIngresados = strlen(array)-1;

   if(array != NULL && size > 0)
   {

       for(i=0;i < size && array[i] != '\0';i++)
       {
            if(array[i] < '0' || array[i] > '9')
            {
                if(array[i] != '-' ||
                   array[4] != '-' ||
                   array[2] != '-' ||
                   contadorSimbolos > 2 ||
                   array[digitosIngresados] == '-')
                {
                retorno = 0;
                break;
                }
            }

            if(array[i] == '-')
            {
                contadorSimbolos++;
            }
            retorno = 1;
       }

   }

   return retorno;
}

/**
 * \brief Verifica si el string recibido es un numero de dni valido
 * \param array Es el string recibido para ser validado
 * \return Retorna 1 si cumple el formato si no retorna 0
 */

int validacion_DNI(char* array,int size)
{
   int i=0;
   int retorno = 0;
   int contadorSimbolos = 0;
   int digitosIngresados;

   digitosIngresados = strlen(array);

   if(array != NULL && size > 0)
   {

       for(i=0;i < size && array[i] != '\0';i++)
       {
            if(array[i] < '0' || array[i] > '9'|| array[i] != '.')
            {
                if(array[2] != '.' || array[6] != '.' || contadorSimbolos > 2 || digitosIngresados < 10)
                {
                retorno = 0;
                break;
                }
            }

            if(array[i] == '.')
            {
                contadorSimbolos++;
            }
            retorno = 1;

       }

   }
   return retorno;
}

/**
 * \brief Verifica si el string recibido es un numero de cuit valido
 * \param array Es el string recibido para ser validado
 * \return Retorna 1 si cumple el formato si no retorna 0
 */

int validacion_Cuit(char* array,int size)
{
   int i=0;
   int retorno = 0;
   int contadorSimbolos = 0;
   int digitosIngresados;

   digitosIngresados = strlen(array);

   if(array != NULL && size > 0)
   {

       for(i=0;i < size && array[i] != '\0';i++)
       {
            if(array[i] < '0' || array[i] > '9')
            {

                if(array[i] != '-' || contadorSimbolos > 2 || digitosIngresados != 13)
                {
                    retorno = 0;
                    break;
                }

                retorno = 0;

            }


            if(array[i] == '-')
            {
                contadorSimbolos++;
            }
            retorno = 1;
       }

       if(array[2] != '-' || array[11] != '-' || digitosIngresados != 13)
       {
           retorno = 0;
       }

   }
   return retorno;
}
