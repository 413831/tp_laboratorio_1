#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"
#include "../inc/Employee.h"
#include "../inc/utn.h"
#include "../inc/parser.h"

#define BUFFER 2000

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param pFile Es el puntero a archivo para leer los datos
 * \param pLinkedListEmployee Es la LinkedList donde se guardaran los datos
 * \return Retorna 0 si existe el archivo sino retorna -1
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pLinkedListEmployee)
{
    int retorno = -1;
    char* bufferId;
    char* bufferName;
    char* bufferHorasTrabajadas;
    char* bufferSueldo;
    char bufferText[BUFFER];
    Employee* pEmployee;

    if(pFile != NULL)
    {
        while(!feof(pFile))
        {
            fgets(bufferText,sizeof(bufferText),pFile);
            if(bufferText != NULL || strlen(bufferText) > 8)
            {
                bufferId = strtok(bufferText,",");
                bufferName = strtok(NULL,",");
                bufferHorasTrabajadas = strtok(NULL,",");
                bufferSueldo = strtok(NULL,"\n");

                pEmployee = employee_newConParametros(bufferId,bufferName,bufferHorasTrabajadas,bufferSueldo);
                if(pEmployee != NULL)
                {
                    ll_add(pLinkedListEmployee,pEmployee);//Se agrega ELEMENTO a LINKED LIST
                    retorno = 0;
                }
            }
        }
    }
    return retorno;
}


/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param pFile Es el puntero a archivo para leer los datos
 * \param pLinkedListEmployee Es la LinkedList donde se guardaran los datos
 * \return Retorna 0 si existe el archivo sino retorna -1
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pLinkedListEmployee)
{
    int retorno = -1;
    int cantidadLeida;
    Employee* pEmployee;
    Employee* aux = employee_new();

    if(pFile != NULL)
    {
        while(!feof(pFile))
        {
            pEmployee = employee_new();
            cantidadLeida = fread(pEmployee,sizeof(Employee),1,pFile);
            if(pEmployee != NULL && cantidadLeida == 1)
            {
                employee_setId(aux,"0");
                ll_add(pLinkedListEmployee,pEmployee);
                retorno = 0;
            }
        }
    }
    return retorno;
}

/** \brief Parsea los datos del linked list al archivo data.csv (modo texto).
 *
 * \param pFile Es el puntero a archivo para escribir los datos
 * \param pLinkedListEmployee Es la LinkedList de donde se toman los datos
 * \return Retorna 0 si existe el archivo y el LinkedList sino retorna -1
 *
 */
int parser_SaveToText(FILE* pFile , LinkedList* pLinkedListEmployee)
{
    int retorno = -1;
    Employee* auxEmployee;
    int len;
    int index;
    int bufferId;
    char bufferName[BUFFER];
    int bufferHorasTrabajadas;
    float bufferSueldo;

    if(pFile != NULL && pLinkedListEmployee != NULL)
    {
        len = ll_len(pLinkedListEmployee);

        for(index=0;index<len;index++)//Recorro todo el array hasta el LEN
        {
            auxEmployee = ll_get(pLinkedListEmployee,index);//Obtengo el elemento del array en posicion index
            employee_getAll(auxEmployee,bufferName,&bufferHorasTrabajadas,&bufferSueldo,&bufferId);
            fprintf(pFile,"%d,%s,%d,%f\n",bufferId,bufferName,bufferHorasTrabajadas,bufferSueldo);
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Parsea los datos del linked list al archivo data.bin (modo binario).
 *
 * \param pFile Es el puntero a archivo para escribir los datos
 * \param pLinkedListEmployee Es la LinkedList de donde se toman los datos
 * \return Retorna 0 si existe el archivo y el LinkedList sino retorna -1
 *
 */
int parser_SaveToBinary(FILE* pFile , LinkedList* pLinkedListEmployee)
{
    int retorno = -1;
    int i = 0;
    int len;
    Employee* auxEmployee;

    if(pFile != NULL && pLinkedListEmployee != NULL)
    {
        len = ll_len(pLinkedListEmployee);
        while(i != len)
        {
            auxEmployee = ll_get(pLinkedListEmployee,i);
            if(auxEmployee != NULL)
            {
                fwrite(auxEmployee,sizeof(Employee),1,pFile);
            }
            retorno = 0;
            i++;
        }
    }
    return retorno;
}
