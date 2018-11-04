#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "utn.h"


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
    limpiarPantalla();

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
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee,Employee* arrayDismissed[])
{
    int retorno = -1;
    limpiarPantalla();
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
    function_type criterio;
    if(pArrayListEmployee != NULL)
    {
        criterio = employee_selectorCriterio();
        if(criterio!=NULL)
        {
            printf("\n%p",criterio);
        }
        if(ll_sort(pArrayListEmployee,criterio,1))
        {
            printf("\nORDENADO!!!");
            pause();
            controller_ListEmployee(pArrayListEmployee);
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

int controller_init()
{

    int option;
    int counter = 0;
    int flag = 0;
    LinkedList* listaEmpleados = ll_newLinkedList();
    Employee* arrayDismissed[2000];//HARDCODE
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
                    printf("\nCarga realizada previamente modo texto");
                    break;
                }
                else if(flag == 2)
                {
                    printf("\nCarga realizada previamente modo binario");
                    break;
                }
                printf("\nSize Linked List %d",ll_len(listaEmpleados));
                if(!controller_loadFromText("data.csv",listaEmpleados))
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
                    printf("\nCarga realizada previamente modo texto");
                    break;
                }
                else if(flag == 2)
                {
                    printf("\nCarga realizada previamente modo binario");
                    break;
                }
                printf("\nSize Linked List %d",ll_len(listaEmpleados));
                if(!controller_loadFromBinary("data.bin",listaEmpleados))
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
                    controller_removeEmployee(listaEmpleados,arrayDismissed);
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
                    printf("\nSize Linked List %d",ll_len(listaEmpleados));
                }
                else
                {
                    printf("\nNo hay datos cargados");
                }
                break;
            case 8: //GUARDAR TEXTO
                if(counter > 0)
                {
                    if(!controller_saveAsText("data.csv",listaEmpleados))
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
                    if(!controller_saveAsBinary("data.bin",listaEmpleados))
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
