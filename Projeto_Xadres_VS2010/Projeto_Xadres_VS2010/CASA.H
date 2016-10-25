#pragma once
#if ! defined( CASA_ )
#define CASA_
/***************************************************************************
*
*  $MCD Módulo de definição: PEC  Estrutura de uma Casa
*
*  Arquivo gerado:              CASA.h
*  Letras identificadoras:      CASA
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\CASA.BSW
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


#if defined( CASA_OWN )
#define CASA_EXT
#else

#define CASA_EXT extern
#endif

/***********************************************************************
*
*  $TC Tipo de dados: CAS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções de uma CASA
*
***********************************************************************/

typedef enum {

	CAS_CondRetOK,
	/* Concluiu corretamente  = 0*/

	CAS_CondRetListaVazia,
	/* A lista não contém elementos = 1 */

	CAS_CondRetFimLista,
	/* Foi atingido o fim de lista  = 2*/

	CAS_CondRetNaoAchou,
	/* Não encontrou o valor procurado = 3*/

	CAS_CondRetFaltouMemoria
	/* Faltou memória ao tentar criar um elemento de lista = 4 */

} CAS_tpCondRet;


/*Estruturas*/
typedef struct CAS_tagCasa * CAS_tppCasa;


/*Funções de acesso*/


/***********************************************************************
*
*  $FC Função: LIS  &Criar Casa
*
*  $ED Descrição da função
*     Cria uma estrutura de uma casa com listas de ameacantes, ameacados e uma peca inicializadas.
*
*  $EP Parâmetros
*     casa          - ponteiro de ponteiro para a estrutura casa
*					  a ser criada.
*
*  $FV Valor retornado
*     Se executou corretamente retorna a condição de retorno CAS_CondRetOK.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     LIS_CondRetFaltouMemoria.
*
*     Se ocorreu algum erro na criação de uma peca sera retornado PEC_CondRetFaltouMemoria
*
*	$AE - Assertivas de entrada:
*	-Recebe uma identidade de lista que é um string de ate 4 caracteres válidos
*	$AS - Assertivas de saída:
*	-Se pAnt ≠ NULL, então pCorr->pAnt->pProx = pCorr ; Se pProx ≠ NULL, então pCorr->pProx->pAnt->pCorr (essas são as assertivas estruturais da lista duplamente encadeada com cabeça)
*	-Lista foi criada
*	-Os ponteiros de inicio, fim e pElem corrente apontam para o mesmo local(origem da lista)
*
*
***********************************************************************/
CAS_tpCondRet CAS_criaCasa(CAS_tppCasa *pCasa, void **pPeca);


#undef CASA_EXT

/********** Fim do módulo de definição: TAB  Tabuleiro **********/

#else
#endif
