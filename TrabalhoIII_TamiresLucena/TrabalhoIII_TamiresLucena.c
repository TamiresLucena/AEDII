#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define INF 99999

typedef struct Tvertice{
    int dado;
    float grau;
    float closeness;
    float clustering;
    struct Tvertice *proximo;
}Tvertice;

typedef struct Tgrafo{
    int tamanho;
    Tvertice *adjacente;
}Tgrafo;

void InicializaGrafo(Tgrafo *lista, int N){ //ok
    lista->adjacente = malloc(N*sizeof(Tvertice));
    int i;
    for(i=0; i<N; i++){
        lista->adjacente[i].proximo = NULL;
        lista->adjacente[i].dado = i;
        lista->adjacente[i].grau = 0;
        lista->adjacente[i].closeness = 0;
        lista->adjacente[i].clustering = 0;
    }
    lista->tamanho = N;
}

void Quicksort(Tgrafo *lista, int inicio, int fim){ // ok
    int i, j, pivo;
    Tvertice aux;

    i = inicio;
    j = fim;

    pivo = lista->adjacente[(i + j) /2].dado;

    do{
        while(lista->adjacente[i].dado < pivo) i++;
        while(lista->adjacente[j].dado > pivo) j--;

        if(i <= j){
            aux = lista->adjacente[i];
            lista->adjacente[i] = lista->adjacente[j];
            lista->adjacente[j] = aux;
            i++;
            j--;
        }
    }while (i <= j);

    if(inicio < j) Quicksort(lista, inicio, j);
    if(i < fim) Quicksort(lista, i, fim);

}

void QuicksortGrau(Tgrafo *lista, int inicio, int fim){ // ok
    int i, j;
    float  pivo;
    Tvertice aux;

    i = inicio;
    j = fim;

    pivo = lista->adjacente[(i + j) /2].grau;

    do{
        while(lista->adjacente[i].grau > pivo) i++;
        while(lista->adjacente[j].grau < pivo) j--;

        if(i <= j){
            aux = lista->adjacente[i];
            lista->adjacente[i] = lista->adjacente[j];
            lista->adjacente[j] = aux;
            i++;
            j--;
        }
    }while (i <= j);

    if(inicio < j) QuicksortGrau(lista, inicio, j);
    if(i < fim) QuicksortGrau(lista, i, fim);

}

void QuicksortCloseness(Tgrafo *lista, int inicio, int fim){ // ok
    int i, j;
    float pivo;
    Tvertice aux;

    i = inicio;
    j = fim;

    pivo = lista->adjacente[(i + j) /2].closeness;

    do{
        while(lista->adjacente[i].closeness > pivo) i++;
        while(lista->adjacente[j].closeness < pivo) j--;

        if(i <= j){
            aux = lista->adjacente[i];
            lista->adjacente[i] = lista->adjacente[j];
            lista->adjacente[j] = aux;
            i++;
            j--;
        }
    }while (i <= j);

    if(inicio < j) QuicksortCloseness(lista, inicio, j);
    if(i < fim) QuicksortCloseness(lista, i, fim);

}

void QuicksortClustering(Tgrafo *lista, int inicio, int fim){ // ok
    int i, j;
    float pivo;
    Tvertice aux;

    i = inicio;
    j = fim;

    pivo = lista->adjacente[(i + j) /2].clustering;

    do{
        while(lista->adjacente[i].clustering > pivo) i++;
        while(lista->adjacente[j].clustering < pivo) j--;

        if(i <= j){
            aux = lista->adjacente[i];
            lista->adjacente[i] = lista->adjacente[j];
            lista->adjacente[j] = aux;
            i++;
            j--;
        }
    }while (i <= j);

    if(inicio < j) QuicksortClustering(lista, inicio, j);
    if(i < fim) QuicksortClustering(lista, i, fim);

}

void DjikstraCloseness(Tgrafo *lista, int indorigem){ // ok

    if(lista->adjacente[indorigem].proximo == NULL) return;

    int *aux = malloc(lista->tamanho*sizeof(int));
    float *distancia = malloc(lista->tamanho*sizeof(int));
    int *antecessor = malloc(lista->tamanho*sizeof(int));

    int i;
    for(i=0; i < lista->tamanho ; i++){
        antecessor[i] = -1;
        distancia[i] = INF;
    }
    antecessor[indorigem] = indorigem;
    distancia[indorigem] = 0;

    Tvertice *percorre;
    for(percorre = lista->adjacente[indorigem].proximo; percorre != NULL; percorre = percorre->proximo) {
        int ID = percorre->dado;
        distancia[ID] = 1;
        aux[ID] = indorigem;
    }

    while (1) {
        int indMin, j;
        int mindist = INF;
        for(j = 0; j < lista->tamanho; ++j){
            if(antecessor[j] == -1 && distancia[j] < mindist){
                mindist = distancia[j];
                indMin = j;
            }
        }
        if (mindist == INF) break;

        antecessor[indMin] = aux[indMin];

        for(percorre = lista->adjacente[indMin].proximo; percorre != NULL; percorre = percorre->proximo){
            int destino = percorre->dado;
            float peso = 1;
            if (distancia[indMin] + peso < distancia[destino]){
                distancia[destino] = distancia[indMin] + peso;
                aux[destino] = indMin;
            }
        }
    }
    free(aux);

    float excluir = lista->tamanho-1;
    float total=0;
    for(i=0; i<lista->tamanho; i++){
        if(distancia[i] != INF) total += distancia[i];
        else if(distancia[i] == INF) excluir --;
    }

    float closeness = total/excluir;
    lista->adjacente[indorigem].closeness = closeness;
}

float Clustering(Tgrafo *lista){ // ok
   // float soma = 0;
    //int excluir = lista->tamanho;

    int i;
    Tvertice *aux1, *aux2, *aux3;

    float triangulos;
    for(i=0; i<lista->tamanho; i++){
        triangulos = 0;
        aux1 = lista->adjacente[i].proximo;
        while(aux1 != NULL){
            aux2 = lista->adjacente[aux1->dado].proximo;
            while(aux2!=NULL){
                if(aux2->dado == i) aux2 = aux2->proximo;
                if(aux2 == NULL) break;
                aux3 = lista->adjacente[aux2->dado].proximo;
                while(aux3 != NULL){
                    if(aux3->dado == i) {
                        triangulos++;
                    }
                    aux3 = aux3->proximo;
                }
                aux2 = aux2->proximo;
            }
            aux1 = aux1->proximo;
        }

        //lista->adjacente[i].clustering = triangulos;

        if (lista->adjacente[i].grau > 1) {// se há conexão
            lista->adjacente[i].clustering = (2*triangulos)/(lista->adjacente[i].grau*(lista->adjacente[i].grau-1));
           // soma = soma + (2*triangulos)/(lista->adjacente[i].grau*(lista->adjacente[i].grau-1));
        }

        else{
            lista->adjacente[i].clustering = 0;
            //excluir --;
        }

    }


    /*float media = soma/lista->tamanho;
    printf("%.4f", media);*/

}

void InsereGrafo(Tgrafo *lista, int vorigem, int vdestino){ //ok

    Tvertice *aux = malloc(sizeof(Tvertice));
    aux->dado = vdestino;
    aux->proximo = NULL;

    if(lista->adjacente[vorigem].proximo == NULL) lista->adjacente[vorigem].proximo = aux;

    else if(lista->adjacente[vorigem].proximo != NULL){
        if(lista->adjacente[vorigem].proximo->dado > aux->dado){
            aux->proximo = lista->adjacente[vorigem].proximo;
            lista->adjacente[vorigem].proximo = aux;
        }
        else{
            Tvertice *percorre = lista->adjacente[vorigem].proximo;
            while (percorre->proximo != NULL && percorre->proximo->dado < aux->dado){
            percorre = percorre->proximo;
            }
            aux->proximo = percorre->proximo;
            percorre->proximo = aux;
        }
    }
    lista->adjacente[vorigem].grau ++;

}

void ImprimeGrafo(Tgrafo *lista, FILE *inteiro){ // ok
    int i=0;
    Tvertice *percorre = lista->adjacente[i].proximo;
    while(i < lista->tamanho){
        fprintf(inteiro, "Vértice: %d - Grau: %.4f - Closeness: %.4f - Clustering: %.4f\n", lista->adjacente[i].dado, lista->adjacente[i].grau, lista->adjacente[i].closeness, lista->adjacente[i].clustering);
        fprintf(inteiro, "Vertice: %d |", lista->adjacente[i].dado);
        while(percorre != NULL){
            fprintf(inteiro, "%d ", percorre->dado);
            percorre = percorre->proximo;
        }
        i++;
        percorre = lista->adjacente[i].proximo;
        fprintf(inteiro, "\n\n");
    }
    fprintf(inteiro, "\n");
}

float GrauVertice(Tgrafo *lista){ // ok
    int i=0;
    float soma = 0;
    Tvertice *percorre = lista->adjacente[i].proximo;
    while(i < lista->tamanho){
        int cont = 0;
        while(percorre != NULL){
            cont ++;
            percorre = percorre->proximo;
        }
        lista->adjacente[i].grau = cont;
        //printf("grau: %d\n", lista->adjacente[i].grau);
        i++;
        percorre = lista->adjacente[i].proximo;
        soma = soma + cont;
    }
    return soma;
}

int main(){

    setlocale(LC_ALL, "Portuguese");

    Tgrafo lista;
    InicializaGrafo(&lista, 1005);

    FILE *arquivo = fopen("TrocadeEmails.txt", "r");

    int vorigemtemp;
    int vdestinotemp;
    int idtemp;
    int i;


    //FILE *v1 = fopen("v1.txt", "w");
    //FILE *v2 = fopen("v2.txt", "w");

   while(fscanf(arquivo, "%d", &idtemp) != EOF){

            vorigemtemp = idtemp;
           // fprintf(v1, "%d\n", vorigemtemp);
            fscanf(arquivo, "%d", &idtemp);
            vdestinotemp = idtemp;
            //fprintf(v2, "%d\n", vdestinotemp);

            InsereGrafo(&lista, vorigemtemp, vdestinotemp);
    }
    //fclose(v1);
    //fclose(v2);

    FILE *grau = fopen("Grau.txt", "w");
    FILE *closeness = fopen("Closeness.txt", "w");
    FILE *clustering = fopen("Clustering.txt", "w");
    FILE *inteiro = fopen("Inteiro.txt", "w");

    float soma = GrauVertice(&lista);
    QuicksortGrau(&lista, 0, lista.tamanho-1);
    fprintf(grau, "Vertice\tGrau\n");
    for (i = 0; i < lista.tamanho; i++)
        fprintf(grau, "%d\t%.2f\n", lista.adjacente[i].dado, lista.adjacente[i].grau);
    fclose(grau);


    for(i=0; i<lista.tamanho; i++){
        DjikstraCloseness(&lista, i);
    }

    QuicksortCloseness(&lista, 0, lista.tamanho-1);
    fprintf(closeness, "Vertice\tCloseness\n");
    for (i = 0; i < lista.tamanho; i++)
        fprintf(closeness, "%d\t%.4f\n", lista.adjacente[i].dado, lista.adjacente[i].closeness);
    fclose(closeness);


    Clustering(&lista);

    QuicksortClustering(&lista, 0, lista.tamanho-1);
    fprintf(clustering, "Vertice\tClustering\n");
    for (i = 0; i < lista.tamanho; i++)
        fprintf(clustering, "%d\t%.4f\n", lista.adjacente[i].dado, lista.adjacente[i].clustering);
    fclose(clustering);

    Quicksort(&lista, 0, lista.tamanho-1);
    fprintf(inteiro, "Troca de emails realizadas por membros de uma grande instituição de pesquisa Européia\n\n");
    fprintf(inteiro, "Soma dos Graus || Arestas: %.4f\n\n", soma);
    ImprimeGrafo(&lista, inteiro);
    fclose(inteiro);


    return 0;
}
