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

static const char INICIALIZA_JOGO_CMD[] = "=inicializajogo";
static const char CARREGA_ARQUIVO_CMD[] = "=carregaarquivo";
static const char PREENCHE_TABULEIRO_CMD[] = "=preenchetabuleiro";
static const char IMPRIME_TABULEIRO_CMD[] = "=imprimetabuleiro";
static const char MOVE_PECA_CMD[] = "=movepeca";
static const char RESET_LISTA_CMD[] = "=resetteste";

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
CAS_tppCasa				vtCasas[DIM_VT_TAB];
PEC_tppPeca				vtPecas[DIM_VT_PEC];

/***********************************************************************
*
*  $TC Tipo de dados: PRI Descritor da cabeça de uma simulação
*
*
*  $ED Descrição do tipo
*     Armazena referências para o tabuleiro e para as cabeças das
*     listas de peças e classes de peças.
*
***********************************************************************/

typedef struct PRI_tagSimulacao {

	TAB_ppAncoraTabuleiro pTab;
	/* Ponteiro para o tabuleiro corrente */
	LIS_tppLista pListaPecas;
	/* Ponteiro para a lista de peças */
	LIS_tppLista pListaClasses;
	/* Ponteiro para a lista de classes de peças */

} PRI_tpSimulacao;

/*****  Variável global que armazena a simulação corrente  *****/

PRI_tpSimulacao simulacao;

void PRI_MenuPrincipal(int * opcao);
void PRI_PreencheTabuleiro();
void PRI_ImprimirTabuleiro();
int PRI_CarregarArquivoMovimento(char* path);
void PRI_Inicializa();
int PRI_ChecarMovimentoPulo(int movI, int movJ);
int PRI_ChecarLegalidade(char jogador, char iOrigem, int jOrigem, char iDestino, int jDestino);
void PRI_ChecarChequeMate(char jogador);
int PRI_ChecarAmeacaRei(char jogador);
PEC_tppPeca PRI_ObterRei(char* j, int* i, char jogador);
CPC_tppClassePeca PRI_BuscaClassePeca(char classeProcurada);
void PRI_insereTorre(char corJogador, int posicao);
void PRI_insereCavalo(char corJogador, int posicao);
void PRI_insereBispo(char corJogador, int posicao);
void PRI_insereRainha(char corJogador, int posicao);
void PRI_insereRei(char corJogador, int posicao);
void PRI_MoverPeca(int iOrigem, char jOrigem, int iDestino, char jDestino);
int PRI_ChecarMovimentoLegal(int iOrigem, char jOrigem, int iDestino, char jDestino);
int PRI_ChecarLegalidadePeao(int iOrigem, int movI, int movJ, int iDest, char jDest, PEC_tppPeca pPeca);

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
		inxMatriz = -1,
		inxCasa = -1,
		inxPeca = -1;

	int  movI, movJ, idxMovimento, iOrigem, iDestino;
	int* resposta;
	char nome, jOrigem, jDestino;


	/*Condicoes de Retorno*/
	TST_tpCondRet CondRet;
	LIS_tpCondRet CondRet_LIS;
	TAB_tpCondRet CondRet_TAB;
	PEC_tpCondRet CondRet_PEC;
	CPC_tpCondRet CondRet_CPC;
	CAS_tpCondRet CondRet_CAS;


	/*Strings*/
	char   StringDado[DIM_VALOR], StringDado_2[DIM_VALOR], CharObtido;
	char* pDado;
	char  CharDado;
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


	else if (strcmp(ComandoTeste, INICIALIZA_JOGO_CMD) == 0)
	{

		PRI_Inicializa( );

		return;
	} /* fim ativa: Efetuar inicializaçao das estruturas da simulacao da partida */

	else if (strcmp(ComandoTeste, CARREGA_ARQUIVO_CMD) == 0)
	{
		numLidos = LER_LerParametros("s", &StringDado);

		if ((numLidos != 1))
		{
			return TST_CondRetParm;
		} /* if */

		if (!PRI_CarregarArquivoMovimento(StringDado))          
			return TST_CondRetNaoExecutou;

		return TST_CondRetOK;
	} /* fim ativa: Efetuar carregamento de arquivo contendo movimentos de pecas */

	else if (strcmp(ComandoTeste, IMPRIME_TABULEIRO_CMD) == 0)
	{

		PRI_ImprimirTabuleiro( );

		return TST_CondRetOK;
	} /* fim ativa: Efetuar impressao do tabuleiro */

	else if (strcmp(ComandoTeste, PREENCHE_TABULEIRO_CMD) == 0)
	{

		PRI_PreencheTabuleiro();

		return TST_CondRetOK;
	} /* fim ativa: Efetuar preenchimento do tabuleiro */


	else if (strcmp(ComandoTeste, MOVE_PECA_CMD) == 0)
	{
		numLidos = LER_LerParametros("icic", &iOrigem, &jOrigem, &iDestino, &jDestino);

		if ((numLidos != 4))
		{
			return TST_CondRetParm;
		} /* if */

		PRI_MoverPeca(iOrigem, jOrigem, iDestino, jDestino);

		return TST_CondRetOK;
	} /* fim ativa: Efetuar movimentacao de uma peca */


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

void PRI_ImprimirTabuleiro() {
	int linha;
	int coluna;

	printf("\n\n");
	for (coluna = 0; coluna < 8; coluna++) {
		printf("  %c  ", coluna + 'A');
	}
	printf("\n  ");
	for (coluna = 0; coluna <8; coluna++) {
		printf(" ___ ");
	}
	printf("\n");
	for (linha = 0; linha< 8; linha++) {
		printf("%d ", linha);
		for (coluna = 0; coluna <8; coluna++) {
			PEC_tppPeca pPeca;
			CPC_tppClassePeca ClassePeca;
			char nome;
			char cor;

			if (TAB_ObterPeca(simulacao.pTab, linha, (char)(coluna + 'A'), (void*)&pPeca, &cor) == TAB_CondRetCasaVazia) {
				printf("|   |");
			}
			else {
				PEC_ObterCorDePeca(pPeca, &cor);
				PEC_ObterClasseDePeca(pPeca, &ClassePeca);
				CPC_ObterNome(ClassePeca, &nome);
				printf("| %c |", nome);
				pPeca = NULL;
			}
		}
		printf("\n  ");
		for (coluna = 0; coluna <8; coluna++) {
			printf("|___|");
		}
		printf("\n");
	}
}

void PRI_PreencheTabuleiro() {
	int i;
	PEC_tppPeca pPeca;
	char nome, cor;

	//inserir peoes brancos
	CPC_tppClassePeca pClassePeca;

	pClassePeca = PRI_BuscaClassePeca('P');

	//insere peoes brancos
	for (i = 0; i<8; i++)
	{
		PEC_criaPeca(&pPeca, pClassePeca, 'B');
		PEC_ObterCorDePeca(pPeca, &cor);
		TAB_InserirPeca(simulacao.pTab, (void**)pPeca, 6, (char)(i + 'A'), cor);
	}

	//insere peoes pretos
	for (i = 0; i<8; i++)
	{
		PEC_criaPeca(&pPeca, pClassePeca, 'P');
		PEC_ObterCorDePeca(pPeca, &cor);
		TAB_InserirPeca(simulacao.pTab, (void**)pPeca, 1, (char)(i + 'A'), cor);
	}

	PRI_insereTorre('B', 7);
	PRI_insereTorre('P', 0);

	PRI_insereCavalo('B', 7);
	PRI_insereCavalo('P', 0);

	PRI_insereBispo('B', 7);
	PRI_insereBispo('P', 0);

	PRI_insereRei('B', 7);
	PRI_insereRei('P', 0);

	PRI_insereRainha('B', 7);
	PRI_insereRainha('P', 0);


}
void PRI_insereTorre(char corJogador, int posicao) {
	PEC_tppPeca pPeca;
	char cor;
	CPC_tppClassePeca pClassePeca;

	pClassePeca = PRI_BuscaClassePeca('T');

	PEC_criaPeca(&pPeca, pClassePeca, corJogador);
	PEC_ObterCorDePeca(pPeca, &cor);
	TAB_InserirPeca(simulacao.pTab, (void**)pPeca, posicao, 'A', cor);
	PEC_criaPeca(&pPeca, pClassePeca, corJogador);
	PEC_ObterCorDePeca(pPeca, &cor);
	TAB_InserirPeca(simulacao.pTab, (void**)pPeca, posicao, 'H', cor);
}

void PRI_insereCavalo(char corJogador, int posicao) {
	PEC_tppPeca pPeca;
	char cor;
	CPC_tppClassePeca pClassePeca;

	pClassePeca = PRI_BuscaClassePeca('H');

	PEC_criaPeca(&pPeca, pClassePeca, corJogador);
	PEC_ObterCorDePeca(pPeca, &cor);
	TAB_InserirPeca(simulacao.pTab, (void**)pPeca, posicao, 'B', cor);
	PEC_criaPeca(&pPeca, pClassePeca, corJogador);
	PEC_ObterCorDePeca(pPeca, &cor);
	TAB_InserirPeca(simulacao.pTab, (void**)pPeca, posicao, 'G', cor);
}

void PRI_insereBispo(char corJogador, int posicao) {
	PEC_tppPeca pPeca;
	char cor;
	CPC_tppClassePeca pClassePeca;

	pClassePeca = PRI_BuscaClassePeca('B');

	PEC_criaPeca(&pPeca, pClassePeca, corJogador);
	PEC_ObterCorDePeca(pPeca, &cor);
	TAB_InserirPeca(simulacao.pTab, (void**)pPeca, posicao, 'C', cor);
	PEC_criaPeca(&pPeca, pClassePeca, corJogador);
	PEC_ObterCorDePeca(pPeca, &cor);
	TAB_InserirPeca(simulacao.pTab, (void**)pPeca, posicao, 'F', cor);
}

void PRI_insereRainha(char corJogador, int posicao) {
	PEC_tppPeca pPeca;
	char cor;
	CPC_tppClassePeca pClassePeca;

	pClassePeca = PRI_BuscaClassePeca('Q');

	PEC_criaPeca(&pPeca, pClassePeca, corJogador);
	PEC_ObterCorDePeca(pPeca, &cor);
	TAB_InserirPeca(simulacao.pTab, (void**)pPeca, posicao, 'E', cor);
}

void PRI_insereRei(char corJogador, int posicao) {
	PEC_tppPeca pPeca;
	char cor;
	CPC_tppClassePeca pClassePeca;

	pClassePeca = PRI_BuscaClassePeca('K');

	PEC_criaPeca(&pPeca, pClassePeca, corJogador);
	PEC_ObterCorDePeca(pPeca, &cor);
	TAB_InserirPeca(simulacao.pTab, (void**)pPeca, posicao, 'D', cor);
}

int PRI_CarregarArquivoMovimento(char* path) {

	char auxString[200], classe, jogador;
	int i, j;
	FILE *fp;
	CPC_tppClassePeca pClasse;
	PEC_tppPeca pPeca;

	fp = fopen(path, "r");
	if (fp == NULL) {
		printf("Path invalido.\n\n");
		return 0;
	}

	while (fscanf(fp, " %s", auxString) == 1) {
		if (strcmp(auxString, "CLASSE") == 0) {
			fscanf(fp, " %s", auxString);
			if (CPC_CriarClassePeca(&pClasse, auxString[0], auxString) != CPC_CondRetOK) {
				printf("Faltou memória.");
				exit(1);
			}/*if*/
			LIS_InserirNo(simulacao.pListaClasses, (void*)pClasse);

		}/*if*/
		else if (strcmp(auxString, "MOV") == 0) {
			fscanf(fp, " %d %d", &i, &j);
			if (CPC_AdicionarMovimento(pClasse, i, j) == CPC_CondRetFaltouMemoria)
			{
				printf("Faltou memória.");
				exit(1);
			}/*if*/

		}/*else if*/
	}/*while*/

	fclose(fp);
	return 1;
}


void PRI_Inicializa() {

	if (TAB_CriaTabuleiro(&(simulacao.pTab), 8) != TAB_CondRetOK)
	{
		printf("ERRO DE MEMORIA AO CRIAR TABULEIRO");
		exit(1);
	}


	if (LIS_CriarLista(&(simulacao.pListaClasses), "Classes") != 0)
	{
		TAB_DestruirTabuleiro(simulacao.pTab);
		printf("ERRO DE MEMORIA AO CRIAR LISTA DE CLASSES");
		exit(1);
	}

	if (LIS_CriarLista(&(simulacao.pListaPecas), "Pecas") != 0)
	{
		TAB_DestruirTabuleiro(simulacao.pTab);
		LIS_DestroiLista(simulacao.pListaClasses);
		printf("ERRO DE MEMORIA AO CRIAR LISTA DE PECAS");
		exit(1);
	}
}
int PRI_ChecarMovimentoPulo(int movI, int movJ)
{
	if (movI == movJ || movI == -movJ || movI == 0 || movJ == 0)
	{
		return 0;
	}

	return 1;
}

CPC_tppClassePeca PRI_BuscaClassePeca(char classeProcurada) {
	LIS_tpCondRet lisCondRet;
	CPC_tppClassePeca pClassePeca;
	char classeObtida;

	if (classeProcurada == NULL) {
		return NULL;
	}

	LIS_IrInicioLista(simulacao.pListaClasses);

	do {
		LIS_ObterNo(simulacao.pListaClasses, (CPC_tppClassePeca)&pClassePeca);

		if (pClassePeca != NULL) {
			CPC_ObterNome(pClassePeca, &classeObtida);

			if (classeObtida == classeProcurada) {
				return pClassePeca;
			}
		}

		lisCondRet = LIS_AvancarElementoCorrente(simulacao.pListaClasses, 1);
	} while (lisCondRet != LIS_CondRetFimLista && lisCondRet != LIS_CondRetListaVazia);

	return NULL;
}

int PRI_ChecarLegalidade(char jogador, char jOrigem, int iOrigem, char jDestino, int iDestino) {
	PEC_tppPeca defensor;
	char jogadorDefensor;
	PEC_tppPeca obstaculo;
	int movI, movJ;
	char j; int i;
	char coraux;

	movI = iDestino - iOrigem;
	movJ = jDestino - jOrigem;

	TAB_ObterPeca(simulacao.pTab, iDestino, jDestino, (void**)&defensor, &jogadorDefensor);
	//PEC_ObterCorDePeca(defensor, &jogadorDefensor);

	if ((jogador != 'B') && (jogador != 'P'))
		return 0;

	if (defensor != NULL)
	{
		PEC_ObterCorDePeca(defensor, &jogadorDefensor); //verifica se a cor da peca que esta ocupando a pos é a mesma (nao e permitido comer pecas do mesmo time)
		if (jogadorDefensor == jogador) {
			return 0;
		}
	}

	//
	if (PRI_ChecarMovimentoPulo(movI, movJ) == 1) {
		// Sendo um movimento de pulo, não há necessidade de checar obstáculos

		return 1;
	}

	// Não sendo um movimento de pulo, precisamos saber se há obstáculos.

	if (movJ == 0) {
		if (movI > 0) {
			// movimento de letra crescente
			j = jOrigem; // = jDestino;

			for (i = iOrigem + 1; i < iDestino; i++) {
				if (TAB_ObterPeca(simulacao.pTab, i, j, (void**)&obstaculo, &coraux) == TAB_CondRetOK) {
					return 0;
				}
			}

			return 1;
		}
		if (movI < 0) {
			// movimento de letra decrescente
			j = jOrigem; // = jDestino;

			for (i = iOrigem - 1; i > iDestino; i--) {
				if (TAB_ObterPeca(simulacao.pTab, i, j, (void**)&obstaculo, &coraux) == TAB_CondRetOK) {
					return 0;
				}
			}

			return 1;
		}
	}

	if (movI == 0) {
		if (movJ > 0) {
			// movimento de numero crescente
			i = iOrigem; // = iDestino;

			for (j = jOrigem + 1; j < jDestino; j++) {
				if (TAB_ObterPeca(simulacao.pTab, i, j, (void**)&obstaculo, &coraux) == TAB_CondRetOK) {
					return 0;
				}
			}

			return 1;
		}
		if (movJ < 0) {
			// movimento de numero decrescente
			i = iOrigem; // = iDestino;

			for (j = jOrigem - 1; j > jDestino; j--) {
				if (TAB_ObterPeca(simulacao.pTab, i, j, (void**)&obstaculo, &coraux) == TAB_CondRetOK) {
					return 0;
				}
			}

			return 1;
		}
	}

	if (movJ > 0) {
		if (movI > 0) {
			// movimento de letra e numero crescente
			for (i = iOrigem + 1, j = jOrigem + 1; i < iDestino && j < jDestino; i++, j++) {
				if (TAB_ObterPeca(simulacao.pTab, i, j, (void**)&obstaculo, &coraux) == TAB_CondRetOK) {
					return 0;
				}
			}

			return 1;
		}
		else {
			//movimento de letra crescente e numero decrescente
			for (i = iOrigem - 1, j = jOrigem + 1; i > iDestino && j < jDestino; i--, j++) {
				if (TAB_ObterPeca(simulacao.pTab, i, j, (void**)&obstaculo, &coraux) == TAB_CondRetOK) {
					return 0;
				}
			}

			return 1;
		}
	}

	else {
		if (movI > 0) {
			// movimento de letra decrescente e numero crescente
			for (i = iOrigem + 1, j = jOrigem - 1; i < iDestino && j > jDestino; i++, j--) {
				if (TAB_ObterPeca(simulacao.pTab, i, j, (void**)&obstaculo, &coraux) == TAB_CondRetOK) {
					return 0;
				}
			}

			return 1;
		}
		else {
			// movimento de letra e numero decrescente
			for (i = iOrigem - 1, j = jOrigem - 1; i > iDestino && j > jDestino; i--, j--) {
				if (TAB_ObterPeca(simulacao.pTab, i, j, (void**)&obstaculo, &coraux) == TAB_CondRetOK) {
					return 0;
				}
			}

			return 1;
		}
	}

	return 1;
}

int PRI_ChecarMovimentoLegal(int iOrigem, char jOrigem, int iDestino, char jDestino) {
	PEC_tppPeca pPeca;
	char classe;
	CPC_tppClassePeca pClassePeca;
	int movI, movJ, resposta = 0;

	//Buscar classe na simulação
	TAB_ObterPeca(simulacao.pTab, iOrigem, jOrigem, &pPeca, &classe);
	//PEC_ObterCharClasseDePeca(pPeca, &classe);
	pClassePeca = PRI_BuscaClassePeca(classe);

	//Verificar se o movimento consta la (destino - origem)
	movI = iDestino - iOrigem;
	movJ = jDestino - jOrigem;

	//Checar legalidade movimento de peão
	if (classe == 'P')
		return PRI_ChecarLegalidadePeao(iOrigem, movI, movJ, iDestino, jDestino, pPeca);

	CPC_ChecarMovimento(pClassePeca, movI, movJ, &resposta);

	if (resposta)
		return 1;
	else
		return 0;

}

int PRI_ChecarLegalidadePeao(int iOrigem, int movI, int movJ, int iDest, char jDest, PEC_tppPeca pPeca) {
	char cor;
	TAB_tppCasa pCasaOrig, pCasaDest;

	//Obter cor da peca
	PEC_ObterCorDePeca(pPeca, &cor);

	//Checar duplo movimento inicial
	if (iOrigem == 1 || iOrigem == 6) {
		if ((movI == -2 && movJ == 0) || (movI == 2 && movJ == 0)) {
			return 1;
		}
	}

	//Obter casa destino
	TAB_DefinirPosCorrente(simulacao.pTab, iDest, jDest);

	TAB_ObterValorCorrente(simulacao.pTab, &pCasaDest);

	//Checar movimento exclusivo de cor
	if (cor == 'B') {
		if ((movI == -1 && movJ == 0)) {
			if (pCasaDest == NULL)
				return 1;
		}
		if ((movI == -1 && movJ == 1) || (movI == -1 && movJ == -1)) {
			if (pCasaDest != NULL) {
				return 1;
			}
		}
	}

	if (cor == 'P') {
		if ((movI == 1 && movJ == 0)) {
			if (pCasaDest == NULL)
				return 1;
		}
		if ((movI == 1 && movJ == 1) || (movI == 1 && movJ == -1)) {
			if (pCasaDest != NULL) {
				return 1;
			}
		}
	}

	return 0;

}

void PRI_MoverPeca(int iOrigem, char jOrigem, int iDestino, char jDestino) {
	int legalidade = 0, movLegal, pecaObtida;
	char cor, *jogadorComido;
	PEC_tppPeca pPeca, PecaComida;

	pecaObtida = TAB_ObterPeca(simulacao.pTab, iOrigem, jOrigem, &pPeca, &cor);

	movLegal = PRI_ChecarMovimentoLegal(iOrigem, jOrigem, iDestino, jDestino);

	//Checar legalidade do movimento
	if (movLegal) {
		if (PRI_ChecarLegalidade(cor, jOrigem, iOrigem, jDestino, iDestino) == 0)
			printf("\nMovimento ilegal. Insira um movimento valido");
		else {
			TAB_MoverPeca(simulacao.pTab, jOrigem, iOrigem, jDestino, iDestino, (void**)&PecaComida, &jogadorComido);
			legalidade = 1;
		}

	}
	else {
		if (pecaObtida == 9)
			printf("\nCoordenada de ORIGEM invalida.");
		printf("\nA Peca nao realiza este movimento. Insira um movimento valido\n");
	}
}
//}
//Mover de fato

/*void PRI_ChecarChequeMate(char jogador) {
	char reiJ;
	int reiI;
	PEC_tppPeca rei;

	int* jogadorComido;
	int i, iDest;
	char j, jDest;
	PEC_tppPeca pecaAtual, pPecaComida;
	char jogadorPecaAtual;
	CPC_tppClassePeca tipoPecaAtual;

	int nMovs, c, movI, movJ, ameaca, legalidade;

	rei = PRI_ObterRei(&reiJ, &reiI, jogador);
	if (rei == NULL) {
		printf("Nao foi encontrado nenhum rei no tabuleiro.");
		return;
	}
	if (PRI_ChecarAmeacaRei(jogador) == 0) {
		printf("Nao ha cheque-mate, nem cheque. (O rei nao esta ameacado)");
		return;
	}

	for (i = 0; i <= 7; i++) {
		for (j = 'A'; j <= 'H'; j++) {
			TAB_ObterPeca(simulacao.pTab, i, j, (void**)&pecaAtual, &jogadorPecaAtual);

			if (pecaAtual != NULL) {

				if (jogadorPecaAtual == jogador) {
					PEC_ObterClasseDePeca(pecaAtual, &tipoPecaAtual);

					if (tipoPecaAtual == NULL) {
						printf("Erro: peca com tipo nulo.");
						exit(1);
					}

					CPC_ObterNumeroMovimentos(tipoPecaAtual, &nMovs);

					for (c = 0; c < nMovs; c++) {
						CPC_ObterMovimento(tipoPecaAtual, c, &movI, &movJ);

						iDest = i + movI;
						jDest = j + movJ;

						if (TAB_ChecarPosicaoValida(iDest, jDest) == TAB_CondRetOK) {

							legalidade = PRI_ChecarLegalidade(jogadorPecaAtual, j, i, jDest, iDest);
							if (legalidade == 1) {

								TAB_MoverPeca(simulacao.pTab, j, i, jDest, iDest, &pPecaComida, &jogadorComido);

								ameaca = PRI_ChecarAmeacaRei(jogador);

								TAB_DesfazerMovimento(simulacao.pTab, i, j, iDest, jDest, pPecaComida);

								if (ameaca == 0) {
									printf("O jogador %c esta em cheque, mas nao em cheque-mate.\n"
										"Movimento: %c%d para %c%d.", jogador, j, i, jDest, iDest);
									return;
								}
							}
						}
					}
				}
			}
		}
	}

	printf("O jogador branco esta em cheque-mate.");

	return;
}


int PRI_ChecarAmeacaRei(char jogador) {
	int reiI; char reiJ;
	PEC_tppPeca rei, pecaAtual;
	CPC_tppClassePeca classePecaAtual;

	char jogadorPecaAtual;
	int i;
	char j;
	int movI, movJ, resposta, legalidade;

	rei = PRI_ObterRei(&reiJ, &reiI, jogador);
	if (rei == NULL) {
		printf("Nao foi encontrado nenhum rei da cor buscada no tabuleiro.");
		return 0;
	}

	for (i = 0; i <= 7; i++) {
		for (j = 'A'; j <= 'H'; j++) {
			if (TAB_ObterPeca(simulacao.pTab, i, j, (void**)&pecaAtual, &jogadorPecaAtual) == TAB_CondRetOK) {

				if (jogadorPecaAtual != jogador) {
					PEC_ObterClasseDePeca(pecaAtual, &classePecaAtual);

					if (classePecaAtual == NULL) {
						printf("Erro: peca com classe nula.");
						exit(1);
					}

					movI = (reiI - i);
					movJ = (reiJ - j);

					CPC_ChecarMovimento(classePecaAtual, movI, movJ, &resposta);

					if (resposta == 1) {
						legalidade = PRI_ChecarLegalidade(jogadorPecaAtual, j, i, reiJ, reiI);
						if (legalidade == 1) {
							return 1;
						}
					}
				}
			}
		}
	}

	return 0;
}


PEC_tppPeca PRI_ObterRei(char* j, int* i, char jogador) {
	PEC_tppPeca pPeca;
	char jogadorAtual;
	CPC_tppClassePeca pClasse;

	char jc;
	int ic;
	char nome;

	for (ic = 0; ic <= 7; ic++) {
		for (jc = 'A'; jc <= 'H'; jc++) {

			TAB_ObterPeca(simulacao.pTab, ic, jc, &pPeca, &jogadorAtual);
			if (pPeca == NULL)
				continue;

			if (jogador != jogadorAtual)
				continue;

			PEC_ObterClasseDePeca(pPeca, &pClasse);
			CPC_ObterNome(pClasse, &nome);

			if (nome != 'K')
				continue;

			*i = ic;
			*j = jc;
			return pPeca;
		}
	}

	return NULL;
}*/

