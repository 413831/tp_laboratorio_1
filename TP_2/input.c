#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"

/**
 * \brief Limpia el buffer del teclado
 * \param void
 * \return void
 */

void limpiarMemoria()
{
    //fflush(stdin);  //WINDOWS
    __fpurge(stdin);  //LINUX
}

/**
 * \brief Limpia la pantalla de la consola
 * \param void
 * \return void
 */

void limpiarPantalla()
{
    //system("cls"); //WINDOWS
    system("clear"); //LINUX
}

/**
 * \brief Solicita un número entero y lo retorna
 * \param mensaje Es el mensaje para mostrar al usuario
 * \param numero Es el puntero de la variable para guardar el numero ingresado
 * \return Retorna 0 si se realiza si no retorna -1
 */

int input_ScanInt(char* mensaje,int* numero)
{
    int retorno = -1;
    int auxiliarInt;
    printf("%s",mensaje);
    scanf("%d",&auxiliarInt);
    *numero = auxiliarInt;
    retorno = 0;
    return retorno;
}

/**
 * \brief Solicita un número flotante y lo retorna
 * \param mensaje Es el mensaje para mostrar al usuario
 * \param numero Es el puntero de la variable para guardar el numero ingresado
 * \return Retorna 0 si se realiza si no retorna -1
 */

float input_ScanFloat(char mensaje[],float* numero)
{
    int retorno = -1;
    float auxiliarFloat;
    printf("%s",mensaje);
    scanf("%f",&auxiliarFloat);
    *numero = auxiliarFloat;
    retorno = 0;
    return retorno;
}


/**
 * \brief Solicita un caracter y lo retorna
 * \param mensaje Es el mensaje para mostrar al usuario
 * \param caracter Es el puntero de la variable para guardar el caracter ingresado
 * \return Retorna 0 si se realiza si no retorna -1
 */

char input_ScanChar(char* mensaje,char* caracter)
{
    int retorno = -1;
    char auxiliarChar;
    printf("%s",mensaje);
    scanf("%c",&auxiliarChar);
    *caracter = auxiliarChar;
    retorno = 0;
    return retorno;
}


/**
 * \brief Ingreso de un texto al usuario y lo devuelve
 * \param mensaje Es el mensaje a ser mostrado
 * \param input Array donde se cargará el texto ingresado
 * \return void
 */

int input_getString(char mensaje[],int size,char input[])
{
    int retorno = -1;
    char buffer[size];
    int length;

    limpiarMemoria();
    fgets(buffer,size,stdin);
    if(buffer!=NULL)
    {
        length = strlen(buffer);
        if(length != size-1 || buffer[size-2] == '\n')
        {
            buffer[length-1] = '\0';
        }
        strncpy(input,buffer,size);
        retorno = 0;
    }


    return retorno;
}

/**
 * \brief Solicita ingreso de un texto con solo letras
 * \param input Es la variable donde se cargará el texto ingresado
 * \param size Es el tamaño maximo del string
 * \param mensaje Es el mensaje a ser mostrado
 * \param msjError Es el mensaje de error a ser mostrado
 * \param reintentos Es la cantidad de reintentos que tiene le usuario
 * \return Retorna 0 si lo carga en variable del main si no retorna -1
 */

int input_getLetras(char input[],int size,char mensaje[],char msjError[],int reintentos)
{
    char buffer[size];
    int retorno = 1;

    do
    {
        printf("%s",mensaje);
        //Se recibe variable a cargar por string
        if(!input_getString(mensaje,size,buffer) && validacion_Letras(buffer,size) && strlen(buffer) > 0)
        {
            strncpy(input,buffer,size);//Se copia string cargado a variable local
            retorno = 0;
            break;
        }
        else
        {
            printf("%s",msjError);
            reintentos--;
        }

    }while(reintentos > 0);

    return retorno;
}

/**
 * \brief Solicita un texto numérico al usuario y lo convierte en entero
 * \param input Es el puntero de la variable para cargar el numero
 * \param size Es la cantidad permitida de digitos del numero
 * \param mensaje Es el mensaje a ser mostrado
 * \param msjError Es el mensaje de error a ser mostrado
 * \param minimo Es el minimo valor permitido para ingresar
 * \param maximo Es el maximo valor permitido para ingresar
 * \param reintentos Es la cantidad de intentos para ingresar
 * \return Retorna 0 si se carga el numero si no retorna -1
 */

int input_getNumeros(int* input,int size,char mensaje[],char msjError[],int minimo,int maximo,int reintentos)
{
    char buffer[size];
    int retorno = -1;

    do
    {
        printf("%s",mensaje);

        if(!input_getString(mensaje,size,buffer) &&
           validacion_Int(buffer,size) &&
           atoi(buffer) >= minimo &&
           atoi(buffer) <= maximo)
        {
            *input = atoi(buffer);
            retorno = 0;
            break;
        }
        else
        {
            printf("%s",msjError);
            limpiarMemoria();
            reintentos--;
        }

    }while(reintentos > 0);

    return retorno;
}

/**
 * \brief Solicita un texto numérico al usuario y lo convierte en numero flotante
 * \param input Es el puntero de la variable para cargar el numero
 * \param size Es la cantidad permitida de digitos del numero
 * \param mensaje Es el mensaje a ser mostrado
 * \param msjError Es el mensaje de error a ser mostrado
 * \param minimo Es el minimo valor permitido para ingresar
 * \param maximo Es el maximo valor permitido para ingresar
 * \param reintentos Es la cantidad de intentos para ingresar
 * \return Retorna 0 si se carga el numero si no retorna -1
 */

int input_getFloat(float* input,int size,char mensaje[],char msjError[],float minimo,float maximo,int reintentos)
{
    char buffer[size];
    int retorno = -1;

    do
    {
        printf("%s",mensaje);

        if(!input_getString(mensaje,size,buffer) &&
           validacion_Float(buffer,size) &&
           atof(buffer) >= minimo &&
           atof(buffer) <= maximo )
        {
            *input = atof(buffer);
            retorno = 0;
            break;
        }
        else
        {
            printf("%s",msjError);
            limpiarMemoria();
            reintentos--;
        }
    }while(reintentos > 0);

    return retorno;
}


/**
 * \brief Solicita el ingreso de un texto alfanumerico
 * \param input Es la variable donde se cargará el texto ingresado
 * \param size Es el tamaño maximo del string
 * \param mensaje Es el mensaje a ser mostrado
 * \param msjError Es el mensaje de error a ser mostrado
 * \param reintentos Es la cantidad de reintentos que tiene le usuario
 * \return Retorna 0 si lo carga en variable del main si no retorna -1
 */

int input_getAlfanumerico(char input[],int size,char mensaje[],char msjError[],int reintentos)
{
    char buffer[size];
    int retorno = 1;

    do
    {
        printf("%s",mensaje);
        //Se recibe variable a cargar por string
        if(!input_getString(mensaje,size,buffer) && validacion_AlfaNumerico(buffer,size))
        {
            strncpy(input,buffer,size);//Se copia string cargado a variable local
            retorno = 0;
            break;
        }
        else
        {
            printf("%s",msjError);
            reintentos--;
        }
    }while(reintentos > 0);

    return retorno;
}


/**
 * \brief Solicita el ingreso de un numero de DNI
 * \param input Es la variable donde se cargará el texto ingresado
 * \param size Es el tamaño maximo del string
 * \param mensaje Es el mensaje a ser mostrado
 * \param msjError Es el mensaje de error a ser mostrado
 * \param reintentos Es la cantidad de reintentos que tiene le usuario
 * \return Retorna 0 si lo carga en variable del main si no retorna -1
 */

int input_getDNI(char input[],int size,char mensaje[],char msjError[],int reintentos)
{
    char buffer[size];
    int retorno = 1;

    do
    {
        printf("%s",mensaje);

        if(!input_getString(mensaje,size,buffer) && validacion_DNI(buffer,size))
        {
            strncpy(input,buffer,size);//Se copia string cargado a variable local
            retorno = 0;
            break;
        }
        else
        {
            printf("%s",msjError);
            reintentos--;
        }
    }while(reintentos > 0);

    return retorno;
}

/**
 * \brief Solicita el ingreso de un numero de Telefono
 * \param input Es la variable donde se cargará el texto ingresado
 * \param size Es el tamaño maximo del string
 * \param mensaje Es el mensaje a ser mostrado
 * \param msjError Es el mensaje de error a ser mostrado
 * \param reintentos Es la cantidad de reintentos que tiene le usuario
 * \return Retorna 0 si lo carga en variable del main si no retorna -1
 */

int input_getTelefono(char input[],int size,char mensaje[],char msjError[],int reintentos)
{
    char buffer[size];
    int retorno = 1;

    do
    {
        printf("%s",mensaje);

        if(!input_getString(mensaje,size,buffer) && validacion_Telefono(buffer,size))
        {
            strncpy(input,buffer,size);//Se copia string cargado a variable local
            retorno = 0;
            break;
        }
        else
        {
            printf("%s",msjError);
            reintentos--;
        }
    }while(reintentos > 0);

    return retorno;
}

/**
 * \brief Solicita el ingreso de un numero de CUIT
 * \param input Es la variable donde se cargará el texto ingresado
 * \param size Es el tamaño maximo del string
 * \param mensaje Es el mensaje a ser mostrado
 * \param msjError Es el mensaje de error a ser mostrado
 * \param reintentos Es la cantidad de reintentos que tiene le usuario
 * \return Retorna 0 si lo carga en variable del main si no retorna -1
 */

int input_getCuit(char input[],int size,char mensaje[],char msjError[],int reintentos)
{
    char buffer[size];
    int retorno = 1;

    do
    {
        printf("%s",mensaje);

        if(!input_getString(mensaje,size,buffer) && validacion_Cuit(buffer,size))
        {
            strncpy(input,buffer,size);//Se copia string cargado a variable local
            retorno = 0;
            break;
        }
        else
        {
            printf("%s",msjError);
            reintentos--;
        }
    }while(reintentos > 0);

    return retorno;
}

