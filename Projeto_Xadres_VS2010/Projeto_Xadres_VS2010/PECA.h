#pragma once
#if ! defined( PECA_ )
#define PECA_
/***************************************************************************
*
*  $MCD Módulo de definição: PEC  Estrutura de uma Pca
*
*  Arquivo gerado:              PECA.h
*  Letras identificadoras:      PECA
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\PECA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: Julia Aleixo , Lucas Palma , Tauan Binato
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       tbf,ja,lp   26/set/2016 início desenvolvimento.
*
*  $ED Descrição do módulo
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
*  $TC Tipo de dados: PEC Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções de uma PECA
*
***********************************************************************/

typedef enum {

	PEC_CondRetOK,
	/* Concluiu corretamente  = 0*/

	PEC_CondRetListaVazia,
	/* A lista não contém elementos = 1 */

	PEC_CondRetFimLista,
	/* Foi atingido o fim de lista  = 2*/

	PEC_CondRetNaoAchou,
	/* Não encontrou o valor procurado = 3*/

	PEC_CondRetFaltouMemoria,
	/* Faltou memória ao tentar criar um elemento de lista = 4 */

	PEC_CondRetPonteiroNulo
	/* Ponteiro para elemento passado é Nulo = 5 */

} PEC_tpCondRet;


//Estruturas-----------------------------------------

	typedef struct PEC_tagPeca * PEC_tppPeca ;

/***********************************************************************
*
*  $FC Função: PEC  &Insere Classe em Peca
*
*  $ED Descrição da função
*     Insere uma classe a estrutura peça
*
*  $EP Parâmetros
*     peca  - ponteiro para a estrutura a ser manipulada
*	  ClassePeca - ponteiro para Classe peça a ser inserida
*
*  $FV Valor retornado
*     CondRetOK            - se um elemento tiver sido voltado
*	  CondRetPonteiroNulo  - se ou peça ou Classe Peça estiverem vazios
*
*  $AE - Assertivas de entrada
*  - Recebe um ponteiro para peça (criada) e uma classe peça a ser inserida
*  $AS - Assertivas de saida
*  - É passado por referencia o ponteiro preenchido com a classe desejada
***********************************************************************/

	PEC_tpCondRet PEC_InserirClassePeca(PEC_tppPeca peca, CPC_tppClassePeca ClassePeca) ;

/**********************************************************************
*
*  $FC Função: PEC  &Obtem Valores de Peca
*
*  $ED Descrição da função
*     Funcao de acesso para obter Classe e cor de uma estrutura peca
*
*  $EP Parâmetros
*     peca  - ponteiro para a estrutura a ser manipulada
*	  ClassePeca  - ponteiro para uma classePeca a ser manipulada
*	  cor_Peca  - cor da Peça a ser manipulada
*
*  $FV Valor retornado
*     CondRetOK            - se um elemento tiver sido voltado
*	  CondRetPonteiroNulo  - se a peça passada for nula
*
*  $AE - Assertivas de entrada
*  - Recebe uma peça criada
*  - Recebe ponteiros para serem preenchidos com classe e cor da peça
*  $AS - Assertivas de saida
*  - Ponteiros estao preencidos com os valores da peça enviada
***********************************************************************/

	PEC_tpCondRet PEC_ObtemValoresDePeca(PEC_tppPeca peca, CPC_tppClassePeca *ClassePeca, char *cor_peca) ;

/***********************************************************************
*
*  $FC Função: PEC  &Cria Peca
*
*  $ED Descrição da função
*     Cria e inicializa uma peca
*
*  $EP Parâmetros
*     peca  - ponteiro para a estrutura a ser manipulada
*	  ClassePeca  - ponteiro para classe da peça a ser inserida
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
*  $FC Função: PEC  &DestroiPeca
*
*  $ED Descrição da função
*     Destroi a peça
*
*  $EP Parâmetros
*     peca  - ponteiro para a estrutura a ser manipulada
*
*  $FV Valor retornado
*	  CondRetNaoAchou      - se a peça nao existir
*     CondRetOK            - se um elemento tiver sido destruido
*  $AE - Assertivas de entrada
*  - Recebe uma peca
*  $AS - Assertivas de saida
*  - Se ela fosse nula, retorna que nao achou, caso contrario, seu espaco é liberado 
***********************************************************************/

PEC_tpCondRet PEC_DestroiPeca(PEC_tppPeca peca) ;

#undef PECA_EXT

/********** Fim do módulo de definição: TAB  Tabuleiro **********/

#else
#endif
