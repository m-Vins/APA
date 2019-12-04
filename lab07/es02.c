#include <stdio.h>
#include <stdlib.h>
#define FileName "test.txt"
#define DBG 0

typedef enum {z,r,t,s,err}pietre_t;

typedef struct {
    pietre_t p;
    int val;
}val_t;

typedef struct{
    val_t item;
    int n;
}wrapper_t;


void initItem(wrapper_t *ptr);
void disp(int pos, wrapper_t *pietre, pietre_t *sol, int n, int maxRip, int contRip, int nz, int ns,int *BestVal, pietre_t *BestSol,int *trovato);
int disp_wrapper(wrapper_t *pietre, int maxRip,pietre_t *Bestsol,int n);
void stampa(pietre_t *arr, int arr_count);
int getVal(wrapper_t *valori, pietre_t *arr, int arr_count);


int main() {
    wrapper_t *pietre;
    int i,n=0,l_sol,maxRip,nr,j;
    pietre_t *sol;
    FILE *fp;

#if DBG
    initItem(pietre);
    printf("inserire maxRip: ");
    scanf("%d",&maxRip);

    for(i=0;i<err;i++)
        n+=pietre[i].n;

    sol=malloc(n* sizeof(pietre_t));
    l_sol=disp_wrapper(pietre,maxRip,sol,n);
    printf("la sequenza della collana è :\n");
    stampa(sol,l_sol);
    printf("\ndi lunghezza %d e valore %d",l_sol,getVal(pietre,sol,l_sol));
#endif

    fp=fopen(FileName,"r");
    if(fp==NULL){
        printf("ERRORE FILE");
        return -1;
    }
    fscanf(fp,"%d\n",&nr);
    pietre=malloc(err * sizeof(wrapper_t));

    for(i=0;i<err;i++) pietre[i].item.p=i;

    for(i=0;i<nr;i++){
        fscanf(fp,"%d%d%d%d%d%d%d%d%d\n",&pietre[0].n,&pietre[1].n,&pietre[2].n,&pietre[3].n,&pietre[0].item.val,
                &pietre[1].item.val,&pietre[2].item.val,&pietre[3].item.val,&maxRip);
        printf("zaffiro=%d[%d], rubino=%d[%d],topazio= %d[%d],smeraldo= %d[%d],\nmaxRip=%d\n",
                pietre[0].n,pietre[0].item.val,pietre[1].n,pietre[1].item.val,pietre[2].n,pietre[2].item.val,pietre[3].n,
                pietre[3].item.val,maxRip);
        n=0;
        for(j=0;j<err;j++)
            n+=pietre[i].n;

        sol=malloc(n* sizeof(pietre_t));
        l_sol=disp_wrapper(pietre,maxRip,sol,n);
        printf("la sequenza della collana è :\n");
        stampa(sol,l_sol);
        printf("di lunghezza %d e valore %d\n",l_sol,getVal(pietre,sol,l_sol));
        for(j=0;j<50;j++) printf("_");
        printf("\n");
    }
    fclose(fp);


    return 0;
}

void initItem(wrapper_t *ptr) {
    char nome[4][9] = {"zaffiro", "smeraldo", "rubino", "topazio"};
    int i,tmp;
    printf("\n");
    for(i=0;i<err;i++){
        ptr[i].item.p=i;
        printf("inserire valore %s: ",nome[i]);
        scanf("%d",&tmp);
        ptr[i].item.val=tmp;
        printf("\ninserire numero %s: ",nome[i]);
        scanf("%d",&tmp);
        ptr[i].n=tmp;
        printf("\n");
    }
    printf("\n");
}

int getVal(wrapper_t *valori, pietre_t *arr, int arr_count){
    int i,j;
    int sum=0;
    for(i=0;i<arr_count;i++){
        for(j=0;j<err;j++){
            if(arr[i]==valori[j].item.p)
                sum+=valori[j].item.val;
        }
    }
    return sum;
}
void newBestSol(pietre_t *sol1,pietre_t *sol2,int arr_c){
    for(int i=0;i<arr_c;i++)
        sol1[i]=sol2[i];
}

int disp_wrapper(wrapper_t *pietre, int maxRip,pietre_t *Bestsol,int n){
    pietre_t *sol;
    int i,trovato=0;
    int BestVal=0;

    for(i=n;i>0&&!trovato;i--){
        sol=malloc(i* sizeof(pietre_t));
        disp(0,pietre,sol,i,maxRip,0,0,0,&BestVal,Bestsol,&trovato);
        free(sol);
    }
    return i+1;
}


void disp(int pos, wrapper_t *pietre, pietre_t *sol, int n, int maxRip, int contRip, int nz, int ns,int *BestVal, pietre_t *BestSol, int *trovato){
    int i;

    if(pos>=n){
        if(*BestVal<getVal(pietre,sol,n)&&nz<=ns){
            *BestVal=getVal(pietre,sol,n);
            newBestSol(BestSol,sol,n);
            *trovato=1;
        }
        return ;
    }

    if(pos==0){
        for(i=0;i<err;i++){
            switch (i) {
                case z:
                    pietre[i].n--;
                    sol[pos] = pietre[i].item.p;
                    disp(pos + 1, pietre, sol, n, maxRip, contRip + 1, 1, 0, BestVal, BestSol,trovato);
                    pietre[i].n++;
                    break;
                case s:
                    pietre[i].n--;
                    sol[pos] = pietre[i].item.p;
                    disp(pos + 1, pietre, sol, n, maxRip, contRip + 1, 0, 1, BestVal, BestSol,trovato);
                    pietre[i].n++;
                    break;
                default:
                    pietre[i].n--;
                    sol[pos] = pietre[i].item.p;
                    disp(pos + 1, pietre, sol, n, maxRip, contRip + 1, 0, 0, BestVal, BestSol,trovato);
                    pietre[i].n++;
            }
        }
    }else{
        if(sol[pos-1]==z||sol[pos-1]==t){
            if(pietre[z].n > 0){
                pietre[z].n--;
                sol[pos] = pietre[z].item.p;
                if(sol[pos-1]==z&&contRip<maxRip)
                    disp(pos + 1, pietre, sol, n, maxRip, contRip + 1, nz + 1, ns, BestVal, BestSol,trovato);
                else if(sol[pos-1]==t)
                    disp(pos + 1, pietre, sol, n, maxRip, 1, nz + 1, ns, BestVal, BestSol,trovato);
                pietre[z].n++;//backtrack

            }
            if(pietre[r].n > 0){
                pietre[r].n--;
                sol[pos] = pietre[r].item.p;
                disp(pos + 1, pietre, sol, n, maxRip, 1, nz, ns, BestVal, BestSol,trovato);
                pietre[r].n++;//backtrack
            }
        }else if(sol[pos-1]==s||sol[pos-1]==r){
            if(pietre[s].n > 0){
                pietre[s].n--;
                sol[pos] = pietre[s].item.p;
                if(sol[pos-1]==s&&contRip<maxRip)
                    disp(pos + 1, pietre, sol, n, maxRip, contRip + 1, nz, ns+1, BestVal, BestSol,trovato);
                else if(sol[pos-1]==r)
                    disp(pos + 1, pietre, sol, n, maxRip, 1, nz, ns+1, BestVal, BestSol,trovato);
                pietre[s].n++;//backtrack
            }
            if(pietre[t].n > 0){
                pietre[t].n--;
                sol[pos] = pietre[t].item.p;
                disp(pos + 1, pietre, sol, n, maxRip, 1, nz, ns, BestVal, BestSol,trovato);
                pietre[t].n++;//backtrack
            }
        }
    }
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
