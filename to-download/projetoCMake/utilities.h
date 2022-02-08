//
// Created by daniela on 04/09/2020.
//
#ifndef TP1_UTILITIES_H
#define TP1_UTILITIES_H

// Define uma linkedlista para armazenar as ocorrência de palavras em um nó
struct linkedlist{
    int numPalavras;
    struct noList *inicio;
};

// Define um nó da lista de ocorrência de palavras
struct noList {
    int ocorrencias;
    char* palavra;
    struct noList *prox;
};

//Insere um nó ListaOcorrencias se a palavra ainda não existe na lista. Retorna 0 se novo ou 1 se  já existir
int insere(struct linkedlist *l, char cadeia[], int numOcor);

// Converte cadeia para caracteres para minúsculos
// sem símbolos especiais
int toMinusculas(char *cadeia);



//Une a lista orig ao final de dest, sem destruir orig.
// O retorno é o número de itens após cópia na lista dest.
int concatena(struct linkedlist *dest, struct linkedlist *orig);

// Ordena palavras por número de ocorrências na linkedlist.
// Preenche o vetor palavras (por referência) e
// Retorna 0 se a lista não tiver palavras ou o número de palavras, caso conctrário
int ordenaOcorrencias(struct linkedlist *l, struct noList **v);

//Preenche o vetor palavras[] para retorno
//palavras = (char**) malloc(l->numPalavras * sizeof(char*));
void geraVetorOcorrencias(struct noList* v[], char* ocorrencias[], int tam);

//Retira o nó inicial e retorna. Se a lista é vazia retorna NULL
struct noList* retiraPrimeiro(struct linkedlist *l);

//Excecuta ordenação método simples em ordem descendente de ocorrencias de palavras
void ordenaDecrescente(struct noList **v, int tam);

//Impressao da lista
void imprime(struct linkedlist *l);

//---excluir funcao abaixo!
//Ordena palavras por ocorrencia na linkedlist. Preenche o vetor palavras e return 0 se lista vazia
// ou o número de elementos, caso contrario
int ordenaListaOcor(struct linkedlist *l, char* palavras[]);

#endif //TP1_UTILITIES_H
