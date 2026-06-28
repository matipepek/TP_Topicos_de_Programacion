#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

#define ERROR_APERTURA -2
#define ERROR_SIN_MEMORIA -1
#define TODO_OK 1
#define ERROR_ARCH_CORRUPTO -3
#define FECHA_INVALIDA -4

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    unsigned int dia;
    unsigned int mes;
    unsigned int anio;
} tFecha;

tFecha descomponeFecha(unsigned long long fecha);
int esBisiesto(unsigned int anio);
int esDiaValido(unsigned int dia, unsigned int mes, int bisiesto);
int esFechaValida(unsigned long long fecha);

#endif // FECHA_H_INCLUDED
