#include "Celda.c"
#include "Hilo.c"
#define ANSI_COLOR_RESET   "\x1b[0m"

// GLOBALES************************

bool flag = true;

int g_alto;
int g_largo;
Celda **matriz;

Hilo hilos[99];
int Hid=0;

pthread_t tid[99];
int Tid=0;

pthread_mutex_t lock;

char* colores[16]={"\033[22;30m", "\033[22;31m", "\033[22;32m", "\033[22;33m", "\033[22;34m"
, "\033[22;35m", "\033[22;36m", "\033[22;37m", "\033[01;30m", "\033[01;31m", "\033[01;32m"
, "\033[01;33m", "\033[01;34m", "\033[01;35m", "\033[01;36m", "\033[01;37m"}; 
int Cid=1;

//*********************************

//PROTOTITPOS***********************

void printMatriz();
void ImpresorT();
void *MoverU(void *arg);
void *MoverD(void *arg);
void *MoverR(void *arg);
void *MoverL(void *arg);
bool MirarU(Hilo hilo);
bool MirarD(Hilo hilo);
bool MirarR(Hilo hilo);
bool MirarL(Hilo hilo);
void InsertarMatriz(char *caracteres);
void Crearmatriz(int alto,int largo);

//**********************************

//FUNCIONES DE HILO**************************************

bool MirarU(Hilo hilo){
    bool retorno = false;
    int pasos=hilo.pasos, i=hilo.i, j=hilo.j;
    pthread_mutex_lock(&lock);

    //Revisa si hay salida
    //************************************

    if(matriz[hilo.i][hilo.j].tipo=='/'){
            flag=false;
            Hilo hiloL={hilo.id , pasos, i , j, hilo.color};
            hilos[Hid]=hiloL;
            Hid++;
            return false;
    }

    //************************************

    //Revisar el camino hacia arriba
    //************************************
    
    if (hilo.i>0)if (matriz[hilo.i-1][hilo.j].tipo!='*' 
        && matriz[hilo.i-1][hilo.j].arriba==false) retorno = true;
    
    //************************************


    //Revisar el camino hacia izquierda
    //************************************

    if (hilo.j>0) if(matriz[hilo.i][hilo.j-1].tipo!='*' 
        && matriz[hilo.i][hilo.j-1].izq==false){
            Hilo hijo={Tid, pasos, i , j-1, Cid};
            if(Cid<15) Cid++;
            else Cid=0;
            pthread_create(&(tid[Tid]), NULL, MoverL, &hijo);
            Tid++;
        }

    //************************************

    sleep(0.1);

    //Revisar el camino hacia derecha
    //************************************

    if (hilo.j<g_largo-1) if(matriz[hilo.i][hilo.j+1].tipo!='*' 
        && matriz[hilo.i][hilo.j+1].der==false){
            Hilo hijo={Tid, pasos, i , j+1, Cid};
            if(Cid<15) Cid++;
            else Cid=0;
            pthread_create(&(tid[Tid]), NULL, MoverR, &hijo);
            Tid++;
        }

    //************************************

    sleep(0.1);

    pthread_mutex_unlock(&lock);

    return retorno;
}

bool MirarL(Hilo hilo){
    bool retorno = false;
    int pasos=hilo.pasos, i=hilo.i, j=hilo.j;
    pthread_mutex_lock(&lock);

    //Revisa si hay salida
    //************************************

    if(matriz[hilo.i][hilo.j].tipo=='/'){
            flag=false;
            Hilo hiloL={hilo.id , pasos, i , j, hilo.color};
            hilos[Hid]=hiloL;
            Hid++;
            return false;
    }

    //************************************

    //Revisar el camino hacia izquierda
    //************************************

    if (hilo.j>0)if (matriz[hilo.i][hilo.j-1].tipo!='*' 
        && matriz[hilo.i][hilo.j-1].izq==false) retorno = true;

    //************************************


    //Revisar el camino hacia abajo
    //************************************

    if (hilo.i<g_alto-1) if (matriz[hilo.i+1][hilo.j].tipo!='*' 
        && matriz[hilo.i+1][hilo.j].abajo==false){
            Hilo hijo={Tid, pasos, i+1 , j, Cid};
            if(Cid<15) Cid++;
            else Cid=0;Cid++;
            pthread_create(&(tid[Tid]), NULL, MoverD, &hijo);
            Tid++;
        }

    //************************************

    sleep(0.1);

    //Revisar el camino hacia arriba
    //************************************

    if (hilo.i>0) if(matriz[hilo.i-1][hilo.j].tipo!='*' 
        && matriz[hilo.i-1][hilo.j].arriba==false){
            Hilo hijo={Tid, pasos, i-1 , j, Cid};
            if(Cid<15) Cid++;
            else Cid=0;
            pthread_create(&(tid[Tid]), NULL, MoverU, &hijo);
            Tid++;
        }

    //************************************

    sleep(0.1);

    pthread_mutex_unlock(&lock);

    return retorno;
}

bool MirarD(Hilo hilo){
    bool retorno = false;
    int pasos=hilo.pasos, i=hilo.i, j=hilo.j;
    pthread_mutex_lock(&lock);

    //Revisa si hay salida
    //************************************

    if(matriz[hilo.i][hilo.j].tipo=='/'){
            flag=false;
            Hilo hiloL={hilo.id , pasos, i , j, hilo.color};
            hilos[Hid]=hiloL;
            Hid++;
            return false;
    }

    //************************************

    //Revisar el camino hacia abajo
    //************************************

    if (hilo.i<g_alto-1)if (matriz[hilo.i+1][hilo.j].tipo!='*' 
        && matriz[hilo.i+1][hilo.j].abajo==false) retorno = true;

    //************************************
    

    //Revisar el camino hacia izquierda
    //************************************
    if (hilo.j>0)if(matriz[hilo.i][hilo.j-1].tipo!='*' 
        && matriz[hilo.i][hilo.j-1].izq==false){
            Hilo hijo={Tid, pasos, i , j-1, Cid};
            if(Cid<15) Cid++;
            else Cid=0;
            pthread_create(&(tid[Tid]), NULL, MoverL, &hijo);
            Tid++;
        }

    //************************************

    sleep(0.1);

    //Revisar el camino hacia derecha
    //************************************
    if (hilo.j<g_largo-1) if(matriz[hilo.i][hilo.j+1].tipo!='*' 
        && matriz[hilo.i][hilo.j+1].der==false){
            Hilo hijo={Tid, pasos, i , j+1, Cid};
            if(Cid<15) Cid++;
            else Cid=0;
            pthread_create(&(tid[Tid]), NULL, MoverR, &hijo);
            Tid++;
        }

    //************************************

    sleep(0.1);

    pthread_mutex_unlock(&lock);

    return retorno;
}

bool MirarR(Hilo hilo){
    bool retorno = false;
    int pasos=hilo.pasos, i=hilo.i, j=hilo.j;
    pthread_mutex_lock(&lock);

    //Revisa si hay salida
    //************************************

    if(matriz[hilo.i][hilo.j].tipo=='/'){
            flag=false;
            Hilo hiloL={hilo.id , pasos, i , j, hilo.color};
            hilos[Hid]=hiloL;
            Hid++;
            return false;
    }

    //************************************

    //Revisar el camino hacia derecha
    //************************************

    if (hilo.j<g_largo-1)if (matriz[hilo.i][hilo.j+1].tipo!='*' 
        && matriz[hilo.i][hilo.j+1].der==false) retorno = true;

    //************************************


    //Revisar el camino hacia abajo
    //************************************

    if (hilo.i<g_alto-1) if (matriz[hilo.i+1][hilo.j].tipo!='*' 
        && matriz[hilo.i+1][hilo.j].abajo==false){
            Hilo hijo={Tid, pasos, i+1 , j, Cid};
            if(Cid<15) Cid++;
            else Cid=0;
            pthread_create(&(tid[Tid]), NULL, MoverD, &hijo);
            Tid++;
        }

    //************************************

    sleep(0.1);

    //Revisar el camino hacia arriba
    //************************************

    if (hilo.i>0) if(matriz[hilo.i-1][hilo.j].tipo!='*' 
        && matriz[hilo.i-1][hilo.j].arriba==false){
            Hilo hijo={Tid, pasos, i-1 , j, Cid};
            if(Cid<15) Cid++;
            else Cid=0;
            pthread_create(&(tid[Tid]), NULL, MoverU, &hijo);
            Tid++;
        }

    //************************************

    sleep(0.1);

    pthread_mutex_unlock(&lock);

    return retorno;   
}

void *MoverU(void *arg){
    Hilo hilo=*(Hilo*)arg;

    hilo.pasos++;

    while(MirarU(hilo) && flag){
        pthread_mutex_lock(&lock);
        matriz[hilo.i][hilo.j].arriba=true;
        matriz[hilo.i][hilo.j].out="\u23F6";
        matriz[hilo.i][hilo.j].color=colores[hilo.color];
        hilo.i--;
        hilo.pasos++;
        pthread_mutex_unlock(&lock);
        sleep(1);
    }

    pthread_mutex_lock(&lock);
    matriz[hilo.i][hilo.j].arriba=true;
    matriz[hilo.i][hilo.j].out="\u23F6";
    matriz[hilo.i][hilo.j].color=colores[hilo.color];
    hilo.pasos++;
    pthread_mutex_unlock(&lock);

    int id=hilo.id, pasos=hilo.pasos, i=hilo.i, j=hilo.j, color=hilo.color;
    Hilo hiloL={id, pasos, i , j, color};
    hilos[Hid]=hiloL;
    Hid++;

    return NULL;
}

void *MoverL(void *arg){
    Hilo hilo=*(Hilo*)arg;

    hilo.pasos++;

    while(MirarL(hilo) && flag){
        pthread_mutex_lock(&lock);
        matriz[hilo.i][hilo.j].izq=true;
        matriz[hilo.i][hilo.j].out="\u23F4";
        matriz[hilo.i][hilo.j].color=colores[hilo.color];
        hilo.j--;
        hilo.pasos++;
        pthread_mutex_unlock(&lock);
        sleep(1);
    }

    pthread_mutex_lock(&lock);
    matriz[hilo.i][hilo.j].izq=true;
    matriz[hilo.i][hilo.j].out="\u23F4";
    matriz[hilo.i][hilo.j].color=colores[hilo.color];
    hilo.pasos++;
    pthread_mutex_unlock(&lock);

    int id=hilo.id, pasos=hilo.pasos, i=hilo.i, j=hilo.j, color=hilo.color;
    Hilo hiloL={id, pasos, i , j, color};
    hilos[Hid]=hiloL;
    Hid++;

    return NULL;
}

void *MoverD(void *arg){
    Hilo hilo=*(Hilo*)arg;

    hilo.pasos++;

    while(MirarD(hilo) && flag){
        pthread_mutex_lock(&lock);
        matriz[hilo.i][hilo.j].abajo=true;
        matriz[hilo.i][hilo.j].out="\u23F7";
        matriz[hilo.i][hilo.j].color=colores[hilo.color];
        hilo.i++;
        hilo.pasos++;
        pthread_mutex_unlock(&lock);
        sleep(1);
    }

    pthread_mutex_lock(&lock);
    matriz[hilo.i][hilo.j].abajo=true;
    matriz[hilo.i][hilo.j].out="\u23F7";
    matriz[hilo.i][hilo.j].color=colores[hilo.color];
    hilo.pasos++;
    pthread_mutex_unlock(&lock);

    int id=hilo.id, pasos=hilo.pasos, i=hilo.i, j=hilo.j, color=hilo.color;

    Hilo hiloL={id, pasos, i , j, color};
    hilos[Hid]=hiloL;
    Hid++;

    return NULL;
}

void *MoverR(void *arg){
    Hilo hilo=*(Hilo*)arg;

    hilo.pasos++;

    while(MirarR(hilo) && flag){
        pthread_mutex_lock(&lock);
        matriz[hilo.i][hilo.j].der=true;
        matriz[hilo.i][hilo.j].out="\u23F5";
        matriz[hilo.i][hilo.j].color=colores[hilo.color];
        hilo.j++;
        hilo.pasos++;
        pthread_mutex_unlock(&lock);
        sleep(1);
    }

    pthread_mutex_lock(&lock);
    matriz[hilo.i][hilo.j].der=true;
    matriz[hilo.i][hilo.j].out="\u23F5";
    matriz[hilo.i][hilo.j].color=colores[hilo.color];
    hilo.pasos++;
    pthread_mutex_unlock(&lock);

    int id=hilo.id, pasos=hilo.pasos, i=hilo.i, j=hilo.j, color=hilo.color;
    Hilo hiloL={id, pasos, i , j, color};
    hilos[Hid]=hiloL;
    Hid++;

    return NULL;
}

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
            
            h++;
        }  
    }
}

void printMatriz(){
    
    for(int i = 0; i < g_alto; i++)
    {
        for(int j = 0; j < g_largo; j++)
        {
            if (matriz[i][j].tipo=='0') printf("%s%s%c%s", matriz[i][j].color , matriz[i][j].out,' ', ANSI_COLOR_RESET);

            else{
                if(matriz[i][j].tipo=='*' || matriz[i][j].tipo!='/') 
                    printf("%s%s", matriz[i][j].out, matriz[i][j].out); 
                else printf("%s%c", matriz[i][j].out, ' ');
            }
        }
        printf("\n");
    }
}

void ImpresorT(){
    system("clear");
    pthread_mutex_lock(&lock);
    printMatriz();
    pthread_mutex_unlock(&lock);
    sleep(1);
}


//*******************************************************