#include <iostream>
#include <string>

using namespace std;

class elemento {
    friend class lista;
private:
    int chave;
    elemento* proximo;
    elemento* anterior;
public:
    elemento(int c) {
        chave = c;
        proximo = NULL;
        anterior = NULL;
    }
};

class lista {
private:
    elemento* inicio;
    elemento* fim;
    int tamanho;
public:
    lista();
    ~lista();
    void insereInicio(int c);
    void insereFim(int c);
    int removeRepetidos();//retorna a quantidade de elementos restantes na lista
    bool vazia();
    void imprimeLista();
};

lista::lista() {
    inicio = NULL;
    fim = NULL;
    tamanho = 0;
}

lista::~lista() {
    elemento* aux = inicio;
    elemento* proximo = NULL;
    while (aux != NULL) {
        proximo = aux->proximo;
        delete aux;
        aux = proximo;
    }
}

void lista::insereInicio(int c) {
    elemento* novo = new elemento(c);
    if (inicio == NULL and fim == NULL) {
        inicio = novo;
        fim = novo;
    } else {
        novo->proximo = inicio;
        inicio->anterior = novo;
        inicio = novo;
    }
    tamanho++;
}

void lista::insereFim(int c) {
    elemento* novo = new elemento(c);
    if (inicio == NULL and fim == NULL) {
        inicio = novo;
        fim = novo;
    } else {
        fim->proximo = novo;
        novo->anterior = fim;
        fim = novo;
    }
    tamanho++;
}

int lista::removeRepetidos() {
    elemento *aux = inicio;
    while (aux != NULL) { // percorre a lista
        elemento *aux2 = aux->proximo;
        while (aux2 != NULL) { //aux2 percorre a lista a partir da posicao de aux, para verificar se existe repetidos
            if (aux->chave == aux2->chave) {
                if (aux2->proximo != NULL) { // se aux2 nao for o ultimo elemento da lista
                    aux2->proximo->anterior = aux2->anterior;
                }
                if (aux2->anterior != NULL) { // se aux2 nao for o primeiro elemento da lista
                    aux2->anterior->proximo = aux2->proximo;
                }
                if (aux2 == inicio) { // se aux2 for o primeiro elemento da lista
                    inicio = aux2->proximo;
                }
                if (aux2 == fim) { // se aux2 for o ultimo elemento da lista
                    fim = aux2->anterior;
                }
                tamanho--;
                delete aux2;
                aux2 = aux->proximo;
            } else {
                aux2 = aux2->proximo;
            }
        }
        aux = aux->proximo;
    }
    return tamanho;
}

void lista::imprimeLista() {
    if (inicio != NULL) {
        elemento* auxiliar = inicio;
        cout << auxiliar->chave << " ";
        while (auxiliar->proximo != NULL) {
            cout << auxiliar->proximo->chave << " ";
            auxiliar = auxiliar->proximo;
        }
        cout << endl;
        auxiliar = fim;
        cout << auxiliar->chave << " ";
        while (auxiliar->anterior != NULL) {
            cout << auxiliar->anterior->chave << " ";
            auxiliar = auxiliar->anterior;
        }
        cout << endl;
    } else {
        cout << "VAZIA";
    }
}

int main() {

    int n;
    cin >> n;
    lista l;
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        l.insereFim(c);
    }
    l.removeRepetidos();
    l.imprimeLista();


    return 0;
}

