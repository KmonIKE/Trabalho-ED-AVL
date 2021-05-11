#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h" //inclui os Protótipos

struct NO{
    char original[30];
    char traduzida[30];
    int acessos;
    int altura;
    struct NO *esq;
    struct NO *dir;
};

ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}


void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}


void libera_ArvAVL(ArvAVL* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada nó
    free(raiz);//libera a raiz
}

int altura_NO(struct NO* no){
    if(no == NULL)
        return -1;
    else
    return no->altura;
}

int fatorBalanceamento_NO(struct NO* no){
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

int estaVazia_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int totalNO_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvAVL(&((*raiz)->esq));
    int alt_dir = totalNO_ArvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

int altura_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvAVL(&((*raiz)->esq));
    int alt_dir = altura_ArvAVL(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}


void palavra_completa(ArvAVL *raiz, char* palavra,int nAcesso){

    if(raiz == NULL)
        return;
    if(*raiz != NULL){

        
        int a = strlen(palavra);            

        if(strncmp(palavra,(*raiz)->original,a)==0){

					palavra_completa(&(*raiz)->esq,palavra,nAcesso);
          
          if((*raiz)->acessos >= nAcesso)
          printf("%s\n",(*raiz)->original);
          
					palavra_completa(&(*raiz)->dir,palavra,nAcesso);
					
        }

        if(strncmp(palavra,(*raiz)->original,a)>0)

        palavra_completa(&(*raiz)->dir,palavra,nAcesso);
                            
        if(strncmp(palavra,(*raiz)->original,a)<0)

				palavra_completa(&(*raiz)->esq,palavra,nAcesso);

				 
          
    }
}

int palavra_traduzida(ArvAVL *raiz, char* pOrigem){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(strcmp(pOrigem, atual->original)== 0){
            printf("%s\n",atual->traduzida);
            atual->acessos++;
        }
        if(strcmp(pOrigem, atual->original) > 0){
          if(atual->dir == NULL) return 0;
            atual = atual->dir;
           // printf("\nfoi direita\n");
        }
        else{
          if(atual->esq == NULL)return 0;  
            atual = atual->esq;
            //printf("\nfoi esquerda\n");
        }
            
    }
    return 0;
}

//=================================
void RotacaoLL(ArvAVL *A){//LL
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
    *A = B;
}

void RotacaoRR(ArvAVL *A){//RR
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

void RotacaoLR(ArvAVL *A){//LR
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(ArvAVL *A){//RL
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

int insere_ArvAVL(ArvAVL *raiz, int acessos, char* original, char* traduzida){
    
	
    int res;
    if(*raiz == NULL){//árvore vazia ou nó folha
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;

        strcpy(novo->original, original);
        strcpy(novo->traduzida, traduzida);
        novo->acessos = acessos;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    
    if(strcmp(original, atual->original)<0){
        if((res = insere_ArvAVL(&(atual->esq),acessos ,original,traduzida)) == 1){
            if(fatorBalanceamento_NO(atual) >= 2){
                if((strcmp(original, (*raiz)->esq->original)<0)){
                    RotacaoLL(raiz);
                }else{
                    RotacaoLR(raiz);
                }
            }
        }
    }else{
        if(strcmp(original, atual->original)>0){
            if((res = insere_ArvAVL(&(atual->dir),acessos ,original,traduzida)) == 1){
                if(fatorBalanceamento_NO(atual) >= 2){
                    if((strcmp(original, (*raiz)->dir->original)>0)){
                        RotacaoRR(raiz);
                    }else{
                        RotacaoRL(raiz);
                    }
                }
            }
        }else{
            printf("Valor duplicado!!\n");
            return 0;
        }
    }

    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return res;
}

struct NO* procuraMenor(struct NO* atual){
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int remove_ArvAVL(ArvAVL *raiz, char* original){
	if(*raiz == NULL){// valor não existe
	    printf("valor não existe!!\n");
	    return 0;
	}

    int res;
	if(strcmp(original, (*raiz)->original) < 0){
	    if((res = remove_ArvAVL(&(*raiz)->esq,original)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
	    }
	}

	if(strcmp(original, (*raiz)->original) > 0){
	    if((res = remove_ArvAVL(&(*raiz)->dir, original)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq) )
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
	    }
	}

	if(strcmp(original, (*raiz)->original) == 0){
	    if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)){// nó tem 1 filho ou nenhum
			struct NO *oldNode = (*raiz);
			if((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
			free(oldNode);
		}else { // nó tem 2 filhos
			struct NO* temp = procuraMenor((*raiz)->dir);
      strcpy((*raiz)->original, temp->original);
			
			remove_ArvAVL(&(*raiz)->dir, (*raiz)->original);
            if(fatorBalanceamento_NO(*raiz) >= 2){
				if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
		if (*raiz != NULL)
            (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
		return 1;
	}

	(*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;

	return res;
}