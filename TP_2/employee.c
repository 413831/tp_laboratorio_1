#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "employee.h"

/**
*\brief Realiza el swap entre dos elementos
*\param valorA es el puntero del primer elemento
*\param valorB es el puntero del segundo elemento
*\return Retorna void
*/


static void swap(Employee* valorA,Employee* valorB)
{
    Employee auxiliar;//TIPO employee
    auxiliar = *valorA;
    *valorA = *valorB;
    *valorB = auxiliar;
}

/**
*\brief Genera automáticamente un ID único
*\param void
*\return Retorna el número de ID
*/

static int generateID()
{
    static int id = 0;
    id++;
    return id;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
*\brief Busca el indice libre en un array
*\param array Es el array que reciba para recorrer
*\param size Es el tamaño del array
*\return Retorna el indice del lugar libre si no retorna -1
*/

int employee_buscarIndiceLibre(Employee array[],int size)
{
    int retorno = -1;
    int i;

    for(i=0;i < size; i++)
    {
        if(array[i].isEmpty)
        {
            retorno = i;
            break;
        }
    }
    return retorno;
}

/**
*\brief Inicializa todos los elementos de un array con un valor de vacio
*\param array Es el array que reciba para recorrer
*\param size Es el tamaño del array
*\param valor Es el valor con el cual cargara el campo de estado
*\return Retorna 0 si no retorna -1
*/

int employee_init(Employee array[],int size,int valor)
{
    int i;
    int retorno = -1;
    if(array != NULL && size > 0 && valor >= 0)
    {
        retorno = 0;
        for(i=0;i < size; i++)
        {
        array[i].isEmpty = valor;
        }

    }
    return retorno;
}

/**
*\brief Busca un elemento por ID dentro de un array de estructuras
*\param array Es el array que reciba para recorrer
*\param size Es el tamaño del array
*\param id Es el ID que recibe para buscar
*\return Retorna el puntero del elemento si no retorna NULL
*/

Employee* employee_getByID(Employee array[],int size,int id)
{
    Employee* retorno = NULL;
    int i;

    if(array != NULL && size > 0)
    {
        for(i=0;i<size;i++)
        {
           if(!array[i].isEmpty && array[i].id == id)
            {
            retorno = array+i;
            break;
            }
        }
    }
    return retorno;
}

/**
*\brief Realiza el alta de un elemento del array
*\param array Es el array que reciba para recorrer
*\param size Es el tamaño del array
*\return Retorna 0 si no retorna -1
*/

int employee_alta(Employee array[],int size)
{
    char auxName[100];
    char auxLastName[100];
    int auxSector;
    float auxSalary;
    int retorno = -1;
    int indice;

    indice = employee_buscarIndiceLibre(array,size);

    if( !input_getLetras(auxName,50,"\nIngrese nombre: ","\nError,dato invalido.",2)&&
        !input_getLetras(auxLastName,50,"\nIngrese apellido: ","\nError,dato invalido.",2)&&
        !input_getNumeros(&auxSector,3,"\nIngrese numero del sector: ","\nError,dato invalido.",1,10,2)&&
        !input_getFloat(&auxSalary,7,"\nIngrese el salario: ","\nError,dato invalido.",1000,100000,2))
    {
        strncpy(array[indice].name,auxName,50);
        strncpy(array[indice].lastName,auxLastName,50);
        array[indice].sector = auxSector;
        array[indice].salary = auxSalary;
        array[indice].isEmpty = 0;
        array[indice].id = generateID();//SE PASA ID ASIGNADO A LA ESTRUCTURA
        retorno = 0;
    }

    return retorno;
}

/**
*\brief Modifica los campos de un elemento del array
*\param array Es el puntero que recibe del elemento del array
*\param size Es el tamaño del array
*\return Retorna 0 si no retorna -1
*/

int employee_modificar(Employee* array,int size)
{
    char auxName[100];
    char auxLastName[100];
    int auxSector;
    float auxSalary;
    int opcion = 0;
    int retorno = -1;

    if(array != NULL && array->isEmpty == 0)
    {

        input_ScanInt("\n--Ingrese opcion--\n1) Nombre \n2) Apellido \n3) Sector\n4) Salario\n\n--> ",&opcion);

        switch(opcion)
        {
            case 1 :
                if(!input_getLetras(auxName,50,"\nIngrese nombre: ","\nError,dato invalido.",2))
                {
                    strncpy(array->name,auxName,50);
                }
            break;
            case 2 :
                if(!input_getLetras(auxLastName,50,"\nIngrese apellido: ","\nError,dato invalido.",2))
                {
                    strncpy(array->lastName,auxLastName,50);
                }
            break;
            case 3 :
                if(!input_getNumeros(&auxSector,3,"\nIngrese sector: ","\nError,dato invalido.",1,10,2))
                {
                    array->sector = auxSector;
                }
            break;
            case 4 :
                if(!input_getFloat(&auxSalary,6,"\nIngrese el salario: ","\nError,dato invalido.",10000,100000,2))
                {
                    array->salary = auxSalary;
                }
            break;
        }
    }
    else
    {
        printf("\nCasillero vacio");
    }

    return retorno;
}

/**
*\brief Modifica los campos de un elemento del array
*\param array Es el puntero que recibe del elemento del array
*\param size Es el tamaño del array
*\return Retorna 0 si no retorna -1
*/

int employee_eliminar(Employee* array,int size)
{
    int retorno = -1;

    if(array != NULL)
    {
            array->isEmpty = 1;
            retorno = 0;
    }
    else
    {
        printf("\nCasillero vacio");
    }
    return retorno;
}

/**
*\brief Ordena todos los elementos de un array
*\param array Es el array que recibe para ordenar
*\param size Es el tamaño del array
*\param orden Es el numero que indica ordenar de forma ascendente o descendente
*\return Retorna 0 si no retorna -1
*/

int employee_sortName(Employee array[],int size,int orden)
{
    int retorno = -1;
    int i;
    int j;

    if(array != NULL && size > 0)
    {

        if(orden == 1)
        {
            retorno = 0;

            for(i=0;i<size;i++)
            {
                for(j=i+1;j<size;j++)
                {
                    if(array[i].sector == array[j].sector && strcmp(array[i].lastName,array[j].lastName) > 0)
                    {
                        swap(array+i,array+j);
                    }
                }
            }
        }
        else if(orden == 0)
        {
            retorno = 0;

            for(i=0;i<size;i++)
            {
                for(j=i+1;j<size;j++)
                {
                    if(array[i].sector == array[j].sector && strcmp(array[i].lastName,array[j].lastName) < 0)
                    {
                        swap(array+i,array+j);
                    }
                }
            }
        }


    }
    return retorno;
}

int employee_sortSector(Employee array[],int size,int orden)
{
    int retorno = -1;
    int i;
    int j;

    if(array != NULL && size > 0)
    {

        if(orden == 1)
        {
            retorno = 0;

            for(i=0;i<size;i++)
            {
                for(j=i+1;j<size;j++)
                {
                    if(array[i].sector > array[j].sector)
                    {
                        swap(array+i,array+j);
                    }
                }
            }
        }
        else if(orden == 0)
        {
            retorno = 0;

            for(i=0;i<size;i++)
            {
                for(j=i+1;j<size;j++)
                {
                    if(array[i].sector < array[j].sector)
                    {
                        swap(array+i,array+j);
                    }
                }
            }
        }


    }
    return retorno;


}

/**
*\brief Muestra los datos de un elemento del array
*\param array Es el puntero que recibe del elemento del array
*\param size Es el tamaño del array
*\return Retorna 0 si no retorna -1
*/

int employee_mostrar(Employee* array,int size)
{
    int retorno = -1;

    if(array != NULL && size > 0 )
    {
        printf("\n\nNOMBRE -- %s %s",array->name,array->lastName);
        printf("\nSECTOR -- %d",array->sector);
        printf("\nSALARIO -- $%.2f",array->salary);

        retorno = 0;
    }
    return retorno;
}

/**
*\brief Lista los datos de todos los elementos del array
*\param array Es el array que recibe para recorrer
*\param size Es el tamaño del array
*\return Retorna 0 si no retorna -1
*/

int employee_listar(Employee array[],int size)
{
    int retorno = -1;
    int i;

    if(array != NULL && size > 0)
    {
        for(i=0;i<size;i++)
        {
            if(!array[i].isEmpty)
            {
                printf("\n\nNOMBRE -- %s %s",array[i].name,array[i].lastName);
                printf("\nSECTOR -- %d",array[i].sector);
                printf("\nSALARIO -- $%.2f",array[i].salary);
                printf("\nID -- %d",array[i].id);

                retorno = 0;
            }
        }
    }
    return retorno;
}

/**
*\brief Carga todos los campos de un elemento de un array
*\param array Es el array que recibe para cargar
*\param size Es el tamaño del array
*\param name Es el valor del campo name
*\param lastName Es el valor del campo lastName
*\param sector Es el valor del campo sector
*\param salary Es el valor del campo salary
*\return Retorna 0 si no retorna -1
*/


int employee_ingresoForzado(Employee array[],int size,char name[],char lastName[],int sector,float salary)
{
    int retorno = -1;
    int indice;

    if(array != NULL && size > 0)
    {
        retorno = 0;
        indice = employee_buscarIndiceLibre(array,size);
        strncpy(array[indice].name,name,100);
        strncpy(array[indice].lastName,lastName,100);
        array[indice].sector=sector;
        array[indice].salary=salary;
        array[indice].id=generateID();
        array[indice].isEmpty=0;
    }

    return retorno;
}

/**
*\brief Construye un menu de ABM con las variables a utilizar
*\param array Es el array que recibe para trabajar
*\param size Es el tamaño del array
*\return Retorna 0 si no retorna -1
*/

int employe_menu(Employee array[],int size)
{
    int retorno = -1;
    int i;
    int opcion;
    float totalSalario;
    float promedioSalario;
    int contadorEmpleadosSalario = 0;
    int contadorEmpleados = 0;
    int flag = 0;
    int idIngresado;
    Employee* empleadoSeleccionado;

    employee_init(array,size,1);

   do
   {
       limpiarPantalla();
       printf("\n<<<MENU>>>\n\n1) ALTA\n2) MODIFICAR\n3) BAJA\n4) INFORMES\n5) SALIR\n");
       input_ScanInt("\nIngrese opcion: ",&opcion);

       switch(opcion)
       {
            case 1 :
                printf("\n--ALTA--\n");
                if(employee_buscarIndiceLibre(array,size) >= 0)
                {
                    employee_alta(array,size);
                    contadorEmpleados++;
                    flag = 1;
                }
                else
                {
                    printf("\nNo hay espacios libres.");
                    printf("\nIngrese cualquier tecla para continuar...");
                    limpiarMemoria();
                    getchar();
                }
            break;

            case 2 :
                if(flag == 1 && contadorEmpleados >0)
                {
                    printf("\n--MODIFICAR--\n");
                    employee_listar(array,size);
                    input_ScanInt("\nIngrese ID de empleado: ",&idIngresado);
                    empleadoSeleccionado = employee_getByID(array,size,idIngresado);
                    employee_modificar(empleadoSeleccionado,size);
                }
                else
                {
                    printf("\nNo hay datos cargados.");
                    printf("\nIngrese cualquier tecla para continuar...");
                    limpiarMemoria();
                    getchar();
                }

            break;

            case 3 :
                if(flag == 1 && contadorEmpleados >0)
                {
                    printf("\n--BAJA--\n");
                    employee_listar(array,size);
                    input_ScanInt("\nIngrese ID de empleado: ",&idIngresado);
                    empleadoSeleccionado = employee_getByID(array,size,idIngresado);
                    employee_eliminar(empleadoSeleccionado,size);
                    contadorEmpleados--;
                }
                else
                {
                    printf("\nNo hay datos cargados.");
                    printf("\nIngrese cualquier tecla para continuar...");
                    limpiarMemoria();
                    getchar();
                }

            break;

            case 4 :
                if(flag == 1 && contadorEmpleados >0)
                {
                    totalSalario = 0;
                    promedioSalario = 0;
                    contadorEmpleadosSalario = 0;

                    printf("\n--INFORMES--");
                    employee_sortSector(array,size,1);
                    employee_sortName(array,size,1);
                    employee_listar(array,size);

                    for(i=0;i<size;i++)
                    {
                        if(!array[i].isEmpty)
                        {
                            totalSalario = totalSalario + array[i].salary;
                        }
                    }

                    promedioSalario = totalSalario / contadorEmpleados;

                    for(i=0;i<size;i++)
                    {
                        if(array[i].salary > promedioSalario && !array[i].isEmpty)
                        {
                            contadorEmpleadosSalario++;
                        }
                    }

                    printf("\nEl total de salarios es %.2f",totalSalario);
                    printf("\nEl promedio de salarios es %.2f",promedioSalario);
                    printf("\nEl total de empleados que superan el promedio es %d",contadorEmpleadosSalario);
                    limpiarMemoria();
                    printf("\nIngrese cualquier tecla para continuar...");
                    getchar();
                 }
                else
                {
                    printf("\nNo hay datos cargados.");
                    printf("\nIngrese cualquier tecla para continuar...");
                    limpiarMemoria();
                    getchar();
                }
                break;
            case 5 :
                {
                    printf("\nVuelvas prontos...:)");
                    limpiarMemoria();
                    getchar();
                }
                break;

            default :
                printf("\nOpcion invalida.:P");
                printf("\nIngrese cualquier tecla para continuar...");
                limpiarMemoria();
                getchar();


        }
        retorno = 0;
   }while(opcion != 5);

        return retorno;

}
