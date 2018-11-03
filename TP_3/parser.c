#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"

#define BUFFER 1000

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    char bufferId[1000];
    char bufferName[1000];
    char bufferHorasTrabajadas[1000];
    char bufferSueldo[1000];
    Employee* pEmployee;

    if(pFile != NULL)
    {
        while(!feof(pFile))
        {
            fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",bufferId,bufferName,bufferHorasTrabajadas,bufferSueldo);
            pEmployee = employee_newConParametros(bufferId,bufferName,bufferHorasTrabajadas,bufferSueldo);
            if(pEmployee != NULL)
            {
                ll_add(pArrayListEmployee,pEmployee);//Se agrega ELEMENTO a LINKED LIST
                retorno = 0;
            }
        }
    }
    return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
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
                ll_add(pArrayListEmployee,pEmployee);//Se agrega ELEMENTO a LINKED LIST
                retorno = 0;
            }
        }
    }
    return retorno;
}

/** \brief Parsea los datos del linked list al archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_SaveToText(FILE* pFile , LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    Employee* auxEmployee;
    int len;
    int index;
    int bufferId;
    char bufferName[1000];
    int bufferHorasTrabajadas;
    float bufferSueldo;

    if(pFile != NULL && pArrayListEmployee != NULL)
    {
        len = ll_len(pArrayListEmployee);

        for(index=0;index<len;index++)//Recorro todo el array hasta el LEN
        {
            auxEmployee = ll_get(pArrayListEmployee,index);//Obtengo el elemento del array en posicion index
            employee_getAll(auxEmployee,bufferName,&bufferHorasTrabajadas,&bufferSueldo,&bufferId);
            fprintf(pFile,"%d,%s,%d,%f\n",bufferId,bufferName,bufferHorasTrabajadas,bufferSueldo);
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Parsea los datos del linked list al archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_SaveToBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int i = 0;
    int len;
    Employee* auxEmployee;

    if(pFile != NULL && pArrayListEmployee != NULL)
    {
        len = ll_len(pArrayListEmployee);
        while(i != len)
        {
            auxEmployee = ll_get(pArrayListEmployee,i);
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
