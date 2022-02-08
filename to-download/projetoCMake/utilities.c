//
// Created by daniela on 04/09/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utilities.h"

// Lista ligada, sem célula cabeçalho, para ocorrencias de palavras. Cada noList contém: (palavra, nº ocorrencias)
// Insere um nó na lista de ocorrencias se a palavra ainda não existe na lista.
// Retorna 0 se nova palavra for inserida,  1 se a palavra já existir somando 1 no nº de ocorrências,
// -1 se palavra nula
int insere(struct linkedlist *l, char cadeia[], int numOcor) {
    struct noList *aux = l->inicio, *auxAnt;
    char* palavra = (char *) malloc(sizeof(strlen(cadeia)));
    strcpy(palavra, cadeia);
    int tam = toMinusculas(palavra);
    if (tam == 0) return -1;  //cadeia vazia
    while (aux != NULL){
        if(strcmp (palavra, aux->palavra) == 0){
            aux->ocorrencias+=numOcor;
            return 1;
        }
        auxAnt = aux;
        aux = aux->prox;
    }
    struct noList *novo = (struct noList*) malloc(sizeof(struct noList));
    if (l->inicio == NULL){
        l->inicio = novo;  //primeiro da lista
    }else{
        auxAnt->prox = novo;  //liga novo nó à lista existente
    }
    novo->ocorrencias = numOcor;
    novo->palavra = (char*) malloc((strlen(palavra)+1) *sizeof(char));
    strcpy(novo->palavra, palavra);
    novo->prox = NULL;
    l->numPalavras++;  //uma palavra a mais na lista
    return 0;
}

//--------
// Ordena palavras por número de ocorrências na linkedlist.
// Preenche o vetor palavras (por referência) e
// Retorna 0 se a lista não tiver palavras ou o número de palavras, caso conctrário
int ordenaOcorrencias(struct linkedlist *l, struct noList **v) {
    if (l->numPalavras == 0) {
        return 0;
    }
    //v = (struct noList**) malloc(l->numPalavras * sizeof(struct noList*));
    struct noList *aux = l->inicio;
    int i;
    for (i = 0; (aux != NULL); i++) {
        v[i] = aux;
        aux = aux->prox;
    }
    //ordena palavras pelo número de ocorrências (ordem decrescente)
    ordenaDecrescente(v, l->numPalavras);

    return l->numPalavras;
}

//Preenche o vetor palavras[] para retorno
//palavras = (char**) malloc(l->numPalavras * sizeof(char*));
void geraVetorOcorrencias(struct noList* v[], char* ocorrencias[], int tam){
    int i = 0;
    for(i = 0; i <tam; i++){
        char ocorre[20];
        sprintf(ocorre, "(%04d)",v[i]->ocorrencias);

        ocorrencias[i] = (char*) calloc((strlen(v[i]->palavra) + (strlen(ocorre)+1)), sizeof(char));

        strcpy(ocorrencias[i], v[i]->palavra);
        strcat(ocorrencias[i], ocorre);
    }

}



//----------
// Ordena palavras por número de ocorrências na linkedlist.
// Preenche o vetor palavras (por referência) e
// Retorna 0 se a lista não tiver palavras ou o número de palavras, caso conctrário
int ordenaListaOcor(struct linkedlist *l, char** palavras){
    if (l->numPalavras == 0){
        return 0;
    }
    struct noList*  v[l->numPalavras];
    struct noList *aux = l->inicio;
    int i;
    for(i = 0; (aux != NULL); i++){
        v[i] = aux;
        aux = aux->prox;
    }
    //ordena palavras pelo número de ocorrências (ordem decrescente)
    ordenaDecrescente(v, l->numPalavras);

    //Preenche o vetor palavras[] para retorno
    //palavras = (char**) malloc(l->numPalavras * sizeof(char*));

    for(i = 0; i <l->numPalavras; i++){
        char ocorrencias[20];
        sprintf(ocorrencias, "(%02d)",v[i]->ocorrencias);

        palavras[i] = (char*) calloc((strlen(v[i]->palavra) + (strlen(ocorrencias)+1)), sizeof(char));

        strcpy(palavras[i], v[i]->palavra);
        strcat(palavras[i], ocorrencias);
    }
    return l->numPalavras;
}

// Excecuta ordenação das palavras por número de ocorrencias
// em ordem descendente, usando método simples
void ordenaDecrescente(struct noList **v, int tam){
    struct noList* temp;
    int i, j, troca = 1;
    for(i= tam-2; (i >= 0) && (troca); i--){
        troca = 0;
        for(j= 0; j < i; j++){
            if (v[j]->ocorrencias < v[j+1]->ocorrencias){
                temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
                troca = 1;
            }
        }
    }
}

//Impressao da lista de ocorrências
void imprime(struct linkedlist *l){
    printf("\nPalavras na lista: %d",l->numPalavras);
    struct noList *aux = l->inicio;
    while (aux != NULL){
        printf("\n%s(%d)", aux->palavra, aux->ocorrencias);
        aux = aux->prox;
    }
}

// Converte cadeia para caracteres para minúsculos
// sem símbolos especiais
int toMinusculas(char *cadeia){
    int i;
    for(i=0; (i < (int) strlen(cadeia)); i++){
        cadeia[i] = (char) tolower((int)cadeia[i]);
    }
    return ((int) strlen(cadeia));
}

//Une a lista orig ao final de dest, sem destruir orig.
// O retorno é o número de itens após cópia na lista dest.
int concatena(struct linkedlist *dest, struct linkedlist *orig){
    if(orig->numPalavras ==0)
        return dest->numPalavras;
    struct noList *aux = orig->inicio;
    while (aux!= NULL){
        insere(dest, aux->palavra, aux->ocorrencias);
        aux = aux->prox;
    }
    return orig->numPalavras;
}


/*
//Une a lista orig ao final de dest. O retorno é o número de itens após cópia na lista dest.
int concatena(struct linkedlist *dest, struct linkedlist *orig){
    if(orig->numPalavras ==0)
        return dest->numPalavras;
    struct noList *aux = orig->inicio, auxAnt;
    while (orig->numPalavras > 0){
        aux = retiraPrimeiro(orig);
        insere(dest, aux->palavra);
    }
    return orig->numPalavras;
} */

//Retira o nó inicial e retorna. Se a lista é vazia retorna NULL
struct noList* retiraPrimeiro(struct linkedlist *l){
    if(l->numPalavras == 0)
        return NULL;
    struct noList* primeiro = l->inicio;
    l->inicio = l->inicio->prox;
    l->numPalavras--;
    return primeiro;
}

