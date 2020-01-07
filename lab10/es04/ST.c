//
// Created by Master on 04/01/2020.
//

#include "ST.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct st_s {
    struct item_s{char *name;char *rete;} *item;
    int n,maxn;
};


ST STinit(){
    ST st=(struct st_s*)malloc(sizeof(struct st_s));
    st->n=0;
    st->maxn=1;
    st->item=(struct item_s *)malloc(st->maxn * sizeof(struct item_s));
    return st;
}

int STinsert(char* name,char *rete, struct st_s *st){
    if(STsearchByName(name,st)!=-1) return STsearchByName(name,st);
    if(st->n == st->maxn){
        st->maxn*=2;
        st->item=realloc(st->item, sizeof(struct item_s )*st->maxn);
    }
    st->item[st->n].name=strdup(name);
    st->item[st->n++].rete=strdup(rete);
    return st->n-1;
}

int STsearchByName(char *name, struct st_s *st){
    for(int i=0;i<st->n;i++) {
        if (strcmp(name, st->item[i].name) == 0)
            return i;
    }
    return -1;
}

int STsearchByRete(char *rete, struct st_s *st){
    for(int i=0;i<st->n;i++) {
        if (strcmp(rete, st->item[i].rete) == 0)
            return i;
    }
    return -1;
}

char *STsearchNameByIndex(int index, struct st_s *st){
    return st->item[index].name;
}
char *STsearchReteByIndex(int index, struct st_s *st){
    return st->item[index].rete;
}


void STdelete(int index, struct st_s *st){
    st->n--;
    for(int i=index;i<st->n;i++)
        st->item[i]=st->item[i+1];
}

void STfree(ST st){
    if(st==NULL){
        printf("errore st free");
        return;
    }
    for(int i=0;i<st->n;i++){
        free(st->item[i].name);
        free(st->item[i].rete);
        free(st->item);
    }
    free(st);
}

int STcount(ST st){
    return st->n;
}