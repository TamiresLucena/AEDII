#include <stdio.h>
#include <stdlib.h>


void contagem(int vetorA[], int N){
    int i, maior;

    maior = vetorA[0];
    for(i=1; i<N; i++){
        if(vetorA[i] > maior){
            maior = vetorA[i];
        }
    } //achou o maior numero, que sera o tamanho do vetorB

    int vetorB[maior+1];

    for(i=0; i<maior+1; i++){
        vetorB[i] = 0;
    } //inicializa vetorB com 0

    for(i=0; i<N; i++){
        vetorB[vetorA[i]]++;
    } //percorre vetorA contando quantos numeros há de cada

    for(i=1; i<maior+1; i++){
        vetorB[i] = vetorB[i] + vetorB[i-1];
    } //soma o conteudo de cada indice com seu anterior


    int vetorC[N];

    for(i=0; i<N; i++){
        vetorC[vetorB[vetorA[i]]-1] = vetorA[i];
        vetorB[vetorA[i]]--;
    }


    for(i=0; i<N; i++){
        printf("%d ", vetorC[i]);
    }

    printf("\n");

}





int main(){


 int N;
    scanf("%d", &N);

    int vetorA[N];

    int i;
    for(i=0; i<N; i++){
        vetorA[i] = rand() % 100;
    }

    printf("n ordenado: ");

    for(i=0; i<N; i++){
        printf("%d ", vetorA[i]);
    }
    printf("\n");

    contagem(vetorA, N);


    return 0;
}
