#include <stdio.h>
#include <stdlib.h>
#define FileNameBoard "board.txt"
#define FileNameTiles "tiles.txt"

typedef struct {
    char col;
    int val;
}seg_t;

typedef struct {
    seg_t o,v;
    int index;
    int mark;
}tess_t;

void ruotaTessera(tess_t *punt);
tess_t *creaElencoTess(FILE *fp,int *N);
tess_t **AllocaScacchiera(int nr,int nc);
tess_t **initScacchiera(FILE *fp,tess_t *tess,int *nr, int *nc);
void dispR(int pos, tess_t **Sc, tess_t *tess, int nr, int nc, int nt, int *BestVal,tess_t **BSol);
int disp(tess_t **Scacchiera,tess_t *tessere, int nr, int nc, int nt);
int getVal(tess_t **S,int nr, int nc);
void newSol(tess_t **new,tess_t **tmp,int nr,int nc);
void displaySol(tess_t **S,int nr,int nc);
void free2d(tess_t **x,int nr);


int main() {
    tess_t **Scacchiera=NULL;
    tess_t *tessere=NULL;
    int nr,nc,nt,val;
    FILE *fp;

    fp=fopen(FileNameTiles,"r");
    tessere=creaElencoTess(fp,&nt);
    fclose(fp);

    fp=fopen(FileNameBoard,"r");
    Scacchiera=initScacchiera(fp,tessere,&nr,&nc);
    fclose(fp);
    val=disp(Scacchiera,tessere,nr,nc,nt);
    displaySol(Scacchiera,nr,nc);
    printf("di valore : %d",val);

    free(tessere);
    free2d(Scacchiera,nr);
    return 0;
}

tess_t *creaElencoTess(FILE *fp,int *N){
    tess_t *punt=NULL;
    fscanf(fp,"%d\n",N);
    punt=malloc(*N*sizeof(tess_t));
    for(int i=0;i<*N;i++){
        fscanf(fp,"%c%d%*c%c%d\n",&punt[i].o.col,&punt[i].o.val,
                &punt[i].v.col,&punt[i].v.val);
        punt[i].index=i;
        punt[i].mark=0;
    }
    return punt;
}

tess_t **AllocaScacchiera(int nr,int nc) {
    int i;
    tess_t **punt = (tess_t **)malloc(nr * sizeof(tess_t *));
    for (i = 0; i < nr; i++)
        punt[i]=(tess_t *)malloc(nc* sizeof(tess_t));
    return punt;
}

tess_t **initScacchiera(FILE *fp,tess_t *tess,int *nr, int *nc){
    int i,j;
    int rot,pos;
    seg_t tmp;
    tess_t **puntS=NULL;

    fscanf(fp,"%d%d\n",nr,nc);
    puntS=AllocaScacchiera(*nr,*nc);
    for(i=0;i<*nr;i++){
        for(j=0;j<*nc;j++){
            fscanf(fp,"%d/%d",&pos,&rot);
            if(pos!=-1&&rot!=-1) {
                puntS[i][j] = tess[pos];
                tess[pos].mark=puntS[i][j].mark=1;
                if(rot%2!=0)
                    ruotaTessera(&puntS[i][j]);
            }else
                puntS[i][j].mark=0;
        }
    }
    return puntS;
}

int disp(tess_t **Scacchiera,tess_t *tessere, int nr, int nc, int nt){
    int BestVal=0;
    tess_t **BScacchiera=AllocaScacchiera(nr,nc);
    dispR(0,Scacchiera,tessere,nr,nc,nt,&BestVal,BScacchiera);
    //memorizzo in Scacchiera la soluzione
    newSol(Scacchiera,BScacchiera,nr,nc);
    free2d(BScacchiera,nr);
    return BestVal;
}

void dispR(int pos, tess_t **Sc, tess_t *tess, int nr, int nc, int nt, int *BestVal,tess_t **BSol){
    int i,x=0,y=0;
    int val;

    if(pos>=nr*nc){
        val=getVal(Sc,nr,nc);
        if(val>*BestVal){
            *BestVal=val;
            newSol(BSol,Sc,nr,nc);
        }
        return;
    }

    //aritmetica degli indici della Scacchiera
    x=pos/nr;
    y=pos%nc;

    if(Sc[x][y].mark==1){
        dispR(pos+1,Sc,tess,nr,nc,nt,BestVal,BSol);
        return;
    }
    else {
        for (i = 0; i < nt; i++) {
            if (tess[i].mark == 0) {//controlla se la tessera è già usata
                Sc[x][y].mark = tess[i].mark = 1;
                Sc[x][y] = tess[i];
                dispR(pos + 1, Sc, tess, nr, nc, nt, BestVal, BSol);
                ruotaTessera(&Sc[x][y]);
                dispR(pos + 1, Sc, tess, nr, nc, nt, BestVal, BSol);
                Sc[x][y].mark = tess[i].mark = 0;//backtrack
            }
        }
    }
}

void ruotaTessera(tess_t *punt){
    seg_t tmp;
    tmp=punt->o;
    punt->o=punt->v;
    punt->v=tmp;
}

int getVal(tess_t **S,int nr, int nc){
    int totval=0,val,ok;
    int i,j;
    char col;

    for(i=0;i<nr;i++){
        col=S[i][0].o.col;
        for(val=0,ok=1,j=0;j<nc;j++){
            if(col!=S[i][j].o.col)
                ok=0;
            val+=S[i][j].o.val;
        }
        if(ok)
            totval+=val;
    }
    for(j=0;j<nc;j++){
        col=S[0][j].v.col;
        for(val=0,ok=1,i=0;i<nr;i++){
            if(col!=S[i][j].v.col)
                ok=0;
            val+=S[i][j].v.val;
        }
        if(ok)
            totval+=val;
    }
    return totval;
}

void newSol(tess_t **new,tess_t **tmp,int nr,int nc){
    int i,j;
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            new[i][j]=tmp[i][j];
        }
    }
}

void displaySol(tess_t **S,int nr,int nc){
    int i,j;
    printf("la soluzione migliore é:\n[v=colore verticale,o=colore orizzontale,i=indice tessera]\n");
    printf("\n");
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            printf("|v:%c,o:%c,i:%d",S[i][j].v.col,S[i][j].o.col,S[i][j].index);
        }
        printf("|\n\n");
    }
}

void free2d(tess_t **x,int nr){
    int i;
    for(i=0;i<nr;i++)
        free(x[i]);
    free(x);
}
