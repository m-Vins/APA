#include <stdio.h>
#include <stdlib.h>

typedef enum {z,r,t,s,err}pietra;

typedef struct {
    pietra p;
    int n;
}item;

int ****memorySol;


int max(int n1, int n2) {
    return n1>n2 ? n1:n2;
}

void MEMORYSOLinit(int z, int r,int t, int s);
void MEMORYSOLfree(int z, int r, int t);
void MEMORYSOLcanc(int z, int r,int t, int s);
int searchSol(item *val);

int main() {
    char *nomi[]={"zaffiro","rubino","topazio","smeraldo"};
    item pietre[err];

    for(int i=0;i<err;i++) {
        printf("inserire numero pietre %s: ",nomi[i]);
        scanf("%d",&pietre[i].n);
        pietre[i].p = i;
    }
    MEMORYSOLinit(pietre[z].n,pietre[r].n,pietre[t].n,pietre[s].n);
    printf("\nla soluzione migliore ha lunghezza %d",searchSol(pietre));
    MEMORYSOLfree(pietre[z].n,pietre[r].n,pietre[t].n);
    return 0;
}


int fT(int z, int r, int t, int s);
int fS(int z, int r, int t, int s);

int fZ(int z, int r, int t, int s){
    if(z == 0) return 0;
    if(memorySol[z][r][t][s] != -1) return memorySol[z][r][t][s];
    memorySol[z][r][t][s]= 1 + max(fZ(z - 1, r, t, s), fT(z - 1, r, t, s));
    return memorySol[z][r][t][s];
}
int fR(int z, int r, int t, int s){
    if(r == 0) return 0;
    if(memorySol[z][r][t][s] != -1) return memorySol[z][r][t][s];
    memorySol[z][r][t][s] = 1 + max(fZ(z, r - 1, t, s), fT(z, r - 1, t, s));
    return memorySol[z][r][t][s];
}
int fT(int z, int r, int t, int s){
    if(t == 0) return 0;
    if(memorySol[z][r][t][s] != -1) return memorySol[z][r][t][s];
    memorySol[z][r][t][s] = 1 + max(fS(z, r, t - 1, s), fR(z, r, t - 1, s));
    return memorySol[z][r][t][s];
}
int fS(int z, int r, int t, int s){
    if(s == 0) return 0;
    if(memorySol[z][r][t][s] != -1) return memorySol[z][r][t][s];
    memorySol[z][r][t][s] = 1 + max(fS(z, r, t, s - 1), fR(z, r, t, s - 1));
    return memorySol[z][r][t][s];
}

int searchSol(item *val){
    int tmp,max;
    max=fZ(val[z].n,val[r].n,val[t].n,val[s].n);
    MEMORYSOLcanc(val[z].n,val[r].n,val[t].n,val[s].n);
    tmp=fT(val[z].n,val[r].n,val[t].n,val[s].n);
    MEMORYSOLcanc(val[z].n,val[r].n,val[t].n,val[s].n);
    if(tmp>max) max=tmp;
    tmp=fR(val[z].n,val[r].n,val[t].n,val[s].n);
    MEMORYSOLcanc(val[z].n,val[r].n,val[t].n,val[s].n);
    if(tmp>max) max=tmp;
    tmp=fS(val[z].n,val[r].n,val[t].n,val[s].n);
    MEMORYSOLcanc(val[z].n,val[r].n,val[t].n,val[s].n);
    if(tmp>max) max=tmp;
    return max;
}

void MEMORYSOLinit(int z, int r,int t, int s){
        memorySol = (int ****) malloc((1+z) * sizeof(int ***));
        for (int i = 0; i <= z; i++) {
            memorySol[i] = (int ***) malloc((1+r) * sizeof(int **));
            for (int j = 0; j <= r; j++) {
                memorySol[i][j] = (int **) malloc((1+t) * sizeof(int *));
                for (int k = 0; k <= t; k++) {
                    memorySol[i][j][k] = (int *) malloc((1+s) * sizeof(int));
                    for (int h = 0; h <= s; h++)
                        memorySol[i][j][k][h] = -1;
                }
            }
        }
}

void MEMORYSOLcanc(int z, int r,int t, int s){
    for (int i = 0; i <= z; i++) {
        for (int j = 0; j <= r; j++) {
            for (int k = 0; k <= t; k++) {
                for (int h = 0; h <= s; h++)
                    memorySol[i][j][k][h] = -1;
            }
        }
    }
}

void MEMORYSOLfree(int z, int r, int t) {
        for (int i = 0; i <= z; i++) {
            for (int j = 0; j <= r; j++) {
                for (int k = 0; k <= t; k++) {
                    free(memorySol[i][j][k]);
                }
                free(memorySol[i][j]);
            }
            free(memorySol[i]);
        }
    free(memorySol);
}
