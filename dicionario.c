#include "ortografia.h"

void abrirDicionario(char ***words, int *tamanhoDicionario, char *dicionario) {

    FILE *ficheiro = fopen(dicionario, "r");
    if (!ficheiro) {
        fprintf(stderr, "O ficheiro '%s' nao foi encontrado.\n", dicionario);
        return EXIT_FAILURE;
    }

    char palavra[50];
    while (fscanf(ficheiro, "%s", palavra) == 1) {
        char **temp = (char **)realloc(*words, (*tamanhoDicionario + 1) * sizeof(char *));
        if (temp == NULL) {
            fprintf(stderr, "Erro ao alocar memoria.\n");
            fclose(ficheiro);
            return EXIT_FAILURE;
        }
        *words = temp;
        (*words)[*tamanhoDicionario] = (char *)malloc(strlen(palavra) + 1);
        strcpy((*words)[*tamanhoDicionario], palavra);
        (*tamanhoDicionario)++;
    }
    fclose(ficheiro);
}