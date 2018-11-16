#include <stdio.h>
#include <stdlib.h>
#include "../inc/Controller.h"
#include "../inc/LinkedList.h"
#include "../inc/Employee.h"
#include "../inc/utn.h"
#include "../inc/parser.h"

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path Ruta del archivo para leer
 * \param pArrayListEmployee Es el LinkedList
 * \return retorna 0 si el array no es null y el archivo existe sino retorna -1
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

/** \brief Carga los datos de los empleados desde el archivo data.bin (modo binario).
 *
 * \param path Ruta del archivo para leer
 * \param pArrayListEmployee Es el LinkedList
 * \return retorna 0 si el array no es null y el archivo existe sino retorna -1
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
 * \param pArrayListEmployee Es el LinkedList donde se agregara el empleado
 * \return Retorna 0 si se logra hacer el alta sino retorna -1
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    limpiarPantalla();

    if(pArrayListEmployee != NULL)
    {
        printf("\n<ALTA>");
        if(!employee_add(pArrayListEmployee))
        {
            printf("\nEmployee added :)");
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param pArrayListEmployee Es el LinkedList del cual se va a editar un empleado
 * \return Retorna 0 si se logra editar sino retorna -1
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    limpiarPantalla();
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
 * \param pArrayListEmployee Es la LinkedList de empleados activos
 * \param arrayDismissed Es la LinkedList de empleados inactivos !!!!!!!!!!!!!!!!!!!!!!!!!
 * \return Retorna 0 si se logra realizar la baja sino retorna -1
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;

    limpiarPantalla();
    if(pArrayListEmployee != NULL)
    {
        printf("\n<BAJA>");
        if(!employee_remove(pArrayListEmployee))
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
 * \param pArrayListEmployee Es la LinkedList de la cual se desea listar los elementos
 * \return retorna 0 si la LinkedList es diferente a NULL sino retorna -1
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

/** \brief Ordenar empleados por criterio y orden
 *
 * \param pArrayListEmployee Es la LinkedList que se desea ordenar
 * \return retorna 0 si se logra ordenar sino retorna -1
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;

    if(pArrayListEmployee != NULL)
    {
        if(!employee_sort(pArrayListEmployee))
        {
            retorno = 0;
            printf("\nORDENADO");
        }
        else
        {
            printf("\nError.");
        }
    }
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path Ruta donde se guardara el archivo
 * \param pArrayListEmployee Es la LinkedList con los elementos a guardar
 * \return Retorna 0 si se logra guardar sino retorna -1
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

/** \brief Guarda los datos de los empleados en el archivo data.bin (modo binario).
 *
 * \param path Ruta donde se guardara el archivo
 * \param pArrayListEmployee Es la LinkedList con los elementos a guardar
 * \return Retorna 0 si se logra guardar sino retorna -1
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

/** \brief Menu con opciones para trabajar con la LinkedList
 *
 * \return Retorna 0 siempre
 *
 */
int controller_init()
{
    int option;
    int counter = 0;
    int flag = 0;
    LinkedList* listaEmpleados = ll_newLinkedList();

    do
    {
        printf("\n>>MENU<<\n1) Carga de archivo (modo texto)\n2) Carga de archivo (modo binario)");
        printf("\n3) Alta\n4) Editar\n5) Baja\n6) Listar\n7) Ordenar");
        printf("\n8) Guardar (modo texto)\n9) Guardar (modo binario)\n10) Salir");
        input_getEnteros(&option,"\nIngrese opcion: ","\nDato invalido",2);

        switch(option)
        {
            case 1: //CARGA TEXTO
                //BUSCAR FUNCION PARA BORRAR
                if(flag == 1)
                {
                    printf("\nCarga realizada previamente (modo texto)");
                    break;
                }
                else if(flag == 2)
                {
                    printf("\nCarga realizada previamente (modo binario)");
                    break;
                }
                printf("\nSize Linked List %d",ll_len(listaEmpleados));
                if(!controller_loadFromText("../files/data.csv",listaEmpleados))
                {
                    printf("\nDatos cargados");
                    counter = ll_len(listaEmpleados);
                    flag = 1;
                }
                printf("\nSize Linked List %d",ll_len(listaEmpleados));
                break;
            case 2: // CARGA BINARIO
                if(flag == 1)
                {
                    printf("\nCarga realizada previamente (modo texto)");
                    break;
                }
                else if(flag == 2)
                {
                    printf("\nCarga realizada previamente (modo binario)");
                    break;
                }
                printf("\nSize Linked List %d",ll_len(listaEmpleados));
                if(!controller_loadFromBinary("../files/data.bin",listaEmpleados))
                {
                    printf("\nDatos cargados");
                    counter = ll_len(listaEmpleados);
                    flag = 2;
                }
                printf("\nSize Linked List %d",ll_len(listaEmpleados));
                break;
            case 3: //ALTA
                if(counter > 0)
                {
                   controller_addEmployee(listaEmpleados);
                    printf("\nSize Linked List %d",ll_len(listaEmpleados));
                    counter = ll_len(listaEmpleados);
                }
                else
                {
                    printf("\nNo hay datos cargados");
                }
                break;
            case 4: //MODIFICACION
                if(counter > 0)
                {
                    controller_editEmployee(listaEmpleados);
                }
                else
                {
                    printf("\nNo hay datos cargados");
                }
                break;
            case 5: //BAJA
                if(counter > 0)
                {
                    controller_removeEmployee(listaEmpleados);
                    printf("\nSize Linked List %d",ll_len(listaEmpleados));
                    counter = ll_len(listaEmpleados);
                }
                else
                {
                    printf("\nNo hay datos cargados");
                }
                break;
            case 6: //LISTAR
                if(counter > 0)
                {
                    controller_ListEmployee(listaEmpleados);
                    printf("\nSize Linked List %d",ll_len(listaEmpleados));
                }
                else
                {
                    printf("\nNo hay datos cargados");
                }
                break;
            case 7: //ORDENAR
                if(counter > 0)
                {
                    controller_sortEmployee(listaEmpleados);
                }
                else
                {
                    printf("\nNo hay datos cargados");
                }
                break;
            case 8: //GUARDAR TEXTO
                if(counter > 0)
                {
                    if(!controller_saveAsText("../files/data.csv",listaEmpleados))
                    {
                        printf("\nArchivo guardado.");
                    }
                }
                else
                {
                    printf("\nNo hay datos cargados");
                }
                break;
            case 9: //GUARDAR BINARIO
                if(counter > 0)
                {
                    if(!controller_saveAsBinary(".../files/data.bin",listaEmpleados))
                    {
                        printf("\nArchivo guardado.");
                    }
                }
                else
                {
                    printf("\nNo hay datos cargados");
                }
                break;
            case 10: //SALIR
                printf("\nSALIR");
                break;
            default :
                printf("\nOpcion incorrecta");
        }
        pause();
        limpiarPantalla();
    }while(option != 10);
    return 0;
}
