//
// Created by vins on 10/12/19.
//

#include "INV.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct stat_t{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
};

struct inv_t{
    char nome[MAX];
    char tipo[MAX];
    struct stat_t stat;
};

struct tabInv_t{
    struct inv_t *vettInv;
    int nInv;
    int maxInv;
};



struct tabInv_t *creaTabInv(void){
    struct tabInv_t *tabInv=malloc(sizeof(struct tabInv_t));
    tabInv->maxInv=1;
    tabInv->vettInv=malloc(tabInv->maxInv* sizeof(struct inv_t));
    tabInv->nInv=0;
    return tabInv;
}

void freeTabInv(struct tabInv_t *tabInv){
    free(tabInv->vettInv);
    free(tabInv);
}

void addObj(struct tabInv_t *tabInv,struct inv_t obj){
    if(tabInv->nInv==tabInv->maxInv){
        tabInv->maxInv=tabInv->maxInv*2;
        tabInv->vettInv=realloc(tabInv->vettInv,tabInv->maxInv);
    }
    tabInv->vettInv[tabInv->nInv++]=obj;
}

void addObj_wrapper(struct tabInv_t *tabInv,FILE *fp){
    int nr,i;
    struct inv_t tmp;
    if(fp!=stdin){
        fscanf(fp,"%d",&nr);
    }else{
        nr=1;
    }

    for(i=0;i<nr;i++){
        fscanf(fp,"%s%s%d%d%d%d%d%d",tmp.nome,tmp.tipo,&tmp.stat.hp,&tmp.stat.mp,
               &tmp.stat.atk,&tmp.stat.def,&tmp.stat.mag,&tmp.stat.spr);
        addObj(tabInv,tmp);
    }

}

struct inv_t *searchObj(struct tabInv_t *tabinv, char *key){
    int i;

    for(i=0;i<tabinv->nInv;i++){
        if(strcmp(tabinv->vettInv[i].nome,key)==0){
            return &(tabinv->vettInv[i]);
        }
    }
    return NULL;
}

void displayObj(struct inv_t *obj){

    printf("nome: %s\ntipo: %s\n",obj->nome,obj->tipo);
    printf("hp: %d-mp: %d-atk: %d-def: %d-mag: %d-spr: %d\n",obj->stat.hp,
           obj->stat.mp,obj->stat.atk,obj->stat.def,obj->stat.mag,obj->stat.spr);
    printf("\n");
}

int getHP(struct inv_t *inv){
    return inv->stat.hp;
}

int getMP(struct inv_t *inv){
    return inv->stat.mp;
}
int getATK(struct inv_t *inv){
    return inv->stat.atk;
}
int getDEF(struct inv_t *inv){
    return inv->stat.def;
}
int getMAG(struct inv_t *inv){
    return inv->stat.mag;
}
int getSPR(struct inv_t *inv){
    return inv->stat.spr;
}

int getNOBJ(struct tabInv_t *tabInv){
    return tabInv->nInv;
}

void displayINV(struct tabInv_t *tabInv){
    for(int i=0;i<tabInv->nInv;i++) {
        printf("[%d]", i);
        displayObj(&(tabInv->vettInv[i]));
    }
}

INV getOBJ(struct tabInv_t *tabInv,int index){
    if(index<0||index>=tabInv->nInv) {
        printf("errore indice oggetto");
        return NULL;
    }
    return &tabInv->vettInv[index];
}
