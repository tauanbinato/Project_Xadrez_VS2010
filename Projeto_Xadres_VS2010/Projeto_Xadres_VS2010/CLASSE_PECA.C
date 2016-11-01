#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   "lista.h"
#include   "CLASSE_PECA.H"


typedef struct CPC_tagClassePeca {

	char  nome;

	LIS_tppLista movimentos;

} CPC_tpClassePeca;


typedef struct CPC_tagMovimento {

	int movI;

	int movJ;

} CPC_tpMovimento;

CPC_tpCondRet CPC_CriarClassePeca(CPC_tppClassePeca * ppClassePeca, char nome, char* idEnviado) {
	CPC_tpClassePeca * cp;

	cp = (CPC_tppClassePeca)malloc(sizeof(CPC_tpClassePeca));

	if (cp == NULL) {
		return CPC_CondRetFaltouMemoria;
	}

	cp->nome = (char)malloc(sizeof(char));

	if (cp->nome == NULL) {
		free(cp);
		return CPC_CondRetFaltouMemoria;
	}

	cp->nome = nome;

	LIS_CriarLista(&cp->movimentos, idEnviado);

	if (cp->movimentos == NULL) {
		free(cp->nome);
		free(cp);
		return CPC_CondRetFaltouMemoria;
	}

	*ppClassePeca = cp;

	return CPC_CondRetOK;
}