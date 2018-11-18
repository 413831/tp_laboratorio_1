#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "../inc/Controller.h"
#include "../inc/LinkedList.h"
#include "../inc/Employee.h"
#include "../inc/utn.h"
#include "../inc/parser.h"

#define BUFFER 4000
#define LEN_LL 6

extern int errno ;

static char* fecha()
{
    char* retorno = NULL;
    time_t rawtime;//Variable tipo time_t
    struct tm *info;//Tipo de dato tm para cargar fecha y hora

    time(&rawtime);//Se obtiene dia y hora actual
    info = localtime( &rawtime );//Se obtiene formato para fecha y hora
    retorno = asctime(info);

   // printf("%s", asctime(info));//Se muestra informacion
    return retorno;
}

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
        ll_clear(pLinkedList);
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
        printf("<ALTA>");
        if(!employee_add(pLinkedList))
        {
            printf("\nAlta realizada.");
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
            printf("\nModificacion realizada.");
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
int controller_removeEmployee(LinkedList* listaPrincipal[])
{
    int retorno = -1;
    char path[BUFFER] = {"../files/bajas.csv"};

    limpiarPantalla();
    if(listaPrincipal != NULL)
    {
        printf("<BAJA>");
        if(!employee_remove(listaPrincipal[1],listaPrincipal[2]))
        {
            controller_saveAsText(path,listaPrincipal[2]);
            printf("\nBaja realizada.");
            retorno = 0;
        }
    }
    return retorno;
}

int controller_insertEmployee(LinkedList* listaPrincipal[])
{
    int retorno = -1;

    if(listaPrincipal != NULL)
    {
        if(!employee_insert(listaPrincipal[1],listaPrincipal[2]))
        {
            printf("\nEmpleado incorporado.");
        }
    }
    return retorno;
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

    if(pLinkedList != NULL && !ll_isEmpty(pLinkedList))
    {
        ll_map(pLinkedList,employee_show);
        printf("\nTotal empleados %d",ll_len(pLinkedList));
    }
    else
    {
        printf("\nLista inexistente");
    }
    return retorno;
}

/** \brief Generar una nueva lista a partir de la primer lista
 *
 * \param pLinkedList Es el LinkedList del cual se va a editar un empleado
 * \return Retorna 0 si se logra editar sino retorna -1
 *
 */
int controller_generateNewList(LinkedList* listaPrincipal[])
{
    limpiarPantalla();
    int retorno = -1;
    char nombreArchivo[BUFFER];
    int index;
    char path[BUFFER] = {"../files/"};

    if(listaPrincipal != NULL)
    {
        printf("<GENERAR LISTA>");

        if(!employee_generarLista(listaPrincipal[1],listaPrincipal,&index))
        {
            printf("\n>> Atención! si el archivo ya existe sera reemplazado por el actual.");
            input_getPath(nombreArchivo,BUFFER,"\nIngrese nombre de archivo a guardar\n>>","Nombre invalido",2);
            strcat(path,nombreArchivo);
            controller_saveAsText(path,listaPrincipal[index]);
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Eliminar una lista
 *
 * \param pLinkedList Es el LinkedList del cual se va a editar un empleado
 * \return Retorna 0 si se logra editar sino retorna -1
 *
 */
int controller_deleteList(LinkedList* pLinkedList)
{
    int retorno = -1;

    if(pLinkedList != NULL)
    {
        if(!employee_borrarLista(pLinkedList))
        {
            retorno = 0;
        }
    }
    else
    {
        printf("\nLista inexistente.");
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
        }
        else
        {
            printf("\nError.");
        }
    }
    return retorno;
}


/** \brief Carga la lista temporal para deshacer todos los cambios
 *
 * \param pLinkedList Es la LinkedList que se desea deshacer cambios
 * \param pLinkedListTemp Es la LinkedList de donde se toman los datos
 * \return retorna 0 si se logra ordenar sino retorna -1
 *
 */
int controller_undoList(LinkedList* listaPrincipal[])
{
    int retorno = -1;
    char verification[5];

    if(listaPrincipal != NULL)
    {
        input_getLetras(verification,2,"\nATENCION!\nDesea deshacer todos los cambios? S/N\n","\nError.",2);
        if(!strcasecmp("s",verification))
        {
            listaPrincipal[1] = ll_clone(listaPrincipal[0]);
            retorno = 0;
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
    char nombreArchivo[BUFFER];
    char path[BUFFER];

    ll_initLinkedList(listaPrincipal);
    /*  lista[0] - temporal
    /   lista[1] - listado activos
    /   lista[2] - listado inactivos
    /   lista[3] - sublista desde index x hasta y
    /   lista[4] - lista filtrada
    /   lista[5] - back-up de activos
    */
    do
    {
        if(flag == 1)
        {
            listaPrincipal[0] = ll_clone(listaPrincipal[1]);
            controller_saveAsBinary("../files/temp.bin",listaPrincipal[0]);
            flag = 2;
        }

        printf("%s\n>>>MENU PRINCIPAL<<<\n",fecha());
        printf("\n1) Abrir archivo (modo texto)\n2) Listar\n3) Alta\n4) Editar\n5) Baja");
        printf("\n6) Ordenar\n7) Guardar (modo texto) \n8) Generar listas\n9) Eliminar lista");
        printf("\n10) Reincorporar empleado\n11) Deshacer cambios\n12) Salir");
        input_getEnteros(&option,"\nIngrese opcion: ","\nDato invalido",2);

        switch(option)
        {
            case 1: //ABRIR ARCHIVO
                strcpy(path,"../files/");
                if(!input_getEnteros(&option,"\n1) Abrir modo texto\n2) Abrir en modo binario\n>> ","\nError",2))
                {
                    if(!input_getPath(nombreArchivo,BUFFER,"\nIngrese nombre de archivo: ","Nombre invalido",2))
                    {
                        strcat(path,nombreArchivo);
                    }
                    if(!controller_loadFromText(path,listaPrincipal[1]))
                    {
                        printf("\nArchivo |%s| cargado.",nombreArchivo);
                        counter = ll_len(listaPrincipal[1]);
                        flag = 1;
                    }
                    else if(option == 2 && !controller_loadFromBinary(path,listaPrincipal[1]))
                    {
                        printf("\nArchivo |%s| cargado.",nombreArchivo);
                        counter = ll_len(listaPrincipal[1]);
                        flag = 1;
                    }
                    else
                    {
                        printf("\nArchivo inexistente.");
                    }
                    printf("\nTotal empleados: %d",ll_len(listaPrincipal[1]));
                }
                break;
            case 2: //LISTAR
                if(counter > 0)
                {
                    limpiarPantalla();
                    printf("<LISTAR>");
                    printf("\n1) Empleados activos\n2) Empleados inactivos \n3) Sublista\n4) Lista filtrada\n5) Back-up");
                    input_getEnteros(&option,"\nIngrese opcion: ","\nError",2);
                    if(option >= 1 && option <= 5 )
                    {
                        controller_ListEmployee(listaPrincipal[option]);
                    }
                }
                else
                {
                    printf("\nNo hay datos cargados");
                }
                break;
            case 3: //ALTA
                if(counter > 0)
                {
                    controller_addEmployee(listaPrincipal[1]);
                    printf("\nTotal empleados: %d",ll_len(listaPrincipal[1]));
                    counter = ll_len(listaPrincipal[1]);//Cantidad de empleados
                }
                else
                {
                    printf("\nNo hay datos cargados");
                }
                break;
            case 4: //MODIFICACION
                if(counter > 0)
                {
                    controller_editEmployee(listaPrincipal[1]);
                }
                else
                {
                    printf("\nNo hay datos cargados");
                }
                break;
            case 5: //BAJA
                if(counter > 0)
                {
                    controller_removeEmployee(listaPrincipal);
                    printf("\nTotal empleados: %d",ll_len(listaPrincipal[1]));
                    counter = ll_len(listaPrincipal[1]);//Cantidad de empleados
                }
                else
                {
                    printf("\nNo hay datos cargados");
                }
                break;
            case 6 : //ORDENAR
                if(counter > 0)
                {
                    controller_sortEmployee(listaPrincipal[1]);
                }
                else
                {
                    printf("\nNo hay datos cargados");
                }
                break;
            case 7 : //GUARDAR TEXTO
                if(counter > 0)
                {
                    printf("<GUARDAR TEXTO>");
                    input_getPath(nombreArchivo,BUFFER,"\nIngrese nombre de archivo: ","Nombre invalido",2);

                    strcat(path,nombreArchivo);

                    input_getEnteros(&option,"\n1) Abrir modo texto\n2) Abrir en modo binario: ","\nError",2);
                    if(!controller_saveAsText(path,listaPrincipal[1]))
                    {
                        printf("\nArchivo |%s| guardado.",nombreArchivo);
                    }
                }
                else
                {
                    printf("\nNo hay datos cargados");
                }
                break;
             case 8 : //GENERAR LISTAS
                if(counter > 0)
                {
                    if(!controller_generateNewList(listaPrincipal))
                    {
                        printf("\nLista generada.");
                    }
                }
                else
                {
                    printf("\nNo hay datos cargados");
                }
                break;
            case 9 : //BORRAR LISTAS
                if(counter > 0)
                {
                    limpiarPantalla();
                    printf("<BORRAR LISTA>");
                    printf("\n1) Empleados activos\n2) Empleados inactivos \n3) Sublista\n4) Lista filtrada\n5) Back-up");
                    input_getEnteros(&option,"\nIngrese opcion: ","\nError",2);

                    controller_deleteList(listaPrincipal[option]);
                }
                else
                {
                    printf("\nNo hay datos cargados");
                }
                break;
            case 10 : //INSERTAR EMPLEADO
                if(ll_len(listaPrincipal[2] > 0)
                {
                    controller_insertEmployee(listaPrincipal);
                    counter = ll_len(listaPrincipal[1]);
                }
                else
                {
                    printf("\nNo hay datos cargados");
                }
                break;
            case 11 : //DESHACER CAMBIOS
                if(counter > 0)
                {
                    if(!controller_undoList(listaPrincipal))
                    {
                        counter = ll_len(listaPrincipal[1]);
                    }
                }
                break;
            case 12 : //SALIR
                printf("SALIR");
                break;
            default :
                printf("\nOpcion incorrecta");
        }
        pause();
        limpiarPantalla();
    }while(option != 12);
    return 0;
}
