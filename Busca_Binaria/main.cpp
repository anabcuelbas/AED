//bubble sort + busca binária(recursiva e iterativa)
//testar um de cada vez (bubble vetor desordenado, binaria ordenado)
#include <iostream>
using namespace std;

int buscaBinaria_Iterativa(int achar, int vetor[], int tamanho){
    int i = 0, f = tamanho-1, meio;
    while(i <= f){
        meio = (i + f) / 2;
        if(vetor[meio] == achar) return meio;
        else {
            if(achar > vetor[meio]) i = meio + 1;
            else f = meio - 1;
        }
    }
    return -1;
}

int buscaBinaria_Recursiva(int achar, int vetor[], int inicio, int fim){
    int meio = (inicio + fim) / 2;
    if(achar == vetor[meio])return meio;
    else if(achar > vetor[meio]) return buscaBinaria_Recursiva(achar, vetor, meio+1, fim);
    else if(achar < vetor[meio]) return buscaBinaria_Recursiva(achar, vetor, inicio, meio-1);
    return -1;
}

int main(){

    int vetor[10], achar;
    cout << "Insira o vetor" << endl;

    for(int i = 0; i < 10; i++){
        cin >> vetor[i];
    }

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9 - i; j++){
            if(vetor[j] > vetor[j+1]){
                int aux = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = aux;
            }
        }
    }

    for(int i = 0; i < 10; i++){
        cout << vetor[i] << " ";
    }

    cout << endl << endl;
    cout << "Insira o que deseja achar" << endl;
    cin >> achar;
    cout << "Iterativa " << buscaBinaria_Iterativa(achar, vetor, 10) << endl;
    cout << "Recursiva " << buscaBinaria_Recursiva(achar, vetor, 0, 9) << endl;

    return 0;
}
