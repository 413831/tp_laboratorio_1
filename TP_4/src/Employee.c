#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/Employee.h"
#include "../inc/LinkedList.h"
#include "../inc/utn.h"

#define BUFFER 4000
#define LEN_LL 6

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

/**
*\brief Filtra elemento por el campo nombre segun parametro establecido por usuario
*\param this Es el elemento a filtrar
*\return Retorna 0 si es correcto sino retorna 1
*/
static int criterioNombre(void* this)
{
    int retorno = -1;
    static char paramName[BUFFER];
    static int flag = 0;
    char elementName[BUFFER];

    if(this != NULL)
    {
        if(flag == 0)
        {
            input("\n>>Ingrese nombre: ",paramName,BUFFER,isValidName);
            flag = 1;
        }
        employee_getNombre(this,elementName);
        if(!strcmp(elementName,paramName))
        {
            retorno = 0;
        }
    }
    else
    {
        flag = 0;//RESET
    }
    return retorno;
}

/**
*\brief Filtra elemento por el campo sueldo segun parametro establecido por usuario
*\param this Es el elemento a filtrar
*\return Retorna 0 si es correcto sino retorna 1
*/
static int criterioSueldo(void* this)
{
    int retorno = -1;
    static char paramSueldo[BUFFER];
    static int flag = 0;
    float elementSalary;

    if(this != NULL)
    {
        if(flag == 0)
        {
            input("\n>>Sueldos mayores a cifra\nIngrese cifra: ",paramSueldo,BUFFER,isValidSueldo);
            flag = 1;
        }
        employee_getSueldo(this,&elementSalary);
        if(elementSalary > atof(paramSueldo))
        {
            retorno = 0;
        }
    }
    else
    {
        flag = 0;//RESET
    }
    return retorno;
}

/**
*\brief Filtra elemento por el campo horas trabajadas segun parametro establecido por usuario
*\param this Es el elemento a filtrar
*\return Retorna 0 si es correcto sino retorna 1
*/
static int criterioHoras(void* this)
{
    int retorno = -1;
    static int flag = 0;
    static char paramHoras[BUFFER];
    int elementHours;

    if(this != NULL)
    {
        if(flag == 0)
        {
            input("\n>>Filtrar por horas mayores a cantidad\nIngrese cantidad: ",paramHoras,BUFFER,isValidHoras);
            flag = 1;
        }
        employee_getHorasTrabajadas(this,&elementHours);
        if(elementHours > atoi(paramHoras))
        {
            retorno = 0;
        }
    }
    else
    {
        flag = 0;//RESET
    }
    return retorno;
}

/**
*\brief Filtra elemento por el campo id segun parametro establecido por usuario
*\param this Es el elemento a filtrar
*\return Retorna 0 si es correcto sino retorna 1
*/
static int criterioId(void* this)
{
    int retorno = -1;
    static char paramId[BUFFER];
    static int flag = 0;
    int elementId;

    if(this != NULL)
    {
        if(flag == 0)
        {
             input("\n>>Filtrar por ID mayor a numero\nIngrese numero: ",paramId,BUFFER,isValidHoras);
             flag = 1;
        }
        employee_getId(this,&elementId);
        if(elementId > atoi(paramId))
        {
            retorno = 0;
        }
    }
    else
    {
        flag = 0;//RESET
    }
    return retorno;
}


/**
*\brief Se setea las horas trabajadas del elemento
*\param this Es el elemento
*\param horasTrabajadas Es la cantidad de horas para setear
*\return Retorna 0 si setea elemento sino retorna -1
*/
static int copyId(Employee* this,char* id)
{
    int retorno=-1;
    int auxId;

    if(this!=NULL && isValidId(id))
    {
        auxId = atoi(id);
        this->id = auxId;
        retorno=0;
    }
    return retorno;
}


////////////SORT CRITERIOS///////////////


/**
*\brief Funcion criterio por campo nombre
*\param thisA Es el primer elemento
*\param thisB Es el segundo elemento
*\return Retorna 1 si el campo del primer elemento es mayor al segundo,
*\       retorna -1 si el campo del primer elemento es menor al segundo,
*\       retorno 0 si son iguales,
*/
static int employee_criterioNombre(void* thisA,void* thisB)
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
static int employee_criterioSueldo(void* thisA,void* thisB)
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
static int employee_criterioHoras(void* thisA,void* thisB)
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
static int employee_criterioId(void* thisA,void* thisB)
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
*\param pLinkedList Es el array para recorrer
*\param idIngresado Es ID para encontrar
*\return Retorna el elemento sino retorna NULL
*/
Employee* employee_getById(void* pLinkedList,int idIngresado)
{
    Employee* retorno = NULL;
    int index;
    Employee* auxEmployee;
    int auxID = 0;

    if(pLinkedList != NULL)
    {
        for(index=0;index<ll_len(pLinkedList);index++)//Recorro todo el array hasta el LEN
        {
            auxEmployee = ll_get(pLinkedList,index);//Obtengo el elemento del array en posicion index
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
*\param pLinkedList Es el array para ingresar elemento
*\return Retorna 0 si logra agregar elemento sino retorna -1
*/
int employee_add(void* pLinkedList)
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
            ll_add(pLinkedList,this);
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
int employee_remove(void* pLinkedList,void* pListInactives)
{
    Employee* this = NULL;
    int retorno = -1;
    char bufferId[BUFFER];
    char option[2];
    int index;

    if(!input("ID",bufferId,BUFFER,isValidId))
    {
        this = employee_getById(pLinkedList,atoi(bufferId));
        if(this != NULL)
        {
            employee_show(this);
            input_getLetras(option,2,"\nATENCION!\nDesea dar de baja a empleado? S/N\n","\nError.Dato invalido",2);
            if(!strcasecmp("s",option))
            {
                index = ll_indexOf(pLinkedList,this);
                this = ll_pop(pLinkedList,index);//Revisar BAJA LOGICA

                ll_add(pListInactives,this);
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
*\brief Copia los campos de un elemento a otro
*\param thisA Es el elemento hacia donde se va a copiar (destination)
*\param thisB Es el elemento de donde se va a copiar (source)
*\return Retorna 0 si logra copiar sino retorna -1
*/
int employee_copy(Employee* thisA,Employee* thisB)
{
    int retorno = -1;
    char bufferName[BUFFER];
    char bufferHorasTrabajadas[BUFFER];
    char bufferSueldo[BUFFER];
    char bufferId[BUFFER];
    int auxId;
    int auxHoras;
    float auxSueldo;

    if(thisA != NULL && thisB != NULL)
    {
        employee_getAll(thisB,bufferName,&auxHoras,&auxSueldo,&auxId);
        sprintf(bufferId,"%d",auxId);
        sprintf(bufferHorasTrabajadas,"%d",auxHoras);
        sprintf(bufferSueldo,"%.2f",auxSueldo);

        copyId(thisA,bufferId);
        employee_setNombre(thisA,bufferName);
        employee_setHorasTrabajadas(thisA,bufferHorasTrabajadas);
        employee_setSueldo(thisA,bufferSueldo);

        retorno = 0;
    }
    return retorno;
}

/**
*\brief Reemplaza un elemento del LinkedList por otro
*\param pLinkedList Es el puntero al LinkedList
*\param auxElement Es el elemento con el que se va a reemplazar
*\param index Es el indice donde se desea reemplazar elemento
*\return Retorna 0 si logra reemplazar sino retorna -1
*/
int employee_replace(LinkedList* pLinkedList,void* auxElement,int index)
{
    int retorno = -1;
    char option[2];

    if(pLinkedList != NULL && auxElement != NULL && index >= 0 && index <= ll_len(pLinkedList))
    {
        input_getLetras(option,2,"\nDesea modificar dato? S/N\n","\nError.Dato invalido",2);
        if(!strcasecmp("s",option))
        {
            ll_set(pLinkedList,index,auxElement);
            printf("\nModificacion realizada.");
            retorno = 0;
        }
        pause();
    }
    return retorno;
}

/**
*\brief Reincorpora un empleado en el listado de activos
*\param pListActives Es el puntero al listado de activos
*\param pListInactives Es el puntero al listado de inactivos
*\return Retorna 0 si logra reincorporar sino retorna -1
*/
int employee_insert(LinkedList* pListActives,LinkedList* pListInactives)
{
    int retorno = -1;
    char bufferId[BUFFER];
    Employee* auxEmployee;
    Employee* prevEmployee;
    int index;
    int idIngresado;

    if(pListActives != NULL && pListInactives != NULL)
    {
        printf("\n<CAMBIAR STATUS EMPLEADO>");
        ll_map(pListInactives,employee_show);//Muestro los datos del empleado inactivo
        printf("\nSeleccione ID de empleado");

        input("ID",bufferId,BUFFER,isValidId);
        idIngresado= atoi(bufferId);

        auxEmployee = employee_getById(pListInactives,idIngresado);//Obtengo el empleado inactivo seleccionado
        if(auxEmployee != NULL)
        {
            employee_show(auxEmployee);

            do//Se busca el anterior al ID ingresado hasta encontrar elemento valido
            {
                prevEmployee = employee_getById(pListActives,idIngresado-1);
                idIngresado--;
            }
            while(prevEmployee == NULL);

            index = ll_indexOf(pListActives,prevEmployee);
            ll_push(pListActives,index+1,auxEmployee);//Se reincorpora el empleado inactivo
            index = ll_indexOf(pListInactives,auxEmployee);//Busco indice del empleado inactivo en listado de bajas
            ll_remove(pListInactives,index);
            retorno = 0;
        }
    }
    return retorno;
}


/**
*\brief Se busca elemento por ID a modificar con opciones de campos
*\param pLinkedList Es el array a recorrer
*\return Retorna 0 si logra modificar campo sino retorna -1
*/
int employee_edit(void* pLinkedList)
{
    int retorno = -1;
    int option;
    char bufferId[BUFFER];
    int index;
    Employee* this = NULL;
    Employee* auxElement = employee_new();

    if(pLinkedList != NULL)
    {
        do
        {
            retorno = 0;
            limpiarPantalla();
            printf("\n<MODIFICAR DATOS>");
            printf("\n1) Nombre\n2) Sueldo\n3) Horas trabajadas\n4) Volver");
            input_getEnteros(&option,"\nIngrese opcion: ","\nError.Dato invalido",2);

            if(option == 4)
            {
                break;
            }
            input("ID",bufferId,BUFFER,isValidId);
            this = employee_getById(pLinkedList,atoi(bufferId));
            index = ll_indexOf(pLinkedList,this);

            if(this == NULL)
            {
                printf("\nID no encontrado");
                continue;
            }
            else if(this != NULL && auxElement != NULL)
            {
                employee_copy(auxElement,this);
                employee_show(auxElement);
            }

            switch(option)
            {
                case 1 :
                    employee_modify(auxElement,"nombre",isValidName,employee_setNombre);
                    verification(pLinkedList,auxElement,index);
                    break;
                case 2 :
                    employee_modify(auxElement,"sueldo",isValidSueldo,employee_setSueldo);
                    verification(pLinkedList,auxElement,index);
                    break;
                case 3 :
                    employee_modify(auxElement,"horas trabajadas",isValidHoras,employee_setHorasTrabajadas);
                    verification(pLinkedList,auxElement,index);
                    break;
                case 4 :
                    break;
                default :
                    printf("\nOpcion invalida");
            }
        }while(option != 4);
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
    char buffer[BUFFER];

    if(this != NULL && mensaje != NULL && validacion != NULL && set != NULL)
    {
        input(mensaje,buffer,BUFFER,(*validacion));
        if(buffer != NULL)
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
int employee_show(void* this)
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
*\param pLinkedList Es la LinkedList para ordenar
*\return Retorna 0 si logra ordenar sino retorna -1
*/
int employee_sort(void* pLinkedList)
{
    int retorno = -1;
    function_type criterio;
    int orden;

    limpiarPantalla();
    if(pLinkedList != NULL)
    {
        printf("\n<ORDENAR>");
        criterio = employee_ordenCriterio();
        if(criterio != NULL)
        {
            input_getEnteros(&orden,"\n-Seleccione orden\n Descendente (0)\n Ascendente (1)","Error.",2);
            if(orden == 0 || orden == 1)
            {
                ll_sort(pLinkedList,criterio,orden);
                retorno = 0;
            }
        }
    }
    return retorno;
}

/**
*\brief Se realiza un alta forzada
*\param pLinkedList Es la LinkedList para realizar el alta
*\param bufferName Es el nombre a cargar en el elemento
*\param bufferHorasTrabajadas Es la cantidad de horas trabajadas para cargar en el elemento
*\param bufferSueldo Es el sueldo para cargar en el elemento
*\return Retorna 0 si el array es diferente a NULL sino retorna -1
*/
int employee_hardcode(void* pLinkedList,char *bufferName,char* bufferHorasTrabajadas,char* bufferSueldo)
{
    Employee* this = NULL;
    int retorno = -1;

    this = employee_newConParametros("0",bufferName,bufferHorasTrabajadas,bufferSueldo);

    if(this != NULL)
    {
        employee_show(this);
        ll_add(pLinkedList,this);
        retorno = 0;;
    }
    return retorno;
}

/**
*\brief Calcula el valor de la hora trabajada
*\param pLinkedList Es la LinkedList para realizar el alta
*\return Retorna el valor de la hora trabajada sino retorna -1
*/
int employee_calculoSueldo(void* this)
{
    int retorno = -1;
    int auxHoras;
    float auxSueldo;
    int valorHora;

    if(this != NULL)
    {
        employee_getHorasTrabajadas(this,&auxHoras);
        employee_getSueldo(this,&auxSueldo);

        valorHora = auxSueldo / auxHoras;
        retorno = valorHora;
    }
    return retorno;
}

/**
*\brief Funcion para borrar listados de empleados, principal y filtrados
*\param pLinkedList Es el puntero al listado principal que contiene todos los listados
*\return Retorna 0 si el listado principal existe sino retorna -1
*/
int employee_borrarLista(LinkedList* pLinkedList[])
{
    int retorno = -1;
    int option;
    int list;
    char verification[2];

    if(pLinkedList != NULL)
    {
        printf("\n1) Vaciar lista\n2) Eliminar todas las listas\n3) Volver");
        input_getEnteros(&option,"\nIngrese opcion: ","\nDato invalido",2);

        switch(option)
        {
            case 1 :
                printf("\n1) Empleados activos\n2) Empleados inactivos \n3) Sublista\n4) Lista filtrada\n5) Todas las listas");
                input_getEnteros(&list,"\nSeleccione lista: ","\nError",2);
                input_getLetras(verification,2,"\nATENCION!\nDesea vaciar lista? S/N\n","\nError.",2);
                if(list >= 1 && list <= 5 && !ll_isEmpty(pLinkedList[list]) && !strcasecmp("s",verification))
                {
                    if(!ll_clear(pLinkedList[list]))
                    {
                        printf("\nLista vaciada.");//BORRAR IF
                    }
                }
                break;
            case 2 :
                printf("\nATENCION! Las sublistas no se recuperan.");
                input_getLetras(verification,2,"\nDesea eliminar todas las listas? S/N\n","\nError.",2);
                if(!strcasecmp("s",verification))
                {
                    if(!ll_freeLinkedList(pLinkedList))
                    {
                        ll_initLinkedList(pLinkedList);
                        printf("\nListas eliminadas.");
                    }
                }
            case 3 :
                break;
        }
        retorno = 0;

    }
    return retorno;
}


/**
* \brief Generar una lista de empleados segun opciones, sublist, filter, clone.
* \param this Es el puntero al LinkedList original
* \param newList Es el puntero al LinkedList nuevo
* \return Retorna 0 si el LinkedList no es NULL sino retorna -1
*/
int employee_generarLista(LinkedList* pLinkedList,LinkedList* listaPrincipal[],int* index)
{
    int retorno = -1;
    int option;
    int from = 0;
    int to = 0;
    int len;
    criterio_type criterio;
    void* auxLinkedList  = ll_newLinkedList();
    printf("\n1) Dividir lista\n2) Filtrar lista\n3) Copiar lista\n4) Volver\n");
    input_getEnteros(&option,"\nIngrese opcion: ","\nDato invalido",2);

    if(pLinkedList != NULL)
    {
        len = ll_len(pLinkedList);
        switch(option)
        {
            case 1 :
                input_getEnteros(&from,"\nSeleccione primer indice: ","\nDato invalido",2);
                input_getEnteros(&to,"\nSeleccione segundo indice: ","\nDato invalido",2);
                if(from >= 0 && from < len && to >= 1 && to < len)
                {
                    auxLinkedList = ll_subList(pLinkedList,from,to);
                    if(auxLinkedList != NULL)
                    {
                        listaPrincipal[3] = auxLinkedList;
                        *index = 3;
                        retorno = 0;
                    }
                }
                else
                {
                    printf("\nIndice invalido.");
                }
                break;
            case 2 :
                printf("\nSeleccione criterio para filtrar");
                criterio = employee_selectorCriterio();
                auxLinkedList  = ll_filter(pLinkedList,criterio);
                if(auxLinkedList != NULL)
                {
                    listaPrincipal[4] = auxLinkedList;
                    *index = 4;
                    retorno = 0;
                }
                break;
            case 3 :
                printf("\nRealizando back-up...");
                auxLinkedList = ll_clone(pLinkedList);
                if(ll_containsAll(pLinkedList,auxLinkedList))
                {
                    listaPrincipal[5] = auxLinkedList;
                    *index = 5;
                    retorno = 0;
                }
                break;
            case 4 :
                break;
            default :
                printf("\nError.Opcion incorrecta");
                break;
        }
    }
    return retorno;
}


/**
*\brief Funcion selector de criterio para filtrar
*\return Retorna puntero a funcion segun criterio seleccionado si no es correcto retorna NULL
*/
void* employee_selectorCriterio()
{
    int opcion;

    void* retorno = NULL;
    input_getEnteros(&opcion,"\n1) Nombre\n2) Sueldo\n3) Horas\n4) ID\n","\nOpcion incorrecta",2);

    switch(opcion)
    {
        case 1 :
            printf("\nFiltrar por nombre");
            criterioNombre(NULL);
            retorno = criterioNombre;
            break;
        case 2 :
            printf("\nFiltrar por sueldo");
            criterioSueldo(NULL);
            retorno = criterioSueldo;
            break;
        case 3 :
            printf("\nFiltrar por horas trabajadas");
            criterioHoras(NULL);
            retorno = criterioHoras;
            break;
        case 4 :
            printf("\nFiltrar por ID");
            criterioId(NULL);
            retorno = criterioId;
            break;
        default :
            printf("\nOpcion incorrecta");
    }
    return retorno;
}


/**
*\brief Funcion selector de criterio para ordenar
*\return Retorna puntero a funcion segun criterio seleccionado si no es correcto retorna NULL
*/
void* employee_ordenCriterio()
{
    int opcion;

    void* retorno = NULL;
    input_getEnteros(&opcion,"\nSeleccione opcion\n1) Nombre\n2) Sueldo\n3) Horas\n4) ID\n","\nOpcion incorrecta",2);

    switch(opcion)
    {
        case 1 :
            printf("\nNombre");
            retorno = employee_criterioNombre;
            break;
        case 2 :
            printf("\nSueldo");
            retorno = employee_criterioSueldo;
            break;
        case 3 :
            printf("\nHoras Trabajadas");
            retorno = employee_criterioHoras;
            break;
        case 4 :
            printf("\nID");
            retorno = employee_criterioId;
            break;
        default :
            printf("\nOpcion incorrecta");
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
    static int proximoId= 0;
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
    else if(this!=NULL && auxId<proximoId)
    {
        this->id=auxId;
        retorno = 0;
    }
    else if(this!=NULL && auxId > -1)
    {
        proximoId = 0;//Reset
        retorno = 0;
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
