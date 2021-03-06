#pragma once
/* Estruturas */

typedef struct CPC_tagClassePeca * CPC_tppClassePeca ;

/***********************************************************************
*
*  $TC Tipo de dados: CPC Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es de uma CLASSE DE PECA
*
***********************************************************************/

typedef enum {

	CPC_CondRetOK ,
	/* Concluiu corretamente */

	CPC_CondRetPonteiroNulo ,
	/* Retorna um ponteiro para NULL */

	CPC_CondRetNaoAchou ,
	/* Nao encontrou o valor procurado */

	CPC_CondRetFaltouMemoria
	/* Faltou mem�ria ao alocar dados */

} CPC_tpCondRet;

/***********************************************************************
*
*  $FC Fun��o: CPC Criar classe de pe�a
*
*  $ED Descri��o da fun��o
*     Cria um classe de pe�a de xadrez
*     O ponteiro para a classe criada ser� fornecido no valor do ponteiro
*     de ponteiro para classe de pe�a.
*
*  $EP Par�metros
*     - ppClassePeca - ponteiro para ponteiro de classe de pe�a
*     - nome - caracter contendo o nome da classe de pe�a (por exemplo, "T")
*     - idEnviado - nome da Lista criada junto com a classe
*
*  $FV Valor retornado
*     CPC_CondRetOK
*     CPC_CondRetFaltouMemoria
*
***********************************************************************/

CPC_tpCondRet CPC_CriarClassePeca(CPC_tppClassePeca * ppClassePeca, char nome, char* idEnviado);

/***********************************************************************
*
*  $FC Fun��o: CPC Destruir classe de pe�a
*
*  $ED Descri��o da fun��o
*     Destroi um classe de pe�a de xadrez
*
*  $EP Par�metros
*     - pClassePeca - ponteiro de classe de pe�a
*
*  $FV Valor retornado
*     CPC_CondRetOK
*     CPC_CondRetPonteiroNulo
*
***********************************************************************/

CPC_tpCondRet CPC_DestruirClassePeca(CPC_tppClassePeca pClassePeca);

/***********************************************************************
*
*  $FC Fun��o: CPC Adicionar Movimento a classe de pe�a
*
*  $ED Descri��o da fun��o
*     Adiciona movimento � lista de uma classe de pe�a de xadrez
*
*  $EP Par�metros
*     - pClassePeca - ponteiro de classe de pe�a
*	  - movI - inteiro entre -7 e 7 contendo o valor vertical do movimento
*	  - movJ - inteiro entre -7 e 7 contendo o valor horizontal do movimento

*  $FV Valor retornado
*     CPC_CondRetOK
*     CPC_CondRetPonteiroNulo
*	  CPC_CondRetNaoAchou
*
***********************************************************************/

CPC_tpCondRet CPC_AdicionarMovimento(CPC_tppClassePeca pClassePeca, int movI, int movJ);

/***********************************************************************
*
*  $FC Fun��o: CPC Checar movimento de classe de pe�a
*
*  $ED Descri��o da fun��o
*     Checa se certa classe de pe�a pode mover-se de certa maneira
*
*  $EP Par�metros
*     - pClassePeca - ponteiro para a classe de pe�a
*     - movI - inteiro de -7 a 7 contendo o valor vertical do movimento
*     - movJ - inteiro de -7 a 7 contendo o valor horizontal do movimento
*     - resposta - ponteiro para inteiro que conter� a resposta (1 ou 0)
*
*  $FV Valor retornado
*     CPC_CondRetOK
*     CPC_CondRetNaoAchou
*     CPC_CondRetPonteiroNulo
*
***********************************************************************/

CPC_tpCondRet CPC_ChecarMovimento(CPC_tppClassePeca pClassePeca, int movI, int movJ, int * resposta);

/***********************************************************************
*
*  $FC Fun��o: CPC Obter n�mero de movimentos de classe de pe�a
*
*  $ED Descri��o da fun��o
*     Obt�m o n�mero de movimentos distintos que a pe�a possui.
*
*  $EP Par�metros
*     - pClassePeca - ponteiro para a classe de pe�a
*     - pNumMovimentos - ponteiro que ser� modificado para conter o
*           n�mero de movimentos da classe de pe�a dada
*
*  $FV Valor retornado
*     CPC_CondRetOK
*     CPC_CondRetPonteiroNulo
*
***********************************************************************/

CPC_tpCondRet CPC_ObterNumeroMovimentos(CPC_tppClassePeca pClassePeca, int * numMovimentos);

/***********************************************************************
*
*  $FC Fun��o: CPC Obter movimento de classe de pe�a
*
*  $ED Descri��o da fun��o
*     Obt�m os componentes do movimento com dado �ndice
*
*  $EP Par�metros
*	 - pClassePeca - ponteiro para a classe de pe�a
*    - idxMovimento - �ndice do movimento, inteiro de 0 at� (numMovimentos - 1)
*    - pmovI - ponteiro para inteiro que conter� a componente vertical do movimento
*    - pmovJ - ponteiro para inteiro que conter� a componente horizontal do movimento
*
*  $FV Valor retornado
*     CPC_CondRetOK
*     CPC_CondRetNaoAchou
*     CPC_CondRetPonteiroNulo
*
***********************************************************************/

CPC_tpCondRet CPC_ObterMovimento(CPC_tppClassePeca pClassePeca, int idxMovimento, int * pMovI, int * pMovJ);

/***********************************************************************
*
*  $FC Fun��o: CPC Obter nome de classe de pe�a
*
*  $ED Descri��o da fun��o
*     Obt�m o nome da classe de pe�a dada.
*
*  $EP Par�metros
*     - pClassePeca - ponteiro para a classe de pe�a
*     - pNome - ponteiro para caracter que conter� o nome
*
*  $FV Valor retornado
*     CPC_CondRetOK
*     CPC_CondRetPonteiroNulo
*
***********************************************************************/

CPC_tpCondRet CPC_ObterNome(CPC_tppClassePeca pClassePeca, char * pNome);

