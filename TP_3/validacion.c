#include <stdio.h>
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
 * \brief Verifica si el string recibido es numérico
 * \param array Es el array para validar su tipo
 * \param minimo Es el minimo valor permitido para ingresar
 * \param maximo Es el maximo valor permitido para ingresar
 * \return 1 si es númerico y 0 si no lo es
 */

int validacion_Int(char* array,int size)
{
    int retorno = 0;
    int i;

    if(array != NULL && size > 0)
    {
        retorno = 1;
        for(i=0;i < size && array[i] != '\0';i++)
        {
            if((array[i] < '0') && (array[i] > '9'))
            {
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}

// && array[i] < minimo && array[i] > maximo
/**
 * \brief Verifica si el string recibido es de tipo float
 * \param array Es el array para validar su tipo
 * \return 1 si contiene solo un '.' y numeros y 0 si no cumple
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
       retorno = 1;
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
       }
   }

   return retorno;
}


/**
 * \brief Verifica si el string recibido tiene solo letras
 * \param array Es el array para validar su tipo
 * \return 1 si contiene solo ' ' y letras y 0 si no lo es
 *
 */
int validacion_Letras(char* array,int size)
{
    int retorno = 0;
    int i;
    int digitosIngresados;

    digitosIngresados = strlen(array);

    if(array != NULL)
    {
        retorno = 1;
        for(i=0;i < digitosIngresados && array[i] != '\0';i++)
        {
            if((tolower(array[i]) < 'a' || tolower(array[i]) > 'z') && array[i]!= ' ' && array[i]!= '-')
            {
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}

/**
 * \brief Verifica si el valor recibido contiene solo letras y números
 * \param array Es el string para validar el tipo
 * \return 1 si contiene solo espacio o letras y números, y 0 si no lo es
 *
 */
int validacion_AlfaNumerico(char* array,int size)
{
   int i=0;
   int retorno = 0;

   if(array != NULL && size > 0)
   {
       retorno = 1;
       for(i=0;i<size;i++)
       {
           if((array[i] != ' ') &&
              (array[i] < 'a' || array[i] > 'z') &&
              (array[i] < 'A' || array[i] > 'Z') &&
              (array[i] < '0' || array[i] > '9'))
           {
            retorno = 0;
            break;
           }

       }

   }
   return retorno;
}

/**
 * \brief Verifica si el string recibido es un numero de telefono valido
 * \param array Es el string recibido para ser validado
 * \return 1 si contiene solo numeros, espacios y un guion.
 *
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
       retorno = 1;
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
       }
   }

   return retorno;
}

/**
 * \brief Verifica si el string recibido es un numero de dni valido
 * \param array Es el string recibido para ser validado
 * \return 1 si contiene solo numeros, espacios y un guion.
 *
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
       retorno = 1;
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
       }
   }
   return retorno;
}


int validacion_Cuit(char* array,int size)
{
   int i=0;
   int retorno = 0;
   int contadorSimbolos = 0;
   int digitosIngresados;

   digitosIngresados = strlen(array);

   if(array != NULL && size > 0)
   {
       retorno = 1;
       for(i=0;i < size && array[i] != '\0';i++)
       {
            if(array[i] < '0' || array[i] > '9')
            {
                if(array[2] != '-' || array[11] != '-' || contadorSimbolos > 2 || digitosIngresados > 13)
                {
                    printf("\nENTRO AL IF %d",i);
                retorno = 0;
                break;
                }
            }

            if(array[i] == '-')
            {
                contadorSimbolos++;
            }
       }
   }
   return retorno;
}
