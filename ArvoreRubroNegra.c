#include <stdio.h>
#include <stdlib.h>

typedef struct Tno{
    int info;
    struct Tno *esquerda;
    struct Tno *direita;
    int cor;
}Tno;

typedef struct Tarvore{
    Tno *raiz;
}Tarvore;

void Inicializa(Tarvore *arvore){
    arvore->raiz = NULL;
}

void TrocaCor(Tno *no){
    if(no->cor == 0) no->cor = 1;
    else no->cor = 0;
}

Tno* RotacaoDireita(Tno *no){
    Tno *aux = no->esquerda;
    no->esquerda = aux->direita;
    aux->direita = no;
    return aux;
}

Tno* RotacaoEsquerda(Tno *no){
    Tno *aux = no->direita;
    no->direita = aux->esquerda;
    aux->esquerda = no;
    return aux;
}

int ePreto(Tno *no){
    if(no == NULL || no->cor == 1) return 1;
    return 0;
}

Tno* Balancear(Tno *avo, Tno *pai, Tno *filho){
    Tno *tio;

    if(!ePreto(pai) && !ePreto(filho) && avo!= NULL){ //se pai e filho sao vermelhos
        if(avo->direita == pai) tio = avo->esquerda;
        else if(avo->esquerda == pai) tio = avo->direita;

        printf("pai e filho sao verm\n");
        if(!ePreto(tio)){ //se o tio é vermelho
            printf("tio eh verm\n");
            TrocaCor(avo);
            TrocaCor(pai);
            TrocaCor(tio);
        }
        else{ //se o tio é preto

            printf("tio eh preto\n");
            if(avo->esquerda == pai){
                if(pai->direita == filho) pai = RotacaoEsquerda(pai); //se tem cotovelo
                TrocaCor(avo);
                TrocaCor(pai);
                avo = RotacaoDireita(avo);
            }
            else if(avo->direita == pai){
                if(pai->esquerda == filho) pai = RotacaoDireita(pai); //se tem cotovelo
                TrocaCor(avo);
                TrocaCor(pai);
                avo = RotacaoEsquerda(avo);
            }
        }
    }
    return pai;
}

Tno* Insere(Tno *avo, Tno *pai, int info){
    if(pai == NULL){
        Tno *aux = malloc(sizeof(Tno));
        aux->info = info;
        aux->cor = 0;
        aux->esquerda = NULL;
        aux->direita = NULL;
        return aux;
    }

    else {
        if(info < pai->info){
            pai->esquerda = Insere(pai, pai->esquerda, info);
            pai = Balancear(avo, pai, pai->esquerda);
        }
        else{
            pai->direita = Insere(pai, pai->direita, info);
            pai = Balancear(avo, pai, pai->direita);
        }
    }
    return pai;
}


int AlturaPreta(Tno *no){
    int esquerda, direita;
    if(no == NULL) return 0;
    esquerda = AlturaPreta(no->esquerda);
    direita = AlturaPreta(no->direita);
    if(esquerda > direita) return(ePreto(no)+esquerda); //retorna somente o número de nos pretos
    else return(ePreto(no)+direita);
}

int ArvoreRN(Tno *no){
    if(no == NULL || (ArvoreRN(no->esquerda) && ArvoreRN(no->direita))) return 1; //se o no e NULL e se direita e esquerda sao ARN, a arvore eh AVP
    else if(AlturaPreta(no->direita) != AlturaPreta(no->esquerda) || (!ePreto(no) && (!ePreto(no->direita) || !ePreto(no->esquerda)))) return 0; //se a AlturaPreta pra esquerda e pra direita for diferente ou se ha dois nos consecutivos vermelhos, nao eh AVP
}

void Imprime(Tno *no){
	if (no != NULL) {
		if (ePreto(no)) printf("(P%d", no->info);
		else printf("(V%d", no->info);
		Imprime(no->esquerda);
		Imprime(no->direita);
		printf(")");
	}
	else printf("()");
}


int main(){
    int N, i;
    //Tarvore arvore;
    //Inicializa(&arvore);

    scanf("%d", &N);
    int info;

    Tno *raiz = NULL;

    for(i=0; i<N; i++){
        scanf("%d", &info);
        Insere(NULL, raiz, info);
    }

    if(ArvoreRN(raiz)) Imprime((raiz));

    return 0;
}
