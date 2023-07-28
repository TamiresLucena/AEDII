#include <stdio.h>
#include <stdlib.h>

void quicksort(int vetor[], int inicio, int fim){
    int i, j, pivo, aux;

    i = inicio;
    j = fim;

    pivo = vetor[(i + j) /2];

    do{
        while(vetor[i] < pivo) i++; //procurando itens a trocar
        while(vetor[j] > pivo) j--; //procurando itens a trocar

        if(i <= j){
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            i++;
            j--;
        }
    }while (i <= j);

    if(inicio < j) quicksort(vetor, inicio, j);
    if(i < fim) quicksort(vetor, i, fim);

}

int main(){

    printf("Entre com o tamanho do vetor: ");
    int N;
    scanf("%d", &N);

    int vetor[N];

    int i;
    for(i=0; i<N; i++){
        vetor[i] = rand() % 100;
    }

    int inicio = 0;
    int fim = N-1;

    printf("Vetor desordenado: ");
    for(i=0; i<N; i++){
            printf("%d ", vetor[i]);
    }
    printf("\n");

    quicksort(vetor, inicio, fim);

    printf("Vetor ordenado: ");
    for(i=0; i<N; i++){
        printf("%d ", vetor[i]);
    }


    return 0;
}
