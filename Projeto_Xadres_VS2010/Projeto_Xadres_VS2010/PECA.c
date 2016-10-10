/***************************************************************************
*  $MCI Módulo de implementação: PEC Peca
*
*  Arquivo gerado:              PECA.c
*  Letras identificadoras:      PEC
*
*  Nome da base de software:    Arcabouço para a automaçãoo de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\PECA.BSW
*
*  Projeto: INF 1301 / 1628 Automatizacao dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       tb,ja,lp   26/set/2016 início desenvolvimento.
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   "lista.h"


#define LISTA_OWN
#include "Peca.h"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: PEC Descritor de uma estrutura Peca
*
***********************************************************************/

typedef struct PEC_tagPeca {

	char nome_peca;
	/* Nome da peca especifica*/

	char cor_peca;
	/* Cor da peca especifica*/
	char *movimento;

} PEC_Peca;


/***********************************************************************
*
*  $TC Tipo de dados: PEC Cria peca
*
***********************************************************************/

PEC_tpCondRet PEC_criaPeca(PEC_tppPeca *peca) {

	PEC_Peca *aux_peca;
	aux_peca = (PEC_Peca *)malloc(sizeof(PEC_Peca));
	if (aux_peca == NULL) return PEC_CondRetFaltouMemoria;

	aux_peca->cor_peca = 'V';
	aux_peca->nome_peca = 'V';

	*peca = aux_peca;
	
	return PEC_CondRetOK;
}

/***********************************************************************
*
*  $TC Tipo de dados: PEC Insere Valor Em Peca
*
***********************************************************************/

PEC_tpCondRet PEC_insereValorEmPeca(PEC_tppPeca peca , char *nome_peca , char *cor_peca) {

	/*Aloca nome*/
	char* aux_nome;
	char* aux_cor;

	aux_nome = (char *)malloc(sizeof(char));
	if (aux_nome == NULL) return PEC_CondRetFaltouMemoria;

	aux_nome = nome_peca;

	/*Aloca cor*/
	aux_cor = (char *)malloc(sizeof(char));
	if (aux_cor == NULL) return PEC_CondRetFaltouMemoria;

	aux_cor = cor_peca;


	peca->cor_peca = *aux_cor;
	peca->nome_peca = *aux_nome;
	
	return PEC_CondRetOK;
}

/***********************************************************************
*
*  $TC Tipo de dados: PEC Obtem Valor de Peca
*
***********************************************************************/

PEC_tpCondRet PEC_obtemValoresdePeca(PEC_tppPeca peca, char *nome_peca , char *cor_peca) {

	*nome_peca = peca->nome_peca;
	*cor_peca = peca->cor_peca;
	
	return PEC_CondRetOK;
}

/***********************************************************************
*
*  $TC Tipo de dados: PEC Esvazia peca
*
***********************************************************************/

PEC_tpCondRet PEC_EsvaziaPeca(PEC_tppPeca peca) {
	
	if (peca == NULL)
		return PEC_CondRetNaoAchou;

	peca->cor_peca  = 'V' ;
	peca->nome_peca = 'V' ;

	return PEC_CondRetOK;

}

/***********************************************************************
*
*  $TC Tipo de dados: PEC Destroi Peca
*
***********************************************************************/

PEC_tpCondRet PEC_DestroiPeca(PEC_tppPeca peca) {
	
	if (peca == NULL)
		return PEC_CondRetNaoAchou;
	
	printf("\nda free");
	
	free(peca);

	printf("\nallal");
	
	return PEC_CondRetOK;
}