#include <stdio.h>
#include <stdlib.h>

void selecao(int vetor[], int N){
    int i, j, menor, indice, aux;

    for(i=0; i<N; i++){
        menor = vetor[i];
        indice = i;
        for(j=i+1; j<N; j++){
            if(vetor[j] < menor){
                menor = vetor[j];
                indice = j;
            }
        }
        aux = vetor[i];
        vetor[i] = vetor[indice];
        vetor[indice] = aux;
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

    selecao(vetor, N);

    return 0;
}
