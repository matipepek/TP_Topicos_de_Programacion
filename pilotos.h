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
#include "carreras.h"

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

// Lote de pruebas
int crearLotePilotos(const char* nombrearchivo);
int pilotosABin(const char* nombrearchivodestino, const char* nombrearchivoorigen);
void trozadoCampoVariablePilotos(char* cadena,tPiloto* piloto); // Auxiliar lote de prueba

void mostrarPilotos(tPiloto* pilotos); // Auxiliar
int listarPilotosyPuntos(const char* nombrearchivo); // Punto 1
int mostrarRankingPilotos(const char* archPilotos, const char* archEscuderias); // Punto 4
int buscaPiloto(FILE* archPiloto, unsigned id); // Auxiliar Punto 3
int listarEstadistica(const char* nombrearchivo);
int devuelveCantPilotos(const char* archPilotos);
#endif // PILOTOS_H_INCLUDED
