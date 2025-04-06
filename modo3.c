#include "ortografia.h"

// Helper function to find closest dictionary word using your offset logic
char* encontrarCorrecao(const char *palavra, char **words, int tamanhoDicionario, int offsetMaximo) {
    int melhorOffset = INT_MAX;
    char *melhorPalavra = NULL;
    
    for (int i = 0; i < tamanhoDicionario; i++) {
        int offset = 0;
        for (int k = 0; palavra[k] && words[i][k]; k++) {
            if (palavra[k] != words[i][k]) offset++;
        }
        offset += abs((int)strlen(palavra) - (int)strlen(words[i]));
        
        if (offset <= offsetMaximo && offset < melhorOffset) {
            melhorOffset = offset;
            melhorPalavra = words[i];
        }
    }
    return melhorPalavra ? melhorPalavra : (char*)palavra;
}

// Modified version of separarPalavras that builds corrected sentence
char* corrigirFrase(const char *fraseOriginal, char **words, int tamanhoDicionario, int offsetMaximo) {
    char *frase = strdup(fraseOriginal);
    char *resultado = malloc(strlen(fraseOriginal) * 2);
    char *token = strtok(frase, " -\t\r\n/");
    
    while (token) {
        char palavra[256];
        strcpy(palavra, token);
        
        formalizarPalavras(token);
        
        int encontrada = 0;
        for (int i = 0; i < tamanhoDicionario; i++) {
            if (strcasecmp(token, words[i]) == 0) {
                encontrada = 1;
                break;
            }
        }
        
        if (encontrada) {
            strcat(resultado, palavra);
        } else {
            char *correcao = encontrarCorrecao(token, words, tamanhoDicionario, offsetMaximo);
            strcat(resultado, correcao);
        }
        
        token = strtok(NULL, " -\t\r\n/");
        if (token) strcat(resultado, " ");
    }
    
    free(frase);
    return resultado;
}

// Modified compararPalavras to work with correction
int compararPalavrasModo3(char palavras[], char **words, int tamanhoDicionario, char ***palavrasErradas, int *nPalavrasErradas, int offsetMaximo) {
    int resultado = FALSE;
    char *correcao = NULL;
    
    for (int i = 0; i < tamanhoDicionario; i++) {
        if (strcasecmp(palavras, words[i]) == 0) {
            resultado = TRUE;
            break;
        }
    }
    
    if (!resultado) {
        correcao = encontrarCorrecao(palavras, words, tamanhoDicionario, offsetMaximo);
        if (strcasecmp(palavras, correcao) != 0) {
            *palavrasErradas = realloc(*palavrasErradas, (*nPalavrasErradas + 1) * sizeof(char *));
            (*palavrasErradas)[*nPalavrasErradas] = strdup(palavras);
            (*nPalavrasErradas)++;
        }
    }
    
    return resultado;
}