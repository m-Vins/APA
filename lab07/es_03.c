#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FileNamePG "pg.txt"
#define FileNameINV "inv.txt"
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

typedef enum {c_add,c_remove}c_equip;
typedef enum {c_loadListPg,c_loadObj,c_newPg,c_delPg,c_editEquipPg,c_stat,c_exit,c_err}c_com;


tabInv_t *creaTabInv(void);
void freeTabInv(tabInv_t *tabInv);
void addObj(tabInv_t *tabInv,inv_t obj);
void addObj_wrapper(tabInv_t *tabInv,FILE *fp);

tabPg_t *creaListaPg(void);
link newNode(pg_t pg,link next);
void loadPg(tabPg_t *tabPg, FILE *fp);
link searchPg(link head,char *key);
link deletePg(link head, char *key);
void editEquipPg(link head,char *key,tabInv_t *tabInv);
void displayStat(tabPg_t *tabPg,char *key);
void freeTabList(tabPg_t *tabPg);

c_com leggicomando();

int main() {
    int esci=0;
    char key[7];
    tabPg_t *tabPg=NULL;
    tabInv_t *tabInv=NULL;
    FILE *fp;

    while(!esci){
        switch (leggicomando()){
            case c_loadListPg:
                tabPg=creaListaPg();
                fp=fopen(FileNamePG,"r");
                loadPg(tabPg,fp);
                fclose(fp);
                break;
            case c_loadObj:
                tabInv=creaTabInv();
                fp=fopen(FileNameINV,"r");
                addObj_wrapper(tabInv,fp);
                fclose(fp);
                break;
            case c_newPg:
                loadPg(tabPg,stdin);
                break;
            case c_delPg:
                printf("inserire codice PG:\n");
                scanf("%s",key);
                tabPg->headPg=deletePg(tabPg->headPg,key);
                break;
            case c_editEquipPg:
                printf("inserire codice PG:\n");
                scanf("%s",key);
                editEquipPg(tabPg->headPg,key,tabInv);
                break;
            case c_stat:
                printf("inserire codice PG:\n");
                scanf("%s",key);
                displayStat(tabPg,key);
                break;
            case c_exit:
                esci=1;
                break;
            case c_err:
                printf("comando errato\n");
                break;
        }
    }


    freeTabInv(tabInv);
    freeTabList(tabPg);
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

void freeTabList(tabPg_t *tabPg){
    freeListR(tabPg->headPg);
    free(tabPg);
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
    for(x=tabPg->headPg;x->next!=NULL;x=x->next);
    tabPg->tailPg=x;
}

link searchPg(link head,char *key){
    link x;

    for(x=head;x!=NULL;x=x->next){

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
            freePG(&x->pg);
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


c_com leggicomando(){
    int cmd;
    printf("\ninserire numero comando:\n");
    printf("[1]carica elenco PG;\n[2]carica elenco oggetto;\n");
    printf("[3]aggiungi PG;\n[4]elimina PG;\n[5]modifica equipaggiamento Pg;\n");
    printf("[6]calcola statistiche;\n[7]EXIT;\n");
    if(scanf("%d",&cmd)==1&&cmd>=0&&cmd<=c_err)
        return (c_com)cmd-1;
    return c_err;
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
