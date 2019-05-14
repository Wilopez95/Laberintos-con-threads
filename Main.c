#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "Matriz.c"


//GLOBALES****************************

char caracter;
int largo; //j
int alto;//i

//************************************
bool leerArchivo(char *nombre){
    FILE *archivo;
	
    int i = 0;
    char matrizsize [5];
    char *largoStr = malloc(2 * sizeof(char));
    char *altoStr = malloc(2 * sizeof(char));
    
    //APERTURA DEL ARCHIVO****************************
    char file[25] = "Mapas/";
    strcat(file, nombre);
    archivo = fopen(file,"r");
    if (archivo == NULL)
        {
            return false;
            
        }
        else
        {
            //printf("\nEl tamaño de la matriz es \n\n");


            while((caracter = fgetc(archivo)) != '\n') //Leer la primera linea
            {
                
                matrizsize[i]=caracter;
                i++;
            }

            memcpy(largoStr, matrizsize, 2 * sizeof(char));
            memcpy(altoStr, matrizsize + 3, 2 * sizeof(char));
            largo = atoi(largoStr);
            alto = atoi(altoStr);

            //crea una matriz de nxn
            Crearmatriz(alto,largo);

            char *caracteres;
            caracteres= (char*)malloc((alto*largo)*sizeof(char));
            i=0;
            while((caracter = fgetc(archivo)) != EOF)
	        {
                if(caracter!='\n' ){ 
                    if(i<=alto*largo){
                        caracteres[i]=caracter;
                        i++;
                    }

                    else {
                        printf("¡Tamaño dado inadecuado!\n");
                        return false;
                    }
                }
                                
	        }

            if(i<alto*largo){
                printf("¡Tamaño dado inadecuado!\n");
                return false;
            }

            i=0;

            //inserta a en todos los campos de la matriz
            InsertarMatriz(caracteres);
            free(caracteres);
        }
        fclose(archivo);
        return true;
}
int main()
{
    printf("%s","Ingresar el nombre del archivo: ");
    char archivo[15];
    scanf("%s",archivo);
    //printf("%s%s","Procesando el archivo: ",archivo);
    system("clear");
    int stat;

    bool abierto = leerArchivo(archivo);

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

    if(abierto){

        Hilo hilod = {Tid,-1,0,0,0};

        stat = pthread_create(&(tid[Tid]), NULL, MoverD, &hilod);
        if ( 0 != stat ) {
 	    // Error al crear el thread, salimos del padre lanzando signal o exit
            exit(-1);
        }

        Tid++;

        while(flag){
            ImpresorT();
        }

        system("clear");
        printMatriz();

        printf("\n\n");

        printf("ID : PASOS");
        printf("\n");

        for(int i = 0; i < Hid; i++)
        {
            if(hilos[i].id<10){
                if(hilos[i].pasos>=10){
                    printf("%s%c%d%s%d%s", colores[hilos[i].color], '0', hilos[i].id, " : ", hilos[i].pasos, ANSI_COLOR_RESET);
                }
                else
                {
                    printf("%s%c%d%s%c%d%s", colores[hilos[i].color], '0', hilos[i].id, " : ", '0', hilos[i].pasos, ANSI_COLOR_RESET);
                }
                
            }
            else{
                printf("%s%d%s%d%s", colores[hilos[i].color], hilos[i].id, " : ", hilos[i].pasos, ANSI_COLOR_RESET);
            }

            if(i==Hid-1) printf("%s%s%s", colores[hilos[i].color], " ¡SALIDA!", ANSI_COLOR_RESET);

            printf("\n");
                
        }

    }   

     pthread_mutex_destroy(&lock);

   return 0;
}
