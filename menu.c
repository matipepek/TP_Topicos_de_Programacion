#include "menu.h"

void menu()
{
    int estado;
    do{
        printf("\n");
        printf("0. Salir\n");
        printf("1. Listar pilotos y sus puntos\n");
        printf("2. Registrar una carrera (ingreso de posiciones)\n");
        printf("3. Mostrar ranking de pilotos (ordenado) de la temporada en cuestion\n");
        printf("4. Mostrar pilotos por escuderia\n");
        printf("5. Calcular estadisticas de pilotos\n");
        printf("6. Exportar datos a archivos de texto\n");
        printf("Ingrese opcion: ");
        scanf("%d", &estado);
        while(!(estado>=0 && estado <=7))
        {
            printf("Ingrese opcion valida: ");
            scanf("%d", &estado);
        }
        printf("\n");
        switch (estado)
        {
            case 0:
                break;
            case 1:
                listarPilotosyPuntos("pilotos.bin");
                break;
            case 2:
                registrarCarrera("carreras.dat", "pilotos.bin", "estadisticas.bin");
                //verificarCarrerasDat("carreras.dat");
                break;
            case 3:
                mostrarRankingPilotos("pilotos.bin", "escuderias.bin");
                break;
            case 4:
                MostrarpilotosXEscuderia("escuderias.bin","pilotos.bin");
                break;
            case 5:
                verificaPuntosStats("pilotos.bin","estadisticas.bin");
                break;
            case 6:
                CarrerasABin("carreras.txt","carreras.dat");
                break;
        }
    }while(estado);
}
