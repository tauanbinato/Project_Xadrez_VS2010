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

/**************************COMANDOS SCRIPT**************************/

static const char CRIAR_TABULEIRO_CMD[]	    =				"=criartabuleiro"      ;
static const char DESTRUIR_TABULEIRO_CMD[]  =				"=destruirtabuleiro"   ;
static const char INSERIR_PECA_CMD[]		=				"=inserirpeca"         ;
static const char RETIRAR_PECA_CMD[]        =               "=retirarpeca"         ;
static const char RESET_LISTA_CMD[]			=				"=resetteste"          ;
static const char CRIAR_LISTA_CMD[]			=				"=criarlista"          ;
static const char DESTROI_LISTA_CMD[]		=				"=destroilista"        ;
static const char INS_NO_CMD[]				=				"=inserirno"           ;
static const char OBTER_NO_CMD[]			=				"=obterno"             ;
static const char EXC_NO_CORRENTE_CMD[]	    =			    "=excluirnocorrente"   ;
static const char AVANCAR_ELEM_CMD[]		=				"=irprox"              ;
static const char VOLTAR_ELEM_CMD[]			=				"=irant"               ;
static const char OBTER_ID_LISTA_CMD[]      =			    "=obteridlista"        ;
static const char ALTERA_NO_CORRENTE_CMD[]  =		     	"=alterarnocorrente"   ;

/************************FIM COMANDOS SCRIPT************************/


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VT_TAB	   10
#define DIM_VT_PEC	   10
#define DIM_VALOR     100

LIS_tppLista            vtListas[DIM_VT_LISTA];
LIS_tppLista            vtListas_2[DIM_VT_LISTA];
TAB_ppAncoraTabuleiro	vtMatrizes[DIM_VT_TAB];


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
*     =criarlista                   inxLista  idLista                                     CondRetEsp
*     =obteridlista                 inxLista  idLista
*     =excluirnocorrente            inxLista
*     =irprox						inxLista                                              CondRetEsp
*     =irant						inxLista                                              CondRetEsp
*     =alterarnocorrente			inxLista  char                                        CondRetEsp
*     =destroilista                 inxLista                                              CondRetEsp
*     ==inserirno                   inxLista  char                                        CondRetEsp
*     =obterno                      inxLista  char                                        CondRetEsp
*     =excluirelem                  inxLista                                              CondRetEsp
*	  =criartabuleiro				inxLista  inxLista_2                                  CondRetEsp
*	  =destruirtabuleiro			inxLista			                                  CondRetEsp
*     =inserirpeca                  inxMatriz cordLinha  cordColuna   idPeca  idCor       CondRetEsp
*     =retirarpeca                  inxMatriz cordLinha  cordColuna                       CondRetEsp
*
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
	int  cord_linha , cord_coluna;



	/*Condicoes de Retorno*/
	TST_tpCondRet CondRet;
	LIS_tpCondRet CondRet_LIS;
	TAB_tpCondRet CondRet_TAB;
	PEC_tpCondRet CondRet_PEC;


	/*Strings*/
	char   StringDado[DIM_VALOR], StringDado_2[DIM_VALOR] , CharObtido;
	char* pDado;
	char  CharDado ;
	char* pCharDado;
	char* CharDado_2;
	//char* id_peca;
	//char* id_cor;
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


	/* Testar DestruirTabuleiro */

	else if (strcmp(ComandoTeste, DESTRUIR_TABULEIRO_CMD) == 0)
	{
		printf("\n%d", vtMatrizes[ inxMatriz ]);
		numLidos = LER_LerParametros("ii", &inxMatriz, &CondRetEsp);
		if ((numLidos != 2)
			|| (!ValidarInxMatriz(inxMatriz, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		printf("\nentrou");
		CondRet_TAB = destruirTabuleiro(vtMatrizes[inxMatriz]);
		printf("\nsaiu");

		if (CondRet_TAB == 6) {

			return TST_CondRetMemoria;

		}

		return TST_CompararInt(CondRetEsp, CondRet_TAB,
			"Condicao de retorno errada ao destruir tabuleiro");

	} /* fim ativa: Testar DestruirTabuleiro */



	  /* Testar InserirPeca */

	else if (strcmp(ComandoTeste, INSERIR_PECA_CMD) == 0)
	{

		/* Declaracoes Necessarias */
		PEC_tppPeca  *peca_PEC;
		char id_peca , id_cor;
		

		numLidos = LER_LerParametros("iiicci", &inxMatriz,&cord_linha,&cord_coluna, &id_peca,&id_cor,  &CondRetEsp);

		if ((numLidos != 6) || (!ValidarInxMatriz(inxMatriz, NAO_VAZIO)))
		{
			printf("Entrou");
			return TST_CondRetParm;
		} 

		printf("\nRecebe do script: %d %d %d %c %c %d\n",inxMatriz , cord_linha , cord_coluna , id_peca , id_cor , CondRetEsp);

		/*Parte da Tabuleiro*/
		PEC_criaPeca(&peca_PEC);
		PEC_insereValorEmPeca(&peca_PEC, &id_peca, &id_cor);
		printf("b4 - %d", peca_PEC);
		CondRet_TAB = inserirPeca(vtMatrizes[inxMatriz] , cord_linha , cord_coluna , peca_PEC );
		
		if (CondRet_TAB == 6) {
			printf("Entrou");
			return TST_CondRetMemoria;
		}
		
		return TST_CompararInt(CondRetEsp, CondRet_TAB,"Condicao de retorno errada ao inserir valor em Peca");

	} 
	/* fim ativa: Testar Inserir Peca */


	/* Testar Retirar Peca */
	else if (strcmp(ComandoTeste, RETIRAR_PECA_CMD) == 0)
	{
		/* Declaracoes Necessarias */
		PEC_tppPeca  *peca_PEC;
		numLidos = LER_LerParametros("iiii", &inxMatriz, &cord_linha, &cord_coluna, &CondRetEsp) ;

		if ((numLidos != 4) || (!ValidarInxMatriz(inxMatriz, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */


		//printf(" retirar: recebe do script: %d %d %d %c %c %d\n", inxMatriz, cord_linha, cord_coluna, CondRetEsp);
		
		CondRet_TAB = retirarPeca(vtMatrizes[inxMatriz], cord_linha, cord_coluna);
		if (CondRet_TAB == 6) {

			return TST_CondRetMemoria ;
		}
		PEC_EsvaziaPeca( &peca_PEC );
		return TST_CompararInt(CondRetEsp, CondRet_TAB,
			"Condicao de retorno errada ao retirar peca");

	} /* fim ativa: Testar Retirar Peca */


	  /* Testar CriarTabuleiro */

	else if (strcmp(ComandoTeste, CRIAR_TABULEIRO_CMD) == 0)
	{

		int lado_linhas, lado_colunas;

		numLidos = LER_LerParametros("iiii", &inxMatriz,&lado_linhas,&lado_colunas, &CondRetEsp);

		if ((numLidos != 4)
			|| (!ValidarInxMatriz(inxMatriz, VAZIO)))
		{
			printf("\n%d\n", numLidos);
			printf("Entrou");
			return TST_CondRetParm;
		} /* if */

		printf("\nANTES: %p , %d %d", vtMatrizes[inxMatriz] , lado_linhas , lado_colunas);

		CondRet_TAB = cria_tabuleiro(&vtMatrizes[inxMatriz], &lado_linhas , &lado_colunas);
		
		printf("\nDEPOIS: %p", vtMatrizes[inxMatriz]);
		if (CondRet_TAB == 6) {

			return TST_CondRetMemoria;

		}

		return TST_CompararInt(CondRetEsp, CondRet_TAB,
			"Condicao de retorno errada ao criar tabuleiro");

	} /* fim ativa: Testar CriarTabuleiro */

	} /* Fim função: TLIS &Testar jogo*/


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

