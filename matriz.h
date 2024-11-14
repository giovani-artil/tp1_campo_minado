// Aloca uma matriz dinamicamente
int **alocaMatriz(int linha, int coluna);

// Aloca uma matriz quadrada de ordem "tam" dinamicamente
int **alocaMatrizQuadrada(int tam);

// Imprime uma matriz. Podendo escolher entre usar %d, caso flagModificadorChar = 0, ou %c, caso flagModificadorChar = 1
void imprimeMatriz(int **mat, int tam, int flagModificadorChar);

// Insere um valor passado por parâmetro nas coordenadas especificadas
void insereMatriz(int** mat, int i, int j, int valor);

// Libera a memória alocada para a matriz
void liberaMatriz(int **mat, int linhas);