#include "pilotos.h"


void ordenamientoBurbuja(tPiloto* vPiloto, size_t ce)
{
    size_t i, j;
    tPiloto auxPiloto;

    for(i=0; i<ce - 1; i++)
    {
        for(j=0; j<ce - i - 1; j++)
        {
            if(((vPiloto + j)->puntos_acumulados) < ((vPiloto + j + 1)->puntos_acumulados))
            {
                auxPiloto = *(vPiloto + j);
                *(vPiloto + j) = *(vPiloto + j + 1);
                *(vPiloto + j + 1) = auxPiloto;
            }
        }
    }
}

int crearLotePilotos(const char* nombrearchivo)
{
    tPiloto Pilotos[] = {
    {145,  "Lando Norris",      "Reino Unido", 1, 0, 'R', 19991113},
    {192,  "Oscar Piastri",     "Australia",   1, 0, 'A', 20010406},

    {250,  "George Russell",    "Reino Unido", 2, 0, 'A', 19980215},
    {264,  "Kimi Antonelli",    "Italia",      2, 0, 'S', 20060825},

    {284,  "Charles Leclerc",   "Monaco",      3, 0, 'A', 19971016},
    {496,  "Lewis Hamilton",    "Reino Unido", 3, 0, 'A', 19850107},

    {497,  "Max Verstappen",    "Paises Bajos",4, 0, 'A', 19970930},
    {500,  "Isack Hadjar",      "Francia",     4, 0, 'A', 20040928},

    {542,  "Fernando Alonso",   "Espania",      5, 0, 'R', 19810729},
    {568, "Lance Stroll",      "Canada",      5, 0, 'A', 19981029},

    {589, "Carlos Sainz",      "Espania",      6, 0, 'A', 19940901},
    {599, "Alexander Albon",   "Tailandia",   6, 0, 'A', 19960323},

    {600, "Pierre Gasly",      "Francia",     7, 0, 'A', 19960207},
    {648, "Franco Colapinto",  "Argentina",   7, 0, 'A', 20030527},

    {678, "Esteban Ocon",      "Francia",     8, 0, 'S', 19960917},
    {700, "Oliver Bearman",    "Reino Unido", 8, 0, 'A', 20050508},

    {701, "Liam Lawson",       "Nueva Zelanda",9, 0, 'A', 20020211},
    {752, "Arvid Lindblad",    "Reino Unido", 9, 0, 'A', 20070808},

    {846, "Nico Hulkenberg",   "Alemania",    10, 0, 'A', 19870819},
    {873, "Gabriel Bortoleto", "Brasil",      10, 0, 'A', 20041014},

    {962, "Sergio Perez",      "Mexico",      11, 0, 'R', 19900126},
    {999, "Valtteri Bottas",   "Finlandia",   11, 0, 'R', 19890828}
    };

    int ce = sizeof(Pilotos)/sizeof(tPiloto);
    tPiloto *pPilotos = Pilotos;

    FILE* pf = fopen(nombrearchivo, "wt");
    if(!pf)
    {
        return ERROR_APERTURA;
    }
    for(int i = 0; i<ce; i++)
    {
        fprintf(pf, "%u|%s|%s|%u|%u|%c|%llu\n", pPilotos->id, pPilotos->nombre, pPilotos->nacionalidad, pPilotos->id_escuderia, pPilotos->puntos_acumulados, pPilotos->estado, pPilotos->fechaNacimiento);
        pPilotos++;
    }
    fclose(pf);
    return TODO_OK;
}

int pilotosABin(const char* nombrearchivodestino, const char* nombrearchivoorigen)
{
    tPiloto Pilotos;
    tEstadisticaPiloto Estadistica;
    tIndicePiloto Indice;
    unsigned cont = 0;
    char cadena[BUFFER];
    FILE* pf = fopen(nombrearchivoorigen, "rt");
    FILE* pf2 = fopen(nombrearchivodestino, "wb");
    FILE* pf3 = fopen ("estadisticas.bin", "wb");
    FILE* pf4 = fopen ("indicepilotos.bin", "wb");

    if(!pf)
    {
        return ERROR_APERTURA;
    }

    if(!pf2)
    {
        fclose(pf);
        return ERROR_APERTURA;
    }

    if(!pf3)
    {
        fclose(pf);
        fclose(pf2);
        return ERROR_APERTURA;
    }

    if(!pf4)
    {
        fclose(pf);
        fclose(pf2);
        fclose(pf3);
        return ERROR_APERTURA;
    }

    while(fgets(cadena, BUFFER, pf))
    {
        trozadoCampoVariablePilotos(cadena, &Pilotos);
        Estadistica.id_piloto = Pilotos.id;
        Estadistica.carreras_corridas = 0;
        Estadistica.mejor_posicion = 0;
        Estadistica.peor_posicion = 0;
        Estadistica.suma_posiciones = 0;
        Estadistica.victorias = 0;

        Indice.id = Pilotos.id;
        Indice.indice = cont;
        cont++;

        mostrarPilotos(&Pilotos);
        fwrite(&Estadistica, sizeof(Estadistica),1, pf3);
        fwrite(&Indice, sizeof(Indice), 1, pf4);
        fwrite(&Pilotos, sizeof(Pilotos), 1, pf2);
    }

    fclose(pf);
    fclose(pf2);
    fclose(pf3);
    fclose(pf4);
    return TODO_OK;
}

void trozadoCampoVariablePilotos(char* cadena,tPiloto* piloto)
{
    char * aux;
    aux = strchr(cadena, '\n');
    *aux = '\0';
    aux = strrchr(cadena, '|');
    sscanf(aux+1,"%llu",&piloto->fechaNacimiento);
    *aux = '\0';
    aux = strrchr(cadena, '|');
    sscanf(aux+1,"%c",&piloto->estado);
    *aux = '\0';
    aux = strrchr(cadena, '|');
    sscanf(aux+1,"%u",&piloto->puntos_acumulados);
    *aux = '\0';
    aux = strrchr(cadena, '|');
    sscanf(aux+1,"%u",&piloto->id_escuderia);
    *aux = '\0';
    aux = strrchr(cadena, '|');
    strcpy(piloto->nacionalidad, aux+1);
    *aux = '\0';
    aux = strrchr(cadena, '|');
    strcpy(piloto->nombre, aux+1);
    *aux = '\0';
    sscanf(cadena,"%u",&piloto->id);
}

void mostrarPilotos(tPiloto* pilotos)
{
        printf("%u|%s|%s|%u|%u|%c|%llu\n",  pilotos->id,
                                            pilotos->nombre,
                                            pilotos->nacionalidad,
                                            pilotos->id_escuderia,
                                            pilotos->puntos_acumulados,
                                            pilotos->estado,
                                            pilotos->fechaNacimiento);
}

// 1. listar pilotos y sus puntos

int listarPilotosyPuntos(const char* nombrearchivo)
{
    tPiloto piloto;

    FILE* pf = fopen(nombrearchivo, "rb");
    if(!pf)
        return ERROR_APERTURA;
    rewind(pf);
    printf("\n=====================================\n");
    printf("%-25s | %8s\n", "Piloto", "Puntos");
    printf("=====================================\n");

    fread(&piloto, sizeof(tPiloto),1,pf);
    while(!feof(pf))
    {
        if(piloto.estado == 'A')
        {
            printf("%-25s | %8u\n",     piloto.nombre,
                                        piloto.puntos_acumulados);
        }
        fread(&piloto, sizeof(tPiloto),1,pf);
    }
    printf("=====================================\n");
    fclose(pf);
    return TODO_OK;
}

// 4. Mostrar ranking de pilotos (ordenado) de la temporada en cuestión.

int mostrarRankingPilotos(const char* archPilotos, const char* archEscuderias)
{
    int cantActivos = 0, i;
    FILE* pPilotos = fopen(archPilotos, "rb"); // Abro archivo para plasmar los datos en un vector dinámico.
    FILE* pEscuderias = fopen(archEscuderias, "rb"); // Abro archivo para plasmar los datos en un vector dinámico, y buscar el nombre de escudería por id.

    if(!pPilotos)
        return ERROR_APERTURA;

    if(!pEscuderias)
    {
        fclose(pPilotos);
        return ERROR_APERTURA;
    }

    fseek(pPilotos, 0, SEEK_END);
    size_t tam = ftell(pPilotos);
    fseek(pPilotos, 0, SEEK_SET);

    fseek(pEscuderias, 0, SEEK_END);
    size_t tamEsc = ftell(pEscuderias);
    fseek(pEscuderias, 0, SEEK_SET);

    size_t ce = tam / sizeof(tPiloto);
    size_t ceEsc = tamEsc / sizeof(tEscuderia);

    tPiloto* vPiloto = (tPiloto*)malloc(ce * sizeof(tPiloto));
    if(!vPiloto)
    {
        fclose(pPilotos);
        return ERROR_SIN_MEMORIA;
    }

    tPiloto vAuxPiloto; // Creo un auxiliar para filtrar los activos de los retirados.

    fread(&vAuxPiloto, sizeof(tPiloto), 1, pPilotos);
    while(!feof(pPilotos))
    {
        if(vAuxPiloto.estado == 'A')
        {
            *(vPiloto + cantActivos) = vAuxPiloto;
            cantActivos++;
        }

        fread(&vAuxPiloto, sizeof(tPiloto), 1, pPilotos);
    }

    fclose(pPilotos);

    tEscuderia* vEscuderia = (tEscuderia*)malloc(ceEsc * sizeof(tEscuderia));
    if(!vEscuderia)
    {
        fclose(pEscuderias);
        free(vPiloto);
        return ERROR_SIN_MEMORIA;
    }

    fread(vEscuderia, sizeof(tEscuderia), ceEsc, pEscuderias);

    fclose(pEscuderias);

    ordenamientoBurbuja(vPiloto, cantActivos);

    printf("\n---- %35s %25s\n", "Ranking de Pilotos", "----");
    printf("\n%-4s | %-25s | %-20s | %-7s\n", "N", "Nombre", "Escuderia", "Puntaje");
    printf("------------------------------------------------------------------\n");

    for(i=0; i<cantActivos; i++)
    {
        printf("%-4d | %-25s | %-20s | %-7u\n", i + 1, (vPiloto + i)->nombre, devuelveNombreEscuderia(vEscuderia, (vPiloto + i)->id_escuderia, ceEsc), (vPiloto + i)->puntos_acumulados);
    }

    free(vPiloto);
    free(vEscuderia);

    return TODO_OK;
}

int buscaPiloto(const tPiloto* vPiloto, int cantPilotos, unsigned id)
{
    int i;

    for(i=0; i<cantPilotos; i++)
    {
        if((vPiloto + i)->id == id)
            return i;
    }

    return -1;
}

int listarEstadistica(const char* nombrearchivo)
{
    tEstadisticaPiloto Estadisticas;

    FILE* pf = fopen(nombrearchivo, "rb");
    if(!pf)
        return ERROR_APERTURA;
    rewind(pf);
    fread(&Estadisticas,sizeof(tEstadisticaPiloto),1,pf);
    while(!feof(pf))
    {
            printf("%d|%d|%d|%d|%d|%d\n",     Estadisticas.id_piloto,
                                        Estadisticas.carreras_corridas,
                                        Estadisticas.mejor_posicion,
                                        Estadisticas.peor_posicion,
                                        Estadisticas.suma_posiciones,
                                        Estadisticas.victorias);

        fread(&Estadisticas, sizeof(tEstadisticaPiloto),1,pf);
    }
    fclose(pf);
    return TODO_OK;
}

int listarIndicePilotos(const char* nombrearchivo)
{
    tIndicePiloto Indice;

    FILE* pf = fopen(nombrearchivo, "rb");
    if(!pf)
    {
        return ERROR_APERTURA;
    }
    rewind(pf);
    fread(&Indice,sizeof(tIndicePiloto),1,pf);
    while(!feof(pf))
    {
            printf("%u|%u\n", Indice.id,
                                Indice.indice);
            fread(&Indice,sizeof(tIndicePiloto),1,pf);
    }
    fclose(pf);
    return TODO_OK;
}
int modificarEstadoPiloto(const char* nombrearchivo, const char* nombrearchivoindice)
{
    unsigned id;
    int pos;
    char nuevoestado;
    tPiloto piloto;
    tBajas baja;
    FILE* pf = fopen(nombrearchivo,"r+b");
    if(!pf)
        return ERROR_APERTURA;
    printf("Escriba la ID del piloto a modificar el estado: \n");
    scanf("%u",&id);
    getchar();
    pos = busquedaIdPiloto(id,nombrearchivoindice);
    while(pos<0)
    {
        printf("Esa id no existe, reintente: \n");
        scanf("%u",&id);
        pos = busquedaIdPiloto(id,nombrearchivoindice);
    }
    fseek(pf, pos*sizeof(tPiloto),SEEK_SET);
    fread(&piloto, sizeof(tPiloto),1, pf);
    printf("ingrese el nuevo estado A. Activo R.Retirado S.Suspendido: \n");
    scanf("%c",&nuevoestado);
    getchar();
    while(nuevoestado == piloto.estado || busquedaEstadoPiloto(nuevoestado)<0)
    {
        printf("Reingrese un estado valido A. Activo R. Retirado S. Suspendido: \n");
        scanf("%c",&nuevoestado);
        getchar();
    }
    piloto.estado = nuevoestado;
    fseek(pf, pos*sizeof(tPiloto),SEEK_SET);
    fwrite(&piloto, sizeof(piloto),1, pf);
    if (nuevoestado == 'R')
    {
        FILE* pf2 = fopen("bajas.bin","ab");
        if(!pf2)
        {
            fclose(pf);
            return ERROR_APERTURA;
        }
        baja.id = id;
        strcpy(baja.nombre, piloto.nombre);
        strcpy(baja.entidad, "Piloto");
        fwrite(&baja, sizeof(baja),1,pf2);
        fclose(pf2);
    }
    fclose(pf);
    return TODO_OK;
}

int busquedaIdPiloto(unsigned id, const char* nombrearchivoindice)
{
    tIndicePiloto piloto;
    FILE* pf = fopen(nombrearchivoindice,"rb");
    if(!pf)
        return ERROR_APERTURA;
    while(fread(&piloto, sizeof(tIndicePiloto),1,pf))
    {
        if(id == piloto.id)
        {
            fclose(pf);
            return piloto.indice;
        }
    }
    fclose(pf);
    return ERROR_NO_ENCONTRADO;
}

int busquedaEstadoPiloto(char estado)
{
    char estados[CANT_ESTADOS_PILOTOS] = {'A','R','S'};
    char* pEstados = estados;
    for(int i = 0; i<CANT_ESTADOS_PILOTOS; i++)
    {
        if(estado == *pEstados)
            return TODO_OK;
        else
            pEstados++;
    }
    return ERROR_NO_ENCONTRADO;
}

int verBajas(const char *nombrearchivo)
{
    tBajas baja;
    FILE* pf = fopen(nombrearchivo, "rb");
    if(!pf)
        return ERROR_APERTURA;
    while(fread(&baja,sizeof(tBajas),1,pf))
    {
        printf("%u|%s|%s\n",    baja.id,
                                baja.nombre,
                                baja.entidad);
    }
    fclose(pf);
    return TODO_OK;
}
//
