#include <stdio.h>
#include"avl.h"
#include<stdlib.h>


int main(void) {

//num acessos
//palavra origem 25
//palavra traduzida 25
// traducao = 0 //pEntrada
//1-99999 completar //pCompleta

FILE *dict;

dict = fopen( "dict.txt" ,"rt");
       if(dict == NULL) exit(0);


ArvAVL *raiz;

raiz = cria_ArvAVL();


int nAcesso = 0;
char pOrigem[30];
char pTraduzida[30];

int comando;
char pEntrada[30];
char pCompleta[30];


 while(!feof(dict)){

    fscanf(dict,"%d", &nAcesso);

    if(nAcesso == -1) break;
    
    fscanf(dict,"%s", pOrigem);
    fscanf(dict,"%s", pTraduzida);

    insere_ArvAVL(raiz, nAcesso,pOrigem,pTraduzida);
    
 }



fclose(dict);

do{
  
  scanf("%d",&comando);

  if(comando == -1) break;
  
  if(comando == 0){

  scanf("%s",pEntrada);
  
  palavra_traduzida(raiz,pEntrada);
  

  } else{

    nAcesso = comando;

    scanf("%s",pCompleta);

    palavra_completa(raiz,pCompleta,nAcesso); //em ordem
    
  }

}while(comando!=-1);


libera_ArvAVL(raiz);


}