#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

/**
*\brief Ingresar un caracter por el usuario
*\param caracterAuxiliar Puntero del caracter ingresado
*\param mensaje Mensaje que se muestra al usuario para ingresar caracter
*\return Retorna 0 si es correcto si es incorrecto retorna -1
*/
char getCaracter(char * caracterAuxiliar,char * mensaje)
{
    //__fpurge(stdin);
    fflush(stdin);
    printf(mensaje);
    scanf("%c",caracterAuxiliar);
    return 0;

}

/**
*\brief Ingresar un número por el usuario
*\param numeroAuxiliar Puntero del número ingresado
*\return Retorna 0 si es correcto si es incorrecto retorna -1
*/

float getNumero(float * numeroAuxiliar)
{
    //__fpurge(stdin);
    fflush(stdin);
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
     //__fpurge(stdin);
    fflush(stdin);
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
     //__fpurge(stdin);
    fflush(stdin);
    resultado = auxiliarUno - auxiliarDos;
    printf("\nEl resultado de la resta %.2f - %.2f es: %.2f",auxiliarUno,auxiliarDos,resultado);
    return resultado;

}


/**
*\brief Multiplicar dos numeros ingresados por el usuario
*\param auxiliarUno Valor del primer numero a multiplicar
*\param auxiliarDos Valor del segundo numero a multiplicar
*\return Retorna el resultado de la multiplición
*/

float funcionMultiplicar(float auxiliarUno,float auxiliarDos)
{
    float resultado;
    //__fpurge(stdin);
    fflush(stdin);
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
     //__fpurge(stdin);
    fflush(stdin);
    if(auxiliarUno != 0 && auxiliarDos != 0)
    {resultado = auxiliarUno / auxiliarDos;
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
*\brief Se utiliza un numero para calcular el factorial del mismo iterando hasta llegar a uno
*\param auxiliarUno
*\return Retorna el valor del factorial del numero ingresado
*/

float funcionFactorial(float auxiliarUno)
{
     //__fpurge(stdin);
    fflush(stdin);
    float resultado;
    //   4        =     4                  4           == 1       4 - 1
    if(auxiliarUno==1)
    {
    return 1;
    }
    resultado=auxiliarUno* funcionFactorial(auxiliarUno-1);
    printf("\nEl factorial de %.2f es: %.2f",auxiliarUno,resultado);
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
    funcionSuma(auxiliarUno,auxiliarDos);
    funcionResta(auxiliarUno,auxiliarDos);
    funcionMultiplicar(auxiliarUno,auxiliarDos);
    funcionDividir(auxiliarUno,auxiliarDos);
    return 0;
}

/**
*\brief Crear un menú con 5 calculos para dos numeros ingresados por el usuario hasta que no quiera ingresar más
*\param void
*\return Retorna 0 si esta bien, si no retorna -1
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
