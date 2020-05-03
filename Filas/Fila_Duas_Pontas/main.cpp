#include <iostream>
#include <malloc.h>
#include <stdio.h>

using namespace std;

typedef struct s{
    int chave;
    struct s* prox;
    struct s* ant;

}NO;

typedef struct{
    NO* inicio1;
    NO* inicio2;
}DEQUE;

void inicializar(DEQUE* d){
    d->inicio1 = NULL;
    d->inicio2 = NULL;
}

void entrarInicio1(DEQUE* d, int ch){
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->chave = ch;
    novo->ant = NULL;
    novo->prox = d->inicio1;
    if(d->inicio1){
        d->inicio1->ant = novo;
    } else {
        d->inicio2 = novo;
    }
    d->inicio1 = novo;
}

int sairInicio1(DEQUE* d){
    int resp = -1;
    if(d->inicio1){
        resp = d->inicio1->chave;
        NO* aux = d->inicio1;
        d->inicio1 = d->inicio1->prox;
        free(aux);
        if(!d->inicio1){
            d->inicio2 = NULL;
            return resp;
        }
        d->inicio1->ant = NULL;
    }
    return resp;
}

int entrarInicio2(DEQUE* d, int ch){
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->chave = ch;
    novo->ant = d->inicio2;
    novo->prox = NULL;
    if(d->inicio2){
        d->inicio2->prox = novo;
    } else {
        d->inicio1 = novo;
    }
    d->inicio2 = novo;
}

int sairInicio2(DEQUE* d){
    int resp = -1;
    if(d->inicio2){
        resp = d->inicio2->chave;
        NO* aux = d->inicio2;
        d->inicio2 = d->inicio2->ant;
        free(aux);
        if(!d->inicio2){
            d->inicio1 = NULL;
            return resp;
        }
        d->inicio2->prox = NULL;
    }
    return resp;
}

void exibirFila(DEQUE* d){
    NO* p = d->inicio1;
    while(p){
        cout << p->chave << " ";
        p = p->prox;
    }
}

int main(){

    int ch;
    bool condicao = true;
    DEQUE d;
    inicializar(&d);

    while(condicao) {
        int comando;
        cout << endl << "Escolha um comando:" << endl;
        cout << "1- Entrar 1" << endl << "2- Sair 1" << endl << "3- Entrar 2" << endl << "4- Sair 2" << endl << "5- Fechar" << endl << "6- Exibir Fila" << endl << endl;
        cout << "Digite o numero: ";
        cin >> comando;

        switch(comando) {
            case 1:
                cout << "Digite a chave" << endl;
                cin >> ch;
                entrarInicio1(&d, ch);
                break;

            case 2:
                sairInicio1(&d);
                break;

            case 3:
                cout << "Digite a chave" << endl;
                cin >> ch;
                entrarInicio2(&d, ch);
                break;

            case 4:
                sairInicio2(&d);
                break;

            case 5:
                condicao = false;
                break;

            case 6:
                exibirFila(&d);
                break;
        }
    }

    return 0;
}
