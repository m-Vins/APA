/*applicabilità della programmazione dinamica:
 *
 * ipotesi:  sol[k] massimo, P vettore con gli indici degli elementi precedenti nella soluzione.
 *
 * la sottosoluzione sol[P[k-1]] deve essere la massima possibile, altrimenti se così non fosse
 * avremmo sol'[k]=sol'[P[k-1]]+val[k]>sol[k] e contraddice l'ipotesi sol[k]= massima soluzione.
 *
 *
 * la sottosoluzione sol[X] del problema è data da due possibili casi:
 *
 * sol[X(N-1)]:=   -max(val[X(N-1)]+val[X(i)])     dove 0 <= i < N-1 e sia verificata la compatibiltà tra X(N-1) e X(i)
 *                 -val[X(N)]                      se N=1
 *
 *
*/
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int i,f;
    int val;
}att;

int compatibilty(att x1,att x2){
    return (x1.f<=x2.i);
}

void DisplaySol(att *time, int *P,int i){
    if(P[i]==-1) {
        printf("%d-%d\n",time[i].i,time[i].f);
        return;
    }
    DisplaySol(time,P,P[i]);
    printf("%d-%d\n",time[i].i,time[i].f);
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

void DP(att *time, int N){
    int i,j,max,BestR=0;
    int Value[N],P[N],last=1;

    Value[0]=time[0].val;
    P[0]=-1;


    for(i=1;i<N;i++){
        Value[i]=time[i].val;
        P[i]=-1;
        for(j=0,max=0;j<i;j++){
            if(compatibilty(time[j], time[i]) && Value[j] > max){
                max=Value[j];
                Value[i]= Value[j] + time[i].val;
                P[i]=j;
            }
        }

        if(BestR<Value[i]){
            BestR=Value[i];
            last=i;
        }
    }
    printf("the Best Solution is:\n");
    DisplaySol(time,P,last);
    printf("and the total time is: %d.",BestR);
}



int main() {
    att *attivity;
    int N,i;
    printf("inserire numero intervalli: ");
    scanf("%d",&N);
    attivity=malloc(N*sizeof(att));
    for(i=0;i<N;i++){
        printf("\n[%d]inserire Ti e Tf: ",i);
        scanf("%d%d",&attivity[i].i,&attivity[i].f);
        attivity[i].val=attivity[i].f-attivity[i].i;
    }
    printf("\n");
bubblesort(attivity,N);
DP(attivity,N);


    return 0;
}
