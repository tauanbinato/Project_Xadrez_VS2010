/***************************************************************************
*  $MCI M�dulo de implementa��o: PEC Peca
*
*  Arquivo gerado:              PECA.c
*  Letras identificadoras:      PEC
*
*  Nome da base de software:    Arcabou�o para a automa��oo de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\PECA.BSW
*
*  Projeto: INF 1301 / 1628 Automatizacao dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       tb,ja,lp   26/set/2016 in�cio desenvolvimento.
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#include "CLASSE_PECA.H"


#define LISTA_OWN
#include "Peca.h"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: PEC Descritor de uma estrutura Peca
*
***********************************************************************/

typedef struct PEC_tagPeca {

	CPC_tppClassePeca ClassePeca;
	/* Nome da peca especifica*/

	char cor_peca;
	/* Cor da peca especifica*/

} PEC_Peca;


/***********************************************************************
*
*  $TC Tipo de dados: PEC Cria peca
*
***********************************************************************/

PEC_tpCondRet PEC_criaPeca(PEC_tppPeca *peca, CPC_tppClassePeca ClassePeca, char cor_peca) {

	PEC_Peca *aux_peca;

	aux_peca = (PEC_Peca *)malloc(sizeof(PEC_Peca));
	if (aux_peca == NULL) return PEC_CondRetFaltouMemoria;

	aux_peca->cor_peca = cor_peca;
	aux_peca->ClassePeca = ClassePeca;

	*peca = aux_peca;
	
	return PEC_CondRetOK;
}

/***********************************************************************
*
*  $TC Tipo de dados: PEC Insere Valor Em Peca
*
***********************************************************************/

PEC_tpCondRet PEC_InserirClassePeca(PEC_tppPeca peca , CPC_tppClassePeca ClassePeca) {
	if (peca == NULL || ClassePeca == NULL) {
		return PEC_CondRetPonteiroNulo;
	}

	peca->ClassePeca = ClassePeca;

	return PEC_CondRetOK;
}

/***********************************************************************
*
*  $TC Tipo de dados: PEC Obtem Classe de Peca
*
***********************************************************************/

PEC_tpCondRet PEC_ObterClasseDePeca(PEC_tppPeca peca, CPC_tppClassePeca *ClassePeca) {
	if (peca == NULL) return PEC_CondRetPonteiroNulo;

	*ClassePeca = peca->ClassePeca;

	return PEC_CondRetOK;
}

/***********************************************************************
*
*  $TC Tipo de dados: PEC Destroi Peca
*
***********************************************************************/

PEC_tpCondRet PEC_DestroiPeca(PEC_tppPeca peca) {
	
	if (peca == NULL)
		return PEC_CondRetPonteiroNulo;

	free(peca);

	return PEC_CondRetOK;
}

/***********************************************************************
*
*  $FC Fun��o: PEC &Obter jogador ao qual pertence a pe�a
*
***********************************************************************/

PEC_tpCondRet PEC_ObterCorDePeca(PEC_tppPeca pPeca, char * cor_peca) {
	if (pPeca == NULL) {
		return PEC_CondRetPonteiroNulo;
	}

	*cor_peca = pPeca->cor_peca;

	return PEC_CondRetOK;
}
