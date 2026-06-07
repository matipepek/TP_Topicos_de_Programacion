#include "pilotos.h"
#include "escuderias.h"
#include "carreras.h"

int main(int argc, char* argv[])
{
    //menu
    int estado;
    do{
        printf("\n");
        printf("0. Salir\n");
        printf("1. Listar pilotos y sus puntos\n");
        printf("2. Registrar una carrera (ingreso de posiciones)\n");
        printf("3. Calcular y actualizar puntos automaticamente\n");
        printf("4. Mostrar ranking de pilotos (ordenado) de la temporada en cuestion\n");
        printf("5. Mostrar pilotos por escuderia\n");
        printf("6. Calcular estadisticas de pilotos\n");
        printf("7. Exportar datos a archivos de texto\n");
        printf("Ingrese opcion: ");
        scanf("%d", &estado);
        printf("\n");
        switch (estado)
        {
            case 0:
                break;
            case 1:
                listarPilotosyPuntos("pilotos.bin");
                break;
            case 2:
                registrarCarrera("carreras.dat");
                //verificarCarrerasDat("carreras.dat");
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
        }
    }while(estado);

    return 0;
}
