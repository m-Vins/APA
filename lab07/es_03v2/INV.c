//
// Created by vins on 10/12/19.
//

#include "INV.h"
#include <stdlib.h>
#include <stdio.h>


tabInv_t *creaTabInv(void){
    tabInv_t *tabInv=malloc(sizeof(tabInv_t));
    tabInv->maxInv=1;
    tabInv->vettInv=malloc(tabInv->maxInv* sizeof(inv_t));
    tabInv->nInv=0;
    return tabInv;
}

void freeTabInv(tabInv_t *tabInv){
    free(tabInv->vettInv);
    free(tabInv);
}

void addObj(tabInv_t *tabInv,inv_t obj){
    if(tabInv->nInv==tabInv->maxInv){
        tabInv->maxInv=tabInv->maxInv*2;
        tabInv->vettInv=realloc(tabInv->vettInv,tabInv->maxInv);
    }
    tabInv->vettInv[tabInv->nInv++]=obj;
}

void addObj_wrapper(tabInv_t *tabInv,FILE *fp){
    int nr,i;
    inv_t tmp;
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

struct inv_t *searchObj(tabInv_t *tabinv, char *key){
    int i;

    for(i=0;i<tabinv->nInv;i++){
        if(strcmp(tabinv->vettInv[i].nome,key)==0){
            return &(tabinv->vettInv[i]);
        }
    }
    return NULL;
}

void displayObj(tabInv_t *tabInv, char *key){
    struct inv_t *obj=searchObj(tabInv,key);

    printf("nome: %s\ntipo: %s\n",obj->nome,obj->tipo);
    printf("hp: %d\nmp: %d\natk: %d\ndef: %d\nmag: %d \nspr: %d\n",obj->stat.hp,
           obj->stat.mp,obj->stat.atk,obj->stat.def,obj->stat.mag,obj->stat.spr);
    printf("\n");
}
