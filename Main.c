#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "Matriz.c"
#include "Leerarchivo.c"


//************************************

void *Impresor(void *x){
    while(flag){
        printMatriz();
        usleep(3);
        system("clear");
    }
    return NULL;
}

void *moveUp(void *x){

}

void *moveDown(void *x){
     for(int i = 0; i < g_alto; i++)
    {
        for(int j = 0; j < g_largo; j++)
        {
           printf("%c",matriz[i][j].tipo);
           fflush ( stdout ) ;
           usleep (1000000) ;
        }
        printf("\n");
    }

}

void *moveLeft(void *x){

}

void *moveRigth(void *x){

}

bool cheekup(int i, int j){
    if(i== 0){
        printf("%s","No se puede ir para arriba");
        printf("\n");
        return false;
    }else{
        if(matriz[i-1][j].tipo=='*' || matriz[i-1][j].arriba){
            printf("%s","No se puede ir para arriba");
            printf("\n");
            return false;
        }

    }
    printf("%s","Se puede ir para arriba");
    printf("\n");
    return true;
    
}

bool cheekdown(int i, int j){
    if(i== g_alto-1){
        printf("%s","No se puede ir para abajo");
        printf("\n");
        return false;
    }else{
        if(matriz[i+1][j].tipo=='*' || matriz[i+1][j].abajo){
            printf("%s","No se puede ir para abajo");
            printf("\n");
            return false;
        }

    }
    printf("%s","Se puede ir para abajo");
    printf("\n");
    return true;
    
}

bool cheekrigth(int i, int j){
    if(j== g_largo-1){
        printf("%s","No se puede ir para la derecha");
        printf("\n");
        return false;
    }else{
        if(matriz[i][j+1].tipo=='*' || matriz[i][j+1].der){
            printf("%s","No se puede ir para la derecha");
            printf("\n");
            return false;
        }

    }
    printf("%s","Se puede ir para la derecha");
    printf("\n");
    return true;
    
}

bool cheekleft(int i, int j){
    if(j== 0){
        printf("%s","No se puede ir para la izquierda");
        printf("\n");
        return false;
    }else{
        if(matriz[i][j-1].tipo=='*' || matriz[i][j-1].izq){
            printf("%s","No se puede ir para la izquierda");
            printf("\n");
            return false;
        }

    }
    printf("%s","Se puede ir para la derecha");
    printf("\n");
    return true;
    
}


void run (int i, int j){
    cheekup(i,j);
    cheekdown(i,j);
    cheekrigth(i,j);
        
    

}

int main()
{
    printf("%s","Ingresar el nombre del archivo: ");
    char archivo[15];
    scanf("%s",archivo);
    //printf("%s%s","Procesando el archivo: ",archivo);
    system("clear");
    bool abierto = leerArchivo(archivo);
    
    if(abierto){
        //HILO IMPRESOR*****************************
        //pthread_t print;
        //int x=0;
        //pthread_create(&print, NULL, moveDown, &x);
        //pthread_join ( print , NULL ) ;
        //******************************************
        
        //Mover('d',0,0);
        run(9,0);
    }

   return 0;
}
