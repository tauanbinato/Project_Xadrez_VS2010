/***************************************************************************
*  $MCI Módulo de implementação: TJOG Teste do Jogo
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
#include	<stdlib.h>
#include    <windows.h>
#include	<memory.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Lista.h"
#include	"Tabuleiro.h"
#include    "Peca.h"
#include	"CLASSE_PECA.H"



#define MAXNOME 100
#define MAXNOME_S "100"

/**************************COMANDOS SCRIPT**************************/  

static const char CRIAR_CLASSE[]	                =				"=criarcp" ;
static const char PREENCHE_TAB[]			        =				"=preenchetab"  ;
static const char PROCURA_CLASSE[]					=				"=procuraclasse" ;
static const char INSERE_PECA[]						=               "=inserepeca";
static const char CHECAR_MOV_PULO[]			        =				"=checarpulo"  ;
static const char CHECAR_LEGALIDADE[]				=				"=checarlegalidade"	;
static const char CHECAR_AMEACA_REI[]				=				"=checarameacarei";			 
static const char CHECAR_CHEQUE_MATE[]				=				"=checarchequemate";
static const char OBTER_REI[]					    =				"=obterrei";
static const char MOVER_PECA[]				        =				"=moverpeca" ;
static const char CHECAR_MOV_LEGAL[]				=				"=checarmovlegal";
static const char CHECAR_LEG_PEAO[]					=				"=checarlegpeao";
static const char LISTA_AMEACANTES[]				=				"=listaameacantes";
static const char LISTA_AMEACADOS[]					=				"=listaameacados";
/************************FIM COMANDOS SCRIPT************************/

typedef struct PRI_tagSimulacao {

	TAB_ppAncoraTabuleiro pTab;
	/* Ponteiro para o tabuleiro corrente */
	LIS_tppLista pListaPecas;
	/* Ponteiro para a lista de peças */
	LIS_tppLista pListaClasses;
	/* Ponteiro para a lista de classes de peças */

} PRI_tpSimulacao;


char turno = 'B';

/*****  Variável global que armazena a simulação corrente  *****/

PRI_tpSimulacao simulacao;

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
PEC_tppPeca				vtPeca[DIM_VT_PEC];

/***** Protótipos das funções encapuladas no módulo *****/
// void DestruirValor( void * pValor );
static int ValidarInxLista(int inxLista, int Modo);
static int ValidarInxMatriz(int inxLista, int Modo);


int PRI_CarregarArquivoMovimento(char* path);
void PRI_Inicializa(void);

int PRI_PreencheTabuleiro( );
void PRI_CriarClasse( );
void PRI_ListarClasses( void );
CPC_tppClassePeca PRI_ProcurarClasse (char *nomeProcurado);
void PRI_inserePeca(char corJogador, char classe, int i , char j);

int PRI_ChecarMovimentoPulo (int movI, int movJ);
int PRI_ChecarLegalidade(char jogador, char iOrigem, int jOrigem, char iDestino, int jDestino);

int PRI_ChecarAmeacaRei(char jogador);
void PRI_ChecarChequeMate(char jogador);

PEC_tppPeca PRI_ObterRei(char* j, int* i, char jogador);
CPC_tppClassePeca PRI_BuscaClassePeca(char classeProcurada);

void PRI_MoverPeca();
int PRI_ChecarMovimentoLegal(int iOrigem, char jOrigem, int iDestino, char jDestino);
int PRI_ChecarLegalidadePeao(int iOrigem, int movI, int movJ, int iDest, char jDest, PEC_tppPeca pPeca);

void PRI_AtualizarListasAmeacantes( TAB_ppAncoraTabuleiro *pTabuleiro, int i, char j );
void PRI_AtualizarListaAmeacados( TAB_ppAncoraTabuleiro *pTabuleiro, int i, char j );
//void PRI_AtualizarListasTab( TAB_ppAncoraTabuleiro *pTabuleiro );


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
		inxMatriz= -1,
		inxCasa = -1,
		inxTab = -1,
		inxPeca = -1,
		inxCP = -1;

	int  movI, movJ, idxMovimento;
	int* resposta;
	char nome,j;


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


	/* Efetuar teste de criar classe */

	if (strcmp(ComandoTeste, CRIAR_CLASSE) == 0)
	{

		numLidos = LER_LerParametros("icsi",&inxCP, &CharDado,pCharDado, &CondRetEsp);

		//CPC_CriarClassePeca(CPC_tppClassePeca * ppClassePeca, char nome, char* idEnviado);
		if (numLidos != 4)
		{
			return TST_CondRetParm;
		} /* if */

		CondRet_CPC= CPC_CriarClassePeca(&vtClasse[inxCP], CharDado, pCharDado);
		//LIS_CriarLista(&vtListas[inxLista], StringDado);


		if (CondRet_LIS == 6) {

			return TST_CondRetMemoria;

		}

		return TST_CompararInt(CondRetEsp, CondRet_CPC,
			"Condicao de retorno errada ao criar classe");

	} /* fim ativa: Testar CriarClasse */
	//testar preenche tab
	else if (strcmp(ComandoTeste,PREENCHE_TAB) == 0)
	{
		CondRetEsp = CPC_CondRetOK;
		if(PRI_PreencheTabuleiro() != 1)
		{
			CondRet_CPC = CPC_CondRetNaoAchou;
		}	
		else
		{
			CondRet_CPC = CPC_CondRetOK;
		}

		return TST_CompararInt(CondRetEsp, CondRet_CPC,
			"Condicao de retorno errada ao preencher tabuleiro");
	} /* fim ativa: preenche tab */
	//Testar procura classe
	else if (strcmp(ComandoTeste,PROCURA_CLASSE) == 0)
	{
		numLidos = LER_LerParametros("si",pCharDado, &inxCP);

		if (numLidos != 2)
		{
			return TST_CondRetParm;
		} /* if */

		 vtClasse[inxCP] = PRI_ProcurarClasse(pCharDado);
		//LIS_CriarLista(&vtListas[inxLista], StringDado);

		 if(vtClasse[inxCP] != NULL )
		 { 
			 CondRetEsp = CPC_CondRetOK;
			 CondRet_CPC = CPC_CondRetOK;
			 return TST_CompararInt(CondRetEsp, CondRet_CPC,
			"Condicao de retorno errada ao procurar classe");
		 }
		 else
		 {
			 CondRetEsp = CPC_CondRetPonteiroNulo;
			 CondRet_CPC = CPC_CondRetPonteiroNulo;
			 return TST_CompararInt(CondRetEsp, CondRet_CPC,
			"Condicao de retorno errada ao procurar classe");
		 }
		
	
	} /* fim ativa: procura classe */
	//Testar insere peca
	else if (strcmp(ComandoTeste,INSERE_PECA) == 0)
	{
		numLidos = LER_LerParametros("iiicci",&inxTab,&inxPeca,i,j,pCharDado, &CondRetEsp);
		
		if (numLidos != 6)
		{
			return TST_CondRetParm;
		} /* if */

		CondRet_TAB = TAB_InserirPeca(&vtMatrizes[inxTab], &vtPeca[inxPeca], i, j, CharDado);
		PRI_inserePeca(CharDado, &vtClasse[inxCP],  i , j);
		
		return TST_CompararInt(CondRetEsp, CondRet_TAB,
			"Condicao de retorno errada ao inserir peca");
		
	
	} /* fim ativa: insere peca */
	//checar mov pulo
	else if (strcmp(ComandoTeste,CHECAR_MOV_PULO) == 0)
	{
		numLidos = LER_LerParametros("iiicci",&inxTab,&inxPeca,i,j,pCharDado, &CondRetEsp);
		
		if (numLidos != 6)
		{
			return TST_CondRetParm;
		} /* if */

		CondRet_TAB = TAB_InserirPeca(&vtMatrizes[inxTab], &vtPeca[inxPeca], i, j, CharDado);
		PRI_inserePeca(CharDado, &vtClasse[inxCP],  i , j);
		
		return TST_CompararInt(CondRetEsp, CondRet_TAB,
			"Condicao de retorno errada ao inserir peca");
		
	
	} /* fim ativa: preenche tab */

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




void PRI_MenuPrincipal( int * opcao ) {
	char c[5];
	
    printf("\n=== MENU ===\n\n");
    printf("01. Mover Peca\n02. Adicionar Peca\n\n");
    printf("11. Criar classe de peca\n12. Listar classes\n\n");
    printf("21. Excluir peca\n\n");

    scanf(" %s", c);
	if( !strcmp(c,"FIM") )
	{
		*opcao = 99;
	}
	else if( !strcmp(c,"1") )
	{
		*opcao = 1;
	}
	else if( !strcmp(c,"2") )
	{
		*opcao = 2;
	}
	else if( !strcmp(c,"11") )
	{
		*opcao = 11;
	}
	else if( !strcmp(c,"12") )
	{
		*opcao = 12;
	}
	else if( !strcmp(c,"21") )
	{
		*opcao = 21;
	}
	else
	{
		*opcao = 0;
	}
}

void PRI_ImprimirTabuleiro( TAB_ppAncoraTabuleiro * pTabuleiro ) {
	int linha;
	int coluna;
	HANDLE  hConsole;
	
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;

	printf("TABULEIRO\n\n  ");
	for( coluna = 0; coluna < 8; coluna ++){
			printf("  %c  ", coluna + 'A');
	}
	printf("\n  ");
	for( coluna = 0; coluna <8; coluna ++){
			printf(" ___ ");
	}
	printf("\n");
	for( linha = 0; linha< 8; linha ++){
		printf("%d ", linha);
		for( coluna = 0; coluna <8; coluna ++){
			PEC_tppPeca pPeca;
			CPC_tppClassePeca ClassePeca;
			char nome;
			char cor;

			if(TAB_ObterPeca(*pTabuleiro, linha, (char)(coluna + 'A'), (void*)&pPeca, &cor) == TAB_CondRetCasaVazia){
				printf("|   |");
			} else {
				PEC_ObterCorDePeca(pPeca, &cor);
				PEC_ObterClasseDePeca(pPeca, &ClassePeca);
				CPC_ObterNome(ClassePeca, &nome);
				
				printf("| ");
				if (cor == 'P') {
					SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
				}
				printf("%c", nome);
				SetConsoleTextAttribute(hConsole, saved_attributes);
				printf(" |");
				pPeca = NULL;
			}
		}
		printf("\n  ");
		for( coluna = 0; coluna <8; coluna ++){
			printf("|___|");
		}
		printf("\n");
	}
}

int PRI_PreencheTabuleiro( ) {
	int i;
	PEC_tppPeca pPeca;
	char nome, cor, j;
	//inserir peoes brancos
	CPC_tppClassePeca pClassePeca;



	pClassePeca = PRI_BuscaClassePeca('P');
	//reset
	for(j='A';j<'I';j++){
		for(i=0; i<8; i++)
		{
			PEC_criaPeca(&pPeca, pClassePeca, 'B');
			PEC_ObterCorDePeca(pPeca, &cor);
			TAB_InserirPeca(simulacao.pTab, (void**)pPeca, i, j, cor);
			TAB_RetirarPeca(simulacao.pTab, i, j);
		}
	}

	//insere peoes brancos
	for(i=0; i<8; i++)
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

	/*pClassePeca = PRI_BuscaClassePeca('H');

	PEC_criaPeca(&pPeca, pClassePeca, 'B');
	PEC_ObterCorDePeca(pPeca, &cor);
	TAB_InserirPeca(simulacao.pTab, (void**)pPeca, 2, 'C', cor);*/

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
	
	return 1;
}
void PRI_insereTorre (char corJogador, int posicao) {
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

void PRI_inserePeca(char corJogador, char classe, int i , char j){
	PEC_tppPeca pPeca;
	char cor;
	CPC_tppClassePeca pClassePeca;

	pClassePeca = PRI_BuscaClassePeca(classe);

	if (pClassePeca == NULL){
		printf("A classe peca %c não existe, verifique a lista antes de adicionar");
		return;
	}

	PEC_criaPeca(&pPeca, pClassePeca, corJogador);
	PEC_ObterCorDePeca(pPeca, &cor);
	TAB_InserirPeca(simulacao.pTab, (void**)pPeca, i, j, cor);
}

void PRI_AdicionarPeca( ){
	char classe, j, cor;
	int i;
	printf("\nQual a classe da peça que deseja colocar?\n>");
	scanf(" %c", &classe);
	printf("\nQual a cor da peça que deseja colocar <P, B>?\n>");
	scanf(" %c", &cor);
	if(cor != 'P' && cor != 'B'){
		printf("\nCor de Peca inserida invalida\n");
		return;
	}
	printf("\nQual a coordenada vertical em que deseja inserir a peca <0, 7>?\n>");
	scanf(" %d", &i);
	if(i < 0 || i > 7){
		printf("\nPosição invalida\n");
		return;
	}
	printf("\nQual a coordenada horizontal em que deseja inserir a peca <A, H>?\n>");
	scanf(" %c", &j);
	if(j < 'A' || j > 'H'){
		printf("\nPosição invalida\n");
		return;
	}
	PRI_inserePeca(cor, classe, i , j);

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


void PRI_Inicializa(void) {
	if (TAB_CriaTabuleiro(&simulacao.pTab, 8) != TAB_CondRetOK) 
	{
		printf("ERRO DE MEMORIA AO CRIAR TABULEIRO");
		exit(1);
	}
	
	if (LIS_CriarLista(&simulacao.pListaClasses, "Classes") != 0)
	{
		TAB_DestruirTabuleiro(&simulacao.pTab);
		printf("ERRO DE MEMORIA AO CRIAR LISTA DE CLASSES");
		exit(1);
	}

	if (LIS_CriarLista(&simulacao.pListaPecas, "Pecas") != 0) 
	{
		TAB_DestruirTabuleiro(&simulacao.pTab);
		LIS_DestroiLista(&simulacao.pListaClasses);
		printf("ERRO DE MEMORIA AO CRIAR LISTA DE PECAS");
		exit(1);
	}
}
int PRI_ChecarMovimentoPulo (int movI, int movJ) 
{
	if(movI == movJ || movI == -movJ || movI == 0 || movJ == 0)
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

	TAB_ObterPeca(simulacao.pTab, iDestino, jDestino, &defensor, &jogadorDefensor);
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
				TAB_ObterPeca(simulacao.pTab, i, j, &obstaculo, &coraux);
				if (obstaculo != NULL) {
					return 0;
				}
			}

			return 1;
		}
		if (movI < 0) {
			// movimento de letra decrescente
			j = jOrigem; // = jDestino;

			for (i = iOrigem - 1; i > iDestino; i--) {
				TAB_ObterPeca(simulacao.pTab, i, j,&obstaculo,&coraux);;
				if (obstaculo != NULL) {
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
				TAB_ObterPeca(simulacao.pTab, i, j,&obstaculo,&coraux);
				if (obstaculo != NULL) {
					return 0;
				}
			}

			return 1;
		}
		if (movJ < 0) {
			// movimento de numero decrescente
			i = iOrigem; // = iDestino;

			for (j = jOrigem - 1; j > jDestino; j--) {
				TAB_ObterPeca(simulacao.pTab, i, j,&obstaculo,&coraux);
				if (obstaculo != NULL) {
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
				TAB_ObterPeca(simulacao.pTab, i, j,&obstaculo,&coraux);
				if (obstaculo != NULL) {
					return 0;
				}
			}

			return 1;
		}
		else {
			//movimento de letra crescente e numero decrescente
			for (i = iOrigem - 1, j = jOrigem + 1; i > iDestino && j < jDestino; i--, j++) {
				TAB_ObterPeca(simulacao.pTab, i, j,&obstaculo,&coraux);
				if (obstaculo != NULL) {
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
				TAB_ObterPeca(simulacao.pTab, i, j,&obstaculo,&coraux);
				if (obstaculo != NULL) {
					return 0;
				}
			}

			return 1;
		}
		else {
			// movimento de letra e numero decrescente
			for (i = iOrigem - 1, j = jOrigem - 1; i > iDestino && j > jDestino; i--, j--) {
				TAB_ObterPeca(simulacao.pTab, i, j,&obstaculo,&coraux);
				if (obstaculo != NULL) {
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
	PEC_ObterCharClasseDePeca(pPeca, &classe);
	pClassePeca = PRI_BuscaClassePeca(classe);

	//Verificar se o movimento consta la (destino - origem)
	movI = iDestino - iOrigem;
	movJ = jDestino - jOrigem;

	//Checar legalidade movimento de peão
	if (classe == 'P')
		return PRI_ChecarLegalidadePeao(iOrigem, movI, movJ, iDestino, jDestino, pPeca) ;	

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

void PRI_MoverPeca() {
	int iOrigem, iDestino, legalidade = 0, movLegal, pecaObtida;
	char jOrigem, jDestino, cor, *jogadorComido;
	PEC_tppPeca pPeca, PecaComida;

	//Obter origem da peça a ser movida
	while (legalidade == 0) {
		printf("\nInsira a coordenada vertical da peca a ser movida (A - H): ");
		scanf(" %c", &jOrigem);
		printf("\nInsira a coordenada horizontal da peca a ser movida (0 - 7): ");
		scanf(" %d", &iOrigem);

		pecaObtida = TAB_ObterPeca(simulacao.pTab, iOrigem, jOrigem, &pPeca, &cor);

		if( cor != turno )
		{
			printf ("\n Agora nao e sua vez.\n ");
			continue;
		}
	//Obter destino da peça a ser movida
		printf("\nInsira a coordenada vertical do destino da peca (A - H): ");
		scanf(" %c", &jDestino);
		printf("\nInsira a coordenada horizontal do destino da peca (0 - 7): ");
		scanf(" %d", &iDestino);

		movLegal = PRI_ChecarMovimentoLegal(iOrigem, jOrigem, iDestino, jDestino);

		//Checar legalidade do movimento
		if (movLegal) {
			if (PRI_ChecarLegalidade(cor, jOrigem, iOrigem, jDestino, iDestino) == 0)
				printf("\nMovimento ilegal. Insira um movimento valido");
			else {
				TAB_MoverPeca(simulacao.pTab, jOrigem, iOrigem, jDestino, iDestino, &PecaComida, &jogadorComido);
				legalidade = 1;
			}

		}
		else {
			if ( pecaObtida == 8)
				printf("\nCoordenada de ORIGEM invalida.");
			printf("\nA Peca nao realiza este movimento. Insira um movimento valido\n");
		}
	}
}
	//Mover de fato

void PRI_ChecarChequeMate(char jogador) {
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
			TAB_ObterPeca(simulacao.pTab, i, j, &pecaAtual, &jogadorPecaAtual);

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

								TAB_DesfazerMovimento(simulacao.pTab, i, j, iDest, jDest, (void**)pPecaComida);

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

	printf("O jogador %c esta em cheque-mate.",jogador);

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
			char pecaz, corz;
			TAB_ObterPeca(simulacao.pTab, i, j, (void*)&pecaAtual, &jogadorPecaAtual);
			
			if (pecaAtual != NULL) {
				
				if (jogadorPecaAtual != jogador) {
					PEC_ObterClasseDePeca(pecaAtual, &classePecaAtual);
					PEC_ObterCorDePeca(pecaAtual, &corz);
					PEC_ObterCharClasseDePeca(pecaAtual, &pecaz);
					//printf("Peca atual: %c - %c : nas coords: i:%d j:%c\n", pecaz, corz, i, j );
					if (classePecaAtual == NULL) {
						printf("Erro: peca com classe nula.");
						exit(1);
					}

					movI = -(reiI - i);
					movJ = -(reiJ - j);

					CPC_ChecarMovimento(classePecaAtual, movI, movJ, &resposta);

					if (resposta == 1) {
						legalidade = PRI_ChecarLegalidade(jogadorPecaAtual, j, i, reiJ, reiI);
						if (legalidade == 1) {
							printf("A LEGALIDADE EH !");
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
}
void PRI_AtualizarListasAmeacantes( TAB_ppAncoraTabuleiro *pTabuleiro, int i, char j )
{
	int linha,movLegal, numelem;
	char jogador,coluna;
	PEC_tppPeca pPeca;
	LIS_tppLista pListaAmeacantes;

	TAB_ObterPeca(*pTabuleiro, i, j, (void*)&pPeca, &jogador);

	LIS_CriarLista(&pListaAmeacantes, "Ameacantes");

	
	
	for (linha=0;linha<8;linha++)
	{
		for (coluna='A';coluna<'I';coluna++)
		{
			movLegal = PRI_ChecarMovimentoLegal(linha, coluna, i, j);
			if(movLegal)
			{
				if(PRI_ChecarLegalidade(jogador, coluna, linha, j, i)!=0)
				{
					//TAB_AdicionarListaAmeacantesAmeacados(*pTabuleiro, linha, coluna, i, j);
					//LIS_InserirNo( pListaAmeacantes , void * pValor        );
				}
					
			} 
		}
	}

}
void PRI_AtualizarListaAmeacados( TAB_ppAncoraTabuleiro *pTabuleiro, int i, char j )
{
	int linha,movLegal;
	char jogador,coluna;
	PEC_tppPeca pPeca;
	LIS_tppLista *pListaAmeacados;

	TAB_ObterPeca(*pTabuleiro, i, j, (void*)&pPeca, &jogador);

	TAB_ObterListaAmeacantes(*pTabuleiro, i, j, pListaAmeacados);
	//LIS_EsvaziarLista( *pListaAmeacados );
	//LIS_DestroiLista( pListaAmeacados ) ;
	LIS_CriarLista(&pListaAmeacados, "ameacados");


	for (linha=0;linha<8;linha++)
	{
		for (coluna='A';coluna<'I';coluna++)
		{
			movLegal = PRI_ChecarMovimentoLegal(i,j,linha, coluna);
			if(movLegal)
			{
				if(PRI_ChecarLegalidade(jogador, j,i, coluna, linha)!=0)
				{
					TAB_AdicionarListaAmeacantesAmeacados(*pTabuleiro, i, j, linha, coluna);
				}
					
			} 
		}
	}

}
void PRI_AtualizarListasTab( TAB_ppAncoraTabuleiro *pTabuleiro )
{
	int linha;
	char coluna;

	for( linha = 0; linha < 8; linha++ )
	{
		for( coluna = 'A'; coluna < 'I'; coluna++ )
		{
			PRI_AtualizarListasAmeacantes( pTabuleiro, linha, coluna );
			//PRI_AtualizarListaAmeacados( pTabuleiro, linha, coluna );
		}
	}
}
void PRI_CriarClasse( )
{
	char nomeClasse,idClasse;
    int movI, movJ;
    CPC_tppClassePeca pClassePeca;


    printf("Criacao de Classe de Peca\n");
    printf("Digite a sigla da nova classe de peca. (Um unico caracter para representa-la)\n> ");

    scanf(" %c", &nomeClasse);

    if(PRI_ProcurarClasse(nomeClasse) != NULL) { 
        printf("Classe com esse nome ja existe\n");
        return;
    }
	idClasse = nomeClasse;

    CPC_CriarClassePeca(&pClassePeca,idClasse,&nomeClasse);

    if(pClassePeca == NULL) {
        printf("Erro de memoria ao alocar nova classe de peca.");
        exit(1);
    }

    printf("Agora serao cadastrados os movimentos dessa classe criada.\n"
           "Um movimento contem uma componente vertical e um horizontal.\n"
           "Um conjunto de movimentos indicam a totalidade das jogadas possiveis de uma peca.\n"
           "Por exemplo, uma peca que so se move uma casa para a frente tera somente um movimento: {0,1}.\n"
           "Ja uma peca que se move qualquer numero de casas para a direita ou para tras tera os movimentos:\n"
           "{0,1}, {0,2} ... {0,7} e {-1,0}, {-2,0} ... {-7,0}.\n"
           "Vale lembrar que, ja que o tabuleiro de xadrez tem dimensao 8x8, os componentes de movimentos devem ser inteiros entre -7 e 7.\n");

    while(1) {
        printf("\nNovo movimento. Digite as componentes do movimento (ou 0 e 0 para acabar).\n");
        printf("Digite a componente vertical do movimento (entre -7 e 7).\n> ");
        scanf(" %d", &movI);
        printf("Digite a componente horizontal do movimento (entre -7 e 7).\n> ");
        scanf(" %d", &movJ);

        if(movI == 0 && movJ == 0) {
            break;
        }
        if(movI > 7 || movI < -7 || movJ > 7 || movJ < -7) {
            break;
        }

        if( CPC_AdicionarMovimento(pClassePeca, movI, movJ) == CPC_CondRetFaltouMemoria) {
            printf("Erro de memoria ao adicionar movimento.");
            exit(1);
        }
    };

    LIS_IrFinalLista(simulacao.pListaClasses);
    //LIS_InserirElementoApos(simulacao.pListaClasses, pClassePeca);
	LIS_InserirNo( simulacao.pListaClasses ,  pClassePeca);
}
void PRI_ListarClasses( void )
{
    CPC_tppClassePeca pClasse;
    char  nome;
    int count, nMovs;
    int movI, movJ;

    printf("Lista de classes criadas:\n");

    LIS_IrInicioLista( simulacao.pListaClasses );
    while (LIS_ObterNo( simulacao.pListaClasses, (void*)&pClasse ) == LIS_CondRetOK ) {
        //pClasse = (CPC_tppClassePeca) LIS_ObterNo( simulacao.pListaClasses,&pClasse );

        CPC_ObterNome(pClasse, &nome);
        printf("* %c ",nome);

        CPC_ObterNumeroMovimentos(pClasse, &nMovs);
        for(count = 0; count < nMovs; count++) {
            CPC_ObterMovimento( pClasse, count, &movI, &movJ);
            printf("{%d,%d} ", movI, movJ);
        }

        printf("\n");

        if( LIS_AvancarElementoCorrente( simulacao.pListaClasses, 1 ) != LIS_CondRetOK )
            break;
    }

    printf("<fim>");
}
CPC_tppClassePeca PRI_ProcurarClasse (char nomeProcurado) {
    LIS_tpCondRet lisCondRet;
    CPC_tppClassePeca pClassePeca;
    char nomeObtido;

    if(nomeProcurado == NULL) {
        return NULL;
    }

    LIS_IrInicioLista(simulacao.pListaClasses);

    do {
        //pClassePeca = (CPC_tppClassePeca) LIS_ObterValor(simulacao.pListaClasses);
		LIS_ObterNo( simulacao.pListaClasses, (void*)&pClassePeca );
        if(pClassePeca != NULL) {
            CPC_ObterNome(pClassePeca, &nomeObtido);

            if(nomeObtido == nomeProcurado) {
                return pClassePeca;
            }
        }

        lisCondRet = LIS_AvancarElementoCorrente(simulacao.pListaClasses, 1);
    } while(lisCondRet != LIS_CondRetFimLista && lisCondRet != LIS_CondRetListaVazia);

    return NULL;
}

  /********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/

