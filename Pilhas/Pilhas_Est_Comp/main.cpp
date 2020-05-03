#include <iostream>
#include <malloc.h>
#include <stdio.h>
#define MAX 12
#define NP 3

using namespace std;

typedef struct{
    int A[MAX];
    int topo[NP + 1];
    int base[NP + 1];
}npPilhas;

void inicializar(npPilhas* pi){
    int i;
    for(i = 0; i <= NP; i++){
        pi->topo[i] = i * (MAX / NP) - 1;
        pi->base[i] = pi->topo[i];
    }
}

bool pilhaKcheia(npPilhas* pi, int k){
    return(pi->topo[k] == pi->base[k+1]);
}

int contarK(npPilhas* pi, int k){
    if(k < 0 || k > (NP - 1)) return -1;
    return pi->topo[k] - pi->base[k];
}

void deslocar1Direita(npPilhas* pi, int k){
    if(k < 1 || k > (NP - 1)) return;
    if(pilhaKcheia(pi, k)) return;
    for(int i = pi->topo[k] + 1; i > pi->base[k] + 1; i--){
        pi->A[i] = pi->A[i-1];
    }
    pi->topo[k] = pi->topo[k] + 1;
    pi->base[k] = pi->base[k] + 1;
}

void deslocar1Esquerda(npPilhas* pi, int k){
    if(k < 1 || k > (NP - 1)) return;
    if(pilhaKcheia(pi, k - 1)) return;
    for(int i = pi->base[k]; i < pi->topo[k] + 1; i++){
        pi->A[i] = pi->A[i+1];
    }
    pi->topo[k] = pi->topo[k] - 1;
    pi->base[k] = pi->base[k] - 1;
}

bool pushK(npPilhas* pi, int k, int ch){
    if(pilhaKcheia(pi, k)){
        int i;
        for(i = NP - 1; i > k; i--) deslocar1Direita(pi, i);
        if(pilhaKcheia(pi, k)){
            for(i = 1; i <= k; i++) deslocar1Esquerda(pi, i);
            if(pilhaKcheia(pi, k)) return false;
        }
    }
    pi->topo[k] = pi->topo[k] + 1;
    pi->A[pi->topo[k]] = ch;
    return true;
}

int popK(npPilhas* pi, int k){
    if(k < 0 || k > (NP - 1)) return -1;
    if(pi->base[k] == pi->topo[k]) return -1;
    pi->topo[k] = pi->topo[k] - 1;
    return pi->A[pi->topo[k] + 1];
}

void exibirVetor(npPilhas* pi){

    for(int i = 0; i < MAX; i++){
        cout << pi->A[i] << " ";
    }

    cout << endl;
    return;
}

int main(){

    int ch, k;
    bool condicao = true;
    npPilhas pi;
    inicializar(&pi);

    while(condicao) {
        int comando;
        cout << endl << "Escolha um comando:" << endl;
        cout << "1- Push" << endl << "2- Pop" << endl  << "3- Exibir Vetor" << endl << endl;
        cout << "Digite o numero: ";
        cin >> comando;

        switch(comando) {

            case 1:
                cout << "Digite o indice da pilha e a chave" << endl;
                cin >> k >> ch;
                pushK(&pi, k, ch);
                break;

            case 2:
                cout << "Digite o indice da pilha" << endl;
                cin >> k;
                popK(&pi, k);
                break;

            case 3:
                exibirVetor(&pi);
                break;

            default:
                condicao = false;
                break;
        }
    }

    return 0;
}
