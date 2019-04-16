#include "Celda.c"
#include "Hilo.c"
#define ANSI_COLOR_RESET   "\x1b[0m"

// GLOBALES************************

int g_alto;
int g_largo;
Celda **matriz;
bool flag=true;

char* colores[16]={"\033[22;30m", "\033[22;31m", "\033[22;32m", "\033[22;33m", "\033[22;34m"
, "\033[22;35m", "\033[22;36m", "\033[22;37m", "\033[01;30m", "\033[01;31m", "\033[01;32m"
, "\033[01;33m", "\033[01;34m", "\033[01;35m", "\033[01;36m", "\033[01;37m"}; 

//*********************************

//FUNCIONES DE HILO**************************************

bool Mirar(int i, int j){
    if(matriz[i+1][j].tipo=='0'){
        return true;
    }
    return false;
}

void Mover(char direccion, int i, int j){
    Hilo hilo={1,direccion,0,i,j,colores[3]};
    while(Mirar(i,j)){
        matriz[i][j].color=hilo.color;
        matriz[i][j].abajo=true;
        i++;
        sleep(3);
    }
    flag=false;
}

void *MoverP(void *arg){
    Hilo *hilo=(Hilo*)arg;
    while(Mirar(hilo->i,hilo->j) && flag){
        matriz[hilo->i][hilo->j].color=hilo->color;
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
        usleep(3);
    }
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
    for(int i = 0; i < g_alto; i++)
    {
        for(int j = 0; j < g_largo; j++)
        {
            if (caracteres[h]==' '){
                caracteres[h]='0';   
            }

            Celda celda={caracteres[h],0,0,0,0,ANSI_COLOR_RESET};
            matriz[i][j]= celda;
            
            h++;
        }  
    }
}

void printMatriz(){
    for(int i = 0; i < g_alto; i++)
    {
        for(int j = 0; j < g_largo; j++)
        {
            if (matriz[i][j].tipo=='0') printf("%s%c%s", matriz[i][j].color ,matriz[i][j].tipo, ANSI_COLOR_RESET);

            else printf("%c",matriz[i][j].tipo);
        }
        printf("\n");
    }
}

bool check(int i , int j){
    printf("%c",matriz[i][j].tipo);
    return false;
}

//*******************************************************