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
 * \param pLinkedList Es el LinkedList
 * \return retorna 0 si el array no es null y el archivo existe sino retorna -1
 *
 */
int controller_loadFromText(char* path , LinkedList* pLinkedList)
{
    FILE* pArchivo = fopen(path,"r");
    int retorno = -1;
    if(pLinkedList != NULL && path != NULL)
    {
        retorno = parser_EmployeeFromText(pArchivo,pLinkedList);
    }
    fclose(pArchivo);
    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.bin (modo binario).
 *
 * \param path Ruta del archivo para leer
 * \param pLinkedList Es el LinkedList
 * \return retorna 0 si el array no es null y el archivo existe sino retorna -1
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pLinkedList)
{
    FILE* pArchivo = fopen(path,"rb");
    int retorno = -1;
    if(pLinkedList != NULL && path != NULL)
    {
        retorno = parser_EmployeeFromBinary(pArchivo,pLinkedList);
    }
    fclose(pArchivo);
    return retorno;
}

/** \brief Alta de empleados
 *
 * \param pLinkedList Es el LinkedList donde se agregara el empleado
 * \return Retorna 0 si se logra hacer el alta sino retorna -1
 *
 */
int controller_addEmployee(LinkedList* pLinkedList)
{
    int retorno = -1;
    limpiarPantalla();

    if(pLinkedList != NULL)
    {
        printf("\n<ALTA>");
        if(!employee_add(pLinkedList))
        {
            printf("\nEmployee added :)");
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param pLinkedList Es el LinkedList del cual se va a editar un empleado
 * \return Retorna 0 si se logra editar sino retorna -1
 *
 */
int controller_editEmployee(LinkedList* pLinkedList)
{
    int retorno = -1;
    limpiarPantalla();
    if(pLinkedList != NULL)
    {
        printf("\n<MODIFICAR DATOS>");
        if(!employee_edit(pLinkedList))
        {
            printf("\nEmployee modified :)");
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Baja de empleado
 *
 * \param pLinkedList Es la LinkedList de empleados activos
 * \param arrayDismissed Es la LinkedList de empleados inactivos !!!!!!!!!!!!!!!!!!!!!!!!!
 * \return Retorna 0 si se logra realizar la baja sino retorna -1
 *
 */
int controller_removeEmployee(LinkedList* pLinkedList,LinkedList* pListInactive)
{
    int retorno = -1;

    limpiarPantalla();
    if(pLinkedList != NULL)
    {
        printf("\n<BAJA>");
        if(!employee_remove(pLinkedList,pListInactive))
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
 * \param pLinkedList Es la LinkedList de la cual se desea listar los elementos
 * \return retorna 0 si la LinkedList es diferente a NULL sino retorna -1
 *
 */
int controller_ListEmployee(LinkedList* pLinkedList)
{
    int retorno = -1;

    if(pLinkedList != NULL)
    {
        printf("\n<LISTAR>");
        ll_map(pLinkedList,employee_show);
        printf("\nSize Linked List %d",ll_len(listaEmpleados));
    }
    else
    {
        printf("\nLista inexistente");
    }
    return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param pLinkedList Es el LinkedList del cual se va a editar un empleado
 * \return Retorna 0 si se logra editar sino retorna -1
 *
 */
int controller_generateNewList(LinkedList* pLinkedList,)
{
    limpiarPantalla();
    int retorno = -1;
    int option;
    int from = 0;
    int to = 0;
    LinkedList* pNewLinkedList;
    function_type criterio;

    if(pLinkedList != NULL)
    {
        printf("\n<GENERAR LISTA>");
        pNewLinkedList =  ll_newLinkedList();
        input_getEnteros(&option,"\n1) Dividir lista\n2) Filtrar\n3) Copiar\n\nIngrese opcion: ","\nDato invalido",2);
        switch(option)
        {
            case 1 :
                input_getEnteros(&from,"\nSeleccione primer indice: ","\nDato invalido",2);
                input_getEnteros(&to,"\nSeleccione segundo indice","\nDato invalido",2);
                pNewLinkedList = ll_sublist(pLinkedList,from,to)
            break;
            case 2 :
                printf("\nSeleccione criterio para filtrar")
                criterio = employee_selectorCriterio()
                pNewLinkedList = ll_filter(pLinkedList,criterio);
            break;
            case 3 :
                pNewLinkedList = ll_clone(pLinkedList);
            break;
        }

        if(pNewLinkedList != NULL)
        {

        }
        else
        {
            ll_deleteLinkedList(pNewLinkedList);
        }
    return retorno;
}


/** \brief Ordenar empleados por criterio y orden
 *
 * \param pLinkedList Es la LinkedList que se desea ordenar
 * \return retorna 0 si se logra ordenar sino retorna -1
 *
 */
int controller_sortEmployee(LinkedList* pLinkedList)
{
    int retorno = -1;

    if(pLinkedList != NULL)
    {
        if(!employee_sort(pLinkedList))
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
 * \param pLinkedList Es la LinkedList con los elementos a guardar
 * \return Retorna 0 si se logra guardar sino retorna -1
 *
 */
int controller_saveAsText(char* path , LinkedList* pLinkedList)
{
    FILE* pArchivo = fopen(path,"w");
    int retorno = -1;

    if(pArchivo != NULL && !parser_SaveToText(pArchivo,pLinkedList))
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
 * \param pLinkedList Es la LinkedList con los elementos a guardar
 * \return Retorna 0 si se logra guardar sino retorna -1
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pLinkedList)
{
    FILE* pArchivo = fopen(path,"wb");
    int retorno = -1;

    if(pArchivo != NULL && !parser_SaveToBinary(pArchivo,pLinkedList))
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
    LinkedList* listaInactivos = ll_newLinkedList();

    do
    {
        printf("\n>>MENU<<\n1) Carga de archivo (modo texto)\n2) Carga de archivo (modo binario)");
        printf("\n3) Alta\n4) Editar\n5) Baja\n6) Listar activos o inactivos\n7) Ordenar");
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
                    controller_removeEmployee(listaEmpleados,listaInactivos);
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
                    input_getEnteros(&option,"\n1) Empleados activos\n2) Empleados inactivos \nIngrese opcion: ","\nError",2);
                    if(option == 1)
                    {
                        controller_ListEmployee(listaEmpleados);

                    }
                    else if(option == 2)
                    {
                        controller_ListEmployee(listaInactivos);
                    }
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
