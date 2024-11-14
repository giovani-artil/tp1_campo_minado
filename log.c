#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "log.h"

FILE* criaArquivo(void){
    FILE *log = fopen("log.txt", "w");

    if(log==NULL){ // verifica se houve erro ao acessar o arquivo
        printf("Arquivo não pode ser acessado!\n");
    }
    
    return log;
}

void abreArquivo(FILE *log){
    log = fopen("log.txt", "a");

    if(log==NULL){
        printf("Arquivo não pode ser acessado!\n");
    }
}

void imprimeDataHora(FILE *log){
    struct tm *inicioJogo; // struct que armazena a data e a hora
    time_t segundos; // armazena o tempo em segundos
    time(&segundos); // obtém o tempo em segundos

    inicioJogo = localtime(&segundos); // converte para o horário local

    fprintf(log, "Inicio do Jogo: %d/%d/%d %d:%d:%d\n\n", inicioJogo->tm_mday, inicioJogo->tm_mon+1, inicioJogo->tm_year+1900, inicioJogo->tm_hour, inicioJogo->tm_min, inicioJogo->tm_sec);
}

// Utiliza a mesma lógica de impressão no método imprimeMatriz() do matriz.c, só que adaptada para imprimir em arquivo
void imprimeLog(FILE *log, int **mat, int tam, int x, int y, int flagModificadorChar){
    fprintf(log, "  ");
    for (int i = 1; i <= tam; i++){
        fprintf(log, " %2d", i);
    }
    fprintf(log, "\n");

    if (flagModificadorChar){
        for (int i = 0; i < tam; i++){
            fprintf(log, "%2d ", i + 1);

            for (int j = 0; j < tam; j++){
                fprintf(log, " %c ", mat[i][j]);
            }
            fprintf(log, "\n");
        }
        fprintf(log, "%d,%d\n\n", x, y);
    }
    else{
        for (int i = 0; i < tam; i++){
            fprintf(log, "%2d ", i + 1);
            for (int j = 0; j < tam; j++){
                fprintf(log, "%2d ", mat[i][j]);
            }
            fprintf(log, "\n");
        }
    }
}

void fechaLog(FILE *log){
    fclose(log);
}