#ifndef PILOTOS_H_INCLUDED
#define PILOTOS_H_INCLUDED

#define ERROR_APERTURA -2
#define TODO_OK 1

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    unsigned id;
    char nombre[30];
    char nacionalidad[30];
    unsigned id_escuderia;
    unsigned puntos_acumulados;
    char estado;                //(A: Activo, R: Retirado, S: Suspendido)
    unsigned long long fechaNacimiento;
} tPiloto;

int CrearLotePilotos(const char* nombrearchivo);
#endif // PILOTOS_H_INCLUDED
