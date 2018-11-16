#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    float sueldo;
}Employee;

typedef int (*function_type)(void* thisA,void* thisB);

Employee* employee_new();
Employee* employee_newConParametros(char* id,char* nombre,char* horasTrabajadas,char* sueldo);
Employee* employee_getById(void* pArrayListEmployee,int idIngresado);
int employee_add(void* pArrayListEmployee);
int employee_remove(void* pArrayListEmployee);
int employee_delete(Employee* this);
int employee_edit(void* pArrayListEmployee);
int employee_modify(Employee* this,
                        char* mensaje,
                        int (*validacion)(char*),
                        int (*set)(Employee*,char*));
int employee_show(Employee* this);
int employee_sort(void* pArrayListEmployee);
int employee_hardcode(void* pArrayListEmployee,char *bufferName,char* bufferHorasTrabajadas,char* bufferSueldo);

int employee_setId(Employee* this,char* id);
int employee_getId(Employee* this,int* id);

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setHorasTrabajadas(Employee* this,char* horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

int employee_setSueldo(Employee* this,char* sueldo);
int employee_getSueldo(Employee* this,float* sueldo);

int employee_setAll(Employee* this,char* id,char* name,char* hours,char* salary);
int employee_getAll(Employee* this,char* name,int* hours,float* salary,int* id);

void* employee_selectorCriterio();
int employee_criterioNombre(void* thisA,void* thisB);
int employee_criterioSueldo(void* thisA,void* thisB);
int employee_criterioHoras(void* thisA,void* thisB);
int employee_criterioId(void* thisA,void* thisB);

int employee_searchEmpty(Employee* array[]);
#endif // employee_H_INCLUDED
