#include <stdio.h>
#include <stdlib.h>


void Merge(int vetor[], int inicio, int fim){
    int i, j, k, metade;
    int vetorAux[inicio + fim + 1];
    if(inicio == fim) return;
    metade = (inicio + fim) / 2;

    Merge(vetor, inicio, metade);
    Merge(vetor, metade+1, fim);

    i = inicio;
    j = metade + 1;
    k = 0;

    while(i < metade+1 || j < fim +1){
        if(i == metade +1){
            vetorAux[k] = vetor[j];
            j++;
            k++;
        }
        else {
            if(j == fim +1){
                vetorAux[k] = vetor[i];
                i++;
                k++;
            }
            else{
                if(vetor[i] < vetor[j]){
                    vetorAux[k] = vetor[i];
                    i++;
                    k++;
                }
                else{
                    vetorAux[k] = vetor[j];
                    j++;
                    k++;
                }
            }
        }
    } // fim do while

    for(i= inicio; i<= fim; i++){
        vetor[i] = vetorAux[i-inicio];
    }

}




int main(){

    int N, i;
    scanf("%d", &N);

    int vetor[N];

    for(i=0; i<N;i++){
        scanf("%d", &vetor[i]);
    }

    printf("Desordenado: ");
    for(i=0; i<N;i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");

    Merge(vetor, 0, N-1);


    printf("Ordenado: ");
    for(i=0; i<N;i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");

    return 0;
}