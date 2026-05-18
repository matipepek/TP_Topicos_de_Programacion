#ifndef ESCUDERIAS_H_INCLUDED
#define ESCUDERIAS_H_INCLUDED

typedef struct
{
    unsigned id;
    char[4] codigo;
    char[30] nombre;
    char[50] pais;
    int estado;     //(1: Activo, 0: inactivo)
} tEscuderia;

#endif // ESCUDERIAS_H_INCLUDED
