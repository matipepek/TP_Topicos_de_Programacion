#include "carreras.h"
#include "fecha.h"

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

int registrarCarrera(const char* nombreArchivo, const char* archPilotos, const char* archEstadisticas)
{
    tCarreras carrera;
    FILE* pf;
    int i, cantPilotos; // Usamos la cantidad de pilotos totales para validar los máximos que pueden participar
    int** matriz = NULL;
    int* bloqueDatos = NULL; // Puntero auxiliar para el bloque de memoria contigua

    printf("Registro de nueva carrera\n");

    printf("ID de la carrera: ");
    scanf("%d", &carrera.id);

    while(carrera.id < 1)
    {
        printf("\nERROR - ID invalida | ID de la carrera: ");
        scanf("%d", &carrera.id);
    }
    //Limpio el salto de linea con getchar
    getchar();

    printf("\nCircuito (maximo 20 caracteres): ");
    fgets(carrera.circuito, 20, stdin);
    limpiarSalto(carrera.circuito);

    printf("\nFecha (formato AAAAMMDD): ");
    scanf("%llu", &carrera.fecha);

    while(esFechaValida(carrera.fecha) != TODO_OK)
    {
        printf("\nERROR - Fecha invalida | Fecha (formato AAAAMMDD): ");
        scanf("%llu", &carrera.fecha);
    }

    printf("\nEstado (1 - Finalizada, 0 - Suspendida): ");
    scanf("%d", &carrera.estado);

    while(carrera.estado < 0 || carrera.estado > 1)
    {
        printf("\nERROR - Estado invalido | Estado (1 - Finalizada, 0 - Suspendida): ");
        scanf("%d", &carrera.estado);
    }

    if(carrera.estado == 0)
    {
        carrera.Cant_resultados = 0;
        carrera.resultados = NULL;
    } else {
        cantPilotos = devuelveCantPilotos(archPilotos);

        printf("\nCantidad de pilotos que finalizaron/participaron: ");
        scanf("%d", &carrera.Cant_resultados);

        while(carrera.Cant_resultados < 0 || carrera.Cant_resultados > cantPilotos)
        {
            printf("\nERROR - Cantidad invalida | Cantidad de pilotos que finalizaron/participaron: ");
            scanf("%d", &carrera.Cant_resultados);
        }

        carrera.resultados = (void**)malloc(carrera.Cant_resultados * sizeof(void*));
        if(!carrera.resultados)
            return ERROR_SIN_MEMORIA;

        matriz = (int**)carrera.resultados;

        bloqueDatos = (int*)malloc(carrera.Cant_resultados * 2 * sizeof(int));
        if(!bloqueDatos)
        {
            free(carrera.resultados);
            return ERROR_SIN_MEMORIA;
        }

        matriz = (int**)carrera.resultados;

        //Conectamos cada puntero del estante a su sector en el bloque gigante
        for(i = 0; i < carrera.Cant_resultados; i++)
        {
            matriz[i] = bloqueDatos + (i * 2);
        }

        printf("\nIngreso de posiciones\n");

        for(i = 0; i < carrera.Cant_resultados; i++)
        {
            //Posicion de llegada (columna 0)
            matriz[i][0] = i + 1;

            //ID del piloto (columna 1)
            printf("Ingrese el ID del piloto que finalizo en la posicion %d: ", matriz[i][0]);
            scanf("%d", &matriz[i][1]);
        }

        int actualizacion = actualizarPuntosEstadisticas(archPilotos, archEstadisticas, carrera); // Se lleva el struct tCarrera para actualizar puntos y estadísticas de pilotos
        if(actualizacion != TODO_OK)
            printf("ERROR al actualizar estadisticas.\n");

    }

    pf = fopen(nombreArchivo, "ab");
    if (!pf)
    {
        if(carrera.estado != 0)
        {
            free(bloqueDatos);
            free(carrera.resultados);
        }
        return ERROR_APERTURA;
    }

        //Guardamos primero los campos de longitud fija
    fwrite(&carrera.id, sizeof(int), 1, pf);
    fwrite(carrera.circuito, sizeof(char), 20, pf);
    fwrite(&carrera.fecha, sizeof(unsigned long long), 1, pf);
    fwrite(&carrera.estado, sizeof(int), 1, pf);
    fwrite(&carrera.Cant_resultados, sizeof(int), 1, pf);

    fwrite(bloqueDatos, sizeof(int), carrera.Cant_resultados * 2, pf);

    if(carrera.estado != 0)
    {
        free(bloqueDatos);
        free(carrera.resultados);
    }

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

unsigned obtenerPuntos(unsigned posicion)
{
    unsigned puntos[] = {25, 18, 15, 12, 10, 8, 6, 4, 2, 1};

    if(posicion >= 1 && posicion <= 10)
    {
        return *(puntos + posicion - 1);
    }

    return 0;
}

int buscaEstadistica(FILE* archEstadisticas, unsigned id)
{
    rewind(archEstadisticas);

    tEstadisticaPiloto auxEstadistica;
    int ind = 0;

    fread(&auxEstadistica, sizeof(tEstadisticaPiloto), 1, archEstadisticas);
    while(!feof(archEstadisticas))
    {
        if(auxEstadistica.id_piloto == id)
            return ind;

        ind++;
        fread(&auxEstadistica, sizeof(tEstadisticaPiloto), 1, archEstadisticas);
    }

    return -1;
}

int actualizarPuntosEstadisticas(const char* archPilotos, const char* archEstadisticas, tCarreras vCarrera) // Actualizamos al piloto, según la cantidad que terminaron la carrera bajo la estructura de carrera ingresada
{
    FILE* pfPilotos = fopen(archPilotos, "rb+"); // Abro archivos, para leer todo de una
    FILE* pfEstadisticas = fopen(archEstadisticas, "rb+");

    if(!pfPilotos)
        return ERROR_APERTURA;

    if(!pfEstadisticas)
    {
        fclose(pfPilotos);
        return ERROR_APERTURA;
    }

    tPiloto vPiloto;
    tEstadisticaPiloto vEstadistica;

    int* pFila; // Creo puntero para acceder bien a carrera.resultados, igualmente tenemos que castearlo después, para la posición usamos *(pFila + i) y para el id *(*(pFila + i) + 1)
    int pos, posEstadistica, posPiloto, i; // Me guardo la "pos" de la matriz resultados, busco la posicion en el archivo de las estadísticas y de los pilotos para acceder por ID
    unsigned idActual; // Guardo la id actual de la matriz resultados

    for(i=0; i<vCarrera.Cant_resultados; i++)
    {
        pFila = (int*)*(vCarrera.resultados + i);
        pos = *pFila;
        idActual = (unsigned)*(pFila + 1);

        posPiloto = buscaPiloto(pfPilotos, idActual);
        posEstadistica = buscaEstadistica(pfEstadisticas, idActual);

        if(posPiloto != -1 && posEstadistica != -1) // Si encontró al piloto y si encuentra su estadística (debe existir)
        {
            fseek(pfPilotos, posPiloto * sizeof(tPiloto), SEEK_SET);
            fseek(pfEstadisticas, posEstadistica * sizeof(tEstadisticaPiloto), SEEK_SET);

            fread(&vPiloto, sizeof(tPiloto), 1, pfPilotos);
            fread(&vEstadistica, sizeof(tEstadisticaPiloto), 1, pfEstadisticas);

            if(vPiloto.estado == 'A') // Si está activo
                vPiloto.puntos_acumulados += obtenerPuntos((unsigned)pos);

            vEstadistica.carreras_corridas++;
            vEstadistica.suma_posiciones += pos;

            if(pos == 1) // Si terminó primero
                vEstadistica.victorias++;

            if(vEstadistica.carreras_corridas == 1) // Si es la primera carrera que corre
            {
                vEstadistica.mejor_posicion = pos;
                vEstadistica.peor_posicion = pos;
            } else {
                if(vEstadistica.mejor_posicion > pos)
                    vEstadistica.mejor_posicion = pos;

                if(vEstadistica.peor_posicion < pos)
                    vEstadistica.peor_posicion = pos;
            }

            fseek(pfPilotos, -1 * (long)sizeof(tPiloto), SEEK_CUR);
            fseek(pfEstadisticas, -1 * (long)sizeof(tEstadisticaPiloto), SEEK_CUR);

            fwrite(&vPiloto, sizeof(tPiloto), 1, pfPilotos);
            fwrite(&vEstadistica, sizeof(tEstadisticaPiloto), 1, pfEstadisticas);

            fflush(pfPilotos);
            fflush(pfEstadisticas); // Limpio buffers
        }
    }

    fclose(pfPilotos);
    fclose(pfEstadisticas);

    return TODO_OK;
}

int verificaPuntosStats(const char* archPilotos, const char* archEstadisticas)
{
    FILE* pfPilotos = fopen(archPilotos, "rb");
    if(!pfPilotos)
        return ERROR_APERTURA;

    FILE* pfStats = fopen(archEstadisticas, "rb");
    if(!pfStats)
    {
        fclose(pfPilotos);
        return ERROR_APERTURA;
    }


    fseek(pfPilotos, 0, SEEK_END);
    size_t tamPil = ftell(pfPilotos);
    fseek(pfPilotos, 0, SEEK_SET);

    fseek(pfStats, 0, SEEK_END);
    size_t tamStats = ftell(pfStats);
    fseek(pfStats, 0, SEEK_SET);

    size_t cePil = tamPil / sizeof(tPiloto);
    size_t ceStats = tamStats / sizeof(tEstadisticaPiloto);

    tPiloto* vPilotos = (tPiloto*)malloc(cePil * sizeof(tPiloto));
    if(!vPilotos)
        return ERROR_SIN_MEMORIA;

    tEstadisticaPiloto* vStats = (tEstadisticaPiloto*)malloc(ceStats * sizeof(tEstadisticaPiloto));
    if(!vStats)
    {
        free(vPilotos);
        return ERROR_SIN_MEMORIA;
    }

    fread(vPilotos, sizeof(tPiloto), cePil, pfPilotos);
    fread(vStats, sizeof(tEstadisticaPiloto), ceStats, pfStats);

    fclose(pfPilotos);
    fclose(pfStats);

    size_t i;
    printf("Pilotos\n\n");
    printf("%-6s | %-30s | %-6s | %-18s\n", "ID", "NOMBRE", "ESTADO", "PUNTOS ACUMULADOS");
    printf("-------------------------------------------------------------------------\n");
    for(i=0; i<cePil; i++)
    {
        printf("%-6u | %-30s | %-6c | %-18u\n", (vPilotos + i)->id, (vPilotos + i)->nombre, (vPilotos + i)->estado, (vPilotos + i)->puntos_acumulados);
    }
    printf("=========================================================================\n");
    printf("\n\n");
    printf("Stats\n\n");
    printf("%-7s | %-8s | %-11s | %-11s | %-11s | %-12s | %-8s\n",
           "ID Pil.", "Carreras", "Victorias", "Mejor Pos.", "Peor Pos.", "Suma Posoc.", "Promedio");
    printf("---------------------------------------------------------------------------------------\n");
    for(i=0; i<ceStats; i++)
    {
        printf("ID: %-4d | %-8d | %-11d | %-11d | %-11d | %-12d\n", (vStats + i)->id_piloto, (vStats + i)->carreras_corridas, (vStats + i)->victorias, (vStats + i)->mejor_posicion, (vStats + i)->peor_posicion, (vStats + i)->suma_posiciones);
    }
    printf("=======================================================================================\n");

    free(vPilotos);
    free(vStats);

    return TODO_OK;
}

int CarrerasATxt(const char* nombrearchivodestino, const char* nombrearchivoorigen)
{
    FILE* pf1 = fopen(nombrearchivoorigen, "rb");
    if(!pf1)
        return ERROR_APERTURA;

    FILE* pf2 = fopen(nombrearchivodestino, "wt");
    if(!pf2)
    {
        fclose(pf1);
        return ERROR_APERTURA;
    }

    tCarreras carrera;
    int resultado[2];

    while(fread(&carrera, sizeof(carrera), 1, pf1) == 1)
    {
        fprintf(pf2, "%d|%s|%llu|%d|%d\n",  carrera.id,
                                            carrera.circuito,
                                            carrera.fecha,
                                            carrera.estado,
                                            carrera.Cant_resultados);

        for(int i = 0; i < carrera.Cant_resultados; i++)
        {
            if(fread(resultado, sizeof(int), 2, pf1) != 2)
                {
                    fclose(pf1);
                    fclose(pf2);
                    return ERROR_ARCH_CORRUPTO;
                }

            fprintf(pf2, "%d|%d\n", resultado[0],   // posición
                                    resultado[1]);  // id piloto
        }
    }

    fclose(pf1);
    fclose(pf2);

    return TODO_OK;
}

/**
int crearLoteEstadisticas(const char* archEstadisticas)
{
    tEstadisticaPiloto vEstadisticas[] = {
    { 145 },
    { 192 },
    { 250 },
    { 264 },
    { 284 },
    { 496 },
    { 497 },
    { 500 },
    { 542 },
    { 568 },
    { 589 },
    { 599 },
    { 600 },
    { 648 },
    { 678 },
    { 700 },
    { 701 },
    { 752 },
    { 846 },
    { 873 },
    { 962 },
    { 999 }

    };

    int ce = sizeof(vEstadisticas)/sizeof(tEstadisticaPiloto);
    tEstadisticaPiloto* pStats = vEstadisticas;

    FILE* pf = fopen(archEstadisticas, "wt");
    if(!pf)
    {
        return ERROR_APERTURA;
    }
    for(int i = 0; i<ce; i++)
    {
        fprintf(pf, "%d|%d|%d|%d|%d|%d\n", pStats->id_piloto, pStats->carreras_corridas, pStats->victorias, pStats->mejor_posicion, pStats->peor_posicion, pStats->suma_posiciones);
        pStats++;
    }
    fclose(pf);
    return TODO_OK;
}

void trozadoCampoVariableEstadisticas(char* cadena, tEstadisticaPiloto* vEstadisticas)
{
    char* aux;

    aux = strchr(cadena, '\n');
    if(aux) *aux = '\0';

    aux = strrchr(cadena, '|');
    if(!aux) return;
    sscanf(aux + 1, "%d", &vEstadisticas->suma_posiciones);
    *aux = '\0';

    aux = strrchr(cadena, '|');
    if(!aux) return;
    sscanf(aux + 1, "%d", &vEstadisticas->peor_posicion);
    *aux = '\0';

    aux = strrchr(cadena, '|');
    if(!aux) return;
    sscanf(aux + 1, "%d", &vEstadisticas->mejor_posicion);
    *aux = '\0';

    aux = strrchr(cadena, '|');
    if(!aux) return;
    sscanf(aux + 1, "%d", &vEstadisticas->victorias);
    *aux = '\0';

    aux = strrchr(cadena, '|');
    if(!aux) return;
    sscanf(aux + 1, "%d", &vEstadisticas->carreras_corridas);
    *aux = '\0';

    sscanf(cadena, "%d", &vEstadisticas->id_piloto);
}

int estadisticasABin(const char* nombrearchivodestino, const char* nombrearchivoorigen)
{
    tEstadisticaPiloto vEstadisticas;
    char cadena[BUFFER];
    FILE* pf = fopen(nombrearchivoorigen, "rt");
    FILE* pf2 = fopen(nombrearchivodestino, "wb");

    if(!pf)
    {
        return ERROR_APERTURA;
    }

    if(!pf2)
    {
        fclose(pf);
        return ERROR_APERTURA;
    }

    while(fgets(cadena, BUFFER, pf))
    {
        trozadoCampoVariableEstadisticas(cadena, &vEstadisticas);
        fwrite(&vEstadisticas, sizeof(tEstadisticaPiloto), 1, pf2);
    }

    fclose(pf);
    fclose(pf2);
    return TODO_OK;
}
*/
