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

#include   "lista.h"

#define LISTA_OWN
#include "Tabuleiro.h"
#undef LISTA_OWN

#define _DEBUG

#ifdef _DEBUG
#include   "CESPDIN.H"
#include   "CONTA.H"
#endif


/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor da cabeca (ancora) da matriz
*
***********************************************************************/

typedef struct TAB_tagTabuleiro {

	LIS_tppLista pCabecaLista;
	/* Ponteiro para um ponteiro de uma cabeça da lista */

	int i;
	/*Coordenada i do corrente*/

	char j;
	/*Coordenada j do corrente*/

	int tam;
	/*Tamanho do tabuleiro*/

	#ifdef _DEBUG
	int tamValores; /*tamanho total dos elementos da lista do tab*/
	#endif

} TAB_ancoraTabuleiro;


/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor de uma casa no tabuleiro
*
***********************************************************************/

typedef struct TAB_tagCasa {

	void*	 pPeca; /* Ponteiro para a estrutura da peca */
	char	 cor; /* Cor da peca, que define o jogador */
	LIS_tppLista pAmeacantes; /* Lista de pecas ameacantes na dada casa */
	LIS_tppLista pAmeacados; /* Lista de pecas ameacadas na dada casa */
	#ifdef _DEBUG
	TAB_ancoraTabuleiro *cabeça; /*ponteiro para cabeça do tabuleiro*/
	int tamCasa; /*tamanho da estrutura em cada no do tabuleiro*/
	int idTipo; /*tipo de estrutura aceita pela casa*/
	#endif 

} TAB_tpCasa;

#ifdef _DEBUG
void CED_InicializarControlador() ;
#endif

/***************************************************************************
*
*  Funcao: TAB  &Criar Tabuleiro
*
*  **************************************************************************/

TAB_tpCondRet TAB_CriaTabuleiro(TAB_ppAncoraTabuleiro * ppTabuleiro, int tam) {
	TAB_ppAncoraTabuleiro pTabuleiro;
	int linhaCorrente;
	int colunaCorrente;

	if (tam <= 0) {
		#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_CriarTabuleiro-inv" ) ;
   		#endif
	   return TAB_CondRetInvalido;
	}

	if (ppTabuleiro == NULL) {
		#ifdef _DEBUG
   		CNT_CONTAR( "TAB_CriarTabuleiro-pnulo" ) ;
		#endif
		return TAB_CondRetPonteiroNulo;
	}

	pTabuleiro = (TAB_ancoraTabuleiro*)malloc(sizeof(TAB_ancoraTabuleiro));
	if (pTabuleiro == NULL) {
		return TAB_CondRetFaltouMemoria;
	}
	#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_CriarTabuleiro" ) ;
   	#endif
	if (LIS_CriarLista(&pTabuleiro->pCabecaLista, "tab") == LIS_CondRetFaltouMemoria) {
		free(pTabuleiro);
		return TAB_CondRetFaltouMemoria;
	}
	pTabuleiro->tam = tam;
	#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_CriarTabuleiro-1" ) ;
   	#endif
	for (linhaCorrente = 0; linhaCorrente < tam; linhaCorrente++) {
		for (colunaCorrente = 0; colunaCorrente < tam; colunaCorrente++) {
			if (LIS_InserirNo(pTabuleiro->pCabecaLista, NULL) != LIS_CondRetOK) {
				LIS_DestroiLista(pTabuleiro->pCabecaLista);
				free(pTabuleiro);
				return TAB_CondRetFaltouMemoria;
			}
		}
	}
	#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_CriarTabuleiro-2" ) ;
   	#endif
	LIS_IrInicioLista(pTabuleiro->pCabecaLista);

	pTabuleiro->i = 0;
	pTabuleiro->j = 'A';

	#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_CriarTabuleiro-3" ) ;
   	#endif
	
	#ifdef _DEBUG
	   CED_MarcarEspacoAtivo(ppTabuleiro);
	   pTabuleiro->tam = 0;
	   pTabuleiro->tamValores = 0;
	#endif
	
	*ppTabuleiro = pTabuleiro;
	return TAB_CondRetOK;

}
/***********************************************************************
*  $FC Função: TAB Checar Posicao Valida
***********************************************************************/
TAB_tpCondRet TAB_ChecarPosicaoValida(int i, char j) {
	if (j < 'A' || j > 'H' || i < 0 || i > 7) {
		#ifdef _DEBUG
   			CNT_CONTAR( "TAB_ChecarPosicaoValida-naoachou" ) ;
   		#endif
			return TAB_CondRetNaoAchou;
	}
	#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_ChecarPosicaoValida" ) ;
   	#endif
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
		#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_DefinirPosCorrente-invalido" ) ;
   		#endif
	   return TAB_CondRetInvalido;
	}
	
	if (pTabuleiro == NULL) {
		#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_DefinirPosCorrente-pnulo" ) ;
   	#endif
	   TAB_CondRetPonteiroNulo;	
	}

	if (TAB_ChecarPosicaoValida(i, j) == TAB_CondRetNaoAchou ) {
		#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_DefinirPosCorrente-naoachou" ) ;
   		#endif
	   return TAB_CondRetNaoAchou;
	}

	LIS_IrInicioLista(pTabuleiro->pCabecaLista);

	if (LIS_AvancarElementoCorrente(pTabuleiro->pCabecaLista, qtdParaAndar) == LIS_CondRetFimLista) {
		#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_DefinirPosCorrente-fimlista" ) ;
   	#endif
	   return TAB_CondRetInvalido;
	}

	pTabuleiro->i = i;
	pTabuleiro->j = j;
	#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_DefinirPosCorrente" ) ;
   	#endif
	return TAB_CondRetOK;
}

/***********************************************************************
*  $FC Função: TAB Obter Posicao Corrente
***********************************************************************/
TAB_tpCondRet TAB_ObterPosCorrente(TAB_ppAncoraTabuleiro pTabuleiro, int* i, char* j) {
	if (pTabuleiro == NULL) {
		#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_ObterPosCorrente-pnulo" ) ;
   		#endif
	   return TAB_CondRetPonteiroNulo;
	}

	*i = (int)pTabuleiro->i;
	*j = (char)pTabuleiro->j;
	#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_ObterPosCorrente" ) ;
   	#endif
	return TAB_CondRetOK;

}

/***********************************************************************
*  $FC Função: TAB Atribuir Valor Corrente
***********************************************************************/
TAB_tpCondRet TAB_AtribuirValorCorrente(TAB_ppAncoraTabuleiro pTabuleiro, TAB_tppCasa pCasa) {
	if (pTabuleiro == NULL) {
		#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_AtribuirValorCorrente-pnulo" ) ;
		#endif
	   return TAB_CondRetPonteiroNulo;
	}

	LIS_AlterarElementoCorrente(pTabuleiro->pCabecaLista, (void*)pCasa);
	#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_AtribuirValorCorrente" ) ;
   	#endif
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
	#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_ObterPecaCorrente" ) ;
   	#endif
		return TAB_CondRetOK;
	}
	#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_ObterPecaCorrente-casavazia" ) ;
   	#endif
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
		#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_InserirPeca-pnulo" ) ;
		#endif
	   return TAB_CondRetPonteiroNulo;
	}

	if (TAB_ChecarPosicaoValida(i, j) != TAB_CondRetOK) {
	#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_InserirPeca-naoachou" ) ;
   	#endif
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
	#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_InserirPeca" ) ;
   	#endif
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
	#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_MoverPeca-pnulo" ) ;
   	#endif
	return TAB_CondRetPonteiroNulo;
	}

	// Checa se a posicao de origem e destino dadas sao validas.
	if (TAB_ChecarPosicaoValida(iOrig, jOrig) == TAB_CondRetNaoAchou ||
		TAB_ChecarPosicaoValida(iDest, jDest) == TAB_CondRetNaoAchou) {
		#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_MoverPeca-naoachou" ) ;
   		#endif
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
		#ifdef _DEBUG
   			CNT_CONTAR( "TAB_MoverPeca-jogadoresdifs" ) ;
		#endif
			TAB_ObterPeca(pTabuleiro, iDest, jDest, PecaComida, &jogadorComido);
			
			TAB_DefinirPosCorrente(pTabuleiro, iOrig, jOrig);
		
			TAB_RetirarPeca(pTabuleiro, iOrig, jOrig);
		
			TAB_DefinirPosCorrente(pTabuleiro, iDest, jDest);
		
			TAB_AtribuirValorCorrente(pTabuleiro, pCasaOrig);
			
		}
	}
	else {
		#ifdef _DEBUG
   			CNT_CONTAR( "TAB_MoverPeca-jogadoresig" ) ;
		#endif
		TAB_DefinirPosCorrente(pTabuleiro, iOrig, jOrig);
	
		TAB_ObterValorCorrente(pTabuleiro, &pCasaOrig);
	
		TAB_DefinirPosCorrente(pTabuleiro, iDest, jDest);
	
		TAB_AtribuirValorCorrente(pTabuleiro, pCasaOrig);
	
		TAB_RetirarPeca(pTabuleiro, iOrig, jOrig);
	}
	#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_MoverPeca" ) ;
   	#endif
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
	#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_RetirarPeca-pnulo" ) ;
   	#endif
		return TAB_CondRetPonteiroNulo;
	}

	if (TAB_ChecarPosicaoValida(i, j) != TAB_CondRetOK) {
		#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_RetirarPeca-naoachou" ) ;
		#endif
	   return TAB_CondRetNaoAchou;
	}

	ppCasa = (TAB_tppCasa*)malloc(sizeof(TAB_tppCasa));
	if (ppCasa == NULL) {
		return TAB_CondRetFaltouMemoria;
	}

	TAB_DefinirPosCorrente(pTabuleiro, i, j);
	TAB_ObterValorCorrente(pTabuleiro, ppCasa);

	if (ppCasa == NULL) {
	#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_RetirarPeca-casavazia" ) ;
   	#endif
		return TAB_CondRetCasaVazia;
	}

	//LIS_InserirNo( LIS_tppLista pLista , void * pValor);
	LIS_AlterarElementoCorrente(pTabuleiro->pCabecaLista, NULL);
	#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_RetirarPeca" ) ;
   	#endif
	return TAB_CondRetOK;
}

 /***********************************************************************
 *  $FC Função: TAB Desmover Peca
 ***********************************************************************/
TAB_tpCondRet TAB_DesfazerMovimento(TAB_ppAncoraTabuleiro pTabuleiro, int iOrig, char jOrig, int iDest, char jDest, void** pPecaComida) {
	void** pPeca;
	char cor, cor2;
	if (pTabuleiro == NULL) {
	#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_DesfazerMovimento-pnulo" ) ;
   	#endif
		return TAB_CondRetPonteiroNulo;
	}

	if (TAB_ChecarPosicaoValida(iOrig, jOrig) == TAB_CondRetNaoAchou
		|| TAB_ChecarPosicaoValida(iDest, jDest) == TAB_CondRetNaoAchou) {
		#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_DesfazerMovimento-naoachou" ) ;
   	#endif	
		return TAB_CondRetNaoAchou;
	}

	TAB_DefinirPosCorrente(pTabuleiro, iDest, jDest);
	
	TAB_ObterPeca(pTabuleiro, iDest, jDest, &pPeca, &cor);
	if(cor == 'P'){
		cor2 = 'B';
		#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_DesfazerMovimento-corP" ) ;
   		#endif
	}
	else{
		cor2 = 'P';
		#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_DesfazerMovimento-corB" ) ;
   		#endif
	}
	TAB_ObterValorCorrente(pTabuleiro, &pPeca);
	TAB_AtribuirValorCorrente(pTabuleiro, pPecaComida);
	TAB_AtribuirValorCorrente(pTabuleiro, pPeca);
	
	//TAB_InserirPeca(pTabuleiro, &pPecaComida, iDest, jDest,  cor2);
	//TAB_DefinirPosCorrente(pTabuleiro, iOrig, jOrig);
	//TAB_InserirPeca(pTabuleiro, &pPeca, iOrig, jOrig,  cor);
	#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_DesfazerMovimento" ) ;
   	#endif
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
		#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_ObterPeca-pnulo" ) ;
   	#endif
		return TAB_CondRetPonteiroNulo;
	}

	if (TAB_ChecarPosicaoValida(i, j) != TAB_CondRetOK) {
		#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_ObterPeca-posinv" ) ;
   	#endif
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
	#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_ObterPeca-casavazia" ) ;
   	#endif
		*pPeca = NULL;
		return TAB_CondRetCasaVazia;
	}
	
	if(((pCasa)->pPeca) == NULL){
		//*pPeca = (*ppCasa)->pPeca;
		//*cor = (*ppCasa)->cor;
		return TAB_CondRetOK;
	}
	#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_ObterPeca" ) ;
   	#endif
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
		#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_ObterListaAmeacantes-pnulo" ) ;
   	#endif
		return TAB_CondRetPonteiroNulo;
	}

	if (TAB_ChecarPosicaoValida(i, j) != TAB_CondRetOK) {
		#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_ObterListaAmeacantes-naoachou" ) ;
   	#endif
		return TAB_CondRetNaoAchou;
	}

	pCasa = (TAB_tppCasa)malloc(sizeof(TAB_tpCasa));
	if (pCasa == NULL) {
		return TAB_CondRetFaltouMemoria;
	}

	TAB_DefinirPosCorrente(pTabuleiro, i, j);
	TAB_ObterValorCorrente(pTabuleiro, &pCasa);
	

	if (pCasa != NULL) {
		#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_ObterListaAmeacantes-casannula" ) ;
   		#endif
		//pCasa->pAmeacantes = (LIS_tppLista)malloc(sizeof(LIS_tppLista));
		if (pCasa->pAmeacantes == NULL) {
			#ifdef _DEBUG
   				 CNT_CONTAR( "TAB_ObterListaAmeacantes-listanula" ) ;
   			#endif
			pCasa->pAmeacantes = (LIS_tppLista)malloc(sizeof(LIS_tppLista));
			//return TAB_CondRetPonteiroNulo;
		}

		*pLista = (pCasa->pAmeacantes);
	}
	else {
		return TAB_CondRetPonteiroNulo;
	}
	#ifdef _DEBUG
   	   CNT_CONTAR( "TAB_ObterListaAmeacantes" ) ;
   	#endif
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

