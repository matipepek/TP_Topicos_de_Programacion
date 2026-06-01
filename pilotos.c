#include "pilotos.h"

int CrearLotePilotos(const char* nombrearchivo)
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
    return TODO_OK;
}
