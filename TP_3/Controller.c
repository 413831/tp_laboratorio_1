#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"


//El controller es quien define "QUÉ" hace el programa


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
    FILE* pArchivo = fopen(path,"r");
    int retorno = -1;
    if(pArrayListEmployee != NULL && path != NULL)
    {
        retorno = parser_EmployeeFromText(pArchivo,pArrayListEmployee);
    }
    fclose(pArchivo);
    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
    FILE* pArchivo = fopen(path,"rb");
    int retorno = -1;
    if(pArrayListEmployee != NULL && path != NULL)
    {
        retorno = parser_EmployeeFromBinary(pArchivo,pArrayListEmployee);
    }
    fclose(pArchivo);
    return retorno;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    if(pArrayListEmployee != NULL)
    {
        printf("\n<ALTA>");

        if(!employee_EmployeeFromUser(pArrayListEmployee))
        {
            printf("\nEmployee added :)");
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{//Agregar SWITCH para opciones
    int retorno = -1;

    if(pArrayListEmployee != NULL)
    {
        printf("\n<MODIFICAR DATOS>");
        if(!employee_edit(pArrayListEmployee))
        {
            printf("\nEmployee modified :)");
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee,Employee* arrayDismissed[])
{
    int retorno = -1;
    if(pArrayListEmployee != NULL)
    {
        printf("\n<BAJA>");
        if(!employee_remove(pArrayListEmployee,arrayDismissed))
        {
            printf("\nEmployee removed :(");
            retorno = 0;
        }
    }
    return retorno;
    return 1;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int i;
    Employee* employee;

    if(pArrayListEmployee != NULL)
    {
        printf("\n<LISTAR>");
        for(i=0;i<ll_len(pArrayListEmployee);i++)
        {
            employee = ll_get(pArrayListEmployee,i);
            if(employee != NULL)
            {
                employee_show(employee);
            }
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    if(pArrayListEmployee != NULL)
    {
        if(!ll_sort(pArrayListEmployee,employee_sort,1))
        {
           retorno = 0;
        }
    }
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
    FILE* pArchivo = fopen(path,"w");
    int retorno = -1;
    if(pArchivo != NULL && !parser_SaveToText(pArchivo,pArrayListEmployee))
    {
        printf("\n<GUARDAR TEXTO>");
        retorno = 0;
    }
    fclose(pArchivo);
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
    FILE* pArchivo = fopen(path,"wb");
    int retorno = -1;
    if(pArchivo != NULL && !parser_SaveToBinary(pArchivo,pArrayListEmployee))
    {
        printf("\n<GUARDAR BINARIO>");
        retorno = 0;
    }
    fclose(pArchivo);
    return retorno;
}

