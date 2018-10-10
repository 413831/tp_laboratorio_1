#ifndef VENTAS_H_INCLUDED
#define VENTAS_H_INCLUDED


#define STATUS_0 "Disponible"
#define STATUS_1 "A cobrar"
#define STATUS_2 "Cobrado"

typedef struct
{
    char nombreAfiche[50];
    char zona[50];
    int cantidad;
    int idCliente;
    //------------
    int id;
    char status[20];
}Venta;


int venta_buscarIndiceLibre(Venta array[],int size);
int venta_init(Venta array[],int size,char status[]);
Venta* venta_getByID(Venta* array,int size,int id);
int venta_validarZona(char zona[]);
int venta_alta(Venta* array,int size,int idIngresado);
int venta_modificar(Venta* array);
int venta_baja(Venta* array);
int venta_eliminar(Venta* array);
int venta_ordenar(Venta array[],int size);
int venta_mostrar(Venta array[],int size,int idIngresado);
int venta_cobradas(Venta array[],int size,int idIngresado);
int venta_listar(Venta array[],int size);
int venta_ingresoForzado(Venta array[],
                        int size,
                        char auxNombreArchivo[],
                        char auxZona[],
                        int auxCantidad,
                        int idCliente);


//int proximoId();
//int pantalla_buscarPorId(Pantalla* array,int size, int id);

#endif // VENTA_H_INCLUDED

