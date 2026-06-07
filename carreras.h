#ifndef CARRERAS_H_INCLUDED
#define CARRERAS_H_INCLUDED

#define ERROR_APERTURA -2
#define ERROR_SIN_MEMORIA -1
#define TODO_OK 1

typedef struct
{
    int id;
    char circuito[20];
    unsigned long long fecha;
    int estado;
    int Cant_resultados;
    void** resultados;  //Matriz que contenga los resultados
} tCarreras;

void limpiarSalto(char* cadena);
int registrarCarrera(const char* nombreArchivo);
void verificarCarrerasDat(const char* nombreArchivo);

#endif // CARRERAS_H_INCLUDED
