//Tamires Lucena, 111866

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tpecuaria{
    char nome[25];
    char local[3];

    int quant13;
    int quant14;
    int quant15;

    int valor13;
    int valor14;
    int valor15;
}Tpecuaria;

typedef struct Tlocal{
    char local[3];
    int quantidadetotal;
    int valortotal;
}Tlocal;

typedef struct Tano{
    int ano;
    int valortotal;
    int quantidadetotal;
}Tano;

typedef struct Tpeixe{
    char nome[50];
    int valortotal;
    int quantidadetotal;
}Tpeixe;

Tpecuaria *LeituraDados(FILE *arquivo, int *nlinhas){

    char carac; // leitura caracter por caracter


    char nometemp[25];
    char localtemp[3];

    char quant13temp[25];
    char quant14temp[25];
    char quant15temp[25];

    char valor13temp[25];
    char valor14temp[25];
    char valor15temp[25];

    Tpecuaria *pecuaria = malloc(sizeof(Tpecuaria));
    *nlinhas = 0; // conteudo nlinhas inicializado com 0
    carac = 0; // inicializando com qualquer coisa


    do{
        fscanf(arquivo, "%c", &carac);
    }while (carac != '\n'); // leitura da primeira linha de titulos



    while(fscanf(arquivo, "%c", &carac) != EOF){

        int i = 0;
        while(carac != ';'){ // nome
            nometemp[i] = carac;
            i++;
            fscanf(arquivo, "%c", &carac);
        }
        nometemp[i] = '\0';
        strcpy(pecuaria[*nlinhas].nome, nometemp);
        //printf("%s",pecuaria[*nlinhas].nome);


        fscanf(arquivo, "%c", &carac);
        i = 0;
        while(carac != ';'){ // local
            localtemp[i] = carac;
            i++;
            fscanf(arquivo, "%c", &carac);
        }
        localtemp[i] = '\0';
        strcpy(pecuaria[*nlinhas].local, localtemp);
        //printf("%s",pecuaria[*nlinhas].local);



        fscanf(arquivo, "%c", &carac);
        i = 0;
        while(carac != ';'){ // quantidade 2013
            quant13temp[i] = carac;
            i++;
            fscanf(arquivo, "%c", &carac);
        }
        quant13temp[i] = '\0';
        sscanf(quant13temp, "%d", &pecuaria[*nlinhas].quant13);
        //printf("%d",pecuaria[*nlinhas].quant13);

        fscanf(arquivo, "%c", &carac);
        i = 0;
        while(carac != ';'){ // quantidade 2014
            quant14temp[i] = carac;
            i++;
            fscanf(arquivo, "%c", &carac);
        }
        quant14temp[i] = '\0';
        sscanf(quant14temp, "%d", &pecuaria[*nlinhas].quant14);
        //printf("%d",pecuaria[*nlinhas].quant14);


        fscanf(arquivo, "%c", &carac);
        i = 0;
        while(carac != ';'){ // quantidade 2015
            quant15temp[i] = carac;
            i++;
            fscanf(arquivo, "%c", &carac);
        }
        quant15temp[i] = '\0';
        sscanf(quant15temp, "%d", &pecuaria[*nlinhas].quant15);
        //printf("%d",pecuaria[*nlinhas].quant15);


        fscanf(arquivo, "%c", &carac);
        i = 0;
        while(carac != ';'){ // valor producao 2013
            valor13temp[i] = carac;
            i++;
            fscanf(arquivo, "%c", &carac);
        }
        valor13temp[i] = '\0';
        sscanf(valor13temp, "%d", &pecuaria[*nlinhas].valor13);
        //printf("%d",pecuaria[*nlinhas].valor13);


        fscanf(arquivo, "%c", &carac);
        i = 0;
        while(carac != ';'){ // valor producao 2014
            valor14temp[i] = carac;
            i++;
            fscanf(arquivo, "%c", &carac);
        }
        valor14temp[i] = '\0';
        sscanf(valor14temp, "%d", &pecuaria[*nlinhas].valor14);
        //printf("%d",pecuaria[*nlinhas].valor14);


        fscanf(arquivo, "%c", &carac);
        i = 0;
        while(carac != '\n'){ // valor producao 2015
            valor15temp[i] = carac;
            i++;
            fscanf(arquivo, "%c", &carac);
        }
        valor15temp[i] = '\0';
        sscanf(valor15temp, "%d", &pecuaria[*nlinhas].valor15);
        //printf("%d",pecuaria[*nlinhas].valor15);


        *nlinhas = *nlinhas + 1;
        pecuaria = (Tpecuaria*) realloc(pecuaria, (*nlinhas+1)*sizeof(Tpecuaria));


    }

    return pecuaria;

}

Tpeixe *TotalPeixe(Tpecuaria *pecuaria, int nlinhas, int *npeixes){

    Tpeixe *peixes = malloc(sizeof(Tpeixe));
    *npeixes = 0;

    int i, j;

    for(i=0; i<nlinhas;i++){
        strcpy(peixes[*npeixes].nome, pecuaria[i].nome);

        j = i;
        peixes[*npeixes].quantidadetotal = 0;
        peixes[*npeixes].valortotal = 0;

        while(strcmp(peixes[*npeixes].nome, pecuaria[j].nome) == 0){
            peixes[*npeixes].quantidadetotal += pecuaria[j].quant13 + pecuaria[j].quant14 + pecuaria[j].quant15;
            peixes[*npeixes].valortotal += pecuaria[j].valor13 + pecuaria[j].valor14 + pecuaria[j].valor15;
            j++;
        }

        *npeixes = *npeixes+1;
        peixes = (Tpeixe*) realloc(peixes, (*npeixes+1)*sizeof(Tpeixe));
        i = j-1;

    }


    /*for(i=0; i<*npeixes; i++){
        printf("Tipo do Peixe: %s | Quantidade Total: %d (milheiros)| Valor Total: %d (milhares de reais)\n", peixes[i].nome, peixes[i].quantidadetotal, peixes[i].valortotal);
    }*/

    return peixes;
}

void CriaheapLocal(Tpecuaria *pecuaria, int i, int f){
    Tpecuaria aux = pecuaria[i];
    int j = i * 2 + 1;
    while(j <= f){
        if(j < f){
            if(strcmp(pecuaria[j].local, pecuaria[j+1].local) < 0){
                j = j+1;
            }
        }

        if(strcmp(aux.local, pecuaria[j].local) < 0){
            pecuaria[i] = pecuaria[j];
            i=j;
            j = 2* i + 1;
        }
        else{
            j = f + 1;
        }
    }
    pecuaria[i] = aux;
}

void HeapsortLocal(Tpecuaria *pecuaria, int nlinhas){
    clock_t inicio = clock();

    int i;
    Tpecuaria aux;

    for(i=(nlinhas-1)/2; i>=0; i--){ // do meio para a esquerda
        CriaheapLocal(pecuaria, i, nlinhas-1);
    } // cria o heap

    for(i=nlinhas-1; i>= 1; i--){
        aux = pecuaria[0];
        pecuaria[0] = pecuaria[i];
        pecuaria[i] = aux;
        CriaheapLocal(pecuaria, 0, i-1); // reconstroi heap
    }// pega maior elemento e coloca na posição certa do pecuaria

    clock_t fim = clock();
    double tempo = (double) (fim-inicio)/CLOCKS_PER_SEC;
    printf("Tempo Heap: %f segundos\n", tempo);

    /*printf("HeapSort: \n");
    for(i=0; i<nlinhas; i++){
        printf("%s %d %d %d %d %d %d\n", pecuaria[i].local, pecuaria[i].quant13, pecuaria[i].quant14, pecuaria[i].quant15, pecuaria[i].valor13, pecuaria[i].valor14, pecuaria[i].valor15);
    }*/
}

void InsercaoLocal(Tpecuaria *pecuaria, int nlinhas){
    clock_t inicio = clock();

    int i, j;
    Tpecuaria aux;

    for(i=1; i<nlinhas; i++){
        j=i-1;
        while(j>=0 && strcmp(pecuaria[j+1].local, pecuaria[j].local) < 0){
            aux = pecuaria[j+1];
            pecuaria[j+1] = pecuaria[j];
            pecuaria[j] = aux;
            j--;
        }
    }

    clock_t fim = clock();
    long double tempo = (long double) ((fim-inicio)/CLOCKS_PER_SEC);
    printf("Tempo Insertion: %f segundos\n", tempo);

   /* printf("Insertion Sort:\n");
    for(i=0; i<nlinhas; i++){
        printf("%s %d %d %d %d %d %d\n", pecuaria[i].local, pecuaria[i].quant13, pecuaria[i].quant14, pecuaria[i].quant15, pecuaria[i].valor13, pecuaria[i].valor14, pecuaria[i].valor15);
    }*/

}

void CriaheapQuantidade(Tlocal *locais, int i, int f){
    Tlocal aux = locais[i];
    int j = i * 2 + 1;
    while(j <= f){
        if(j < f){
            if(locais[j].quantidadetotal < locais[j+1].quantidadetotal){
                j = j+1;
            }
        }

        if(aux.quantidadetotal < locais[j].quantidadetotal){
            locais[i] = locais[j];
            i=j;
            j = 2* i + 1;
        }
        else{
            j = f + 1;
        }
    }
    locais[i] = aux;
}

void HeapsortQuantidade(Tlocal *locais, int nlocais){
    clock_t inicio = clock();

    int i;
    Tlocal aux;

    for(i=(nlocais-1)/2; i>=0; i--){ // do meio para a esquerda
        CriaheapQuantidade(locais, i, nlocais-1);
    } // cria o heap

    for(i=nlocais-1; i>= 1; i--){
        aux = locais[0];
        locais[0] = locais[i];
        locais[i] = aux;
        CriaheapQuantidade(locais, 0, i-1); // reconstroi heap
    }// pega maior elemento e coloca na posição certa do locais

    clock_t fim = clock();
    double tempo = (double) (fim-inicio)/CLOCKS_PER_SEC;
    printf("Tempo Heap: %f segundos\n", tempo);

    /*printf("HeapSort: \n");
    for(i=0; i<nlinhas; i++){
        printf("%s %d %d %d %d %d %d\n", pecuaria[i].local, pecuaria[i].quant13, pecuaria[i].quant14, pecuaria[i].quant15, pecuaria[i].valor13, pecuaria[i].valor14, pecuaria[i].valor15);
    }*/
}

void InsercaoQuantidade(Tlocal *locais, int nlocais){
    clock_t inicio = clock();

    int i, j;
    Tlocal aux;

    for(i=1; i<nlocais; i++){
        j=i-1;
        while(j>=0 && locais[j+1].quantidadetotal < locais[j].quantidadetotal){
            aux = locais[j+1];
            locais[j+1] = locais[j];
            locais[j] = aux;
            j--;
        }
    }

    clock_t fim = clock();
    long double tempo = (long double) ((fim-inicio)/CLOCKS_PER_SEC);
    printf("Tempo Insertion: %f segundos\n", tempo);

    /*printf("Insertion Sort:\n");
    for(i=0; i<nlocais; i++){
        printf("%s %d\n", locais[i].local, locais[i].quantidadetotal);
    }*/

}

void CriaheapValor(Tlocal *locais, int i, int f){
    Tlocal aux = locais[i];
    int j = i * 2 + 1;
    while(j <= f){
        if(j < f){
            if(locais[j].valortotal < locais[j+1].valortotal){
                j = j+1;
            }
        }

        if(aux.valortotal < locais[j].valortotal){
            locais[i] = locais[j];
            i=j;
            j = 2* i + 1;
        }
        else{
            j = f + 1;
        }
    }
    locais[i] = aux;
}

void HeapsortValor(Tlocal *locais, int nlocais){
    clock_t inicio = clock();

    int i;
    Tlocal aux;

    for(i=(nlocais-1)/2; i>=0; i--){ // do meio para a esquerda
        CriaheapValor(locais, i, nlocais-1);
    } // cria o heap

    for(i=nlocais-1; i>= 1; i--){
        aux = locais[0];
        locais[0] = locais[i];
        locais[i] = aux;
        CriaheapValor(locais, 0, i-1); // reconstroi heap
    }// pega maior elemento e coloca na posição certa do locais

    clock_t fim = clock();
    double tempo = (double) (fim-inicio)/CLOCKS_PER_SEC;
    printf("Tempo Heap: %f segundos\n", tempo);

    /*printf("HeapSort: \n");
    for(i=0; i<nlinhas; i++){
        printf("%s %d %d %d %d %d %d\n", pecuaria[i].local, pecuaria[i].quant13, pecuaria[i].quant14, pecuaria[i].quant15, pecuaria[i].valor13, pecuaria[i].valor14, pecuaria[i].valor15);
    }*/
}

void InsercaoValor(Tlocal *locais, int nlocais){
    clock_t inicio = clock();

    int i, j;
    Tlocal aux;

    for(i=1; i<nlocais; i++){
        j=i-1;
        while(j>=0 && locais[j+1].valortotal < locais[j].valortotal){
            aux = locais[j+1];
            locais[j+1] = locais[j];
            locais[j] = aux;
            j--;
        }
    }

    clock_t fim = clock();
    long double tempo = (long double) ((fim-inicio)/CLOCKS_PER_SEC);
    printf("Tempo Insertion: %f segundos\n", tempo);

   /* printf("Insertion Sort:\n");
    for(i=0; i<nlocais; i++){
        printf("%s %d\n", locais[i].local, locais[i].valortotal);
    }*/

}

Tlocal *TotalLocal(Tpecuaria *pecuaria, int nlinhas, int *nlocais){

    Tlocal *locais = malloc(3*sizeof(Tlocal));
    *nlocais = 0;

    int i, j;

    for(i=0; i<nlinhas;i++){
        strcpy(locais[*nlocais].local, pecuaria[i].local);

        j = i;
        locais[*nlocais].quantidadetotal = 0;
        locais[*nlocais].valortotal = 0;

        while(strcmp(locais[*nlocais].local, pecuaria[j].local) == 0){
            locais[*nlocais].quantidadetotal += pecuaria[j].quant13 + pecuaria[j].quant14 + pecuaria[j].quant15;
            locais[*nlocais].valortotal += pecuaria[j].valor13 + pecuaria[j].valor14 + pecuaria[j].valor15;
            j++;
        }

        *nlocais = *nlocais+1;
        locais = (Tlocal*) realloc(locais, (*nlocais+1)*sizeof(Tlocal));
        i = j-1;

    }


   /* for(i=0; i<*nlocais; i++){
        printf("UF: %s | Quantidade Total: %d (milheiros)| Valor Total: %d (milhares de reais)\n", locais[i].local, locais[i].quantidadetotal, locais[i].valortotal);
    }*/

    return locais;
}

Tano *TotalAno(Tpecuaria *pecuaria, int nlinhas, int *nanos){
    Tano *anos = malloc(3*sizeof(Tano));
    *nanos = 0;

    anos[*nanos].ano = 2013;
    anos[*nanos].quantidadetotal = 0;
    anos[*nanos].valortotal = 0;
    int i;
    for(i=0; i<nlinhas; i++){
        anos[*nanos].quantidadetotal += pecuaria[i].quant13;
        anos[*nanos].valortotal += pecuaria[i].valor13;
    }
    //printf("Quantidade 2013: %d (milheiros)| ", anos[*nanos].quantidadetotal);
    //printf("Valor 2013: %d (milhares de reais) \n", anos[*nanos].valortotal);
    *nanos = *nanos +1;



    anos[*nanos].ano = 2014;
    anos[*nanos].quantidadetotal = 0;
    anos[*nanos].valortotal = 0;
    for(i=0; i<nlinhas; i++){
        anos[*nanos].quantidadetotal += pecuaria[i].quant14;
        anos[*nanos].valortotal += pecuaria[i].valor14;
    }
    //printf("Quantidade 2014: %d (milheiros)| ", anos[*nanos].quantidadetotal);
    //printf("Valor 2014: %d (milhares de reais) \n", anos[*nanos].valortotal);
    *nanos = *nanos +1;



    anos[*nanos].ano = 2015;
    anos[*nanos].quantidadetotal = 0;
    anos[*nanos].valortotal;
    for(i=0; i<nlinhas; i++){
        anos[*nanos].quantidadetotal += pecuaria[i].quant15;
        anos[*nanos].valortotal += pecuaria[i].valor15;
    }
    //printf("Quantidade 2015: %d (milheiros)| ", anos[*nanos].quantidadetotal);
    //printf("Valor 2015: %d (milhares de reais) \n", anos[*nanos].valortotal);
    *nanos = *nanos +1;

    return anos;

}

int main(int argc, char* argv[]){

    FILE *arquivo = fopen(argv[1], "r"); // read ler
    int nlinhas;
    printf("Lendo Dados...\n");
    Tpecuaria *pecuaria = LeituraDados(arquivo, &nlinhas); // le e armazena na struct
    fclose(arquivo);


    //printf("Agrupando por tipos de peixes...\n");
    int npeixes;
    Tpeixe *peixes = TotalPeixe(pecuaria, nlinhas, &npeixes);


    int o;
    printf("Escolha o modo de ordenacao: 1-HeapSort ou 2-InsertionSort para organizar os dados por localidade\n");
    scanf("%d", &o);
    if(o == 2) InsercaoLocal(pecuaria, nlinhas);
    else if(o == 1) HeapsortLocal(pecuaria, nlinhas);
    //printf("Ordenando por localidade...\n");



    //printf("Agrupando dados por localidade...\n");
    int nlocais;
    Tlocal *locais = TotalLocal(pecuaria, nlinhas, &nlocais);


    int i;
    FILE *novoarquivo = fopen("Local e Quantidade Total.txt", "w");
    for (i=0; i<nlocais; i++){
        fprintf(novoarquivo, "%s %d\n", locais[i].local, locais[i].quantidadetotal);
    }
    fclose(novoarquivo);

    FILE *novoarquivo1 = fopen("Local e Valor Total.txt", "w");
    for (i=0; i<nlocais; i++){
        fprintf(novoarquivo1, "%s %d\n", locais[i].local, locais[i].valortotal);
    }
    fclose(novoarquivo1);


    int oq;
    printf("Deseja ordenar por quantidade? 0-Nao desejo ordenar, 1-HeapSort, 2-InsertionSort\n");
    scanf("%d", &oq);
    if(oq == 2) InsercaoQuantidade(locais, nlocais);
    else if(oq == 1) HeapsortQuantidade(locais, nlocais);

    if(oq == 1 || oq == 2){
        novoarquivo = fopen("Local e Quantidade Total.txt", "w");
        for (i=0; i<nlocais; i++){
            fprintf(novoarquivo, "%s %d\n", locais[i].local, locais[i].quantidadetotal);
        }
        fclose(novoarquivo);
    }


    int ov;
    printf("Deseja ordenar por valor? 0-Nao desejo ordenar, 1-HeapSort, 2-InsertionSort\n");
    scanf("%d", &ov);

    if(ov == 2) InsercaoValor(locais, nlocais);
    else if(ov == 1) HeapsortValor(locais, nlocais);
    if(ov == 1 || ov ==2){
        novoarquivo1 = fopen("Local e Valor Total.txt", "w");
        for (i=0; i<nlocais; i++){
            fprintf(novoarquivo1, "%s %d\n", locais[i].local, locais[i].valortotal);
        }
        fclose(novoarquivo1);
    }

    //printf("Agrupando dados por ano...\n");
    int nanos;
    Tano *anos = TotalAno(pecuaria, nlinhas, &nanos);



    FILE *novoarquivo2 = fopen("Ano e Quantidade Total.txt", "w");
    for (i=0; i<nanos; i++){
        fprintf(novoarquivo2, "%d %d\n", anos[i].ano, anos[i].quantidadetotal);
    }
    fclose(novoarquivo2);

    FILE *novoarquivo3 = fopen("Ano e Valor Total.txt", "w");
    for (i=0; i<nanos; i++){
        fprintf(novoarquivo3, "%d %d\n", anos[i].ano, anos[i].valortotal);
    }
    fclose(novoarquivo3);


    FILE *novoarquivo4 = fopen("Tipo do Peixe e Valor Total.txt", "w");
    for (i=0; i<npeixes; i++){
        fprintf(novoarquivo4, "%s %d\n", peixes[i].nome, peixes[i].valortotal);
    }
    fclose(novoarquivo4);

    FILE *novoarquivo5 = fopen("Tipo do Peixe e Quantidade Total.txt", "w");
    for (i=0; i<npeixes; i++){
        fprintf(novoarquivo5, "%s %d\n", peixes[i].nome, peixes[i].quantidadetotal);
    }
    fclose(novoarquivo5);


    return 0;
}
