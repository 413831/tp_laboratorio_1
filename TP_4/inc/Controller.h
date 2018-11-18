#include "../inc/LinkedList.h"
#include "../inc/Employee.h"

int controller_loadFromText(char* path , LinkedList* pLinkedList);
int controller_loadFromBinary(char* path , LinkedList* pLinkedList);
int controller_addEmployee(LinkedList* pLinkedList);
int controller_editEmployee(LinkedList* pLinkedList);
int controller_removeEmployee(LinkedList* pListActives,LinkedList* pListInactives);
int controller_ListEmployee(LinkedList* pLinkedList);

int controller_generateNewList(LinkedList* pLinkedList,LinkedList* listaPrincipal[]);
int controller_sortEmployee(LinkedList* pLinkedList);
int controller_saveAsText(char* path , LinkedList* pLinkedList);
int controller_saveAsBinary(char* path , LinkedList* pLinkedList);
int controller_init();
