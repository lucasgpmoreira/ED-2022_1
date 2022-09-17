//IMPLEMENTA A FILA ENCADEADA
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class Fila {
private:
    struct No {
        string valor;
        No* proximo;
    };
    No* inicio;
    No* fim;
    int qtd;
    bool filaVazia();
public:
    Fila();
    ~Fila();
    void enfileirar(string valor);
    string desenfileirar();
    int retornaTam();
    bool carroEstaNaFila(string valor);
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

void Fila::enfileirar(string valor) {
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

string Fila::desenfileirar() {
    string valor;
    if (filaVazia()) {}
    else {
        valor = inicio->valor;
        No* aux = inicio;
        inicio = inicio->proximo;
        delete aux;
        qtd--;
    }
    return valor;
}

bool Fila::filaVazia() {
    return qtd == 0;
}


bool Fila::carroEstaNaFila(string valor) {
    No* aux = inicio;
    while (aux != NULL) {
        if (aux->valor == valor) {
            return true;
        }
        aux = aux->proximo;
    }
    return false;
}

int Fila::retornaTam() {
    return qtd;
}

int main() {
    Fila fila;
    char opcao;
    string valor;
    string carroRetirado;
    int numDeCarrosDesestacionados = 0;
    do {
        cin >> opcao;
        switch (opcao) {
        case 'E':
            cin >> valor;
            fila.enfileirar(valor);
            break;
        case 'D':
            cin >> valor;
            if (fila.carroEstaNaFila(valor)) {
                do {
                    carroRetirado = fila.desenfileirar();
                    numDeCarrosDesestacionados++;
                    if (!(carroRetirado.compare(valor) == 0)) {
                        fila.enfileirar(carroRetirado);
                    }
                } while (carroRetirado != valor);
                cout << numDeCarrosDesestacionados << endl;
                numDeCarrosDesestacionados = 0;
                
                for (int i = 0; i < fila.retornaTam(); i++) {
                    string elem = fila.desenfileirar();
                    cout << elem << endl;
                    fila.enfileirar(elem);
                }
                
            } else {
                cout << "NAO ENCONTRADO" << endl;
            }
            break;
        }
    } while (opcao != 'S');
    return 0;
}