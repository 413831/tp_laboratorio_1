#include "LinkedList.h"
#include "Venta.h"

int controller_loadFromText(char* path , LinkedList* pLinkedList);
int controller_loadFromBinary(char* path , LinkedList* pLinkedList);
int controller_addPeople(LinkedList* pLinkedList);
int controller_editPeople(LinkedList* pLinkedList);
int controller_removePeople(LinkedList* listaPrincipal[]);
int controller_ListPeople(LinkedList* pLinkedList);
int controller_insertPeople(LinkedList* listaPrincipal[]);
int controller_generateNewList(LinkedList* listaPrincipal);
int controller_undoList(LinkedList* listaPrincipal[]);
int controller_sortPeople(LinkedList* pLinkedList);
int controller_saveAsText(char* path , LinkedList* pLinkedList);
int controller_saveAsBinary(char* path , LinkedList* pLinkedList);
int controller_init();
