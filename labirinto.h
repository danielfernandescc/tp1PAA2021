// TP01 PAA - 2020/2 - Daniel Fernandes Pinho (2634) e Taianne Mota (2679)

#ifndef LABIRINTO_H_INCLUDED
#define LABIRINTO_H_INCLUDED

// Coordenadas da posicao do estudante onde x é linha e y coluna
typedef struct Posicao{
    int x;
    int y;
    char * valor; // tratar 
}TipoPosicao;

//posicoes do estudante em alguns momentos
typedef struct Estudante{
    TipoPosicao primeiraPosicao;
    TipoPosicao posicaoAtual;
    TipoPosicao ultimaPosicao;
}TipoEstudante;

//Dados do labrinto
typedef struct Labirinto{
    char **posicionamento; 
    int qtdLinhas;  //ok            
    int qtdColunas; //ok 
	int numeroChaves; //ok // mudara para numero de vidas
    
}TipoLabirinto;


// Dados das análise a serem feitas
typedef struct ModoAnalise{
	int chamadasRecursivas;
	int numeroMovimentos;
	int qtdMaxChamadasRecursivas;
	int maxAux;
}TipoModoAnalise;


//escopo das funcoes
void aloca_espaco_memoria(TipoLabirinto *Labirinto);
int lerArquivo(TipoLabirinto *labirinto, char *nomeArquivo);
int movimenta_estudante(TipoEstudante *estudante, TipoLabirinto *labirinto, TipoModoAnalise *analise, int caminho[labirinto->qtdLinhas][labirinto->qtdColunas], int x, int y, int chave[labirinto->qtdLinhas][labirinto->qtdColunas]);
int inicializacoes(TipoLabirinto *labirinto, TipoEstudante *estudante, TipoModoAnalise *analise, int opcao);

#endif // LABIRINTO_H_INCLUDED
