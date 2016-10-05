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


} PEC_Peca;

PEC_tpCondRet PEC_criaPeca(PEC_tppPeca *peca , char nome_peca , char cor_peca) {

	PEC_Peca *aux_peca;
	aux_peca = (PEC_Peca *)malloc(sizeof(PEC_Peca));
	if (aux_peca == NULL) return PEC_CondRetFaltouMemoria;

	aux_peca->nome_peca = nome_peca;
	aux_peca->cor_peca = cor_peca;
	
	*peca = aux_peca;
	
	return PEC_CondRetOK;
}

PEC_tpCondRet PEC_insereNomeDePeca(PEC_tppPeca peca , char nome_peca) {

	peca->nome_peca= nome_peca;
	return PEC_CondRetOK;
}

PEC_tpCondRet PEC_insereCorDePeca(PEC_tppPeca peca, char cor_peca) {


	peca->cor_peca = cor_peca;
	return PEC_CondRetOK;
}

PEC_tpCondRet PEC_obtemNomeDePeca(PEC_tppPeca peca, char *nome_peca) {

	char aux;
	aux = (char )malloc(1 + sizeof(char));
	if (aux == NULL) return PEC_CondRetFaltouMemoria;
	
	aux = peca->nome_peca;
	*nome_peca= aux;

	return PEC_CondRetOK;
}

PEC_tpCondRet PEC_obtemCorDePeca(PEC_tppPeca peca, char *cor_peca) {

	char aux;
	aux = (char )malloc(1 + sizeof(char));
	if (aux == NULL) return PEC_CondRetFaltouMemoria;
	
	aux = peca->cor_peca;
	*cor_peca = aux;
	

	return PEC_CondRetOK;
}

PEC_tpCondRet PEC_EsvaziaPeca(PEC_tppPeca peca) {
	
	if (peca == NULL)
		return PEC_CondRetNaoAchou;

	peca->cor_peca  = 'V' ;
	peca->nome_peca = 'V' ;

	return PEC_CondRetOK;

}

PEC_tpCondRet PEC_DestroiPeca(PEC_tppPeca peca) {
	
	if (peca == NULL)
		return PEC_CondRetNaoAchou;
	
	printf("\nda free");
	
	free(peca);

	printf("\nallal");
	
	return PEC_CondRetOK;
}