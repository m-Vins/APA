
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


void DP(att *time, int N){
    int i,j,max,BestR=0;
    int Value[N],P[N],last=1;

    Value[0]=1;
    P[0]=-1;


    for(i=1;i<N;i++){
        Value[i]=1;
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

DP(attivity,N);
    
    free(attivity);


    return 0;
}
