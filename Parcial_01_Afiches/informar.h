#ifndef INFORMAR_H_INCLUDED
#define INFORMAR_H_INCLUDED


#include "ventas.h"
#include "clientes.h"

int informar_ClientesPendientes(Cliente arrayUno[],
                                       int sizeUno,
                                       Venta arrayDos[],
                                       int sizeDos,
                                       int contadorClientes,
                                       int contadorVentas);

int informar_statusVentas(Venta array[],
                                int size);

int informar_ventasPromedioAfiches(Venta array[],
                                int size,
                                int calculo);

int informar_calculoTotalVentas(Venta arrayDos[],int sizeDos,int idIngresado,char status[]);

int informar_calculoTotalAfiches(Venta arrayDos[],int sizeDos,int idIngresado,char status[]);

int informar_calculoPromedioCantidad(Venta array[],
                                int size,
                                float* promedio);

int informar_calculoAfichesZona(Venta array[], int size);

int informar_calculoZonaMenosVenta(Venta array[],
                                int size);
int informar_calculoVentasZona(Venta array[],
                                int size);

int informar_calculoClientesZona(Cliente arrayUno[],
                                 Venta arrayDos[],
                                int sizeUno,
                                int sizeDos,
                                int opcion);


int informar_ventasPorCuit(Cliente arrayUno[],
                                 Venta arrayDos[],
                                int sizeUno,
                                int sizeDos);

int informar_ventasPorCuitZona(Cliente arrayUno[],
                                 Venta arrayDos[],
                                int sizeUno,
                                int sizeDos,
                                int opcion);

int informar_clienteMasVentas(Cliente arrayUno[],Venta arrayDos[],
                                int sizeUno,int sizeDos);

int informar_clienteMasVentasCobradas(Cliente arrayUno[],Venta arrayDos[],
                                int sizeUno,int sizeDos);

int informar_clienteMasVentasPendientes(Cliente arrayUno[],Venta arrayDos[],
                                int sizeUno,int sizeDos);

int informar_clienteMenosVentasPendientes(Cliente arrayUno[],Venta arrayDos[],
                                int sizeUno,int sizeDos);

int informar_clienteMenosVentasCobradas(Cliente arrayUno[],Venta arrayDos[],
                                int sizeUno,int sizeDos);

int informar_clientesAfichesMenorMil(Cliente arrayUno[],Venta arrayDos[],
                                int sizeUno,int sizeDos);

int informar_clienteMasAfiches(Cliente arrayUno[],Venta arrayDos[],
                                int sizeUno,int sizeDos);

int informar_clienteMasAfichesPagados(Cliente arrayUno[],Venta arrayDos[],
                                int sizeUno,int sizeDos);

int informar_clienteMenosAfiches(Cliente arrayUno[],Venta arrayDos[],
                                int sizeUno,int sizeDos);

Cliente* informar_buscarClienteCuit(Cliente array[],int size,char cuit[]);


int informar_menu(Cliente arrayClientes[],int sizeUno,Venta arrayVentas[],int sizeDos);

int informar_initListadoCuit(Cliente array[],int qty_clientes);

#endif
