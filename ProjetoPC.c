#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>
#include <time.h>

#define TAM 100000
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
    time_t t;
    srand((unsigned) time(&t));

    struct no* v;
    v = gerarVetor(TAM);
    int i, j;

    /*VERSÃO SEQUENCIAL*/
    double inicio = omp_get_wtime();
    for(i = 2; i < TAM; i++){
        if(v[i].marcado == TRUE){
            for(j = v[i+1].num; j < TAM; j++){
                if(v[j].num % v[i].num == 0) v[j].marcado = FALSE;
            }
        }
    }
    double fim = omp_get_wtime();
    double tSerial = fim - inicio;
    printf("Execucao Serial: %fseg\n", tSerial);

    /*teste*/

    struct no* v_;
    v_ = gerarVetor(TAM);
    
    /*VERSÃO OPENMP*/
    inicio = omp_get_wtime(); 
    
            #pragma omp parallel num_threads(4)
            {
                for(i = 2; i < TAM; i++){
                    if(v_[i].marcado == TRUE){
                        #pragma omp parallel for 
                        for(j = v_[i+1].num; j < TAM; j++){
                            if(v_[j].num % v_[i].num == 0) v_[j].marcado = FALSE;
                        }
                    }
                }
            }
            
        
    
    fim = omp_get_wtime();
    tSerial = fim - inicio;
    printf("Execucao openmp: %fseg\n", tSerial);
    printf("\n");

    /*int c = 0;
    int c_s = 0;
    for(i = 2; i < TAM; i++){
        if(v[i].marcado == TRUE){
            printf("%d\t", v[i].num);
            c_s++;
        }

        if(v_[i].marcado == TRUE){
            printf("%d\t", v_[i].num);
            c++;
        }
    }
    printf("count: %d\t%d", c, c_s);*/

    /*VERSÃO MPI*/
    
    
    return 0;
}