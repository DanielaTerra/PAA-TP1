//
// Created by daniela on 09/09/2020.
//
#ifndef TP1_TRIE_H
#define TP1_TRIE_H
#include "utilities.h"
// Constante R - tamanho do alfabeto das chaves (palavras língua inglesa)
#define R 256  //base (tamanho do alfateto)

// Define Estrutura para árvore trie
struct trie{
    struct noTrie *root;
};

// Define um nó da arvore trie.
// Um nó possui ou não uma lista de ocorrências de palavras (vide struct linkedlist em utilities.h)
// se isReg=0, value será igual a  NULL
// se isReg=1, value é uma lista ligada de ocorrẽncias de palavras
struct noTrie {
    int isReg;   //1 se o nó tem value ou 0 caso contário
    struct linkedlist *value;  //ponteiro para lista de ocorrências de palavras
    struct noTrie* next[R];  // R apontadores um para cada caractere do alfabeto das chaves
};

//Insere uma chave (palavra) na trie
void putTrie(char *key, struct trie* arvore);

//Função recursiva de apoio à putTrie()
struct noTrie* putRec(struct noTrie* x, char* key, int d);

//Preenche todas as ocorrencias de palabras com o prefixo 'pre' informado
//no vetor ocorrencias e retorna o tamanho do vetor
int keysWithPrefix(char *pre, struct trie* arvore, char*** ocorrencias);

//Funcao de apoio ao keysWithPrefix()
//Coleta as listas de ocorrẽncias não nulas de todos os nós,
// a partir de x, que são registros válidos, na lista q
void collect(struct noTrie* x, char* pre, struct linkedlist* q);

//Retorna a lista de ocorrências da chave (palavra)  na árvore.
//ou NULL se palavra não encontrada
struct linkedlist * getTrie(char * chave, struct trie* arvore);

//Função recursiva de apoio à getTrie()
struct noTrie* getRec(struct noTrie* x, char* key, int d); //apoia execução de getTrie

#endif //TP1_TRIE_H
