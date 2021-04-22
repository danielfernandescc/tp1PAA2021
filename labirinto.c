// TP01 PAA - 2020/2 - Daniel Fernandes Pinho (2634) e Taianne Mota (2679)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "labirinto.h"
#define modoAnalise 1

//funcao para alocar espacco na memoria de acordo com a informação do arquivo lido
void aloca_espaco_memoria(TipoLabirinto *labirinto){
	int i;
    labirinto->posicionamento = (char **) malloc(labirinto->qtdLinhas * sizeof(char *));
    for (i = 0; i < labirinto->qtdLinhas; i++) {
        labirinto->posicionamento[i] = (char *) malloc(labirinto->qtdColunas * sizeof(char));
    }
}


int lerArquivo(TipoLabirinto *labirinto, char *nomeArquivo){
	FILE *arquivo;
    char caminhoArquivo[150];
    char *string;
    int i, j, linhas, colunas, vidas;
    strcpy(caminhoArquivo, "/home/daniel/tp2/"); 
    strcat(caminhoArquivo, nomeArquivo); 
    strcat(caminhoArquivo, ".txt");
    arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        printf("\nErro de leitura do arquivo\n");
        return 0; //retorna 0 caso nao seja possivel ler o arquivo
    }else{
        fscanf(arquivo, "%d %d %d\n", &linhas, &colunas, &vidas); // leitura linha a linha
        // atribuição de valores na estrutura dinâmicamente alocada
        labirinto->qtdLinhas = linhas;
        labirinto->qtdColunas = colunas;
        labirinto->numeroChaves = vidas;
        aloca_espaco_memoria(labirinto); 
        // leitura do arquivo a partir da segunda linha 
        while (!feof(arquivo)) { 
            for (i = 0; i < labirinto->qtdLinhas; i++) { 
                for (j = 0; j < labirinto->qtdColunas; j++) {
                    fscanf(arquivo, "%s ", string); 
                    if(strcmp(string,"F"))
                        labirinto->posicionamento[i][j] = '0'; // 1 para posicao F
                    if(strcmp(string,"I"))
                        labirinto->posicionamento[i][j] = '1'; // 1 para posicao I                     
                    if(!strcmp(string,"I") && !(strcmp(string,"F"))){
                        labirinto->posicionamento[i][j] = *string;
                       
                    }
                     //printf("%s\n", &labirinto->posicionamento[i][j]);  
                         //preenche o labirinto
                }
            }
        }
	}
    fclose(arquivo);
    return 1; 
}

//funcao de programção dinâmica 
/*
//mudar para cima ou esquerda
int Memoization(TipoLabirinto *piramide, int caminho[piramide->qtdLinhas][piramide->qtdLinhas], int linha, int coluna){ // linha = posicao_inicial_x , coluna= posicao_inicia_y
    //int cima = 0 , esquerda = 0;	
    int baixo = 0, direita = 0;

    if(linha == piramide->qtdLinhas - 1){ //ultima linha
        return (piramide->espaco[linha][coluna]);
    }

    if(caminho[linha + 1][coluna] == 0){
        baixo = piramideMemoization(piramide, analise, caminho, linha + 1, coluna);
		analise->qtdChamadaRecursiva ++;
    } else{
        baixo = caminho[linha + 1][coluna];
    }
    if(caminho[linha + 1][coluna + 1] == 0){
        direita = piramideMemoization(piramide, analise, caminho, linha + 1, coluna + 1);
        analise->qtdChamadaRecursiva ++;
    } else{
        direita = caminho[linha + 1][coluna + 1];
    }

    if(baixo>=direita){
        caminho[linha][coluna] = piramide->espaco[linha][coluna] + baixo;
		return caminho[linha][coluna];
    } else{
        caminho[linha][coluna] = piramide->espaco[linha][coluna] + direita;
		return caminho[linha][coluna];
    }
}
*/






//função para recursividade do backtracking.
int movimenta_estudante(TipoEstudante *estudante, TipoLabirinto *labirinto, TipoModoAnalise *analise, int caminho[labirinto->qtdLinhas][labirinto->qtdColunas], int x, int y, int chave[labirinto->qtdLinhas][labirinto->qtdColunas]){
	int i, j, cont = 0, qtdChave;
	estudante->posicaoAtual.x = x;
	estudante->posicaoAtual.y = y;
	analise->maxAux++;
	analise->chamadasRecursivas++;

    // conta quantas chaves tem na matriz chave
	for (i = 0; i < labirinto->qtdLinhas; i++) { 
        for (j = 0; j < labirinto->qtdColunas; j++) {
            if (chave[i][j] == 1) {
                cont++; 
            }
        }
    }

	qtdChave = labirinto->numeroChaves - cont;

    //quando chegar na primeira linha da matriz (labirinto)
	if (estudante->posicaoAtual.x == 0 && labirinto->posicionamento[x][y] != '2'){
		if (labirinto->posicionamento[x][y] == '3'){ // caso seja uma porta verifica se há uma chave suficiente para abri-la
    		if (qtdChave > 0){ 
    			chave[x][y] = 1;
				estudante->ultimaPosicao.x = x;
				estudante->ultimaPosicao.y = y;
				analise->numeroMovimentos++;
				printf("Linha: %d Coluna: %d\n", estudante->ultimaPosicao.x+1, estudante->ultimaPosicao.y+1); //imprime a posicao final do estudante
				return 1;
			}
			return 0;
		}

		estudante->ultimaPosicao.x = x;
		estudante->ultimaPosicao.y = y;
		analise->numeroMovimentos++;
		printf("Linha: %d Coluna: %d\n", estudante->ultimaPosicao.x+1, estudante->ultimaPosicao.y+1);
		return 1;
	}


    // percorre o labirinto sem que repita posicoes ja verificadas
    if ((x >= 0) && (x < labirinto->qtdLinhas) && (y >= 0) && (y < labirinto->qtdColunas) && (labirinto->posicionamento[x][y] != '2') && (caminho[x][y] == 0)){
    	caminho[x][y] = 1; 
    	analise->numeroMovimentos++;
    	printf("Linha: %d Coluna: %d\n", x+1, y+1); // imprime os movimentos

    	if (labirinto->posicionamento[x][y] == '3'){ 
    		if (qtdChave > 0){ 
    			chave[x][y] = 1; // usou uma chave
    	        // movimento para cima
				if (movimenta_estudante(estudante, labirinto, analise, caminho, x - 1, y, chave)){
					return 1;
				}
				//movimento para a direita
				if (movimenta_estudante(estudante, labirinto, analise, caminho, x, y + 1, chave)){
					return 1;
				}
				//movimento para a esquerda
				if (movimenta_estudante(estudante, labirinto, analise, caminho, x, y - 1, chave)){
					return 1;
				}
				//movimento para baixo 
				if (movimenta_estudante(estudante, labirinto, analise, caminho, x + 1, y, chave)){
					return 1;
				}
				chave[x][y] = 0; // 0 para voltar pela porta
			}
			return 0;
		}

		if (movimenta_estudante(estudante, labirinto, analise, caminho, x - 1, y, chave)){
			return 1;
		}

		if (movimenta_estudante(estudante, labirinto, analise, caminho, x, y + 1, chave)){
			return 1;
		}

		if (movimenta_estudante(estudante, labirinto, analise, caminho, x, y - 1, chave)){
			return 1;
		}

		if (movimenta_estudante(estudante, labirinto, analise, caminho, x + 1, y, chave)){
			return 1;
		}
		return 0;
	}


	if (analise->qtdMaxChamadasRecursivas < analise->maxAux){
		analise->qtdMaxChamadasRecursivas = analise->maxAux;
	}

	analise->maxAux = 0; 
	return 0;
}

int inicializacoes(TipoLabirinto *labirinto, TipoEstudante *estudante, TipoModoAnalise *analise, int opcao){
    int i, j, x , y ;
    int caminho[labirinto->qtdLinhas][labirinto->qtdColunas];
    int chave[labirinto->qtdLinhas][labirinto->qtdColunas];

    //inicializa posicao
    for (i = 0; i < labirinto->qtdLinhas; i++) {
        for (j = 0; j < labirinto->qtdColunas; j++) {
            if (labirinto->posicionamento[i][j] == '0') {//se a posicao for a do estudante
                estudante->primeiraPosicao.x = i;
                estudante->primeiraPosicao.y = j;
                estudante->posicaoAtual.x = i;
                estudante->posicaoAtual.y = j;
                estudante->ultimaPosicao.x = 0;
                estudante->ultimaPosicao.y = 0;
                //x e y sao usados para enviar para as funcoes que movimentam o estudante
                x = estudante->posicaoAtual.x;
                y = estudante->posicaoAtual.y;
            }
        }
    }

    //inicializa caminho
    for (i = 0; i < labirinto->qtdLinhas; i++) {
        for (j = 0; j < labirinto->qtdColunas; j++){
            caminho[i][j] = 0;
    	}
    }

	//inicializa chaves
    for (i = 0; i < labirinto->qtdLinhas; i++) {
        for (j = 0; j < labirinto->qtdColunas; j++){
            chave[i][j] = 0;
    	}
    }

    //inicializa analise
    analise->chamadasRecursivas = -1; // -1 para chamada nao recursiva
	analise->numeroMovimentos = -1; // -1 para dizer que nao ha movimento
	analise->qtdMaxChamadasRecursivas = -1; // -1 para chamada nao recursiva pois é a primeira 
	analise->maxAux = 0;

    if (opcao == 1){
		return (movimenta_estudante(estudante, labirinto, analise, caminho, x, y, chave));
	}
}
