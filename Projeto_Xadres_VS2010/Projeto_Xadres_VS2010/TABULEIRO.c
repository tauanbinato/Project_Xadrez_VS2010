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

	int i;
	/*Coordenada i do corrente*/

	char j;
	/*Coordenada j do corrente*/

	int tam;
	/*Tamanho do tabuleiro*/


} TAB_ancoraTabuleiro;


/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor da cabeca (ancora) de uma casa
*
***********************************************************************/

typedef struct TAB_tagCasa {

	void*	 pPeca; /* Ponteiro para a estrutura da peca */
	char	 cor; /* Cor da peca, que define o jogador */
	LIS_tppLista pAmeacantes; /* Lista de pecas ameacantes na dada casa */
	LIS_tppLista pAmeacados; /* Lista de pecas ameacadas na dada casa */

} TAB_tpCasa;

/***************************************************************************
*
*  Funcao: TAB  &Criar Tabuleiro
*
*  **************************************************************************/

TAB_tpCondRet TAB_CriaTabuleiro(TAB_ppAncoraTabuleiro* ppTabuleiro, int tam) {
	TAB_ppAncoraTabuleiro pTabuleiro;
	int linhaCorrente;
	int colunaCorrente;

	if (tam <= 0) {
		return TAB_CondRetInvalido;
	}

	if (ppTabuleiro == NULL) {
		return TAB_CondRetPonteiroNulo;
	}

	pTabuleiro = (TAB_ancoraTabuleiro*)malloc(sizeof(TAB_ancoraTabuleiro));
	if (pTabuleiro == NULL) {
		return TAB_CondRetFaltouMemoria;
	}

	if (LIS_CriarLista(&pTabuleiro->pCabecaLista, "tab") == LIS_CondRetFaltouMemoria) {
		free(pTabuleiro);
		return TAB_CondRetFaltouMemoria;
	}
	pTabuleiro->tam = tam;

	for (linhaCorrente = 0; linhaCorrente < tam; linhaCorrente++) {
		for (colunaCorrente = 0; colunaCorrente < tam; colunaCorrente++) {
			if (LIS_InserirNo(pTabuleiro->pCabecaLista, NULL) != LIS_CondRetOK) {
				LIS_DestroiLista(pTabuleiro->pCabecaLista);
				free(pTabuleiro);
				return TAB_CondRetFaltouMemoria;
			}
		}
	}

	LIS_IrInicioLista(pTabuleiro->pCabecaLista);

	pTabuleiro->i = 0;
	pTabuleiro->j = 'A';

	*ppTabuleiro = pTabuleiro;

	return TAB_CondRetOK;

}
/***********************************************************************
*  $FC Função: TAB Checar Posicao Valida
***********************************************************************/
TAB_tpCondRet TAB_ChecarPosicaoValida(int i, char j) {
	if (j < 'A' || j > 'H' || i < 0 || i > 7) {
		return TAB_CondRetNaoAchou;
	}

	return TAB_CondRetOK;
}

/***********************************************************************
*
*  $FC Função: TAB Definir Posicao Corrente
*
***********************************************************************/
TAB_tpCondRet TAB_DefinirPosCorrente(TAB_ppAncoraTabuleiro pTabuleiro, int i, char j) {
	int qtdParaAndar;
	int k;

	qtdParaAndar = i*(pTabuleiro->tam) + (j - 'A');

	if (i < 0 || i > (pTabuleiro->tam - 1) || j < 'A' || j > 'A' + (pTabuleiro->tam - 1)) {
		return TAB_CondRetInvalido;
	}
	
	if (pTabuleiro == NULL) {
		TAB_CondRetPonteiroNulo;
	}

	if (TAB_ChecarPosicaoValida(i, j) == TAB_CondRetNaoAchou ) {
		return TAB_CondRetNaoAchou;
	}

	LIS_IrInicioLista(pTabuleiro->pCabecaLista);

	if (LIS_AvancarElementoCorrente(pTabuleiro->pCabecaLista, qtdParaAndar) == LIS_CondRetFimLista) {
		return TAB_CondRetInvalido;
	}

	pTabuleiro->i = i;
	pTabuleiro->j = j;

	return TAB_CondRetOK;
}

/***********************************************************************
*  $FC Função: TAB Obter Posicao Corrente
***********************************************************************/
TAB_tpCondRet TAB_ObterPosCorrente(TAB_ppAncoraTabuleiro pTabuleiro, int* i, char* j) {
	if (pTabuleiro == NULL) {
		return TAB_CondRetPonteiroNulo;
	}

	*i = (int)pTabuleiro->i;
	*j = (char)pTabuleiro->j;

	return TAB_CondRetOK;

}

/***********************************************************************
*  $FC Função: TAB Atribuir Valor Corrente
***********************************************************************/
TAB_tpCondRet TAB_AtribuirValorCorrente(TAB_ppAncoraTabuleiro pTabuleiro, TAB_tppCasa pCasa) {
	if (pTabuleiro == NULL) {
		return TAB_CondRetPonteiroNulo;
	}

	LIS_AlterarElementoCorrente(pTabuleiro->pCabecaLista, (void*)pCasa);

	return TAB_CondRetOK;
}

/***********************************************************************
*  $FC Função: TAB Obter Peca corrente
***********************************************************************/
TAB_tpCondRet TAB_ObterPecaCorrente(TAB_ppAncoraTabuleiro pTabuleiro, void** pPeca, int* cor) {
	TAB_tpCasa* pCasa;

	pCasa = (TAB_tpCasa*)malloc(sizeof(TAB_tpCasa));
	if (pCasa == NULL) {
		return TAB_CondRetFaltouMemoria;
	}

	TAB_ObterValorCorrente(pTabuleiro, &pCasa);

	if (pCasa != NULL) {
		*pPeca = pCasa->pPeca;
		*cor = pCasa->cor;
		return TAB_CondRetOK;
	}

	return TAB_CondRetCasaVazia;
}



/***************************************************************************
*
*  Funcao: TAB &inserir Peca
*
*  *************************************************************************/
TAB_tpCondRet TAB_InserirPeca(TAB_ppAncoraTabuleiro pTabuleiro, void** pPeca, int i, char j, char cor)
{
	TAB_tpCasa* pCasa;

	if (pTabuleiro == NULL) {
		return TAB_CondRetPonteiroNulo;
	}

	if (TAB_ChecarPosicaoValida(i, j) != TAB_CondRetOK) {
		return TAB_CondRetNaoAchou;
	}

	pCasa = (TAB_tpCasa*)malloc(sizeof(TAB_tpCasa));
	if (pCasa == NULL) {
		return TAB_CondRetFaltouMemoria;
	}

	TAB_DefinirPosCorrente(pTabuleiro, i, j);

	pCasa->pPeca = pPeca;
	pCasa->cor = cor;
	pCasa->pAmeacados = NULL;
	pCasa->pAmeacantes = NULL;

	LIS_AlterarElementoCorrente(pTabuleiro->pCabecaLista, (void*)pCasa);

	return TAB_CondRetOK;

}/*Fim funcao: TAB &Inserir Peça*/


/***************************************************************************
*
*  Funcao: TAB  &Mover Peca
*
*  **************************************************************************/

TAB_tpCondRet TAB_MoverPeca(TAB_ppAncoraTabuleiro pTabuleiro, char jOrig, int iOrig, char jDest, int iDest, void** PecaComida, char* jogadorComido) {
	char jogador1, jogador2;
	TAB_tpCasa *pCasaOrig, *pCasaDest;

	if (pTabuleiro == NULL) {
		return TAB_CondRetPonteiroNulo;
	}

	// Checa se a posicao de origem e destino dadas sao validas.
	if (TAB_ChecarPosicaoValida(iOrig, jOrig) == TAB_CondRetNaoAchou ||
		TAB_ChecarPosicaoValida(iDest, jDest) == TAB_CondRetNaoAchou) {
		return TAB_CondRetNaoAchou;
	}

	pCasaOrig = (TAB_tppCasa*)malloc(sizeof(TAB_tppCasa));
	if (pCasaOrig == NULL) {
		return TAB_CondRetFaltouMemoria;
	}

	pCasaDest = (TAB_tppCasa*)malloc(sizeof(TAB_tppCasa));
	if (pCasaDest == NULL) {
		return TAB_CondRetFaltouMemoria;
	}

	TAB_DefinirPosCorrente(pTabuleiro, iOrig, jOrig);

	TAB_ObterValorCorrente(pTabuleiro, &pCasaOrig);

	TAB_DefinirPosCorrente(pTabuleiro, iDest, jDest);

	TAB_ObterValorCorrente(pTabuleiro, &pCasaDest);

	if (pCasaDest != NULL) {
		jogador1 = pCasaOrig->cor;
		
		jogador2 = pCasaDest->cor;

		if (jogador1 != jogador2) {
			TAB_ObterPeca(pTabuleiro, iDest, jDest, PecaComida, &jogadorComido);
			
			TAB_DefinirPosCorrente(pTabuleiro, iOrig, jOrig);
		
			TAB_RetirarPeca(pTabuleiro, iOrig, jOrig);
		
			TAB_DefinirPosCorrente(pTabuleiro, iDest, jDest);
		
			TAB_AtribuirValorCorrente(pTabuleiro, pCasaOrig);
		}
	}
	else {
		TAB_DefinirPosCorrente(pTabuleiro, iOrig, jOrig);
	
		TAB_ObterValorCorrente(pTabuleiro, &pCasaOrig);
	
		TAB_DefinirPosCorrente(pTabuleiro, iDest, jDest);
	
		TAB_AtribuirValorCorrente(pTabuleiro, pCasaOrig);
	
		TAB_RetirarPeca(pTabuleiro, iOrig, jOrig);
	}

	return TAB_CondRetOK;
}


/***************************************************************************
*
*  Funcao: TAB  &Retirar Peca
*
*  **************************************************************************/

TAB_tpCondRet TAB_RetirarPeca(TAB_ppAncoraTabuleiro pTabuleiro, int i, char j) {
	TAB_tppCasa* ppCasa;

	if (pTabuleiro == NULL) {
		return TAB_CondRetPonteiroNulo;
	}

	if (TAB_ChecarPosicaoValida(i, j) != TAB_CondRetOK) {
		return TAB_CondRetNaoAchou;
	}

	ppCasa = (TAB_tppCasa*)malloc(sizeof(TAB_tppCasa));
	if (ppCasa == NULL) {
		return TAB_CondRetFaltouMemoria;
	}

	TAB_DefinirPosCorrente(pTabuleiro, i, j);
	TAB_ObterValorCorrente(pTabuleiro, ppCasa);

	if (ppCasa == NULL) {
		return TAB_CondRetCasaVazia;
	}

	//LIS_InserirNo( LIS_tppLista pLista , void * pValor);
	LIS_AlterarElementoCorrente(pTabuleiro->pCabecaLista, NULL);

	return TAB_CondRetOK;
}

 /***********************************************************************
 *  $FC Função: TAB Desmover Peca
 ***********************************************************************/
TAB_tpCondRet TAB_DesfazerMovimento(TAB_ppAncoraTabuleiro pTabuleiro, int iOrig, char jOrig, int iDest, char jDest, void** pPecaComida) {
	void** pPeca;
	char cor, cor2;
	if (pTabuleiro == NULL) {
		return TAB_CondRetPonteiroNulo;
	}

	if (TAB_ChecarPosicaoValida(iOrig, jOrig) == TAB_CondRetNaoAchou
		|| TAB_ChecarPosicaoValida(iDest, jDest) == TAB_CondRetNaoAchou) {
		return TAB_CondRetNaoAchou;
	}

	TAB_DefinirPosCorrente(pTabuleiro, iDest, jDest);
	
	TAB_ObterPeca(pTabuleiro, iDest, jDest, &pPeca, &cor);
	if(cor == 'P'){
		cor2 = 'B';
	}
	else{
		cor2 = 'P';
	}
	TAB_ObterValorCorrente(pTabuleiro, &pPeca);
	TAB_AtribuirValorCorrente(pTabuleiro, pPecaComida);
	TAB_AtribuirValorCorrente(pTabuleiro, pPeca);
	
	//TAB_InserirPeca(pTabuleiro, &pPecaComida, iDest, jDest,  cor2);
	//TAB_DefinirPosCorrente(pTabuleiro, iOrig, jOrig);
	//TAB_InserirPeca(pTabuleiro, &pPeca, iOrig, jOrig,  cor);

	return TAB_CondRetOK;
}


 /***********************************************************************
 *  $FC Função: TAB Obter Peca
 ***********************************************************************/
TAB_tpCondRet TAB_ObterPeca(TAB_ppAncoraTabuleiro pTabuleiro, int i, char j, void** pPeca, char* cor) {
	int iOrig;
	char jOrig;
	TAB_tppCasa pCasa;

	if (pTabuleiro == NULL) {
		return TAB_CondRetPonteiroNulo;
	}

	if (TAB_ChecarPosicaoValida(i, j) != TAB_CondRetOK) {
		return TAB_CondRetInvalido;
	}

	pCasa = (TAB_tppCasa)malloc(sizeof(TAB_tpCasa));
	if (pCasa == NULL) {
		return TAB_CondRetFaltouMemoria;
	}

	TAB_ObterPosCorrente(pTabuleiro, &iOrig, &jOrig);
	TAB_DefinirPosCorrente(pTabuleiro, i, j);
	TAB_ObterValorCorrente(pTabuleiro, &pCasa);
	TAB_DefinirPosCorrente(pTabuleiro, iOrig, jOrig);

	if ((pCasa) == NULL) {
		*pPeca = NULL;
		return TAB_CondRetCasaVazia;
	}
	
	if(((pCasa)->pPeca) == NULL){
		//*pPeca = (*ppCasa)->pPeca;
		//*cor = (*ppCasa)->cor;
		return TAB_CondRetOK;
	}

	*pPeca = (pCasa)->pPeca;
	*cor = (pCasa)->cor;
	return TAB_CondRetOK;
}


/***************************************************************************
*
*  Funcao: TAB  &Obter Lista Ameacantes
*
*  **************************************************************************/
TAB_tpCondRet TAB_ObterListaAmeacantes(TAB_ppAncoraTabuleiro pTabuleiro, int i, char j, LIS_tppLista* pLista) {
	TAB_tppCasa pCasa;

	if (pTabuleiro == NULL) {
		return TAB_CondRetPonteiroNulo;
	}

	if (TAB_ChecarPosicaoValida(i, j) != TAB_CondRetOK) {
		return TAB_CondRetNaoAchou;
	}

	pCasa = (TAB_tppCasa)malloc(sizeof(TAB_tpCasa));
	if (pCasa == NULL) {
		return TAB_CondRetFaltouMemoria;
	}

	TAB_DefinirPosCorrente(pTabuleiro, i, j);
	TAB_ObterValorCorrente(pTabuleiro, &pCasa);
	

	if (pCasa != NULL) {
		//pCasa->pAmeacantes = (LIS_tppLista)malloc(sizeof(LIS_tppLista));
		if (pCasa->pAmeacantes == NULL) {
			pCasa->pAmeacantes = (LIS_tppLista)malloc(sizeof(LIS_tppLista));
			//return TAB_CondRetPonteiroNulo;
		}

		*pLista = (pCasa->pAmeacantes);
	}
	else {
		return TAB_CondRetPonteiroNulo;
	}

	return TAB_CondRetOK;
}

/***************************************************************************
*
*  Funcao: TAB  &Obter Lista Ameacados
*
*  **************************************************************************/
TAB_tpCondRet TAB_ObterListaAmeacados(TAB_ppAncoraTabuleiro pTabuleiro, int i, char j, LIS_tppLista* pLista) {
	TAB_tppCasa pCasa;

	if (pTabuleiro == NULL) {
		return TAB_CondRetPonteiroNulo;
	}

	if (TAB_ChecarPosicaoValida(i, j) != TAB_CondRetOK) {
		return TAB_CondRetNaoAchou;
	}

	pCasa = (TAB_tppCasa)malloc(sizeof(TAB_tpCasa));
	if (pCasa == NULL) {
		return TAB_CondRetFaltouMemoria;
	}

	TAB_DefinirPosCorrente(pTabuleiro, i, j);
	TAB_ObterValorCorrente(pTabuleiro, &pCasa);

	if (pCasa != NULL) {
		if (LIS_CriarLista(&pCasa->pAmeacados,"ameacados") == LIS_CondRetFaltouMemoria) {
			return TAB_CondRetFaltouMemoria;
		}

		pLista = pCasa->pAmeacados;
	}
	else {
		return TAB_CondRetPonteiroNulo;
	}

	return TAB_CondRetOK;
}
/*Fim funcao: &TAB obter Lista Ameacados*/

/***************************************************************************
*
*  Funcao: TAB  &Destruir Tabuleiro
*
*  **************************************************************************/
TAB_tpCondRet TAB_DestruirTabuleiro(TAB_ppAncoraTabuleiro pTabuleiro){
	if (pTabuleiro == NULL) {
		return TAB_CondRetPonteiroNulo;
	}

	LIS_DestroiLista(pTabuleiro->pCabecaLista);
	free(pTabuleiro);

	return TAB_CondRetOK;
}
/*Fim funcao: &TAB Destruir Tabuleiro*/

/***********************************************************************
*  $FC Função: TAB Adicionar Lista Ameacantes e Ameaçados
***********************************************************************/

TAB_tpCondRet TAB_AdicionarListaAmeacantesAmeacados(TAB_ppAncoraTabuleiro pTabuleiro, int iAmeacante, char jAmeacante, int iAmeacado, char jAmeacado) {
	LIS_tpCondRet condRet1, condRet2;
	int iOrig;
	char jOrig;
	TAB_tppCasa pCasaAmeacante, pCasaAmeacada;

	if (pTabuleiro == NULL) {
		return TAB_CondRetPonteiroNulo;
	}

	TAB_ObterPosCorrente(pTabuleiro, &iOrig, &jOrig);
	TAB_DefinirPosCorrente(pTabuleiro, iAmeacante, jAmeacante);
	TAB_ObterValorCorrente(pTabuleiro, &pCasaAmeacante);
	TAB_DefinirPosCorrente(pTabuleiro, iAmeacado, jAmeacado);
	TAB_ObterValorCorrente(pTabuleiro, &pCasaAmeacada);
	TAB_DefinirPosCorrente(pTabuleiro, iOrig, jOrig);

	condRet1 = LIS_InserirNo(pCasaAmeacante->pAmeacados, pCasaAmeacada);
	condRet2 = LIS_InserirNo(pCasaAmeacada->pAmeacantes, pCasaAmeacante);

	if (condRet1 == LIS_CondRetFaltouMemoria || condRet2 == LIS_CondRetFaltouMemoria) {
		return TAB_CondRetFaltouMemoria;
	}

	if (condRet1 == LIS_CondRetListaNaoExiste || condRet2 == LIS_CondRetListaNaoExiste) {
		return TAB_CondRetPonteiroNulo;
	}

	return TAB_CondRetOK;
}


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*  $FC Função: TAB Obter Valor Corrente
***********************************************************************/
TAB_tpCondRet TAB_ObterValorCorrente(TAB_ppAncoraTabuleiro pTabuleiro, TAB_tppCasa* ppCasa) {
	if (pTabuleiro == NULL) {
		return TAB_CondRetPonteiroNulo;
	}

	LIS_ObterNo(pTabuleiro->pCabecaLista, (void**)ppCasa);

	return TAB_CondRetOK;
}

