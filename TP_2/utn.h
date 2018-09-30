/**
*Funciones de ENTRADA
*/
int input_ScanInt(char* mensaje,int* numero);
float input_ScanFloat(char* mensaje,float* numero);
char input_ScanChar(char* mensaje,char* caracter);
int input_getString(char mensaje[],int size,char input[]);
int input_getLetras(char input[],int size,char mensaje[],char msjError[],int reintentos);
int input_getNumeros(int* input,int size,char mensaje[],char msjError[],int minimo,int maximo,int reintentos);
int input_getFloat(float* input,int size,char mensaje[],char msjError[],float minimo,float maximo,int reintentos);
int input_getDNI(char input[],int size,char mensaje[],char msjError[],int reintentos);
int input_getTelefono(char input[],int size,char mensaje[],char msjError[],int reintentos);
int input_getCuit(char input[],int size,char mensaje[],char msjError[],int reintentos);
int input_getAlfanumerico(char input[],int size,char mensaje[],char msjError[],int reintentos);

void limpiarMemoria();
void limpiarPantalla();
/**
*Funciones de CÁLCULOS
*/
float calculo_AreaCirculo(float radio);
/**
*Funciones de VALIDACION y TESTING
*/
char test_RandomInt(int desde , int hasta, int iniciar);
int validacion_Letras(char* array,int size);
int validacion_Int(char* array,int size);
int validacion_AlfaNumerico(char* array,int size);
int validacion_Telefono(char* array,int size);
int validacion_Float(char* array,int size);
int validacion_DNI(char* array,int size);
int validacion_Cuit(char* array,int size);

/**
*Funciones de LISTADOS
*/
void array_mostrarInt(int* pArray,int indice,int size,char* pMensaje);

/**
*Funciones de ORDENAMIENTO de Array
*/
void sort_Bubble(int* pArray,int size);
int sort_Selection(int* pArray, int limite, int orden);
int sort_Insertion(int* pArray, int limite, int orden);
