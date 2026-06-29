#include "fecha.h"

tFecha descomponeFecha(unsigned long long fecha) // Troza la fecha para usarla en las funciones
{
    tFecha fechaCarrera;

    fechaCarrera.dia = (unsigned int)(fecha % 100);
    fechaCarrera.mes = (unsigned int)((fecha / 100) % 100);
    fechaCarrera.anio = (unsigned int)(fecha / 10000);

    return fechaCarrera;
}

int esBisiesto(unsigned int anio) // Revisa si es bisiesto
{
    return(anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0));
}

int esDiaValido(unsigned int dia, unsigned int mes, int bisiesto) // Usa el rango de días según el mes y si es bisiesto
{
    int valido = 1;

    switch(mes)
    {
        case 1: if(dia < 1 || dia > 31){valido = 0;} break;
        case 2: if(bisiesto){ if(dia < 0 || dia > 29) {valido = 0;} } else {if(dia < 0 || dia > 28) {valido = 0;}} break;
        case 3: if(dia < 1 || dia > 31){valido = 0;} break;
        case 4: if(dia < 1 || dia > 30){valido = 0;} break;
        case 5: if(dia < 1 || dia > 31){valido = 0;} break;
        case 6: if(dia < 1 || dia > 30){valido = 0;} break;
        case 7: if(dia < 1 || dia > 31){valido = 0;} break;
        case 8: if(dia < 1 || dia > 31){valido = 0;} break;
        case 9: if(dia < 1 || dia > 30){valido = 0;} break;
        case 10: if(dia < 1 || dia > 31){valido = 0;} break;
        case 11: if(dia < 1 || dia > 30){valido = 0;} break;
        case 12: if(dia < 1 || dia > 31){valido = 0;} break;
    }

    return valido;
}

int esFechaValida(unsigned long long fecha) // Usa el rango de fecha, mes y el año para saber si es una fecha válida
{
    tFecha fechaAux;
    fechaAux = descomponeFecha(fecha);
    if(fechaAux.anio > 2025)
    {
        if(fechaAux.mes > 0 && fechaAux.mes < 13){
           if(esDiaValido(fechaAux.dia, fechaAux.mes, esBisiesto(fechaAux.anio)))
                return TODO_OK;
        }
    }

    return FECHA_INVALIDA;
}
