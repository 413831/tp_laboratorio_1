
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "utn.h"
#include "Venta.h"

static int isValidId(int id);
static int isValidFecha(char* fecha);
static int isValidCodigo(char* codigo);
static int isValidCantidad(int cantidad);
static int isValidPrecio(float precio);
static int isValidCuit(char* cuit);

/**
*\brief Valida un dato del campo id
*\param id Es el dato recibido para validar
*\return Retorna 1 si el dato es valido sino retorna 0
*/
static int isValidId(int id)
{
	int retorno = 0;
	if(id >= 0)
	{
		retorno = 1;
	}
	return retorno;
}

/**
*\brief Valida un dato del campo fecha
*\param fecha Es el dato recibido para validar
*\return Retorna 1 si el dato es valido sino retorna 0
*/
static int isValidFecha(char* fecha)
{
	int retorno = 0;
	if(fecha != NULL && strlen(fecha) > 6)
	{
		retorno = 1;
	}
	return retorno;
}

/**
*\brief Valida un dato del campo codigo
*\param codigo Es el dato recibido para validar
*\return Retorna 1 si el dato es valido sino retorna 0
*/
static int isValidCodigo(char* codigo)
{
	int retorno = 0;
	if(codigo != NULL && strlen(codigo) > 3)
	{
		retorno = 1;
	}
	return retorno;
}

/**
*\brief Valida un dato del campo cantidad
*\param cantidad Es el dato recibido para validar
*\return Retorna 1 si el dato es valido sino retorna 0
*/
static int isValidCantidad(int cantidad)
{
	int retorno = 0;
	if(cantidad >= 1)
	{
		retorno = 1;
	}
	return retorno;
}

/**
*\brief Valida un dato del campo precio
*\param precio Es el dato recibido para validar
*\return Retorna 1 si el dato es valido sino retorna 0
*/
static int isValidPrecio(float precio)
{
	int retorno = 0;
	if(precio >= 1)
	{
		retorno = 1;
	}
	return retorno;
}

/**
*\brief Valida un dato del campo cuit
*\param cuit Es el dato recibido para validar
*\return Retorna 1 si el dato es valido sino retorna 0
*/
static int isValidCuit(char* cuit)
{
	int retorno = 0;
	if(cuit != NULL && strlen(cuit) > 8)
	{
		retorno = 1;
	}
	return retorno;
}


//////////////////PUBLIC//////////////////

/**
*\brief Reserva espacio en memoria para un elemento
*\param void
*\return Retorna el elemento si reserva memoria sino NULL
*/
Venta* venta_new()
{
    Venta* this;
    this=malloc(sizeof(Venta));
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
*\param COMPLETAR
*\return Retorna 0 si logra agregar elemento sino retorna -1
*/
Venta* venta_constructor(int id,char* fecha,char* codigo,int cantidad,float precio,char* cuit)
{
	Venta* this = malloc(sizeof(Venta));
    Venta* retorno = NULL;

	if(this != NULL)
	{
		if(	!venta_setId(this,id) &&
			!venta_setFecha(this,fecha) &&
			!venta_setCodigo(this,codigo) &&
			!venta_setCantidad(this,cantidad) &&
			!venta_setPrecio(this,precio) &&
			!venta_setCuit(this,cuit)
			)
		{
			retorno = this;
		}
		else
		{
			venta_destructor(this);
		}
	}
	return retorno;
}

/**
*\brief Es el destructor del elemento que funciona para liberar memoria reservada
*\param this Es el elemento para eliminar
*\return Retorna 0 si logra eliminar elemento sino retorna -1
*/
int venta_destructor(Venta* this)
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
*\brief Se realiza el alta de un elemento desde consola
*\param pLinkedList Es el array para ingresar elemento
*\return Retorna 0 si logra agregar elemento sino retorna -1
*/
int venta_add(void* pLinkedList)
{
    int retorno = -1;
    char id[BUFFER];
    char fecha[BUFFER];
    char codigo[BUFFER];
    char cantidad[BUFFER];
    char precio[BUFFER];
    char cuit[BUFFER];
    Venta* this = NULL;

    if( !input("Id",id,BUFFER,validacion_Int) &&
        !input("Fecha",fecha,BUFFER,validacion_AlfaNumerico) &&
        !input("Codigo",codigo,BUFFER,validacion_AlfaNumerico) &&
        !input("Cantidad",cantidad,BUFFER,validacion_Int) &&
        !input("Precio",precio,BUFFER,validacion_Float) &&
        !input("CUIT",cuit,BUFFER,validacion_Cuit))
    {
        this = venta_constructor(atoi(id),fecha,codigo,atoi(cantidad),atof(precio),cuit);
        if(this != NULL)
        {
            venta_show(this);
            ll_add(pLinkedList,this);
            retorno = 0;;
        }
    }
    return retorno;
}

/**
*\brief Es el setter del campo id del elemento
*\param this Es el elemento que se recibe para setear un campo
*\param id Es el dato recibido para setear el campo
*\return Retorna 0 si el elemento existe y si el dato es valido sino retorna COMPLETAR
*/
int venta_setId(Venta* this,int id)
{
	int retorno = -1;
	if(this != NULL && isValidId(id))
	{
		this->id = id;
		retorno = 0;
	}
	return retorno;
}

/**
*\brief Es el setter del campo fecha del elemento
*\param this Es el elemento que se recibe para setear un campo
*\param fecha Es el dato recibido para setear el campo
*\return Retorna 0 si el elemento existe y si el dato es valido sino retorna COMPLETAR
*/
int venta_setFecha(Venta* this,char* fecha)
{
	int retorno = -1;
	if(this != NULL && fecha != NULL && isValidFecha(fecha))
	{
		strcpy(this->fecha,fecha);
		retorno = 0;
	}
	return retorno;
}

/**
*\brief Es el setter del campo codigo del elemento
*\param this Es el elemento que se recibe para setear un campo
*\param codigo Es el dato recibido para setear el campo
*\return Retorna 0 si el elemento existe y si el dato es valido sino retorna COMPLETAR
*/
int venta_setCodigo(Venta* this,char* codigo)
{
	int retorno = -1;
	if(this != NULL && codigo != NULL && isValidCodigo(codigo))
	{
		strcpy(this->codigo,codigo);
		retorno = 0;
	}
	return retorno;
}

/**
*\brief Es el setter del campo cantidad del elemento
*\param this Es el elemento que se recibe para setear un campo
*\param cantidad Es el dato recibido para setear el campo
*\return Retorna 0 si el elemento existe y si el dato es valido sino retorna COMPLETAR
*/
int venta_setCantidad(Venta* this,int cantidad)
{
	int retorno = -1;
	if(this != NULL && isValidCantidad(cantidad))
	{
		this->cantidad = cantidad;
		retorno = 0;
	}
	return retorno;
}

/**
*\brief Es el setter del campo precio del elemento
*\param this Es el elemento que se recibe para setear un campo
*\param precio Es el dato recibido para setear el campo
*\return Retorna 0 si el elemento existe y si el dato es valido sino retorna COMPLETAR
*/
int venta_setPrecio(Venta* this,float precio)
{
	int retorno = -1;
	if(this != NULL && isValidPrecio(precio))
	{
		this->precio = precio;
		retorno = 0;
	}
	return retorno;
}

/**
*\brief Es el setter del campo cuit del elemento
*\param this Es el elemento que se recibe para setear un campo
*\param cuit Es el dato recibido para setear el campo
*\return Retorna 0 si el elemento existe y si el dato es valido sino retorna COMPLETAR
*/
int venta_setCuit(Venta* this,char* cuit)
{
	int retorno = -1;
	if(this != NULL && cuit != NULL && isValidCuit(cuit))
	{
		strcpy(this->cuit,cuit);
		retorno = 0;
	}
	return retorno;
}

/**
*\brief Es el getter del campo id del elemento
*\param this Es el elemento del cual se obtiene el dato id
*\return Retorna 0 si el elemento existe y si el dato es valido sino retorna COMPLETAR
*/
int venta_getId(Venta* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		retorno = this->id;
	}
	return retorno;
}

/**
*\brief Es el getter del campo fecha del elemento
*\param this Es el elemento del cual se obtiene el dato fecha
*\return Retorna 0 si el elemento existe y si el dato es valido sino retorna COMPLETAR
*/
char* venta_getFecha(Venta* this)
{
	char* retorno = NULL;
	if(this != NULL)
	{
		strcpy(retorno,this->fecha);
	}
	return retorno;
}

/**
*\brief Es el getter del campo codigo del elemento
*\param this Es el elemento del cual se obtiene el dato codigo
*\return Retorna 0 si el elemento existe y si el dato es valido sino retorna COMPLETAR
*/
char* venta_getCodigo(Venta* this)
{
	char* retorno = malloc(sizeof(char));
	if(this != NULL)
	{
		strcpy(retorno,this->codigo);
	}
	return retorno;
}

/**
*\brief Es el getter del campo cantidad del elemento
*\param this Es el elemento del cual se obtiene el dato cantidad
*\return Retorna 0 si el elemento existe y si el dato es valido sino retorna COMPLETAR
*/
int venta_getCantidad(Venta* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		retorno = this->cantidad;
	}
	return retorno;
}

/**
*\brief Es el getter del campo precio del elemento
*\param this Es el elemento del cual se obtiene el dato precio
*\return Retorna 0 si el elemento existe y si el dato es valido sino retorna COMPLETAR
*/
float venta_getPrecio(Venta* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		retorno = this->precio;
	}
	return retorno;
}

/**
*\brief Es el getter del campo cuit del elemento
*\param this Es el elemento del cual se obtiene el dato cuit
*\return Retorna 0 si el elemento existe y si el dato es valido sino retorna COMPLETAR
*/
char* venta_getCuit(Venta* this)
{
	char* retorno = NULL;
	if(this != NULL)
	{
		strcpy(retorno,this->cuit);
	}
	return retorno;
}

/**
*\brief Retorna un elemento segun el dato id ingresado
*\param pArray Es el puntero a LinkedList recibido para buscar elemento
*\param id Es el dato que se recibe para encontrar el elemento
*\return Retorna el elemento si lo encuentra sino retorna NULL
*/
Venta* venta_getById(LinkedList* pArray,int id)
{
	int i;
	Venta* aux;
	Venta* retorno=NULL;

	if(pArray != NULL && isValidId(id))
	{
		for(i=0;i<ll_len(pArray);i++)
		{
			aux = ll_get(pArray,i);
			if(id == venta_getId(aux))
			{
				retorno = aux;
				break;
			}
		}
	}
	return retorno;
}

/**
*\brief Retorna un elemento segun el dato fecha ingresado
*\param pArray Es el puntero a LinkedList recibido para buscar elemento
*\param fecha Es el dato que se recibe para encontrar el elemento
*\return Retorna el elemento si lo encuentra sino retorna NULL
*/
Venta* venta_getByFecha(LinkedList* pArray,char* fecha)
{
	int i;
	Venta* aux;
	Venta* retorno=NULL;

	if(pArray != NULL && isValidFecha(fecha))
	{
		for(i=0;i<ll_len(pArray);i++)
		{
			aux = ll_get(pArray,i);
			if(strcmp(fecha,venta_getFecha(aux))==0)
			{
				retorno = aux;
				break;
			}
		}
	}
	return retorno;
}

/**
*\brief Retorna un elemento segun el dato codigo ingresado
*\param pArray Es el puntero a LinkedList recibido para buscar elemento
*\param codigo Es el dato que se recibe para encontrar el elemento
*\return Retorna el elemento si lo encuentra sino retorna NULL
*/
Venta* venta_getByCodigo(LinkedList* pArray,char* codigo)
{
	int i;
	Venta* aux;
	Venta* retorno=NULL;

	if(pArray != NULL && isValidCodigo(codigo))
	{
		for(i=0;i<ll_len(pArray);i++)
		{
			aux = ll_get(pArray,i);
			if(strcmp(codigo,venta_getCodigo(aux))==0)
			{
				retorno = aux;
				break;
			}
		}
	}
	return retorno;
}

/**
*\brief Retorna un elemento segun el dato cantidad ingresado
*\param pArray Es el puntero a LinkedList recibido para buscar elemento
*\param cantidad Es el dato que se recibe para encontrar el elemento
*\return Retorna el elemento si lo encuentra sino retorna NULL
*/
Venta* venta_getByCantidad(LinkedList* pArray,int cantidad)
{
	int i;
	Venta* aux;
	Venta* retorno=NULL;

	if(pArray != NULL && isValidCantidad(cantidad))
	{
		for(i=0;i<ll_len(pArray);i++)
		{
			aux = ll_get(pArray,i);
			if(cantidad == venta_getCantidad(aux))
			{
				retorno = aux;
				break;
			}
		}
	}
	return retorno;
}

/**
*\brief Retorna un elemento segun el dato precio ingresado
*\param pArray Es el puntero a LinkedList recibido para buscar elemento
*\param precio Es el dato que se recibe para encontrar el elemento
*\return Retorna el elemento si lo encuentra sino retorna NULL
*/
Venta* venta_getByPrecio(LinkedList* pArray,float precio)
{
	int i;
	Venta* aux;
	Venta* retorno=NULL;

	if(pArray != NULL && isValidPrecio(precio))
	{
		for(i=0;i<ll_len(pArray);i++)
		{
			aux = ll_get(pArray,i);
			if(precio == venta_getPrecio(aux))
			{
				retorno = aux;
				break;
			}
		}
	}
	return retorno;
}

/**
*\brief Retorna un elemento segun el dato cuit ingresado
*\param pArray Es el puntero a LinkedList recibido para buscar elemento
*\param cuit Es el dato que se recibe para encontrar el elemento
*\return Retorna el elemento si lo encuentra sino retorna NULL
*/
Venta* venta_getByCuit(LinkedList* pArray,char* cuit)
{
	int i;
	Venta* aux;
	Venta* retorno=NULL;

	if(pArray != NULL && isValidCuit(cuit))
	{
		for(i=0;i<ll_len(pArray);i++)
		{
			aux = ll_get(pArray,i);
			if(strcmp(cuit,venta_getCuit(aux))==0)
			{
				retorno = aux;
				break;
			}
		}
	}
	return retorno;
}

/**
*\brief Compara dos elementos por su campo id
*\param thisA Es el puntero al primer elemento a comparar
*\param thisB Es el puntero al segundo elemento a comparar
*\return Retorna 0 si ambos campos son iguales
		Retorna 1 si el campo del primer elemento es mayor al segundo
		Retorna -1 si el campo del segundo elemento es mayor al primero
*/
int venta_compareById(void* thisA ,void* thisB)
{
	int retorno = 0;

	if(thisA != NULL && thisB != NULL)
	{
		if(venta_getId(thisA) > venta_getId(thisB))
		{
				retorno = 1;
		}
		else if(venta_getId(thisA) < venta_getId(thisB))
		{
			retorno = -1;
		}
	}
	return retorno;
}

/**
*\brief Compara dos elementos por su campo fecha
*\param thisA Es el puntero al primer elemento a comparar
*\param thisB Es el puntero al segundo elemento a comparar
*\return Retorna 0 si ambos campos son iguales
		Retorna 1 si el campo del primer elemento es mayor al segundo
		Retorna -1 si el campo del segundo elemento es mayor al primero
*/
int venta_compareByFecha(void* thisA ,void* thisB)
{
	int retorno = 0;

	if(thisA != NULL && thisB != NULL)
	{
		retorno = strcmp(venta_getFecha(thisA),venta_getFecha(thisB));
	}
	return retorno;
}

/**
*\brief Compara dos elementos por su campo codigo
*\param thisA Es el puntero al primer elemento a comparar
*\param thisB Es el puntero al segundo elemento a comparar
*\return Retorna 0 si ambos campos son iguales
		Retorna 1 si el campo del primer elemento es mayor al segundo
		Retorna -1 si el campo del segundo elemento es mayor al primero
*/
int venta_compareByCodigo(void* thisA ,void* thisB)
{
	int retorno = 0;

	if(thisA != NULL && thisB != NULL)
	{
		retorno = strcmp(venta_getCodigo(thisA),venta_getCodigo(thisB));
	}
	return retorno;
}

/**
*\brief Compara dos elementos por su campo cantidad
*\param thisA Es el puntero al primer elemento a comparar
*\param thisB Es el puntero al segundo elemento a comparar
*\return Retorna 0 si ambos campos son iguales
		Retorna 1 si el campo del primer elemento es mayor al segundo
		Retorna -1 si el campo del segundo elemento es mayor al primero
*/
int venta_compareByCantidad(void* thisA ,void* thisB)
{
	int retorno = 0;

	if(thisA != NULL && thisB != NULL)
	{
		if(venta_getCantidad(thisA) > venta_getCantidad(thisB))
		{
				retorno = 1;
		}
		else if(venta_getCantidad(thisA) < venta_getCantidad(thisB))
		{
			retorno = -1;
		}
	}
	return retorno;
}

/**
*\brief Compara dos elementos por su campo precio
*\param thisA Es el puntero al primer elemento a comparar
*\param thisB Es el puntero al segundo elemento a comparar
*\return Retorna 0 si ambos campos son iguales
		Retorna 1 si el campo del primer elemento es mayor al segundo
		Retorna -1 si el campo del segundo elemento es mayor al primero
*/
int venta_compareByPrecio(void* thisA ,void* thisB)
{
	int retorno = 0;

	if(thisA != NULL && thisB != NULL)
	{
		if(venta_getPrecio(thisA) > venta_getPrecio(thisB))
		{
				retorno = 1;
		}
		else if(venta_getPrecio(thisA) < venta_getPrecio(thisB))
		{
			retorno = -1;
		}
	}
	return retorno;
}

/**
*\brief Compara dos elementos por su campo cuit
*\param thisA Es el puntero al primer elemento a comparar
*\param thisB Es el puntero al segundo elemento a comparar
*\return Retorna 0 si ambos campos son iguales
		Retorna 1 si el campo del primer elemento es mayor al segundo
		Retorna -1 si el campo del segundo elemento es mayor al primero
*/
int venta_compareByCuit(void* thisA ,void* thisB)
{
	int retorno = 0;

	if(thisA != NULL && thisB != NULL)
	{
		retorno = strcmp(venta_getCuit(thisA),venta_getCuit(thisB));
	}
	return retorno;
}

/**
*\brief Muestra los datos de un elemento
*\param this Es el elemento que recibe para mostrar
*\return Retorna 0 si el elemento existe sino retorna -1
*/
int venta_show(void* this)
{
    int retorno = -1;
    char codigoVenta[BUFFER];
    char fechaVenta[BUFFER];
    char cuitVenta[BUFFER];

	if(this != NULL)
	{
     //   strcpy(codigoVenta,venta_getCodigo(this));
   //     strcpy(fechaVenta,venta_getFecha(this));
   //     strcpy(cuitVenta,venta_getCuit(this));

		printf("\nId -- %d",venta_getId(this));
		printf("\nFecha -- %s",fechaVenta);
		printf("\nCodigo -- %s",codigoVenta);
		printf("\nCantidad -- %d",venta_getCantidad(this));
		printf("\nPrecio -- %.2f",venta_getPrecio(this));
		printf("\nCuit -- %s",cuitVenta);
		retorno = 0;
	}
	return retorno;
}

/*
int venta_generarLista(LinkedList* listaVentas)
{
    int retorno;

    if(listaVentas != NULL)
    {




    }


    return retorno;

}
*/

int venta_seleccionarVenta10k(void* this)
{
    int retorno = 0;
    float valorVenta;
    int cantidad;
    int totalVenta;

    if(this != NULL)
    {
        valorVenta = venta_getPrecio(this);
        cantidad = venta_getCantidad(this);
        totalVenta = valorVenta * cantidad;

        if(totalVenta > 10000)//Comparo el sueldo del elemento contra el numero ingresado
        {
            retorno = 1;
        }
    }
    return retorno;
}

int venta_seleccionarVenta20k(void* this)
{
    int retorno = 0;
    float valorVenta;
    int cantidad;
    int totalVenta;

    if(this != NULL)
    {
        valorVenta = venta_getPrecio(this);
        cantidad = venta_getCantidad(this);
        totalVenta = valorVenta * cantidad;

        if(totalVenta > 20000)//Comparo el sueldo del elemento contra el numero ingresado
        {
            retorno = 1;
        }
    }
    return retorno;
}

int venta_seleccionarLCD(void* this)
{
    int retorno = 0;
    char codigoVenta[BUFFER];

    if(this != NULL)
    {
        strcpy(codigoVenta,venta_getCodigo(this));
        if(!strcmp(codigoVenta,"LCD_TV"))//Comparo el sueldo del elemento contra el numero ingresado
        {
            retorno = 1;
        }
    }
    return retorno;
}

int venta_unidades(void* this)
{
    int retorno = 0;
    int cantidadVenta;

    if(this != NULL)
    {
        cantidadVenta = venta_getCantidad(this);
        if(cantidadVenta > 0)//Comparo el sueldo del elemento contra el numero ingresado
        {
            retorno = cantidadVenta;
        }
    }
    return retorno;
}

/**
*\brief Funcion para ordenar el LinkedList segun criterio y orden
*\param pLinkedList Es la LinkedList para ordenar
*\return Retorna 0 si logra ordenar sino retorna -1
*/
int venta_sort(void* pLinkedList)
{
    int retorno = -1;
    int orden;

    limpiarPantalla();
    if(pLinkedList != NULL)
    {
        printf("\n<ORDENAR>");

        input_getEnteros(&orden,"\n-Seleccione orden\n Descendente (0)\n Ascendente (1)","Error.",2);

        if(orden == 0 || orden == 1)
        {
            ll_sort(pLinkedList,venta_compareById,orden);
            retorno = 0;
        }

    }
    return retorno;
}

