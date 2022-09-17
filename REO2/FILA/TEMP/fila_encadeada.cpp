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
    while (aux != NULL) {
        cout << aux->valor << " ";
        aux = aux->proximo;
    }
    cout << endl;
}

int main () {
    Fila fila;
    int opcao, valor;
    do {
        cout << "1 - Enfileirar" << endl;
        cout << "2 - Desenfileirar" << endl;
        cout << "3 - Tamanho da fila" << endl;
        cout << "4 - Fila vazia?" << endl;
        cout << "5 - Imprimir fila" << endl;
        cout << "6 - Sair" << endl;
        cout << "Digite a opcao: ";
        cin >> opcao;
        switch (opcao) {
            case 1:
                cout << "Digite o valor: ";
                cin >> valor;
                fila.enfileirar(valor);
                break;
            case 2:
                valor = fila.desenfileirar();
                cout << "Valor desenfileirado: " << valor << endl;
                break;
            case 3:
                cout << "Tamanho da fila: " << fila.tamanhoFila() << endl;
                break;
            case 4:
                if (fila.filaVazia()) {
                    cout << "Fila vazia" << endl;
                } else {
                    cout << "Fila nao vazia" << endl;
                }
                break;
            case 5:
                fila.imprimirFila();
                break;
            case 6:
                break;
            default:
                cout << "Opcao invalida" << endl;
        }
    } while (opcao != 6);
    return 0;
}

