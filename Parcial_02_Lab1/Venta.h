

#include "LinkedList.h"

#ifndef _VENTA_H
#define _VENTA_H
typedef struct
{
	int id;
	char fecha[15];
	char codigo[35];
	int cantidad;
	float precio;
	char cuit[15];
}Venta;
#endif// _VENTA_H


#define BUFFER 4000
#define LEN_LL 6

Venta* venta_new();
Venta* venta_constructor(int id,char* fecha,char* codigo,int cantidad,float precio,char* cuit);
int venta_destructor(Venta* this);
int venta_add(void* pLinkedList);
int venta_setId(Venta* this,int id);
int venta_setFecha(Venta* this,char* fecha);
int venta_setCodigo(Venta* this,char* codigo);
int venta_setCantidad(Venta* this,int cantidad);
int venta_setPrecio(Venta* this,float precio);
int venta_setCuit(Venta* this,char* cuit);
int venta_getId(Venta* this);
char* venta_getFecha(Venta* this);
char* venta_getCodigo(Venta* this);
int venta_getCantidad(Venta* this);
float venta_getPrecio(Venta* this);
char* venta_getCuit(Venta* this);
Venta* venta_getById(LinkedList* pArray,int id);
Venta* venta_getByFecha(LinkedList* pArray,char* fecha);
Venta* venta_getByCodigo(LinkedList* pArray,char* codigo);
Venta* venta_getByCantidad(LinkedList* pArray,int cantidad);
Venta* venta_getByPrecio(LinkedList* pArray,float precio);
Venta* venta_getByCuit(LinkedList* pArray,char* cuit);
int venta_compareById(void* thisA ,void* thisB);
int venta_compareByFecha(void* thisA ,void* thisB);
int venta_compareByCodigo(void* thisA ,void* thisB);
int venta_compareByCantidad(void* thisA ,void* thisB);
int venta_compareByPrecio(void* thisA ,void* thisB);
int venta_compareByCuit(void* thisA ,void* thisB);
int venta_show(void* this);
int venta_seleccionarVenta20k(void* this);
int venta_seleccionarVenta10k(void* this);
int venta_seleccionarLCD(void* this);
int venta_unidades(void* this);
int venta_sort(void* pLinkedList);
