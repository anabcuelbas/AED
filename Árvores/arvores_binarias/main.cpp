#include <iostream>
#include <malloc.h>
#include <stdio.h>

using namespace std;

typedef struct s{
    int chave;
    struct s* esq;
    struct s* dir;
} NO;

NO* inserir(NO* *raiz, NO* pai, int ch, int pos){
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->chave = ch;
    novo->esq = NULL;
    novo->dir = NULL;
    if(!pai){
        *raiz = novo;
        return novo;
    }
    if(pos == 1){
        pai->esq = novo;
    } else {
        pai->dir = novo;
    }
    return novo;
}

void visitar(NO* p){
    printf("%d ", p->chave);
}

/*
void preOrdemIterativo(NO* raiz){
    pilha pi;
    inicializar(&pi);
    NO* p = raiz;
    while(p){
        visitar(p);
        if(p->dir) push (&pi, p->dir);
        p = p->esq;
        if(!p) p = pop(&pi);
    }
}
*/

void preOrdemRecursivo(NO* p){
    if(p){
        visitar(p);
        preOrdemRecursivo(p->esq);
        preOrdemRecursivo(p->dir);
    }
}

void emOrdemRecursivo(NO* p){
    if(p){
        emOrdemRecursivo(p->esq);
        visitar(p);
        emOrdemRecursivo(p->dir);
    }
}

void posOrdemRecursivo(NO* p){
    if(p){
        posOrdemRecursivo(p->esq);
        posOrdemRecursivo(p->dir);
        visitar(p);
    }
}

/*
void emNivel(NO* raiz){
    fila f;
    inicializar(&f);
    entrarFila(&f, raiz);
    while(f.inicio){
        NO* p = sairFila(&f);
        visitar(p);
        if(p->esq) entrarFila(&f, p->esq);
        if(p->dir) entrarFila(&f, p->dir);
    }
}
*/

//retornar nó pai de uma chave apontada por *p
void acharPai(NO* raiz, NO* p, NO* *pai) { //pai = NULL
    if(raiz){
        if(raiz == p) return;
        if(raiz->esq == p || raiz ->dir == p){
            *pai = raiz;
        }
        acharPai(raiz->esq, p, pai);
        if(*pai) return;
        acharPai(raiz->dir, p, pai);
    }
}

int contar(NO* p){
    if(p) return 1 + contar(p->esq) + contar(p->dir);
    else return 0;
}

//contar ocorrências de ch em uma arvore
int contarCH(NO* raiz, int ch){
    if(raiz){
        printf("%d \n", raiz->chave);
        if(raiz->chave == ch) return 1 + contarCH(raiz->esq, ch) + contarCH(raiz->dir, ch);
        else return 0 + contarCH(raiz->esq, ch) + contarCH(raiz->dir, ch);
    }
    return 0;
}

int main(){

    NO* raiz = NULL;
    NO* paizin = NULL;
    NO* pai = inserir(&raiz, paizin, 10, 1);
    NO* pai2 = inserir(&raiz, pai, 200, 1);
    NO* pai3 = inserir(&raiz, pai, 10, 2);
    NO* pai4 = inserir(&raiz, pai2, 10, 2);
    NO* pai5 = inserir(&raiz, pai4, 10, 1);

    int quantidade = contarCH(raiz, 1);
    printf("%d", quantidade);

    return 0;
}
