#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 100000000
#define TRUE 1
#define FALSE 0

struct no{
    int num;
    int marcado;
};


int main(){
    MPI_Init(NULL, NULL);

    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    float t_inicio, t_fim;

    int *v = NULL, *subvetor = NULL;
    int quantidades =(int)(TAM/nprocs);
    subvetor = malloc(quantidades*sizeof(int));
    
    v = malloc(TAM*sizeof(int));

    int i, j;
    int k = 2;
    int *juncao = NULL;
    for(i = 0; i < TAM; i++){
        v[i] = TRUE;
    }
    juncao = malloc((nprocs*quantidades)*sizeof(int));
    if (rank == 0) {
        t_inicio = MPI_Wtime();
    }
    while((k*k)<=TAM){

        MPI_Scatter(v, quantidades, MPI_INT, subvetor, quantidades, MPI_INT, 0, MPI_COMM_WORLD);
        
        if(rank == 0){
            for(j = k*k; j < quantidades; j++){
                if((j+(quantidades*rank)) % k == 0){
                subvetor[j]= FALSE;   
            }
        }
        }else{
            for(j = 0; j<quantidades; j++){
                if((j+(quantidades*rank)) % k == 0){
                    subvetor[j]= FALSE;
                }
            }
        }

        MPI_Allgather(subvetor, quantidades, MPI_INT, juncao, quantidades, MPI_INT, MPI_COMM_WORLD);
        v = juncao;
        for(j = k+1; j<TAM; j++){
                if(juncao[j] == TRUE){   
                    k = j;
                    break;
                }
        }     
    }

    MPI_Barrier(MPI_COMM_WORLD);   
    int count = 0;
    if(rank == 0){
        for(i = 2; i < TAM; i++){
		    if(v[i] == TRUE){
			count++;
		    }
	    }
        printf("count %d\n", count);
        t_fim = MPI_Wtime();
        printf("Tempo: %.6f\n", t_fim - t_inicio);
    }

    printf("TERMINOU\n");
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}
