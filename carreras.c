#include "carreras.h"
#include <stdio.h>
#include <stdlib.h>

void limpiarSalto(char* cadena)
{
    while (*cadena != '\0')
    {
        if (*cadena == '\n')
        {
            *cadena = '\0';
            break;
        }
        cadena++;
    }
}

int registrarCarrera(const char* nombreArchivo)
{
    tCarreras carrera;
    FILE* pf;
    int i;
    int* pFila;

    printf("Registro de nueva carrera\n");

    printf("ID de la carrera: ");
    scanf("%d", &carrera.id);
    getchar();

    printf("\nCircuito: ");
    fgets(carrera.circuito, 20, stdin);
    limpiarSalto(carrera.circuito);

    printf("\nFecha (formato AAAAMMDD): ");
    scanf("%llu", &carrera.fecha);

    printf("\nEstado (1 - Finalizada, 0 - Suspendida): ");
    scanf("%d", &carrera.estado);

    printf("\nCantidad de pilotos que finalizaron/participaron: ");
    scanf("%d", &carrera.Cant_resultados);

    carrera.resultados = (void**)malloc(carrera.Cant_resultados * sizeof(void*));
    if(!carrera.resultados)
    {
        return ERROR_SIN_MEMORIA;
    }

    printf("\nIngreso de posiciones\n");

    for(i = 0; i < carrera.Cant_resultados; i++)
    {
        //Asignamos memoria para dos enteros por fila: posicion y id piloto
        *(carrera.resultados + i) = malloc(2 * sizeof(int));
        if(!*(carrera.resultados + i))
        {
            return ERROR_SIN_MEMORIA;
        }

        pFila = (int*)*(carrera.resultados + i);
        *pFila = i + 1; //Columna 0 : Posicion de llegada

        printf("Ingrese el ID del piloto que finalizo en la posicion %d: ", *pFila);
        scanf("%d", pFila + 1); //Columna 1: ID Piloto ingresado directamente en su offset
    }

    pf = fopen(nombreArchivo, "ab");
    if (!pf)
    {
        return ERROR_APERTURA;
    }

    //Guardamos primero los campos de longitud fija
    fwrite(&carrera.id, sizeof(int), 1, pf);
    fwrite(carrera.circuito, sizeof(char), 20, pf);
    fwrite(&carrera.fecha, sizeof(unsigned long long), 1, pf);
    fwrite(&carrera.estado, sizeof(int), 1, pf);
    fwrite(&carrera.Cant_resultados, sizeof(int), 1, pf);

    //Guardamos el contenido de la matriz dinámica fila por fila
    for(i = 0; i < carrera.Cant_resultados; i++)
    {
        pFila = (int*)*(carrera.resultados + i);
        fwrite(pFila, sizeof(int), 2, pf);

        free(*(carrera.resultados + i));
    }

    free(carrera.resultados);
    fclose(pf);

    printf("\nCarrera registrada y guardada exitosamente en %s.\n", nombreArchivo);
    return TODO_OK;
}

void verificarCarrerasDat(const char* nombreArchivo) {
    FILE* pf;
    int id, estado, Cant_resultados;
    char circuito[20];
    unsigned long long fecha;
    int fila[2]; /* Para leer [Posición, ID_Piloto] */
    int i;

    pf = fopen(nombreArchivo, "rb");
    if (!pf) {
        printf("Error: No se pudo abrir el archivo %s para lectura.\n", nombreArchivo);
        return;
    }

    printf("\n--- Contenido de %s ---\n", nombreArchivo);

    /* Leemos bloque por bloque hasta el final del archivo */
    while (fread(&id, sizeof(int), 1, pf) == 1) {
        /* Si pudimos leer el ID, leemos el resto de los campos fijos */
        fread(circuito, sizeof(char), 20, pf);
        fread(&fecha, sizeof(unsigned long long), 1, pf);
        fread(&estado, sizeof(int), 1, pf);
        fread(&Cant_resultados, sizeof(int), 1, pf);

        printf("\nID Carrera: %d\n", id);
        printf("Circuito: %s\n", circuito);
        printf("Fecha: %llu\n", fecha);
        printf("Estado: %d\n", estado);
        printf("Cant. Resultados: %d\n", Cant_resultados);
        printf("Posiciones:\n");

        /* Iteramos según la cantidad de resultados para leer la matriz aplanada */
        for (i = 0; i < Cant_resultados; i++) {
            fread(fila, sizeof(int), 2, pf);
            printf("  - Posicion %d: Piloto ID %d\n", fila[0], fila[1]);
        }
        printf("-----------------------------------\n");
    }

    fclose(pf);
}