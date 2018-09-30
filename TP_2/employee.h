typedef struct
{
    char name[100];
    char lastName[100];
    int sector;
    float salary;
    int isEmpty;
    int id;

}Employee;

int employee_buscarIndiceLibre(Employee array[],int size);
int employee_init(Employee array[],int size,int valor);
Employee* employee_getByID(Employee array[],int size,int id);
int employee_alta(Employee array[],int size);
int employee_modificar(Employee* array,int size);
int employee_eliminar(Employee* array,int size);
int employee_sortName(Employee array[],int size,int orden);
int employee_sortSector(Employee array[],int size,int orden);
int employee_mostrar(Employee* array,int size);
int employee_listar(Employee array[],int size);
int employee_ingresoForzado(Employee array[],int size,char name[],char lastName[],int sector,float salary);
int employe_menu(Employee array[],int size);


