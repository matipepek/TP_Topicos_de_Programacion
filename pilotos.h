#ifndef PILOTOS_H_INCLUDED
#define PILOTOS_H_INCLUDED

typedef struct
{
    unsigned id;
    char[30] nombre;
    char[30] nacionalidad;
    unsigned id_escuderia;
    unsigned puntos_acumulados;
    char estado;                //(A: Activo, R: Retirado, S: Suspendido)
    unsigned long long fechaNacimiento;
} tPiloto;

#endif // PILOTOS_H_INCLUDED
