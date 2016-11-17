/***********************************************************************
*
*  $FC Função: PRN - Le arquivo de configuracao
*
*  $ED Descrição da função
*     Lê o arquivo de configuração no caminho dado, carregando seus dados
*       no tabuleiro.
*
*  $FV Valor retornado
*     1 se leu com sucesso
*     0 caso contrário
*
***********************************************************************/
int PRI_CarregarArquivoMovimento(char* path);

/***********************************************************************
*
*  $FC Função: PRN funcao de inicialização
*
*  $ED Descrição da função
*     Inicializa a variável global, criando as estruturas necessárias.
*
***********************************************************************/
void PRI_Inicializa(void);

/***********************************************************************
*
*  $FC Função: PRN checa se movimento é do tipo pulo
*
*  $ED Descrição da função
*     Checa se o movimento descrito pelos parâmetros é do tipo pulo ou não.
*     Se for um movimento vertical, horizontal ou diagonal, não é de pulo.  
*
*  $FV Valor retornado
*     1 se o movimento é pulo
*     0 se o movimento não é pulo
*
***********************************************************************/
int PRI_ChecarMovimentoPulo (int movI, int movJ);

/***********************************************************************
*
*  $FC Função: PRN checar legalidade de movimento
*
*  $ED Descrição da função
*     Checa se um movimento é legal, CHECANDO SOMENTE OBSTACULOS NO CAMINHO
*       E CONFLITOS DE DESTINO COM PEÇAS DO MESMO JOGADOR.
*     ASSUME-SE QUE O MOVIMENTO PRIMITIVO É UM MOVIMENTO VÁLIDO PARA A
*       CLASSE DA PEÇA NA ORIGEM.
*
*  $FV Valor retornado
*     1 se o movimento é legal
*     0 se o movimento é ilegal
*
***********************************************************************/
int PRI_ChecarLegalidade(char jogador, char iOrigem, int jOrigem, char iDestino, int jDestino);

/***********************************************************************
*
*  $FC Função: PRN checar xeque-mate
*
*  $ED Descrição da função
*     Verifica se a configuração do tabuleiro configura um xeque-mate.
*     Dá informacoes para o usuário sobre o xeque-mate.
*
***********************************************************************/
void PRI_ChecarXequeMate( );

/***********************************************************************
*
*  $FC Função: PRN checar xeque
*
*  $ED Descrição da função
*     Função auxiliar que verifica se o rei branco está ameaçado pelas peças pretas.
*
*  $FV Valor retornado
*     1, caso esteja
*     0, caso contrário
*
***********************************************************************/
int PRI_ChecarAmeacaReiBranco ( );

/***********************************************************************
*
*  $FC Função: PRI - Obter rei branco
*
*  $ED Descrição da função
*     Procura no tabuleiro a peça um classe de nome "Rei" que pertença
*       ao jogador branco.
*
*  $FV Valor Retornado
*     NULL caso não tenha achado
*     Ponteiro para a peça, caso tenha achado, e nesse caso o valor de i e de j
*       serão atualizados para conter a posição dessa peça no tabuleiro.
*
***********************************************************************/
PEC_tppPeca PRN_ObterReiBranco ( char * i, int * j );

/***********************************************************************
*
*  $FC Função: PRN main
*
*  $ED Descrição da função
*     Coordena a excecução do programa.
*
*  $FV Valor retornado
*     PRN_CondRetOK
*     PRN_CondRetFaltouMemoria
*
***********************************************************************/

int main( void );

/***********************************************************************
*
*  $FC Função: PRN renderizar menu principal
*
*  $ED Descrição da função
*     Mostra o menu principal na tela para o usuário, solicitando a escolha de uma opcao.
*
***********************************************************************/

void PRN_MenuPrincipal( int * opcao );