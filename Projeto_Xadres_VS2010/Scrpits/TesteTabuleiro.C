/***************************************************************************
*  $MCI M�dulo de implementa��o: TLIS Teste lista de s�mbolos
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor      Data         Observa��es
*     5       lp,ja, tb 28/set/2016   altera��o de fun��es e edi��o do scrpit de teste
*     4       avs       01/fev/2006   criar linguagem script simb�lica
*     3       avs       08/dez/2004   uniformiza��o dos exemplos
*     2       avs       07/jul/2003   unifica��o de todos os m�dulos em um s� projeto
*     1       avs       16/abr/2003   in�cio desenvolvimento
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

/**************************COMANDOS SCRIPT**************************/  

static const char CRIAR_TABULEIRO_CMD[]	       =				"=criartabuleiro"      ;
static const char MOVER_PECA_CMD[]			   =				"=moverpeca"           ;
static const char OBTER_PECA_CMD[]			   =				"=obterpeca"		   ;
static const char DESTRUIR_TABULEIRO_CMD[]     =				"=destruirtabuleiro"   ;
static const char INSERIR_PECA_CMD[]		   =				"=inserirpeca"         ;
static const char RETIRAR_PECA_CMD[]           =                "=retirarpeca"         ;
static const char RESET_LISTA_CMD[]			   =				"=resetteste"          ;
static const char OBTER_LISTA_AMEACANTES_CMD[] =				"=obterlistaameacantes";
static const char OBTER_LISTA_AMEACADOS_CMD[]  =				"=obterlistaameacados" ;

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


/***** Prot�tipos das fun��es encapuladas no m�dulo *****/
// void DestruirValor( void * pValor );
static int ValidarInxLista(int inxLista, int Modo);
static int ValidarInxMatriz(int inxLista, int Modo);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TLIS &Testar jogo
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 10 listas, identificadas pelos �ndices 0 a 10
*
*     Comandos dispon�veis:
*
*     =resetteste                   - anula o vetor de listas. Provoca vazamento de mem�ria
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
	int  cord_linha, cord_coluna;
	char cord_coluna_char;



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


	/* Testar DestruirTabuleiro */

	else if (strcmp(ComandoTeste, DESTRUIR_TABULEIRO_CMD) == 0)
	{
		//printf("\n%d", vtMatrizes[ inxMatriz ]);
		numLidos = LER_LerParametros("ii", &inxMatriz, &CondRetEsp);
		if ((numLidos != 2)
			|| (!ValidarInxMatriz(inxMatriz, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */
		printf("CRIAASDASD");

		CondRet_TAB = TAB_DestruirTabuleiro(vtMatrizes[inxMatriz]);

		printf("CRIAASDASD");
		return TST_CompararInt(CondRetEsp, CondRet_TAB,
			"Condicao de retorno errada ao destruir tabuleiro");

	} /* fim ativa: Testar DestruirTabuleiro */



	  /* Testar InserirPeca */

	else if (strcmp(ComandoTeste, INSERIR_PECA_CMD) == 0)
	{

		/* Declaracoes Necessarias */
		PEC_tppPeca  *peca_PEC;
		char id_peca , id_cor;
		

		numLidos = LER_LerParametros("iiccci", &inxMatriz,&cord_linha,&cord_coluna_char, &id_peca,&id_cor,  &CondRetEsp);
		cord_coluna = (int)(cord_coluna_char - 'a');
		if ((numLidos != 6) || (!ValidarInxMatriz(inxMatriz, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} 

		/*Parte da Tabuleiro*/
		PEC_criaPeca(&peca_PEC);

		PEC_insereValorEmPeca(&peca_PEC, &id_peca, &id_cor);
		
		CondRet_TAB = TAB_InserirPeca(vtMatrizes[inxMatriz] , cord_linha , cord_coluna ,(void**)peca_PEC );

		return TST_CompararInt(CondRetEsp, CondRet_TAB,"Condicao de retorno errada ao inserir Peca");

	} 
	/* fim ativa: Testar Inserir Peca */


	/* Testar Retirar Peca */
	else if (strcmp(ComandoTeste, RETIRAR_PECA_CMD) == 0)
	{
		/* Declaracoes Necessarias */
		PEC_tppPeca  *peca_PEC;

		numLidos = LER_LerParametros("iici", &inxMatriz, &cord_linha, &cord_coluna_char, &CondRetEsp) ;
		cord_coluna = (int)(cord_coluna_char - 'a');
		if ((numLidos != 4) || (!ValidarInxMatriz(inxMatriz, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		
		CondRet_TAB = TAB_RetirarPeca(vtMatrizes[inxMatriz], cord_linha, cord_coluna);

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
			return TST_CondRetParm;
		} /* if */

		CondRet_TAB = TAB_CriaTabuleiro(&vtMatrizes[inxMatriz], &lado_linhas , &lado_colunas);

		if (CondRet_TAB == 6) {

			return TST_CondRetMemoria;

		}

		return TST_CompararInt(CondRetEsp, CondRet_TAB,
			"Condicao de retorno errada ao criar tabuleiro");

	} /* fim ativa: Testar CriarTabuleiro */


	/*Inicio teste Obter Peca*/
	else if (strcmp(ComandoTeste, OBTER_PECA_CMD) == 0)
	{

		//Declaracoes
		PEC_tppPeca* peca_PEC;
		char id_peca, id_cor;


		numLidos = LER_LerParametros("iici", &inxMatriz, &cord_linha, &cord_coluna_char, &CondRetEsp);
		cord_coluna = (int)(cord_coluna_char - 'a');
		if ((numLidos != 4) || (!ValidarInxMatriz(inxMatriz, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

	
		PEC_criaPeca(&peca_PEC);
	
		CondRet_TAB = TAB_ObterPeca(vtMatrizes[inxMatriz], cord_linha, cord_coluna ,(void**)peca_PEC);
		PEC_obtemValoresdePeca(peca_PEC, &id_peca, &id_cor);
		
		if (CondRet_TAB == 6) {

			return TST_CondRetMemoria;

		}

		return TST_CompararInt(CondRetEsp, CondRet_TAB,
			"Condicao de retorno errada ao tentar obter peca de um tabuleiro");

	} /* fim ativa: Testar ObterPeca */

	/* Testar Obter Lista Ameacantes */
	else if (strcmp(ComandoTeste, OBTER_LISTA_AMEACANTES_CMD) == 0)
	{
		//LIS_tppLista Lista;
		int lado_linhas, lado_colunas;

		numLidos = LER_LerParametros("iicii", &inxMatriz, &cord_linha, &cord_coluna_char, &inxLista, &CondRetEsp);
		cord_coluna = (int)(cord_coluna_char - 'a');
		if ((numLidos != 5) || (!ValidarInxMatriz(inxMatriz, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */
		
		CondRet_TAB = TAB_ObterListaAmeacantes(vtMatrizes[inxMatriz], cord_linha, cord_coluna, &vtListas[inxLista] );

		return TST_CompararInt(CondRetEsp, CondRet_TAB,
			"Condicao de retorno errada ao obter lista ameacantes");

	} /* fim ativa: Testar ObterListaAmeacantes */

	/* Testar Obter Lista Ameacados */
	else if (strcmp(ComandoTeste, OBTER_LISTA_AMEACADOS_CMD) == 0)
	{
		//LIS_tppLista Lista;
		int lado_linhas, lado_colunas;

		numLidos = LER_LerParametros("iicii", &inxMatriz, &cord_linha, &cord_coluna_char, &inxLista, &CondRetEsp);
		cord_coluna = (int)(cord_coluna_char - 'a');

		if ((numLidos != 5) || (!ValidarInxMatriz(inxMatriz, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		CondRet_TAB = TAB_ObterListaAmeacados(vtMatrizes[inxMatriz], lado_linhas, lado_colunas, &vtListas[inxLista] );

		return TST_CompararInt(CondRetEsp, CondRet_TAB,
			"Condicao de retorno errada ao obter lista ameacados");

	} /* fim ativa: Testar ObterListaAmeacados */
	

	 /*Testar mover peca*/

	else if (strcmp(ComandoTeste, MOVER_PECA_CMD) == 0)
	{
		LIS_tppLista Lista;
		int xOrg , yOrg , xDes , yDes;
		char yCharDes, yCharOrg; 

		numLidos = LER_LerParametros("iiciccci", &inxMatriz,&xOrg,&yCharOrg,&xDes,&yCharDes,&id_corDest,&id_corOrg,&CondRetEsp);
		yOrg = (int)(yCharOrg - 'a');
		yDes = (int)(yCharDes- 'a');
		if (numLidos != 8)
		{
			return TST_CondRetParm;
		} /* if */

		CondRet_TAB = TAB_MoverPeca(vtMatrizes[inxMatriz], xOrg, yOrg, xDes, yDes,id_corDest,id_corOrg);
 
		return TST_CompararInt(CondRetEsp, CondRet_TAB,
			"Condicao de retorno errada ao mover peca");

	} /* fim ativa: Testar Mover Peca */


	} /* Fim fun��o: TJOG &Testar jogo*/



  /*****  C�digo das fun��es encapsuladas no m�dulo  *****/

  /***********************************************************************
  *
  *  $FC Fun��o: TLIS -Destruir valor
  *
  ***********************************************************************/

void DestruirValor(void * pValor)
{

	free(pValor);

} /* Fim fun��o: TLIS -Destruir valor */

  /***********************************************************************
  *
  *  $FC Fun��o: TLIS -Validar indice de lista
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

} /* Fim fun��o: TLIS -Validar indice de lista */

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

} /* Fim fun��o: TLIS -Validar indice de lista */

  /********** Fim do m�dulo de implementa��o: TLIS Teste lista de s�mbolos **********/

