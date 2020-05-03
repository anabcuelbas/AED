#include <iostream>
#include <malloc.h>
#include <stdio.h>

using namespace std;

typedef struct s{
    struct s* esq;
    struct s* dir;
    int chave;
    int bal;
} NO;

int maior(int x, int y){
    if(x > y) return x;
    else return y;
}

int altura(NO* p){
    if(p){
        int he = altura(p->esq);
        int hd = altura(p->dir);
        return 1 + maior(hd, he);
    } else return 0;
}

int fatorBalanceamento(NO* p){
    if(p) return (altura(p->dir) - altura(p->esq));
    return 0;
}

void busca(NO* p, int ch, NO* *resp){
    if(p){
        if(p->chave == ch){
            *resp = p;
            return;
        }
        busca(p->esq, ch, resp);
        if(*resp) return;
        busca(p->dir, ch, resp);
    }
}

//achar o sucessor de p na ordem natural de chaves void sucessor(NO* raiz, NO* p, NO* *resp)

int main(){



    return 0;
}
