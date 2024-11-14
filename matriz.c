#include<stdio.h>
#include<stdlib.h>
#include "matriz.h"

int **alocaMatriz(int linha, int coluna){
    int **mat = (int **)malloc(linha * sizeof(int *));

    if(mat == NULL){ //verifica se há memória suficiente pra ser alocada
        printf("Memória Insuiciente!\n");
        exit(1);
    }

    for (int i = 0; i < linha; i++){
        mat[i] = (int *)malloc(coluna * sizeof(int));
        
        if(mat[i] == NULL){
            printf("Memória Insuiciente!\n");
            exit(1);
        }
    }

    return mat;
}

int **alocaMatrizQuadrada(int tam){
    int **mat = (int **)malloc(tam * sizeof(int *));

    if(mat == NULL){ //verifica se há memória suficiente pra ser alocada
        printf("Memória Insuiciente!\n");
        exit(1);
    }

    for (int i = 0; i < tam; i++){
        mat[i] = (int *)calloc(tam * tam, sizeof(int)); // inicializa as matrizes do jogo com 0's
        
        if(mat[i] == NULL){
            printf("Memória Insuiciente!\n");
            exit(1);
        }
    }

    return mat;
}

void imprimeMatriz(int **mat, int tam, int flagModificadorChar){ // flagModificadorChar: indica se a impressão vai usar %c ou %d // 1 = %c, 0 = %d
    printf("  ");
    for (int i = 1; i <= tam; i++){
        printf(" %2d", i);
    }
    printf("\n");

    if (flagModificadorChar){
        for (int i = 0; i < tam; i++){
            printf("%2d ", i + 1);

            for (int j = 0; j < tam; j++){
                printf(" %c ", mat[i][j]);
            }
            printf("\n");
        }
    }
    else{
        for (int i = 0; i < tam; i++){
            printf("%2d ", i + 1);
            for (int j = 0; j < tam; j++){
                printf("%2d ", mat[i][j]);
            }
            printf("\n");
        }
    }
}

void insereMatriz(int** mat, int i, int j, int valor){
    mat[i][j] = valor;
}

void liberaMatriz(int **mat, int linhas){
    for (int i = 0; i < linhas; i++){
        free(mat[i]);
    }
    free(mat);
}