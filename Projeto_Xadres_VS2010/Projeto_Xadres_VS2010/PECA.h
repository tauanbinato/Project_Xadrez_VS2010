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

	PEC_CondRetFaltouMemoria
	/* Faltou memória ao tentar criar um elemento de lista = 4 */

} PEC_tpCondRet;


//Estruturas-----------------------------------------
typedef struct PEC_tagPeca * PEC_tppPeca;
//Estruturas-----------------------------------------



/***********************************************************************
*
*  $FC Função: PEC  &Insere Valor em Peca
*
*  $ED Descrição da função
*     Insere um nome e uma cor em uma estrutura peca
*
*  $EP Parâmetros
*     peca  - ponteiro para a estrutura a ser manipulada
*     cor_peca   - cor de uma peca
*	  nome_peca  - nome de uma peca
*
*  $FV Valor retornado
*     CondRetOK            - se um elemento tiver sido voltado
*
*  $AE - Assertivas de entrada
*  - Recebe um ponteiro para peça (criada) e um nome e cor válidos a serem inseridos nela
*  $AS - Assertivas de saida
*  - É passado por referencia o ponteiro preenchido com a cor e nome desejados
***********************************************************************/
PEC_tpCondRet PEC_insereValorEmPeca(PEC_tppPeca *peca, char *nome_peca, char *cor_peca);

/***********************************************************************
*
*  $FC Função: PEC  &Obtem Valores de Peca
*
*  $ED Descrição da função
*     Funcao de acesso para obter nome e cor de uma estrutura peca
*
*  $EP Parâmetros
*     peca  - ponteiro para a estrutura a ser manipulada
*	  cor_peca  - cor de uma peca
*	  nome_peca  - nome de uma peca
*
*  $FV Valor retornado
*     CondRetOK            - se um elemento tiver sido voltado
*
*  $AE - Assertivas de entrada
*  - Recebe uma peça criada
*  - Recebe ponteiros para serem preenchidos com nome e cor da peça
*  $AS - Assertivas de saida
*  - Ponteiros estao preencidos com os valores da peça enviada
***********************************************************************/
PEC_tpCondRet PEC_obtemValoresdePeca(PEC_tppPeca peca, char *nome_peca, char *cor_peca);

/***********************************************************************
*
*  $FC Função: PEC  &Cria Peca
*
*  $ED Descrição da função
*     Cria e inicializa uma peca
*
*  $EP Parâmetros
*     peca  - ponteiro para a estrutura a ser manipulada
*	  nome_peca  - nome de uma peca
*	  cor_peca - nome da cor de uma peca
*
*  $FV Valor retornado
*     CondRetOK            - se um elemento tiver sido voltado
*  $AE - Assertivas de entrada
*  - Recebe ponteiro para esse tipo de estrutura
*  $AS - Assertivas de saida
*  - Foi criado a estrutura com seus respectivos campos (nome, cor e movimento- todos preenchidos com nome ‘V’, cor: NULL e movimento: NULL)
*  
***********************************************************************/

PEC_tpCondRet PEC_criaPeca(PEC_tppPeca *peca);

/***********************************************************************
*
*  $FC Função: PEC  &EsvaziaPeca
*
*  $ED Descrição da função
*     Esvazia a Peça
*
*  $EP Parâmetros
*     peca  - ponteiro para a estrutura a ser manipulada
*
*  $FV Valor retornado
*	  CondRetNaoAchou      - se a peça nao existir
*     CondRetOK            - se um elemento tiver sido esvaziado
*
*  $AE - Assertivas de entrada
*  - Recebe uma peça (pode ser nula ou não)
*  $AS - Assertivas de saida
*  - A os campos da peça foram substituidos por 'V' (se a peça nao fosse nula), caso fosse nula, recebe nao achou
***********************************************************************/

PEC_tpCondRet PEC_EsvaziaPeca(PEC_tppPeca peca) ;

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
PEC_tpCondRet PEC_DestroiPeca(PEC_tppPeca peca);

#undef PECA_EXT

/********** Fim do módulo de definição: TAB  Tabuleiro **********/

#else
#endif
