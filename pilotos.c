#include "pilotos.h"
#include "escuderias.h"

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
    {1,  "Lando Norris",      "Reino Unido", 1, 0, 'A', 19991113},
    {2,  "Oscar Piastri",     "Australia",   1, 0, 'A', 20010406},

    {3,  "George Russell",    "Reino Unido", 2, 0, 'A', 19980215},
    {4,  "Kimi Antonelli",    "Italia",      2, 0, 'A', 20060825},

    {5,  "Charles Leclerc",   "Monaco",      3, 0, 'A', 19971016},
    {6,  "Lewis Hamilton",    "Reino Unido", 3, 0, 'A', 19850107},

    {7,  "Max Verstappen",    "Paises Bajos",4, 0, 'A', 19970930},
    {8,  "Isack Hadjar",      "Francia",     4, 0, 'A', 20040928},

    {9,  "Fernando Alonso",   "Espania",      5, 0, 'A', 19810729},
    {10, "Lance Stroll",      "Canada",      5, 0, 'A', 19981029},

    {11, "Carlos Sainz",      "Espania",      6, 0, 'A', 19940901},
    {12, "Alexander Albon",   "Tailandia",   6, 0, 'A', 19960323},

    {13, "Pierre Gasly",      "Francia",     7, 0, 'A', 19960207},
    {14, "Franco Colapinto",  "Argentina",   7, 0, 'A', 20030527},

    {15, "Esteban Ocon",      "Francia",     8, 0, 'A', 19960917},
    {16, "Oliver Bearman",    "Reino Unido", 8, 0, 'A', 20050508},

    {17, "Liam Lawson",       "Nueva Zelanda",9, 0, 'A', 20020211},
    {18, "Arvid Lindblad",    "Reino Unido", 9, 0, 'A', 20070808},

    {19, "Nico Hulkenberg",   "Alemania",    10, 0, 'A', 19870819},
    {20, "Gabriel Bortoleto", "Brasil",      10, 0, 'A', 20041014},

    {21, "Sergio Perez",      "Mexico",      11, 0, 'A', 19900126},
    {22, "Valtteri Bottas",   "Finlandia",   11, 0, 'A', 19890828}
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
    char cadena[BUFFER];
    FILE* pf = fopen(nombrearchivoorigen, "rt");
    FILE* pf2 = fopen(nombrearchivodestino, "wb");

    if(!pf || !pf2)
    {
        return ERROR_APERTURA;
    }

    while(fgets(cadena, BUFFER, pf))
    {
        trozadoCampoVariablePilotos(cadena, &Pilotos);
        mostrarPilotos(&Pilotos);
        fwrite(&Pilotos, sizeof(Pilotos), 1, pf2);
    }

    fclose(pf);
    fclose(pf2);
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
    tPiloto* piloto = malloc(sizeof(tPiloto));
    if (!piloto)
        return ERROR_SIN_MEMORIA;

    FILE* pf = fopen(nombrearchivo, "rb");
    if(!pf)
        return ERROR_APERTURA;

    while(fread(piloto, sizeof(*piloto),1,pf))
    {
        printf("%s|%-u\n",  piloto->nombre,
                            piloto->puntos_acumulados);
    }
    fclose(pf);
    free(piloto);
    return TODO_OK;
}

// 4. Mostrar ranking de pilotos (ordenado) de la temporada en cuestión.

char* devuelveNombreEscuderia(tEscuderia* vEscuderia, unsigned idBuscado, size_t ce)
{
    size_t i;
    for(i=0; i<ce; i++)
    {
        if((vEscuderia + i)->id == idBuscado)
            return (vEscuderia + i)->nombre;
    }

    return NULL;
}

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
