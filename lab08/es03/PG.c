#include "PG.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int inUso;
    INV *vettEq;
}tabEquip_t;

typedef struct {
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat_t;

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

struct tabPg_t{
    link headPg;
    link tailPg;
    int nPg;
};



typedef enum {c_add,c_remove}c_equip;


struct tabPg_t *creaListaPg(void){
    struct tabPg_t *tabPg=malloc(sizeof(struct tabPg_t));
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

void loadPg(struct tabPg_t *tabPg, FILE *fp){
    link x;
    pg_t tmp;
    if(fp==stdin){
        fscanf(fp,"%s%s%s%d%d%d%d%d%d",tmp.codice,tmp.nome,tmp.classe,
               &tmp.stat.hp,&tmp.stat.mp,&tmp.stat.atk,&tmp.stat.def,&tmp.stat.mag,
               &tmp.stat.spr);
        tmp.equip=malloc(sizeof(tabEquip_t));
        tmp.equip->inUso = 0;
        tmp.equip->vettEq = malloc(8 * sizeof(INV));
        tabPg->headPg=newNode(tmp,tabPg->headPg);
    }else {

        while(fscanf(fp, "%s%s%s%d%d%d%d%d%d", tmp.codice, tmp.nome, tmp.classe,
                     &tmp.stat.hp, &tmp.stat.mp, &tmp.stat.atk, &tmp.stat.def, &tmp.stat.mag,
                     &tmp.stat.spr)!=EOF){
            tmp.equip=malloc(sizeof(tabEquip_t));
            tmp.equip->inUso = 0;
            tmp.equip->vettEq = malloc(8 * sizeof(INV));
            tabPg->headPg = newNode(tmp, tabPg->headPg);
            tabPg->nPg++;
        }
    }
    for(x=tabPg->headPg;x!=NULL;x=x->next);
    tabPg->tailPg=x;
}

link searchPg(struct tabPg_t *tabPg,char *key){
    link x;

    for(x=tabPg->headPg;x!=NULL;x=x->next){
        if(strcmp(x->pg.codice,key)==0)
            return x;
    }
    return NULL;
}

void deletePg(struct tabPg_t *tabPg, char *key){
    link x,p;
    if(tabPg->headPg==NULL) return;
    for(x=tabPg->headPg,p=NULL;x!=NULL;p=x,x=x->next){
        if(strcmp(x->pg.codice,key)==0){
            if(x==tabPg->headPg)
                tabPg->headPg=x->next;
            else
                p->next=x->next;
            free(x);
            break;
        }
        tabPg->nPg--;
    }
}

void editEquipPg(struct tabPg_t *tabPg,char *key,TABINV tabInv){
    int i,cmd,n;
    pg_t pg;

    if(searchPg(tabPg,key)==NULL){
        printf("il PG non è presente nella lista\n");
        return;
    }
    pg=searchPg(tabPg,key)->pg;

    if(pg.equip->inUso==0){
        printf("il pg non ha ancora nessun equipaggiamento.\n");
    }else {
        printf("sono in uso su questo pg %d oggetti:\n", pg.equip->inUso);
        for (i = 0; i < pg.equip->inUso; i++) {
            printf("[%d]", i);
            displayObj(pg.equip->vettEq[i]);
        }
    }
    printf("inserire comando: (0):aggiungi oggetto-(1)rimuovi oggetto\n");
    scanf("%d",&cmd);

    switch((c_equip)cmd){
        case c_add:
            printf("nell'inventario ci sono i seguenti oggetti:\n");
            displayINV(tabInv);

            printf("inserire numero oggetto da aggiungere fino a un max di 8,\npoi premere -1 per uscire\n");
            while(scanf("%d",&n)==1&&n!=-1&&pg.equip->inUso<8){
                    if((pg.equip->vettEq[pg.equip->inUso++] = getOBJ(tabInv,n))==NULL)
                        pg.equip->inUso--;
            }
            break;
        case c_remove:
            printf("inserire indice oggetto da rimuovere,\npoi premere -1 per uscire\n");
            while(scanf("%d",&n)==1&&n!=-1&&pg.equip->inUso>0){
                if(n<0||n>=pg.equip->inUso){
                    printf("errore numero oggetto");
                }else{
                    pg.equip->inUso--;
                    for(i=n-1;i<pg.equip->inUso;i++){
                        pg.equip->vettEq[i]=pg.equip->vettEq[i+1];//traslo tutta la parte successiva
                    }
                    for (i = 0; i < pg.equip->inUso; i++)
                        displayObj(pg.equip->vettEq[i]);
                }
            }

            break;
        default: printf("\nERRORE COMANDO EQUIPAGGIAMENTO\n");
    }
}


void displayStat_int(pg_t pg) {
    int tmp,i;


    printf("le statistiche del pg sono: \n");
    for(tmp=pg.stat.hp,i=0;i<pg.equip->inUso;i++)
        tmp+=getHP(pg.equip->vettEq[i]);
    if(tmp<1) tmp=1;
    printf("hp: %d\n",tmp);
    for(tmp=pg.stat.mp,i=0;i<pg.equip->inUso;i++)
        tmp+=getMP(pg.equip->vettEq[i]);
    if(tmp<1) tmp=1;
    printf("mp: %d\n",tmp);
    for(tmp=pg.stat.atk,i=0;i<pg.equip->inUso;i++)
        tmp+=getATK(pg.equip->vettEq[i]);
    if(tmp<1) tmp=1;
    printf("atk: %d\n",tmp);
    for(tmp=pg.stat.def,i=0;i<pg.equip->inUso;i++)
        tmp+=getDEF(pg.equip->vettEq[i]);
    if(tmp<1) tmp=1;
    printf("def: %d\n",tmp);
    for(tmp=pg.stat.mag,i=0;i<pg.equip->inUso;i++)
        tmp+=getMAG(pg.equip->vettEq[i]);
    if(tmp<1) tmp=1;
    printf("mag: %d\n",tmp);
    for(tmp=pg.stat.spr,i=0;i<pg.equip->inUso;i++)
        tmp+=getSPR(pg.equip->vettEq[i]);
    if(tmp<1) tmp=1;
    printf("spr: %d\n",tmp);
}

void displayStat(struct tabPg_t *tabPg,char *key){
    pg_t pg;
    if(searchPg(tabPg,key)==NULL){
        printf("PG non presente nella lista;\n");
        return;
    }
    pg=searchPg(tabPg,key)->pg;
    displayStat_int(pg);
}


void displayPg(link node){
    int i;

    printf("codice: %s\nnome: %s\nclasse: %s\n",node->pg.codice,node->pg.nome,node->pg.classe);
    if(node->pg.equip->inUso==0){
        printf("il PG non ha ancora nessun equipaggiamento.\n");
    }else{
        printf("sono in uso su questo pg %d oggetti:\n", node->pg.equip->inUso);
        for (i = 0; i < node->pg.equip->inUso; i++)
            displayObj(node->pg.equip->vettEq[i]);
    }
    displayStat_int(node->pg);
}

void freePG(pg_t *pg){
    free(pg->equip->vettEq);
    free(pg->equip);
}


void freeListR(link head){
    if(head==NULL) return;

    freeListR(head->next);
    freePG(&head->pg);
    free(head);
}

void freeTabList(struct tabPg_t *tabPg){
    freeListR(tabPg->headPg);
    free(tabPg);
}


void displayList(struct tabPg_t *tabPg){
    link x;
    for(x=tabPg->headPg;x!=NULL;x=x->next) {
        displayPg(x);
        printf("\n\n");
        for (int i = 0; i < 50; i++) printf("_");
    }

}
