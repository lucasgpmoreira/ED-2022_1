//IMPLEMENTA A FILA ENCADEADA
#include <iostream>
#include <string>

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
public:
    Fila();
    ~Fila();
    void enfileirar(string valor);
    string desenfileirar();
    int tamanhoFila();
    bool filaVazia();
    int retornaTamanho();
    string retornaInicio();
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

string Fila::retornaInicio() {
    return inicio->valor;
}

int Fila::retornaTamanho() {
    return qtd;
}

/*
Implemente uma estrutura do tipo fila com as operações básicas de inserção e remoção. Com a estrutura implementada, faça um programa que utilize a fila para gerar números binários de 1 a N. O trecho a seguir dá uma dica de como resolver o problema:

inicio = "1"
enfileira (inicio) // fila = (1)
laço
    enfileira(inicio + “0”) // fila = (1, 10)
    enfileira(inicio + “1”) // fila(1, 10, 11)
    elemento = desenfileira()
fim  do laço
Note que como cada passo do laço enfileira por padrão dois elementos, você precisará inserir um controle adicional no laço ou na impressão para evitar enfileirar um elemento a mais, dependendo da entrada.
*/

int main() {
    Fila filaAux;
    Fila filaFinal;
    int tamanho;
    cin >> tamanho;
    filaAux.enfileirar("1");
    for (int i = 0; i < tamanho; i++) {
        filaAux.enfileirar(filaAux.retornaInicio() + "0");
        filaAux.enfileirar(filaAux.retornaInicio() + "1");
        filaFinal.enfileirar(filaAux.desenfileirar());
    }
    for(int i = 0; i < filaFinal.retornaTamanho(); i++) {
        string elem = filaFinal.desenfileirar();
        cout << elem << " ";
        filaFinal.enfileirar(elem);
    }
    return 0;
}

