#pragma once
#if ! defined( TABULEIRO_ )
#define TABULEIRO_
/***************************************************************************
*
*  $MCD Módulo de definição: TAB  Matriz de listas duplamente encadeadas
*
*  Arquivo gerado:              TABULEIRO.h
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\TABULEIRO.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: Julia Aleixo , Lucas Palma , Tauan Binato
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       tbf   26/set/2016 início desenvolvimento.
*
*  $ED Descrição do módulo
*
*
***************************************************************************/

#include "Lista.h"

#if defined( TABULEIRO_OWN )
#define TABULEIRO_EXT
#else
#define TABULEIRO_EXT extern
#endif

//Estruturas-----------------------------------------

typedef struct TAB_tagTabuleiro * TAB_ppAncoraTabuleiro;
typedef struct TAB_tagAncoraCasa * TAB_ppAncoraCasa;

//FIM Estruturas-----------------------------------------



/***********************************************************************
*
*  $TC Tipo de dados: TAB Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do Tabuleiro
*
***********************************************************************/

typedef enum {

	TAB_CondRetOK,
	/* Concluiu corretamente  = 0*/

	TAB_CondRetListaVazia,
	/* A lista não contém elementos = 1 */

	TAB_CondRetFimLista,
	/* Foi atingido o fim de lista  = 2*/

	TAB_CondRetNaoAchou,
	/* Não encontrou o valor procurado = 3*/

	TAB_CondRetFaltouMemoria
	/* Faltou memória ao tentar criar um elemento de lista = 4 */

} TAB_tpCondRet;

/***********************************************************************
*
*  $FC Função: TAB  &inserir Peça
*
*  $ED Descrição da função
*     insere Peça na casa passada
*
*  $EP Parâmetros
*     cabeca_TAB		- cabeça do tabuleiro a ser destruido
*	  cord_linha		- coordenada para a linha
*	  cord_coluna		- coordenada para a coluna
*     id_Peca		    - ponteiro parao tipo de peca a ser inserida
*     id_cor		    - ponteiro parao a cor da peca a ser inserida
*
*  $FV Valor retornado
*     Se executou corretamente retorna a condição de retorno LIS_CondRetOK.
*
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

TAB_tpCondRet inserirPeca(TAB_ppAncoraTabuleiro cabeca_TAB, int cord_linha , int cord_coluna , char **id_peca , char **id_cor);

/***********************************************************************

-Função MoverPeca –a coordenada de origem e a coordenada de destino. Esta função deverá verificar se a peça poderá executar este movimento e se capturará uma peça de outra cor.
Caso isso aconteça, a peça oponente será retirada do tabuleiro.  Crie os retornos necessários.

***********************************************************************/

TAB_tpCondRet moverPeca();

/***********************************************************************
*
*  $FC Função: TAB  &Retirar Peça
*
*  $ED Descrição da função
*     Retira a peca que ocupa a coordenada passada
*
*  $EP Parâmetros
*     cabeca_TAB		- cabeça do tabuleiro a ser destruido
*	  cord_linha		- coordenada para a linha
*	  cord_coluna		- coordenada para a coluna
*
*  $FV Valor retornado
*     Se executou corretamente retorna a condição de retorno LIS_CondRetOK.
*
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

TAB_tpCondRet retirarPeca(TAB_ppAncoraTabuleiro cabeca_TAB, int cord_linha, int cord_coluna);

/***********************************************************************
*
*  $FC Função: TAB  &Obter Peça
*
*  $ED Descrição da função
*     Obtem a peca que ocupa a coordenada passada
*
*  $EP Parâmetros
*     cabeca_TAB		- cabeça do tabuleiro a ser destruido
*	  cord_linha		- coordenada para a linha
*	  cord_coluna		- coordenada para a coluna
*     id_Peca		    - ponteiro parao tipo de peca a ser obtida
*     id_cor		    - ponteiro parao a cor da peca a ser obtida
*
*  $FV Valor retornado
*     Se executou corretamente retorna a condição de retorno LIS_CondRetOK.
*
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

TAB_tpCondRet obterPeca(TAB_ppAncoraTabuleiro cabeca_TAB, int cord_linha, int cord_coluna, char *id_peca, char *id_cor) ;

/***********************************************************************
*
*  $FC Função: TAB  &Obter Lista Ameacantes
*
*  $ED Descrição da função
*     Obtem a Lista de Ameaçantes àquela casa
*
*  $EP Parâmetros
*     cabeca_TAB		- cabeça do tabuleiro a ser destruido
*	  linha				- coordenada para a linha
*	  coluna			- coordenada para a coluna
*     pListaAmeacantes  - ponteiro para a lista ameacantes a ser obtida
*
*
*  $FV Valor retornado
*     Se executou corretamente retorna a condição de retorno LIS_CondRetOK.
*
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

TAB_tpCondRet obterListaAmeacantes(TAB_ppAncoraTabuleiro cabeca_TAB, int linha, int coluna, LIS_tppLista * pListaAmeacantes);

/***********************************************************************
*
*  $FC Função: TAB  &Obter Lista Ameacados
*
*  $ED Descrição da função
*     Obtem a Lista de elementos que ameacam aquela casa
*
*  $EP Parâmetros
*     cabeca_TAB		- cabeça do tabuleiro a ser destruido
*	  linha				- coordenada para a linha
*	  coluna			- coordenada para a coluna
*     pListaAmeacados   - ponteiro para a lista de ameacados a ser obtida
*
*
*  $FV Valor retornado
*     Se executou corretamente retorna a condição de retorno LIS_CondRetOK.
*
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

TAB_tpCondRet obterListaAmeacados(TAB_ppAncoraTabuleiro cabeca_TAB, int linha, int coluna, LIS_tppLista * pListaAmeacados);

/***********************************************************************
*
*  $FC Função: TAB  &Destruir Tabuleiro
*
*  $ED Descrição da função
*     Destroi o tabuleiro (as listas que a compoe e o tudo que está contido nelas) 
*
*  $EP Parâmetros
*     cabeca_TAB - cabeça do tabuleiro a ser destruido
*	
*
*  $FV Valor retornado
*     Se executou corretamente retorna a condição de retorno LIS_CondRetOK.
*
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

TAB_tpCondRet destruirTabuleiro(TAB_ppAncoraTabuleiro cabeca_TAB);

/***********************************************************************
*
*  $FC Função: TAB  &Criar Tabuleiro
*
*  $ED Descrição da função
*     Cria uma ancora que aponta para o inicio de uma lista e coluna de tamanho fixo
*     Cria uma lista duplamente encadeada com um identificador para representar a linha de uma matriz	
*	  Cria uma lista duplamente encadeada com um identificador para representar a coluna de uma matriz	
*
*  $EP Parâmetros
*     $EP Parâmetros
*     cabeca_TAB - cabeça do tabuleiro a ser destruido
*	
*
*  $FV Valor retornado
*     Se executou corretamente retorna a condição de retorno LIS_CondRetOK.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     LIS_CondRetFaltouMemoria.
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

TAB_tpCondRet cria_tabuleiro(TAB_ppAncoraTabuleiro cabeca_TAB);



#undef TABULEIRO_EXT

/********** Fim do módulo de definição: TAB  Tabuleiro **********/

#else
#endif