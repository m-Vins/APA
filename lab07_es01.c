#include <stdio.h>
#include <stdlib.h>

typedef enum {z,r,t,s,err}tipo;
typedef struct {
    tipo pietra;
    int n;//numero di pietre
}t_val;



int disp(int pos, t_val *val, tipo *sol, int n);
int disp_wrapper(t_val *val);
//int valida(tipo *arr, int arr_count);
void stampa(tipo *arr, int arr_count);


int main() {
    t_val *val;
    int r_file;
    FILE *fp;

    val=(t_val *)malloc(err*sizeof(t_val));
    for(int i=0;i<err;i++) val[i].pietra=i;


    fp=fopen("f2.txt","r");


    fscanf(fp,"%d\n",&r_file);
    for(int i=0;i<r_file;i++){
        fscanf(fp,"%d%d%d%d\n",&val[0].n,&val[1].n,&val[2].n,&val[3].n);
        printf("\n\nzaffiro: %d, rubino: %d, topazio: %d ,smeraldo: %d\n",val[0].n,val[1].n,val[2].n,val[3].n);
        printf("\nlunghezza collana: %d\n\n",disp_wrapper(val));
        printf("\n");
        for(int j=0;j<15;j++) printf("-");
    }
    fclose(fp);

    return 0;
}

int disp_wrapper(t_val *val){
    int n=0,i;
    tipo *sol;

    //totale pietre
    for(i=0;i<err;i++)  n+=val[i].n;

    for(i=n;i>0;i--){
        sol=malloc(i* sizeof(tipo));
        if(disp(0,val,sol,i)) {
            free(sol);
            return i;
        }
        free(sol);
    }
    return -1;
}

int disp(int pos, t_val *val, tipo *sol, int n){
    int i;
    //condizione di terminazione
    if(pos>=n){
        stampa(sol,pos);
        return 1;
    }

    if(pos==0){
        for(i=0;i<err;i++){
            val[i].n--;
            sol[pos]=val[i].pietra;
            if(disp(pos+1,val,sol,n)) return 1;
            val[i].n++;//backtrack
        }
    }else {
        if(sol[pos-1]==z||sol[pos-1]==t){
            if(val[z].n>0){
                val[z].n--;
                sol[pos]=val[z].pietra;
                if(disp(pos+1,val,sol,n)) return 1;
                val[z].n++;//backtrack
            }
            if(val[r].n>0){
                val[r].n--;
                sol[pos]=val[r].pietra;
                if(disp(pos+1,val,sol,n)) return 1;
                val[r].n++;//backtrack
            }
        }else if(sol[pos-1]==s||sol[pos-1]==r){
            if(val[s].n>0){
                val[s].n--;
                sol[pos]=val[s].pietra;
                if(disp(pos+1,val,sol,n)) return 1;
                val[s].n++;//backtrack
            }
            if(val[t].n>0){
                val[t].n--;
                sol[pos]=val[t].pietra;
                if(disp(pos+1,val,sol,n)) return 1;
                val[t].n++;//backtrack
            }
        }
    }
    return 0;
}
//cotrolla che tra l'ultima pietra e la prima
//le regole vengano rispettate
int valida(tipo *arr, int arr_count){

    if(arr[arr_count-1]==r||arr[arr_count-1]==s){
        if(*arr==s||*arr==t)
            return 1;
        return 0;
    }else if(arr[arr_count-1]==z||arr[arr_count-1]==t){
        if(*arr==z||*arr==r)
            return 1;
        return 0;
    }

    return 0;
}
void stampa(tipo *arr, int arr_count){
    int i;

    printf("\nla sequenza della collana è:\n");
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
    printf("");
};
