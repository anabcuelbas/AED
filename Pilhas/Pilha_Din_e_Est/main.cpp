#include <iostream>
#include <malloc.h>
#include <stdio.h>
#define MAX 100

using namespace std;

typedef struct s{
    int chave;
    struct s* prox;
}NO;

typedef struct{
    NO* topo;
}pilha_din;

void inicializarDin(pilha_din* pi){
    pi->topo = NULL;
}

void push_din(pilha_din* pi, int ch){
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->chave = ch;
    novo->prox = pi->topo;
    pi->topo = novo;
}

int pop_din(pilha_din* pi){
    int resp = -1;
    if(pi->topo){
        resp = pi->topo->chave;
        NO* aux = pi->topo;
        pi->topo = pi->topo->prox;
        free(aux);
    }
    return resp;
}

void exibirDin(pilha_din* pi){
    NO* p = pi->topo;
    while(p){
        cout << p->chave << " ";
        p = p->prox;
    }
}

typedef struct{
    int A[MAX];
    int topo;
}pilha_est;

void inicializarEst(pilha_est* pi){
    pi->topo = -1;
}

bool push_est(pilha_est* pi, int ch){
    if(pi->topo == (MAX - 1)) return false;
    pi->topo = pi->topo + 1;
    pi->A[pi->topo] = ch;
    return true;
}

int pop_est(pilha_est* pi){
    int resp = -1;
    if(pi->topo != -1){
        resp = pi->A[pi->topo];
        pi->topo = pi->topo - 1;
    }
    return resp;
}

void exibirEst(pilha_est* pi){
    for(int i = pi->topo; i >= 0; i--){
        cout << pi->A[i] << " ";
    }
}


int main(){

    pilha_din pidin;
    pilha_est peste;
    inicializarDin(&pidin);
    inicializarEst(&peste);

    push_din(&pidin, 56);
    push_din(&pidin, 49);
    pop_din(&pidin);
    push_din(&pidin, 18);
    push_din(&pidin, 9);
    push_din(&pidin, 01);
    pop_din(&pidin);
    pop_din(&pidin);
    exibirDin(&pidin);

    push_est(&peste, 56);
    push_est(&peste, 49);
    pop_est(&peste);
    push_est(&peste, 18);
    push_est(&peste, 9);
    push_est(&peste, 01);
    pop_est(&peste);
    pop_est(&peste);
    exibirEst(&peste);

    return 0;
}
