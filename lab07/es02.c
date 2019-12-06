#include <stdio.h>
#include <stdlib.h>
#define FileName "test.txt"
#define DBG 0


typedef enum {z,r,t,s,err}pietre_t;

typedef struct {
    pietre_t p;
    int val;
    int n;
}item_t;

typedef struct {
    pietre_t *pietre;
    int val,n;
}itemSol_t;

int getVal(item_t *val, pietre_t *arr, int arr_count);
void newSol(itemSol_t *BestSol, pietre_t *sol,int n,int val);
void dispR(int pos, item_t *val,pietre_t *sol, int n, int maxRip, int contRip,itemSol_t *BestSol,int *trovato);
void disp(item_t *val,int n,int maxRip,itemSol_t *BestSol);
int valida(pietre_t *sol, int n);
void stampa(pietre_t *arr, int arr_count);

int main() {
    itemSol_t *BestSol;
    char nomi[4][9]={"zaffiro","rubino","topazio","smeraldo"};
    item_t *pietre=malloc(err* sizeof(item_t));
    int tot,i,maxRip,n_test,j;
    FILE *f;

    //inizializzo le pietre
    for(i=0;i<err;i++) pietre[i].p=i;

    BestSol=malloc(sizeof(itemSol_t));

#if DBG
    tot=0;
    for(i=0;i<err;i++){
        printf("inserire numero pietre [%s]: ",nomi[i]);
        scanf("%d",&pietre[i].n);
        printf("di valore: ");
        scanf("%d",&pietre[i].val);
        tot+=pietre[i].n;
    }
    printf("inserire maxRip: ");
    scanf("%d",&maxRip);


    BestSol->pietre=malloc(tot* sizeof(pietre_t));

    disp(pietre,tot,maxRip,BestSol);

    printf("\nla soluzione ha valore: %d \nnumero pietre: %d \n",BestSol->val,BestSol->n);
    stampa(BestSol->pietre,BestSol->n);

    free(BestSol->pietre);

#endif

    f=fopen(FileName,"r");
    if(f==NULL){
        printf("ERRORE FILE");
        return -1;
    }
    fscanf(f,"%d\n",&n_test);
    for(i=0;i<n_test;i++){
        printf("TEST %d\n",i);
        fscanf(f,"%d%d%d%d%d%d%d%d%d\n",&pietre[0].n,&pietre[1].n,&pietre[2].n,&pietre[3].n,
               &pietre[0].val,&pietre[1].val,&pietre[2].val,&pietre[3].val,&maxRip);

        for(tot=0,j=0;j<err;j++) tot+=pietre[j].n;//totale pietre
        printf("totale pietre: %d",tot);

        BestSol->pietre=malloc(tot* sizeof(pietre_t));

        disp(pietre,tot,maxRip,BestSol);

        //output risultato
        printf("\nla soluzione ha valore: %d \nnumero pietre: %d \n",BestSol->val,BestSol->n);
        stampa(BestSol->pietre,BestSol->n);
        for(j=0;j<50;j++) printf("_");
        printf("\n");

        free(BestSol->pietre);
    }


    free(BestSol);


    return 0;
}

void disp(item_t *val,int n,int maxRip,itemSol_t *BestSol){
    int i, trovato=0;
    pietre_t *sol=malloc(n*sizeof(pietre_t));

    BestSol->val=BestSol->n=0;

    for(i=n;i>0&&!trovato;i--){
        dispR(0,val,sol,i,maxRip,0,BestSol,&trovato);
    }
    free(sol);
}
void dispR(int pos, item_t *val,pietre_t *sol, int n, int maxRip, int contRip,itemSol_t *BestSol,int *trovato){
    int i;

    if(pos>=n){
        if(getVal(val,sol,n)>BestSol->val&&valida(sol,n)){
            newSol(BestSol,sol,n,getVal(val,sol,n));
            *trovato=1;
        }
        return;
    }

    if(pos==0){
        for(i=0;i<err;i++) {
            val[i].n--;
            sol[pos]=val[i].p;
            dispR(pos + 1, val, sol, n, maxRip, 1,BestSol, trovato);
            val[i].n++;
        }
    }else {
        switch (sol[pos-1]){
            case z:
                if(val[z].n>0&&contRip<maxRip){
                    val[z].n--;
                    sol[pos]=val[z].p;
                    dispR(pos+1,val,sol,n,maxRip,contRip+1,BestSol,trovato);
                    val[z].n++;
                }
                if(val[r].n>0){
                    val[r].n--;
                    sol[pos]=val[r].p;
                    dispR(pos+1,val,sol,n,maxRip,1,BestSol,trovato);
                    val[r].n++;
                }
                break;
            case r:
                if(val[s].n>0){
                    val[s].n--;
                    sol[pos]=val[s].p;
                    dispR(pos+1,val,sol,n,maxRip,1,BestSol,trovato);
                    val[s].n++;
                }
                if(val[t].n>0){
                    val[t].n--;
                    sol[pos]=val[t].p;
                    dispR(pos+1,val,sol,n,maxRip,1,BestSol,trovato);
                    val[t].n++;
                }
                break;
            case t:
                if(val[z].n>0){
                    val[z].n--;
                    sol[pos]=val[z].p;
                    dispR(pos+1,val,sol,n,maxRip,1,BestSol,trovato);
                    val[z].n++;
                }
                if(val[r].n>0){
                    val[r].n--;
                    sol[pos]=val[r].p;
                    dispR(pos+1,val,sol,n,maxRip,1,BestSol,trovato);
                    val[r].n++;
                }
                break;
            case s:
                if(val[s].n>0&&contRip<maxRip){
                    val[s].n--;
                    sol[pos]=val[s].p;
                    dispR(pos+1,val,sol,n,maxRip,contRip+1,BestSol,trovato);
                    val[s].n++;
                }
                if(val[t].n>0){
                    val[t].n--;
                    sol[pos]=val[t].p;
                    dispR(pos+1,val,sol,n,maxRip,1,BestSol,trovato);
                    val[t].n++;
                }
                break;
            default:
                printf("ERRORE SWITCH");
        }
    }
}

int getVal(item_t *val, pietre_t *arr, int arr_count){
    int i,j;
    int sum=0;
    for(i=0;i<arr_count;i++){
        for(j=0;j<err;j++){
            if(arr[i]==val[j].p){
                sum+=val[j].val;
            }
        }
    }
    return sum;
}

void newSol(itemSol_t *BestSol, pietre_t *sol,int n,int val){
    int i;
    BestSol->n=n;
    BestSol->val=val;
    for(i=0;i<n;i++){
        BestSol->pietre[i]=sol[i];
    }
}

int valida(pietre_t *sol, int n){
    int i,nz=0,ns=0;
    for(i=0;i<n;i++){
        switch(sol[i]){
            case z: nz++;
                break;
            case s: ns++;
                break;
        }
    }
    return nz<=ns;
}

void stampa(pietre_t *arr, int arr_count){
    int i;

    for(i=0;i<arr_count;i++){
        switch ((int)arr[i]){
            case z:
                printf("z");
                break;
            case r:
                printf("r");
                break;
            case t:
                printf("t");
                break;
            case s:
                printf("s");
                break;
            default: printf("|");
        }
    }
    printf("\n");
}
