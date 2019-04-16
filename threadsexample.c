//Mae ejecute esta vara y vea lo q pasa , luego ejecuta sin los comentarios de abajo

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


void * hola ( void * arg ) {
char * msg = " Hola ";
int i;
for ( i = 0 ; i < strlen ( msg ) ; i ++ ) {
printf (" %c" , msg [ i ]) ;
fflush ( stdout ) ;
usleep (1000000) ;
}
return NULL ;
}
void * mundo ( void * arg ) {
char * msg = " mundo ";
int i;
for ( i = 0 ; i < strlen ( msg ) ; i ++ ) {
printf (" %c" , msg [ i ]) ;
fflush ( stdout ) ;
usleep (1000000) ;
}
return NULL ;
}
int main ( int argc , char * argv []) {
pthread_t h1 ;
pthread_t h2 ;
pthread_create (& h1 , NULL , hola , NULL );
pthread_create (& h2 , NULL , mundo , NULL );
pthread_join ( h1 , NULL ) ; //Descomente 
pthread_join ( h2 , NULL ) ; //Descomente
printf ( " Fin \n ");
}