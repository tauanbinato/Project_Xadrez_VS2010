#pragma once
#if ! defined( TABULEIRO_ )
#define TABULEIRO_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: TAB  Matriz de listas duplamente encadeadas
*
*  Arquivo gerado:              TABULEIRO.h
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\TABULEIRO.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: Julia Aleixo , Lucas Palma , Tauan Binato
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       tbf   26/set/2016 in�cio desenvolvimento.
*
*  $ED Descri��o do m�dulo
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
*  $TC Tipo de dados: TAB Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es do Tabuleiro
*
***********************************************************************/

typedef enum {

	TAB_CondRetOK,
	/* Concluiu corretamente  = 0*/

	TAB_CondRetListaVazia,
	/* A lista n�o cont�m elementos = 1 */

	TAB_CondRetFimLista,
	/* Foi atingido o fim de lista  = 2*/

	TAB_CondRetNaoAchou,
	/* N�o encontrou o valor procurado = 3*/

	TAB_CondRetFaltouMemoria
	/* Faltou mem�ria ao tentar criar um elemento de lista = 4 */

} TAB_tpCondRet;

/***********************************************************************
*
*  $FC Fun��o: TAB  &inserir Pe�a
*
*  $ED Descri��o da fun��o
*     insere Pe�a por referencia na casa passada
*
*  $EP Par�metros
*     cabeca_TAB		- cabe�a do tabuleiro a ser inserida
*	  cord_linha		- coordenada para a linha
*	  cord_coluna		- coordenada para a coluna
*	  peca_PEC			- ponteiro pra void de uma peca
*
*  $FV Valor retornado
*     Se executou corretamente retorna a condi��o de retorno LIS_CondRetOK.
*
*
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*	$AE - Assertivas de entrada
*	- Recebe n�mero da linha e da coluna v�lidos (menores ou iguais a 8)
*	- A posi��o da casa no encontro da linha com a coluna est� vazia
*	- Tabuleiro j� foi criado
*	- Recebe cor valida (�P� ou �B�) e identidade (string de 4 caracteres)
*	$AS - Assertivas de sa�da:
*	- Pe�a foi criada e inserida na posi��o desejada do tabuleiro
*
***********************************************************************/

TAB_tpCondRet TAB_InserirPeca(TAB_ppAncoraTabuleiro cabeca_TAB, int cord_linha, int cord_coluna, void** peca_PEC);

/***********************************************************************
*
*	$FC Fun�ao: TAB &MoverPeca 
* 
*	$ED Descri��o da fun��o:
*	Esta fun��o dever� mover a pe�a recebida para a posi��o desejada no tabuleiro
*	
*	$EP Par�metros
*	- Coordenadas de origem e destino
*
*	$AE - Assertivas de entrada
*	- Pe�a j� foi criada, com suas informa��es preenchidas ( e n�o � vazia )
*	- Posi��o para qual ela vai se mover est� vazia, al�m de ser uma posi��o valida (contida dentro do tabuleiro)
*	- Movimento � permitido para aquela pe�a
*	- Tabuleiro j� foi criado
*	$AS - Assertivas de sa�da:
*	- Peca agora est� na posi��o desejada
*	- Sua posi��o antiga agora est� vazia (�V�)
*
***********************************************************************/

TAB_tpCondRet TAB_MoverPeca(TAB_ppAncoraTabuleiro cabeca_TAB, int xOrg, int yOrg, int xDest, int yDest);

/***********************************************************************
*
*  $FC Fun��o: TAB  &Retirar Pe�a
*
*  $ED Descri��o da fun��o
*     Retira a peca que ocupa a coordenada passada
*
*  $EP Par�metros
*     cabeca_TAB		- cabe�a do tabuleiro a ser destruido
*	  cord_linha		- coordenada para a linha
*	  cord_coluna		- coordenada para a coluna
*
*  $FV Valor retornado
*     Se executou corretamente retorna a condi��o de retorno LIS_CondRetOK.
*
*
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*	$AE - Assertivas de entrada
*	- Existe uma pe�a na coordenada enviada
*	- Tabuleiro existe
*	$AS - Assertivas de sa�da:
*	- Pe�a foi retirada
*	- Posi��o (casa) que ela estava agora est� vazia
*
***********************************************************************/

TAB_tpCondRet TAB_RetirarPeca(TAB_ppAncoraTabuleiro cabeca_TAB, int cord_linha, int cord_coluna);

/***********************************************************************
*
*  $FC Fun��o: TAB  &Obter Pe�a
*
*  $ED Descri��o da fun��o
*     Obtem a peca que ocupa a coordenada passada
*
*  $EP Par�metros
*     cabeca_TAB		- cabe�a do tabuleiro a ser destruido
*	  cord_linha		- coordenada para a linha
*	  cord_coluna		- coordenada para a coluna
*     id_Peca		    - ponteiro parao tipo de peca a ser obtida
*     id_cor		    - ponteiro parao a cor da peca a ser obtida
*
*  $FV Valor retornado
*     Se executou corretamente retorna a condi��o de retorno LIS_CondRetOK.
*
*
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*	$AE - Assertivas de entrada
*	- Tabuleiro est� criado
*	- Posi��o enviada � v�lida
*	- Ponteiro a ser preenchido � do mesmo tipo estrutural que pe�a
*	$AS - Assertivas de sa�da:
*	- Ponteiro agora contem informa��o sobre a pe�a que estava na posi��o inserida (pode ser uma pe�a ou �V�-vazio)
***********************************************************************/

TAB_tpCondRet TAB_ObterPeca(TAB_ppAncoraTabuleiro cabeca_TAB, int cord_linha, int cord_coluna, void** peca);

/***********************************************************************
*
*  $FC Fun��o: TAB  &Obter Lista Ameacantes
*
*  $ED Descri��o da fun��o
*     Obtem a Lista de Amea�antes �quela casa
*
*  $EP Par�metros
*     cabeca_TAB		- cabe�a do tabuleiro a ser destruido
*	  linha				- coordenada para a linha
*	  coluna			- coordenada para a coluna
*     pListaAmeacantes  - ponteiro para a lista ameacantes a ser obtida
*
*
*  $FV Valor retornado
*     Se executou corretamente retorna a condi��o de retorno LIS_CondRetOK.
*
*
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*	$AE - Assertivas de entrada
*	- Recebe �ndice de linha e coluna v�lidos (menores ou igual a 8)
*	- Tabuleiro tem que estar criado e preenchido (com vazios ou com pe�as)
*	$AS - Assertivas de sa�da:
*	- Valem assertivas estruturais de lista
*	- Foi obtido a lista amea�antes que estava na posi��o dos �ndices recebidos
***********************************************************************/

TAB_tpCondRet TAB_ObterListaAmeacantes(TAB_ppAncoraTabuleiro cabeca_TAB, int linha, int coluna, LIS_tppLista * pListaAmeacantes);

/***********************************************************************
*
*  $FC Fun��o: TAB  &Obter Lista Ameacados
*
*  $ED Descri��o da fun��o
*     Obtem a Lista de elementos que ameacam aquela casa
*
*  $EP Par�metros
*     cabeca_TAB		- cabe�a do tabuleiro a ser destruido
*	  linha				- coordenada para a linha
*	  coluna			- coordenada para a coluna
*     pListaAmeacados   - ponteiro para a lista de ameacados a ser obtida
*
*
*  $FV Valor retornado
*     Se executou corretamente retorna a condi��o de retorno LIS_CondRetOK.
*
*
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*	$AE - Assertivas de entrada
*	- Recebe �ndice de linha e coluna v�lidos (menores ou igual a 8)
*	- Tabuleiro tem que estar criado e preenchido (com vazios ou com pe�as)
*	$AS - Assertivas de sa�da:
*	Valem assertivas estruturais de lista
*	- Foi obtido a lista amea�ados que estava na posi��o dos �ndices recebidos
*	 
***********************************************************************/

TAB_tpCondRet TAB_ObterListaAmeacados(TAB_ppAncoraTabuleiro cabeca_TAB, int linha, int coluna, LIS_tppLista * pListaAmeacados);

/***********************************************************************
*
*  $FC Fun��o: TAB  &Destruir Tabuleiro
*
*  $ED Descri��o da fun��o
*     Destroi o tabuleiro (as listas que a compoe e o tudo que est� contido nelas) 
*
*  $EP Par�metros
*     cabeca_TAB - cabe�a do tabuleiro a ser destruido
*	
*
*  $FV Valor retornado
*     Se executou corretamente retorna a condi��o de retorno LIS_CondRetOK.
*
*
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*	$AE - Assertivas de entrada
*	- Recebe o endere�o da cabe�a do tabuleiro (j� criado)
*	$AS - Assertivas de sa�da:
*	- Tabuleiro foi destru�do, e todos seus componentes tamb�m. Al�m disso, toda a mem�ria alocada antes por ele e seus componentes foram liberadas
***********************************************************************/

TAB_tpCondRet TAB_DestruirTabuleiro(TAB_ppAncoraTabuleiro cabeca_TAB);

/***********************************************************************
*
*  $FC Fun��o: TAB  &Criar Tabuleiro
*
*  $ED Descri��o da fun��o
*     Cria uma ancora que aponta para o inicio de uma lista e coluna de tamanho fixo
*     Cria uma lista duplamente encadeada com um identificador para representar a linha de uma matriz	
*	  Cria uma lista duplamente encadeada com um identificador para representar a coluna de uma matriz	
*
*  $EP Par�metros
*     $EP Par�metros
*     cabeca_TAB - cabe�a do tabuleiro a ser destruido
*	
*
*  $FV Valor retornado
*     Se executou corretamente retorna a condi��o de retorno LIS_CondRetOK.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     LIS_CondRetFaltouMemoria.
*
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*	$AE - Assertivas de entrada
*	- Recebe o endere�o de uma cabe�a de matriz a ser preenchida
*	$AS - Assertivas de sa�da:
*	- Valem todas as assertivas de estruturais de lista
*	- Ponteiro agora foi preenchido para a estrutura criada, que � uma matriz composta por listas ( com 8 linhas e 8 colunas )
***********************************************************************/

TAB_tpCondRet TAB_CriaTabuleiro(TAB_ppAncoraTabuleiro *cabeca_TAB, int *lado_linhas, int *lado_colunas);



#undef TABULEIRO_EXT

/********** Fim do m�dulo de defini��o: TAB  Tabuleiro **********/

#else
#endif