// TP01 PAA - 2020/2 - Daniel Fernandes Pinho (2634) e Taianne Mota (2679)

#include <stdio.h>
#include "labirinto.c"

int main(){
	srand(time(NULL)); //usado para funcao rand gerar numeros diferentes de acordo com o tempo do PC

	int op, leuArquivo, solucao, selecao, linhas, colunas, qtdChaves, qtdParedes, qtdPortas, tamanho;
	char nomeArquivo[50];
	TipoModoAnalise analise;
	TipoLabirinto labirinto;
	TipoEstudante estudante;

	do{
		//MENU
        printf("TESTE");
        printf("-----------------------------TRABALHO 1 - PAA---------------------------------\n");	    
        printf("|                PROGRAMA LabirintScape: Opcoes do programa:                  |\n");
        printf("|                1) Carregar novo arquivo de dados.                           |\n");
        printf("|                2) Processar e exibir resposta                               |\n");
        printf("|                3) Sair do programa                                          |\n");
        printf("------------------------------------------------------------------------------\n");	
        
        // tratamento de entrada dos dados
        do{
            printf ("Digite um número:");
            scanf ("%d", &op);
        }while (op < 0 || op > 3); 

        switch(op){
            case 1:
                printf("Digite o nome do arquivo de texto (sem a extensao): ");
                scanf("%s", nomeArquivo);
                leuArquivo = lerArquivo(&labirinto, nomeArquivo);
                if (leuArquivo){ 
                	system("clear");
                	printf ("\n->>>>Arquivo lido com sucesso!<<<<-\n\n");
            	}
            break;
            case 2:
            if(!leuArquivo){
               printf("Por favor carregue antes um arquivo de dados!");
            }
            solucao = inicializacoes(&labirinto, &estudante, &analise, 1); 
		                    if (modoAnalise){
						    	printf ("\nModo analise ativo\n\n");
						    	if(solucao){ // solucao = 1 
									printf("O estudante se movimentou %d vezes e chegou na coluna %d da primeira linha\n", analise.numeroMovimentos, estudante.ultimaPosicao.y, estudante.ultimaPosicao.x);
									printf("Numero total de chamadas recursivas: %d\n", analise.chamadasRecursivas);
									printf("Nivel maximo de recursao: %d\n", analise.qtdMaxChamadasRecursivas);
								}else{
									printf("O estudante se movimentou %d vezes e percebeu que o labirinto nao tem saida\n", analise.numeroMovimentos);
									printf("Numero total de chamadas recursivas: %d\n", analise.chamadasRecursivas);
									printf("Nivel maximo de recursao: %d\n", analise.qtdMaxChamadasRecursivas); // nivel max de recursao
								}
							}else{
								printf ("\nModo analise nao ativo\n\n");
								if(solucao){
									printf("O estudante se movimentou %d vezes e chegou na coluna %d da primeira linha\n", analise.numeroMovimentos, estudante.ultimaPosicao.y, estudante.ultimaPosicao.x);
								}else{
									printf("O estudante se movimentou %d vezes e percebeu que o labirinto nao tem saida\n", analise.numeroMovimentos);
								}
							}
		            	break;
	    case 3:
		  exit(0);
		break;
	    }
    }while(op!=3);

    return 0;
}
