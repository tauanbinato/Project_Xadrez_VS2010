#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD Módulo de definição: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor        Data          Observações
*     5       lp,ja, tb 28/nov/2016   alteração de funções e edição do scrpit de teste
*     4       avs       01/fev/2006   criar linguagem script simbólica
*     3       avs       08/dez/2004	  uniformização dos exemplos
*     2       avs       07/jul/2003	  unificação de todos os módulos em um só projeto
*     1       avs       16/abr/2003	  início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa listas genéricas duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia = 2 ,
               /* A lista não contém elementos */

         LIS_CondRetListaNaoExiste,
               /* Lista não existe */

         LIS_CondRetFimLista ,
               /* Foi atingido o final da lista */

		 LIS_CondRetInicioLista,
			   /*Foi atingido o início da lista */

         LIS_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar um elemento de lista */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Função: LIS  &Criar lista
*
*  $ED Descrição da função
*     Cria uma cabeça de lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     pLista        - ponteiro de ponteiro para a estrutura do tipo LIS_tpLista*
*					  a ser criada.
*
*     idLista       - string de identificação da lista
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
*	$AE - Assertivas de entrada:
*	-Recebe uma identidade de lista que é um string de ate 4 caracteres válidos 
*	$AS - Assertivas de saída:
*	-Se pAnt ≠ NULL, então pCorr->pAnt->pProx = pCorr ; Se pProx ≠ NULL, então pCorr->pProx->pAnt->pCorr (essas são as assertivas estruturais da lista duplamente encadeada com cabeça)
*	-Lista foi criada
*	-Os ponteiros de inicio, fim e pElem corrente apontam para o mesmo local(origem da lista)
*
*
***********************************************************************/

   LIS_tpCondRet LIS_CriarLista(LIS_tppLista* pLista, char* idLista);

/***********************************************************************
*
*  $FC Função: LIS  &Destruir lista
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*
*  $FV Valor retornado
*     LIS_CondRetOK                - destruiu sem problemas
*     LIS_CondRetListaNaoExiste    - lista nao existe
*
*	$AE - Assertivas de entrada:
*	-Valem as assertivas estruturais da lista duplamente encadeada com cabeça
*
*	$AS - Assertivas de saída:
*	-Lista foi destruída e o espaço alocado por ela foi liberado 
***********************************************************************/

   LIS_tpCondRet LIS_DestroiLista( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  $FC Função: LIS  &Obter Id
*
*  $ED Descrição da função
*     Obtem o Id contido dentro da cabeça da Lista passada
*
*  $EP Parâmetros
*     pLista  - ponteiro para a cabeça a ser encontrado o Id
*	  idLista - ponteiro para identificacao da Id da lista
*
*	$AE - Assertivas de entrada:
*	- Valem assertivas estruturais da lista duplamente encadeadas
*	- Recebe uma lista já criada (e não nula)
*
*	$AS - Assertivas de saída:
*	- Valem assertivas estruturais da lista duplamente encadeadas
*	- Ponteiro foi preenchido com identidade da lista enviada
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterId(LIS_tppLista pLista, char *idLista) ;

/***********************************************************************
*
*  $FC Função: LIS  &Esvaziar lista
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a ser esvaziada
*
*	$AE - Assertivas de entrada:
*
*	$AS - Assertivas de saída:
*	- Se a lista não for nula, todos seus elementos estão eliminados
*	- Valem todas as assertivas estruturais de lista
*
***********************************************************************/

   void LIS_EsvaziarLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir No
*
*  $ED Descrição da função
*     Insere novo elemento apás o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     Parâmetros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*           
*
*  $FV Valor retornado
*     Valor retornado
*        LIS_CondRetOK
*        LIS_CondRetFaltouMemoria
*	$AE - Assertivas de entrada
*	- Valem assertivas estruturais da lista duplamente encadeadas
*	- Lista existe (já foi criada, mas pode estar vazia)
*	- Nó corrente aponta para o último elemento da lista
*	- Valor a ser inserido é valido (nesse caso, é um char)
*	$AS - Assertivas de saída:
*	- Valem assertivas estruturais da lista duplamente encadeadas
*	- Lista tem um novo nó, com a informação recebida, e o elemento corrente aponta para ele, bem como o ponteiro de final de lista (se a lista estava vazia esse será o primeiro nó)
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirNo( LIS_tppLista pLista ,
                                          void * pValor        )
       ;


/***********************************************************************
*
*  $FC Função: LIS  &Excluir no corrente
*
*  $ED Descrição da função
*     Exclui o elemento do no corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  $EP Parâmetros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
*	$AE - Assertivas de entrada
*	- Lista existe com pelo menos três nós
*	- Corrente aponta para o nó intermediário que precisa ser excluído
*	- Valem assertivas estruturais da lista duplamente encadeada com cabeça 
*	$AS - Assertivas de saída:
*	- Valem as assertivas estruturais da lista duplamente encadeada com cabeça
*	- Nó corrente foi excluído
*	- Corrente aponta para o próximo 
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirNoCorrente(LIS_tppLista pLista);


/***********************************************************************
*
*  $FC Função: LIS  &Obter referência para o caracter contido no elemento
*
*  $ED Descrição da função
*     Obtem a referência para o caracter contido no elemento corrente da lista
*
*  $EP Parâmetros
*     pLista     - ponteiro para a lista de onde se quer o valor
*     CharObtido - referência para o char a ser passado pela função
*
*  $FV Valor retornado
*     LIS_CondRetOK             - se o elemento corrente existe
*     LIS_CondRetListaVazia     - se a lista estiver vazia
*
*	$AE - Assertivas de entrada
*	- Valem as assertivas de lista duplamente encadeadas
*	$AS - Assertivas de saída:
*	- O caracter que está contido no ponteiro enviado era o contido no nó que o ponteiro corrente apontava
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterNo(LIS_tppLista pLista, void** pValor);

/***********************************************************************
*
*  $FC Função: LIS  &AvancarElementoCorrente
*
*  $ED Descrição da função
*     Avança o elemento corrente numElem elementos na lista
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*	  numElem - numero de elementos a serem andados
*
*  $FV Valor retornado
*     CondRetOK         - se um elemento tiver sido andado
*     CondRetFimLista   - se encontrou o fim da lista antes de andar um elemento
*     CondRetListaVazia - se a lista está vazia
*
*	$AE - Assertivas de entrada
*	- Recebe uma lista já criada 
*	- Valem as assertivas estruturais da lista duplamente encadeada com cabeça
*	$AS - Assertivas de saída:
*	- Valem as assertivas estruturais da lista duplamente encadeada com cabeça
*	- O ponteiro corrente aponta para o elemento após numElem elementos, no caso que era o último, ele continua apontando para o mesmo elemento
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente(LIS_tppLista pLista, int numElem);


/***********************************************************************
*
*  $FC Função: LIS  &Voltar Elemento Corrente
*
*  $ED Descrição da função
*     Volta o elemento corrente um elemento na lista
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*
*  $FV Valor retornado
*     CondRetOK            - se um elemento tiver sido voltado
*     CondRetInicioLista   - se encontrou o inicio da lista antes de voltar um elemento
*     CondRetListaVazia    - se a lista está vazia
*
*	$AE - Assertivas de entrada
*	- Valem as assertivas estruturais da lista duplamente encadeada com cabeça
*	- Recebe uma lista já criada 
*	$AS - Assertivas de saída:
*	- Valem as assertivas estruturais da lista duplamente encadeada com cabeça
*	- O ponteiro corrente aponta para o anterior, e caso o enviado fosse o primeiro, continua apontando para o mesmo elemento
*
***********************************************************************/

   LIS_tpCondRet LIS_VoltarElementoCorrente(LIS_tppLista pLista);

/***********************************************************************
*
*  $FC Função: LIS  &Alterar no corrente
*
*  $ED Descrição da função
*     Altera o elemento o caracter contido no elemento corrente
*	  para o fornecido na função
*
*  $EP Parâmetros
*     pLista   - ponteiro para a lista a ser manipulada
*     CharDado - caracter fornecido
*
*  $FV Valor retornado
*     CondRetOK               - se o caracter for alterado com sucesso
*     CondRetListaNaoExiste   - se a lista não existe
*     CondRetListaVazia       - se a lista está vazia
*
*	$AE - Assertivas de entrada
*	- Valem as assertivas estruturais da lista duplamente encadeada com cabeça
*	- Nó corrente aponta para um índice valido
*	$AS - Assertivas de saída:
*	- Valem as assertivas estruturais da lista duplamente encadeada com cabeça
*	- Nó corrente agora aponta para o mesmo elemento, mas ao invés de conter um índice, contém um char
*
***********************************************************************/

   LIS_tpCondRet LIS_AlterarElementoCorrente(LIS_tppLista pLista, void* CharDado);

/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento inicial
*
*  $ED Descrição da função
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
*	$AE - Assertivas de entrada
*	- valem assertivas estruturais de lista duplamente encadeada
*	$AS - Assertivas de saída:
*	- O elemento corrente da lista agora aponta para o elemento inicial
*
***********************************************************************/

   LIS_tpCondRet LIS_IrInicioLista(LIS_tppLista pLista) ;

/***********************************************************************
*
*  $FC Função: LIS  &Obter Numero de Elementos
*
*  $ED Descrição da função
*     Obtem o numero de elementos de uma lista fornecida.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
*	$AE - Assertivas de entrada
*	- valem assertivas estruturais de lista duplamente encadeada
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterNumElementos(LIS_tppLista pLista, int *numElementos);
  /***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento final
*
*  $ED Descrição da função
*     Torna corrente o ultimo elemento da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*	  numElementos - ponteiro para numero de elementos na lista
*
*	$AE - Assertivas de entrada
*	- valem assertivas estruturais de lista duplamente encadeada
*	$AS - Assertivas de saída:
*	- O elemento corrente da lista agora aponta para o elemento final
*
***********************************************************************/
  
   void LIS_IrFinalLista(LIS_tppLista pLista);

#undef LISTA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/                 

#else
#endif
