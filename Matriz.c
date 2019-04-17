#include "Celda.c"
#include "Hilo.c"
#define ANSI_COLOR_RESET   "\x1b[0m"

// GLOBALES************************

int g_alto;
int g_largo;
Celda **matriz;

pthread_t tid[99];

int Tid=0;
pthread_mutex_t lock;

char* colores[16]={"\033[22;30m", "\033[22;31m", "\033[22;32m", "\033[22;33m", "\033[22;34m"
, "\033[22;35m", "\033[22;36m", "\033[22;37m", "\033[01;30m", "\033[01;31m", "\033[01;32m"
, "\033[01;33m", "\033[01;34m", "\033[01;35m", "\033[01;36m", "\033[01;37m"}; 

//*********************************

//PROTOTITPOS***********************

void printMatriz();
void *MoverU(void *arg);
void *MoverD(void *arg);
void *MoverR(void *arg);
void *MoverL(void *arg);

//**********************************

void printMatriz(){
    
    for(int i = 0; i < g_alto; i++)
    {
        for(int j = 0; j < g_largo; j++)
        {
            if (matriz[i][j].tipo=='0') printf("%s%s%c%s", matriz[i][j].color , matriz[i][j].out,' ', ANSI_COLOR_RESET);

            else{
                if (j<g_largo-1)if(matriz[i][j+1].tipo=='*' && matriz[i][j].tipo!='/') 
                    printf("%s%s", matriz[i][j].out, matriz[i][j].out); 
                else printf("%s%c", matriz[i][j].out, ' ');
            }
        }
        printf("\n");
    }
}

void ImpresorT(){
    system("clear");
    printMatriz();
    sleep(1);
}

//FUNCIONES DE HILO**************************************

bool MirarU(Hilo* hilo){
    bool retorno = false;
    int pasos=hilo->pasos, i=hilo->i, j=hilo->j;

    //Revisar el camino hacia arriba
    if (hilo->i>0) if (matriz[hilo->i-1][hilo->j].tipo!='*' 
    && matriz[hilo->i-1][hilo->j].arriba==false) retorno = true;
    

    //Revisar el camino hacia izquierda
    if (hilo->j>0) if(matriz[hilo->i][hilo->j-1].tipo!='*' 
    && matriz[hilo->i][hilo->j-1].izq==false){
        Hilo hijo={pasos, i , j, colores[8]};
        pthread_create(&(tid[Tid]), NULL, MoverL, &hijo);
        pthread_join(tid[Tid], NULL);
        Tid++;
    }

    //Revisar el camino hacia derecha
    if (hilo->j<g_largo-1) if(matriz[hilo->i][hilo->j+1].tipo!='*' 
    && matriz[hilo->i][hilo->j+1].der==false){
        Hilo hijo={pasos, i , j, colores[8]};
        pthread_create(&(tid[Tid]), NULL, MoverR, &hijo);
        pthread_join(tid[Tid], NULL);
        Tid++;
    }

    return retorno;
}

bool MirarL(Hilo* hilo){
    bool retorno = false;
    int pasos=hilo->pasos, i=hilo->i, j=hilo->j;

    //Revisar el camino hacia izquierda
    if (hilo->j>0) if (matriz[hilo->i][hilo->j-1].tipo!='*' 
    && matriz[hilo->i][hilo->j-1].izq==false) retorno = true;

    //Revisar el camino hacia abajo
    if (hilo->i<g_alto-1) if (matriz[hilo->i+1][hilo->j].tipo!='*' 
    && matriz[hilo->i+1][hilo->j].abajo==false){
        Hilo hijo={pasos, i , j, colores[8]};
        pthread_create(&(tid[Tid]), NULL, MoverD, &hijo);
        pthread_join(tid[Tid], NULL);
        Tid++;
    }

    //Revisar el camino hacia arriba
    if (hilo->i>0) if(matriz[hilo->i-1][hilo->j].tipo!='*' 
    && matriz[hilo->i-1][hilo->j].arriba==false){
        Hilo hijo={pasos, i , j, colores[8]};
        pthread_create(&(tid[Tid]), NULL, MoverU, &hijo);
        pthread_join(tid[Tid], NULL);
        Tid++;
    }

    return retorno;
}

bool MirarD(Hilo* hilo){
    bool retorno = false;
    int pasos=hilo->pasos, i=hilo->i, j=hilo->j;

    //Revisar el camino hacia abajo
    if (hilo->i<g_alto-1) if (matriz[hilo->i+1][hilo->j].tipo!='*' 
    && matriz[hilo->i+1][hilo->j].abajo==false) retorno = true;
    

    //Revisar el camino hacia izquierda DESCOMENTAR PARA PROBAR
    /*if (hilo->j>0) if(matriz[hilo->i][hilo->j-1].tipo!='*' 
    && matriz[hilo->i][hilo->j-1].izq==false){
        Hilo hijo={pasos, i , j, colores[8]};
        pthread_create(&(tid[Tid]), NULL, MoverL, &hijo);
        pthread_join(tid[Tid], NULL);
        Tid++;
    }*/

    //Revisar el camino hacia derecha
    if (hilo->j<g_largo-1) if(matriz[hilo->i][hilo->j+1].tipo!='*' 
    && matriz[hilo->i][hilo->j+1].der==false){
        Hilo hijo={pasos, i , j, colores[8]};
        pthread_create(&(tid[Tid]), NULL, MoverR, &hijo);
        pthread_join(tid[Tid], NULL);
        Tid++;
    }

    return retorno;
}

bool MirarR(Hilo* hilo){
    bool retorno = false;
    int pasos=hilo->pasos, i=hilo->i, j=hilo->j;

    //Revisar el camino hacia derecha
    if (hilo->j<g_largo-1) if (matriz[hilo->i][hilo->j+1].tipo!='*' 
    && matriz[hilo->i][hilo->j+1].der==false) retorno = true;

    //Revisar el camino hacia abajo
    if (hilo->i<g_alto-1) if (matriz[hilo->i+1][hilo->j].tipo!='*' 
    && matriz[hilo->i+1][hilo->j].abajo==false){
        Hilo hijo={pasos, i , j, colores[8]};
        pthread_create(&(tid[Tid]), NULL, MoverD, &hijo);
        pthread_join(tid[Tid], NULL);
        Tid++;
    }

    //Revisar el camino hacia arriba DESCOMENTAR PARA PROBAR
    if (hilo->i>0) if(matriz[hilo->i-1][hilo->j].tipo!='*' 
    && matriz[hilo->i-1][hilo->j].arriba==false){
        Hilo hijo={pasos, i , j, colores[8]};
        pthread_create(&(tid[Tid]), NULL, MoverU, &hijo);
        pthread_join(tid[Tid], NULL);
        Tid++;
    }

    return retorno;   
}

void *MoverU(void *arg){
    //pthread_mutex_lock(&lock);

    Hilo *hilo=(Hilo*)arg;
    while(MirarU(hilo)){
        matriz[hilo->i][hilo->j].arriba=true;
        matriz[hilo->i][hilo->j].out="\u23F6";
        matriz[hilo->i][hilo->j].color=hilo->color;
        hilo->i--;
        hilo->pasos++;
        ImpresorT();
    }

    matriz[hilo->i][hilo->j].arriba=true;
    matriz[hilo->i][hilo->j].out="\u23F6";
    matriz[hilo->i][hilo->j].color=hilo->color;
    hilo->pasos++;
    ImpresorT();

    //pthread_mutex_unlock(&lock);

    return NULL;
}

void *MoverL(void *arg){
    //pthread_mutex_lock(&lock);
    Hilo *hilo=(Hilo*)arg;
    while(MirarL(hilo)){
        matriz[hilo->i][hilo->j].izq=true;
        matriz[hilo->i][hilo->j].out="\u23F4";
        matriz[hilo->i][hilo->j].color=hilo->color;
        hilo->j--;
        hilo->pasos++;
        ImpresorT();
    }

    matriz[hilo->i][hilo->j].izq=true;
    matriz[hilo->i][hilo->j].out="\u23F4";
    matriz[hilo->i][hilo->j].color=hilo->color;
    hilo->pasos++;
    ImpresorT();

    //pthread_mutex_unlock(&lock);

    return NULL;
}

void *MoverD(void *arg){
    //pthread_mutex_lock(&lock);
    Hilo *hilo=(Hilo*)arg;
    while(MirarD(hilo)){
        matriz[hilo->i][hilo->j].abajo=true;
        matriz[hilo->i][hilo->j].out="\u23F7";
        matriz[hilo->i][hilo->j].color=hilo->color;
        hilo->i++;
        hilo->pasos++;
        ImpresorT();
    }

    matriz[hilo->i][hilo->j].abajo=true;
    matriz[hilo->i][hilo->j].out="\u23F7";
    matriz[hilo->i][hilo->j].color=hilo->color;
    hilo->pasos++;
    ImpresorT();

    //pthread_mutex_unlock(&lock);

    return NULL;
}

void *MoverR(void *arg){
    //pthread_mutex_lock(&lock);
    Hilo *hilo=(Hilo*)arg;
    while(MirarR(hilo)){
        matriz[hilo->i][hilo->j].der=true;
        matriz[hilo->i][hilo->j].out="\u23F5";
        matriz[hilo->i][hilo->j].color=hilo->color;
        hilo->j++;
        hilo->pasos++;
        ImpresorT();
    }

    matriz[hilo->i][hilo->j].der=true;
    matriz[hilo->i][hilo->j].out="\u23F5";
    matriz[hilo->i][hilo->j].color=hilo->color;
    hilo->pasos++;
    ImpresorT();

    //pthread_mutex_unlock(&lock);

    return NULL;
}

/*void *MoverP(void *arg){
    Hilo *hilo=(Hilo*)arg;
    matriz[hilo->i][hilo->j].color=hilo->color;
    while(Mirar(hilo->i,hilo->j) && flag){
        switch (hilo->direccion){
            case 'u':
                matriz[hilo->i][hilo->j].arriba=true;
                hilo->i--;
                break;
            case 'd':
                matriz[hilo->i][hilo->j].abajo=true;
                hilo->i++;
                break;
            case 'l':
                matriz[hilo->i][hilo->j].izq=true;
                hilo->j--;
                break;
            case 'r':
                matriz[hilo->i][hilo->j].der=true;
                hilo->j++;
                break;
        }
        hilo->pasos++;
        matriz[hilo->i][hilo->j].color=hilo->color;
        usleep(3);
    }
    return NULL;
}*/

//*******************************************************

//FUNCIONES DE MATRIZ************************************

void Crearmatriz(int alto,int largo){
    g_alto=alto;
    g_largo=largo;
    matriz = (Celda**)malloc(alto*sizeof(Celda*));
    for(size_t i = 0; i < alto; i++)
    {
        matriz[i] = (Celda*)malloc(largo*sizeof(Celda));
    }
    
}

void InsertarMatriz(char *caracteres){
    int h=0;
    //printf("%d",g_largo);
    //printf("%d",g_alto);
    char* outSET="\u2588";
    for(int i = 0; i < g_alto; i++)
    {
        for(int j = 0; j < g_largo; j++)
        {
            if (caracteres[h]==' '){
                caracteres[h]='0';
                outSET=" ";
            }

            else if (caracteres[h]=='/'){
                outSET="\u26DD";
            }

            Celda celda={caracteres[h],outSET,0,0,0,0,ANSI_COLOR_RESET};
            matriz[i][j]= celda;
            outSET="\u2588";
            //printf("%c",caracteres[h]);
            
            h++;
        }  
    }
}

//*******************************************************