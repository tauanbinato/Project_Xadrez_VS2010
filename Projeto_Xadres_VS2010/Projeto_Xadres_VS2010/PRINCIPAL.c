#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   <stdlib.h>

#include   "lista.h"
#include   "TABULEIRO.h"
#include   "Peca.h"
#include   "CLASSE_PECA.H"
#include   "PRINCIPAL.H"

/***********************************************************************
*
*  $TC Tipo de dados: PRI Descritor da cabeça de uma simulação
*
*
*  $ED Descrição do tipo
*     Armazena referências para o tabuleiro e para as cabeças das
*     listas de peças e classes de peças.
*
***********************************************************************/

typedef struct PRI_tagSimulacao {

	TAB_ppAncoraTabuleiro pTab;
	/* Ponteiro para o tabuleiro corrente */
	LIS_tppLista pListaPecas;
	/* Ponteiro para a lista de peças */
	LIS_tppLista pListaClasses;
	/* Ponteiro para a lista de classes de peças */

} PRI_tpSimulacao;

/*****  Variável global que armazena a simulação corrente  *****/

PRI_tpSimulacao simulacao;

int main(void) 
{

	int opcao;

	LIS_CriarLista(&simulacao.pListaClasses, "Classes");
	PRI_Inicializa();
	PRI_CarregarArquivoMovimento("./MOVIMENTOS.txt");

	do {
        printf("\n(pressione qualquer tecla para exibir o menu)");
        PRI_MenuPrincipal( &opcao );
       /* switch(opcao) {
            case 1:
            PRN_NovoTabuleiro( );
            break;
            case 2:
            PRN_AbrirTabuleiro( );
            break;
            case 3:
            PRN_SalvarTabuleiro( );
            break;
            case 9:
            system("dir");
            break;
            case 11:
            PRN_ListarClasses( );
            break;
            case 12:
            PRN_CriarClasse( );
            break;
            case 21:
            PRN_ListarPecas( );
            break;
            case 22:
            PRN_CriarPeca( );
            break;
            case 23:
            PRN_AlterarPeca( );
            break;
            case 24:
            PRN_ExcluirPeca( );
            break;
            case 31:
            PRN_ExibirTabuleiro( );
            break;
            case 32:
            PRN_ChecarXequeMate( );
            break;
        }*/
    } while( opcao != 99 );


	return 0;
}
void PRI_MenuPrincipal( int * opcao ) {
    printf("\n=== MENU ===\n\n");
    printf("01. Novo\n02. Abrir\n");
    printf("11. Listar classes de peca\n12. Criar classe de peca\n\n");
    printf("21. Listar pecas\n22. Criar peca\n23. Alterar peca\n24. Excluir peca\n\n");
    printf("31. Exibir tabuleiro.\n32. Checar Xeque-mate\n\n");
    printf("99. Sair\n\nDigite o codigo da opcao desejada: \n> ");

    scanf("%d", opcao);
}


int PRI_CarregarArquivoMovimento(char* path) {

	char auxString[200], classe,jogador;
	int i, j;
	FILE *fp;
	CPC_tppClassePeca pClasse;
	PEC_tppPeca pPeca;

	fp = fopen(path, "r");
	if (fp == NULL) {
		printf("Path invalido.\n\n");
		return 0;
	}

	while (fscanf(fp, " %s", auxString) == 1) {
		if (strcmp(auxString, "CLASSE") == 0) {
			fscanf(fp, " %s", auxString);
			if (CPC_CriarClassePeca(&pClasse, auxString[0], auxString) != CPC_CondRetOK) {
				printf("Faltou memória.");
				exit(1);
			}
			LIS_InserirNo(simulacao.pListaClasses, (void*) pClasse);

		}
		else if (strcmp(auxString, "MOV") == 0) {
			fscanf(fp, " %d %d", &i, &j);
			if (CPC_AdicionarMovimento(pClasse, i, j) == CPC_CondRetFaltouMemoria) 
			{
				printf("Faltou memória.");
				exit(1);
			}

		}

	fclose(fp);
	return 1;
}
}

void PRI_Inicializa(void) {
	//int linha = 8;
	//int coluna = 8;
	if (TAB_CriaTabuleiro(&simulacao.pTab, 8) != TAB_CondRetOK) 
	{
		printf("ERRO DE MEMORIA AO CRIAR TABULEIRO");
		exit(1);
	}
	
	if (LIS_CriarLista(&simulacao.pListaClasses, "Classes") != 0)
	{
		TAB_DestruirTabuleiro(&simulacao.pTab);
		printf("ERRO DE MEMORIA AO CRIAR LISTA DE CLASSES");
		exit(1);
	}

	if (LIS_CriarLista(&simulacao.pListaPecas, "Pecas") != 0) 
	{
		TAB_DestruirTabuleiro(&simulacao.pTab);
		LIS_DestroiLista(&simulacao.pListaClasses);
		printf("ERRO DE MEMORIA AO CRIAR LISTA DE PECAS");
		exit(1);
	}
}
int PRI_ChecarMovimentoPulo (int movI, int movJ) 
{
	if(movI == movJ || movI == -movJ || movI == 0 || movJ == 0)
	{
		return 0;
	}

    return 1;
}

int PRI_ChecarLegalidade(char jogador, char iOrigem, int jOrigem, char iDestino, int jDestino) {
	PEC_tppPeca defensor;
	char jogadorDefensor;
	PEC_tppPeca obstaculo;
	int movI, movJ;
	char i; int j;
	char coraux;

	movI = iDestino - iOrigem;
	movJ = jDestino - jOrigem;

	PEC_ObterCorDePeca(&defensor,&jogadorDefensor);
	TAB_ObterPeca(simulacao.pTab, iDestino, jDestino,&defensor,&jogadorDefensor);

	if (defensor != NULL) 
	{
		PEC_ObterCorDePeca(defensor, &jogadorDefensor); //verifica se a cor da peca que esta ocupando a pos é a mesma (nao e permitido comer pecas do mesmo time)
		if (jogadorDefensor == jogador) {
			return 0;
		}
	}

	//
	if (PRI_ChecarMovimentoPulo(movI, movJ) == 1) {
		// Sendo um movimento de pulo, não há necessidade de checar obstáculos

		return 1;
	}

	// Não sendo um movimento de pulo, precisamos saber se há obstáculos.

	if (movJ == 0) {
		if (movI > 0) {
			// movimento de letra crescente
			j = jOrigem; // = jDestino;

			for (i = iOrigem + 1; i < iDestino; i++) {
				TAB_ObterPeca(simulacao.pTab, i, j,&obstaculo,&coraux);
				if (obstaculo != NULL) {
					return 0;
				}
			}

			return 1;
		}
		if (movI < 0) {
			// movimento de letra decrescente
			j = jOrigem; // = jDestino;

			for (i = iOrigem - 1; i > iDestino; i--) {
				TAB_ObterPeca(simulacao.pTab, i, j,&obstaculo,&coraux);;
				if (obstaculo != NULL) {
					return 0;
				}
			}

			return 1;
		}
	}

	if (movI == 0) {
		if (movJ > 0) {
			// movimento de numero crescente
			i = iOrigem; // = iDestino;

			for (j = jOrigem + 1; j < jDestino; j++) {
				TAB_ObterPeca(simulacao.pTab, i, j,&obstaculo,&coraux);
				if (obstaculo != NULL) {
					return 0;
				}
			}

			return 1;
		}
		if (movJ < 0) {
			// movimento de numero decrescente
			i = iOrigem; // = iDestino;

			for (j = jOrigem - 1; j > jDestino; j--) {
				TAB_ObterPeca(simulacao.pTab, i, j,&obstaculo,&coraux);
				if (obstaculo != NULL) {
					return 0;
				}
			}

			return 1;
		}
	}

	if (movJ > 0) {
		if (movI > 0) {
			// movimento de letra e numero crescente
			for (i = iOrigem + 1, j = jOrigem + 1; i < iDestino && j < jDestino; i++, j++) {
				TAB_ObterPeca(simulacao.pTab, i, j,&obstaculo,&coraux);
				if (obstaculo != NULL) {
					return 0;
				}
			}

			return 1;
		}
		else {
			//movimento de letra crescente e numero decrescente
			for (i = iOrigem - 1, j = jOrigem + 1; i > iDestino && j < jDestino; i--, j++) {
				TAB_ObterPeca(simulacao.pTab, i, j,&obstaculo,&coraux);
				if (obstaculo != NULL) {
					return 0;
				}
			}

			return 1;
		}
	}

	else {
		if (movI > 0) {
			// movimento de letra decrescente e numero crescente
			for (i = iOrigem + 1, j = jOrigem - 1; i < iDestino && j > jDestino; i++, j--) {
				TAB_ObterPeca(simulacao.pTab, i, j,&obstaculo,&coraux);
				if (obstaculo != NULL) {
					return 0;
				}
			}

			return 1;
		}
		else {
			// movimento de letra e numero decrescente
			for (i = iOrigem - 1, j = jOrigem - 1; i > iDestino && j > jDestino; i--, j--) {
				TAB_ObterPeca(simulacao.pTab, i, j,&obstaculo,&coraux);
				if (obstaculo != NULL) {
					return 0;
				}
			}

			return 1;
		}
	}

	return 1;
}
void PRI_ChecarXequeMate( ) {
    char reiI; int reiJ;
    PEC_tppPeca rei;

    char i, iDest;
    int j, jDest;
    PEC_tppPeca pecaAtual, pPecaComida;
    char jogadorDaPecaAtual;
    CPC_tppClassePeca classeDaPecaAtual;
	char *cor,*nomeclassepeca,*corpeccomida;
    int nMovs, c, movI, movJ, ameaca, legalidade;

    
    // Primeiro, precisamos ter um rei válido
    rei = PRI_ObterReiBranco(&reiI, &reiJ);
    if(rei == NULL) {
        printf("Nao foi encontrado um Rei do jogador branco no tabuleiro. ");
        return;
    }

    // CHECAR XEQUE
    // Um pré-requisito para estar em xeque-mate é estar em xeque. Vamos checar essa condição.
    // O jogador branco está (no mínimo) em xeque caso o rei branco esteja ameaçado e seja a vez do jogador branco.
    if( PRI_ChecarAmeacaReiBranco() == 0) {
        printf("Não é xeque-mate nem xeque.");
        return;
    }

    // Agora, precisamos ver se ha algum movimento que possa ser feito que deixe o rei branco fora de ameaça.
    // Para cada casa do tabuleiro, vamos ver se contém uma peça branca; se sim, vamos realizar cada um  
    // de seus movimentos, retornando o tabuleiro para a posição inicial após cada movimento realizado.
    // Depois de cada movimento, será verificado se a posição ainda configura ameaça para o rei branco. 
    // Se houver algum movimento possível que deixe o rei branco fora de perigo, o jogador branco não
    // está em xeque-mate. Caso contrário, ele está em xeque-mate.
    for(i = 'A'; i <= 'H'; i++) {
        for(j = 1; j <= 8; j++) {
			if(PEC_ObterCorDePeca(pecaAtual,cor)==PEC_CondRetOK)
			{
            TAB_ObterPeca( simulacao.pTab,  i, j ,&pecaAtual,cor);

            if( pecaAtual != NULL ) {
                PEC_ObterCorDePeca( pecaAtual, &jogadorDaPecaAtual );

                if( jogadorDaPecaAtual == 'B') {
                    CPC_ObterNome( &classeDaPecaAtual,nomeclassepeca);

                    if( classeDaPecaAtual == NULL ){
                        printf("Erro: peca com classe nula.");
                        exit(1);
                    }

                    CPC_ObterNumeroMovimentos( classeDaPecaAtual, &nMovs );

                    for(c = 0; c < nMovs; c++){
                        CPC_ObterMovimento( classeDaPecaAtual, c, &movI, &movJ );

                        iDest = i + movI;
                        jDest = j + movJ;

                        if(TAB_ChecarPosicaoValida(iDest, jDest) == TAB_CondRetOK) {

                            //checar se movimento eh legal
							legalidade = PRI_ChecarLegalidade( jogadorDaPecaAtual, i, j, iDest, jDest);
                            if( legalidade == 1 ) {
								PEC_ObterCorDePeca(pPecaComida,corpeccomida);
                                TAB_MoverPeca( simulacao.pTab, j, i, jDest, iDest,&pPecaComida,corpeccomida);

								ameaca = PRI_ChecarAmeacaReiBranco();

								TAB_DesfazerMovimento( simulacao.pTab, j, i, iDest, jDest, (void**)pPecaComida);

                                if(ameaca == 0){
                                    printf("O jogador branco esta em xeque.\n"
                                           "Movimento: %c%d para %c%d.", i, j, iDest, jDest);
                                    return;
								}
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    printf("O jogador branco esta em xeque-mate.");

    return;
}

int PRI_ChecarAmeacaReiBranco ( ) {
    char reiI; int reiJ;
    PEC_tppPeca rei, pecaAtual;
	char jogadorDaPecaAtual;
	CPC_tppClassePeca classeDaPecaAtual;
	char cor,*nomeclassepeca;
	char i;
	int j, movI, movJ, resposta, legalidade;
	
	// Primeiro, precisamos ter um rei válido
    rei = PRI_ObterReiBranco(&reiI, &reiJ);
    if(rei == NULL) {
        printf("Nao foi encontrado uma peca com a classe 'Rei' que pertenca "
               "ao jogador branco e que esteja posicionado no tabuleiro.\n"
               "Por favor, ajuste o cenario do tabuleiro e tente novamente.");
        return 0;
    }

	// Vamos ver se há algum movimento possível que coma o rei branco.
	// Para cada casa do tabuleiro, vamos ver se contém uma peça preta; se sim, vamos verificar
	// se existe algum movimento possível e legal para essa peça que a permita comer
	// o rei branco.
	for(i = 'A'; i <= 'H'; i++) {
        for(j = 1; j <= 8; j++) {
            TAB_ObterPeca( simulacao.pTab,i, j, &pecaAtual,&cor);

            if( pecaAtual != NULL ) {
                PEC_ObterCorDePeca( pecaAtual, &jogadorDaPecaAtual );

                if( jogadorDaPecaAtual == 'P') {
                    CPC_ObterNome( &classeDaPecaAtual, nomeclassepeca );

                    if( classeDaPecaAtual == NULL ){
                        printf("Erro: peca com classe nula.");
                        exit(1);
                    }

					movI = -(reiI - i);
					movJ = -(reiJ - j);

					CPC_ChecarMovimento(classeDaPecaAtual, movI, movJ, &resposta);

					if(resposta == 1){
						legalidade = PRI_ChecarLegalidade( jogadorDaPecaAtual, i, j, reiI, reiJ);
						if(legalidade == 1){
							return 1;
						}
					}
                }
            }
        }
    }

    return 0;
}

PEC_tppPeca PRI_ObterReiBranco ( char * i, int * j ) {
    PEC_tppPeca pPeca;
    char jogador;
    CPC_tppClassePeca pClasse;
	char ic; int jc;
	char *nome,cor;

	for( ic = 'A'; ic <= 'H'; ic++) {
        for( jc = 1; jc <= 8; jc++) {
            TAB_ObterPeca(simulacao.pTab,ic, jc, &pPeca,&cor );
            if(pPeca == NULL)
                continue;

            PEC_ObterCorDePeca(pPeca, &jogador);
            if(jogador != 'B') 
				continue;
			
            CPC_ObterNome(pClasse, &nome);
						
			if(strcmp(nome, "Rei") != 0)
				continue;
			
			*i = ic;
			*j = jc;
			return pPeca;
        }
    }

	return NULL;
}