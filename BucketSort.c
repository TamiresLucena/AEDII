#include <stdio.h>
#include <stdlib.h>

typedef struct Titem{
    struct Titem *prox;
    float n;
}Titem;

void insere(float n, Titem ** pdig, int i){
    Titem *aux = malloc(sizeof(Titem));
    aux->n = n;
    aux->prox = NULL;

    if(pdig[i] == NULL) pdig[i] = aux;
    else{
        if(pdig[i]->n > aux->n){
            aux->prox = pdig[i];
            pdig[i] = aux;
        }
        else{
            Titem *percorre = pdig[i];
            while (percorre->prox != NULL && percorre->prox->n < aux->n){
                percorre = percorre->prox;
            }
            aux->prox = percorre->prox;
            percorre->prox = aux;
        }
    }
}

void bucket(float vetor[], int N){
    int i, j;
    int novoAux;

    Titem** pdig = malloc(10*sizeof(Titem*));
    for(i=0; i<10; i++) pdig[i] = NULL;

    for(i=0; i<N; i++){
        novoAux = vetor[i]*10;
        insere(vetor[i], pdig, novoAux);
    }

    j=0;
    Titem *remove;
    for(i=0; i<10; i++){
        while(pdig[i] != NULL){
            vetor[j] = pdig[i]->n;
            j++;
            remove = pdig[i];
            pdig[i] = pdig[i]->prox;
            free(remove);
        }
    }

    printf("ordenado: ");
    for(i=0; i<N; i++){
        printf("%f ", vetor[i]);
    }
    printf("\n");
}


int main(){
    int N;
    scanf("%d", &N);

    float vetor[N];

    int i;
    for(i=0; i<N; i++){
        vetor[i] = (rand() % 999);
    }

    for(i=0; i<N; i++){
        vetor[i] = vetor[i]/1000;
    }

    printf("nao ordenado: ");
    for(i=0; i<N; i++){
        printf("%f ", vetor[i]);
    }
    printf("\n");

    bucket(vetor, N);

    return 0;
}
