#include <iostream>
#include <stdio.h>
using namespace std;
#define MAX 100

typedef struct{
    int chave;
    int prox;
}registro;

typedef struct{
    registro aluno[MAX];
    int inicio;
    int dispo;
}lista_lig;

void inicializar(lista_lig *l){
    l->inicio = -1;
    l->dispo = 0;

    for(int i = 0; i < MAX - 1; i++){
        l->aluno[i].prox = i + 1;
    }
    l->aluno[MAX - 1].prox = -1;
}

int ultimo(lista_lig *l){ //usado na função ultimaChave
    int i = l->inicio;

    while(i != -1){
        if(l->aluno[i].prox == -1) return i;
        i = l->aluno[i].prox;
    }
    return -1;
}

void imprimir(lista_lig *l){
    int i = l->inicio;

    while(i != -1){
        printf("%i\n", l->aluno[i].chave);
        i = l->aluno[i].prox;
    }
}

int contar(lista_lig *l){
    int i = l->inicio;
    int cont = 0;

    while(i != -1){
        cont++;
        i = l->aluno[i].prox;
    }
    return cont;
}

bool buscarChave(lista_lig *l, int ch){
    int i = l->inicio;

    while(i != -1){
        if(l->aluno[i].chave == ch) {
            printf("%s", "A chave está na posicao ");
            printf("%d\n", i);
            return true;
        }
        if(l->aluno[i].chave > ch) return false;
        i = l->aluno[i].prox;
    }
    return false;
}

int ultimaChave(lista_lig *l){
    return l->aluno[ultimo(l)].chave;
}

int enesimaChave(lista_lig *l, int i){
    return l->aluno[i].chave;
}

int buscar(lista_lig *l, int ch, int *ant){ //pra ser usada dentro das funções de inserir excluir
    *ant = -1;
    int i = l->inicio;

    while(i != -1){
        if(l->aluno[i].chave == ch) return i;
        if(l->aluno[i].chave > ch) return -1;
        *ant = i;
        i = l->aluno[i].prox;
    }
    return -1;
}

void devolver(lista_lig *l, int i){ //usado na função de excluir
    l->aluno[i].prox = l->dispo;
    l->dispo = i;
}

int obter(lista_lig *l){ //usado na função de inserir
    int resp = l->dispo;

    if(l->dispo > -1) l->dispo = l->aluno[l->dispo].prox;
    return resp;
}

bool excluir(lista_lig *l, int ch){
    int ant;
    int pos = buscar(l, ch, &ant);
    if(pos == -1) return false;

    if(ant > - 1) l->aluno[ant].prox = l->aluno[pos].prox;
    else l->inicio = l->aluno[pos].prox;

    devolver(l, pos);
    return true;
}

bool inserir(lista_lig *l, int ch){
    int ant;
    if(l->dispo == -1) return false;
    int pos = buscar(l, ch, &ant);
    if(pos > -1) return false; //chave já existe
    pos = obter(l);
    l->aluno[pos].chave = ch;

    if(ant > -1){
        l->aluno[pos].prox = l->aluno[ant].prox;
        l->aluno[ant].prox = pos;
    } else {
        l->aluno[pos].prox = l->inicio;
        l->inicio = pos;
    }
    return true;
}

int main(){

    int ch, i;
    bool condicao = true;
    lista_lig l;
    inicializar(&l);


    while(condicao) {
        int comando;
        cout << endl << "Escolha um comando:" << endl;
        cout << "1- Inserir" << endl << "2- Excluir" << endl << "3- Exibir" << endl << "4- Buscar" << endl << "5- Contar elementos" << endl << "6- Ultima chave" << endl << "7- Enesima chave" << endl << "8- Fechar" << endl << endl;
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
                cout << "Digite a chave" << endl;
                cin >> ch;
                buscarChave(&l, ch);
                break;

            case 5:
                cout << contar(&l) << endl;
                break;

            case 6:
                cout << ultimaChave(&l) << endl;
                break;

            case 7:
                cin >> i;
                cout << enesimaChave(&l, i) << endl;
                break;

            case 8: condicao = false;
                break;
        }
    }
    return 0;
}
