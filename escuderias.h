#ifndef ESCUDERIAS_H_INCLUDED
#define ESCUDERIAS_H_INCLUDED

typedef struct
{
    unsigned id;
    char codigo[4];
    char nombre[30];
    char pais[50];
    int estado;     //(1: Activo, 0: inactivo)
} tEscuderia;

#endif // ESCUDERIAS_H_INCLUDED
