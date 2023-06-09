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

int main(){
	
	struct no* v;
    v = gerarVetor(TAM);
    int i;

    /*VERSÃO SEQUENCIAL*/
	double inicio = omp_get_wtime();
	int k = 2;
	while((k*k) <= TAM){
		//printf("K: %d\n", k);
		//printf("OK\n");
		for(i = k*k; i < TAM; i++){
			if(v[i].num % k == 0) v[i].marcado = FALSE;
		}
		for(i = k + 1; i < TAM; i++){
			//printf("i: %d\n", v[i].num);
			//printf("v[i]: %d\n", v[i].marcado);
			if(v[i].marcado == TRUE){
				k = v[i].num;
				break;
			}
		}
	}
	double fim = omp_get_wtime();
	printf("Tempo %f", fim - inicio);
	return 0;
}