#include <stdio.h>
#include <stdlib.h>
#define MAX 50+1

typedef struct {
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat_t;

typedef struct {
    char nome[MAX];
    char tipo[MAX];
    stat_t stat;
}inv_t;

typedef struct {
    inv_t *vettInv;
    int nInv;
    int maxInv;
}tabInv_t;

typedef struct {
    int inUso;
    inv_t **vettEq;
}tabEquip_t;

typedef struct {
    char codice[7];
    char nome[MAX];
    char classe[MAX];
    tabEquip_t *equip;
    stat_t stat;
}pg_t;
 

typedef struct node *link,nodoPg_t;

struct node{
    pg_t pg;
    link next;
};

typedef struct {
    link headPg;
    link tailPg;
    int nPg;
}tabPg_t;


int main() {

    return 0;
}

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




tabPg_t *creaListaPg(void){
    tabPg_t *tabPg=malloc(sizeof(tabPg_t));
    tabPg->headPg=tabPg->tailPg=NULL;
    tabPg->nPg=0;

    return tabPg;
}

link newNode(pg_t pg,link next){
    nodoPg_t *x=malloc(sizeof(nodoPg_t));
    if(x==NULL)
        return NULL;
    x->pg=pg;
    x->next=next;
    return x;
}

void loadPg(tabPg_t *tabPg, FILE *fp){
    int i,nr;
    link x;
    pg_t tmp;
    if(fp!=stdin){
        fscanf(fp,"%d",&nr);
    }else{
        nr=1;
    }
    for(i=0;i<nr;i++){
        fscanf(fp,"%s%s%s%d%d%d%d%d%d",tmp.codice,tmp.nome,tmp.classe,
                &tmp.stat.hp,&tmp.stat.mp,&tmp.stat.atk,&tmp.stat.def,&tmp.stat.mag,
                &tmp.stat.spr);
        tmp.equip=NULL;
        tabPg->headPg=newNode(tmp,tabPg->headPg);
    }
    for(x=tabPg->headPg;x->next!=NULL;x=x->next);
    tabPg->tailPg=x;
}

void deletePg
