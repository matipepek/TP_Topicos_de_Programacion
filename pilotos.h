#ifndef PILOTOS_H_INCLUDED
#define PILOTOS_H_INCLUDED

#define ERROR_APERTURA -2
#define ERROR_SIN_MEMORIA -1
#define ERROR_NO_ENCONTRADO -5
#define TODO_OK 1
#define BUFFER 200
#define CANT_ESTADOS_PILOTOS 3

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

typedef struct {
                unsigned id;
                int indice;
}tIndicePiloto;

typedef struct {
            unsigned id;
            char nombre[30];
            char entidad[20];
} tBajas;

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

int modificarEstadoPiloto(const char* nombrearchivo, const char* nombrearchivoindice);
int listarIndicePilotos(const char* nombrearchivo);
int busquedaIdPiloto(unsigned id, const char* nombrearchivoindice);
int busquedaEstadoPiloto(char estado);
int verBajas(const char *nombrearchivo);

int devuelveCantPilotos(const char* archPilotos);

//Indice persistente
int generarIndiceOrdenadoPilotos(const char* archPilotos, const char* archIdx);
int busquedaBinariaPiloto(unsigned idBuscado, const char* archIdx);

int cuentaPilotosXEscuderia(FILE* archPilotos, unsigned id);
int modificaDatosPiloto(const char* archPiloto, const char* archIdxPiloto, const char* archIdxEscuderia);

#endif // PILOTOS_H_INCLUDED
