#include <stdio.h>
#include <stdlib.h>

void insercao(int vetor[], int N){
    int i, j, aux;

    for(i=1; i<N; i++){
        j=i-1;
        while(j>=0 && vetor[j+1] < vetor[j]){
            aux = vetor[j+1];
            vetor[j+1] = vetor[j];
            vetor[j] = aux;
            j--;
        }
    }

    printf("ordenado: ");
    for(i=0; i<N; i++){
        printf("%d ", vetor[i]);
    }

}



int main(){

    int N;
    scanf("%d", &N);

    int vetor[N];

    int i;
    for(i=0; i<N; i++){
        vetor[i] = rand() % 100;
    }

    printf("desordenado: ");
    for(i=0; i<N; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");

    insercao(vetor, N);


    return 0;
}
