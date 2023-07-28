#include <stdio.h>
#include <stdlib.h>

void bolha(int vetor[], int N){
    int i, j, aux;

    for(i=0; i<N; i++){
        for(j=i+1; j<N; j++){
            if(vetor[j] < vetor[i]){
                aux = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = aux;
            }
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

    bolha(vetor, N);


    return 0;
}
