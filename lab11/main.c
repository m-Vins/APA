#include <stdio.h>
#include "DATA.h"
#include "TITLIST.h"
#include "QUOTBST.h"
#include "TITOLO.h"
#define MAX 50

typedef enum {new_file,s_tit,s_quot,s_quotdate,s_minmax,s_balance,displayBST,esci,err}cmd_t;


cmd_t leggicomando();

int main() {
    FILE *fp;
    TLIST TList;
    DATA d1,d2;
    float tmp,Qmin,Qmax;
    char FileName[MAX+1],cod[MAX+1];
    int FineProgramma=0,Soglia,cmd;

    TList=TLISTinit();

    while(!FineProgramma){
        switch (leggicomando()){
            case new_file:
                printf("inserire nome File: ");
                scanf("%s",FileName);
                fp=fopen(FileName,"r");
                if(fp==NULL)   printf("ERRORE NOME FILE\n");
                else {
                    TLISTload(TList, fp);
                    fclose(fp);
                }

                break;
            case s_tit:
                printf("inserire codice titolo:");
                scanf("%s",cod);
                TITprint(TLISTsearch(TList,cod),stdout);
                break;
            case s_quot:
                printf("inserire codice titolo:");
                scanf("%s",cod);
                printf("inserire data:");
                d1=DATAread(stdin);
                if((tmp=BSTsearch(TITgetBst(TLISTsearch(TList,cod)),d1))!=-1) {
                    printf("la quotazione del titolo %s  nella data: ", cod);
                    DATAprint(stdout, d1);
                    printf(" è pari a: %f\n", tmp);
                } else
                    printf("quotazione non trovata");
                break;
            case s_quotdate:
                printf("inserire codice titolo: ");
                scanf("%s",cod);
                printf("inserire data minore: ");
                d1=DATAread(stdin);
                printf("inserire data maggiore: ");
                d2=DATAread(stdin);
                BSTsearchMinMaxInterval(TITgetBst(TLISTsearch(TList,cod)),d1,d2,&Qmin,&Qmax);
                printf("min: %f --  max: %f\n",Qmin,Qmax);
                break;
            case s_minmax:
                printf("inserire codice titolo: ");
                scanf("%s",cod);
                BSTsearchMinMax(TITgetBst(TLISTsearch(TList,cod)),&Qmin,&Qmax);
                printf("min: %f --  max: %f\n",Qmin,Qmax);;
                break;
            case s_balance:
                printf("inserire codice titolo: ");
                scanf("%s",cod);
                printf("inserire Soglia :");
                scanf("%d",&Soglia);
                BSTbalance(TITgetBst(TLISTsearch(TList,cod)),Soglia);
                break;
            case displayBST:
                printf("inserire codice titolo: ");
                scanf("%s",cod);
                printf("[1]->PREORDER\n[2]->INORDER\n[3]->POSTORDER\n");
                scanf("%d",&cmd);
                BSTDisplay(TITgetBst(TLISTsearch(TList,cod)),stdout,cmd);
                break;
            case esci:
                FineProgramma=1;
                break;
            default: printf("ERRORE INSERIMENTO COMANDO\n");
        }
    }


    TLISTfree(TList);
    return 0;
}


cmd_t leggicomando(){
    char comandi[][60]={"leggi newFile","cerca titolo","cerca quotazione","cerca quotazione min/max compresa tra date per titolo","cerca quotazione min/max per titolo","bilancia BST titolo","display BST","exit"};
    cmd_t cmd;
    printf("elenco comandi:\n");
    for(int i=0;i<err;i++)
        printf("[%d]->%s\n",i,comandi[i]);
    scanf("%d",&cmd);
    return cmd;
}