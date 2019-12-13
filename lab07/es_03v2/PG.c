//
// Created by vins on 10/12/19.
//

#include "PG.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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
    link x;
    pg_t tmp;
    if(fp==stdin){
        fscanf(fp,"%s%s%s%d%d%d%d%d%d",tmp.codice,tmp.nome,tmp.classe,
               &tmp.stat.hp,&tmp.stat.mp,&tmp.stat.atk,&tmp.stat.def,&tmp.stat.mag,
               &tmp.stat.spr);
        tmp.equip=malloc(sizeof(tabEquip_t));
        tmp.equip->inUso = 0;
        tmp.equip->vettEq = malloc(8 * sizeof(inv_t));
        tabPg->headPg=newNode(tmp,tabPg->headPg);
    }else {

        while(fscanf(fp, "%s%s%s%d%d%d%d%d%d", tmp.codice, tmp.nome, tmp.classe,
                     &tmp.stat.hp, &tmp.stat.mp, &tmp.stat.atk, &tmp.stat.def, &tmp.stat.mag,
                     &tmp.stat.spr)!=EOF){
            tmp.equip=malloc(sizeof(tabEquip_t));
            tmp.equip->inUso = 0;
            tmp.equip->vettEq = malloc(8 * sizeof(inv_t));
            tabPg->headPg = newNode(tmp, tabPg->headPg);
        }
    }
    for(x=tabPg->headPg;x!=NULL;x=x->next);
    tabPg->tailPg=x;
}

link searchPg(link head,char *key){
    link x,p;

    for(x=head;x!=NULL;p=x,x=x->next){

        if(strcmp(x->pg.codice,key)==0)
            return x;
    }
    return NULL;
}

link deletePg(link head, char *key){
    link x,p;
    if(head==NULL) return NULL;
    for(x=head,p=NULL;x!=NULL;p=x,x=x->next){
        if(strcmp(x->pg.codice,key)==0){
            if(x==head)
                head=x->next;
            else
                p->next=x->next;
            free(x);
            break;
        }
    }
    return head;
}

void editEquipPg(link head,char *key,tabInv_t *tabInv){
    int i,cmd,n;
    pg_t pg;
    if(searchPg(head,key)==NULL){
        printf("il PG non è presentenella lista\n");
        return;
    }
    pg=searchPg(head,key)->pg;

    if(pg.equip->inUso==0){
        printf("il pg non ha ancora nessun equipaggiamento.\n");
    }else {
        printf("sono in uso su questo pg %d oggetti:\n", pg.equip->inUso);
        for (i = 0; i < pg.equip->inUso; i++)
            printf("[%d] nome: %s, tipo: %s\n",i+1, pg.equip->vettEq[i]->nome, pg.equip->vettEq[i]->tipo);
    }
    printf("inserire comando: (0):aggiungi oggetto-(1)rimuovi oggetto\n");
    scanf("%d",&cmd);

    switch((c_equip)cmd){
        case c_add:
            printf("nell'inventario ci sono i seguenti oggetti:\n");
            for(i=0;i<tabInv->nInv;i++) printf("[%d] nome: %s, tipo: %s\n",i+1,tabInv->vettInv[i].nome,tabInv->vettInv[i].tipo);
            printf("inserire numero oggetto da aggiungere fino a un max di 8,\npoi premere zero per uscire\n");
            while(scanf("%d",&n)==1&&n!=0&&pg.equip->inUso<8){
                if(n-1<0||n-1>tabInv->nInv){
                    printf("errore numero oggetto\n");
                }else {
                    pg.equip->vettEq[pg.equip->inUso++] = &(tabInv->vettInv[n-1]);
                }
            }
            break;
        case c_remove:
            printf("inserire numero oggetto da rimuovere,\npoi premere zero per uscire\n");
            while(scanf("%d",&n)==1&&n!=0&&pg.equip->inUso>0){
                if(n-1<0||n-1>pg.equip->inUso){
                    printf("errore numero oggetto");
                }else{
                    pg.equip->inUso--;
                    for(i=n-1;i<pg.equip->inUso;i++){
                        pg.equip->vettEq[i]=pg.equip->vettEq[i+1];//traslo tutta la parte successiva
                    }
                    for (i = 0; i < pg.equip->inUso; i++)
                        printf("[%d] nome: %s, tipo: %s\n",i+1, pg.equip->vettEq[i]->nome, pg.equip->vettEq[i]->tipo);
                }
            }

            break;
        default: printf("\nERRORE COMANDO EQUIPAGGIAMENTO\n");
    }
}




void displayStat(tabPg_t *tabPg,char *key){
    pg_t pg;
    int tmp,i;
    if(searchPg(tabPg->headPg,key)==NULL){
        printf("PG non presente nella lista;\n");
        return;
    }
    pg=searchPg(tabPg->headPg,key)->pg;
    printf("le statistiche del pg sono: \n");
    for(tmp=pg.stat.hp,i=0;i<pg.equip->inUso;i++)
        tmp+=pg.equip->vettEq[i]->stat.hp;
    if(tmp<1) tmp=1;
    printf("hp: %d\n",tmp);
    for(tmp=pg.stat.mp,i=0;i<pg.equip->inUso;i++)
        tmp+=pg.equip->vettEq[i]->stat.mp;
    if(tmp<1) tmp=1;
    printf("hp: %d\n",tmp);
    for(tmp=pg.stat.atk,i=0;i<pg.equip->inUso;i++)
        tmp+=pg.equip->vettEq[i]->stat.atk;
    if(tmp<1) tmp=1;
    printf("hp: %d\n",tmp);
    for(tmp=pg.stat.def,i=0;i<pg.equip->inUso;i++)
        tmp+=pg.equip->vettEq[i]->stat.def;
    if(tmp<1) tmp=1;
    printf("hp: %d\n",tmp);
    for(tmp=pg.stat.mag,i=0;i<pg.equip->inUso;i++)
        tmp+=pg.equip->vettEq[i]->stat.mag;
    if(tmp<1) tmp=1;
    printf("hp: %d\n",tmp);
    for(tmp=pg.stat.spr,i=0;i<pg.equip->inUso;i++)
        tmp+=pg.equip->vettEq[i]->stat.spr;
    if(tmp<1) tmp=1;
    printf("hp: %d\n",tmp);
}


void displayPg(tabPg_t *tabPg, char *key){
    int i;
    pg_t pg=searchPg(tabPg->headPg,key)->pg;

    printf("codice: %s\nnome: %s\nclasse: %s\n",pg.codice,pg.nome,pg.classe);
    if(pg.equip->inUso==0){
        printf("il PG non ha ancora nessun equipaggiamento.\n");
    }else{
        printf("sono in uso su questo pg %d oggetti:\n", pg.equip->inUso);
        for (i = 0; i < pg.equip->inUso; i++)
            printf("[%d] nome: %s, tipo: %s\n",i+1, pg.equip->vettEq[i]->nome, pg.equip->vettEq[i]->tipo);
    }
    displayStat(tabPg,key);
}
