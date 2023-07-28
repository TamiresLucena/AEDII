#include <stdio.h>
#include <stdlib.h>

typedef struct Tno{
    int info;
    int altura;
    struct Tno *esquerda;
    struct Tno *direita;
}Tno;

typedef struct TarvoreAVL{
    Tno *raiz;
}TarvoreAVL;

int Maior(int a, int b){
    return (a > b)? a : b;
}

int altura(Tno *raiz) {
    if (raiz == NULL)
        return -1;
    else return Maior(altura(raiz->esquerda), altura(raiz->direita)) +1;
}

int fb(Tno *raiz){
    if (raiz == NULL)
        return 0;
    return (altura(raiz->direita) - altura(raiz->esquerda));
}

Tno *RotacaoDireita(Tno *no){
    printf("rotac dir\n");
    Tno *aux = no->esquerda;
    no->esquerda = aux->direita;
    aux->direita = no;
    return aux;
}

Tno *RotacaoEsquerda(Tno *no){
    printf("rotac esq\n");
    Tno *aux = no->direita;
    no->direita = aux->esquerda;
    aux->esquerda = no;
    return aux;
}

Tno *RotacaoDuplaDireita(Tno *no){
    no->esquerda = RotacaoEsquerda(no->esquerda);
    no = RotacaoDireita(no);
    return no;
}

Tno *RotacaoDuplaEsquerda(Tno *no){
    no->direita = RotacaoDireita(no->direita);
    no = RotacaoEsquerda(no);
    return no;
}

Tno *Insere(Tno *raiz, int info){
    if(raiz == NULL) {
        Tno *aux = (Tno*) malloc(sizeof(Tno));
        aux->info = info;
        //aux->altura = 1;
        aux->esquerda = NULL;
        aux->direita = NULL;
        return aux;
    }

    else {
        if(info < raiz->info) raiz->esquerda = Insere(raiz->esquerda, info);
        else raiz->direita = Insere(raiz->direita, info);
    }

    printf("info: %d no %d esq %d dir %d\n", raiz->info, fb(raiz), fb(raiz->esquerda), fb(raiz->direita));
    if(raiz->esquerda != NULL) printf("esq %d \n", raiz->esquerda->info);
    if(raiz->direita != NULL) printf("dir %d \n", raiz->direita->info);
     if(fb(raiz) == -2 || fb(raiz) == 2){
         if(fb(raiz->esquerda) == -1) raiz = RotacaoDireita(raiz);
         if(fb(raiz->direita) == 1) raiz = RotacaoEsquerda(raiz);
         if(fb(raiz->esquerda) == 1) raiz = RotacaoDuplaDireita(raiz);
         if(fb(raiz->direita) == -1) raiz = RotacaoDuplaEsquerda(raiz);
     }

     /*if(fb(raiz) == 2){
         if(fb(raiz->direita) == 1) raiz = RotacaoEsquerda(raiz);
         if(fb(raiz->esquerda) == -1) raiz = RotacaoDuplaEsquerda(raiz);
     }*/

    return raiz;
}

void ImprimeEmOrdem(Tno *raiz) {
    if(raiz != NULL) {
        ImprimeEmOrdem(raiz->esquerda);
        printf("%d ", raiz->info);
        ImprimeEmOrdem(raiz->direita);
    }
}

void ImprimePosOrdem(Tno *raiz) {
    if(raiz != NULL) {
        ImprimeEmOrdem(raiz->esquerda);
        ImprimeEmOrdem(raiz->direita);
        printf("%d ", raiz->info);
    }
}

void imprime(Tno *no){
	if (no != NULL) {
		printf("(%d", no->info);
		imprime(no->esquerda);
		imprime(no->direita);
		printf(")");
	}
	else printf("()");
}

/*int maiorChaveDaArvore(Tno *raiz){
    if(raiz == NULL) {
        return -1;
    }
    else {
        if(raiz->direita == NULL)
            return raiz->info;
        else
            return maiorChaveDaArvore(raiz->direita);
    }
}

Tno *noDeMenorValor(Tno *raiz){
    Tno *atual = raiz;
    while (atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

Tno *Remove(Tno *raiz, int info){

    if (raiz == NULL)
        return raiz;
    if (info > raiz->info)
        raiz->direita = Remove (raiz->direita, info);
    else if (info < raiz->info)
        raiz->esquerda = Remove (raiz->esquerda, info);
    else{
        if (raiz->esquerda == NULL || raiz->direita == NULL){
            Tno *aux = raiz->esquerda ? raiz->esquerda : raiz->direita;
            if (aux == NULL){
                aux = raiz;
                raiz = NULL;
            }
            else
                *raiz = *aux;
            free (aux);
        }
        else{
            Tno *aux = noDeMenorValor(raiz->direita);
            raiz->info = aux->info;
            raiz->direita = Remove(raiz->direita, aux->info);
        }
    }

    if (raiz == NULL)
        return raiz;

    raiz->altura = Maior(altura(raiz->esquerda), altura (raiz->direita))+1;
    int fb = obterFatorBalanceamentoInteiro (raiz);

    // LL
    if (fb > 1 && obterFatorBalanceamentoInteiro(raiz->esquerda) >= 0)
        raiz = RotacaoDireita(raiz);

    // RR
    if (fb < -1 && obterFatorBalanceamentoInteiro(raiz->direita) <= 0)
        raiz = RotacaoEsquerda (raiz);

    // LR
    if (fb > 1 && obterFatorBalanceamentoInteiro(raiz->esquerda) < 0){
        raiz->esquerda = RotacaoEsquerda(raiz->esquerda);
        raiz = RotacaoDireita(raiz);
    }

    // RL
    if (fb < -1 && obterFatorBalanceamentoInteiro(raiz->direita) > 0){
        raiz->direita = RotacaoDireita (raiz->direita);
        raiz = RotacaoEsquerda(raiz);
    }
    return raiz;
}*/

/*void Inicializa (int c, Tno *noAux) {
    noAux->info = c;
    noAux->esquerda = NULL;
    noAux->direita=NULL;
    noAux->altura = 1;
}

Tno *Carrega(Tno *raiz) {
    int i, N;
    int chave;
    scanf("%d", &N);

    for(i=0; i<N; i++){
        scanf("%d", &chave);
        Insere(raiz, chave);
    }



    /*if(chave >= 0){
      //Inicializa(chave, raiz);
      scanf("%d", &chave);
      while(chave >= 0){
        raiz = Insere(raiz, chave);
        scanf("%d", &chave);
      }
    }
    return raiz;
}*/

/*Tno *RemoveNos(Tno *raiz) {
    int i, chave;
      scanf("%d", &chave);
      while (chave >= 0) {
          raiz = Remove(raiz, chave);
          scanf("%d", &chave);
      }
    return raiz;
}*/

int main(){

    Tno *raiz = NULL;
    //raiz = Carrega(raiz);
    int i, N;
    int chave;
    scanf("%d", &N);

    for(i=0; i<N; i++){
        scanf("%d", &chave);
        raiz = Insere(raiz, chave);
        printf("RAIZ %d\n", raiz->info);
    }

    //raiz = RemoveNos(raiz);
    ImprimeEmOrdem(raiz);
    printf("\n");
    imprime(raiz);
    printf("\n");
    ImprimePosOrdem(raiz);
    return 0;
}
