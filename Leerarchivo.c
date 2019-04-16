#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//GLOBALES****************************

char caracter;
int largo; //j
int alto;//i


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
                if(caracter!='\n'){
                    caracteres[i]=caracter;
                    i++;
                }
                                
	        }
            i=0;

            //inserta a en todos los campos de la matriz
            InsertarMatriz(caracteres);
            free(caracteres);
        }
        fclose(archivo);
        return true;
}