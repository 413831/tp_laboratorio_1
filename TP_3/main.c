#include <stdio_ext.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/

int main()
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
//Fabricarse el arhivo binario para cargarlo
//Crear funcion mapping (recibe puntero a funcion para modificar X caracteristica del elemento , retorna elemento)
//Crear un iterador (variable estatica como guía mas variable movible como next)
//Crear funciones criterio
//Crear funcion de sublistas
//Crear controller_init (El start del switch)
