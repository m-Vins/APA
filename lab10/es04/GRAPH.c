//
// Created by Master on 04/01/2020.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "GRAPH.h"


typedef struct edge {int v; int w; int wt;}Edge;
typedef struct node_s *link;

struct node_s {
    int v;
    int wt;
    link next;
};


struct graph_s {
    int V;
    int E;
    int **madj;
    link *ladj;//la sentinella è NULL;
    ST st;
};



static link NEW(int v, int wt,link next){
    link x=malloc(sizeof *x);
    x->v=v; x->wt=wt;
    x->next=next;
    return x;
}




static int** matrixInit(int r,int c){
    int **m=NULL;
    m=(int **)malloc(r* sizeof(int *));
    for(int i=0;i<r;i++) m[i]=(int *)calloc(c, sizeof(int));
    return m;
}

static void matrixFree(int **m,int r){
    for(int i=0;i<r;i++)
        free(m[i]);
    free(m);
}

static Edge edgeCreate(int v, int w, int wt){
    Edge e;
    e.v=v;  e.w=w; e.wt=wt;
    return e;
}



Graph GRAPHinit(int V){
    Graph G=malloc(sizeof *G);
    G->V=V; G->E=0; G->madj=matrixInit(V,V);
    G->st=STinit();
    G->ladj=NULL;
}

static void freeListR(link x){
    if(x==NULL)
        return;
    freeListR(x->next);
    free(x);
}

static void freeLadj(Graph G){
    for(int i=0;i<G->V;i++)
        freeListR(G->ladj[i]);
}

Graph GRAPHfree(Graph G){
    STfree(G->st);
    matrixFree(G->madj,G->V);
    if(G->ladj!=NULL) freeLadj(G);
    free(G);
}

static void insertEdge(Graph G, Edge E){
    if(G->madj[E.v][E.w]==0) G->E++;
    G->madj[E.v][E.w]=E.wt;
    G->madj[E.w][E.v]=E.wt;
}

Graph GRAPHload(FILE *fp){
    int count=0,val,id1,id2;
    Graph G;
    char tmpelab1[MAXPAROLA],tmpelab2[MAXPAROLA],tmprete1[MAXPAROLA],tmprete2[MAXPAROLA];
    while(fscanf(fp,"%*s%*s%*s%*s%*d\n")!=EOF){
        count++;
    }
    G=GRAPHinit(count);
    rewind(fp);
    while(fscanf(fp,"%s%s%s%s%d\n",tmpelab1,tmprete1,tmpelab2,tmprete2,&val)!=EOF){
        id1=STinsert(tmpelab1,tmprete1,G->st);
        id2=STinsert(tmpelab2,tmprete2,G->st);
        insertEdge(G,edgeCreate(id1,id2,val));
    }
    G->V=STcount(G->st);
    return G;
}


static void vertexSort(ST st,int *vertex, int n){
    int min,l=0,r=n-1;
    int tmp;

    for(int i=l;i<r;i++){
        min=i;
        for(int j=1+i;j<=r;j++){
            if(strcmp(STsearchNameByIndex(vertex[min],st),STsearchNameByIndex(vertex[j],st))>0)
                min=j;
        }
        if(min!=i){
            tmp=vertex[i];
            vertex[i]=vertex[min];
            vertex[min]=tmp;
        }
    }
}

static void edgeSort_w(ST st,Edge *edge, int n){
    int min,l=0,r=n-1;
    Edge tmp;

    for(int i=l;i<r;i++){
        min=i;
        for(int j=1+i;j<=r;j++){
            if(strcmp(STsearchNameByIndex(edge[min].w,st),STsearchNameByIndex(edge[j].w,st))>0)
                min=j;
        }
        if(min!=i){
            tmp=edge[i];
            edge[i]=edge[min];
            edge[min]=tmp;
        }
    }
}

void GRAPHstoreEdges(Graph G,Edge *edge,int n,FILE *fp){
    for(int i=0;i<n;i++)
        fprintf(fp,"nome1: %s, rete1: %s  <---[val: %d]---> nome2: %s, rete2: %s\n",STsearchNameByIndex(edge[i].v,G->st),
                STsearchReteByIndex(edge[i].v,G->st),edge[i].wt,STsearchNameByIndex(edge[i].w,G->st),
                STsearchReteByIndex(edge[i].w,G->st));
}

void GRAPHstore(Graph G,FILE *fp){
    int vertex[G->V];
    Edge edge[G->V];    int count;
    //crea un elenco degli indici dei vertici.
    for(int i=0;i<G->V;i++) vertex[i]=i;
    vertexSort(G->st,vertex,G->V);

    fprintf(fp,"\nVERTICI:\n");
    for(int i=0;i<G->V;i++) {
        fprintf(fp, "nome: %s, rete: %s\n", STsearchNameByIndex(vertex[i], G->st), STsearchReteByIndex(vertex[i], G->st));
        count=0;
        for(int j=0;j<G->V;j++){
            if(G->madj[vertex[i]][j]!=0)
                edge[count++]=edgeCreate(vertex[i],j,G->madj[vertex[i]][j]);
        }
        printf("ARCHI ADIACENTI AL VERTICE:\n");
        edgeSort_w(G->st,edge,count);
        GRAPHstoreEdges(G,edge,count,fp);
        printf("\n\n");
    }
}


void GRAPHloadLadj(Graph G){
    G->ladj=(link *)malloc(G->V*sizeof(link));
    for(int i=0;i<G->V;i++){
        G->ladj[i]=NULL;
        for(int j=0;j<G->V;j++){
            if(G->madj[i][j]!=0)
                G->ladj[i]=NEW(j,G->madj[i][j],G->ladj[i]);
        }
    }
}


void GRAPHstoreLadj(Graph G,FILE *fp){
    fprintf(fp,"RAPPRESENTAZIONE LISTA ADIACENZE:\n");
    for(int i=0;i<G->V;i++){
        fprintf(fp,"vertice[%s %s]:",STsearchNameByIndex(i,G->st),STsearchReteByIndex(i,G->st));
        for(link x=G->ladj[i];x!=NULL;x=x->next){
            fprintf(fp,"%s %s %s",STsearchNameByIndex(x->v,G->st),STsearchReteByIndex(x->v,G->st),x->next==NULL ? "":"-->");
        }
        printf("\n");
    }
}


static int checkVertexR(Graph G,int pos,int root,int *vertex,int *mark,int *sol,int n){
    int ok=1;
    //condizione di terminazione implicita, nel momento in cui il flag ok resta uguale a 1, significa che
    //la ricorsione ha marcato tutti i vertici e che quindi formano un grafo, altrimenti continua a ricorrere finché
    //c'è un vertice adiacente a sol[pos] tra i vertici scelti.
    for(int i=0;i<n;i++){
            if(mark[i]==0) ok=0;
    }
    if(ok==1) return 1;

    //l'assegnazione della radice viene fatta nella chiamata della funzione ricorsiva
    //in quanto il fatto che sia un grafo non dovrebbe dipendere dalla radice.
    if(pos==0) {
        sol[pos]=vertex[root];
        mark[0]=1;
        if(checkVertexR(G,pos+1,root,vertex,mark,sol,n)) return 1;
    }


    for(int i=0;i<n&&pos!=0;i++) {
        //ricorsione solo nei verticici adiacenti.
        if ((G->madj[sol[pos - 1]][vertex[i]] || G->madj[vertex[i]][sol[pos - 1]])&&mark[i]==0) {
            sol[pos] = vertex[i];
            mark[i]=1;
            if (checkVertexR(G, pos + 1,root, vertex,mark, sol, n)) return 1;
        }
    }
    return 0;

}

int GRAPHcheckVertex(Graph G,int *vertex,int n){
    int sol[n];
    int mark[n];

    for(int i=0;i<n;i++){ sol[i]=0;  mark[i]=0; }

    return checkVertexR(G,0,0,vertex,mark,sol,n);
}

void GRAPHstoreVertex(Graph G,FILE *fp){
    fprintf(fp,"ELENCO VERTICI:\n");
    for(int i=0;i<G->V;i++){
        fprintf(fp,"vertice[%d]:%s/%s\n",i,STsearchNameByIndex(i,G->st),STsearchReteByIndex(i,G->st));
    }
    printf("\n");
}

static int checkVertexLadjR(Graph G,int pos,int root,int *vertex,int *mark,int *sol,int n){
    int ok=1;

    for(int i=0;i<n;i++){
        if(mark[i]==0) ok=0;
    }
    if(ok==1) return 1;

    if(pos==0) {
        sol[pos]=vertex[root];
        mark[0]=1;
        if(checkVertexR(G,pos+1,root,vertex,mark,sol,n)) return 1;
    }
    else {
        for (link x = G->ladj[sol[pos - 1]]; x != NULL; x = x->next) {
            for (int i = 0; i < n; i++) {
                if (x->v == vertex[i]&&mark[i]==0) {
                    sol[pos] = vertex[i];
                    mark[i] = 1;
                    if (checkVertexR(G, pos + 1, root, vertex, mark, sol, n)) return 1;
                }
            }
        }
    }
    return 0;
}

int GRAPHcheckVertexLadj(Graph G,int *vertex, int n){
    int sol[n];
    int mark[n];

    for(int i=0;i<n;i++){sol[i]=0; mark[i]=0;}

    return checkVertexLadjR(G,0,0,vertex,mark,sol,n);
}

