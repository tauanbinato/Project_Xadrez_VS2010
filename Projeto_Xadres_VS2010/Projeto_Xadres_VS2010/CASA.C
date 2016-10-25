/***************************************************************************
*  $MCI Módulo de implementação: CAS Casa
*
*  Arquivo gerado:              CASA.c
*  Letras identificadoras:      CAS
*
*  Nome da base de software:    Arcabouço para a automaçãoo de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\CASA.BSW
*
*  Projeto: INF 1301 / 1628 Automatizacao dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       tb,ja,lp   20/out/2016 início desenvolvimento.
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   "lista.h"
#include   "Peca.h"


#define LISTA_OWN
#include "Casa.h"
#undef LISTA_OWN


/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor de uma estrutura casa
*
***********************************************************************/

typedef struct CAS_tagCasa {

	LIS_tppLista pListaAmeacantes;
	LIS_tppLista pListaAmeacados;
	PEC_tppPeca  pPeca;

} CAS_Casa;


/***********************************************************************
*
*  $TC Tipo de dados: CAS Cria Casa
*
***********************************************************************/

CAS_tpCondRet CAS_criaCasa(CAS_tppCasa *pCasa , void **pPeca) {

	(PEC_tppPeca  *)pPeca;
	CAS_Casa *aux_casa;
	aux_casa = (CAS_Casa *)malloc(sizeof(CAS_Casa));
	if (aux_casa == NULL) return CAS_CondRetFaltouMemoria;

	/*Faz devidas inicializacoes*/
	LIS_CriarLista(&aux_casa->pListaAmeacados, "Ameacados");
	LIS_CriarLista(&aux_casa->pListaAmeacantes, "Ameacantes");
	aux_casa->pPeca = *pPeca;

	*pCasa = aux_casa;

	return CAS_CondRetOK;
}

CAS_tpCondRet CAS_InserePecaEmCasa(CAS_tppCasa pCasa, void ** pPeca) {



}





