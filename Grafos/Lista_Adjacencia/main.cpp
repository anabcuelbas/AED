#include <iostream>
#include <malloc.h>
#include <stdio.h>

using namespace std;

typedef struct s{
    int chave;
    struct s* prox;

}NO;

typedef struct{
    int vertices;
    int arestas;
    NO** adj;

}GRAFO;

void inicializar(GRAFO* g, int  quantVertices, int quantArestas) {
    g->vertices = quantVertices;
    g->arestas = quantArestas;
    g->adj = (NO**) malloc (sizeof(NO*) * quantVertices);

    for(int i = 0; i < quantVertices; i++) {
       g->adj[i] = NULL;
    }
}

NO* buscaAdj(GRAFO* g, int vertice){
    NO* ant = g->adj[vertice];
    NO* aux = ant;

    while(aux){
        if(ant->prox != NULL) ant = ant->prox;
        aux = ant->prox;
    }

    return ant;
}

void adicionarAresta(GRAFO* g, int vertice1, int vertice2){
    NO* novo1 = (NO*) malloc(sizeof(NO));
    NO* novo2 = (NO*) malloc(sizeof(NO));
    novo1->chave = vertice2;
    novo2->chave = vertice1;
    novo1->prox = NULL;
    novo2->prox = NULL;

    if(g->adj[vertice1] == NULL) g->adj[vertice1] = novo1;
    else {
        NO* ant1 = buscaAdj(g, vertice1);
        ant1->prox = novo1;
    }

    if(g->adj[vertice2] == NULL) g->adj[vertice2] = novo2;
    else {
        NO* ant2 = buscaAdj(g, vertice2);
        ant2->prox = novo2;
    }
}

void montarGrafo(GRAFO* g){
    int vertice1, vertice2;
    cout << "Digite as arestas: " << endl;

    for(int i = 0; i < g->arestas; i++){
        cin >> vertice1 >> vertice2;
        adicionarAresta(g, vertice1, vertice2);
    }
}

void printarGrafo(GRAFO* g) {
    cout << endl << "Grafo final:" << endl;

    for(int i = 0; i < g->vertices; i++){
        NO* verticeAdj = g->adj[i];
        cout << i << ": ";

        while(verticeAdj){
            cout << verticeAdj->chave << " ";
            verticeAdj = verticeAdj->prox;
        }
        cout << endl;
    }
}

int grauVertice(GRAFO* g, int vertice) {
    int grau = 0;
    NO* aux = g->adj[vertice];

    while(aux){
        grau++;
        aux = aux->prox;
    }

    return grau;
}

int grauMax(GRAFO* g) {
    int grauMaximo = 0;
    for(int i = 0; i < g->vertices; i++) {
        int grau = grauVertice(g, i);
        if(grau > grauMaximo) grauMaximo = grau;
    }

    return grauMaximo;
}

int grauMedio(GRAFO* g) {
    int media = (2*g->arestas)/g->vertices;
    if((2*g->arestas)%g->vertices >= (g->vertices/2)) media++;

    return media;
}

int quantidadeSelfLoops(GRAFO* g){
    int contador = 0;

    for(int i = 0; i < g->vertices; i++) {
        NO* aux = g->adj[i];

        while(aux) {
            if(aux->chave == i) {
                contador++;
                break;
            }
            aux = aux->prox;
        }
    }

    return contador;
}

int main() {
    int V, E;
    GRAFO g;

    cout << "Digite a quantidade de vertices e arestas:" << endl;
    cin >> V >> E;

    inicializar(&g, V, E); //recebe o grafo e quantidade de vértices e arestas
    montarGrafo(&g);
    printarGrafo(&g);

    cout << "Maior grau: " << grauMax(&g) << endl;
    cout << "Grau Medio: " << grauMedio(&g) << endl;
    cout << "Quantidade de Self Loops: " << quantidadeSelfLoops(&g) << endl;

    return 0;
}
