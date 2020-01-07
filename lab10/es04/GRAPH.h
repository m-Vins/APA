//
// Created by Master on 04/01/2020.
//

#ifndef ES04_GRAPH_H
#define ES04_GRAPH_H

#ifndef MAXPAROLA
#define MAXPAROLA 30
#endif

#include "ST.h"

typedef struct graph_s *Graph;

Graph GRAPHinit(int V);
Graph GRAPHfree(Graph G);
Graph GRAPHload(FILE *fp);
void GRAPHstore(Graph G,FILE *fp);
void GRAPHloadLadj(Graph G);
void GRAPHstoreLadj(Graph G,FILE *fp);
int GRAPHcheckVertex(Graph G,int *vertex,int n);
void GRAPHstoreVertex(Graph G,FILE *fp);
int GRAPHcheckVertexLadj(Graph G,int *vertex, int n);



#endif //ES04_GRAPH_H
