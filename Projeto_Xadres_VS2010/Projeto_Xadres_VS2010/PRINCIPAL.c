#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

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


	//LIS_CriarLista(simulacao.pListaClasses, "Classes");
	PRI_Inicializa();
	PRI_CarregarArquivoMovimento("./MOVIMENTOS.txt");

	

	return 0;




}

int PRI_CarregarArquivoMovimento(char* path) {

	char auxString[200], classe;
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
			if (CPC_AdicionarMovimento(pClasse, i, j) == CPC_CondRetFaltouMemoria) {
				printf("Faltou memória.");
				exit(1);
			}

		}
	}

	fclose(fp);
	return 1;
}

void PRI_Inicializa(void) {
	int* linha = 8;
	int* coluna = 8;

	if (TAB_CriaTabuleiro(&simulacao.pTab, &linha, &coluna) != TAB_CondRetOK) {
		printf("ERRO DE MEMORIA AO CRIAR TABULEIRO");
		exit(1);
	}

	
	if (LIS_CriarLista(&simulacao.pListaClasses, "Classes") != 0) {
		TAB_DestruirTabuleiro(&simulacao.pTab);
		printf("ERRO DE MEMORIA AO CRIAR LISTA DE CLASSES");
		exit(1);
	}

	if (LIS_CriarLista(&simulacao.pListaPecas, "Pecas") != 0) {
		TAB_DestruirTabuleiro(&simulacao.pTab);
		LIS_DestroiLista(&simulacao.pListaClasses);
		printf("ERRO DE MEMORIA AO CRIAR LISTA DE PECAS");
		exit(1);
	}
}
