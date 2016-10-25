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



#undef CASA_EXT

/********** Fim do módulo de definição: TAB  Tabuleiro **********/

#else
#endif
