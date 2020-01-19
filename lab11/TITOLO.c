//
// Created by Master on 10/01/2020.
//
#define MAX 100
#include "TITOLO.h"
#include "TRANS.h"
#include <string.h>
#include <stdlib.h>

struct titolo_s {
    char *codice;
    BST Bst;
};

TIT TITnew(char *cod){
    TIT x=malloc(sizeof *x);
    x->codice=strdup(cod);
    x->Bst=BSTinit();
}

void TITfree(TIT x){
    BSTfree(x->Bst);
    free(x);
}

void TITprint(TIT titolo,FILE *fp){
    if(titolo==NULL){
        printf("titolo non trovato\n");
        return;
    }
    fprintf(fp,"codice titolo: %s\n",titolo->codice);
}

char* TITgetName(TIT titolo){
    return titolo->codice;
}

BST TITgetBst(TIT titolo){
    return titolo->Bst;
}

TIT TITread(FILE *fp){
    int Ntrans;
    char cod[MAX];
    TRVETT TRvett=TRVETTinit();
    TIT Titolo;

    fscanf(fp,"%s",cod);
    Titolo=TITnew(cod);
    fscanf(fp,"%d",&Ntrans);
    TRVETTload(fp,Ntrans,TRvett);

    for(int i=0;i<TRvett->N;i++)
        BSTinsertLeafR(Titolo->Bst, NEWQuot(TRvett->DayVett[i].day, TRvett->DayVett[i].Quot));

    TRVETTfree(TRvett);
    return Titolo;
}

int TITcmp(TIT t1,TIT t2){
    return strcmp(t1->codice,t2->codice);
}

int TITcmpCod(TIT t1,char *cod){
    return strcmp(t1->codice,cod);
}