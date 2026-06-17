#include "menu.h"
int main(int argc, char* argv[])
{
    crearLotePilotos("pilotos.txt");
    pilotosABin("pilotos.bin","pilotos.txt");
    listarEstadistica("estadisticas.bin");
    crearLoteEscuderias("escuderias.txt");
    escuderiasABin("escuderias.bin","escuderias.txt");
    menu();
    return 0;
}
