#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define TAM 1000
#define TRUE 1
#define FALSE 0

struct no{
    int num;
    int marcado;
};

struct no *gerarVetor(int num){
    int i;
    struct no *conjunto;
    conjunto = (struct no*)malloc(sizeof(struct no)*num);
    for(i = 0; i < num; i++){
        conjunto[i].num = i;
        conjunto[i].marcado = TRUE;
    }
    conjunto[0].marcado = FALSE;
    conjunto[1].marcado = FALSE;
    return conjunto;
}

/*void resetarVetor(struct no* v){
    int i;
    for(i = 2; i < TAM; i++){
        v[i].marcado = FALSE; 
    }
}*/

int main(){

    struct no* v;
    v = gerarVetor(TAM);
    int i, j;

    /*VERSÃO SEQUENCIAL*/
    
    for(i = 2; i < TAM; i++){
        if(v[i].marcado == TRUE){
            for(j = v[i+1].num; j < TAM; j++){
                if(v[j].num % v[i].num == 0) v[j].marcado = FALSE;
            }
        }
    }

    /*teste*/
    int c = 0;
    for(i = 2; i < TAM; i++){
        if(v[i].marcado == TRUE){
            printf("%d\t", v[i].num);
            c++;
        }
    }

    /*VERSÃO MPI*/
    
    
    return 0;
}