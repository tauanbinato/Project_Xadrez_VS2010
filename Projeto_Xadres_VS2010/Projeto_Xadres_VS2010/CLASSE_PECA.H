#pragma once
/* Estruturas */

typedef struct CPC_tagClassePeca * CPC_tppClassePeca ;

/***********************************************************************
*
*  $TC Tipo de dados: CPC Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções de uma CLASSE DE PECA
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
	/* Faltou memória ao alocar dados */

} CPC_tpCondRet;

/***********************************************************************
*
*  $FC Função: CPC Criar classe de peça
*
*  $ED Descrição da função
*     Cria um classe de peça de xadrez
*     O ponteiro para a classe criada será fornecido no valor do ponteiro
*     de ponteiro para classe de peça.
*
*  $EP Parâmetros
*     - ppClassePeca - ponteiro para ponteiro de classe de peça
*     - nome - caracter contendo o nome da classe de peça (por exemplo, "T")
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
*  $FC Função: CPC Destruir classe de peça
*
*  $ED Descrição da função
*     Destroi um classe de peça de xadrez
*
*  $EP Parâmetros
*     - pClassePeca - ponteiro de classe de peça
*
*  $FV Valor retornado
*     CPC_CondRetOK
*     CPC_CondRetPonteiroNulo
*
***********************************************************************/

CPC_tpCondRet CPC_DestruirClassePeca(CPC_tppClassePeca pClassePeca);

/***********************************************************************
*
*  $FC Função: CPC Adicionar Movimento a classe de peça
*
*  $ED Descrição da função
*     Adiciona movimento à lista de uma classe de peça de xadrez
*
*  $EP Parâmetros
*     - pClassePeca - ponteiro de classe de peça
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
*  $FC Função: CPC Checar movimento de classe de peça
*
*  $ED Descrição da função
*     Checa se certa classe de peça pode mover-se de certa maneira
*
*  $EP Parâmetros
*     - pClassePeca - ponteiro para a classe de peça
*     - movI - inteiro de -7 a 7 contendo o valor vertical do movimento
*     - movJ - inteiro de -7 a 7 contendo o valor horizontal do movimento
*     - resposta - ponteiro para inteiro que conterá a resposta (1 ou 0)
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
*  $FC Função: CPC Obter número de movimentos de classe de peça
*
*  $ED Descrição da função
*     Obtém o número de movimentos distintos que a peça possui.
*
*  $EP Parâmetros
*     - pClassePeca - ponteiro para a classe de peça
*     - pNumMovimentos - ponteiro que será modificado para conter o
*           número de movimentos da classe de peça dada
*
*  $FV Valor retornado
*     CPC_CondRetOK
*     CPC_CondRetPonteiroNulo
*
***********************************************************************/

CPC_tpCondRet CPC_ObterNumeroMovimentos(CPC_tppClassePeca pClassePeca, int * numMovimentos);

/***********************************************************************
*
*  $FC Função: CPC Obter movimento de classe de peça
*
*  $ED Descrição da função
*     Obtém os componentes do movimento com dado índice
*
*  $EP Parâmetros
*	 - pClassePeca - ponteiro para a classe de peça
*    - idxMovimento - índice do movimento, inteiro de 0 até (numMovimentos - 1)
*    - pmovI - ponteiro para inteiro que conterá a componente vertical do movimento
*    - pmovJ - ponteiro para inteiro que conterá a componente horizontal do movimento
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
*  $FC Função: CPC Obter nome de classe de peça
*
*  $ED Descrição da função
*     Obtém o nome da classe de peça dada.
*
*  $EP Parâmetros
*     - pClassePeca - ponteiro para a classe de peça
*     - pNome - ponteiro para caracter que conterá o nome
*
*  $FV Valor retornado
*     CPC_CondRetOK
*     CPC_CondRetPonteiroNulo
*
***********************************************************************/

CPC_tpCondRet CPC_ObterNome(CPC_tppClassePeca pClassePeca, char * pNome);

