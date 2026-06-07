#ifndef PILOTOS_H_INCLUDED
#define PILOTOS_H_INCLUDED

#define ERROR_APERTURA -2
#define ERROR_SIN_MEMORIA -1
#define TODO_OK 1
#define BUFFER 200

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "escuderias.h"

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

void ordenamientoBurbuja(tPiloto* vPiloto, size_t ce); // Necesitado para el punto 4.


int crearLotePilotos(const char* nombrearchivo);
int pilotosABin(const char* nombrearchivodestino, const char* nombrearchivoorigen);
void trozadoCampoVariablePilotos(char* cadena,tPiloto* piloto);
void mostrarPilotos(tPiloto* pilotos);
char* devuelveNombreEscuderia(tEscuderia* vEscuderia, unsigned idBuscado, size_t ce);


int listarPilotosyPuntos(const char* nombrearchivo); // Punto 1


int mostrarRankingPilotos(const char* archPilotos, const char* archEscuderias); // Punto 4
#endif // PILOTOS_H_INCLUDED
