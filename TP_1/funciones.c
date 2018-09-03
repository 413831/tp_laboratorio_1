#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

static void limpiarMemoria()
{
    __fpurge(stdin);
    //fflush(stdin);
}

/**
*\brief Se solicita ingresar un caracter al usuario
*\param caracterAuxiliar Puntero del caracter ingresado
*\param mensaje Mensaje que se muestra al usuario para ingresar caracter
*\return Retorna 0 si es correcto si es incorrecto retorna -1
*/
char getCaracter(char * caracterAuxiliar,char * mensaje)
{
    limpiarMemoria();
    printf(mensaje);
    scanf("%c",caracterAuxiliar);
    return 0;
}

/**
*\brief Se solicita ingresar un número con o sin decimales al usuario
*\param numeroAuxiliar Puntero del número ingresado
*\return Retorna 0 si es correcto si es incorrecto retorna -1
*/

float getNumero(float * numeroAuxiliar)
{
    limpiarMemoria();
    printf("Ingrese un número: ");
    scanf("%f",numeroAuxiliar);
    return 0;
}

/**
*\brief Sumar dos numeros ingresados por el usuario
*\param auxiliarUno Valor del primer numero a sumar
*\param auxiliarDos Valor del segundo numero a sumar
*\return Retorna el resultado de la suma
*/

float funcionSuma(float auxiliarUno,float auxiliarDos)
{
    float resultado;
    resultado = auxiliarUno + auxiliarDos;
    printf("\nEl resultado de la suma %.2f + %.2f es: %.2f",auxiliarUno,auxiliarDos,resultado);
    return resultado;
}

/**
*\brief Restar dos numeros ingresados por el usuario
*\param auxiliarUno Valor del primer numero a restar
*\param auxiliarDos Valor del segundo numero a restar
*\return Retorna el resultado de la resta
*/

float funcionResta(float auxiliarUno,float auxiliarDos)
{
    float resultado;
    resultado = auxiliarUno - auxiliarDos;
    printf("\nEl resultado de la resta %.2f - %.2f es: %.2f",auxiliarUno,auxiliarDos,resultado);
    return resultado;
}

/**
*\brief Multiplicar dos numeros ingresados por el usuario
*\param auxiliarUno Valor del primer numero a multiplicar
*\param auxiliarDos Valor del segundo numero a multiplicar
*\return Retorna el resultado de la multiplicación
*/

float funcionMultiplicar(float auxiliarUno,float auxiliarDos)
{
    float resultado;
    resultado = auxiliarUno * auxiliarDos;
    printf("\nEl resultado de la multiplicación %.2f * %.2f es: %.2f",auxiliarUno,auxiliarDos,resultado);
    return resultado;
}

/**
*\brief Dividir dos numeros ingresados por el usuario
*\param auxiliarUno Valor del primer numero a dividir
*\param auxiliarDos Valor del segundo numero a dividir
*\return Retorna el resultado de la división
*/

float funcionDividir(float auxiliarUno,float auxiliarDos)
{
    float resultado;

    if(auxiliarUno != 0 && auxiliarDos != 0)
    {
        resultado = auxiliarUno / auxiliarDos;
        printf("\nEl resultado de la división %.2f  / %.2f es: %.2f",auxiliarUno,auxiliarDos,resultado);
        return resultado;
    }
    else
    {
        printf("\nError. No se puede dividir por 0 (cero) ");
        return -1;
    }

}

/**
*\brief Se calcula el factorial de un número ingresado por el usuario
*\param auxiliarUno
*\return Retorna el valor del factorial del numero ingresado
*/

float funcionFactorial(float auxiliarUno)
{
    float resultado = 0;

    if(auxiliarUno==1 || auxiliarUno == 0)
    {
        return 1;
    }

    resultado=auxiliarUno* funcionFactorial(auxiliarUno-1);
    return resultado;
}

/**
*\brief Función que agrupa y ejecuta todos los cálculos básicos
*\param auxiliarUno Primer número para realizar los cálculos
*\param auxiliarDos Segundo número para realizar los cálculos
*\return Retorna 0 si es correcto y -1 si es incorrecto
*/

int funcionCalculos(float auxiliarUno,float auxiliarDos)
{
    float resultadoFactorial;

    funcionSuma(auxiliarUno,auxiliarDos);
    funcionResta(auxiliarUno,auxiliarDos);
    funcionMultiplicar(auxiliarUno,auxiliarDos);
    funcionDividir(auxiliarUno,auxiliarDos);
    resultadoFactorial = funcionFactorial(auxiliarUno);
    printf("\nEl factorial de %.2f es: %.2f",auxiliarUno,resultadoFactorial);
    resultadoFactorial = funcionFactorial(auxiliarDos);
    printf("\nEl factorial de %.2f es: %.2f",auxiliarDos,resultadoFactorial);
    return 0;
}

/**
*\brief Crear un menú con 5 calculos para dos números ingresados por el usuario hasta que no quiera ingresar más
*\param void
*\return Retorna 0 si esta bien, sino retorna -1
*/

int menuCalculosDosNumeros()
{
    float numeroUno;
    float numeroDos;
    char opcion;

    do
    {
        printf("\nIngrese dos numeros para calcular\n\n1) Suma\n2) Resta\n3) Multiplicación\n4) División\n5) Factorial\n\n");
        getNumero(&numeroUno);
        getNumero(&numeroDos);

        funcionCalculos(numeroUno,numeroDos);

        getCaracter(&opcion,"\n\n¿Continuar? S/N ");
    }while(opcion == 'S' || opcion == 's');
    return 0;
}