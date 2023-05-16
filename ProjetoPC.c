#include <stdio.h>
#include <stdlib.h>

#define TAM 100
#define TRUE 1
#define FALSE 0

struct no{
    int num;
    int marcado;
};


int main(){

    int i;
    struct no conjunto[TAM];
    for(i = 0; i < TAM; i++){
        conjunto[i].num = i;
        conjunto[i].marcado = FALSE;
    }
    conjunto[0].marcado = TRUE;
    conjunto[1].marcado = TRUE;
    

    /*VERSÃO SEQUENCIAL*/
    
    for(i = 2; i < TAM; i++){
        if(i != 2 && i != 3 && i != 5 && i != 7){
            if(conjunto[i].num % 2 == 0 || conjunto[i].num % 3 == 0 || conjunto[i].num % 5 == 0 || conjunto[i].num % 7 == 0){
                conjunto[i].marcado = TRUE;
            }
        }
    }
    /*teste*/
    for(i = 2; i < TAM; i++){
        if(conjunto[i].marcado == 0) printf("%d\t", conjunto[i].num);
    }
    
    return 0;
}