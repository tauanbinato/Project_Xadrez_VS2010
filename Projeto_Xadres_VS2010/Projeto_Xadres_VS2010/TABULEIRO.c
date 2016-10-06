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
#include   "Peca.h"

#define	   tamanho_matriz	8

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
	PEC_tppPeca  pPeca;

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

TAB_tpCondRet cria_tabuleiro(TAB_ppAncoraTabuleiro cabeca_TAB) {

	/* Declaracoes necessarias */
	int numDoCaminho, numColunas;
	char* vetor_IDS[tamanho_matriz] = { "um" , "dois" , "tres" , "quat" , "cinc" , "seis" , "sete" , "oito" };

	LIS_tppLista  caminho_matriz;
	LIS_tppLista  colunas_matriz ;

	TAB_ppAncoraCasa *cabeca_casa;

	char idObtido[5];
	char idEnviado[5] = "Cami";

	//Auxiliares

	LIS_tppLista   aux_caminhoMatriz;
	TAB_ancoraCasa *aux_cabecaCasa;
	TAB_ppAncoraTabuleiro aux_ancoraTAB;

	/* Fazendo as alocacaos necessarias */


	// - Alocando cabeça da Tabuleiro.
	aux_ancoraTAB = (TAB_ancoraTabuleiro *)malloc(sizeof(TAB_ancoraTabuleiro));
	if (aux_ancoraTAB == NULL) {
	
		return TAB_CondRetFaltouMemoria;
	}

	// - Alocando cabeca de uma casa
	cabeca_casa = (TAB_ppAncoraCasa )malloc(sizeof(TAB_ancoraCasa));
	if (cabeca_casa == NULL) {
		return TAB_CondRetFaltouMemoria;
	}

	// - Aloca a lista que a cabeca tabuleiro aponta
	
	printf("Id enviado: %s\n" , idEnviado);

	// Init Edit: Brandao 05/10 20:16 ####
	//LIS_CriarLista(&cabeca_TAB->pCabecaLista, idEnviado);
	LIS_CriarLista(&aux_ancoraTAB->pCabecaLista, idEnviado);
	
	//caminho_matriz = cabeca_TAB->pCabecaLista;
	caminho_matriz = aux_ancoraTAB->pCabecaLista;
	// Fim Edit ###

	LIS_ObterId(caminho_matriz ,idObtido );
	printf("Id obtido: %s\n" , idObtido);

	 
	//Inicializando estrutura.
	aux_ancoraTAB->num_de_linhas = 0;
	aux_ancoraTAB->num_de_colunas = 0;
	
	for (numDoCaminho = 0; numDoCaminho < tamanho_matriz; numDoCaminho++)
	{
		//Cria 8 caminhos (linhas)
		LIS_CriarLista(&colunas_matriz, vetor_IDS[numDoCaminho]);
		LIS_InserirNo(caminho_matriz, colunas_matriz);
	    aux_ancoraTAB->num_de_linhas++;
		
		for (numColunas = 0; numColunas < tamanho_matriz; numColunas++)
		{
			//Cria 8 elementos para cada linha e aponta para uma casa
			aux_cabecaCasa = (TAB_ancoraCasa *)malloc(sizeof(TAB_ancoraCasa));
			if (aux_cabecaCasa == NULL) {
			
				return TAB_CondRetFaltouMemoria;
			}

			cabeca_casa = (TAB_ppAncoraCasa *)malloc(sizeof(TAB_ppAncoraCasa));
			if (cabeca_casa == NULL) {
				return TAB_CondRetFaltouMemoria;
			}

			*cabeca_casa = aux_cabecaCasa;

			LIS_InserirNo(colunas_matriz, cabeca_casa);

			free(aux_cabecaCasa);    
 
			//cabeca_TAB->num_de_colunas++;
			aux_ancoraTAB->num_de_colunas++;

			printf("(%d,%d) - %d\n", numDoCaminho, numColunas, (*cabeca_casa)->pCasaMatriz);
		
		}
	} /* endFor */


	cabeca_TAB = aux_ancoraTAB;
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
TAB_tpCondRet inserirPeca(TAB_ppAncoraTabuleiro cabeca_TAB, int cord_linha , int cord_coluna , void * peca_PEC)
{

	int corrente;
	char *nomePeca , *corPeca;
	TAB_ppAncoraCasa *aux_Casa;
	PEC_tppPeca aux_Peca;
	
	/*Crio um ponteiro para a primeira lista que a cabeca aponta*/
	LIS_tppLista aux_listaCaminho;
	LIS_tppLista aux_listaColuna;
	aux_listaCaminho = cabeca_TAB->pCabecaLista;

	/*Coloco o pElemCorrente no inicio da lista que iremos caminhar*/
	LIS_IrInicioLista(&aux_listaCaminho);
	printf("Valores: cord_linha: %d  cord_coluna: %d \n" ,cord_linha , cord_coluna);

	//Testa se esta OUT of RANGE
	if ((cord_linha > tamanho_matriz || cord_coluna > tamanho_matriz ) || (cord_linha == 0 || cord_coluna == 0)) {
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
	LIS_ObterNo(aux_listaColuna, (void**)&aux_Peca);

	peca_PEC = &aux_Peca;

	return TAB_CondRetOK;
}/*Fim funcao: TAB &Inserir Peça*/

/***************************************************************************
*
*  Funcao: TAB  &Mover Peca
*
*  **************************************************************************/
TAB_tpCondRet moverPeca(TAB_ppAncoraTabuleiro cabeca_TAB, int xOrg, int yOrg, int xDest, int yDest) 
{
	char *id_peca, *id_cor;

	if (cabeca_TAB == NULL) {
		return TAB_CondRetListaVazia;
	}
	
	if (xDest > 8 || xDest < 1 || yDest> 1 || yDest < 8) {
		return TAB_CondRetFimLista;
	}


	obterPeca(cabeca_TAB, xDest, yDest, id_peca, id_cor);




	return TAB_CondRetOK;
}/*Fim funcao: TAB &Mover Peca*/

/***************************************************************************
*
*  Funcao: TAB  &Retirar Peca
*
*  **************************************************************************/
TAB_tpCondRet retirarPeca(TAB_ppAncoraTabuleiro cabeca_TAB, int cord_linha, int cord_coluna)
{
	int corrente ;
	LIS_tppLista auxCabecaColuna  ;
	TAB_ppAncoraCasa  auxCabecaCasa ;
	//Volta o elemento corrente até o 1º elemento
	LIS_IrInicioLista(cabeca_TAB->pCabecaLista);

	//Busca a linha certa
	for (corrente = 1; corrente == cord_linha; corrente++) {
		if (corrente == cord_linha)
			break;
			LIS_AvancarElementoCorrente(cabeca_TAB->pCabecaLista);
	}
	
	LIS_ObterNo(cabeca_TAB->pCabecaLista, (void**)&auxCabecaColuna) ;
	LIS_IrInicioLista(auxCabecaColuna);

	//Busca coluna certa
	for(corrente = 1; corrente == cord_coluna; corrente++)
		if (corrente == cord_coluna)
			break;
		LIS_AvancarElementoCorrente(auxCabecaColuna);
	
	LIS_ObterNo(auxCabecaColuna, (void**)&auxCabecaCasa);

	PEC_EsvaziaPeca(&auxCabecaCasa->pCasaMatriz->pPeca);

	return TAB_CondRetOK;
}/*Fim funcao: TAB &Retirar Peca*/

/***************************************************************************
*
*  Funcao: TAB  &Obter Peca
*
*  **************************************************************************/
TAB_tpCondRet obterPeca(TAB_ppAncoraTabuleiro cabeca_TAB, int cord_linha, int cord_coluna, char *id_peca, char *id_cor)
{
	int corrente;
	char nomePeca, corPeca;
	TAB_ppAncoraCasa aux_Casa;
	PEC_tppPeca *aux_Peca;

	/*Crio um ponteiro para a primeira lista que a cabeca aponta*/
	LIS_tppLista aux_listaCaminho, aux_listaColuna;

	aux_listaCaminho = cabeca_TAB->pCabecaLista;

	/*Coloco o pElemCorrente no inicio da lista que iremos caminhar*/
	LIS_IrInicioLista(aux_listaCaminho);

	//Testa se esta OUT of RANGE
	if ((cord_linha > tamanho_matriz || cord_coluna > tamanho_matriz) || (cord_linha == 0 || cord_coluna == 0)) {
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

	printf("Corrente : %d || Linha : %d\n", corrente, cord_linha);

	/*Anda atraves dos elementos de uma linha ate encontrar a coluna desejada*/
	for (corrente = 1; corrente == cord_coluna; corrente++) {
		if (corrente == cord_coluna) {
			break;
		}
		LIS_AvancarElementoCorrente(aux_listaColuna);
	}

	LIS_ObterNo(aux_listaColuna, (void**)&aux_Casa);

	PEC_obtemValoresdePeca(aux_Casa->pCasaMatriz->pPeca, &id_peca, &id_cor);

	return TAB_CondRetOK;
}/*Fim funcao: &TAB obter Peca*/
// FIM AREA DO TAUAN----------------


// AREA DA JULIA--------------------

/***************************************************************************
*
*  Funcao: TAB  &Obter Lista Ameacantes
*
*  **************************************************************************/
TAB_tpCondRet obterListaAmeacantes(TAB_ppAncoraTabuleiro cabeca_TAB, int linha, int coluna, LIS_tppLista * pListaAmeacantes )
{
	int corrente;
	char nomePeca, corPeca;
	TAB_ppAncoraCasa aux_Casa;
	PEC_tppPeca *aux_Peca;

	/*Crio um ponteiro para a primeira lista que a cabeca aponta*/
	LIS_tppLista aux_listaCaminho, aux_listaColuna;

	aux_listaCaminho = cabeca_TAB->pCabecaLista;

	/*Coloco o pElemCorrente no inicio da lista que iremos caminhar*/
	LIS_IrInicioLista(aux_listaCaminho);

	//Testa se esta OUT of RANGE
	if ((linha > tamanho_matriz || coluna > tamanho_matriz) || (linha == 0 || coluna == 0)) {
		return TAB_CondRetNaoAchou;
	}

	/*Anda atraves da cabeça ate encontrar a linha desejada*/
	for (corrente = 1; corrente == linha; corrente++) {
		if (corrente == linha) {
			break;
		}
		LIS_AvancarElementoCorrente(aux_listaCaminho);
	}

	LIS_ObterNo(aux_listaCaminho, (void**)&aux_listaColuna);
	LIS_IrInicioLista(aux_listaColuna);

	printf("Corrente : %d || Linha : %d\n", corrente, linha);

	/*Anda atraves dos elementos de uma linha ate encontrar a coluna desejada*/
	for (corrente = 1; corrente == coluna; corrente++) {
		//if (corrente == coluna) {
		//	break;
		//}
		LIS_AvancarElementoCorrente(aux_listaColuna);
		printf("avancou lista coluna\n");
	}
	printf("saiu for funcao obter\n");
	LIS_ObterNo(aux_listaColuna, (void**)&aux_Casa);
	printf("saiu obter no 1\n");
	LIS_ObterNo(aux_Casa->pCasaMatriz->pListaAmeacantes,(void**)&pListaAmeacantes);
	printf("obteve no 2\n");
	
	return TAB_CondRetOK;
}/*Fim funcao: &TAB obter Lista Ameacantes*/

/***************************************************************************
*
*  Funcao: TAB  &Obter Lista Ameacados
*
*  **************************************************************************/
TAB_tpCondRet obterListaAmeacados(TAB_ppAncoraTabuleiro cabeca_TAB, int linha, int coluna, LIS_tppLista * pListaAmeacados )
{
	int corrente;
	char nomePeca, corPeca;
	TAB_ppAncoraCasa aux_Casa;
	PEC_tppPeca *aux_Peca;

	/*Crio um ponteiro para a primeira lista que a cabeca aponta*/
	LIS_tppLista aux_listaCaminho, aux_listaColuna;

	aux_listaCaminho = cabeca_TAB->pCabecaLista;

	/*Coloco o pElemCorrente no inicio da lista que iremos caminhar*/
	LIS_IrInicioLista(aux_listaCaminho);

	//Testa se esta OUT of RANGE
	if ((linha > tamanho_matriz || coluna > tamanho_matriz) || (linha == 0 || coluna == 0)) {
		return TAB_CondRetNaoAchou;
	}

	/*Anda atraves da cabeça ate encontrar a linha desejada*/
	for (corrente = 1; corrente == linha; corrente++) {
		if (corrente == linha) {
			break;
		}
		LIS_AvancarElementoCorrente(aux_listaCaminho);
	}

	LIS_ObterNo(aux_listaCaminho, (void**)&aux_listaColuna);
	LIS_IrInicioLista(aux_listaColuna);

	printf("Corrente : %d || Linha : %d\n", corrente, linha);

	/*Anda atraves dos elementos de uma linha ate encontrar a coluna desejada*/
	for (corrente = 1; corrente == coluna; corrente++) {
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
TAB_tpCondRet destruirTabuleiro(TAB_ppAncoraTabuleiro cabeca_TAB)
{
	int numLinhas, numColunas;
	LIS_tppLista listacolunas, aux, *listaameacantes,*listaameacados;
	TAB_ppAncoraCasa *aux_Casa;
	PEC_tppPeca aux_Peca;
	
	LIS_IrInicioLista(cabeca_TAB->pCabecaLista);
	
	for(numLinhas = 1; numLinhas < tamanho_matriz; numLinhas++)
	{
		LIS_ObterNo(cabeca_TAB->pCabecaLista, (void**)&listacolunas);
		LIS_IrInicioLista(listacolunas);

		for (numColunas = 1; numColunas < tamanho_matriz; numColunas++)
		{
			aux_Casa = (TAB_ppAncoraCasa*)malloc(sizeof(TAB_ppAncoraCasa));

			printf("\nentrou for2");
			LIS_ObterNo(listacolunas, (void**)&aux_Casa);
			printf("\npassou");
			//LIS_EsvaziarLista(listacolunas);
			obterListaAmeacantes(cabeca_TAB, numLinhas, numColunas, listaameacantes);
			LIS_ObterNo(*listaameacantes, (void**)&aux_Peca);
			while (listaameacantes != NULL)
			{
				PEC_DestroiPeca(aux_Peca); //destroi a peca na posicao 
				LIS_ExcluirNoCorrente(*listaameacantes); //exclui o no onde se encontrava a peca
				printf ("printf passou 3\n");
				LIS_ObterNo(*listaameacantes, (void**)&aux_Peca);
			}
			
			printf("esvaziou");
			obterListaAmeacantes(cabeca_TAB, numLinhas, numColunas, listaameacados);
			LIS_ObterNo(*listaameacantes, (void**)&aux_Peca);
			while (listaameacados != NULL)
			{
				PEC_DestroiPeca(aux_Peca);
				LIS_ExcluirNoCorrente(*listaameacados);
				printf ("printf passou 3\n");
				LIS_ObterNo(*listaameacados, (void**)&aux_Peca);
			}
		
			LIS_DestroiLista(*listaameacantes);
			LIS_DestroiLista(*listaameacados);
			//PEC_DestroiPeca(aux_Casa->pCasaMatriz->pPeca);
			//LIS_DestroiLista(aux_Casa->pCasaMatriz->pListaAmeacados);
			//LIS_DestroiLista(aux_Casa->pCasaMatriz->pListaAmeacantes);
	
			free(aux_Casa);
			printf("\nB");
	
			LIS_AvancarElementoCorrente(listacolunas);
			printf("\n%d", numColunas);
		}
		
		LIS_AvancarElementoCorrente(cabeca_TAB->pCabecaLista);
	}
	LIS_EsvaziarLista(cabeca_TAB->pCabecaLista);
	LIS_DestroiLista(cabeca_TAB->pCabecaLista);

	free(cabeca_TAB);

	return TAB_CondRetOK;
}/*Fim funcao: &TAB Destruir Tabuleiro*/
// FIM AREA DA JULIA-----------------
