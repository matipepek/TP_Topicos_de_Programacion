#ifndef ESCUDERIAS_H_INCLUDED
#define ESCUDERIAS_H_INCLUDED

#define ERROR_APERTURA -2
#define TODO_OK 1
#define BUFFER 200
#define CANT_ESTADOS_ESCUDERIAS 2
#define ERROR_NO_ENCONTRADO -5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilotos.h"

typedef struct
{
    unsigned id;
    char codigo[4];
    char nombre[30];
    char pais[50];
    int estado;     //(1: Activo, 0: inactivo)
} tEscuderia;


typedef struct {
                unsigned id;
                int indice;
}tIndiceEscuderia;


// Lote de pruebas

int crearLoteEscuderias(const char* nombrearchivo);
int escuderiasABin(const char* nombrearchivodestino, const char* nombrearchivoorigen);
void trozadoCampoVariableEscuderias(char* cadena,tEscuderia* escuderia);

void mostrarEscuderias(tEscuderia* escuderias);
char* devuelveNombreEscuderia(tEscuderia* vEscuderia, unsigned idBuscado, size_t ce); // Auxiliar Punto 4
int MostrarpilotosXEscuderia(const char* nombrearchivo1, const char* nombrearchivo2); // Punto 5
int modificarEstadoEscuderia(const char* nombrearchivo, const char* nombrearchivoindice);
int listarIndiceEscuderias(const char* nombrearchivo);
int busquedaIdEscuderia(unsigned id, const char* nombrearchivoindice);
int busquedaEstadoEscuderia(char estado);
#endif // ESCUDERIAS_H_INCLUDED
