/*Cria um arquivo "log.txt". Caso ele já exista, o conteúdo dele será sobrescrito*/
FILE* criaArquivo(void);

/*Abre o arquivo "log.txt". Ao invés de ser aberto com modo "w", será aberto com o modo "a", para adicionar conteúdo ao arquivo*/
void abreArquivo(FILE *log);

/*Imprime a data e a hora no arquivo*/
void imprimeDataHora(FILE *log);

/*Registra as jogadas no log, imprimindo as coordenadas e a matriz que o usuário vê*/
void imprimeLog(FILE *log, int **mat, int tam, int x, int y, int flagModificadorChar);

/*Salva as mudanças no arquivo e fecha ele*/
void fechaLog(FILE *log);