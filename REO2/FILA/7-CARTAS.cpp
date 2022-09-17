//IMPLEMENTA A FILA ENCADEADA
#include <iostream>
#include <string>
#include <cmath>

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
    int retornaInicio();
    int retornaTamanho();
    bool filaContemElemento(int n);
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

int Fila::retornaInicio() {
    return inicio->valor;
}

int Fila::retornaTamanho() {
    return qtd;
}

bool Fila::filaContemElemento(int n) {
    No* aux = inicio;
    while (aux != NULL) {
        if (n == aux->valor) {
            return true;
        }
        aux = aux->proximo;
    }
    return false;
}


void removeRepetidos(Fila& fila, int quantElem) { //remove elementos repetidos da fila
    Fila filaAux;
    int elemento;
    for (int i = 0; i < quantElem; i++) {
        elemento = fila.desenfileirar();
        if (not(filaAux.filaContemElemento(elemento))) {
            filaAux.enfileirar(elemento);
        }
        fila.enfileirar(elemento);
    }

    for (int i = 0; i < quantElem; i++) { //limpa fila
        fila.desenfileirar();
    }

    int tamanhoFilaAux = filaAux.tamanhoFila();
    for (int i = 0; i < tamanhoFilaAux; i++) { // passa dados da fila aux para original
        fila.enfileirar(filaAux.desenfileirar());
    }
}

int main() {
    Fila fila1;
    Fila fila2;
    Fila filaFinal;
    int quantElem1, quantElem2;

    cin >> quantElem1;
    for (int i = 0; i < quantElem1; i++) {
        int valor;
        cin >> valor;
        fila1.enfileirar(valor);
    }

    cin >> quantElem2;
    for (int i = 0; i < quantElem2; i++) {
        int valor;
        cin >> valor;
        fila2.enfileirar(valor);
    }
    int elem1, elem2;
    while (not(fila1.filaVazia()) and not(fila2.filaVazia())) {
        elem1 = fila1.retornaInicio();
        elem2 = fila2.retornaInicio();
        if (elem1 < elem2) {
            filaFinal.enfileirar(fila1.desenfileirar());
        } else {
            filaFinal.enfileirar(fila2.desenfileirar());
        }
    }

    //caso seja um numero impar, pode sobrar um elemento na fila, entao removemos e colocamos na fila final
    while (not(fila1.filaVazia())) {
        filaFinal.enfileirar(fila1.desenfileirar());
    }

    while (not(fila2.filaVazia())) {
        filaFinal.enfileirar(fila2.desenfileirar());
    }

    /*
    trecho confuso
        removeRepetidos(fila1, quantElem1);
        removeRepetidos(fila2, quantElem2);
        int elem1, elem2;
        int tamanhoFilasSomadas = fila1.tamanhoFila() + fila2.tamanhoFila();
        if (ehPar(tamanhoFilasSomadas)) {
            tamanhoFilasSomadas /= 2;
        } else {
            tamanhoFilasSomadas = (tamanhoFilasSomadas / 2) + 1;
        }
        for (int i = 0; i < tamanhoFilasSomadas; i++) {
            if (ehPar(tamanhoFilasSomadas)) {
                elem1 = fila1.desenfileirar();
                elem2 = fila2.desenfileirar();
                if (elem1 <= elem2) {
                    filaFinal.enfileirar(elem1);
                    filaFinal.enfileirar(elem2);
                } else if (elem1 >= elem2) {
                    filaFinal.enfileirar(elem2);
                    filaFinal.enfileirar(elem1);
                }
            } else {
                if (tamanhoFilasSomadas - i > 1) {
                    elem1 = fila1.desenfileirar();
                    elem2 = fila2.desenfileirar();
                    if (elem1 <= elem2) {
                        filaFinal.enfileirar(elem1);
                        filaFinal.enfileirar(elem2);
                    } else {
                        filaFinal.enfileirar(elem2);
                        filaFinal.enfileirar(elem1);
                    }
                } else {
                    elem1 = fila1.desenfileirar();
                    filaFinal.enfileirar(elem1);
                }
            }


        }

        */

    removeRepetidos(filaFinal, filaFinal.tamanhoFila());

    for (int i = 0; i < filaFinal.tamanhoFila(); i++) {
        int elem = filaFinal.desenfileirar();
        cout << elem << " ";
        filaFinal.enfileirar(elem);
    }
    return 0;
}

