/***************************************************************************
*  $MCI M�dulo de implementa��o: CPC Classe_Peca
*
*  Arquivo gerado:              CLASSE_PECA.c
*  Letras identificadoras:      CPC
*
*  Nome da base de software:    Arcabou�o para a automa��oo de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\CLASE_PECA.BSW
*
*  Projeto: INF 1301 / 1628 Automatizacao dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       tb,ja,lp   31/out/2016 in�cio desenvolvimento.
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
*  $FC Fun��o: CPC Criar classe de pe�a
***********************************************************************/

CPC_tpCondRet CPC_CriarClassePeca(CPC_tppClassePeca * ppClassePeca, char nome, char* idEnviado) {

	CPC_tpClassePeca * cp;
	cp = (CPC_tppClassePeca)malloc(sizeof(CPC_tpClassePeca));

	if (cp == NULL) {
		return CPC_CondRetFaltouMemoria;
	}

	cp->nome = nome;
	LIS_CriarLista(&(cp->movimentos), idEnviado);

	if (cp->movimentos == NULL) {
		free(cp);
		return CPC_CondRetFaltouMemoria;
	}

	*ppClassePeca = cp;

	return CPC_CondRetOK;
}

/***********************************************************************
*  $FC Fun��o: CPC Destruir classe de pe�a
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
*  $FC Fun��o: CPC Adicionar movimento a classe de pe�a
***********************************************************************/

CPC_tpCondRet CPC_AdicionarMovimento(CPC_tppClassePeca pClassePeca, int movI, int movJ) {

	CPC_tpMovimento * movimento;

	int resp = 0, numMovimentos;

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

	LIS_IrFinalLista(pClassePeca->movimentos);
	if( LIS_InserirNo(pClassePeca->movimentos, (CPC_tpMovimento*)movimento) == LIS_CondRetFaltouMemoria) {
		 return CPC_CondRetFaltouMemoria;
	}

	CPC_ObterNumeroMovimentos(pClassePeca, &numMovimentos);

	return CPC_CondRetOK;
}

/***********************************************************************
*  $FC Fun��o: CPC Checar movimento de classe de pe�a
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
*  $FC Fun��o: CPC Obter n�mero de movimentos de classe de pe�a
*
***********************************************************************/

CPC_tpCondRet CPC_ObterNumeroMovimentos(CPC_tppClassePeca pClassePeca, int * numMovimentos) {

	if (pClassePeca == NULL) {
		return CPC_CondRetPonteiroNulo;
	}

	LIS_ObterNumElementos(pClassePeca->movimentos, numMovimentos);

	return CPC_CondRetOK;
}

/***********************************************************************
*  $FC Fun��o: CPC Obter movimento de classe de pe�a  
***********************************************************************/

CPC_tpCondRet CPC_ObterMovimento(CPC_tppClassePeca pClassePeca, int idxMovimento, int * pMovI, int * pMovJ) {
	int numElem;
	CPC_tpMovimento **movimento;

	movimento = (CPC_tpMovimento**)malloc(sizeof(CPC_tpMovimento));
	if (movimento == NULL) {
		return CPC_CondRetFaltouMemoria;
	}

	if (pClassePeca == NULL) {
		return CPC_CondRetPonteiroNulo;
	}
		
	CPC_ObterNumeroMovimentos(pClassePeca, &numElem);
		

	if (idxMovimento < 0 || idxMovimento > numElem) 
	{

		return CPC_CondRetNaoAchou;
	}

	LIS_IrInicioLista(pClassePeca->movimentos);

	LIS_AvancarElementoCorrente(pClassePeca->movimentos, idxMovimento);

	LIS_ObterNo(pClassePeca->movimentos, (CPC_tpMovimento**)movimento);

	*pMovI = (*movimento)->movI;

	*pMovJ = (*movimento)->movJ;

	return CPC_CondRetOK;

}

/***********************************************************************
*  $FC Fun��o: CPC Obter nome de classe de pe�a
***********************************************************************/

CPC_tpCondRet CPC_ObterNome(CPC_tppClassePeca pClassePeca, char * pNome) {
	if (pClassePeca == NULL) {
		return CPC_CondRetPonteiroNulo;
	}

	*pNome = pClassePeca->nome;

	return CPC_CondRetOK;
}


/***** C�digo das fun��es encapuladas no m�dulo *****/

/***********************************************************************
*
*  $FC Fun��o: Destruir Movimento
*
*  $ED Descri��o da fun��o
*     Encapsula a fun��o de destrui��o de um movimento.
*     Fun��o para ser passada � lista gen�rica, que ser� usada para
*       armazenar movimentos.
*
***********************************************************************/

static void DestruirMovimento(void * pMovimento) {
	free(pMovimento);
}

/********** Fim do m�dulo de implementa��o: M�dulo classe de pe�a de xadrez **********/