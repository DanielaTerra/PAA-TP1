//
// Created by daniela on 04/09/2020.   https://medium.com/aprendacpp/usando-cmake-para-compilar-c-c-abf52c7dcbc8
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "utilities.h"
#include "trie.h"

int main(int argc, char** argv) {
    //Leitura dos argumentos de linha de comando   ../baskervilles.txt -interactive
    if (argc != 3) {
        printf("\nNúmero de argumentos inválido. Programa encerrado");
        exit (EXIT_FAILURE);
    }
    char* arquivo = argv[1];
    char* modo = argv[2];
    //--------------------------------------------

    //Execução no modo de operação indicado
    if(strcmp(modo, "-interactive")==0){
        printf("\n-----Modo Interativo:");
        //---- Cria trie ----//
        struct trie* arvore = (struct trie *) malloc(sizeof(struct trie));

        //Leitura de arquivo e Montagem da árvore trie
        FILE *entrada;
        entrada = fopen (arquivo, "r");
        if (entrada == NULL) {
            printf ("\nNão encontrei o arquivo!\n");
            exit (EXIT_FAILURE);
        }
        int n;
        char linha[200];
        while (1) {
            n = fscanf (entrada, "%s", linha);
            if (n != 1) break;   //verificar usar EOF para testar n
            char* palavra;
            palavra = strtok (linha," /*@()_-!?:%%[]{}<>.,;\'\"");
            while (palavra != NULL)
            {

                char* chave = (char *) malloc(sizeof(strlen(palavra)));
                strcpy(chave, palavra);
                int tam = toMinusculas(chave);

                putTrie(chave, arvore);
                palavra = strtok (NULL," /@*()_-!?:%%[]{}<>.,;\'\"");
            }

        }
        fclose (entrada);
        //Loop interativo
        int continua = 1;
        char * prefixo;
        do{
            printf("\n\nEntre com o prefixo ou digite 0 para sair: ");
            char prefixo[80];
            scanf ("%s",prefixo);
            if (strcmp(prefixo, "0") ==0){
                break;
            }
            getchar();
            //--- consulta palavras com prefixo na trie
            char** ocorrencias;
            int tam = keysWithPrefix(prefixo, arvore, &ocorrencias);
            if (tam == -1) {
                printf("\nPrefixo [%s] nao encontrado no texto.", prefixo);
                continue;
            }
            printf("\nTotal de ocorrencias com o prefixo [%s]: %d\nOcorrencias:", prefixo, tam);
            int i;
            // imprime ocorrências de palavras com o prefixo informado
            for(i=0; i < tam ;i++){
                printf("\n%s", ocorrencias[i]);
            }

        }while(continua);

      //Libera memória
      free(arvore);

       //---------------------------------

    }else if(strcmp(modo, "-exp")==0){
        printf("\n----- Modo experimento: ");
        //Cria arquivo de saída
        FILE * output;
        output = fopen ("exp.txt","w");
        fprintf (output, "\nTempo de execução dos experimentos: \n");

        //experimento 1: arquivo processado 1 vez
        clock_t t;
        int f;
        t = clock();
        //---inicio...
        //---- Cria trie ----//
        struct trie* arvore = (struct trie *) malloc(sizeof(struct trie));

        //Leitura de arquivo e Montagem da árvore trie
        FILE *entrada;
        entrada = fopen (arquivo, "r");
        if (entrada == NULL) {
            printf ("\nNão encontrei o arquivo!\n");
            exit (EXIT_FAILURE);
        }

        int n;
        char linha[200];
        while (1) {
            n = fscanf (entrada, "%s", linha);
            if (n != 1) break;   //verificar usar EOF para testar n
            char* palavra;
            palavra = strtok (linha," /*@()_-!?:%%[]{}<>.,;\'\"");
            while (palavra != NULL)
            {

                char* chave = (char *) malloc(sizeof(strlen(palavra)));
                strcpy(chave, palavra);
                int tam = toMinusculas(chave);

                putTrie(chave, arvore);
                palavra = strtok (NULL," /@*()_-!?:%%[]{}<>.,;\'\"");
            }

        }
        fclose (entrada);
        //Libera memória
        free(arvore);
        //--- Fim
        t = clock() - t;
        float seg = ((float)t) / CLOCKS_PER_SEC;
        printf ("\nTempo de execução (experimento - 1 cópia do arquivo): %.4f s.",seg);
        fprintf (output, "\nTempo de execução (experimento - 1 cópia do arquivo): %.4f s.",seg );

        //experimento 2:  arquivo processado 10 vezes
        t = clock();
        //---inicio...
        //---- Cria trie ----//
        arvore = (struct trie *) malloc(sizeof(struct trie));

        // lê 10 vezes o mesmo arquivo
        int i;
        for(i= 0; i < 10; i++) {
            //Releitura de arquivo e Montagem da árvore trie
            entrada = fopen(arquivo, "r");
            if (entrada == NULL) {
                printf("\nNão encontrei o arquivo!\n");
                exit(EXIT_FAILURE);
            }

            while (1) {
                n = fscanf(entrada, "%s", linha);
                if (n != 1) break;   //verificar usar EOF para testar n
                char *palavra;
                palavra = strtok(linha, " /*@()_-!?:%%[]{}<>.,;\'\"");
                while (palavra != NULL) {

                    char *chave = (char *) malloc(sizeof(strlen(palavra)));
                    strcpy(chave, palavra);
                    int tam = toMinusculas(chave);

                    putTrie(chave, arvore);
                    palavra = strtok(NULL, " /@*()_-!?:%%[]{}<>.,;\'\"");
                }

            }
            fclose(entrada);

        }
        //Libera memória
        free(arvore);

        //--- Fim
        t = clock() - t;
        seg = ((float) t) / CLOCKS_PER_SEC;
        printf("\nTempo de execução (experimento - 10 cópias do arquivo): %.4f s.", seg);
        fprintf (output, "\nTempo de execução  (experimento - 10 cópias do arquivo): %.4f s.",seg );

        //experimento 3:  arquivo processado 100 vezes
        t = clock();
        //---inicio...
        //---- Cria trie ----//
        arvore = (struct trie *) malloc(sizeof(struct trie));

        // lê 100 vezes o mesmo arquivo

        for(i= 0; i < 100; i++) {
            //Releitura de arquivo e Montagem da árvore trie
            entrada = fopen(arquivo, "r");
            if (entrada == NULL) {
                printf("\nNão encontrei o arquivo!\n");
                exit(EXIT_FAILURE);
            }

            while (1) {
                n = fscanf(entrada, "%s", linha);
                if (n != 1) break;   //verificar usar EOF para testar n
                char *palavra;
                palavra = strtok(linha, " /*@()_-!?:%%[]{}<>.,;\'\"");
                while (palavra != NULL) {

                    char *chave = (char *) malloc(sizeof(strlen(palavra)));
                    strcpy(chave, palavra);
                    int tam = toMinusculas(chave);

                    putTrie(chave, arvore);
                    palavra = strtok(NULL, " /@*()_-!?:%%[]{}<>.,;\'\"");
                }

            }
            fclose(entrada);

        }
        //Libera memória
        free(arvore);
        //--- Fim

        t = clock() - t;
        seg = ((float) t) / CLOCKS_PER_SEC;
        printf("\nTempo de execução (experimento - 100 cópias do arquivo): %.4f s.\n", seg);
        fprintf (output, "\nTempo de execução  (experimento - 100 cópias do arquivo): %.4f s.\n",seg );

        //-----------
        fclose (output);
    }else{
        printf("\nModo de operação inválido. Programa encerrado");
        exit (EXIT_FAILURE);
    }

 }




