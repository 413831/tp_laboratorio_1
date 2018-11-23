#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "utn.h"
#include "Venta.h"
#include "parser.h"
#include "Controller.h"

int main()
{
    int counter;
    LinkedList* listadoVentas = ll_newLinkedList();

    controller_loadFromText("data.csv",listadoVentas);
    counter = ll_len(listadoVentas);
   // controller_ListVenta(listadoVentas);
    printf("\nLEN %d",counter);
    controller_generateNewList(listadoVentas);

   return 0;
}
