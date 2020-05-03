#include <iostream>
#include <malloc.h>
#include <stdio.h>
#define MAX 5

using namespace std;

typedef struct s{
    int chave;
    struct s* prox;
}NO;

typedef struct {
    NO* inicio;
    NO* fim;
}fila_din;

void inicializarDin(fila_din* f){
    f->inicio = NULL;
    f->fim = NULL;
}

void entrarFilaDin(fila_din* f, int ch){
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->chave = ch;
    novo->prox = NULL;
    if(f->fim){
        f->fim->prox = novo;
    } else {
        f->inicio = novo;
    }
    f->fim = novo;
}

int sairFilaDin(fila_din* f){
    int resp = -1;
    if(f->inicio){
        resp = f->inicio->chave;
        NO* aux = f->inicio;
        f->inicio = f->inicio->prox;
        free(aux);
        if(!f->inicio)f->fim = NULL;
    }
    return resp;
}

typedef struct{
    int A[MAX];
    int inicio;
    int fim;
}fila_est;

void inicializarEst(fila_est* g){
    g->inicio = -1;
    g->fim = -1;
}

bool vetorCheio(fila_est* g){
    if(g->inicio == 0){
        if(g->fim == MAX-1) return true;
    } else if(g->fim == g->inicio - 1) return true;

    return false;
}

bool entrarFilaEst(fila_est* g, int ch){
    if(vetorCheio(g))return false;
    g->fim = (g->fim+1) % MAX;
    g->A[g->fim] = ch;
    if(g->inicio == -1){
        g->inicio = g->fim;
    }
    return true;
}

int sairFilaEst(fila_est* g){
    int resp = -1;
    if(g->inicio > -1){
        resp = g->A[g->inicio];
        if(g->inicio == g->fim){
            g->inicio = -1;
            g->fim = -1;
            return resp;
        }
        g->inicio = (g->inicio+1) % MAX;
    }
    return resp;
}

void exibirVetor(fila_est* g){
    for(int i = 0; i < MAX; i++){
        cout << g->A[i] << endl;
    }
}

void exibirFila(fila_din* f){
    NO* p = f->inicio;
    while(p){
        cout << p->chave << endl;
        p = p->prox;
    }
}

int main() {

    int ch;
    bool condicao = true;
    fila_din f;
    inicializarDin(&f);
    fila_est g;
    inicializarEst(&g);


    while(condicao) {
        int comando;
        cout << endl << "Escolha um comando:" << endl;
        cout << "1- Inserir_Dinamica" << endl << "2- Excluir_Dinamica" << endl << "3- Inserir_Estatica" << endl << "4- Excluir_Estatica" << endl << "5- Fechar" << endl << "6- Exibir Estatica" << endl << "7- Exibir Dinamica" << endl << endl;
        cout << "Digite o numero: ";
        cin >> comando;

        switch(comando) {
            case 1:
                cout << "Digite a chave" << endl;
                cin >> ch;
                entrarFilaDin(&f, ch);
                break;

            case 2:
                sairFilaDin(&f);
                break;

            case 3:
                cout << "Digite a chave" << endl;
                cin >> ch;
                entrarFilaEst(&g, ch);
                break;

            case 4:
                sairFilaEst(&g);
                break;

            case 5:
                condicao = false;
                break;

            case 6:
                exibirVetor(&g);
                break;

            case 7:
                exibirFila(&f);
                break;
        }
    }

    return 0;
}
