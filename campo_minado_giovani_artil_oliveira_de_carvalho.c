#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define F 10
#define M 20
#define D 30

int **alocaMatriz(int tam){
    int **mat = (int **)malloc(tam * sizeof(int *));

    for (int i = 0; i < tam; i++){
        mat[i] = (int *)calloc(tam * tam, sizeof(int)); // inicializa as matrizes do jogo com 0's
    }

    return mat;
}

int **alocaMatrizCoordenadasResposta(int tam, int *qtdBombas){ // aloca uma matriz com N linhas, onde N é a quantidade de bombas, e 2 colunas, em que cada linha representa a coordenada de uma bomba
    int **mat;

    if (tam == F){
        *qtdBombas = 3;
        mat = (int **)malloc(*qtdBombas * sizeof(int *));
        for (int i = 0; i < *qtdBombas; i++){
            mat[i] = (int *)malloc(2 * sizeof(int));
        }
    }
    else if (tam == M){
        *qtdBombas = 6;
        mat = (int **)malloc(*qtdBombas * sizeof(int *));
        for (int i = 0; i < *qtdBombas; i++){
            mat[i] = (int *)malloc(2 * sizeof(int));
        }
    }
    else{
        *qtdBombas = 9;
        mat = (int **)malloc(*qtdBombas * sizeof(int *));
        for (int i = 0; i < *qtdBombas; i++){
            mat[i] = (int *)malloc(2 * sizeof(int));
        }
    }

    return mat;
}

void imprimeMatriz(int** mat, int tam, int flagModificadorChar){ // flagModificadorChar: indica se a impressão vai usar %c ou %d
    if(flagModificadorChar){
        for(int i = 0; i < tam; i++){
            for(int j = 0; j < tam; j++){
                printf("%c ", mat[i][j]);
            }
            printf("\n");
        }
    }else{
        for(int i = 0; i < tam; i++){
            for(int j = 0; j < tam; j++){
                printf("%2d ", mat[i][j]);
            }
        printf("\n");
        }
    }
}

int defineTamCampo(char *dificuldade){
    int tamCampo;

    if (!strcmp(dificuldade, "facil")){
        tamCampo = F;
    }
    else if (!strcmp(dificuldade, "medio")){
        tamCampo = M;
    }
    else{
        tamCampo = D;
    }

    return tamCampo;
}

void gerarPosicaoBombas(int **mat, int qtdBombas, int tam){
    int x, y;
    for (int i = 0; i < qtdBombas; i++){ // gera a posição aleatória da bomba
        x = rand() % tam;
        y = rand() % tam;
        mat[i][0] = x;
        mat[i][1] = y;
    }
}

int verificaQuantidadeBombas(int **mat, int x, int y, int tam){ // verifica quantas bombas há ao redor do elemento, começando da diagonal superior esquerda e seguindo no sentido horário
    int contBombas = 0;

    if (x - 1 >= 0 && y - 1 >= 0){
        if (mat[x - 1][y - 1] == -1){
            contBombas++;
        }
    }

    if (x - 1 >= 0){
        if (mat[x - 1][y] == -1){
            contBombas++;
        }
    }

    if (x - 1 >= 0 && y + 1 <= tam - 1){
        if (mat[x - 1][y + 1] == -1){
            contBombas++;
        }
    }

    if (y + 1 <= tam - 1){
        if (mat[x][y + 1] == -1){
            contBombas++;
        }
    }

    if (x + 1 <= tam - 1 && y + 1 <= tam - 1){
        if (mat[x + 1][y + 1] == -1){
            contBombas++;
        }
    }

    if (x + 1 <= tam - 1){
        if (mat[x + 1][y] == -1){
            contBombas++;
        }
    }

    if (x + 1 <= tam - 1 && y - 1 >= 0){
        if (mat[x + 1][y - 1] == -1){
            contBombas++;
        }
    }

    if (y - 1 >= 0){
        if (mat[x][y - 1] == -1){
            contBombas++;
        }
    }

    return contBombas;
}

void preencheMatrizJogo(int **mat, int tam){ // preenche a matriz com 120, código do 'x' na tabela ASCII
    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            mat[i][j] = 120;
        }
    }
}

void preencheMatrizResposta(int **mat, int **coordResp, int tam, int qtdBomba){
    for (int i = 0; i < qtdBomba; i++){ // preenche os lugares das bombas no campo
        mat[coordResp[i][0]][coordResp[i][1]] = -1;
    }

    for (int i = 0; i < tam; i++){ // preenche o restante dos lugares do campo
        for (int j = 0; j < tam; j++){
            if (mat[i][j] != -1){
                mat[i][j] = verificaQuantidadeBombas(mat, i, j, tam);
            }
        }
    }
}

int verificaJogada(int** jogo, int** resposta, int x, int y){ 
    int resultado;

    if(jogo[x][y] != resposta[x][y]){
        if(resposta[x][y] != -1){
            jogo[x][y] = resposta[x][y]+48; // transforma o número de bombas em código ASCII
            resultado = 1; // jogador não achou uma bomba, jogo continua
        }else{
            resultado = 0; // jogador achou uma bomba e perdeu o jogo
        }
    }else{
        resultado = -1; // -1 indica que o usuário fez a mesma jogada mais de uma vez
    }

    return resultado;
}

void inicioJogo(int** campoJogo, int** campoResposta, int** coordenadasResposta, int tamCampo, int qtdBombas){
    int qtdJogadas = tamCampo*tamCampo - qtdBombas, bombaExplodiu = 0;

    gerarPosicaoBombas(coordenadasResposta, qtdBombas, tamCampo);

    preencheMatrizJogo(campoJogo, tamCampo);
    preencheMatrizResposta(campoResposta, coordenadasResposta, tamCampo, qtdBombas);

    while(qtdJogadas > 0 && !bombaExplodiu){
        int x, y;
        scanf("%d,%d", &x, &y);

        int jogada = verificaJogada(campoJogo, campoResposta, x, y);

        if(jogada != -1){
            if(jogada){
                imprimeMatriz(campoJogo, tamCampo, 1);
                qtdJogadas--;
            }else{
                bombaExplodiu = 1;
            }
        }
    }

    if(!bombaExplodiu){
        printf("parabéns, vc eh fera\n");
        imprimeMatriz(campoResposta, tamCampo, 1);
    }else{
        printf("game over\n");
        imprimeMatriz(campoResposta, tamCampo, 0);
    }
}

int main(void){
    srand((unsigned int)time(NULL)); // seed do gerador aleatório, baseado no tempo
    char *dificuldade = malloc(6 * sizeof(char));
    int **campoJogo, **campoResposta, **coordenadasResposta, tamCampo, qtdBombas;

    printf("Digite a dificuldade:\nfacil\nmedio\ndificil\n");
    scanf("%s", dificuldade);

    tamCampo = defineTamCampo(dificuldade);
    campoResposta = alocaMatriz(tamCampo);
    campoJogo = alocaMatriz(tamCampo);
    coordenadasResposta = alocaMatrizCoordenadasResposta(tamCampo, &qtdBombas);

    inicioJogo(campoJogo, campoResposta, coordenadasResposta, tamCampo, qtdBombas); // método que inicia o jogo

    // liberando todos os espaços alocados das matrizes e dos vetores
    for (int i = tamCampo; i < tamCampo; i++){
        free(campoJogo[i]);
        free(campoResposta[i]);
    }
    free(campoJogo);
    free(campoResposta);

    for (int i = 0; i < qtdBombas; i++){
        free(coordenadasResposta[i]);
    }
    free(coordenadasResposta);

    free(dificuldade);

    return 0;
}