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
    fclose(pf);
    return TODO_OK;
}

int escuderiasABin(const char* nombrearchivodestino, const char* nombrearchivoorigen)
{
    tEscuderia Escuderias;
    tIndiceEscuderia Indice;
    unsigned cont = 0;
    char cadena[BUFFER];
    FILE* pf = fopen(nombrearchivoorigen, "rt");
    FILE* pf2 = fopen(nombrearchivodestino, "wb");
    FILE* pf3 = fopen ("indiceescuderias.bin", "wb");

    if(!pf)
    {
        return ERROR_APERTURA;
    }

    if(!pf2)
    {
        fclose(pf);
        return ERROR_APERTURA;
    }

    if(!pf3)
    {
        fclose(pf);
        fclose(pf2);
        return ERROR_APERTURA;
    }

    while(fgets(cadena, BUFFER, pf))
    {
        trozadoCampoVariableEscuderias(cadena, &Escuderias);

        Indice.id = Escuderias.id;
        Indice.indice = cont;
        cont++;

        mostrarEscuderias(&Escuderias);
        fwrite(&Escuderias, sizeof(Escuderias), 1, pf2);
        fwrite(&Indice, sizeof(Indice), 1, pf3);
    }

    fclose(pf);
    fclose(pf2);
    fclose(pf3);
    return TODO_OK;
}

void trozadoCampoVariableEscuderias(char* cadena,tEscuderia* escuderia)
{
    char * aux;
    aux = strchr(cadena, '\n');
    *aux = '\0';
    aux = strrchr(cadena, '|');
    sscanf(aux+1,"%d",&escuderia->estado);
    *aux = '\0';
    aux = strrchr(cadena, '|');
    strcpy(escuderia->pais, aux+1);
    *aux = '\0';
    aux = strrchr(cadena, '|');
    strcpy(escuderia->nombre, aux+1);
    *aux = '\0';
    aux = strrchr(cadena, '|');
    strcpy(escuderia->codigo, aux+1);
    *aux = '\0';
    sscanf(cadena,"%u",&escuderia->id);
}

void mostrarEscuderias(tEscuderia* escuderias)
{
        printf("%u|%s|%s|%s|%d\n",          escuderias->id,
                                            escuderias->codigo,
                                            escuderias->nombre,
                                            escuderias->pais,
                                            escuderias->estado);
}

char* devuelveNombreEscuderia(tEscuderia* vEscuderia, unsigned idBuscado, size_t ce)
{
    size_t i;
    for(i=0; i<ce; i++)
    {
        if((vEscuderia + i)->id == idBuscado)
            return (vEscuderia + i)->nombre;
    }

    return NULL;
}

int MostrarpilotosXEscuderia(const char* nombrearchivo1, const char* nombrearchivo2)
{
    FILE* pf=fopen(nombrearchivo1,"rb");
    FILE* pf2=fopen(nombrearchivo2,"rb");

    if(pf==NULL)
    {
        return ERROR_APERTURA;
    }

    if(pf2==NULL)
    {
        fclose(pf);
        return ERROR_APERTURA;
    }

    int pilotosencontrados=0;
    int idseleccionado;
    char nombreescuderia[30]="";
    tEscuderia Escuderias;
    tPiloto Pilotos;

    printf("\n========================================\n");
    printf("       ESCUDERIAS DISPONIBLES\n");
    printf("========================================\n");


    fread(&Escuderias,sizeof(tEscuderia),1,pf);
    while(!feof(pf))
    {
        if(Escuderias.estado==1)
        {
            printf("ID:%d | %s\n",Escuderias.id,Escuderias.nombre);
        }
        fread(&Escuderias,sizeof(tEscuderia),1,pf);
    }

    printf("----------------------------------------\n");
    printf("Ingrese el codigo de la escuderia para ver sus pilotos (0 para salir):");
    scanf("%d",&idseleccionado);
    while(idseleccionado!=0)
    {
        rewind(pf);
        fread(&Escuderias,sizeof(tEscuderia),1,pf);
        while(!feof(pf))
        {
            if(Escuderias.estado==1&&(Escuderias.id==idseleccionado))
            {
                strcpy(nombreescuderia,Escuderias.nombre);
            }
            fread(&Escuderias,sizeof(tEscuderia),1,pf);
        }
        printf("\n========================================\n");
        printf(" PILOTOS DE LA ESCUDERIA: %s\n",nombreescuderia);
        printf("========================================\n");

        rewind(pf2);
        fread(&Pilotos,sizeof(tPiloto),1,pf2);
        while(!feof(pf2))
        {
            if(Pilotos.estado=='A'&&(Pilotos.id_escuderia==idseleccionado))
            {
                printf("  - %s (Puntos: %d)\n", Pilotos.nombre, Pilotos.puntos_acumulados);
                pilotosencontrados++;
            }
                fread(&Pilotos,sizeof(tPiloto),1,pf2);
        }
        if(pilotosencontrados==0)
        {
            printf("No se encontraron pilotos activos para esta escuderia\n");
        }

        printf("----------------------------------------\n");
        printf("Ingrese el codigo de la escuderia para ver sus pilotos (0 para salir):");
        scanf("%d",&idseleccionado);
    }
    printf("========================================\n");
    fclose(pf);
    fclose(pf2);
    return TODO_OK;
}

int modificarEstadoEscuderia(const char* nombrearchivo, const char* nombrearchivoindice)
{
    unsigned id;
    int pos;
    int nuevoestado;
    tEscuderia escuderia;
    tBajas baja;
    FILE* pf = fopen(nombrearchivo,"r+b");
    if(!pf)
        return ERROR_APERTURA;
    printf("Escriba el ID de la escuderia para modificar el estado: \n");
    scanf("%u",&id);
    getchar();
    pos = busquedaIdEscuderia(id,nombrearchivoindice);
    while(pos<0)
    {
        printf("Esa id no existe, reintente: \n");
        scanf("%u",&id);
        pos = busquedaIdEscuderia(id,nombrearchivoindice);
    }
    fseek(pf, pos*sizeof(tEscuderia),SEEK_SET);
    fread(&escuderia, sizeof(tEscuderia),1, pf);
    printf("ingrese el nuevo estado 1.Activo 0.Inactivo \n");
    scanf("%d",&nuevoestado);
    getchar();
    while(nuevoestado == escuderia.estado || busquedaEstadoEscuderia(nuevoestado)<0)
    {
        printf("Reingrese un estado valido 1.Activo 0.Inactivo: \n");
        scanf("%d",&nuevoestado);
        getchar();
    }
    escuderia.estado = nuevoestado;
    fseek(pf, pos*sizeof(tEscuderia),SEEK_SET);
    fwrite(&escuderia, sizeof(escuderia),1, pf);
    if (nuevoestado == 0)
    {
        FILE* pf2 = fopen("bajas.bin","ab");
        if(!pf2)
        {
            fclose(pf);
            return ERROR_APERTURA;
        }
        baja.id = id;
        strcpy(baja.nombre, escuderia.nombre);
        strcpy(baja.entidad, "Escuderia");
        fwrite(&baja, sizeof(baja),1,pf2);
        fclose(pf2);
    }
    fclose(pf);
    return TODO_OK;
}

int listarIndiceEscuderias(const char* nombrearchivo)
{
     tIndiceEscuderia Indice;

    FILE* pf = fopen(nombrearchivo, "rb");
    if(!pf)
    {
        return ERROR_APERTURA;
    }
    rewind(pf);
    fread(&Indice,sizeof(tIndiceEscuderia),1,pf);
    while(!feof(pf))
    {
            printf("%u|%u\n", Indice.id,
                                Indice.indice);
            fread(&Indice,sizeof(tIndiceEscuderia),1,pf);
    }
    fclose(pf);
    return TODO_OK;
}

int busquedaIdEscuderia(unsigned id, const char* nombrearchivoindice)
{
    tIndiceEscuderia escuderia;
    FILE* pf = fopen(nombrearchivoindice,"rb");
    if(!pf)
        return ERROR_APERTURA;
    while(fread(&escuderia, sizeof(tIndiceEscuderia),1,pf))
    {
        if(id == escuderia.id)
        {
            fclose(pf);
            return escuderia.indice;
        }
    }
    fclose(pf);
    return ERROR_NO_ENCONTRADO;
}

int busquedaEstadoEscuderia(char estado)
{
    int estados[CANT_ESTADOS_ESCUDERIAS] = {0,1};
    int* pEstados = estados;
    for(int i = 0; i<CANT_ESTADOS_ESCUDERIAS; i++)
    {
        if(estado == *pEstados)
            return TODO_OK;
        else
            pEstados++;
    }
    return ERROR_NO_ENCONTRADO;
}
