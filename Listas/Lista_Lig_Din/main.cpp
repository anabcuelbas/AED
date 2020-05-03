#include <iostream>
#include <malloc.h>
#include <stdio.h>
using namespace std;

typedef struct s{
    int chave;
    struct s* prox;
}NO;

typedef struct{
    NO* inicio;
}lista_din;

void inicializar(lista_din* l){
    l->inicio = NULL;
}

void imprimir(lista_din* l){
    NO* p = l->inicio;

    while(p){
        printf("\n %i", p->chave);
        p = p->prox;
    }
}

NO* busca(lista_din* l, int ch, NO* *ant){
    *ant = NULL;
    NO* p = l->inicio;

    while(p){
        if(p->chave == ch) return p;
        if(p->chave > ch) return NULL;
        *ant = p;
        p = p->prox;
    }
    return NULL;
}

bool excluir(lista_din* l, int ch){
    NO* ant;
    NO* p = busca(l, ch, &ant);
    if(!p) return false;
    if(ant) ant->prox = p->prox;
    else l->inicio = p->prox;
    free(p);
    return true;
}

bool inserir(lista_din* l, int ch){
    NO* ant;
    NO* p = busca(l, ch, &ant);
    if(p) return false;
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->chave = ch;

    if(ant){
        novo->prox = ant->prox;
        ant->prox = novo;
    } else {
        novo->prox = l->inicio;
        l->inicio = novo;
    }
    return true;
}

//busca pra trocar de lugar
bool buscaTrocar(lista_din* l, NO* *pos1, NO* *pos2, NO* *ant1, NO* *ant2, int n1, int n2){
    ant1 = NULL;
    ant2 = NULL;
    int cont = 0;
    NO* p = l->inicio;
    while(p){
        if(cont == n1 - 1) *ant1 = p;
        if(cont == n1) *pos1 = p;
        if(cont == n2 - 1) *ant2 = p;
        if(cont == n2) {
            *pos2 = p;
            return true;
        }
        p = p->prox;
        cont++;
    }
    return false;
}

//trocar chaves de posição
bool trocarChaves(lista_din* l, int n1, int n2){
    NO* ant1;
    NO* ant2;
    NO* pos1 = NULL;
    NO* pos2 = NULL;
    bool teste = buscaTrocar(l, &pos1, &pos2, &ant1, &ant2, n1, n2);
    if(!teste) return false;
    ant2->prox = pos2->prox;
    pos2->prox = pos1->prox;
    pos1->prox = ant2->prox;
    ant2->prox = pos1;
    ant1->prox = pos2;
    return true;
}

//mover chave pro começo da lista
bool moverInicio(int ch, lista_din* l){
    NO* ant;
    NO* p = busca(l, ch, &ant);
    if(p == l->inicio) return false;
    if(!p) return false;
    ant->prox = p->prox;
    p->prox = l->inicio;
    l->inicio = p;
    return true;
}

int main() {

    bool condicao = true;
    int i, ch, n1, n2;
    lista_din l;
    inicializar(&l);


    while(condicao) {
        int comando;
        cout << endl << "Escolha um comando:" << endl;
        cout << "1- Inserir" << endl << "2- Excluir" << endl << "3- Exibir" << endl << "4- Trocar de Posicao" << endl << "5- Inserir em uma posicao" << endl << "6- Inserir mas descobre pra mim ai" << endl << "7- Fechar" << endl << endl;
        cout << "Digite o numero: ";
        cin >> comando;

        switch(comando) {
            case 1:
                cout << "Digite a chave" << endl;
                cin >> ch;
                inserir(&l, ch);
                break;

            case 2:
                cout << "Digite a chave" << endl;
                cin >> ch;
                excluir(&l, ch);
                break;

            case 3: imprimir(&l);
                break;

            case 4:
                cout << "Digite as posicoes em ordem" << endl;
                cin >> n1 >> n2;
                trocarChaves(&l, n1, n2);
                break;

            /*case 5:
                cout << "Digite a chave e a posicao" << endl;
                cin >> ch >> i;
                incluir_i(&l, ch, i);
                break;

            case 6:
                cout << "Digite a chave" << endl;
                cin >> ch;
                inserir_ordenada(&l, ch);
                break;
            */
            case 7: condicao = false;
                break;
        }
    }

    return 0;
}
