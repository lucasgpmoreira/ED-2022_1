//IMPLEMENTA A FILA ENCADEADA
#include <iostream>
#include <string>

using namespace std;

class Fila {
private:
    struct No {
        int valor;
        No* proximo;
    };
    No* inicio;
    No* fim;
    int qtd;
public:
    Fila();
    ~Fila();
    void enfileirar(int valor);
    int desenfileirar();
    int tamanhoFila();
    bool filaVazia();
    void imprimirFila();
    int retornaInicio();
    int retornaPrimeiroNegativo();
};

Fila::Fila() {
    inicio = NULL;
    fim = NULL;
    qtd = 0;
}

Fila::~Fila() {
    No* aux = inicio;
    while (aux != NULL) {
        No* aux2 = aux;
        aux = aux->proximo;
        delete aux2;
    }
}

void Fila::enfileirar(int valor) {
    No* novo = new No;
    novo->valor = valor;
    novo->proximo = NULL;
    if (filaVazia()) {
        inicio = novo;
    } else {
        fim->proximo = novo;
    }
    fim = novo;
    qtd++;
}

int Fila::desenfileirar() {
    int valor;
    if (filaVazia()) {
        cout << "Fila vazia" << endl;
    } else {
        valor = inicio->valor;
        No* aux = inicio;
        inicio = inicio->proximo;
        delete aux;
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

void Fila::imprimirFila() {
    No* aux = inicio;
    while (aux != NULL) {
        cout << aux->valor << " ";
        aux = aux->proximo;
    }
    cout << endl;
}

int Fila::retornaPrimeiroNegativo() {
    No* aux = inicio;
    int num = 1;
    while (aux != NULL) {
        if (aux->valor < 0) {
            num = aux->valor;
            return num;
        }
        aux = aux->proximo;
    }
    return num;
}

void encontraNumNegativo(Fila& fila, int tamSubfila, int quantElem) {
    Fila filaAux;
    int elemento;

    for (int i = 0; i < quantElem + 1; i++) {
        for (int j = 0; j < tamSubfila; j++) {
            elemento = fila.desenfileirar();
            filaAux.enfileirar(elemento);
            fila.enfileirar(elemento);
        }

        for (int j = 0; j < (quantElem - tamSubfila); j++) {
            fila.enfileirar(fila.desenfileirar());
        }

        fila.imprimirFila();
    }

}

int main() {
    Fila fila;
    Fila filaAux;
    int quantElementos, elemento, tamanhoSubfila;
    int contador = 0;
    cin >> quantElementos;
    for (int i = 0; i < quantElementos; i++) {
        cin >> elemento;
        fila.enfileirar(elemento);
    }
    cin >> tamanhoSubfila;

    int quantidadeSubfilas = (quantElementos - tamanhoSubfila) + 1;

    for (int i = 0; i < quantidadeSubfilas; i++) {

        for (int j = 0; j < tamanhoSubfila; j++) {
            int n = fila.desenfileirar();
            filaAux.enfileirar(n);
            if (j >= 1) {
                fila.enfileirar(n);
            }
        }
        int primeiroNeg = filaAux.retornaPrimeiroNegativo();

        if (primeiroNeg < 0) {
            cout << primeiroNeg << " ";
        } else {
            cout << "inexistente ";
        }

        for (int j = 0; j < tamanhoSubfila; j++) {
            filaAux.desenfileirar();
        }
        for (int j = 0; j < (quantElementos - tamanhoSubfila); j++) {
            fila.enfileirar(fila.desenfileirar());
        }

    }

    return 0;
}

