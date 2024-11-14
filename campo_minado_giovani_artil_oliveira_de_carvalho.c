#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matriz.h"
#include "log.h"

#define F 10
#define M 20
#define D 30
#define bombF 15
#define bombM 60
#define bombD 135

/*Define o tamanho do campo e a quantidade de bombas com base na dificuldade escolhida*/
void defineTamCampoQtdBombas(int dificuldade, int *qtdBombas, int *tamCampo){
    if (dificuldade == 1){
        *qtdBombas = bombF;
        *tamCampo = F;
    }
    else if (dificuldade == 2){
        *qtdBombas = bombM;
        *tamCampo = M;
    }
    else{
        *qtdBombas = bombD;
        *tamCampo = D;
    }
}

/*Aloca uma matriz Nx2, que guardará as coordenadas das bombas, sendo N a quantidade de bombas e cada coluna representando uma coordenada*/
int **alocaMatrizCoordenadasResposta(int qtdBombas){
    int **mat = alocaMatriz(qtdBombas, 2);

    return mat;
}

/*Gera a posição das bombas de maneira aleatória e usando como seed o tempo decorrido desde 01/01/1970*/
void gerarPosicaoBombas(int **mat, int qtdBombas, int tam){
    int x, y, contBombasGeradas = 0;

    while (contBombasGeradas < qtdBombas){
        int flagCoordenadaRepetida = 0;
        // % tam para gerar coordenadas dentro do intervalo [0, tam[
        x = rand() % tam;
        y = rand() % tam;

        // verificação se a coordenada gerada é igual à alguma coordenada já armazenada
        if (!contBombasGeradas){ // verifica se é a primeira coordenda gerada
            insereMatriz(mat, contBombasGeradas, 0, x);
            insereMatriz(mat, contBombasGeradas, 1, y);
            contBombasGeradas++;
        }
        else{
            for (int i = 0; i < contBombasGeradas; i++){
                if (mat[i][0] == x && mat[i][1] == y){
                    flagCoordenadaRepetida = 1; // caso a coordenada gerada seja repetida, o contador não irá ser incrementado
                }
            }

            if (!flagCoordenadaRepetida){
                insereMatriz(mat, contBombasGeradas, 0, x);
                insereMatriz(mat, contBombasGeradas, 1, y);
                contBombasGeradas++;
            }
        }
    }
}

int verificaQuantidadeBombas(int **mat, int x, int y, int tam){ // verifica quantas bombas há ao redor do elemento, começando da diagonal superior esquerda e
    int contBombas = 0;                                        // seguindo no sentido horário

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
            insereMatriz(mat, i, j, 120);
        }
    }
}

// Preenche a matriz resposta colocando as bombas em suas coordenadas e quantas bombas tem ao redor de cada coordenada
void preencheMatrizResposta(int **mat, int **coordResp, int tam, int qtdBomba){
    for (int i = 0; i < qtdBomba; i++){ // preenche os lugares das bombas no campo
        insereMatriz(mat, coordResp[i][0], coordResp[i][1], -1);
    }

    for (int i = 0; i < tam; i++){ // preenche o restante dos lugares do campo
        for (int j = 0; j < tam; j++){
            if (mat[i][j] != -1){
                insereMatriz(mat, i, j, verificaQuantidadeBombas(mat, i, j, tam));
            }
        }
    }
}

/*O método vai revelar a casa que o usuário digitou. Caso ela seja igual a 0, ele vai revelar as casas ao redor, se elas também forem iguais a 0, o método continuará revelando
as casas até que ele ache uma casa diferente 0*/
void revelaCasa(int **jogo, int **resposta, int x, int y, int tam){
    if(!resposta[x][y]){
        insereMatriz(jogo, x, y, resposta[x][y]+48);

        if(x + 1 < tam && jogo[x+1][y] == 120){
            revelaCasa(jogo, resposta, x+1, y, tam);
        }

        if(x - 1 >= 0 && jogo[x-1][y] == 120){
            revelaCasa(jogo, resposta, x-1, y, tam);
        }

        if(y + 1 < tam && jogo[x][y+1] == 120){
            revelaCasa(jogo, resposta, x, y+1, tam);
        }

        if(y - 1 >= 0 && jogo[x][y-1] == 120){
            revelaCasa(jogo, resposta, x, y-1, tam);
        }

        if(x-1 >= 0 && y-1 >= 0 && jogo[x-1][y-1] == 120){
            revelaCasa(jogo, resposta, x-1, y-1, tam);
        }

        if(x+1 < tam && y-1 >= 0 && jogo[x+1][y-1] == 120){
            revelaCasa(jogo, resposta, x+1, y-1, tam);
        }

        if(x-1 >= 0 && y+1 < tam && jogo[x-1][y+1] == 120){
            revelaCasa(jogo, resposta, x-1, y+1, tam);
        }

        if(x+1 < tam && y+1 < tam && jogo[x+1][y+1] == 120){
            revelaCasa(jogo, resposta, x+1, y+1, tam);
        }
    }else if(resposta[x][y] != -1){
        insereMatriz(jogo, x, y, resposta[x][y]+48);
    }
}


int verificaJogada(int **jogo, int **resposta, int x, int y, int tam){
    int resultado;

    if((0 <= x && x < tam) && (0 <= y && y < tam)){ // verifica se as coordenadas estão dentro do limite do tamanho
        if (jogo[x][y] != resposta[x][y]+48){ // verifica se é uma jogada repetida, comparando se a casa escolhida já foi revelada e possui mesmo valor que casa da matriz resposta
            if (resposta[x][y] != -1){
                revelaCasa(jogo, resposta, x, y, tam); // transforma o número de bombas em código ASCII
                resultado = 1; // jogador não achou uma bomba, jogo continua
            }
            else{
                resultado = 0; // jogador achou uma bomba e perdeu o jogo
            }
        }else{
            resultado = -1; // jogador repetiu uma jogada
        }
    }
    else{
        resultado = -1; // coordenada não existe
    }

    // -1 indica que a jogada foi invalidada

    return resultado;
}

/*Por conta de agora várias casas poderem serem reveladas, esse método vai sempre verificar quantas casas não foram reveladas e subtrair pela quantidade de bombas para ter 
a quantidade de jogadas restantes*/
void verificaQuantidadeJogadas(int **jogo, int tam, int *qtdJogadas, int qtdBombas){
    *qtdJogadas = 0;
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            if(jogo[i][j] == 120){
                *qtdJogadas = *qtdJogadas + 1;
            }
        }
    }
    
    *qtdJogadas = *qtdJogadas - qtdBombas;
}

void inicioJogo(int **campoJogo, int **campoResposta, int **coordenadasResposta, int tamCampo, int qtdBombas){
    int qtdJogadas = tamCampo * tamCampo - qtdBombas, bombaExplodiu = 0;

    // cria o arquivo que conterá as jogadas do usuário junto da data e hora que o jogo começou
    FILE *log = criaArquivo();
    imprimeDataHora(log);
    fechaLog(log);

    gerarPosicaoBombas(coordenadasResposta, qtdBombas, tamCampo);

    preencheMatrizJogo(campoJogo, tamCampo);
    preencheMatrizResposta(campoResposta, coordenadasResposta, tamCampo, qtdBombas);

    while (qtdJogadas > 0 && !bombaExplodiu){
        int x, y;
        printf("\nDigite uma coordenada: \n");
        scanf("%d,%d", &x, &y);

        // colocar as coordenadas digitadas para as equivalentes em C, Ex: se o usuário digita "1,1", vira 0,0
        x--;
        y--;

        int jogada = verificaJogada(campoJogo, campoResposta, x, y, tamCampo);

        if (jogada != -1){
            if (jogada){
                imprimeMatriz(campoJogo, tamCampo, 1);
                verificaQuantidadeJogadas(campoJogo, tamCampo, &qtdJogadas, qtdBombas);
            }
            else{
                bombaExplodiu = 1;
            }
        }else{
            printf("JOGADA INVALIDADA! Essa coordenada ja foi digitada ou uma coordenada invalida foi passada.\n");
        }

        // apoós cada jogada, é feito o registro no log
        abreArquivo(log);
        imprimeLog(log, campoJogo, tamCampo, x+1, y+1, 1);
        fechaLog(log);
    }

    if (!bombaExplodiu){
        printf("\nparabens, vc eh fera\n\n");
    }
    else{
        printf("\ngame over\n\n");
    }

    imprimeMatriz(campoResposta, tamCampo, 0);
    abreArquivo(log);
    imprimeLog(log, campoResposta, tamCampo, 0, 0, 0);
    
    fechaLog(log);
}

int main(void){
    srand((unsigned int)time(NULL)); // seed do gerador aleatório, baseado no tempo
    int **campoJogo, **campoResposta, **coordenadasResposta, tamCampo, qtdBombas, dificuldade;

    printf("Digite a dificuldade:\n1 - facil\n2 - medio\n3 - dificil\n\n- ");
    scanf("%d", &dificuldade);

    defineTamCampoQtdBombas(dificuldade, &qtdBombas, &tamCampo);
    campoResposta = alocaMatrizQuadrada(tamCampo);
    campoJogo = alocaMatrizQuadrada(tamCampo);
    coordenadasResposta = alocaMatrizCoordenadasResposta(qtdBombas);

    inicioJogo(campoJogo, campoResposta, coordenadasResposta, tamCampo, qtdBombas); // método que inicia o jogo

    // liberação de memória alocada
    liberaMatriz(campoJogo, tamCampo);
    liberaMatriz(campoResposta, tamCampo);
    liberaMatriz(coordenadasResposta, qtdBombas);

    return 0;
}