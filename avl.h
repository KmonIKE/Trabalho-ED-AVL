typedef struct NO* ArvAVL;

ArvAVL* cria_ArvAVL();
void libera_ArvAVL(ArvAVL *raiz);
int insere_ArvAVL(ArvAVL *raiz, int acessos, char* original, char* traduzida);
int remove_ArvAVL(ArvAVL *raiz, char* original);
int estaVazia_ArvAVL(ArvAVL *raiz);
int altura_ArvAVL(ArvAVL *raiz);
int totalNO_ArvAVL(ArvAVL *raiz);
int palavra_traduzida(ArvAVL *raiz, char* pOrigem);
void palavra_completa(ArvAVL *raiz, char* palavra,int nAcesso);
