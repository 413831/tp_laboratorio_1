#include "Employee.h"
#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"

#define BUFFER 4000
//El elemento.c es el manager de datos que trabaja directamente con los mismos es el "CÓMO"

static int isValidName(char* name)
{
    int retorno = 0;

    if(name != NULL && validacion_Letras(name,strlen(name)))
    {
        retorno = 1;
    }
    return retorno;
}

static int isValidHoras(char* horas)
{
    int retorno = 0;
    int digitosIngresados = strlen(horas);

    if(horas != NULL && validacion_Int(horas,digitosIngresados))
    {
        retorno = 1;
    }
    return retorno;
}

static int isValidSueldo(char* sueldo)
{
    int retorno = 0;
    int digitosIngresados = strlen(sueldo);

    if(sueldo != NULL && validacion_Int(sueldo,digitosIngresados))
    {
        retorno = 1;
    }
    return retorno;
}

static int isValidId(char* id)//CORREGIR
{
    int retorno = 0;
    int digitosIngresados = strlen(id);

    if(id != NULL && validacion_Int(id,digitosIngresados) )
    {
        retorno = 1;
    }
    return retorno;
}

static int getNextId(LinkedList* pArrayListEmployee)////////VALIDAR ID INICIAL CONTRA ARCHIVO
{
    int retorno=-1;
    int index;
    Employee* auxEmployee;
    int auxID;

    if(pArrayListEmployee != NULL)
    {
        for(index=0;index<ll_len(pArrayListEmployee);index++)//Recorro todo el array hasta el LEN
        {
            auxEmployee = ll_get(pArrayListEmployee,index);//Obtengo el elemento del array en posicion index
            employee_getId(auxEmployee,&auxID);//Obtengo el ID del elemento
        }
        retorno = auxID+1;//Retorno el ID del ultimo elemento más uno
    }
    return retorno;
}

//////////////////////////////////////////////////////////////////////////////////////////

/**
*\brief Reservar espacio en memoria para un elemento
*\param void
*\return Retorna el elemento si reserva memoria sino NULL
*/
Employee* employee_new()
{
    Employee* this;
    this=malloc(sizeof(Employee));
    if(this != NULL)
    {
      return this;
    }
    else
    {
        return NULL;
    }
}

/**
*\brief Se realiza el alta de un elemento desde consola
*\param pArrayListEmployee Es el array para ingresar elemento
*\return Retorna 0 si logra agregar elemento sino retorna -1
*/
int employee_EmployeeFromUser(void* pArrayListEmployee)
{
    Employee* this = NULL;
    int retorno = -1;

    char bufferName[BUFFER];
    char bufferHorasTrabajadas[BUFFER];
    char bufferSueldo[BUFFER];

    if( !input("nombre",bufferName,BUFFER,isValidName) &&
        !input("horas trabajadas",bufferHorasTrabajadas,BUFFER,isValidHoras) &&
        !input("sueldo",bufferSueldo,BUFFER,isValidSueldo))
    {
        this = employee_newConParametros("0",bufferName,bufferHorasTrabajadas,bufferSueldo);
        if(this != NULL)
        {
            employee_show(this);
            ll_add(pArrayListEmployee,this);
            retorno = 0;;
        }
    }
    return retorno;
}

/**
*\brief Se realiza el alta de un elemento desde consola
*\param pArrayListEmployee Es el array para ingresar elemento
*\return Retorna 0 si logra agregar elemento sino retorna -1
*/
Employee* employee_newConParametros(char* id,char* nombre,char* horasTrabajadas,char* sueldo)
{
    Employee* this;
    this=employee_new();

    if(!employee_setAll(this,id,nombre,horasTrabajadas,sueldo))
    {

        return this;
    }
    else
    {
        employee_delete(this);
        return NULL;
    }
}


/**
*\brief Libera espacio en memoria ocupado por elemento
*\param tihs Es el elemento
*\return Retorna 0 si logra liberar sino retorna -1
*/
int employee_delete(Employee* this)
{
    int retorno = -1;
    if(this != NULL)
    {
        free(this);
        retorno = 0;
    }
    return retorno;
}

/**
*\brief Se recorre array para encontrar elemento por ID
*\param pArray Es el array para recorrer
*\param idIngresado Es ID para encontrar
*\return Retorna el elemento sino retorna NULL
*/
Employee* employee_getById(LinkedList* pArrayListEmployee,int idIngresado)
{
    Employee* retorno = NULL;
    int index;
    Employee* auxEmployee;
    int auxID;

    if(pArrayListEmployee != NULL)
    {
        for(index=0;index<ll_len(pArrayListEmployee);index++)//Recorro todo el array hasta el LEN
        {
            auxEmployee = ll_get(pArrayListEmployee,index);//Obtengo el elemento del array en posicion index
            employee_getId(auxEmployee,&auxID);//Obtengo el ID del elemento
            if(auxID == idIngresado)
            {
                retorno = auxEmployee;
                break;
            }
        }
    }
    return retorno;
}

/**
*\brief Setea todos los campos del elemento
*\param this Es el elemento
*\param name Es el dato para setear el campo nombre
*\param hours Es el dato para setear el campo horas trabajadas
*\param salary Es el dato para setear el campo salario
*\return Retorna 0 si existe el elemento sino retorna -1
*/
int employee_setAll(Employee* this,char* id,char* name,char* hours,char* salary)
{
    int retorno = -1;

    if(this != NULL)
    {
        if( !employee_setId(this,id) &&
            !employee_setNombre(this,name) &&
            !employee_setHorasTrabajadas(this,hours) &&
            !employee_setSueldo(this,salary))
        {
            retorno = 0;
        }
    }
    return retorno;
}

/**
*\brief Obtiene todos los campos del elemento
*\param this Es el elemento
*\param name Es el dato para obtener el campo nombre
*\param hours Es el dato para obtener el campo horas trabajadas
*\param salary Es el dato para obtener el campo salario
*\return Retorna 0 si existe el elemento sino retorna -1
*/
int employee_getAll(Employee* this,char* name,int* hours,float* salary,int* id)
{
    int retorno = -1;

    if(this != NULL)
    {
        employee_getNombre(this,name);
        employee_getHorasTrabajadas(this,hours);
        employee_getSueldo(this,salary);
        employee_getId(this,id);
        retorno = 0;
    }
    return retorno;
}

/**
*\brief Se da de baja un elemento seteando el ID en valor especifico
*\param pArray Es el array para recorrer
*\return Retorna 0 si existe el ID sino retorna -1
*/
int employee_remove(void* pArrayListEmployee,Employee* arrayDismissed[])
{
    Employee* this = NULL;
    int retorno = -1;
    char bufferId[BUFFER];
    int idIngresado;
    char option[2];
    int index;

   if(!input("ID",bufferId,BUFFER,isValidId))
    {
        idIngresado = atoi(bufferId);
        this = employee_getById(pArrayListEmployee,idIngresado);
        if(this != NULL)
        {
            employee_show(this);
            input_getLetras(option,2,"\nDesea dar de baja? S/N","\nError.Dato invalido",2);
            if(!strcasecmp("s",option))
            {
                index = employee_searchEmpty(arrayDismissed);
                arrayDismissed[index] = this;//Se copia empleado de baja en listado
                index = ll_indexOf(pArrayListEmployee,this);
                ll_pop(pArrayListEmployee,index);

                retorno = 0;
            }
        }
        else
        {
            printf("\nEl ID ingresado no existe");
        }
    }
    return retorno;
}

/**
*\brief Se modifica un campo del elemento
*\param this Es el elemento a modificar
*\param validacion Es el puntero a la funcion de validacion
*\param set Es el puntero a la funcion set del campo
*\return Retorna 0 si logra modificar campo sino retorna -1
*/
int employee_modify(Employee* this,
                        char* mensaje,
                        int (*validacion)(char*),
                        int (*set)(Employee*,char*))//HACER MAS GENERICA MODIFICAR CUALQUIER CAMPO
{
    int retorno = -1;
    char option[2];
    char buffer[BUFFER];

    if(this != NULL && mensaje != NULL && validacion != NULL && set != NULL)
    {
        input(mensaje,buffer,BUFFER,(*validacion));
        input_getLetras(option,2,"\nDesea modificar dato? S/N\n","\nError.Dato invalido",2);
        if(buffer != NULL && !strcasecmp("s",option))
        {
            (*set)(this,buffer);
            employee_show(this);
            retorno = 0;
        }
    }
    else
    {
        printf("\nError");
    }
    return retorno;
}

/**
*\brief Se busca elemento a modificar + menu de campos
*\param pArrayListEmployee Es el array a recorrer
*\return Retorna 0 si logra modificar campo sino retorna -1
*/
int employee_edit(void* pArrayListEmployee)
{
    int retorno = -1;
    int option;
    char bufferId[BUFFER];
    int idIngresado;;
    Employee* this = NULL;

    if(pArrayListEmployee != NULL && !input("ID",bufferId,BUFFER,isValidId))
    {
        idIngresado = atoi(bufferId);
        this = employee_getById(pArrayListEmployee,idIngresado);
        if(this != NULL)
        {
             employee_show(this);
            do
            {

                printf("\n1) Nombre\n2) Sueldo\n3) Horas trabajadas\n4) Volver");
                input_getEnteros(&option,"\nIngrese opcion: ","\nError.Dato invalido",2);
                switch(option)
                {
                    retorno = 0;
                    case 1 :
                        employee_modify(this,"nombre",isValidName,employee_setNombre);
                        break;
                    case 2 :
                        employee_modify(this,"sueldo",isValidSueldo,employee_setSueldo);
                        break;
                    case 3 :
                        employee_modify(this,"horas trabajadas",isValidHoras,employee_setHorasTrabajadas);
                        break;
                    case 4 :
                        break;
                    default :
                        printf("\nOpcion invalida");
                }
            }while(option != 4);
        }
        else
        {
            printf("\nID no encontrado");
        }
    }
    return retorno;
}

/**
*\brief Se setea el ID del elemento
*\param this Es el elemento
*\param id Es el ID para setear
*\return Retorna 0 si setea sino -1
*/
int employee_setId(Employee* this,char* id)
{
    int retorno=-1;
    static int proximoId=0;
    int auxId = atoi(id);

    if(this!=NULL && auxId==0)//Se carga primer ID y en el ALTA
    {
        proximoId++;
        this->id=proximoId;
        retorno=0;
    }
    else if(this!=NULL && auxId>proximoId)//Se comparan los ID al cargar del archivo
    {
        proximoId=auxId;
        this->id=proximoId;
        retorno=0;
    }
    return retorno;
}

/**
*\brief Se obtiene el ID del elemento
*\param this Es el elemento
*\param id Es el ID que se obtiene
*\return Retorna 0 si obtiene sino retorna -1
*/
int employee_getId(Employee* this,int* id)
{
    int retorno=-1;
    if(this!=NULL)
    {
        *id=this->id;
        retorno=0;
    }
    return retorno;
}

/**
*\brief Se setea el nombre del elemento
*\param this Es el elemento
*\param nombre Es el nombre para setear
*\return Retorna 0 si setea elemento sino retorna -1
*/
int employee_setNombre(Employee* this,char* nombre)
{
    int retorno=-1;
    if(this!=NULL && nombre!=NULL && isValidName(nombre))
    {
        strcpy(this->nombre,nombre);
        retorno=0;
    }
    return retorno;
}

/**
*\brief Se obtiene el nombre del elemento
*\param this Es el elemento
*\param nombre Es el nombre que se obtiene
*\return Retorna 0 si obtiene elemento sino retorna -1
*/
int employee_getNombre(Employee* this,char* nombre)
{
    int retorno=-1;
    if(this!=NULL && nombre!=NULL)
    {
        strcpy(nombre,this->nombre);
        retorno=0;
    }
    return retorno;
}

/**
*\brief Se setea las horas trabajadas del elemento
*\param this Es el elemento
*\param horasTrabajadas Es la cantidad de horas para setear
*\return Retorna 0 si setea elemento sino retorna -1
*/
int employee_setHorasTrabajadas(Employee* this,char* horasTrabajadas)
{
    int retorno=-1;
    int auxHorasTrabajadas;

    if(this!=NULL && isValidHoras(horasTrabajadas))
    {
        auxHorasTrabajadas = atoi(horasTrabajadas);
        this->horasTrabajadas = auxHorasTrabajadas;
        retorno=0;
    }
    return retorno;
}

/**
*\brief Se obtienen las horas trabajadas del elemento
*\param this Es el elemento
*\param horasTrabajadas Es la cantidad de horas que se obtiene
*\return Retorna 0 si setea elemento sino retorna -1
*/
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
    int retorno=-1;
    if(this!=NULL)
    {
        *horasTrabajadas=this->horasTrabajadas;
        retorno=0;
    }
    return retorno;
}

/**
*\brief Se setea el sueldo del elemento
*\param this Es el elemento
*\param sueldo Es el sueldo para setear
*\return Retorna 0 si setea elemento sino retorna -1
*/
int employee_setSueldo(Employee* this,char* sueldo)
{
    int retorno=-1;
    float auxSueldo;

    if(this!=NULL && isValidSueldo(sueldo))
    {
        auxSueldo = atof(sueldo);
        this->sueldo=auxSueldo;
        retorno=0;
    }
    return retorno;
}

/**
*\brief Se obtiene el sueldo del elemento
*\param this Es el elemento
*\param sueldo Es el sueldo que se obtiene
*\return Retorna 0 si setea elemento sino retorna -1
*/
int employee_getSueldo(Employee* this,float* sueldo)
{
    int retorno=-1;
    if(this!=NULL)
    {
        *sueldo=this->sueldo;
        retorno=0;
    }
    return retorno;
}

/**
*\brief Se buscan empleados inhabilitados
*\param array Es el array de empleados para recorrer
*\param size Es el tamaño del array
*\return Retorna el indice del elemento sino retorna -1
*/
int employee_searchEmpty(Employee* array[])
{
    int i=0;
    int retorno =-1;
    if(array!=NULL)
    {
        do
        {
           if(array[i]==NULL)
            {
                retorno=i;
                break;
            }
            i++;
        }while(array[i]!=NULL);
    }
    return retorno;
}

/**
*\brief Base de funcion criterio para comparar campos de dos elementos
*\param thisA Es el primer elemento
*\param thisB Es el segundo elemento
*\return Retorna 1 si el primer elemento es mayor al segundo,
*\       retorna -1 si el, sino retorna 0
*/
int employee_sort(void* thisA,void* thisB)
{
    int retorno = 0;
    char nombreEmployeeA[50];
    char nombreEmployeeB[50];
    employee_getNombre(thisA,nombreEmployeeA);
    employee_getNombre(thisB,nombreEmployeeB);

    if(strcmp(nombreEmployeeA,nombreEmployeeB) > 0 )
    {
        retorno = 1;
    }
    else if(strcmp(nombreEmployeeA,nombreEmployeeB) < 0)
    {
        retorno = -1;
    }
    return retorno;
}

/**
*\brief Base de funcion criterio para comparar campos de dos elementos
*\param thisA Es el primer elemento
*\param thisB Es el segundo elemento
*\return Retorna 1 si el primer elemento es mayor al segundo,
*\       retorna -1 si el, sino retorna 0
*/
int employee_show(Employee* this)
{
    int retorno = -1;
    int auxId;
    char auxNombre[128];
    int auxHorasTrabajadas;
    float auxSueldo;

    if(this != NULL)
    {
        employee_getId(this,&auxId);
        if(auxId != -1)
        {
            employee_getNombre(this,auxNombre);
            employee_getSueldo(this,&auxSueldo);
            employee_getHorasTrabajadas(this,&auxHorasTrabajadas);
            employee_getId(this,&auxId);

            printf("\nID -- %d",auxId);
            printf(" / Nombre -- %s",auxNombre);
            printf(" / Sueldo -- $%.2f",auxSueldo);
            printf(" / Horas trabajadas -- %dhs",auxHorasTrabajadas);
            retorno = 0;
        }
    }
    return retorno;
}

int employee_hardcode(void* pArrayListEmployee,char *bufferName,char* bufferHorasTrabajadas,char* bufferSueldo)
{
    Employee* this = NULL;
    int retorno = -1;

    this = employee_newConParametros("0",bufferName,bufferHorasTrabajadas,bufferSueldo);

    if(this != NULL)
    {
        employee_show(this);
        ll_add(pArrayListEmployee,this);
        retorno = 0;;
    }

    return retorno;
}
