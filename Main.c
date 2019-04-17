#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "Matriz.c"
#include "Leerarchivo.c"



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
        pthread_t u, l, d, r;

        Hilo hilou = {0,0,0,colores[5]};

        stat = pthread_create(&(tid[Tid]), NULL, MoverD, &hilou);
        if ( 0 != stat ) {
 	    // Error al crear el thread, salimos del padre lanzando signal o exit
            exit(-1);
        }

        stat = pthread_join(tid[Tid], NULL);
        if ( 0 != stat ) {
	// Error al cerrar el thread, salimos del padre lanzando signal o exit
            exit(-1);
        }

        Tid++;

        /*Hilo hilol = {2,0,4,9,colores[3]};

        stat = pthread_create(&l, NULL, MoverL, &hilol);
        if ( 0 != stat ) {
 	    // Error al crear el thread, salimos del padre lanzando signal o exit
            exit(-1);
        }

        stat = pthread_join(l, NULL);
        if ( 0 != stat ) {
	// Error al cerrar el thread, salimos del padre lanzando signal o exit
            exit(-1);
        }

        Hilo hilor = {3,0,6,0,colores[4]};

        stat = pthread_create(&r, NULL, MoverR, &hilor);
        if ( 0 != stat ) {
 	    // Error al crear el thread, salimos del padre lanzando signal o exit
            exit(-1);
        }

        stat = pthread_join(r, NULL);
        if ( 0 != stat ) {
	// Error al cerrar el thread, salimos del padre lanzando signal o exit
            exit(-1);
        }*/
        
    }

     pthread_mutex_destroy(&lock);

   return 0;
}
