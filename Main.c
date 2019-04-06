#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Matriz.c"


//Caracteres adentro del archivo
char caracter;
int largo; //i
int alto;//j


void leerArchivo(char file[]){
    FILE *archivo;
	
    int i = 0;
    char matrizsize [5];
    char *largoStr = malloc(2 * sizeof(char));
    char *altoStr = malloc(2 * sizeof(char));
    archivo = fopen("Mapas/m1.txt","r");
    if (archivo == NULL)
        {
            printf("\nError de apertura del archivo. \n\n");
            
        }
        else
        {
            printf("\nEl tamaño de la matriz es \n\n");


            while((caracter = fgetc(archivo)) != '\n') //Leer la primera linea
            {
                
                matrizsize[i]=caracter;
                i++;
            }

            memcpy(largoStr, matrizsize, 2 * sizeof(char));
            memcpy(altoStr, matrizsize + 3, 2 * sizeof(char));
            largo = atoi(largoStr);
            alto = atoi(altoStr);


            printf("\n");
            printf("%s%d","Largo: ",largo);
            printf("\n");
            printf("%s%d","Alto: ",alto);
            i=0;
            
            printf("\n");
            //crea una matriz de nxn
            Crearmatriz(alto,largo);
            //inserta a en todos los campos de la matriz 
            InsertarMatriz();
            //imprime la matriz 
            printMatriz();

            
            printf("\n");
            printf("\nLa matriz es \n\n");
            while((caracter = fgetc(archivo)) != EOF)
	        {
                //if(caracter != '\n'){
                    //printf("%d%s%c\n", i," : ",caracter);
                    //i = i+1;
	    	        printf("%c",caracter);
                //}
                                
	        }
            printf("\n");
        }
        fclose(archivo);
}
int main()
{
    printf("%s","Ingresar el nombre del archivo: ");
    char archivo[15];
    scanf("%s",archivo);
    printf("%s%s","Procesando el archivo: ",archivo);
    leerArchivo(archivo);
   return 0;
}
