#include "escuderias.h"

int crearLoteEscuderias(const char* nombrearchivo)
{
    tEscuderia Escuderias[] = {
    {1,  "MCL", "McLaren",       "Reino Unido", 1},
    {2,  "MER", "Mercedes",      "Alemania",    1},
    {3,  "FER", "Ferrari",       "Italia",      1},
    {4,  "RBR", "Red Bull",      "Austria",     1},
    {5,  "AMR", "Aston Martin",  "Reino Unido", 1},
    {6,  "WIL", "Williams",      "Reino Unido", 1},
    {7,  "ALP", "Alpine",        "Francia",     1},
    {8,  "HAS", "Haas",          "Estados Unidos", 1},
    {9,  "RBT", "Racing Bulls",  "Italia",      1},
    {10, "AUD", "Audi",          "Alemania",    1},
    {11, "CAD", "Cadillac",      "Estados Unidos", 1}
    };
    int ce = sizeof(Escuderias)/sizeof(tEscuderia);
    tEscuderia *pEscuderias = Escuderias;

    FILE* pf = fopen(nombrearchivo, "wt");
    if(!pf)
    {
        return ERROR_APERTURA;
    }
    for(int i = 0; i<ce; i++)
    {
        fprintf(pf, "%u|%s|%s|%s|%d\n", pEscuderias->id, pEscuderias->codigo, pEscuderias->nombre, pEscuderias->pais, pEscuderias->estado);
        pEscuderias++;
    }
    return TODO_OK;

}
