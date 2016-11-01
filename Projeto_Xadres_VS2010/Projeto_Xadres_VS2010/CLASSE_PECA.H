typedef struct CPC_tagClassePeca * CPC_tppClassePeca ;

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

CPC_tpCondRet CPC_CriarClassePeca(CPC_tppClassePeca * ppClassePeca, char nome, char* idEnviado);