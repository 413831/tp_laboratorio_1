#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED


typedef struct
{
    char nombre[50];
    char apellido[50];
    char cuit[15];
    //------------
    int id;
    int isEmpty;
}Cliente;


int cliente_buscarIndiceLibre(Cliente array[],int size);
int cliente_init(Cliente array[],int size,int valor);
Cliente* cliente_getByID(Cliente* array,int size,int id);
int cliente_alta(Cliente* array,int size,int* index);
int cliente_modificar(Cliente* array);
int cliente_eliminar(Cliente* array);
int cliente_ordenar(Cliente array[],int size);
int cliente_mostrar(Cliente* array);
int cliente_listar(Cliente array[],int size);
int cliente_ingresoForzado(Cliente array[],int size,char auxNombre[],char auxApellido[],char auxCuit[]);


//int proximoId();
//int pantalla_buscarPorId(Pantalla* array,int size, int id);

#endif // CLIENTES_H_INCLUDED

