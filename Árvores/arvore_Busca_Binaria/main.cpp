#include <iostream>
#include <malloc.h>
#include <stdio.h>

using namespace std;

typedef struct s{
    int chave;
    struct s* esq;
    struct s* dir;
} NO;

NO* busca(NO* raiz, int ch){
    while(raiz){
        if(raiz->chave == ch) return raiz;
        if(ch < raiz->chave) raiz = raiz->esq;
        else raiz = raiz->dir;
    }
    return NULL;
}

NO* retornaPai(NO* raiz, NO* p){
    if(raiz){
        if(raiz->esq == p || raiz->dir == p) return raiz;
        if(p->chave < raiz->chave) retornaPai(raiz->esq, p);
        if(p->chave > raiz->chave) retornaPai(raiz->dir, p);
    }
    return NULL;
}

NO* buscaRecursiva(NO* raiz, int ch, NO* *pai){
    if(raiz){
        if(raiz->chave == ch) return raiz;
        *pai = raiz;
        if(ch < raiz->chave) buscaRecursiva(raiz->esq, ch, pai);
        else buscaRecursiva(raiz->dir, ch, pai);
    }
    return NULL;
}

bool inserir(NO* *raiz, int ch){
    NO* pai = NULL;
    NO* atual = buscaRecursiva(*raiz, ch, &pai);
    if(atual) return false;
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->chave = ch;
    novo->esq = NULL;
    novo->dir = NULL;
    if(!pai){
        *raiz = novo;
        return true;
    }
    if(pai->chave > ch) pai->esq = novo;
    else pai->dir = novo;
    return true;
}

NO* substituir(NO*p){
    NO* ultimo = p->esq;
    while(ultimo->dir){
        ultimo = ultimo->dir;
    }
    return ultimo;
}

bool excluir(NO* *raiz, int ch){
    NO* pai;
    NO* atual = buscaRecursiva(*raiz, ch, &pai);
    if(!atual) return false;

    if(!atual->esq && !atual->dir){
        if(pai){
            if(pai->chave > atual->chave) pai->esq = NULL;
            else pai->dir = NULL;
        } else {
            *raiz = NULL;
        }
        free(atual);
        return true;
    }

    if(!atual->esq || !atual->dir){
        NO* neto;
        if(atual->esq) neto = atual->esq;
        else neto = atual->dir;
        if(pai){
            if(pai->chave > atual->chave) pai->esq = neto;
            else pai->dir = neto;
        } else {
            *raiz = neto;
        }
        free(atual);
        return true;
    }

    NO* substituto = substituir(atual);
    atual->chave = substituto->chave;
    bool booleana = excluir(raiz, substituto->chave);

    return booleana;
}

void visitar(NO* p){
    printf("%d ", p->chave);
}

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

void parent(NO* p){
    if(p){
        printf("%d", p->chave);
        if(p->esq || p->dir){
            printf("(");
            parent(p->esq);
            printf(",");
            parent(p->dir);
            printf(")");
        }
    } else printf("_");
}

void ancestral(NO* p, int ch){
    if(p){
        if(p->chave == ch) return;
        printf("%d", p->chave);
        if(p->chave > ch){
            ancestral(p->esq, ch);
        } else {
            ancestral(p->dir, ch);
        }
    }
}

/*
void ancestralContrario(NO* p, int ch, pilha* pi){
    if(p){
        if(p->chave == ch) {
            printf("%d", p->chave);
            while(pi){
                int resp = pop(&pi);
                printf("%d", resp);
            }
        }
        push(&pi, p->chave);
        if(p->chave > ch){
            ancestral(p->esq, ch);
        } else {
            ancestral(p->dir, ch);
        }
    }
}
*/

int main(){

    NO* raiz = NULL;
    inserir(&raiz, 100);
    inserir(&raiz, 80);
    inserir(&raiz, 200);
    inserir(&raiz, 300);
    inserir(&raiz, 20);
    inserir(&raiz, 90);
    inserir(&raiz, 89);

    emOrdemRecursivo(raiz);

    return 0;
}
