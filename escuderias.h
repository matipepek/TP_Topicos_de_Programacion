#ifndef ESCUDERIAS_H_INCLUDED
#define ESCUDERIAS_H_INCLUDED

#define ERROR_APERTURA -2
#define TODO_OK 1
#define BUFFER 200

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

int crearLoteEscuderias(const char* nombrearchivo);
int escuderiasABin(const char* nombrearchivodestino, const char* nombrearchivoorigen);
void trozadoCampoVariableEscuderias(char* cadena,tEscuderia* escuderia);
void mostrarEscuderias(tEscuderia* escuderias);
char* devuelveNombreEscuderia(tEscuderia* vEscuderia, unsigned idBuscado, size_t ce);
int MostrarpilotosXEscuderia(const char* nombrearchivo1, const char* nombrearchivo2);
#endif // ESCUDERIAS_H_INCLUDED
