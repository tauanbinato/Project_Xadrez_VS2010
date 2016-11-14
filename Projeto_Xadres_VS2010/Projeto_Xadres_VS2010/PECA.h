#pragma once
#if ! defined( PECA_ )
#define PECA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: PEC  Estrutura de uma Pca
*
*  Arquivo gerado:              PECA.h
*  Letras identificadoras:      PECA
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\PECA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: Julia Aleixo , Lucas Palma , Tauan Binato
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       tbf,ja,lp   26/set/2016 in�cio desenvolvimento.
*
*  $ED Descri��o do m�dulo
*
*
***************************************************************************/


#if defined( PECA_OWN )
#define PECA_EXT
#else
#define PECA_EXT extern
#endif


/***********************************************************************
*
*  $TC Tipo de dados: PEC Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es de uma PECA
*
***********************************************************************/

typedef enum {

	PEC_CondRetOK,
	/* Concluiu corretamente  = 0*/

	PEC_CondRetListaVazia,
	/* A lista n�o cont�m elementos = 1 */

	PEC_CondRetFimLista,
	/* Foi atingido o fim de lista  = 2*/

	PEC_CondRetNaoAchou,
	/* N�o encontrou o valor procurado = 3*/

	PEC_CondRetFaltouMemoria,
	/* Faltou mem�ria ao tentar criar um elemento de lista = 4 */

	PEC_CondRetPonteiroNulo
	/* Ponteiro para elemento passado � Nulo = 5 */

} PEC_tpCondRet;


//Estruturas-----------------------------------------

	typedef struct PEC_tagPeca * PEC_tppPeca ;

/***********************************************************************
*
*  $FC Fun��o: PEC  &Insere Classe em Peca
*
*  $ED Descri��o da fun��o
*     Insere uma classe a estrutura pe�a
*
*  $EP Par�metros
*     peca  - ponteiro para a estrutura a ser manipulada
*	  ClassePeca - ponteiro para Classe pe�a a ser inserida
*
*  $FV Valor retornado
*     CondRetOK            - se um elemento tiver sido voltado
*	  CondRetPonteiroNulo  - se ou pe�a ou Classe Pe�a estiverem vazios
*
*  $AE - Assertivas de entrada
*  - Recebe um ponteiro para pe�a (criada) e uma classe pe�a a ser inserida
*  $AS - Assertivas de saida
*  - � passado por referencia o ponteiro preenchido com a classe desejada
***********************************************************************/

	PEC_tpCondRet PEC_InserirClassePeca(PEC_tppPeca peca, CPC_tppClassePeca ClassePeca) ;

/**********************************************************************
*
*  $FC Fun��o: PEC  &Obtem Valores de Peca
*
*  $ED Descri��o da fun��o
*     Funcao de acesso para obter Classe e cor de uma estrutura peca
*
*  $EP Par�metros
*     peca  - ponteiro para a estrutura a ser manipulada
*	  ClassePeca  - ponteiro para uma classePeca a ser manipulada
*	  cor_Peca  - cor da Pe�a a ser manipulada
*
*  $FV Valor retornado
*     CondRetOK            - se um elemento tiver sido voltado
*	  CondRetPonteiroNulo  - se a pe�a passada for nula
*
*  $AE - Assertivas de entrada
*  - Recebe uma pe�a criada
*  - Recebe ponteiros para serem preenchidos com classe e cor da pe�a
*  $AS - Assertivas de saida
*  - Ponteiros estao preencidos com os valores da pe�a enviada
***********************************************************************/

	PEC_tpCondRet PEC_ObtemValoresDePeca(PEC_tppPeca peca, CPC_tppClassePeca *ClassePeca, char *cor_peca) ;

/***********************************************************************
*
*  $FC Fun��o: PEC  &Cria Peca
*
*  $ED Descri��o da fun��o
*     Cria e inicializa uma peca
*
*  $EP Par�metros
*     peca  - ponteiro para a estrutura a ser manipulada
*	  ClassePeca  - ponteiro para classe da pe�a a ser inserida
*	  cor_peca - nome da cor de uma peca
*
*  $FV Valor retornado
*     CondRetOK            - se um elemento tiver sido voltado
*  $AE - Assertivas de entrada
*  - Recebe ponteiro para esse tipo de estrutura
*  $AS - Assertivas de saida
*  - Foi criado a estrutura com seus respectivos campos passados
*  
***********************************************************************/

PEC_tpCondRet PEC_criaPeca(PEC_tppPeca *peca, CPC_tppClassePeca ClassePeca, char cor_peca) ;

/***********************************************************************
*
*  $FC Fun��o: PEC  &DestroiPeca
*
*  $ED Descri��o da fun��o
*     Destroi a pe�a
*
*  $EP Par�metros
*     peca  - ponteiro para a estrutura a ser manipulada
*
*  $FV Valor retornado
*	  CondRetNaoAchou      - se a pe�a nao existir
*     CondRetOK            - se um elemento tiver sido destruido
*  $AE - Assertivas de entrada
*  - Recebe uma peca
*  $AS - Assertivas de saida
*  - Se ela fosse nula, retorna que nao achou, caso contrario, seu espaco � liberado 
***********************************************************************/

PEC_tpCondRet PEC_DestroiPeca(PEC_tppPeca peca) ;

#undef PECA_EXT

/********** Fim do m�dulo de defini��o: TAB  Tabuleiro **********/

#else
#endif
