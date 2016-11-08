/***************************************************************************
*  $MCI Módulo de implementação: TLIS Teste lista de símbolos
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor      Data         Observações
*     5       lp,ja, tb 28/set/2016   alteração de funções e edição do scrpit de teste
*     4       avs       01/fev/2006   criar linguagem script simbólica
*     3       avs       08/dez/2004   uniformização dos exemplos
*     2       avs       07/jul/2003   unificação de todos os módulos em um só projeto
*     1       avs       16/abr/2003   início desenvolvimento
*
***************************************************************************/
#define _CRT_SECURE_NO_DEPRECATE

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Lista.h"
#include	"Tabuleiro.h"
#include    "Peca.h"
#include	"Casa.h"
#include	"CLASSE_PECA.H"

/**************************COMANDOS SCRIPT**************************/  

static const char CRIAR_CP_CMD[]	                =				"=criarcp"               ;
static const char DESTRUIR_CP_CMD[]			        =				"=destruircp"            ;
static const char ADICIONAR_MOVIMENTO_CMD[]		    =				"=adicionarmovimento"     ;
static const char CHECAR_MOVIMENTO_CMD[]            =				"=checarmovimento"       ;
static const char OBTER_MOVIMENTO_CMD[]             =                "=obtermovimento"       ;
static const char OBTER_NOME_CMD[]			        =				"=obternome"             ;
static const char RESET_LISTA_CMD[]					=				"=resetteste"			 ;

/************************FIM COMANDOS SCRIPT************************/


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VT_TAB	   10
#define DIM_VT_PEC	   10
#define DIM_VT_CPC     10
#define DIM_VALOR     100


LIS_tppLista            vtListas[DIM_VT_LISTA];
LIS_tppLista            vtListas_2[DIM_VT_LISTA];
TAB_ppAncoraTabuleiro	vtMatrizes[DIM_VT_TAB];
CPC_tppClassePeca       vtClasse[DIM_VT_CPC];

/***** Protótipos das funções encapuladas no módulo *****/
// void DestruirValor( void * pValor );
static int ValidarInxLista(int inxLista, int Modo);
static int ValidarInxMatriz(int inxLista, int Modo);

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar jogo
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste                   - anula o vetor de listas. Provoca vazamento de memória
*	  =criartabuleiro				inxLista  inxLista_2                                  CondRetEsp
*	  =destruirtabuleiro			inxLista			                                  CondRetEsp
*     =inserirpeca                  inxMatriz cordLinha   cordColuna   TipoPeca  CorPeca  CondRetEsp
*     =retirarpeca                  inxMatriz cordLinha   cordColuna                      CondRetEsp
*	  =obterpeca					inxMatriz cordLinha   cordColuna					  CondRetEsp
*	  =moverpeca					inxMatriz cordXorigem cordYorigem cordXdestino cordYdestino CorPecaDestino CorPecaorigem CondRetEsp
*	  =obterlistaameacantes			inxMatriz cordLinha   cordColuna	inxLista		  CondRetEsp
*	  =obterlistaameacados			inxMatriz cordLinha   cordColuna	inxLista		  CondRetEsp
***********************************************************************/

TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
{

	/*Inteiros*/
	int inxLista = -1,
		inxLista_2 = -1,
		numLidos = -1,
		CondRetEsp = -1,
		numElem = -1,
		ValEsp = -1,
		i,
		inxMatriz = -1;

	int  movI, movJ, idxMovimento;
	int* resposta;
	char nome;



	/*Condicoes de Retorno*/
	TST_tpCondRet CondRet;
	LIS_tpCondRet CondRet_LIS;
	TAB_tpCondRet CondRet_TAB;
	PEC_tpCondRet CondRet_PEC;
	CPC_tpCondRet CondRet_CPC;


	/*Strings*/
	char   StringDado[DIM_VALOR], StringDado_2[DIM_VALOR] , CharObtido;
	char* pDado;
	char  CharDado ;
	char* pCharDado;
	char* CharDado_2;
	char id_corDest;
	char id_corOrg;
	StringDado[0] = 0;


	/* Efetuar reset de teste de lista */

	if (strcmp(ComandoTeste, RESET_LISTA_CMD) == 0)
	{

		for (i = 0; i < DIM_VT_LISTA; i++)
		{
			vtListas[i] = NULL;
		} /* for */

		return TST_CondRetOK;

	} /* fim ativa: Efetuar reset de teste de lista */


	/* Testar DestruirClassePeca*/

	else if (strcmp(ComandoTeste, DESTRUIR_CP_CMD) == 0)
	{
		//printf("\n%d", vtMatrizes[ inxMatriz ]);
		numLidos = LER_LerParametros("ii", &inxMatriz, &CondRetEsp);
		if ((numLidos != 2)
			|| (!ValidarInxMatriz(inxMatriz, VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		CondRet_CPC = CPC_DestruirClassePeca(vtClasse[inxMatriz]);

		return TST_CompararInt(CondRetEsp, CondRet_CPC,
			"Condicao de retorno errada ao destruir classe");

	} /* fim ativa: Testar DestruirClassePeca */



	  /* Testar AdicionarMovimento */

	else if (strcmp(ComandoTeste, ADICIONAR_MOVIMENTO_CMD) == 0)
	{
		/* Declaracoes Necessarias */
		char id_peca , id_cor;
		

		numLidos = LER_LerParametros("iiii", &inxMatriz, &movI, &movJ, &CondRetEsp);

		if ((numLidos != 4) || (!ValidarInxMatriz(inxMatriz, VAZIO)))
		{
			return TST_CondRetParm;
		} 

		CondRet_CPC = CPC_AdicionarMovimento(&vtClasse[inxMatriz] , movI , movJ);
		printf("\n\t\t****ADICIONOU****");
		return TST_CompararInt(CondRetEsp, CondRet_CPC,"Condicao de retorno errada ao adicionar movimento");

	} 
	/* fim ativa: Testar AdicionarMovimento */

	  /* Testar CriarClassePeca */

	else if (strcmp(ComandoTeste, CRIAR_CP_CMD) == 0)
	{
	
		int lado_linhas, lado_colunas;
	
		numLidos = LER_LerParametros("icsi", &inxMatriz, &nome, &StringDado, &CondRetEsp);

		if ((numLidos != 4)
			|| (!ValidarInxMatriz(inxMatriz, VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		CondRet_CPC = CPC_CriarClassePeca(&vtClasse[inxMatriz], nome, StringDado);

		if (CondRet_CPC == 6) {

			return TST_CondRetMemoria;

		}

		return TST_CompararInt(CondRetEsp, CondRet_CPC,
			"Condicao de retorno errada ao criar classe de peca");

	} /* fim ativa: Testar CriarClassePeca */


	/*Inicio teste Obter Movimento*/
	else if (strcmp(ComandoTeste, OBTER_MOVIMENTO_CMD) == 0)
	{
		numLidos = LER_LerParametros("iii", &inxMatriz, &idxMovimento, &CondRetEsp);
		printf("\nidxMovimento: %d", idxMovimento);
		if ((numLidos != 3) || (!ValidarInxMatriz(inxMatriz, VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */
		printf("\nentrou");
		CondRet_CPC = CPC_ObterMovimento(&vtClasse[inxMatriz], idxMovimento, &movI, &movJ) ;
		printf("\nCondRet_CPC: %d", CondRet_CPC);
		printf("\nmovI obtido(teste): %d", movI);
		printf("\nmovJ obtido(teste): %d", movJ);
		if (CondRet_CPC == 6) {

			return TST_CondRetMemoria;

		}
		printf("\n\t\t****OBTEVE****");

		return TST_CompararInt(CondRetEsp, CondRet_CPC,
			"Condicao de retorno errada ao tentar obter movimento de classe de peca");

	} /* fim ativa: Testar ObterMovimento */

	/* Testar Obter Nome*/
	else if (strcmp(ComandoTeste, OBTER_NOME_CMD) == 0)
	{
		//LIS_tppLista Lista;
		int lado_linhas, lado_colunas;

		numLidos = LER_LerParametros("ici", &inxMatriz, &pCharDado, &CondRetEsp);

		if ((numLidos != 3) || (!ValidarInxMatriz(inxMatriz, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */
		
		CondRet_CPC = CPC_ObterNome(vtClasse[inxMatriz], pCharDado);

		return TST_CompararInt(CondRetEsp, CondRet_CPC,
			"Condicao de retorno errada ao obter lista ameacantes");

	} /* fim ativa: Testar ObterNome */

	 /*Testar ChecarMovimento*/

	else if (strcmp(ComandoTeste, CHECAR_MOVIMENTO_CMD) == 0)
	{

		numLidos = LER_LerParametros("iiiii", &inxMatriz, &movI, &movJ, resposta, &CondRetEsp);

		if (numLidos != 5)
		{
			return TST_CondRetParm;
		} /* if */

		CondRet_CPC = CPC_ChecarMovimento(vtClasse, movI, movJ, resposta);
 
		return TST_CompararInt(CondRetEsp, CondRet_CPC,
			"Condicao de retorno errada ao checar movimento");

	} /* fim ativa: TestarChecarMovimento */


	} /* Fim função: TJOG &Testar jogo*/



  /*****  Código das funções encapsuladas no módulo  *****/

  /***********************************************************************
  *
  *  $FC Função: TLIS -Destruir valor
  *
  ***********************************************************************/

void DestruirValor(void * pValor)
{

	free(pValor);

} /* Fim função: TLIS -Destruir valor */

  /***********************************************************************
  *
  *  $FC Função: TLIS -Validar indice de lista
  *
  ***********************************************************************/

int ValidarInxLista(int inxLista, int Modo)
{

	if ((inxLista <  0)
		|| (inxLista >= DIM_VT_LISTA))
	{
		return FALSE;
	} /* if */

	if (Modo == VAZIO)
	{
		if (vtListas[inxLista] != 0)
		{
			return FALSE;
		} /* if */


	}
	else
	{
		if (vtListas[inxLista] == 0)
		{
			return FALSE;
		} /* if */
	} /* if */

	return TRUE;

} /* Fim função: TLIS -Validar indice de lista */

int ValidarInxMatriz(int inxLista, int Modo)
{

	if ((inxLista <  0)
		|| (inxLista >= DIM_VT_LISTA))
	{
		return FALSE;
	} /* if */

	if (Modo == VAZIO)
	{
		if (vtMatrizes[inxLista] != 0)
		{
			return FALSE;
		} /* if */

	}
	else
	{
		if (vtMatrizes[inxLista] == 0)
		{
			return FALSE;
		} /* if */
	} /* if */

	return TRUE;

} /* Fim função: TLIS -Validar indice de lista */

  /********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/

