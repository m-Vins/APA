//
// Created by Master on 11/01/2020.
//

#include "TITLIST.h"
#include <stdlib.h>

typedef struct node_s *link;
struct node_s {
    TIT Titolo;
    link next;
};

struct list_s {
    link head;
    int nPg;
};

TLIST TLISTinit(){
    TLIST x=malloc(sizeof *x);
    x->head=NULL;
    x->nPg=0;
    return x;
}

static link NewNodeList(TIT titolo, link next){
    link x=malloc(sizeof *x);
    x->next=next;
    x->Titolo=titolo;
    return x;
}

static void freeListR(link x){
    if(x==NULL) return;
    freeListR(x->next);

    TITfree(x->Titolo);
    free(x);
}

void TLISTfree(TLIST x){
    freeListR(x->head);
    free(x);
}

void TLISTinsert(TLIST List,TIT titolo){
    link x,p;
    if(List->head==NULL||TITcmp(List->head->Titolo,titolo)>=0) {
        List->head = NewNodeList(titolo, List->head);
        return;
    }

    for(x=List->head->next,p=List->head;x!=NULL&&TITcmp(x->Titolo,titolo)<=0;p=x,x=x->next);
    p->next=NewNodeList(titolo,x);
    List->nPg++;
}

TIT TLISTsearch(TLIST List,char *cod){
    for(link x=List->head;x!=NULL;x=x->next){
        if(TITcmpCod(x->Titolo,cod)==0)
            return x->Titolo;
    }
    return NULL;
}

void TLISTload(TLIST List,FILE *fp){
    int NTit;
    fscanf(fp,"%d",&NTit);
    for(int i=0;i<NTit;i++)
        TLISTinsert(List,TITread(fp));
}