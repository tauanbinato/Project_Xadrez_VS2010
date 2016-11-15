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
typedef struct TAB_tagCasa*	TAB_tppCasa;

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

	TAB_CondRetCasaVazia,
	/* A lista não contém elementos = 1 */

	TAB_CondRetFimLista,
	/* Foi atingido o fim de lista  = 2*/

	TAB_CondRetNaoAchou,
	/* Não encontrou o valor procurado = 3*/

	TAB_CondRetFaltouMemoria,
	/* Faltou memória ao tentar criar um elemento de lista = 4 */

	TAB_CondRetComeu,
	/*Peca foi comida = 5 */

	TAB_CondRetTabVazio,
	/*peca foi comida = 6 */

	TAB_CondRetNaoPermitido,
	/*movimento nao permitido = 7 */

	TAB_CondRetPonteiroNulo,
	/* Ponteiro passado é nulo = 8*/

	TAB_CondRetInvalido
	/* Informação passada não é valida = 9*/


} TAB_tpCondRet;

/***********************************************************************
*
*  $FC Função: TAB  &inserir Peça
*
*  $ED Descrição da função
*     insere Peça por referencia na casa passada
*
*  $EP Parâmetros
*     pTabuleiro		- cabeça do tabuleiro a ser inserida
*	  i					- coordenada para a linha
*	  j					- coordenada para a coluna
*	  pPeca 			- ponteiro pra void de uma peca
*	  cor				- cor do dono da peca
*
*	$FV Valor retornado
*	CondRetOK, se peça foi inserida, 
*   CondRetNaoAchou, se posicao for fora do tabuleiro
*	CondRetPonteiroNulo, se o tabuleiro passado estiver nulo
*	CondRetFaltouMemoria, se nao conseguir alocar a estrutura de casa
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
*	$AE - Assertivas de entrada
*	- Recebe número da linha e da coluna válidos (menores ou iguais a 8)
*	- A posição da casa no encontro da linha com a coluna está vazia
*	- Tabuleiro já foi criado
*	- Recebe cor valida (‘P’ ou ‘B’)
*	$AS - Assertivas de saída:
*	- Peça foi criada e inserida na posição desejada do tabuleiro
*
***********************************************************************/

TAB_tpCondRet TAB_InserirPeca(TAB_ppAncoraTabuleiro pTabuleiro, void* pPeca, int i, char j, int cor);

/***********************************************************************
*
*	$FC Funçao: TAB &MoverPeca 
* 
*	$ED Descrição da função:
*	Esta função deverá mover a peça recebida para a posição desejada no tabuleiro
*	
*	$EP Parâmetros
*	- Coordenadas de origem e destino e ancora do tabuleiro
*   PecaComida    - ponteiro duplo para void com a Peça Comida, se for o caso
*   jogadorComido - ponteiro para a cor da peça comida, se for o caso
*
*	$FV Valor retornado
*   CondRetNaoAchou, se o destino ou origem forem fora do tabuleiro
*   CondRetOK, se tiver executado o movimento com sucesso
*	CondRetFaltouMemoria, se alguma estrutura nao tiver sido alocada
*	CondRetPonteiroNulo, se a ancora estiver vazia
*
*	$AE - Assertivas de entrada
*	- Peça já foi criada, com suas informações preenchidas ( e não é vazia )
*	- Movimento é permitido para aquela peça
*	- Tabuleiro já foi criado
*
*	$AS - Assertivas de saída:
*	- Peca agora está na posição desejada
*	- Sua posição antiga agora está vazia 
*
***********************************************************************/

TAB_tpCondRet TAB_MoverPeca(TAB_ppAncoraTabuleiro pTabuleiro, char jOrig, int iOrig, char jDest, int iDest, void** PecaComida, char* jogadorComido);

/***********************************************************************
*
*  $FC Função: TAB  &Retirar Peça
*
*  $ED Descrição da função
*     Retira a peca que ocupa a coordenada passada
*
*  $EP Parâmetros
*     pTabuleiro		- cabeça do tabuleiro a ser retirada a peça
*	  i					- coordenada para a linha
*	  j					- coordenada para a coluna
*
*  $FV Valor retornado
*	CondRetOK, se peça foi retirada,
*	CondRetNaoAchou, se posicao for fora do tabuleiro
*	CondRetCasaVazia, se a casa estiver vazia
*	CondRetPonteiroNulo, se a ancora estiver vazia
*
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
*	$AE - Assertivas de entrada
*	- Existe uma peça na coordenada enviada
*
*	$AS - Assertivas de saída:
*	- Peça foi retirada
*	- Posição (casa) que ela estava agora está vazia
*
***********************************************************************/

TAB_tpCondRet TAB_RetirarPeca(TAB_ppAncoraTabuleiro pTabuleiro, int i, char j);

/***********************************************************************
*
*  $FC Função: TAB  &Obter Peça
*
*  $ED Descrição da função
*     Obtem a peca que ocupa a coordenada passada
*
*  $EP Parâmetros
*     pTabuleiro		- cabeça do tabuleiro a ser destruido
*	  i					- coordenada para a linha
*	  j					- coordenada para a coluna
*     pPeca 		    - ponteiro para void, que representa a peca a ser obtida
*     cor		        - ponteiro para a cor da peca a ser obtida
*
*	$FV Valor retornado
*	CondRetOK, se peça foi obtida, 
*	CondRetNaoAchou, se posicao for fora do tabuleiro
*	CondRetCasaVazia, se a casa estiver vazia
*	CondRetPonteiroNulo, se a ancora estiver vazia
*	CondRetFaltouMemoria, se alguma estrutura nao tiver sido alocada
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

TAB_tpCondRet TAB_ObterPeca(TAB_ppAncoraTabuleiro pTabuleiro, int i, char j, void** pPeca, char* cor);

/***********************************************************************
*
*  $FC Função: TAB  &Obter Lista Ameacantes
*
*  $ED Descrição da função
*     Obtem a Lista de Ameaçantes àquela casa
*
*  $EP Parâmetros
*     pTabuleiro		- cabeça do tabuleiro a ser destruido
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
*     Não será dada mais informação quanto ao problema ocorrido.
*	$AE - Assertivas de entrada
*	- Recebe índice de linha e coluna válidos (menores ou igual a 8)
*	- Tabuleiro tem que estar criado e preenchido (com vazios ou com peças)
*	$AS - Assertivas de saída:
*	- Valem assertivas estruturais de lista
*	- Foi obtido a lista ameaçantes que estava na posição dos índices recebidos
***********************************************************************/

TAB_tpCondRet ObterListaAmeacantes(TAB_ppAncoraTabuleiro pTabuleiro, int i, char j, LIS_tppLista* pLista);

/***********************************************************************
*
*  $FC Função: TAB  &Obter Lista Ameacados
*
*  $ED Descrição da função
*     Obtem a Lista de elementos que ameacam aquela casa
*
*  $EP Parâmetros
*     pTabuleiro		- cabeça do tabuleiro a ser destruido
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

TAB_tpCondRet ObterListaAmeacados(TAB_ppAncoraTabuleiro pTabuleiro, int i, char j, LIS_tppLista* pLista);

/***********************************************************************
*
*  $FC Função: TAB  &Destruir Tabuleiro
*
*  $ED Descrição da função
*     Destroi o tabuleiro  
*
*  $EP Parâmetros
*     pTabuleiro - cabeça do tabuleiro a ser destruido
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

TAB_tpCondRet TAB_DestruirTabuleiro(TAB_ppAncoraTabuleiro pTabuleiro);

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
*     ppTabuleiro - cabeça do tabuleiro a ser destruido
*	  tam		  - tamanho do tabuleiro quadrado (tam*tam) a ser criado	
*
*  $FV Valor retornado
*	  CondRetOK, se lista foi retornada por referencia,
*	  CondRetInvalido, se o tamanho fornecido for invalido
*     CondRetPonteiroNulo, se a ancora estiver vazia
*	  CondRetFaltouMemoria, se alguma estrutura nao tiver sido alocada
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
*	$AE - Assertivas de entrada
*	- Recebe o endereço de uma cabeça de matriz a ser preenchida
*	$AS - Assertivas de saída:
*	- Valem todas as assertivas de estruturais de lista
*	- Ponteiro agora foi preenchido para a estrutura criada, que é uma matriz composta por listas ( com 8 linhas e 8 colunas )
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

/********** Fim do módulo de definição: TAB  Tabuleiro **********/

#else
#endif