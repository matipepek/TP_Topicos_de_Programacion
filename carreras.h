#ifndef CARRERAS_H_INCLUDED
#define CARRERAS_H_INCLUDED

#define ERROR_APERTURA -2
#define ERROR_SIN_MEMORIA -1
#define TODO_OK 1

#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int id;
    char circuito[20];
    unsigned long long fecha;
    int estado;
    int Cant_resultados;
    void** resultados;  //Matriz que contenga los resultados
} tCarreras;

typedef struct
{
    int id_piloto;
    int carreras_corridas;
    int victorias;
    int mejor_posicion;
    int peor_posicion;
    int suma_posiciones;
} tEstadisticaPiloto;

void limpiarSalto(char* cadena);
int registrarCarrera(const char* nombreArchivo);
void verificarCarrerasDat(const char* nombreArchivo);

#endif // CARRERAS_H_INCLUDED
