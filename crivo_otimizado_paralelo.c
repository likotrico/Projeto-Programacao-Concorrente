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
    int i, j;
    
	int k = 2;
	
	#pragma omp parallel num_threads(2) shared(k)
	{
		while((k*k) <= TAM){
			
			#pragma omp barrier
			#pragma omp for
			for(i = k*k; i < TAM; i++){
				if(v[i].num % k == 0) v[i].marcado = FALSE;
			}
			
			if(omp_get_thread_num() == 0){
				for(i = k + 1; i < TAM; i++){
					if(v[i].marcado == TRUE){
						k = v[i].num;
						break;
					}
				}
			}
			#pragma omp barrier
		}
	}
	
	int count = 0;
	for(i = 2; i < TAM; i++){
		if(v[i].marcado == TRUE){
			//printf("%d\t", i);
			count++;
		}
	}
	
	printf("\nCount:%d\n", count);
	
	return 0;
}









