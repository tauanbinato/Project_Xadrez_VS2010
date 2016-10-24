﻿/***************************************************************************
*  $MCI Módulo de implementação: TAB Tabuleiro
*
*  Arquivo gerado:              TABULEIRO.c
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    Arcabouço para a automaçãoo de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\TABULEIRO.BSW
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

//Include de outros modulos
#include   "lista.h"
#include   "Casa.h"

#define LISTA_OWN
#include "Tabuleiro.h"
#undef LISTA_OWN


/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor da cabeca (ancora) da matriz
*
***********************************************************************/

typedef struct TAB_tagTabuleiro {

	LIS_tppLista pCabecaLista;
	/* Ponteiro para um ponteiro de uma cabeça da lista que representa o caminho das linhas */

	int num_de_linhas;
	/*Numero de linhas do tabuleiro(matriz)*/

	int num_de_colunas;
	/*Numero de colunas do tabuleiro(matriz)*/


} TAB_ancoraTabuleiro;


/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor da cabeca (ancora) de uma casa
*
***********************************************************************/

typedef struct TAB_tagAncoraCasa {

	CAS_tppCasa pCasaMatriz;
	/* Ponteiro para uma casa */

} TAB_ancoraCasa;


/***************************************************************************
*
*  Funcao: TAB  &Criar Tabuleiro
*
*  **************************************************************************/

TAB_tpCondRet TAB_CriaTabuleiro(TAB_ppAncoraTabuleiro *cabeca_TAB , int *lado_linhas , int *lado_colunas) {


	/* Declaracoes necessarias */
	int numDoCaminho, numColunas;
	LIS_tppLista  caminho_matriz;
	LIS_tppLista  colunas_matriz ;
	TAB_ppAncoraCasa *cabeca_casa;
	char idObtido[5];
	char idEnviado[5] = "Cami";

	//Auxiliares
	LIS_tppLista   aux_colunasMatriz;
	TAB_ancoraCasa *aux_cabecaCasa;
	TAB_ppAncoraTabuleiro aux_ancoraTAB;


	// - Alocando cabeça da Tabuleiro.
	aux_ancoraTAB = (TAB_ancoraTabuleiro *)malloc(sizeof(TAB_ancoraTabuleiro));
	if (aux_ancoraTAB == NULL) {
	
		return TAB_CondRetFaltouMemoria;
	}
	

	/*Criando a lista de caminho e testando*/
	
	LIS_CriarLista(&caminho_matriz, idEnviado);
	aux_ancoraTAB->pCabecaLista = caminho_matriz;
	LIS_ObterId(aux_ancoraTAB->pCabecaLista,idObtido );


	//Inicializando estrutura.
	aux_ancoraTAB->num_de_linhas = 0;
	aux_ancoraTAB->num_de_colunas = 0;
	
	
	//Cria 8 caminhos (linhas)
	for (aux_ancoraTAB->num_de_linhas = 0; aux_ancoraTAB->num_de_linhas < *lado_linhas ; aux_ancoraTAB->num_de_linhas++)
	{
	
		LIS_CriarLista(&colunas_matriz, "test");
		LIS_InserirNo(aux_ancoraTAB->pCabecaLista, colunas_matriz);
		
	
		//Cria 8 elementos para cada linha e aponta para uma casa
		for (aux_ancoraTAB->num_de_colunas = 0; aux_ancoraTAB->num_de_colunas < *lado_colunas ; aux_ancoraTAB->num_de_colunas++)
		{
			
			cabeca_casa = (TAB_ppAncoraCasa *)malloc(sizeof(TAB_ancoraCasa));
			if (cabeca_casa == NULL) {
				return TAB_CondRetFaltouMemoria;
			}
			
			aux_cabecaCasa = (TAB_ancoraCasa *)malloc(sizeof(TAB_ancoraCasa));
			if (aux_cabecaCasa == NULL) {
			
				return TAB_CondRetFaltouMemoria;
			}

			*cabeca_casa = aux_cabecaCasa;

			LIS_InserirNo(colunas_matriz, cabeca_casa);

			free(aux_cabecaCasa);
		}
		

	} /* endFor */


	*cabeca_TAB = aux_ancoraTAB;
	return TAB_CondRetOK;

}
/* Fim funcao: TAB  &Criar tabuleiro */



/***************************************************************************
*
*  Funcao: TAB &inserir Peca
*
*  *************************************************************************/
TAB_tpCondRet TAB_InserirPeca(TAB_ppAncoraTabuleiro cabeca_TAB, int cord_linha , int cord_coluna , void** peca_PEC)
{

	/*Declaracoes*/
	int corrente;
	char *nomePeca , *corPeca;
	LIS_tppLista aux_listaCaminho, aux_listaColuna;
	TAB_ppAncoraCasa aux_Ancora_De_Uma_Casa;


	/*Crio um ponteiro para a primeira lista que a cabeca aponta*/
	aux_listaCaminho = &cabeca_TAB->pCabecaLista;

	//Testa se esta OUT of RANGE
	if (cord_linha >= cabeca_TAB->num_de_linhas || cord_coluna >= cabeca_TAB->num_de_colunas || (cord_linha < 0 || cord_coluna < 0)) {
		return TAB_CondRetNaoAchou;
	}

	/*Anda atraves da cabeça ate encontrar a linha desejada*/
	LIS_IrInicioLista(cabeca_TAB->pCabecaLista);
	for(corrente = 0; corrente < cord_linha; corrente++) {
		if (corrente == cord_linha) {
			break;
		}
		LIS_AvancarElementoCorrente(cabeca_TAB->pCabecaLista);
	
	}/*fim for*/
	
	LIS_ObterNo(cabeca_TAB->pCabecaLista, (void**)&aux_listaColuna);
	

	/*Anda atraves dos elementos de uma linha ate encontrar a coluna desejada*/
	LIS_IrInicioLista(aux_listaColuna);
	for (corrente = 0; corrente < cord_coluna; corrente++) {
		if (corrente == cord_coluna) {
			break;
		}
		
		LIS_AvancarElementoCorrente(aux_listaColuna);
		//printf("avancou coluna\n");
	}

	LIS_ObterNo(aux_listaColuna, (void**)&aux_Ancora_De_Uma_Casa);
	
	aux_Ancora_De_Uma_Casa->pCasaMatriz->pPeca = peca_PEC;

	return TAB_CondRetOK;

}/*Fim funcao: TAB &Inserir Peça*/


/***************************************************************************
*
*  Funcao: TAB  &Mover Peca
*
*  **************************************************************************/
TAB_tpCondRet TAB_MoverPeca(TAB_ppAncoraTabuleiro cabeca_TAB, int xOrg, int yOrg, int xDest, int yDest, char corDest, char corOrg) 
{
	void *peca_origem, *peca_dest;

	if (cabeca_TAB == NULL) 
	{
		return TAB_CondRetTabVazio;
	}
	
	if ( xDest > 7 || xDest < 0|| yDest > 7 || yDest < 0 ) 
	{
		return TAB_CondRetNaoAchou;
	}
	if ( xOrg > 7 || xOrg < 0|| yOrg > 7 || yOrg < 0 ) 
	{
		return TAB_CondRetNaoAchou;
	}

	TAB_ObterPeca(cabeca_TAB, xOrg, yOrg, &peca_origem);
	TAB_ObterPeca(cabeca_TAB, xDest, yDest, &peca_dest);

	// TRAB 3: Conferir validade do movimento

	//
	if ( peca_origem == NULL )
	{
		return TAB_CondRetCasaVazia;
	}

	if ( peca_dest == NULL )
	{
		TAB_RetirarPeca(cabeca_TAB, xOrg, yOrg);
		TAB_InserirPeca(cabeca_TAB, xDest , yDest, &peca_origem);
		return TAB_CondRetOK;
	}

	if ( corOrg != corDest ) 
	{	
		TAB_RetirarPeca(cabeca_TAB, xOrg, yOrg);
		TAB_RetirarPeca(cabeca_TAB, xDest, yDest);
		TAB_InserirPeca(cabeca_TAB, xDest , yDest, &peca_origem);
		return TAB_CondRetComeu;
	}
	if ( corOrg == corDest )
	{
		return TAB_CondRetNaoPermitido;
	}

	return TAB_CondRetOK;
}/*Fim funcao: TAB &Mover Peca*/

/***************************************************************************
*
*  Funcao: TAB  &Retirar Peca
*
*  **************************************************************************/
TAB_tpCondRet TAB_RetirarPeca(TAB_ppAncoraTabuleiro cabeca_TAB, int cord_linha, int cord_coluna )
{
	/*Declaracoes*/
	int corrente;
	char *nomePeca, *corPeca;
	LIS_tppLista aux_listaCaminho, aux_listaColuna;
	TAB_ppAncoraCasa aux_Ancora_De_Uma_Casa;


	/*Crio um ponteiro para a primeira lista que a cabeca aponta*/
	aux_listaCaminho = &cabeca_TAB->pCabecaLista;

	//Testa se esta OUT of RANGE
	if (cord_linha >= cabeca_TAB->num_de_linhas || cord_coluna >= cabeca_TAB->num_de_colunas || (cord_linha < 0 || cord_coluna < 0)) {
		return TAB_CondRetNaoAchou;
	}

	/*Anda atraves da cabeça ate encontrar a linha desejada*/
	LIS_IrInicioLista(cabeca_TAB->pCabecaLista);
	for (corrente = 0; corrente < cord_linha; corrente++) {
		if (corrente == cord_linha) {
			break;
		}
		LIS_AvancarElementoCorrente(cabeca_TAB->pCabecaLista);
		
	}/*fim for*/

	LIS_ObterNo(cabeca_TAB->pCabecaLista, (void**)&aux_listaColuna);


	/*Anda atraves dos elementos de uma linha ate encontrar a coluna desejada*/
	LIS_IrInicioLista(aux_listaColuna);
	for (corrente = 0; corrente < cord_coluna; corrente++) {
		if (corrente == cord_coluna) {
			break;
		}

		LIS_AvancarElementoCorrente(aux_listaColuna);

	}

	LIS_ObterNo(aux_listaColuna, (void**)&aux_Ancora_De_Uma_Casa);

	aux_Ancora_De_Uma_Casa->pCasaMatriz->pPeca = NULL;

	return TAB_CondRetOK;
}/*Fim funcao: TAB &Retirar Peca*/


/***************************************************************************
*
*  Funcao: TAB  &Obter Peca
*
*  **************************************************************************/
TAB_tpCondRet TAB_ObterPeca(TAB_ppAncoraTabuleiro cabeca_TAB, int cord_linha, int cord_coluna, void** peca)
{
	int corrente;
	char nomePeca, corPeca;
	TAB_ppAncoraCasa aux_Ancora_De_Uma_Casa;

	/*Crio um ponteiro para a primeira lista que a cabeca aponta*/
	LIS_tppLista aux_listaCaminho, aux_listaColuna;
	
	/*Crio um ponteiro para a primeira lista que a cabeca aponta*/
	aux_listaCaminho = &cabeca_TAB->pCabecaLista;

	//Testa se esta OUT of RANGE
	if (cord_linha >= cabeca_TAB->num_de_linhas || cord_coluna >= cabeca_TAB->num_de_colunas || (cord_linha < 0 || cord_coluna < 0)) {
		return TAB_CondRetNaoAchou;
	}

	/*Anda atraves da cabeça ate encontrar a linha desejada*/
	LIS_IrInicioLista(cabeca_TAB->pCabecaLista);
	for (corrente = 0; corrente < cord_linha; corrente++) {
		if (corrente == cord_linha) {
			break;
		}
		LIS_AvancarElementoCorrente(cabeca_TAB->pCabecaLista);
	}/*fim for*/

	LIS_ObterNo(cabeca_TAB->pCabecaLista, (void**)&aux_listaColuna);


	/*Anda atraves dos elementos de uma linha ate encontrar a coluna desejada*/
	LIS_IrInicioLista(aux_listaColuna);
	for (corrente = 0; corrente < cord_coluna; corrente++) {
		if (corrente == cord_coluna) {
			break;
		}

		LIS_AvancarElementoCorrente(aux_listaColuna);
	}

	LIS_ObterNo(aux_listaColuna, (void**)&aux_Ancora_De_Uma_Casa);
	
	*peca = aux_Ancora_De_Uma_Casa->pCasaMatriz->pPeca;
	
	return TAB_CondRetOK;
}/*Fim funcao: &TAB obter Peca*/


/***************************************************************************
*
*  Funcao: TAB  &Obter Lista Ameacantes
*
*  **************************************************************************/
TAB_tpCondRet TAB_ObterListaAmeacantes(TAB_ppAncoraTabuleiro cabeca_TAB, int linha, int coluna, LIS_tppLista * pListaAmeacantes )
{
	int corrente;
	char nomePeca, corPeca;
	TAB_ppAncoraCasa aux_Casa;
	

	/*Crio um ponteiro para a primeira lista que a cabeca aponta*/
	LIS_tppLista aux_listaCaminho, aux_listaColuna;

	aux_listaCaminho = cabeca_TAB->pCabecaLista;

	/*Coloco o pElemCorrente no inicio da lista que iremos caminhar*/
	LIS_IrInicioLista(aux_listaCaminho);

	//Testa se esta OUT of RANGE
	if (linha >= cabeca_TAB->num_de_linhas || coluna >= cabeca_TAB->num_de_colunas || linha < 0 || coluna < 0) {
		return TAB_CondRetNaoAchou;
	}

	/*Anda atraves da cabeça ate encontrar a linha desejada*/
	for (corrente = 0; corrente < linha; corrente++) {
		if (corrente == linha) {
			break;
		}
		LIS_AvancarElementoCorrente(aux_listaCaminho);
	}
	LIS_ObterNo(aux_listaCaminho, (void**)&aux_listaColuna);



	/*Anda atraves dos elementos de uma linha ate encontrar a coluna desejada*/
	LIS_IrInicioLista(aux_listaColuna);
	for (corrente = 0; corrente < coluna; corrente++) {
		if (corrente == coluna) {
			break;
		}
		LIS_AvancarElementoCorrente(aux_listaColuna);
		
	}
	
	LIS_ObterNo(aux_listaColuna, (void**)&aux_Casa);
	
	LIS_ObterNo(aux_Casa->pCasaMatriz->pListaAmeacantes,(void**)&pListaAmeacantes);
	
	
	return TAB_CondRetOK;
}
/*Fim funcao: &TAB obter Lista Ameacantes*/

/***************************************************************************
*
*  Funcao: TAB  &Obter Lista Ameacados
*
*  **************************************************************************/
TAB_tpCondRet TAB_ObterListaAmeacados(TAB_ppAncoraTabuleiro cabeca_TAB, int linha, int coluna, LIS_tppLista * pListaAmeacados )
{
	int corrente;
	char nomePeca, corPeca;
	TAB_ppAncoraCasa aux_Casa;
	

	/*Crio um ponteiro para a primeira lista que a cabeca aponta*/
	LIS_tppLista aux_listaCaminho, aux_listaColuna;

	aux_listaCaminho = cabeca_TAB->pCabecaLista;

	/*Coloco o pElemCorrente no inicio da lista que iremos caminhar*/
	LIS_IrInicioLista(aux_listaCaminho);

	//Testa se esta OUT of RANGE
	if (linha >= cabeca_TAB->num_de_linhas || coluna >= cabeca_TAB->num_de_colunas || linha < 0 || coluna < 0) {
		return TAB_CondRetNaoAchou;
	}

	/*Anda atraves da cabeça ate encontrar a linha desejada*/
	for (corrente = 0; corrente < linha; corrente++) {
		if (corrente == linha) {
			break;
		}
		LIS_AvancarElementoCorrente(aux_listaCaminho);
	}

	LIS_ObterNo(aux_listaCaminho, (void**)&aux_listaColuna);
	LIS_IrInicioLista(aux_listaColuna);


	/*Anda atraves dos elementos de uma linha ate encontrar a coluna desejada*/
	for (corrente = 0; corrente < coluna; corrente++) {
		if (corrente == coluna) {
			break;
		}
		LIS_AvancarElementoCorrente(aux_listaColuna);
	}

	LIS_ObterNo(aux_listaColuna, (void**)&aux_Casa);
	LIS_ObterNo(aux_Casa->pCasaMatriz->pListaAmeacados, (void**)&pListaAmeacados);

	return TAB_CondRetOK;
}
/*Fim funcao: &TAB obter Lista Ameacados*/

/***************************************************************************
*
*  Funcao: TAB  &Destruir Tabuleiro
*
*  **************************************************************************/
TAB_tpCondRet TAB_DestruirTabuleiro(TAB_ppAncoraTabuleiro cabeca_TAB){

	int numLinhas, numColunas;
	LIS_tppLista listaColunas, aux, *listaAmeacantes,*listaAmeacados;
	TAB_ppAncoraCasa aux_Casa;


	LIS_IrInicioLista(cabeca_TAB->pCabecaLista);
	
	for(numLinhas = 0; numLinhas < cabeca_TAB->num_de_linhas; numLinhas++)
	{
		LIS_ObterNo(cabeca_TAB->pCabecaLista, (void**)&listaColunas);
		
		for ( numColunas = 0; numColunas < cabeca_TAB->num_de_colunas; numColunas++){
			TAB_RetirarPeca(cabeca_TAB, numLinhas, numColunas);
		}

		LIS_EsvaziarLista(listaColunas);
	}
		
	LIS_DestroiLista(cabeca_TAB->pCabecaLista);
	free(cabeca_TAB);

	return TAB_CondRetOK;
}
/*Fim funcao: &TAB Destruir Tabuleiro*/

