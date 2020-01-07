#include <stdio.h>
#include <stdlib.h>

#include "GRAPH.h"

typedef enum {print_vertex,check_vertex_madj,check_vertex_ladj,create_ladj,printf_ladj,esci,err}cmd_t;

int leggicomando();


int main(int argc,char **argv) {
    FILE *fp;
    Graph G;
    int FineProgramma=0,tmp,*vertex;
    int LoadLadj=0;

    if(argc!=2)
        exit(-1);
    fp=fopen(argv[1],"r");
    if(fp==NULL) {
        printf("ERRORE FILE");
        exit(-1);
    }

    G=GRAPHload(fp);
    fclose(fp);


    while(!FineProgramma){
        switch(leggicomando()){
            case print_vertex:
                GRAPHstore(G,stdout);
                break;
            case check_vertex_madj:
                printf("inserire numero vertici:");
                scanf("%d",&tmp);       //nell'esercizio è richiesto che tmp sia 3;
                vertex=calloc(tmp, sizeof(int));
                GRAPHstoreVertex(G,stdout);
                printf("inserire indici vertici: ");
                for(int i=0;i<tmp;i++)  scanf("%d",&vertex[i]);
                if(GRAPHcheckVertex(G,vertex,tmp))
                    printf("i vertici inseriti formano un sottografo\n");
                else printf("i vertici inseriti non formano un sottografo\n");
                free(vertex);
                break;
            case create_ladj:
                GRAPHloadLadj(G);
                LoadLadj=1;
                break;
            case printf_ladj:
                if(LoadLadj)    GRAPHstoreLadj(G,stdout);
                else printf("caricare prima la lista delle adiacenze.\n");
                break;
            case check_vertex_ladj:
                printf("inserire numero vertici:");
                scanf("%d",&tmp);       //nell'esercizio è richiesto che tmp sia 3;
                vertex=calloc(tmp, sizeof(int));
                GRAPHstoreVertex(G,stdout);
                printf("inserire indici vertici: ");
                for(int i=0;i<tmp;i++)  scanf("%d",&vertex[i]);
                if(GRAPHcheckVertexLadj(G,vertex,tmp))
                    printf("i vertici inseriti formano un sottografo\n");
                else printf("i vertici inseriti non formano un sottografo\n");
                free(vertex);
                break;
            case esci:
                FineProgramma=1;
                break;
            case err:
            default: printf("errore comando\n");
        }
    }

    GRAPHfree(G);

    return 0;
}


int leggicomando(){
    cmd_t cmd;
    char comandi[][25]={"print_vertex","check_vertex_madj","check_vertex_ladj","create_ladj","print_ladj","esci"};
    printf("ELENCO COMANDI:\n");
    for(int i=0;i<err;i++) printf("[%d]-> %s;\n",i,comandi[i]);
    scanf("%d",&cmd);
    return cmd;
}
