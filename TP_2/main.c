#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"
#include "utn.h"

#define QTY_EMPLOYEES 1000


int main()
{
    Employee arrayEmpleados[QTY_EMPLOYEES];
    employe_menu(arrayEmpleados,QTY_EMPLOYEES);
    return 0;
}
