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
    cout << "[";
    while (aux != NULL) {
        if (aux->proximo == NULL) {
            cout << aux->valor << "]";
        } else {
            cout << aux->valor << "][";
        }
        aux = aux->proximo;
    }
    cout << endl;
}

int iteracoes = 0;

int main() {
    Fila filaA;
    Fila filaB;
    Fila filaR;
    for (int i = 10; i > 0; i--) {
        filaA.enfileirar(i);
    }
    filaA.imprimirFila();

    filaB.enfileirar(2);
    filaB.enfileirar(7);
    filaB.enfileirar(4);
    filaB.enfileirar(8);

    filaB.imprimirFila();

    cout << "***************************" << endl;
    int cont = 0;
    while (not(filaA.filaVazia())) {
        int el1 = filaA.desenfileirar();
        while (cont < 4) {
            int el2 = filaB.desenfileirar();
            cout << "***************************" << endl;
            cout << "Iteracao " << iteracoes << endl;
            cout << "Elemento 1: " << el1 << endl;
            cout << "Elemento 2: " << el2 << endl;
            iteracoes++;
            filaA.imprimirFila();
            filaB.imprimirFila();
            filaR.imprimirFila();
            cout << "***************************" << endl;
            if (el1 == el2) {
                filaB.enfileirar(el2);
                filaR.enfileirar(el2);
            } else {
                filaB.enfileirar(el2);
            }
            cont++;
        }
        cont = 0;
    }

    cout << endl; 
    filaR.imprimirFila();
    cout << endl;
    return 0;
}

