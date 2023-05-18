#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){

    int i, j;
    int c = 0;

    #pragma omp parallel num_threads(4)
    {
        for(i = 0; i < 10; i++){
            printf("Thread: %d\ti: %d\n", omp_get_thread_num(), i);
            if(omp_get_thread_num() == 0){
                printf("OLA");
                c++;
            }
            #pragma omp for
            for(j = 0; j < 10; j++){
                printf("Thread %d: %d\n", omp_get_thread_num(), j);
            }
            #pragma omp barrier
        }
        
    }

    printf("\nC: %d\n", c);

    return 0;
}