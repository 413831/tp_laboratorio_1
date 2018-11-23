
/**
*Funciones de ENTRADA
*/
void limpiarPantalla();
void pause();
int input(char* message,char* value,int size, int (*validation)(char*,int));
int input_ScanInt(char* mensaje);
float input_ScanFloat(char* mensaje);
char input_ScanChar(char* mensaje);
int input_getString(char input[],int size);
int input_getLetras(char input[],int size,char mensaje[],char msjError[],int reintentos);
int input_getEnteros(int* input,char mensaje[],char msjError[],int reintentos);
int input_getFloat(float* input,char mensaje[],char msjError[],int reintentos);
int input_getDNI(char input[],int size,char mensaje[],char msjError[],int reintentos);
int input_getTelefono(char input[],int size,char mensaje[],char msjError[],int reintentos);
int input_getCuit(char input[],int size,char mensaje[],char msjError[],int reintentos);
int input_getDireccion(char input[],int size,char mensaje[],char msjError[],int reintentos);
int input_getPath(char input[],int size,char mensaje[],char msjError[],int reintentos);
/**
*Funciones de CÁLCULOS
*/
float calculo_AreaCirculo(float radio);
/**
*Funciones de VALIDACION y TESTING
*/
char test_RandomInt(int desde , int hasta, int iniciar);
int validacion_Int(char* array,int size);
int validacion_Float(char* array,int size);
int validacion_Letras(char* array,int size);
int validacion_AlfaNumerico(char* array,int size);
int validacion_Telefono(char* array,int size);
int validacion_DNI(char* array,int size);
int validacion_Cuit(char* array,int size);
int validacion_File(char* array,int size);

/**
*Funciones de ORDENAMIENTO de Array
*/
void sort_Bubble(int* pArray,int size);
int sort_Selection(int* pArray, int limite, int orden);
int sort_Insertion(int* pArray, int limite, int orden);

/**
*Funciones de STRING
*/
int string_getString(char mensaje[],int size,char input[]);
int string_getStringLetras(char input[],int size,char mensaje[],char msjError[]);
int string_getStringEnteros(int* input,int size,char mensaje[],char msjError[],int minimo,int maximo);
int string_getStringFloat(float* input,int size,char mensaje[],char msjError[],int minimo,int maximo);
int string_getStringDNI(char input[],int size,char mensaje[],char msjError[],int minimo,int maximo);
void string_inicializar(char array[],int size,char valor);
