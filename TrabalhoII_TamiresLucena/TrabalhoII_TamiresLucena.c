#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#define T 2
#define MAX 5000

typedef struct TitemLista{
    char palavra[25];
    int qnt;
    struct TitemLista *prox, *ant;
}TitemLista;

typedef struct Tlista{
    TitemLista *inicio, *fim;
    int tamanho;
}Tlista;

typedef struct Titem{
    int cod;
    char titulo[100];
    TitemLista vetor[MAX];
}Titem;

typedef struct Tno{
    Titem item[2*T-1];
    struct Tno *filhos[2*T];
    int qntitem;
}Tno;

typedef struct TarvoreB{
    Tno *raiz;
}TarvoreB;

void InicializaB(TarvoreB *arvore){
    arvore->raiz = NULL;
}

void InicializaLista(Tlista *lista){
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->tamanho = 0;
}

void InsereLista(Tlista *lista, char *palavratemp){

    TitemLista *aux = malloc(sizeof(TitemLista));
    strcpy(aux->palavra, palavratemp);
    aux->prox = NULL;
    aux->ant = NULL;
    aux->qnt = 1;


    if(lista->inicio == NULL){
        lista->fim = aux;
        lista->inicio = aux;
    }

    else{
        TitemLista *percorre = lista->inicio;

        while(percorre != NULL){
            if(strcmp(percorre->palavra, palavratemp) == 0){
                percorre->qnt ++;
                return;
            }
            else percorre = percorre->prox;
        } // verifica se palavra ja existe e incrementa

        lista->fim->prox = aux;
        aux->ant = lista->fim;
        lista->fim = aux;
        aux->prox = NULL;
    }

   lista->tamanho ++;

}

void ImprimeLista(Tlista *lista){
    TitemLista *percorre;
    percorre = lista->inicio;

    while(percorre != NULL){
        printf("%s %d\n", percorre->palavra, percorre->qnt);
        percorre = percorre->prox;
    }
    return;
}

void RemoverPontuacao(FILE *fIn, FILE *fOut){
    char cAux;

    while(fscanf(fIn, "%c", &cAux) != EOF){
        if(cAux == '\n' || !(cAux >= 0 && cAux <= 31 || cAux >= 33 && cAux <= 47 || cAux >= 58 && cAux <= 64 || cAux >= 91 && cAux <= 96 || cAux >= 123 && cAux <= 127)){
            fprintf(fOut, "%c", tolower(cAux));
        }
    }
}

int VerificaStopWords(Tlista *STOP, char *palavra){
    TitemLista *percorre = STOP->inicio;

    while(percorre != NULL){
        if(strcmp(percorre->palavra, palavra) == 0) return 1; // É STOPPP
        else percorre = percorre->prox;
    }
    return 0;
}

void Shellsort(TitemLista vetor[], int N, int inc[], int ninc){
    int incr, i, j, h;
    TitemLista aux;

    for(incr=0; incr<ninc; incr++){
        h=inc[incr];
        for(i=h; i<N; i++){
            aux = vetor[i];
            for(j=i-h; j>=0 && vetor[j].qnt<aux.qnt; j-=h){
                vetor[j+h]=vetor[j];

            }
            vetor[j+h]=aux;
        }
    }
}

Titem Quebrar(Tno *no, Tno *dir){

    int med = (no->qntitem-1)/2;
    Titem meio = no->item[med];

    dir->qntitem = T-1;
    dir->filhos[med] = no->filhos[no->qntitem];

    int i;
    for(i=0; i<med; i++){
        dir->item[i] = no->item[i + med+1];
        dir->filhos[i] = no->filhos[i + med+1];
    }
    no->qntitem = T-1;

    return meio;
}

void EmpurrarItens(Tno *no, int indice){

    int i;
    for(i=no->qntitem-1; i>=indice; i--){
        no->item[i+1] = no->item[i];
        no->filhos[i+2] = no->filhos[i+1];
    }
}

void InsereArvore(TarvoreB *arvore, Titem novoitem, int tamvetor){
    int i, j, indice;

    if(arvore->raiz == NULL){ // novo no

        Tno *novo = malloc(sizeof(Tno));

        novo->item[0] = novoitem;
        novo->qntitem = 1;
        novo->filhos[0] = NULL;
        novo->filhos[1] = NULL;
        arvore->raiz = novo;
    }
    else {
        if (arvore->raiz->qntitem == 2*T-1){ // raiz sobe se no esta cheio

            Tno *novo = malloc(sizeof(Tno));
            Tno *dir =  malloc(sizeof(Tno));

            novo->item[0] = Quebrar(arvore->raiz, dir);
            novo->filhos[0] = arvore->raiz;
            novo->filhos[1] = dir;
            novo->qntitem = 1;
            arvore->raiz = novo;

        }

        Tno *percorre = arvore->raiz;
        while (percorre->filhos[0] != NULL){
            for(i=0; i<percorre->qntitem; i++){
                if(novoitem.cod < percorre->item[i].cod)
                    break;
            }

            if (i == percorre->qntitem){
                if (percorre->filhos[percorre->qntitem]->qntitem == 2*T-1){

                    Tno *dir = malloc(sizeof(Tno));

                    percorre->item[percorre->qntitem] = Quebrar(percorre->filhos[percorre->qntitem], dir);
                    percorre->filhos[percorre->qntitem+1] = dir;
                    percorre->qntitem++;
                }
                if (novoitem.cod < percorre->item[percorre->qntitem-1].cod)
                    percorre = percorre->filhos[percorre->qntitem-1];
                else
                    percorre = percorre->filhos[percorre->qntitem];
            }
            else {
                if (percorre->filhos[i]->qntitem == 2*T-1){

                    EmpurrarItens(percorre, i);

                    Tno *dir = (Tno*) malloc(sizeof(Tno));

                    percorre->item[i] = Quebrar(percorre->filhos[i], dir);
                    percorre->filhos[i+1] = dir;
                    percorre->qntitem++;
                }
                if (novoitem.cod < percorre->item[i].cod)
                    percorre = percorre->filhos[i];
                else
                    percorre = percorre->filhos[i+1];
            }
        }// sai do while -> encontrei folha

        indice = 0;
        while (indice < percorre->qntitem && novoitem.cod > percorre->item[indice].cod) indice++;

        if (indice < percorre->qntitem)
            EmpurrarItens(percorre, indice);

        percorre->item[indice] = novoitem;
        percorre->filhos[indice+1] = NULL;
        percorre->qntitem++;
    }
}

void PuxarItens(Tno *n, int indice){
    int i;
    for (i = indice; i < n->qntitem-1; i++){
        n->item[i] = n->item[i+1];
        n->filhos[i+1] = n->filhos[i+2];
    }
}

void Unir(Tno *n, int indice){
    Titem meio = n->item[indice];
    Tno *esq = n->filhos[indice];
    Tno *dir = n->filhos[indice+1];

    esq->item[esq->qntitem] = meio;
    esq->filhos[esq->qntitem+1] = dir->filhos[0];
    int i;
    for (i = esq->qntitem+1; i < 2*T-1; i++){ // aumenta o no, unindo as duas paginas e suas subpaginas
        esq->item[i] = dir->item[i-(esq->qntitem+1)];
        esq->filhos[i+1] = dir->filhos[i-(esq->qntitem)];
    }

    esq->qntitem = 2*T-1;
}

Titem Remover(Tno *no, int indice){

    Titem novoitem = no->item[indice];
    if (no->filhos[0] == NULL){
        PuxarItens(no, indice);
        no->qntitem--;
    }
    else {
        if (no->filhos[indice]->qntitem > T-1){
            no->item[indice] = Remover(no->filhos[indice], no->filhos[indice]->qntitem-1);
        }
        else if(no->filhos[indice+1]->qntitem > T-1){
            no->item[indice] = Remover(no->filhos[indice+1], 0);
        }
        else {// ninguem pode subir ainda -> item desce unindo os dois e o problema de remove-lo eh passado para onde ele foi

            Unir(no, indice);
            PuxarItens(no, indice);
            no->qntitem--;

            Tno *proximo = no->filhos[indice];
            int med = (proximo->qntitem-1)/2;
            return Remover(proximo, med);
        }
    }
    return novoitem;
}

Titem ProcurarParaExcluir(TarvoreB *arvore, int cod){
    int i;
    Tno *aux = arvore->raiz;

    while(aux != NULL){
        for(i=0; i<aux->qntitem; i++){
            if(cod == aux->item[i].cod){
                printf("Texto removido: %s\n", aux->item[i].titulo);
                return Remover(aux, i);
            }
            if(cod < aux->item[i].cod) break;
        }

        if(aux->filhos[0] == NULL) break;

        if(i == aux->qntitem){
            if(aux->filhos[aux->qntitem]->qntitem == T-1){
                if(aux->filhos[aux->qntitem-1]->qntitem == T-1){
                    Unir(aux, aux->qntitem-1);
                    PuxarItens(aux, aux->qntitem-1);
                    aux->qntitem--;
                }
                else {
                    Tno *esq = aux->filhos[aux->qntitem-1];
                    Tno *dir = aux->filhos[aux->qntitem];

                    EmpurrarItens(dir, 0);
                    dir->item[0] = aux->item[aux->qntitem-1];
                    aux->item[aux->qntitem-1] = esq->item[esq->qntitem-1];
                    dir->filhos[0] = esq->filhos[esq->qntitem];
                    esq->qntitem--;
                    dir->qntitem++;
                }
            }
            aux = aux->filhos[aux->qntitem];
        }
        else {
            if (aux->filhos[i]->qntitem == T-1){
                if (aux->filhos[i+1]->qntitem == T-1){
                    Unir(aux, i);
                    PuxarItens(aux, i);
                    aux->qntitem--;
                }
                else {

                    Tno *esq = aux->filhos[i];
                    Tno *dir = aux->filhos[i+1];

                    esq->item[esq->qntitem] = aux->item[i];
                    aux->item[i] = dir->item[0];
                    esq->filhos[esq->qntitem+1] = dir->filhos[0];
                    dir->filhos[0] = dir->filhos[1];
                    PuxarItens(dir, 0);
                    dir->qntitem--;
                    esq->qntitem++;
                }
            }
            aux = aux->filhos[i];
        }
    }
    printf("Texto não encontrado.\n");
    printf("\n");
}

void PesquisaQuery(Tno *no, char *query){

    int i, j;
    if(no != NULL){
        for(i=0; i<no->qntitem; i++){
            j = 0;
            while(no->item[i].vetor[j].qnt > 2){
                if(strcmp(no->item[i].vetor[j].palavra, query) ==0 ){
                        printf("Código: %d - Título: %s \n", no->item[i].cod, no->item[i].titulo);
                        char abrearquivo[20];
                        sprintf(abrearquivo, "%d", no->item[i].cod);

                        strcat(abrearquivo, ".txt");
                        system(abrearquivo);
                    }
                j++;
            }
        }
        if(no->filhos[0] != NULL){
            for(i=0; i<=no->qntitem; i++){
                PesquisaQuery(no->filhos[i], query);
            }
        }
    }
}

void PesquisaCodigo(Tno *no, int cod){
    int i;
    if(no != NULL){
        for(i=0; i<no->qntitem; i++){
            if(no->item[i].cod == cod){
                    printf("Código: %d - Título: %s \n", no->item[i].cod, no->item[i].titulo);
                    char abrearquivo[20];
                    sprintf(abrearquivo, "%d", no->item[i].cod);

                    strcat(abrearquivo, ".txt");
                    system(abrearquivo);
            }
        }
    }

    if(no->filhos[0] != NULL){
        for(i=0; i<=no->qntitem; i++){
            PesquisaCodigo(no->filhos[i], cod);
        }
    }

}

void ImprimeArvoreB(Tno *no, int h){

    if(no != NULL){
        int i;
        for(i=0; i<2*h; i++) printf(" ");
        printf("|");

        for(i=0; i<no->qntitem; i++){
            printf("Código: %d - Título: %s", no->item[i].cod, no->item[i].titulo);
            if(i != no->qntitem-1) printf(",");
        }
        if(no->filhos[0] != NULL){
            for(i=0; i<=no->qntitem; i++){
                ImprimeArvoreB(no->filhos[i], h+1);
            }
        }
    }
}

void ImprimeEmOrdem (Tno *no, int h){
    int i;
    if(no==NULL) return;

    for(i=0;i<no->qntitem;i++){
        ImprimeEmOrdem(no->filhos[i], h+1);
        printf("Código: %d - Título: %s",no->item[i].cod, no->item[i].titulo);
    }
    ImprimeEmOrdem(no->filhos[no->qntitem], h+1);
}

TitemLista *CriaVetor(Tlista *lista){

    TitemLista *vetortemp = malloc(lista->tamanho*sizeof(TitemLista));
    TitemLista *percorre = lista->inicio;

    int i=0;
    while(percorre != NULL){
        strcpy(vetortemp[i].palavra, percorre->palavra);
        vetortemp[i].qnt = percorre->qnt;
        percorre = percorre->prox;
        i++;
    }

    int N = lista->tamanho;
    int ninc = 3;
    int inc[3] = {3, 2, 1};
    Shellsort(vetortemp, N, inc, ninc);

    return vetortemp;
}

TitemLista *LeituraTextos(FILE *arquivo, Tlista *STOP){

    Tlista lista;
    InicializaLista(&lista);

    char palavratemp[25];
    int contador = 0;

    while(fscanf(arquivo, "%s", &palavratemp) != EOF){
        int sw = VerificaStopWords(STOP, palavratemp);
        if(sw == 0){
            InsereLista(&lista, palavratemp);
        }
    }

    return CriaVetor(&lista);
}

void ListaStop(FILE *stopw, Tlista *STOP){

    char stoptemp[25];
    int i = 0;

    while(fscanf(stopw, "%s", &stoptemp) != EOF){
        InsereLista(STOP, stoptemp);
        i++;
    }
}

int main(int argc, char* argv[]){

    setlocale(LC_ALL, "Portuguese");

    printf("Inserindo textos na Árvore...\n");
    printf("\n");

    TarvoreB arvore;
    InicializaB(&arvore);

    Tlista STOP;
    InicializaLista(&STOP);
    FILE *stopw = fopen("Stopwords.txt", "r");
    ListaStop(stopw, &STOP);

    char *filename[31]; //qnt de arquivos
    int j;

    int codigo = 1;

    for(j=0; j<31; j++){

        filename[j] = argv[j+1];

        FILE *arquivo = fopen(filename[j], "r"); //leitura

        char filenovo[20] = "copia";
        strcat(filenovo,filename[j]);


        FILE *copia = fopen(filenovo, "w");
        RemoverPontuacao(arquivo, copia);
        fclose(copia);
        FILE *copiar = fopen(filenovo, "r");

        TitemLista *vetortemp = LeituraTextos(copiar, &STOP);

        int tamvetor=0, i=0;
        while(vetortemp[i].qnt != 0){
            tamvetor ++;
            i++;
        }


        Titem aux;
        FILE *arquivo1 = fopen(filename[j], "r");
        char titulotemp[100];
        fgets(titulotemp, 100, arquivo1);

        strcpy(aux.titulo, titulotemp);
        aux.cod = codigo;
        for(i=0; i<tamvetor; i++){
            strcpy(aux.vetor[i].palavra, vetortemp[i].palavra);
            aux.vetor[i].qnt = vetortemp[i].qnt;
        }


        /*printf("TAMO AQUI NA MAIN\n");
                printf("%s %d\n", aux.titulo, aux.cod);
                printf("vetor: ");
        for(i=0; i<tamvetor; i++){
            if(aux.vetor[i].qnt > 2){
                    printf("%s %d ", aux.vetor[i].palavra, aux.vetor[i].qnt);
            }
        }*/


        InsereArvore(&arvore, aux, tamvetor);
        codigo ++;
   }

        //setlocale(LC_ALL, "Portuguese");

    while(1){

        int escolha;
        int excluir;
        char query[100];
        int impressao;
        int pesquisar;

        printf(".: 1 Imprimir Arvore :: 2 Remover Texto :: 3 Texto por Query :: 4 Texto por Código :.\n");
        scanf("%d", &escolha);


        switch(escolha){

        case 1:
            printf(" .: 1 Em Ordem :: 2 Pré Ordem :.\n");
            scanf("%d", &impressao);
            if(impressao == 1) ImprimeEmOrdem(arvore.raiz, 0);
            else if(impressao == 2) ImprimeArvoreB(arvore.raiz, 0);

            printf("\n");
            break;

        case 2:
            printf("Entre com código do texto que deseja remover: ");
            scanf("%d", &excluir);
            ProcurarParaExcluir(&arvore, excluir);
            break;

        case 3:
            printf("Entre com a palavra que deseja pesquisar: ");
            scanf("%s", query);

            PesquisaQuery(arvore.raiz, strlwr(query));
            printf("Não há textos a exibir\n");
            printf("\n");
            break;

        case 4:
            printf("Entre com código do texto que deseja pesquisar: ");
            scanf("%d", &pesquisar);
            PesquisaCodigo(arvore.raiz, pesquisar);
            printf("\n");
            break;

        }
    }

    return 0;
}
