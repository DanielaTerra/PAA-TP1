//
// Created by daniela on 09/09/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utilities.h"
#include "trie.h"


//Retorna a lista de ocorrências da chave (palavra)  na árvore.
//ou NULL se palavra não encontrada
struct linkedlist * getTrie(char * chave, struct trie* arvore){
    struct noTrie *no = getRec(arvore->root, chave, 0);
    if (no == NULL)
        return NULL;
    return no->value;
}

//Função recursiva de apoio à getTrie()
struct noTrie* getRec(struct noTrie* x, char* key, int d){
     if(x == NULL)
         return NULL;  //key não encontrada na árvore trie;
     if(d == strlen(key))
         return x;
     char c = key[d]; //obtem o d-ésimo caractere da chave
     return getRec(x->next[c], key, (d + 1));
}


//Função para inserção de uma chave (palavra) na trie
void putTrie(char *key, struct trie* arvore){
    arvore->root = putRec(arvore->root, key, 0);
}

//Função recursiva de apoio à putTrie()
struct noTrie* putRec(struct noTrie* x, char* key, int d){
   if (x == NULL){
       //cria novo noTrie com uma lista de ocorrẽncias vazia
       x = (struct noTrie*) malloc(sizeof(struct noTrie));
       x->isReg = 0;   //a principio um novo nó não contem registro
       x->value = (struct linkedlist*) malloc(sizeof(struct linkedlist)); //cria lista vazia (0 nós)
       // x->next terá 256 ponteiros iguais a (nil)
   }
   if (d == strlen(key)){
       x->isReg = 1;
       insere(x->value, key, 1);
       return x;
   }
   char c = key[d];
   x->next[c] = putRec(x->next[c], key, d + 1);
   return x;
}

//Preenche todas as ocorrencias de palabras com o prefixo 'pre' informado
//no vetor ocorrencias e retorna o tamanho do vetor, ou -1 se 'pre' não encontrado
int keysWithPrefix(char *pre, struct trie* arvore, char*** ocorrencias){
    //criando uma linkedlist para lista geral vazia para armazenar todas as listas do nós trie que são registros (noTrie->isReg = 1)
    struct linkedlist* q = (struct linkedlist*) malloc(sizeof(struct linkedlist));
    q->numPalavras = 0;
    q->inicio = NULL;

    struct noTrie* noPre = getRec(arvore->root, pre,0);

    //Teste para prefixo encontrado!
    if (noPre == NULL)
        return -1;
    // Teste
    printf("\nTeste getRec -------------");
    printf("\n noPre (getRec) possui value com %d ocorrencias", noPre->value->numPalavras);
    imprime (noPre->value);
    printf("\n -------------");

    collect(noPre, pre, q);

    struct noList** v;
    v = (struct noList**) malloc(q->numPalavras * sizeof(struct noList*));
    int tam = ordenaOcorrencias(q, v);

    *ocorrencias = (char**) malloc(tam * sizeof(char*));
    geraVetorOcorrencias(v, *ocorrencias, tam);

    free(q);
    return tam;
}

//Funcao de apoio ao keysWithPrefix()
//Coleta as listas de ocorrẽncias não nulas de todos os nós,
// a partir de x, que são registros válidos, na lista q
void collect(struct noTrie* x, char* pre, struct linkedlist* q){
     if(x == NULL) return;
     if(x->isReg) {   //é nó de registro de ocorrências
         concatena(q, x->value);
     }
     int c;
     for(c= 0; c < R; c++){
         char caractere[] = {c, '\0'};
         char* preAux = (char *) malloc((strlen(pre)+2) *sizeof(char));
         strcpy(preAux, pre);
         strcat(preAux, caractere);
         collect(x->next[c], preAux, q);
     }
 }