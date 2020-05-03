#include <iostream>
#include <stdio.h>
using namespace std;
#define MAX 100

typedef struct{
    int chave;
}registro;

typedef struct{
    registro aluno[MAX];
    int nroElem;
}lista_seq;

void inicializar(lista_seq* l){
    l -> nroElem = 0;
}

int busca(lista_seq* l, int ch){
    for(int i = 0; i < l -> nroElem; i++){
        if(l -> aluno[i].chave == ch) return i;
    }
    return -1;
}

//busca da sem parâmetro
int buscaPosicao(lista_seq* l, int ch){
    for(int i = 0; i < l -> nroElem; i++){
        if(l -> aluno[i].chave == ch) return -1;
        if(l -> aluno[i].chave > ch) return i;
    }
    return l -> nroElem;
}

bool listaCheia(lista_seq* l){
    if(l -> nroElem >= MAX) return true;
    else return false;
}

//lista não ordenada
bool anexar(lista_seq* l, int ch){
    if(listaCheia(l)) return false;
    int aux = busca(l, ch);
    if(aux != -1) return false;
    l -> aluno[l -> nroElem].chave = ch;
    l -> nroElem++;
    return true;
}

//lista ordenada
bool incluir_i(lista_seq* l, int ch, int i){
    if(listaCheia(l) || i < 0 || i > (l->nroElem)) return false;
    int aux = busca(l, ch);
    if(aux != -1) return false;

    for(int j = l -> nroElem; j >= i; j--){
        if(j != i) l -> aluno[j].chave = l -> aluno[j-1].chave;
        if(j == i) l -> aluno[j].chave = ch;
    }
    l -> nroElem++;
    return true;
}

//lista ordenada sem o parâmetro i
bool inserir_ordenada(lista_seq* l, int ch){
    if(listaCheia(l)) return false;
    int aux = buscaPosicao(l, ch);
    if(aux == -1) return false;

    for(int j = l -> nroElem; j >= buscaPosicao(l, ch); j--){
        if(j != buscaPosicao(l, ch)) l -> aluno[j].chave = l -> aluno[j-1].chave;
        if(j == buscaPosicao(l, ch)) {
                l -> aluno[j].chave = ch;
                break; //pq break?
        }
    }
    l -> nroElem++;
    return true;
}

int tamanho(lista_seq* l){
    return l -> nroElem;
}

void exibir(lista_seq* l){
    for(int i = 0; i < l -> nroElem; i++){
        cout << l -> aluno[i].chave << endl;
    }
}

bool excluir(lista_seq* l, int ch){
    int pos = busca(l, ch);
    if(pos == -1) return false;
    for(int i = pos; i < l -> nroElem - 1; i++){
        l -> aluno[i] = l -> aluno[i+1];
    }
    l -> nroElem--;
    return true;
}

int main(){

    int ch, i;
    bool condicao = true;
    lista_seq l;
    inicializar(&l);


    while(condicao) {
        int comando;
        cout << endl << "Escolha um comando:" << endl;
        cout << "1- Inserir" << endl << "2- Excluir" << endl << "3- Exibir" << endl << "4- Buscar" << endl << "5- Inserir em uma posicao" << endl << "6- Inserir mas descobre pra mim ai" << endl << "7- Fechar" << endl << endl;
        cout << "Digite o numero: ";
        cin >> comando;

        switch(comando) {
            case 1:
                cout << "Digite a chave" << endl;
                cin >> ch;
                anexar(&l, ch);
                break;

            case 2:
                cout << "Digite a chave" << endl;
                cin >> ch;
                excluir(&l, ch);
                break;

            case 3: exibir(&l);
                break;

            case 4:
                cout << "Digite a chave" << endl;
                cin >> ch;
                cout << busca(&l, ch) << endl;
                break;

            case 5:
                cout << "Digite a chave e a posicao" << endl;
                cin >> ch >> i;
                incluir_i(&l, ch, i);
                break;

            case 6:
                cout << "Digite a chave" << endl;
                cin >> ch;
                inserir_ordenada(&l, ch);
                break;

            case 7: condicao = false;
                break;
        }
    }
    return 0;
}
