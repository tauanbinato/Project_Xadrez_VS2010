/***************************************************************************
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
*  $TC Tipo de dados: TAB Descritor de uma estrutura casa
*
***********************************************************************/

typedef struct TAB_tagCasa {

	LIS_tppLista pListaAmeacantes;
	LIS_tppLista pListaAmeacados;
	void* pPeca;

} TAB_casaMatriz;


/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor da cabeca (ancora) de uma casa
*
***********************************************************************/

typedef struct TAB_tagAncoraCasa {

	TAB_casaMatriz * pCasaMatriz;
	/* Ponteiro para uma casa */

} TAB_ancoraCasa;



/***************************************************************************
*
*  Funcao: TAB  &Criar Tabuleiro
*
*  **************************************************************************/

TAB_tpCondRet TAB_CriaTabuleiro(TAB_ppAncoraTabuleiro *cabeca_TAB , int *lado_linhas , int *lado_colunas) {


	/*SCRIPT PARA TESTA_LA : =criartabuleiro tabuleiro0	 lado_linhas	lado_colunas	OK  */


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
	printf("\nId enviado: %s\n" , idEnviado);
	LIS_CriarLista(&caminho_matriz, idEnviado);
	aux_ancoraTAB->pCabecaLista = caminho_matriz;
	LIS_ObterId(aux_ancoraTAB->pCabecaLista,idObtido );
	printf("Id obtido: %s\n" , idObtido);

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


			printf("(%d,%d) - (%p,%p)\n", aux_ancoraTAB->num_de_linhas, aux_ancoraTAB->num_de_colunas , colunas_matriz , cabeca_casa);
			free(aux_cabecaCasa);
		}
		

	} /* endFor */


	*cabeca_TAB = aux_ancoraTAB;
	return TAB_CondRetOK;

}
/* Fim funcao: TAB  &Criar tabuleiro */


// AREA DO TAUAN------------------
/***************************************************************************
**
*  Funcao: TAB &inserir Peça
*Função InserirPeca – Receberá a coordenada linha-coluna, o identificador da peça a ser inserida e a sua cor. 
*Crie os retornos necessários inclusive prevendo a colocação da peça em uma coordenada inexistente
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
	if (cord_linha >= cabeca_TAB->num_de_linhas || cord_coluna >= cabeca_TAB->num_de_colunas || cord_linha < 0 || cord_coluna < 0) {
		return TAB_CondRetNaoAchou;
	}

	/*Anda atraves da cabeça ate encontrar a linha desejada*/
	LIS_IrInicioLista(cabeca_TAB->pCabecaLista);

	for(corrente = 0; corrente < cord_linha; corrente++) {
		if (corrente == cord_linha) {
			break;
		}
		LIS_AvancarElementoCorrente(cabeca_TAB->pCabecaLista);
		//printf("avancou linha\n");
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
TAB_tpCondRet TAB_MoverPeca(TAB_ppAncoraTabuleiro cabeca_TAB, int xOrg, int yOrg, int xDest, int yDest) 
{
	char *id_cor_dest, *id_cor_origem;
	void *peca_origem, *peca_dest;

	if (cabeca_TAB == NULL) {
		return TAB_CondRetListaVazia;
	}
	
	if (xDest > 7 || xDest < 0|| yDest> 0 || yDest < 7) {
		return TAB_CondRetFimLista;
	}

	TAB_ObterPeca(cabeca_TAB, xDest, yDest, id_cor_origem, &peca_origem);
	TAB_ObterPeca(cabeca_TAB, xDest, yDest, id_cor_dest, &peca_dest);

	// TRAB 3: Conferir validade do movimento

	// 
	if (peca_dest == NULL) {

	}

	if (id_cor_origem != id_cor_dest) {
		TAB_InserirPeca(cabeca_TAB, xDest , yDest, &peca_origem);
		TAB_RetirarPeca(cabeca_TAB, xDest, yDest);
		return TAB_CondRetOK;
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
	int corrente ;
	LIS_tppLista auxCabecaColuna  ;
	TAB_ppAncoraCasa  auxCabecaCasa ;

	//Testa se esta OUT of RANGE
	if (cord_linha >= cabeca_TAB->num_de_linhas || cord_coluna >= cabeca_TAB->num_de_colunas  || cord_linha < 0 || cord_coluna < 0) {
		printf("out of range\n");
		return TAB_CondRetNaoAchou;
	}

	//Volta o elemento corrente até o 1º elemento
	LIS_IrInicioLista(cabeca_TAB->pCabecaLista);

	//Busca a linha certa
	for (corrente = 1; corrente < cord_linha; corrente++) {
		if (corrente == cord_linha)
			break;
			LIS_AvancarElementoCorrente(cabeca_TAB->pCabecaLista);
	}
	LIS_ObterNo(cabeca_TAB->pCabecaLista, (void**)&auxCabecaColuna) ;
	LIS_IrInicioLista(auxCabecaColuna);

	//Busca coluna certa
	for(corrente = 1; corrente < cord_coluna; corrente++){
		if (corrente == cord_coluna)
			break;
		LIS_AvancarElementoCorrente(auxCabecaColuna);
	}
	LIS_ObterNo(auxCabecaColuna, (void**)&auxCabecaCasa);

	if(auxCabecaCasa->pCasaMatriz->pPeca == (void*)'V' )
	{
		TAB_CondRetNaoAchou;
	}
	auxCabecaCasa->pCasaMatriz->pPeca = (void*)'V'; 
	return TAB_CondRetOK;
}/*Fim funcao: TAB &Retirar Peca*/


/***************************************************************************
*
*  Funcao: TAB  &Obter Peca
*
*  **************************************************************************/
TAB_tpCondRet TAB_ObterPeca(TAB_ppAncoraTabuleiro cabeca_TAB, int cord_linha, int cord_coluna, char *id_cor, void** peca)
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
	if (cord_linha >= cabeca_TAB->num_de_linhas || cord_coluna >= cabeca_TAB->num_de_colunas || cord_linha < 0 || cord_coluna < 0) {
		return TAB_CondRetNaoAchou;
	}

	/*Anda atraves da cabeça ate encontrar a linha desejada*/
	for (corrente = 1; corrente == cord_linha; corrente++) {
		if (corrente == cord_linha) {
			break;
		}
		LIS_AvancarElementoCorrente(aux_listaCaminho);
	}

	LIS_ObterNo(aux_listaCaminho, (void**)&aux_listaColuna);
	LIS_IrInicioLista(aux_listaColuna);


	/*Anda atraves dos elementos de uma linha ate encontrar a coluna desejada*/
	for (corrente = 1; corrente == cord_coluna; corrente++) {
		if (corrente == cord_coluna) {
			break;
		}
		LIS_AvancarElementoCorrente(aux_listaColuna);
	}

	LIS_ObterNo(aux_listaColuna, (void**)&aux_Casa);
	//*id_cor = aux_Casa->pCasaMatriz->pCor;
	*peca = aux_Casa->pCasaMatriz->pPeca;

	return TAB_CondRetOK;
}/*Fim funcao: &TAB obter Peca*/
// FIM AREA DO TAUAN----------------


// AREA DA JULIA--------------------

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
	LIS_IrInicioLista(aux_listaColuna);

	

	/*Anda atraves dos elementos de uma linha ate encontrar a coluna desejada*/
	for (corrente = 0; corrente < coluna; corrente++) {
		if (corrente == coluna) {
			break;
		}
		LIS_AvancarElementoCorrente(aux_listaColuna);
		
	}
	
	LIS_ObterNo(aux_listaColuna, (void**)&aux_Casa);
	
	LIS_ObterNo(aux_Casa->pCasaMatriz->pListaAmeacantes,(void**)&pListaAmeacantes);
	
	
	return TAB_CondRetOK;
}/*Fim funcao: &TAB obter Lista Ameacantes*/

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
		printf("out of range");
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
}/*Fim funcao: &TAB obter Lista Ameacados*/

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

		
		/*Vai ate o final da coluna*/
		LIS_IrInicioLista(listaColunas);
		for (numColunas = 0; numColunas < cabeca_TAB->num_de_colunas; numColunas++){
			LIS_AvancarElementoCorrente(listaColunas);
		}
		
		/*Vem de trás pra frente na coluna*/
		for (numColunas = numColunas; numColunas > 0; numColunas--){
		
			printf("Liberando Linha:%d Coluna:%d\n",numLinhas,numColunas);
			LIS_ObterNo(listaColunas, (void**)&aux_Casa);


			printf("Lista ameacados : %p\n", aux_Casa->pCasaMatriz->pListaAmeacados);
			TAB_ObterListaAmeacados(cabeca_TAB, numLinhas, numColunas, listaAmeacados);
			free(listaAmeacados);
			printf("Lista ameacados LIBERADA : %p\n", aux_Casa->pCasaMatriz->pListaAmeacados);


			printf("Lista ameacantes : %p\n", aux_Casa->pCasaMatriz->pListaAmeacantes);
			TAB_ObterListaAmeacantes(cabeca_TAB, numLinhas, numColunas, listaAmeacantes);
			free(&listaAmeacantes);
			printf("Lista ameacantes LIBERADA : %p\n", listaAmeacantes);


			printf("Peca: %p", aux_Casa->pCasaMatriz->pPeca);
			free(aux_Casa->pCasaMatriz->pPeca);
			printf("Peca LIBERADA: %p", aux_Casa->pCasaMatriz->pPeca);


			printf("Casa: %p", aux_Casa);
			free(aux_Casa);
			printf("Casa: LIBERADA %p", aux_Casa);


			LIS_ExcluirNoCorrente(listaColunas);
			LIS_VoltarElementoCorrente(listaColunas);
			
		} // Fim for
		
		LIS_AvancarElementoCorrente(cabeca_TAB->pCabecaLista);
	}

	LIS_IrInicioLista(cabeca_TAB->pCabecaLista);
	LIS_EsvaziarLista(cabeca_TAB->pCabecaLista);
	LIS_DestroiLista(cabeca_TAB->pCabecaLista);
	free(cabeca_TAB);

	return TAB_CondRetOK;
}
/*Fim funcao: &TAB Destruir Tabuleiro*/
// FIM AREA DA JULIA-----------------
