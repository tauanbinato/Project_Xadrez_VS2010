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


typedef struct CAS_tagCasa * CAS_tppCasa;



#undef CASA_EXT

/********** Fim do módulo de definição: TAB  Tabuleiro **********/

#else
#endif
