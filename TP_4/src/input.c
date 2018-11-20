#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/utn.h"

#define BUFFER 4000


/**
 *\brief Limpia el buffer del archivo stdin
*/
static void limpiarMemoria()
{
    //fflush(stdin);  //WINDOWS
    __fpurge(stdin);  //LINUX
}

/**
 *\brief Limpia los datos mostrados en consola
*/
void limpiarPantalla()
{
    //system("cls"); //WINDOWS
    system("clear"); //LINUX
}

/**
 *\brief Pausa el programa para ver el contenido
*/
void pause()
{
    printf("\nPresione cualquier tecla para continuar...");
    limpiarMemoria();
    getchar();
}
/**
 * \brief Solicita un número entero y lo retorna
 * \param *mensaje Es el mensaje para mostrar al usuario
 * \return Entero ingresado por el usuario
 */
int input_ScanInt(char* mensaje)
{
    int auxiliarInt;
    printf("%s",mensaje);
    scanf("%d",&auxiliarInt);
    return auxiliarInt;
}

/**
 * \brief Solicita un número flotante y lo retorna
 * \param *mensaje Es el mensaje para mostrar al usuario
 * \return Flotante ingresado por el usuario
 */

float input_ScanFloat(char* mensaje)
{
    float auxiliarFloat;
    printf("%s",mensaje);
    scanf("%f",&auxiliarFloat);
    return auxiliarFloat;
}


/**
 * \brief Solicita un caracter y lo retorna
 * \param *mensaje Es el mensaje para mostrar al usuario
 * \return Caracter ingresado por el usuario
 *
 */
char input_ScanChar(char* mensaje)
{
    float auxiliarChar;
    printf("%s",mensaje);
    scanf("%f",&auxiliarChar);
    return auxiliarChar;
}

///////////////////////////////////////////////////STRINGS/////////////////////////////////////////////////////////////////////////

/**
 * \brief Solicita un dato al usuario
 * \param message Es el mensaje para mostrar al usuario
 * \param value Es la variable para retornar el dato ingresado por el usuario
 * \param size Es el limite del dato para ingresar
 * \param validacion Es el puntero a la funcion de validacion del dato
 * \return Retorna 0 si logra cargar el dato sino retorna -1;
 */
int input(char* message,char* value,int size, int (*validation)(char*))
{
    int retorno = -1;
    int retry = 2;
    char* buffer = (char*)malloc(sizeof(char)*size);

    if(value != NULL)
    {
        limpiarMemoria();
        do
        {
            printf("\nIngrese %s: ",message);
            input_getString(buffer,size);
            if((*validation)(buffer))//Validar segun tipo
            {
                buffer = (char*)realloc(buffer,(sizeof(char)*strlen(buffer)+1));
                strcpy(value,buffer);
                printf("\n-> %s",value);
                retorno = 0;
                break;
            }
            else
            {
                printf("\nIntente nuevamente");
            }
            retry--;
        }while(retry > 0);
    }
    return retorno;
}

/**
 * \brief Solicita un texto al usuario y lo devuelve
 * \param mensaje Es el mensaje a ser mostrado
 * \param input Array donde se cargará el texto ingresado
 * \return void
 */
int input_getString(char input[],int size)
{
    int retorno = -1;
    char buffer[size];
    int length;

    do
    {
        limpiarMemoria();
        fgets(buffer,size,stdin);//Se pide el dato limitado por el tamaño del array, parametro 'size'

        length = strlen(buffer);
        if(length != size-1 || buffer[size-2] == '\n')
        {
            buffer[length-1] = '\0';
        }
        strncpy(input,buffer,size);
        retorno = 0;
    }while(input == NULL && size < 0);
    return retorno;
}

/**
 * \brief Solicita un texto al usuario y lo devuelve
 * \param input Array donde se cargará el texto ingresado
 * \param mensaje Es el mensaje a ser mostrado
 * \param msjError Es el mensaje de error a ser mostrado
 * \return Retorna 0 si se pudo pedir y validar string si no retorna error
 */
int input_getLetras(char input[],int size,char mensaje[],char msjError[],int reintentos)
{
    char buffer[size];
    int retorno = -1;

     if(input != NULL && size > 0 && mensaje != NULL &&
       msjError != NULL && reintentos >= 0)
    {
        do
        {
            reintentos--;
            printf("%s",mensaje);
            //Se recibe variable a cargar por string
            if(input_getString(buffer,size) == 0 && validacion_Letras(buffer,size))
            {
                strncpy(input,buffer,size);//Se copia string cargado a variable local
                retorno = 0;
                break;
            }
            else
            {
                printf("%s",msjError);
            }
        }while(reintentos >= 0);
    }
    return retorno;
}


/**
 * \brief Solicita un texto numérico al usuario y lo devuelve
 * \param input Array donde se cargará el texto ingresado
 * \param size Es el tamaño del string recibido
 * \param mensaje Es el mensaje a ser mostrado
 * \param msjError Es el mensaje de error a ser mostrado
 * \param reintentos Es la cantidad de reintentos posibles para ingresar
 * \return Retorna 0 si se pudo pedir y validar string si no retorna error
 */
int input_getEnteros(int* input,char mensaje[],char msjError[],int reintentos)
{
    char buffer[BUFFER];
    int retorno = -1;

    if(input != NULL  && mensaje != NULL &&
       msjError != NULL && reintentos >= 0)
    {
        do
        {
            reintentos--;
            printf("%s",mensaje);
            if( input_getString(buffer,BUFFER) == 0 &&
                validacion_Int(buffer,BUFFER))
            {
                *input = atoi(buffer);//Se copia string cargado a variable local
                retorno = 0;
                break;
            }
            else
            {
                printf("%s",msjError);
            }
        }while(reintentos>=0);
    }
    return retorno;
}

/**
 * \brief Solicita un texto numérico al usuario y lo devuelve
 * \param input Array donde se cargará el texto ingresado
 * \param size Es el tamaño del string recibido
 * \param mensaje Es el mensaje a ser mostrado
 * \param msjError Es el mensaje de error a ser mostrado
 * \param reintentos Es la cantidad de reintentos posibles para ingresar
 * \return Retorna 0 si se pudo pedir y validar string si no retorna error
 */
int input_getFloat(float* input,char mensaje[],char msjError[],int reintentos)
{
    char buffer[BUFFER];
    int retorno = -1;

    if(input != NULL && mensaje != NULL &&
       msjError != NULL && reintentos >= 0)
    {
        do
        {
            reintentos--;
            printf("%s",mensaje);
            if( input_getString(buffer,BUFFER) == 0 &&
                validacion_Float(buffer,BUFFER))
            {
                *input = atof(buffer);//Se copia string cargado a variable local
                retorno = 0;
                break;
            }
            else
            {
                printf("%s",msjError);
            }
        }while(reintentos>=0);
    }
    return retorno;
}

/**
 * \brief Solicita ingresar numero de DNI
 * \param input Array donde se cargará el texto ingresado
 * \param size Es el tamaño del string recibido
 * \param mensaje Es el mensaje a ser mostrado
 * \param msjError Es el mensaje de error a ser mostrado
 * \param reintentos Es la cantidad de reintentos posibles para ingresar
 * \return Retorna 0 si se pudo pedir y validar string si no retorna error
 */
int input_getDNI(char input[],int size,char mensaje[],char msjError[],int reintentos)
{
    char buffer[size];
    int retorno = -1;

    if(input != NULL && size > 0 && mensaje != NULL &&
       msjError != NULL && reintentos >= 0)
    {
        do
        {
            reintentos--;
            printf("%s",mensaje);
            if(input_getString(buffer,size) == 0 &&
                validacion_DNI(buffer,size))
            {
                strncpy(input,buffer,size);//Se copia string cargado a variable local
                retorno = 0;
                break;
            }
            else
            {
                printf("%s",msjError);
            }

        }while(reintentos>=0);
    }
    return retorno;
}

/**
 * \brief Solicita ingresar numero de telefono
 * \param input Array donde se cargará el texto ingresado
 * \param size Es el tamaño del string recibido
 * \param mensaje Es el mensaje a ser mostrado
 * \param msjError Es el mensaje de error a ser mostrado
 * \param reintentos Es la cantidad de reintentos posibles para ingresar
 * \return Retorna 0 si se pudo pedir y validar string si no retorna error
 */
int input_getTelefono(char input[],int size,char mensaje[],char msjError[],int reintentos)
{
    char buffer[size];
    int retorno = -1;

    if(input != NULL && size > 0 && mensaje != NULL &&
       msjError != NULL && reintentos >= 0)
    {
        do
        {
            reintentos--;
            printf("%s",mensaje);
            if( input_getString(buffer,size) == 0 &&
                validacion_Telefono(buffer,size))
            {
                strncpy(input,buffer,size);//Se copia string cargado a variable local
                retorno = 0;
                break;
            }
            else
            {
                printf("%s",msjError);
            }

        }while(reintentos>=0);
    }
    return retorno;
}

/**
 * \brief Solicita ingresar numero de CUIT
 * \param input Array donde se cargará el texto ingresado
 * \param size Es el tamaño del string recibido
 * \param mensaje Es el mensaje a ser mostrado
 * \param msjError Es el mensaje de error a ser mostrado
 * \param reintentos Es la cantidad de reintentos posibles para ingresar
 * \return Retorna 0 si se pudo pedir y validar string si no retorna error
 */
int input_getCuit(char input[],int size,char mensaje[],char msjError[],int reintentos)
{
    char buffer[size];
    int retorno = -1;

    if(input != NULL && size > 0 && mensaje != NULL &&
       msjError != NULL && reintentos >= 0)
    {
        do
        {
            reintentos--;
            printf("%s",mensaje);
            if( input_getString(buffer,size) == 0 &&
                validacion_Cuit(buffer,size))
            {
                strncpy(input,buffer,size);//Se copia string cargado a variable local
                retorno = 0;
                break;

            }
            else
            {
                printf("%s",msjError);
            }

        }while(reintentos>=0);
    }
    return retorno;
}

/**
 * \brief Solicita ingresar una direccion
 * \param input Array donde se cargará el texto ingresado
 * \param size Es el tamaño del string recibido
 * \param mensaje Es el mensaje a ser mostrado
 * \param msjError Es el mensaje de error a ser mostrado
 * \param reintentos Es la cantidad de reintentos posibles para ingresar
 * \return Retorna 0 si se pudo pedir y validar string si no retorna error
 */
int input_getDireccion(char input[],int size,char mensaje[],char msjError[],int reintentos)
{
    char buffer[size];
    int retorno = -1;

    if(input != NULL && size > 0 && mensaje != NULL &&
       msjError != NULL && reintentos >= 0)
    {
        do
        {
            reintentos--;
            printf("%s",mensaje);
            if( input_getString(buffer,size) == 0 &&
                validacion_AlfaNumerico(buffer,size))
            {

                strncpy(input,buffer,size);
                retorno = 0;
                break;

            }
            else
            {
                printf("%s",msjError);
            }

        }while(reintentos>=0);

    }
    return retorno;
}

/**
 * \brief Solicita ingresar un nombre valido de archivo
 * \param input Array donde se cargará el texto ingresado
 * \param size Es el tamaño del string recibido
 * \param mensaje Es el mensaje a ser mostrado
 * \param msjError Es el mensaje de error a ser mostrado
 * \param reintentos Es la cantidad de reintentos posibles para ingresar
 * \return Retorna 0 si se pudo pedir y validar string si no retorna error
 */
int input_getPath(char input[],int size,char mensaje[],char msjError[],int reintentos)
{
    char buffer[size];
    int retorno = -1;

    if(input != NULL && size > 0 && mensaje != NULL &&
       msjError != NULL && reintentos >= 0)
    {
        do
        {
            reintentos--;
            printf("%s",mensaje);
            if( input_getString(buffer,size) == 0 &&
                validacion_File(buffer,size))
            {
                strncpy(input,buffer,size);
                retorno = 0;
                break;
            }
            else
            {
                printf("\n%s",msjError);
            }
        }while(reintentos>=0);
    }
    return retorno;
}
