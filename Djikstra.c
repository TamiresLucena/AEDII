#include <stdio.h>
#include <stdlib.h>


void Djikstra(TlistaAdj *lista, int inicio, int *antecessor, int *dist){
   int *aux = malloc(lista->tam*sizeof(int));

    int i;
   for(i=0; i < lista->tam ; i++){
      antecessor[i] = -1;
      dist[i] = INF;
   }
   antecessor[inicio] = inicio;
   dist[inicio] = 0;

   Tvertice *percorre;
   for(percorre = lista->adj[inicio]; percorre != NULL; percorre = percorre->prox) {
      dist[percorre->destino] = percorre->peso;
      aux[percorre->destino] = inicio;
   }

   while (TRUE) {
      int indMin, z;
      int mindist = INF;
      for(z = 0; z < lista->tam; ++z){
         if(antecessor[z] == -1 && dist[z] < mindist){
            mindist = dist[z];
            indMin = z;
         }
      }
      if (mindist == INF) break;
      antecessor[indMin] = aux[indMin];
      for(percorre = lista->adj[indMin]; percorre != NULL; percorre = percorre->prox) {
         int destino = percorre->destino;
         int peso = percorre->peso;
         if (dist[indMin] + peso < dist[destino]){
            dist[destino] = dist[indMin] + peso;
            aux[destino] = indMin;
         }
      }
   }
   free(aux);
}
