#include <stdio.h>
#include "Celda.c"


int global_i;
int global_j;
char matriz[10][10];

void Crearmatriz( int alto,int largo){
    global_i=alto;
    global_j=largo;
    

}

void InsertarMatriz(){
    for(int i = 0; i < global_i; i++)
    {
        for(int j = 0; j < global_j; j++)
        {
            matriz[i][j]='a';
        }
        
        
    }
}

void printMatriz(){
    for(int i = 0; i < global_i; i++)
    {
        for(int j = 0; j < global_j; j++)
        {
            printf("%c\t",matriz[i][j]);
        }
        printf("\n");
        
    }
}