/***************************************************************************
*  $MCI Módulo de implementação: CPC Classe_Peca
*
*  Arquivo gerado:              CLASSE_PECA.c
*  Letras identificadoras:      CPC
*
*  Nome da base de software:    Arcabouço para a automaçãoo de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\CLASE_PECA.BSW
*
*  Projeto: INF 1301 / 1628 Automatizacao dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       tb,ja,lp   31/out/2016 início desenvolvimento.
*
***************************************************************************/

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

/***********************************************************************
*  $FC Função: CPC Criar classe de peça
***********************************************************************/

CPC_tpCondRet CPC_CriarClassePeca(CPC_tppClassePeca * ppClassePeca, char nome, char* idEnviado) {

	CPC_tpClassePeca * cp;
	cp = (CPC_tppClassePeca)malloc(sizeof(CPC_tpClassePeca));

	if (cp == NULL) {
		return CPC_CondRetFaltouMemoria;
	}

	cp->nome = nome;

	LIS_CriarLista(&cp->movimentos, idEnviado);

	if (cp->movimentos == NULL) {
		//free(cp->nome);
		free(cp);
		return CPC_CondRetFaltouMemoria;
	}

	*ppClassePeca = cp;

	return CPC_CondRetOK;
}

/***********************************************************************
*  $FC Função: CPC Destruir classe de peça
***********************************************************************/

CPC_tpCondRet CPC_DestruirClassePeca(CPC_tppClassePeca pClassePeca) {

	if (pClassePeca == NULL) {
		return CPC_CondRetPonteiroNulo;
	}

	LIS_DestroiLista(pClassePeca->movimentos);

	free(pClassePeca);

	return CPC_CondRetOK;
}

/***********************************************************************
*  $FC Função: CPC Adicionar movimento a classe de peça
***********************************************************************/

CPC_tpCondRet CPC_AdicionarMovimento(CPC_tppClassePeca pClassePeca, int movI, int movJ) {

	CPC_tpMovimento * movimento;

	int resp = 0, numMovimentos, a;

	if (pClassePeca == NULL) {
		return CPC_CondRetPonteiroNulo;
	}
	
	CPC_ChecarMovimento(pClassePeca, movI, movJ, &resp);

	if (resp == 1) {
		return CPC_CondRetNaoAchou;
	}

	movimento = (CPC_tpMovimento*)malloc(sizeof(CPC_tpMovimento));

	if (movimento == NULL) {
		return CPC_CondRetFaltouMemoria;
	}

	movimento->movI = movI;
	movimento->movJ = movJ;

	LIS_IrFinalLista(&pClassePeca->movimentos);
	if( LIS_InserirNo(&pClassePeca->movimentos, movimento) == LIS_CondRetFaltouMemoria) {
		 return CPC_CondRetFaltouMemoria;
	}

	//CPC_ObterNumeroMovimentos(pClassePeca, &numMovimentos);

	return CPC_CondRetOK;
}

/***********************************************************************
*  $FC Função: CPC Checar movimento de classe de peça
***********************************************************************/

CPC_tpCondRet CPC_ChecarMovimento(CPC_tppClassePeca pClassePeca, int movI, int movJ, int * resposta) {

	int numMovimentos;
	int i = 0;
	int movIObtido, movJObtido;

	if (pClassePeca == NULL) {
		return CPC_CondRetPonteiroNulo;
	}

	if (movI > 7 || movJ > 7 || movI < -7 || movJ < -7) {
		*resposta = 0;
		return CPC_CondRetNaoAchou;
	}

	CPC_ObterNumeroMovimentos(pClassePeca, &numMovimentos);

	for (i = 0; i < numMovimentos; i++) {
		CPC_ObterMovimento(pClassePeca, i, &movIObtido, &movJObtido);

		if (movIObtido == movI && movJObtido == movJ) {
			*resposta = 1;
			return CPC_CondRetOK;
		}
	}

	return CPC_CondRetOK;
}

/***********************************************************************
*  $FC Função: CPC Obter número de movimentos de classe de peça
***********************************************************************/

CPC_tpCondRet CPC_ObterNumeroMovimentos(CPC_tppClassePeca pClassePeca, int * numMovimentos) {

	if (pClassePeca == NULL) {
		return CPC_CondRetPonteiroNulo;
	}

	*numMovimentos = LIS_ObterNumElem(pClassePeca->movimentos);
	if (*numMovimentos == -1) {
		return CPC_CondRetNaoAchou;
	}

	printf("\n *numMovimentos: %d", *numMovimentos);
	return CPC_CondRetOK;
}

/***********************************************************************
*  $FC Função: CPC Obter movimento de classe de peça
***********************************************************************/

CPC_tpCondRet CPC_ObterMovimento(CPC_tppClassePeca pClassePeca, int idxMovimento, int * pMovI, int * pMovJ) {
	int numElem;
	CPC_tpMovimento *movimento;

	if (pClassePeca == NULL) {
		return CPC_CondRetPonteiroNulo;
	}

	CPC_ObterNumeroMovimentos(pClassePeca, &numElem);

	if (idxMovimento < 0 || idxMovimento > numElem) {
		return CPC_CondRetNaoAchou;
	}

	LIS_IrInicioLista(pClassePeca->movimentos);

	LIS_AvancarElementoCorrente(&pClassePeca->movimentos, numElem);

	LIS_ObterNo(&pClassePeca->movimentos, (void**)&movimento);

	*pMovI = movimento->movI;
	*pMovJ = movimento->movJ;

	return CPC_CondRetOK;
}

/***********************************************************************
*  $FC Função: CPC Obter nome de classe de peça
***********************************************************************/

CPC_tpCondRet CPC_ObterNome(CPC_tppClassePeca pClassePeca, char * pNome) {
	if (pClassePeca == NULL) {
		return CPC_CondRetPonteiroNulo;
	}

	*pNome = pClassePeca->nome;

	return CPC_CondRetOK;
}


/***** Código das funções encapuladas no módulo *****/

/***********************************************************************
*
*  $FC Função: Destruir Movimento
*
*  $ED Descrição da função
*     Encapsula a função de destruição de um movimento.
*     Função para ser passada à lista genérica, que será usada para
*       armazenar movimentos.
*
***********************************************************************/

static void DestruirMovimento(void * pMovimento) {
	free(pMovimento);
}

/********** Fim do módulo de implementação: Módulo classe de peça de xadrez **********/