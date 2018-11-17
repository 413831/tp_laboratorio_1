#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/Controller.h"
#include "../inc/LinkedList.h"
#include "../inc/Employee.h"
#include "../inc/utn.h"
#include "../inc/parser.h"

#define BUFFER 4000
#define LEN_LL 5
/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path Ruta del archivo para leer
 * \param pLinkedList Es el LinkedList
 * \return retorna 0 si el array no es null y el archivo existe sino retorna -1
 *
 */
int controller_loadFromText(char* path , LinkedList* pLinkedList)
{
    int retorno = -1;
    FILE* pFile = fopen(path,"r");

    if(pLinkedList != NULL && path != NULL)
    {
        if(!parser_EmployeeFromText(pFile,pLinkedList))
        {
            retorno = 0;
            fclose(pFile);
        }
    }
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
        if(!employee_edit(pLinkedList))
        {
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
        ll_map(pLinkedList,employee_show);
        printf("\nSize Linked List %d",ll_len(pLinkedList));
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
int controller_generateNewList(LinkedList* pLinkedList,LinkedList* listaPrincipal[])
{
    limpiarPantalla();
    int retorno = -1;
    char nombreArchivo[BUFFER];
    void* pNewLinkedList;
    int index;
    char path[BUFFER] = {"../files/"};

    if(pLinkedList != NULL)
    {
        printf("\n<GENERAR LISTA>");
        pNewLinkedList = ll_newLinkedList();

        if(pNewLinkedList != NULL)
        {
            if(!employee_generarLista(pLinkedList,listaPrincipal,&index))
            {
                input_getPath(nombreArchivo,BUFFER,"\nIngrese nombre de archivo a guardar\n","Nombre invalido",2);
                strcat(path,nombreArchivo);
                controller_saveAsText(path,listaPrincipal[index]);
                retorno = 0;
            }
        }
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
        printf("\nArchivo %s guardado",path);
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
        printf("\nArchivo %s guardado",path);
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
    LinkedList* listaPrincipal[LEN_LL];
    LinkedList* listaEmpleados = ll_newLinkedList();
    LinkedList* listaInactivos = ll_newLinkedList();
    char nombreArchivo[BUFFER];
    char path[BUFFER] = {"../files/"};
    ll_initLinkedList(listaPrincipal);
    int isEmpty;

    do
    {
        printf("\n>>MENU<<\n1) Abrir archivo (modo texto)\n2) Carga de archivo (modo binario)");
        printf("\n3) Alta\n4) Editar\n5) Baja\n6) Listar activos o inactivos\n7) Ordenar");
        printf("\n8) Guardar (modo texto)\n9) Guardar (modo binario)\n10) Generar listas\n11) Salir");
        input_getEnteros(&option,"\nIngrese opcion: ","\nDato invalido",2);

        switch(option)
        {
            case 1: //ABRIR TEXTO
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
                input_getPath(nombreArchivo,BUFFER,"\nIngrese nombre de archivo: ","Nombre invalido",2);
                strcat(path,nombreArchivo);
                if(!controller_loadFromText(path,listaEmpleados))
                {
                    printf("\nArchivo |%s| cargado.",nombreArchivo);
                    listaPrincipal[1] = listaEmpleados;
                    counter = ll_len(listaEmpleados);
                    flag = 1;
                }
                else
                {
                    printf("\nArchivo inexistente.");
                }
                printf("\nTotal elementos: %d",ll_len(listaEmpleados));
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
                printf("\nTotal elementos: %d",ll_len(listaEmpleados));
                if(!controller_loadFromBinary("../files/data.bin",listaEmpleados))
                {
                    printf("\nDatos cargados");
                    counter = ll_len(listaEmpleados);
                    flag = 2;
                }
                printf("\nElementos cargados: %d",ll_len(listaEmpleados));
                break;
            case 3: //ALTA
                if(counter > 0)
                {
                    controller_addEmployee(listaEmpleados);
                    printf("\nTotal elementos: %d",ll_len(listaEmpleados));
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
                    printf("\nTotal elementos: %d",ll_len(listaEmpleados));
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
                    limpiarPantalla();
                    printf("\n<LISTAR>");
                    printf("\n1) Empleados activos\n2) Empleados inactivos \n3) Sublista\n4) Lista filtrada\n5) Back-up");
                    input_getEnteros(&option,"\nIngrese opcion: ","\nError",2);
                    isEmpty = ll_isEmpty(listaPrincipal[option]);
                    printf("\nIsEmpty %d",isEmpty);
                    if(option >= 1 && option <= 5 && isEmpty == 0)
                    {
                        controller_ListEmployee(listaPrincipal[option]);
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
                    if(!input_getPath(nombreArchivo,BUFFER,"\nIngrese nombre de archivo: ","Nombre invalido",2))
                    {
                        strcat(path,nombreArchivo);
                    }
                    if(!controller_saveAsText(path,listaEmpleados))
                    {
                        printf("\nArchivo |%s| guardado.",nombreArchivo);
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
             case 10: //GENERAR LISTAS
                if(counter > 0)
                {
                    if(!controller_generateNewList(listaEmpleados,listaPrincipal))
                    {
                        printf("\nLista generada.");
                    }
                }
                else
                {
                    printf("\nNo hay datos cargados");
                }
                break;
            case 11: //SALIR
                printf("\nSALIR");
                break;
            default :
                printf("\nOpcion incorrecta");
        }
        pause();
        limpiarPantalla();
    }while(option != 11);
    return 0;
}
