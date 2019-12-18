//
// Created by Master on 16/12/2019.
//

#include "PGlist.h"

typedef struct nodoPg_t *link;

struct nodoPg_t {
    pg_t pg;
    link next;
};


struct pgList_s {
    link headPg;
    link tailPg;
    int nPg;
};

pgList_t pgList_init(){
    struct pgList_s *ret=(struct pgList_s *)malloc(sizeof(struct pgList_s));
    ret->tailPg=ret->headPg=NULL;
    ret->nPg=0;
    return ret;
}

void pgList_freeR(link head){
    if(head == NULL)
        return;
    pgList_freeR(head->next);
    pg_clean(&head->pg);
    free(head);
}

void pgList_free(pgList_t pgList){
    pgList_freeR(pgList->headPg);
    free(pgList);
}

void pgList_read(FILE *fp, pgList_t pgList){
    pg_t tmp;
    while(pg_read(fp,&tmp)!=EOF){
        pgList_insert(pgList,tmp);
    }
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    link x;
    for(x=pgList->headPg;x!=NULL;x=x->next)
        pg_print(fp,&x->pg,invArray);
}

void pgList_insert(pgList_t pgList, pg_t pg){
    struct nodoPg_t *x=malloc(sizeof(struct nodoPg_t));
    //il puntatore alla fine della lista va modificato soltanto
    //alla prima inserzione poiché aggiungiamo sempre in testa;
    if(pgList->headPg==NULL)
        pgList->tailPg=x;
    x->pg=pg;
    x->next=pgList->headPg;
    pgList->headPg=x;
    pgList->nPg++;
}



void pgList_remove(pgList_t pgList, char* cod){
    link x,p;

    if(pgList->headPg==NULL)
        return;
    for(x=pgList->headPg,p=NULL;x!=NULL;p=x,x=x->next){
        if(strcmp(x->pg.cod,cod)==0){
            if(x==pgList->headPg)
                pgList->headPg=x->next;
            else
                p->next=x->next;
            pg_clean(&x->pg);
            free(x);
            return;
        }
    }
}

pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    link x;
    for(x=pgList->headPg;x!=NULL;x=x->next)
        if(strcmp(x->pg.cod,cod)==0){
            return &x->pg;
        }
    return NULL;
}
