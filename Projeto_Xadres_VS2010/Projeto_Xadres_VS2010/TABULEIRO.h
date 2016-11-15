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
typedef struct TAB_tagCasa*	TAB_tppCasa;

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

	TAB_CondRetCasaVazia,
	/* A lista n�o cont�m elementos = 1 */

	TAB_CondRetFimLista,
	/* Foi atingido o fim de lista  = 2*/

	TAB_CondRetNaoAchou,
	/* N�o encontrou o valor procurado = 3*/

	TAB_CondRetFaltouMemoria,
	/* Faltou mem�ria ao tentar criar um elemento de lista = 4 */

	TAB_CondRetComeu,
	/*Peca foi comida = 5 */

	TAB_CondRetTabVazio,
	/*peca foi comida = 6 */

	TAB_CondRetNaoPermitido,
	/*movimento nao permitido = 7 */

	TAB_CondRetPonteiroNulo,
	/* Ponteiro passado � nulo = 8*/

	TAB_CondRetInvalido
	/* Informa��o passada n�o � valida = 9*/


} TAB_tpCondRet;

/***********************************************************************
*
*  $FC Fun��o: TAB  &inserir Pe�a
*
*  $ED Descri��o da fun��o
*     insere Pe�a por referencia na casa passada
*
*  $EP Par�metros
*     pTabuleiro		- cabe�a do tabuleiro a ser inserida
*	  i					- coordenada para a linha
*	  j					- coordenada para a coluna
*	  pPeca 			- ponteiro pra void de uma peca
*	  cor				- cor do dono da peca
*
*	$FV Valor retornado
*	CondRetOK, se pe�a foi inserida, 
*   CondRetNaoAchou, se posicao for fora do tabuleiro
*	CondRetPonteiroNulo, se o tabuleiro passado estiver nulo
*	CondRetFaltouMemoria, se nao conseguir alocar a estrutura de casa
*
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*	$AE - Assertivas de entrada
*	- Recebe n�mero da linha e da coluna v�lidos (menores ou iguais a 8)
*	- A posi��o da casa no encontro da linha com a coluna est� vazia
*	- Tabuleiro j� foi criado
*	- Recebe cor valida (�P� ou �B�)
*	$AS - Assertivas de sa�da:
*	- Pe�a foi criada e inserida na posi��o desejada do tabuleiro
*
***********************************************************************/

TAB_tpCondRet TAB_InserirPeca(TAB_ppAncoraTabuleiro pTabuleiro, void* pPeca, int i, char j, int cor);

/***********************************************************************
*
*	$FC Fun�ao: TAB &MoverPeca 
* 
*	$ED Descri��o da fun��o:
*	Esta fun��o dever� mover a pe�a recebida para a posi��o desejada no tabuleiro
*	
*	$EP Par�metros
*	- Coordenadas de origem e destino e ancora do tabuleiro
*   PecaComida    - ponteiro duplo para void com a Pe�a Comida, se for o caso
*   jogadorComido - ponteiro para a cor da pe�a comida, se for o caso
*
*	$FV Valor retornado
*   CondRetNaoAchou, se o destino ou origem forem fora do tabuleiro
*   CondRetOK, se tiver executado o movimento com sucesso
*	CondRetFaltouMemoria, se alguma estrutura nao tiver sido alocada
*	CondRetPonteiroNulo, se a ancora estiver vazia
*
*	$AE - Assertivas de entrada
*	- Pe�a j� foi criada, com suas informa��es preenchidas ( e n�o � vazia )
*	- Movimento � permitido para aquela pe�a
*	- Tabuleiro j� foi criado
*
*	$AS - Assertivas de sa�da:
*	- Peca agora est� na posi��o desejada
*	- Sua posi��o antiga agora est� vazia 
*
***********************************************************************/

TAB_tpCondRet TAB_MoverPeca(TAB_ppAncoraTabuleiro pTabuleiro, char jOrig, int iOrig, char jDest, int iDest, void** PecaComida, char* jogadorComido);

/***********************************************************************
*
*  $FC Fun��o: TAB  &Retirar Pe�a
*
*  $ED Descri��o da fun��o
*     Retira a peca que ocupa a coordenada passada
*
*  $EP Par�metros
*     pTabuleiro		- cabe�a do tabuleiro a ser retirada a pe�a
*	  i					- coordenada para a linha
*	  j					- coordenada para a coluna
*
*  $FV Valor retornado
*	CondRetOK, se pe�a foi retirada,
*	CondRetNaoAchou, se posicao for fora do tabuleiro
*	CondRetCasaVazia, se a casa estiver vazia
*	CondRetPonteiroNulo, se a ancora estiver vazia
*
*
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*	$AE - Assertivas de entrada
*	- Existe uma pe�a na coordenada enviada
*
*	$AS - Assertivas de sa�da:
*	- Pe�a foi retirada
*	- Posi��o (casa) que ela estava agora est� vazia
*
***********************************************************************/

TAB_tpCondRet TAB_RetirarPeca(TAB_ppAncoraTabuleiro pTabuleiro, int i, char j);

/***********************************************************************
*
*  $FC Fun��o: TAB  &Obter Pe�a
*
*  $ED Descri��o da fun��o
*     Obtem a peca que ocupa a coordenada passada
*
*  $EP Par�metros
*     pTabuleiro		- cabe�a do tabuleiro a ser destruido
*	  i					- coordenada para a linha
*	  j					- coordenada para a coluna
*     pPeca 		    - ponteiro para void, que representa a peca a ser obtida
*     cor		        - ponteiro para a cor da peca a ser obtida
*
*	$FV Valor retornado
*	CondRetOK, se pe�a foi obtida, 
*	CondRetNaoAchou, se posicao for fora do tabuleiro
*	CondRetCasaVazia, se a casa estiver vazia
*	CondRetPonteiroNulo, se a ancora estiver vazia
*	CondRetFaltouMemoria, se alguma estrutura nao tiver sido alocada
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

TAB_tpCondRet TAB_ObterPeca(TAB_ppAncoraTabuleiro pTabuleiro, int i, char j, void** pPeca, char* cor);

/***********************************************************************
*
*  $FC Fun��o: TAB  &Obter Lista Ameacantes
*
*  $ED Descri��o da fun��o
*     Obtem a Lista de Amea�antes �quela casa
*
*  $EP Par�metros
*     pTabuleiro		- cabe�a do tabuleiro a ser destruido
*	  i					- coordenada para a linha
*	  j					- coordenada para a coluna
*     pLista		    - ponteiro para a lista ameacantes a ser obtida
*
*
*	$FV Valor retornado
*	CondRetOK, se lista foi retornada por referencia, 
*	CondRetNaoAchou, se posicao for fora do tabuleiro
*	CondRetPonteiroNulo, se a ancora estiver vazia
*	CondRetFaltouMemoria, se alguma estrutura nao tiver sido alocada
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

TAB_tpCondRet ObterListaAmeacantes(TAB_ppAncoraTabuleiro pTabuleiro, int i, char j, LIS_tppLista* pLista);

/***********************************************************************
*
*  $FC Fun��o: TAB  &Obter Lista Ameacados
*
*  $ED Descri��o da fun��o
*     Obtem a Lista de elementos que ameacam aquela casa
*
*  $EP Par�metros
*     pTabuleiro		- cabe�a do tabuleiro a ser destruido
*	  i					- coordenada para a linha
*	  j					- coordenada para a coluna
*     pLista		    - ponteiro para a lista ameacantes a ser obtida
*
*
*  	$FV Valor retornado
*	CondRetOK, se lista foi retornada por referencia,
*	CondRetNaoAchou, se posicao for fora do tabuleiro
*	CondRetPonteiroNulo, se a ancora estiver vazia
*	CondRetFaltouMemoria, se alguma estrutura nao tiver sido alocada
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

TAB_tpCondRet ObterListaAmeacados(TAB_ppAncoraTabuleiro pTabuleiro, int i, char j, LIS_tppLista* pLista);

/***********************************************************************
*
*  $FC Fun��o: TAB  &Destruir Tabuleiro
*
*  $ED Descri��o da fun��o
*     Destroi o tabuleiro  
*
*  $EP Par�metros
*     pTabuleiro - cabe�a do tabuleiro a ser destruido
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

TAB_tpCondRet TAB_DestruirTabuleiro(TAB_ppAncoraTabuleiro pTabuleiro);

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
*     ppTabuleiro - cabe�a do tabuleiro a ser destruido
*	  tam		  - tamanho do tabuleiro quadrado (tam*tam) a ser criado	
*
*  $FV Valor retornado
*	  CondRetOK, se lista foi retornada por referencia,
*	  CondRetInvalido, se o tamanho fornecido for invalido
*     CondRetPonteiroNulo, se a ancora estiver vazia
*	  CondRetFaltouMemoria, se alguma estrutura nao tiver sido alocada
*
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*	$AE - Assertivas de entrada
*	- Recebe o endere�o de uma cabe�a de matriz a ser preenchida
*	$AS - Assertivas de sa�da:
*	- Valem todas as assertivas de estruturais de lista
*	- Ponteiro agora foi preenchido para a estrutura criada, que � uma matriz composta por listas ( com 8 linhas e 8 colunas )
***********************************************************************/

TAB_tpCondRet TAB_CriaTabuleiro(TAB_ppAncoraTabuleiro* ppTabuleiro, int tam);

/***/

TAB_tpCondRet TAB_ChecarPosicaoValida(int i, char j);

TAB_tpCondRet TAB_DefinirPosCorrente(TAB_ppAncoraTabuleiro pTabuleiro, int i, char j);

TAB_tpCondRet TAB_ObterPosCorrente(TAB_ppAncoraTabuleiro pTabuleiro, int* i, char* j);

TAB_tpCondRet TAB_AtribuirValorCorrente(TAB_ppAncoraTabuleiro pTabuleiro, TAB_tppCasa pCasa);

TAB_tpCondRet TAB_ObterPecaCorrente(TAB_ppAncoraTabuleiro pTabuleiro, void** pPeca, int* cor);

TAB_tpCondRet TAB_DesfazerMovimento(TAB_ppAncoraTabuleiro pTabuleiro, int iOrig, char jOrig, int iDest, char jDest, void** pPecaComida);

TAB_tpCondRet AdicionarListaAmeacantesAmeacados(TAB_ppAncoraTabuleiro pTabuleiro, int iAmeacante, char jAmeacante, int iAmeacado, char jAmeacado);











#undef TABULEIRO_EXT

/********** Fim do m�dulo de defini��o: TAB  Tabuleiro **********/

#else
#endif