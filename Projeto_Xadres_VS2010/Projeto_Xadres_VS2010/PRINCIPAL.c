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
*  $TC Tipo de dados: PRN Descritor da cabeça de uma simulação
*
*
*  $ED Descrição do tipo
*     Armazena referências para o tabuleiro e para as cabeças das
*     listas de peças e classes de peças.
*
***********************************************************************/

typedef struct PRN_tagSimulacao {

	TAB_ppAncoraTabuleiro pTab;
	/* Ponteiro para o tabuleiro corrente */
	LIS_tppLista pListaPecas;
	/* Ponteiro para a lista de peças */
	LIS_tppLista pListaClasses;
	/* Ponteiro para a lista de classes de peças */

} PRN_tpSimulacao;

/*****  Variável global que armazena a simulação corrente  *****/

PRN_tpSimulacao simulacao;

int main(void) {


	LIS_CriarLista(&simulacao.pListaClasses, "Classes");
	PRI_Inicializa();
	PRI_CarregarArquivoMovimento("./MOVIMENTOS.txt");

	

	return 0;




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
int PRN_ChecarMovimentoPulo (int movI, int movJ) 
{
	if(movI == movJ || movI == -movJ || movI == 0 || movJ == 0)
	{
		return 0;
	}

    return 1;
}

int PRN_ChecarLegalidade(char jogador, char iOrigem, int jOrigem, char iDestino, int jDestino) {
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
	if (PRN_ChecarMovimentoPulo(movI, movJ) == 1) {
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
/*void PRN_ChecarXequeMate( ) {
    char reiI; int reiJ;
    PEC_tppPeca rei;

    char i, iDest;
    int j, jDest;
    PEC_tppPeca pecaAtual, pPecaComida;
    //PEC_tpJogador jogadorDaPecaAtual;
    CPC_tppClassePeca classeDaPecaAtual;
	char *cor;
    int nMovs, c, movI, movJ, ameaca, legalidade;

    
    // Primeiro, precisamos ter um rei válido
    rei = PRN_ObterReiBranco(&reiI, &reiJ);
    if(rei == NULL) {
        printf("Nao foi encontrado uma peca com a classe 'Rei' que pertenca "
               "ao jogador branco e que esteja posicionado no tabuleiro.\n"
               "Por favor, ajuste o cenario do tabuleiro e tente novamente.");
        return;
    }

    // CHECAR XEQUE
    // Um pré-requisito para estar em xeque-mate é estar em xeque. Vamos checar essa condição.
    // O jogador branco está (no mínimo) em xeque caso o rei branco esteja ameaçado e seja a vez do jogador branco.
    if( PRN_ChecarAmeacaReiBranco() == 0) {
        printf("O cenario configurado nao eh de xeque-mate (e nem de xeque).");
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
                PEC_ObterJogador( pecaAtual, &jogadorDaPecaAtual );

                if( jogadorDaPecaAtual == JOGADOR_BRANCO) {
                    PEC_ObterClassePeca( pecaAtual, &classeDaPecaAtual );

                    if( classeDaPecaAtual == NULL ){
                        printf("Erro: peca com classe nula.");
                        PRN_Sair(1);
                    }

                    CPC_ObterNumeroMovimentos( classeDaPecaAtual, &nMovs );

                    for(c = 0; c < nMovs; c++){
                        CPC_ObterMovimento( classeDaPecaAtual, c, &movI, &movJ );

                        iDest = i + movI;
                        jDest = j + movJ;

                        if(TAB_ChecarPosicaoValida(iDest, jDest) == TAB_CondRetOK) {

                            //checar se movimento eh legal
							legalidade = PRN_ChecarLegalidade( jogadorDaPecaAtual, i, j, iDest, jDest);
                            if( legalidade == 1 ) {

                                TAB_MoverPeca( simulacao.pTab, j, i, jDest, iDest,&pPecaComida);

								ameaca = PRN_ChecarAmeacaReiBranco();

								TAB_DesfazerMovimento( simulacao.pTab, j, i, iDest, jDest, (void**)pPecaComida,cor);

                                if(ameaca == 0){
                                    printf("O jogador branco esta em xeque, mas nao em xeque-mate.\n"
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
/*

/*
int PRN_ChecarAmeacaReiBranco ( ) {
    char reiI; int reiJ;
    PEC_tppPeca rei, pecaAtual;
	PEC_tpJogador jogadorDaPecaAtual;
	CPC_tppClassePeca classeDaPecaAtual;

	char i;
	int j, movI, movJ, resposta, legalidade;
	
	// Primeiro, precisamos ter um rei válido
    rei = PRN_ObterReiBranco(&reiI, &reiJ);
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
            TAB_ObterValorDeCasa( simulacao.pTab, &pecaAtual, i, j );

            if( pecaAtual != NULL ) {
                PEC_ObterJogador( pecaAtual, &jogadorDaPecaAtual );

                if( jogadorDaPecaAtual == JOGADOR_PRETO) {
                    PEC_ObterClassePeca( pecaAtual, &classeDaPecaAtual );

                    if( classeDaPecaAtual == NULL ){
                        printf("Erro: peca com classe nula.");
                        PRN_Sair(1);
                    }

					movI = -(reiI - i);
					movJ = -(reiJ - j);

					CPC_ChecarMovimento(classeDaPecaAtual, movI, movJ, &resposta);

					if(resposta == 1){
						legalidade = PRN_ChecarLegalidade( jogadorDaPecaAtual, i, j, reiI, reiJ);
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

*/