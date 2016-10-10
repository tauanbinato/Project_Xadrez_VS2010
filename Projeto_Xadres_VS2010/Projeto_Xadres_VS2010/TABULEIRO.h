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
*     insere Peça por referencia na casa passada
*
*  $EP Parâmetros
*     cabeca_TAB		- cabeça do tabuleiro a ser inserida
*	  cord_linha		- coordenada para a linha
*	  cord_coluna		- coordenada para a coluna
*	  peca_PEC			- ponteiro pra void de uma peca
*
*  $FV Valor retornado
*     Se executou corretamente retorna a condição de retorno LIS_CondRetOK.
*
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
*	$AE - Assertivas de entrada
*	- Recebe número da linha e da coluna válidos (menores ou iguais a 8)
*	- A posição da casa no encontro da linha com a coluna está vazia
*	- Tabuleiro já foi criado
*	- Recebe cor valida (‘P’ ou ‘B’) e identidade (string de 4 caracteres)
*	$AS - Assertivas de saída:
*	- Peça foi criada e inserida na posição desejada do tabuleiro
*
***********************************************************************/

TAB_tpCondRet TAB_InserirPeca(TAB_ppAncoraTabuleiro cabeca_TAB, int cord_linha, int cord_coluna, void** peca_PEC);

/***********************************************************************
*
*	$FC Funçao: TAB &MoverPeca 
* 
*	$ED Descrição da função:
*	Esta função deverá mover a peça recebida para a posição desejada no tabuleiro
*	
*	$EP Parâmetros
*	- Coordenadas de origem e destino
*
*	$AE - Assertivas de entrada
*	- Peça já foi criada, com suas informações preenchidas ( e não é vazia )
*	- Posição para qual ela vai se mover está vazia, além de ser uma posição valida (contida dentro do tabuleiro)
*	- Movimento é permitido para aquela peça
*	- Tabuleiro já foi criado
*	$AS - Assertivas de saída:
*	- Peca agora está na posição desejada
*	- Sua posição antiga agora está vazia (‘V’)
*
***********************************************************************/

TAB_tpCondRet TAB_MoverPeca(TAB_ppAncoraTabuleiro cabeca_TAB, int xOrg, int yOrg, int xDest, int yDest);

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
*	$AE - Assertivas de entrada
*	- Existe uma peça na coordenada enviada
*	- Tabuleiro existe
*	$AS - Assertivas de saída:
*	- Peça foi retirada
*	- Posição (casa) que ela estava agora está vazia
*
***********************************************************************/

TAB_tpCondRet TAB_RetirarPeca(TAB_ppAncoraTabuleiro cabeca_TAB, int cord_linha, int cord_coluna);

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
*	$AE - Assertivas de entrada
*	- Tabuleiro está criado
*	- Posição enviada é válida
*	- Ponteiro a ser preenchido é do mesmo tipo estrutural que peça
*	$AS - Assertivas de saída:
*	- Ponteiro agora contem informação sobre a peça que estava na posição inserida (pode ser uma peça ou ‘V’-vazio)
***********************************************************************/

TAB_tpCondRet TAB_ObterPeca(TAB_ppAncoraTabuleiro cabeca_TAB, int cord_linha, int cord_coluna, void** peca);

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
*	$AE - Assertivas de entrada
*	- Recebe índice de linha e coluna válidos (menores ou igual a 8)
*	- Tabuleiro tem que estar criado e preenchido (com vazios ou com peças)
*	$AS - Assertivas de saída:
*	- Valem assertivas estruturais de lista
*	- Foi obtido a lista ameaçantes que estava na posição dos índices recebidos
***********************************************************************/

TAB_tpCondRet TAB_ObterListaAmeacantes(TAB_ppAncoraTabuleiro cabeca_TAB, int linha, int coluna, LIS_tppLista * pListaAmeacantes);

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
*	$AE - Assertivas de entrada
*	- Recebe índice de linha e coluna válidos (menores ou igual a 8)
*	- Tabuleiro tem que estar criado e preenchido (com vazios ou com peças)
*	$AS - Assertivas de saída:
*	Valem assertivas estruturais de lista
*	- Foi obtido a lista ameaçados que estava na posição dos índices recebidos
*	 
***********************************************************************/

TAB_tpCondRet TAB_ObterListaAmeacados(TAB_ppAncoraTabuleiro cabeca_TAB, int linha, int coluna, LIS_tppLista * pListaAmeacados);

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
*	$AE - Assertivas de entrada
*	- Recebe o endereço da cabeça do tabuleiro (já criado)
*	$AS - Assertivas de saída:
*	- Tabuleiro foi destruído, e todos seus componentes também. Além disso, toda a memória alocada antes por ele e seus componentes foram liberadas
***********************************************************************/

TAB_tpCondRet TAB_DestruirTabuleiro(TAB_ppAncoraTabuleiro cabeca_TAB);

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
*	$AE - Assertivas de entrada
*	- Recebe o endereço de uma cabeça de matriz a ser preenchida
*	$AS - Assertivas de saída:
*	- Valem todas as assertivas de estruturais de lista
*	- Ponteiro agora foi preenchido para a estrutura criada, que é uma matriz composta por listas ( com 8 linhas e 8 colunas )
***********************************************************************/

TAB_tpCondRet TAB_CriaTabuleiro(TAB_ppAncoraTabuleiro *cabeca_TAB, int *lado_linhas, int *lado_colunas);



#undef TABULEIRO_EXT

/********** Fim do módulo de definição: TAB  Tabuleiro **********/

#else
#endif