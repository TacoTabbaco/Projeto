#include "ortografia.h"

void funcaomodo3(char frase[], char **words, int tamanhoDicionario, int numeroLinhas, char fraseCopia[], char ***palavrasErrada, int *nPalavrasErradas, FILE *ficheiroSaida){
    char sinalSeparação[] = " -\t\r\n/";
    char *palavras = strtok(frase, sinalSeparação);
    int erro = FALSE;

    while (palavras != NULL) {
        formalizarPalavras(palavras); // chama a função para limpar as palavras
        if (compararPalavras(palavras, words, tamanhoDicionario, palavrasErrada, nPalavrasErradas) == TRUE) {
            fprintf(ficheiroSaida, "%s", palavras);
        }
        //Se as palavras forem iguais, da print e continua
        else{
            /*palavrasAlternativas(char **palavrasErradas, char **words, int nPalavrasErradas, offsetPalavrasDicio *dicio, int TamanhoDicionario, 1, int valorN);
            fprintf(ficheiroSaida, "%s", ????)*/; //N sei o que colocar aqui
        }
        palavras = strtok(NULL, sinalSeparação);
    }
}