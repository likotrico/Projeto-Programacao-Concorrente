#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define TAM 100000000
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

void resetarVetor(struct no* v){
    int i;
    for(i = 2; i < TAM; i++){
        v[i].marcado = TRUE; 
    }
}

int main(){

    struct no* v;
    v = gerarVetor(TAM);

    int i = 2, j;
    int c = 0, n = 0;

    #pragma omp parallel num_threads(4) shared(c, n) 
    {
        while(1){
            #pragma omp barrier
            if(i >= TAM) break;
            //printf("Thread %d no i %d\n", omp_get_thread_num(), i);
            if(v[i].marcado == TRUE){
                #pragma omp for
                for(j = v[i+1].num; j < TAM; j++){
                    if(v[j].num % v[i].num == 0) v[j].marcado = FALSE;
                    //printf("Thread %d no j %d\n", omp_get_thread_num(), j);
                }
            }
            #pragma omp barrier
            if(omp_get_thread_num() == 0){
                i++;
                c++;
            }
        }
    }

    printf("\nC: %d\n", c);

    /*TESTE*/
    for(i = 2; i < TAM; i++){
        if(v[i].marcado == TRUE){
            //printf("%d\t", v[i].num);
            n++;
        }
    }

    printf("\nN: %d\n", n);

    return 0;
}