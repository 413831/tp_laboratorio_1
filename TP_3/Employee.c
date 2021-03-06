#include "Employee.h"
#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"

#define BUFFER 4000

/////////////////////////////////////////////////STATIC/////////////////////////////////////////////////////////////////////

/**
*\brief Valida un nombre del elemento
*\param name Es el string a validar
*\return Retorna 1 si es correcto sino retorna 0
*/
static int isValidName(char* name)
{
    int retorno = 0;

    if(name != NULL && validacion_Letras(name,strlen(name)))
    {
        retorno = 1;
    }
    return retorno;
}

/**
*\brief Valida horas trabajadas del elemento
*\param horas Es el string a validar
*\return Retorna 1 si es correcto sino retorna 0
*/
static int isValidHoras(char* horas)
{
    int retorno = 0;
    int digitosIngresados = strlen(horas);

    if(horas != NULL && validacion_Int(horas,digitosIngresados) && atoi(horas) > 0)
    {
        retorno = 1;
    }
    return retorno;
}

/**
*\brief Valida sueldo del elemento
*\param sueldo Es el string a validar
*\return Retorna 1 si es correcto sino retorna 0
*/
static int isValidSueldo(char* sueldo)
{
    int retorno = 0;
    int digitosIngresados = strlen(sueldo);

    if(sueldo != NULL && validacion_Int(sueldo,digitosIngresados) && atoi(sueldo) > 0)
    {
        retorno = 1;
    }
    return retorno;
}


/**
*\brief Valida ID del elemento
*\param id Es el string a validar
*\return Retorna 1 si es correcto sino retorna 0
*/
static int isValidId(char* id)
{
    int retorno = 0;
    int digitosIngresados = strlen(id);

    if(id != NULL && validacion_Int(id,digitosIngresados))
    {
        retorno = 1;
    }
    return retorno;
}

///////////////////////////////////////////////////PUBLIC/////////////////////////////////////////////////////////////////

/**
*\brief Reserva espacio en memoria para un elemento
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
*\brief Es el constructor del elemento donde se reserva memoria y se setean los campos
*\param id Es el dato id para setear en el campo del elemento
*\param nombre Es el dato nombre para setear en el campo del elemento
*\param horasTrabajadas Es el dato horasTrabajadas para setear en el campo del elemento
*\param sueldo Es el dato sueldo para setear en el campo del elemento
*\return Retorna 0 si logra agregar elemento sino retorna -1
*/
Employee* employee_newConParametros(char* id,char* nombre,char* horasTrabajadas,char* sueldo)
{
    Employee* this;
    this=employee_new();

    if(isValidId(id) &&
       isValidName(nombre) &&
       isValidHoras(horasTrabajadas) &&
       isValidSueldo(sueldo) &&
       !employee_setAll(this,id,nombre,horasTrabajadas,sueldo))
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
*\brief Se recorre array para encontrar elemento por ID
*\param pArrayListEmployee Es el array para recorrer
*\param idIngresado Es ID para encontrar
*\return Retorna el elemento sino retorna NULL
*/
Employee* employee_getById(void* pArrayListEmployee,int idIngresado)
{
    Employee* retorno = NULL;
    int index;
    Employee* auxEmployee;
    int auxID = 0;

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
*\brief Se realiza el alta de un elemento desde consola
*\param pArrayListEmployee Es el array para ingresar elemento
*\return Retorna 0 si logra agregar elemento sino retorna -1
*/
int employee_add(void* pArrayListEmployee)
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
*\brief Se da de baja un elemento seteando el ID en valor especifico
*\param pArray Es el array para recorrer
*\return Retorna 0 si existe el ID sino retorna -1
*/
int employee_remove(void* pArrayListEmployee)
{
    Employee* this = NULL;
    int retorno = -1;
    char bufferId[BUFFER];
    char option[2];
    int index;

    if(!input("ID",bufferId,BUFFER,isValidId))
    {
        this = employee_getById(pArrayListEmployee,atoi(bufferId));
        if(this != NULL)
        {
            employee_show(this);
            input_getLetras(option,2,"\nATENCION!\nDesea eliminar datos de empleado? S/N\n","\nError.Dato invalido",2);
            if(!strcasecmp("s",option))
            {
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
*\brief Libera espacio en memoria ocupado por un elemento
*\param this Es el elemento
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
*\brief Se busca elemento por ID a modificar con opciones de campos
*\param pArrayListEmployee Es el array a recorrer
*\return Retorna 0 si logra modificar campo sino retorna -1
*/
int employee_edit(void* pArrayListEmployee)
{
    int retorno = -1;
    int option;
    char bufferId[BUFFER];
    Employee* this = NULL;

    if(pArrayListEmployee != NULL && !input("ID",bufferId,BUFFER,isValidId))
    {
        this = employee_getById(pArrayListEmployee,atoi(bufferId));
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
*\brief Se muestran los datos de todos los campos del elemento
*\param this Es el puntero al elemento
*\return Retorna 0 si el elemento es diferente a NULL sino retorna -1
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

/**
*\brief Funcion para ordenar el LinkedList segun criterio y orden
*\param pArrayListEmployee Es la LinkedList para ordenar
*\return Retorna 0 si logra ordenar sino retorna -1
*/
int employee_sort(void* pArrayListEmployee)
{
    int retorno = -1;
    function_type criterio;
    int orden;

    limpiarPantalla();
    if(pArrayListEmployee != NULL)
    {
        printf("\n<ORDENAR>");
        criterio = employee_selectorCriterio();
        if(criterio != NULL)
        {
            input_getEnteros(&orden,"\n-Seleccione orden\n Descendente (0)\n Ascendente (1)","Error.",2);
            if(orden == 0 || orden == 1)
            {
                ll_sort(pArrayListEmployee,criterio,orden);
                retorno = 0;
            }
        }
    }
    return retorno;
}

/**
*\brief Se realiza un alta forzada
*\param pArrayListEmployee Es la LinkedList para realizar el alta
*\param bufferName Es el nombre a cargar en el elemento
*\param bufferHorasTrabajadas Es la cantidad de horas trabajadas para cargar en el elemento
*\param bufferSueldo Es el sueldo para cargar en el elemento
*\return Retorna 0 si el array es diferente a NULL sino retorna -1
*/
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

/////////////////////////////////////////////SETTERS & GETTERS///////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////SORT CRITERIOS/////////////////////////////////////////////////////////////////

/**
*\brief Funcion selector de criterio para ordenar
*\return Retorna puntero a funcion segun criterio seleccionado si no es correcto retorna NULL
*/
void* employee_selectorCriterio()
{
    int opcion;

    void* retorno = NULL;
    input_getEnteros(&opcion,"\nSeleccione opcion\n1) Nombre\n2) Sueldo\n3) Horas\n4) ID\n","\nOpcion incorrecta",2);

    switch(opcion)
    {
        case 1 :
            printf("\nOrdenar por nombre");
            retorno = employee_criterioNombre;
            break;
        case 2 :
            printf("\nOrdenar por sueldo");
            retorno = employee_criterioSueldo;
            break;
        case 3 :
            printf("\nOrdenar por horas trabajadas");
            retorno = employee_criterioHoras;
            break;
        case 4 :
            printf("\nOrdenar por ID");
            retorno = employee_criterioId;
            break;
        default :
            printf("\nOpcion incorrecta");
    }
    return retorno;
}

/**
*\brief Funcion criterio por campo nombre
*\param thisA Es el primer elemento
*\param thisB Es el segundo elemento
*\return Retorna 1 si el campo del primer elemento es mayor al segundo,
*\       retorna -1 si el campo del primer elemento es menor al segundo,
*\       retorno 0 si son iguales,
*/
int employee_criterioNombre(void* thisA,void* thisB)
{
    int retorno = 0;
    char bufferStrA[BUFFER];
    char bufferStrB[BUFFER];

    employee_getNombre(((Employee*)thisA),bufferStrA);
    employee_getNombre(((Employee*)thisB),bufferStrB);

    printf("\nOrdenando.");
    if(strcmp(bufferStrA,bufferStrB) > 0)
    {
        printf("\nOrdenando..");
        retorno = 1;
    }
    else if(strcmp(bufferStrA,bufferStrB) < 0)
    {
        printf("\nOrdenando...");
        retorno = -1;
    }
    printf("\nOrdenando....");
    return retorno;
}

/**
*\brief Funcion criterio por campo sueldo
*\param thisA Es el primer elemento
*\param thisB Es el segundo elemento
*\return Retorna 1 si el campo del primer elemento es mayor al segundo,
*\       retorna -1 si el campo del primer elemento es menor al segundo,
*\       retorno 0 si son iguales,
*/
int employee_criterioSueldo(void* thisA,void* thisB)
{
    int retorno = 0;
    float sueldoA = 0;
    float sueldoB = 0;

    employee_getSueldo(((Employee*)thisA),&sueldoA);
    employee_getSueldo(((Employee*)thisB),&sueldoB);

    if(sueldoA > sueldoB)
    {
        printf("\nOrdenando.");
        retorno = 1;
    }
    else if(sueldoA < sueldoB)
    {
        printf("\nOrdenando..");
        retorno = -1;
    }
    printf("\nOrdenando...");
    return retorno;
}

/**
*\brief Funcion criterio por campo horas
*\param thisA Es el primer elemento
*\param thisB Es el segundo elemento
*\return Retorna 1 si el campo del primer elemento es mayor al segundo,
*\       retorna -1 si el campo del primer elemento es menor al segundo,
*\       retorno 0 si son iguales,
*/
int employee_criterioHoras(void* thisA,void* thisB)
{
    int retorno = 0;
    int horasA = 0;
    int horasB = 0;

    employee_getHorasTrabajadas(((Employee*)thisA),&horasA);
    employee_getHorasTrabajadas(((Employee*)thisB),&horasB);

    if(horasA > horasB)
    {
        printf("\nOrdenando.");
        retorno = 1;
    }
    else if(horasA < horasB)
    {
        printf("\nOrdenando..");
        retorno = -1;
    }
    printf("\nOrdenando...");
    return retorno;
}

/**
*\brief Funcion criterio por campo ID
*\param thisA Es el primer elemento
*\param thisB Es el segundo elemento
*\return Retorna 1 si el campo del primer elemento es mayor al segundo,
*\       retorna -1 si el campo del primer elemento es menor al segundo,
*\       retorno 0 si son iguales,
*/
int employee_criterioId(void* thisA,void* thisB)
{
    int retorno = 0;
    int idA = 0;
    int idB = 0;

    employee_getId(((Employee*)thisA),&idA);
    employee_getId(((Employee*)thisB),&idB);

    if(idA > idB)
    {
        printf("\nOrdenando.");
        retorno = 1;
    }
    else if(idA < idB)
    {
        printf("\nOrdenando..");
        retorno = -1;
    }
    printf("\nOrdenando...");
    return retorno;
}
