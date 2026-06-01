#ifndef CARRERAS_H_INCLUDED
#define CARRERAS_H_INCLUDED

typedef struct
{
    int id;
    char circuito[20];
    unsigned long long fecha;
    int estado;
    int Cant_resultados;
    void** resultados;  //Matriz que contenga los resultados
} tCarreras;

#endif // CARRERAS_H_INCLUDED
