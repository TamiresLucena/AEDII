#include <stdio.h>
#include <stdlib.h>
#define INFINITO 99999

typedef struct Tvertice{
    int origem;
    int destino;
    int peso;
}Tvertice;

typedef struct TlistaAdj{
    int nvertices;
    int narestas;
    Tvertice *adj;
}TlistaAdj;


void BellmanFord (TlistaAdj *lista, int V){
    int i, j, o, d, peso;

    int *distancia = malloc(sizeof(int));

    for(i=0; i<lista->nvertices; i++) distancia[i] = INFINITO;

    distancia[V] = 0;
    Tvertice *percorre;

    for (i=V; i<lista->nvertices; i = (i+1)%5){
        percorre = lista->adj[i];
        while(percorre!=NULL){
            if(distancia[percorre.origem]+ percorre.peso < distancia[percorre.destino]){
                distancia[percorre.destino] = distancia[percorre.origem] + percorre.peso;
            }
            percorre = percorre->prox;
        }
    }

    for (i=V; i<lista->nvertices; i = (i+1)%5){
        percorre = lista->adj[i];
        while(percorre!=NULL){
            if(distancia[percorre.origem]+ percorre.peso < distancia[percorre.destino]) printf ("lista contem ciclos com pesos negativos.");
        }
    }
}






int main(){

    return 0;
}
