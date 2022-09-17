#include <iostream>
#include <string>
using namespace std;

//classe de pilha usando arranjo
class pilha {
public:
    pilha(int tam);
    ~pilha();
    void empilha(int);
    int desempilha();
    int espia();
    bool estaVazia();
    void imprimePilha();
private:
    int *p;
    int topo;
    int tamanho;
};

pilha::pilha(int tam) {
    p = new int[tam];
    topo = -1;
    tamanho = tam;
}

pilha::~pilha() {
    delete[] p;
}

void pilha::empilha(int data) {
    if (topo == tamanho - 1) {
        cout << "pilha cheia" << endl;
        return;
    }
    p[++topo] = data;
}

int pilha::desempilha() {
    if (topo == -1) {
        cout << "pilha vazia" << endl;
        return -1;
    }
    return p[topo--];
}

bool pilha::estaVazia() {
    return topo == -1;
}

int pilha::espia() {
    if (estaVazia()) {
        cout << "pilha vazia" << endl;
        return -1;
    }
    return p[topo];
}

void pilha::imprimePilha() {
    if (estaVazia()) {
        cout << "pilha vazia" << endl;
        return;
    }
    for (int i = 0; i <= topo; i++) {
        cout << p[i] << " ";
    }
    cout << endl;
}

int main() {
    
    return 0;
}