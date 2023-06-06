#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 20
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

    
    int *v = NULL, *subvetor = NULL;
    int quantidades =(int)(TAM/nprocs);
    if(rank == 0) printf("quantidades: %d\n", quantidades);
    subvetor = malloc(quantidades*sizeof(int));
    
    /*CRIANDO O TIPO DE DADO MPI_STRUCT NO*/
    //MPI_Datatype mpino;
    //MPI_Type_create_resized( MPI_INT, 0, sizeof(struct no), &mpino);
    // MPI_Type_contiguous(2, MPI_Type_struct, &mpino);
    // MPI_Type_commit( &mpino );

    v = malloc(TAM*sizeof(int));

    int i, j;
    int k = 2;
    int *juncao = NULL;
    for(i = 0; i < TAM; i++){
        v[i] = TRUE;
    }
    juncao = malloc((nprocs)*sizeof(int));
    while((k*k)<=TAM){

        //MPI_Barrier(MPI_COMM_WORLD);   
        MPI_Scatter(v, quantidades, MPI_INT, subvetor, quantidades, MPI_INT, 0, MPI_COMM_WORLD);
        printf("Chegou k%d rank%d\n", k, rank);
        
        if(rank == 0){
            for(j = k*k; j < quantidades; j++){
                if((j+(quantidades*rank)) % k == 0){
                subvetor[j]= FALSE;
                printf("Rank: %d; marcado: %d num: %d k:%d\n", rank, subvetor[j], j, k);    
            }
        }
        }else{
            for(j = 0; j<quantidades; j++){
            if((j+(quantidades*rank)) % k == 0){
                subvetor[j]= FALSE;
                printf("Rank: %d; marcado: %d num: %d k:%d\n", rank, subvetor[j], j, k);
            }
        }
        }
        
        
        printf("Chegou k%d rank%d\n", k, rank);
        
        

        //MPI_Barrier(MPI_COMM_WORLD);
        MPI_Allgather(subvetor, quantidades, MPI_INT, juncao, quantidades, MPI_INT, MPI_COMM_WORLD);
        
        v = juncao;
        // if(rank == 1){
        //     for(i = 0; i < TAM; i++){
        //     if(v[i] == TRUE) printf("Rank%d - V:%d\t", rank, i);
        // }
        // }
        for(j = k+1; j<TAM; j++){
                if(juncao[j] == TRUE){   
                    k = j;
                    printf("k: %d\n", k);        
                    break;
                }
        }
        // free(juncao);
        // juncao = NULL;
        //MPI_Barrier(MPI_COMM_WORLD);   
        
    }
    printf("OK");    

    MPI_Barrier(MPI_COMM_WORLD);   
    if(rank == 0){
        printf("PRIMOS:\n");
        for(i = 2; i < TAM; i++){
		    if(v[i] == TRUE){
			printf("[%d|%d]\t", i, v[i]);
			//count++;
		    }
	    }
    }

    printf("TERMINOU\n");
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}