#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   "lista.h"
#include   "Peca.h"
#include   "CASA.H"

int PRI_CarregarArquivoMovimento(char* path) {

	char auxString[200], jogador;
	int i, j;
	FILE *fp;
	CPC_tppClassePeca pClasse;
	PEC_tppPeca pPeca;

	fp = fopen(path, "r");
	if (!fp) {
		printf("Path invalido.\n\n");
		return 0;
	}

	while (fscanf(fp, " %s", auxString) == 1) {
		if (strcmp(auxString, "CLASSE") == 0) {
			fscanf(fp, " %[^\n]", auxString);
			if (CPC_CriarClassePeca(&pClasse, auxString) != CPC_CondRetOK) {
				printf("Faltou memória.");
				PRN_Sair(1);
			}
			LIS_InserirElementoApos(simulacao.pListaClasses, (void *)pClasse);

		}
		else if (strcmp(auxString, "MOV") == 0) {
			fscanf(fp, " %d %d", &i, &j);
			if (CPC_AdicionarMovimento(pClasse, i, j) == CPC_CondRetFaltouMemoria) {
				printf("Faltou memória.");
				PRN_Sair(1);
			}

		}
	}

	fclose(fp);
	return 1;
}

