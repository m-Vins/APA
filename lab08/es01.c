#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int i,f;
}att;

typedef struct {
    att *array;
    int time, arr_count;
}BSol_t;

int compatibilty(att x1,att x2);
int getTime(att *sol, int n);
void powerSet(int pos, att *val, att *sol, int k, int start,BSol_t *BestSol);
void newSol(att *BestSol,att *tmp,int k);
void attSel(int N,att *v);
void bubblesort(att *array, int arr_count);

int main() {
    att attivity[6];
    int N,i;
    printf("inserire numero intervalli: ");
    scanf("%d",&N);
    for(i=0;i<N;i++){
        printf("\n[%d]inserire Ti e Tf: ",i);
        scanf("%d%d",&attivity[i].i,&attivity[i].f);
    }
    printf("\n");
    attSel(N,attivity);
    return 0;
}

void attSel(int N,att *v){
    BSol_t *BestSol=malloc(sizeof(BSol_t));
    BestSol->array=malloc(N* sizeof(att));
    att *sol=malloc(N* sizeof(att));

    bubblesort(v,N);

    powerSet(0,v,sol,N,0,BestSol);
    printf("la soluzione migliore ha %d intervalli,e durata totale pari a: %d\n",BestSol->arr_count,BestSol->time);
    for(int i=0;i<BestSol->arr_count;i++){
        printf("(%d,%d)\n",BestSol->array[i].i,BestSol->array[i].f);
    }
}

void powerSet(int pos, att *val, att *sol, int k, int start,BSol_t *BestSol){
    int i;
    if(start>=k){
        if(getTime(sol,pos)>BestSol->time){
            BestSol->time=getTime(sol,pos);
            BestSol->arr_count=pos;
            newSol(BestSol->array,sol,pos);
        }
        return;
    }

    for(i=start;i<k;i++){
        if(pos==0||compatibilty(sol[pos-1],val[i])){
            sol[pos]=val[i];
            powerSet(pos+1, val, sol,k,i+1,BestSol);
        }
    }
    powerSet(pos,val,sol,k,k,BestSol);
}

int compatibilty(att x1,att x2){
    return (x1.f<=x2.i);
}

int getTime(att *sol, int n){
    int t=0,i;
    for(i=0;i<n;i++)
        t+=(sol[i].f-sol[i].i);
    return t;
}

void newSol(att *BestSol,att *tmp,int k){
    int i;
    for(i=0;i<k;i++){
        BestSol[i]=tmp[i];
    }
}

void bubblesort(att *array, int arr_count){
    int i,j,l=0,r=arr_count-1;
    att tmp;

    for(i=l;i<r;i++){
        for(j=l;j<l-i+r;j++){
            if(array[j].i>array[j+1].i){
                tmp=array[j];
                array[j]=array[j+1];
                array[j+1]=tmp;
            }
        }
    }
}
