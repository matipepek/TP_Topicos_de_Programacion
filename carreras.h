#ifndef CARRERAS_H_INCLUDED
#define CARRERAS_H_INCLUDED

#define ERROR_APERTURA -2
#define ERROR_SIN_MEMORIA -1
#define TODO_OK 1
#define ERROR_ARCH_CORRUPTO -3

#include <stdio.h>
#include <stdlib.h>
#include "pilotos.h"

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
int registrarCarrera(const char* nombreArchivo, const char* archPilotos, const char* archEstadisticas); // Punto 2
void verificarCarrerasDat(const char* nombreArchivo);
unsigned obtenerPuntos(unsigned posicion); // Auxiliar Punto 3
int buscaEstadistica(FILE* archEstadisticas, unsigned id); // Auxiliar Punto 3
int actualizarPuntosEstadisticas(const char* archPilotos, const char* archEstadisticas, tCarreras vCarrera); // Punto 3 + Sistema incremental de estadísticas
int verificaPuntosStats(const char* archPilotos, const char* archEstadisticas); // Auxiliar Punto 3 (se puede borrar)
int CarrerasATxt(const char* nombrearchivodestino, const char* nombrearchivoorigen); // punto 7

/** // Lote de pruebas para estadisticas, se puede borrar
int crearLoteEstadisticas(const char* archEstadisticas);
int estadisticasABin(const char* nombrearchivodestino, const char* nombrearchivoorigen);
void trozadoCampoVariableEstadisticas(char* cadena, tEstadisticaPiloto* vEstadisticas); **/

#endif // CARRERAS_H_INCLUDED
