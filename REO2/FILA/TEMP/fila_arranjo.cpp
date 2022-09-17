//IMPLEMENTA A FILA USANDO UM ARRAY
#include <iostream>
#include <string>

using namespace std;

class Fila {
private:
    int* fila;
    int tamanho;
    int inicio;
    int fim;
    int qtd;
public:
    Fila(int tamanho);
    ~Fila();
    void enfileirar(int valor);
    int desenfileirar();
    int tamanhoFila();
    bool filaVazia();
    bool filaCheia();
    void imprimirFila();
};

Fila::Fila(int tam) {
    tamanho = tam;
    fila = new int[tam];
    inicio = 0;
    fim = 0;
    qtd = 0;
}

Fila::~Fila() {
    delete[] fila;
}

void Fila::enfileirar(int valor) {
    if (filaCheia()) {
        cout << "Fila cheia" << endl;
    } else {
        fila[fim] = valor;
        fim = (fim + 1) % tamanho;
        qtd++;
    }
}

int Fila::desenfileirar() {
    int valor;
    if (filaVazia()) {
        cout << "Fila vazia" << endl;
    } else {
        valor = fila[inicio];
        inicio = (inicio + 1) % tamanho;
        qtd--;
    }
    return valor;
}

int Fila::tamanhoFila() {
    return qtd;
}

bool Fila::filaVazia() {
    return qtd == 0;
} 

bool Fila::filaCheia() {
    return qtd == tamanho;
}

void Fila::imprimirFila() {
    int i = inicio;
    while (i != fim) {
        cout << fila[i] << " ";
        i = (i + 1) % tamanho;
    }
    cout << endl;
}

int main () {
    Fila fila(2);
    int opcao;
    int valor;
    do {
        cout << "1 - Enfileirar" << endl;
        cout << "2 - Desenfileirar" << endl;
        cout << "3 - Tamanho da fila" << endl;
        cout << "4 - Fila vazia" << endl;
        cout << "5 - Fila cheia" << endl;
        cout << "6 - Imprimir fila" << endl;
        cout << "7 - Sair" << endl;
        cout << "Opcao: ";
        cin >> opcao;
        switch (opcao) {
            case 1:
                cout << "Valor: ";
                cin >> valor;
                if (fila.filaCheia()) {
                    cout << "Fila cheia" << endl;
                } else {
                    fila.enfileirar(valor);
                }
                break;
            case 2:
                if (fila.filaVazia()) {
                    cout << "Fila vazia" << endl;
                } else {
                    valor = fila.desenfileirar();
                    cout << "Valor desenfileirado: " << valor << endl;
                }
                break;
            case 3:
                cout << "Tamanho da fila: " << fila.tamanhoFila() << endl;
                break;
            case 4:
                cout << "Fila vazia: " << fila.filaVazia() << endl;
                break;
            case 5:
                cout << "Fila cheia: " << fila.filaCheia() << endl;
                break;
            case 6:
                fila.imprimirFila();
                break;
            case 7:
                break;
            default:
                cout << "Opcao invalida" << endl;
        }
    } while (opcao != 7);
    return 0;
}


