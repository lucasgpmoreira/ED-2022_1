#include <iostream>
#include <cstdlib>
using namespace std;

typedef int Dado;

class noh {
    friend class listaEnc;
private:
    const Dado dado; // poderia ser outro tipo de variável (é const para não ser alterado)
    noh* proximo;

public:
    noh(Dado d = 0); // Cosntrutor padrão
};

noh::noh(Dado d) : dado(d) {		// tem que usar esse "dado(d)" porque é ponteiro; Assim é mais rápido e pq é const;
    // Mas é como se fosse um "dado = d";
    proximo = NULL;
}

class listaEnc {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista
    bool vazia(); // verifica se a lista está vazia
public:
    // construtores e destrutor
    listaEnc();
    listaEnc(const listaEnc& umalLista);   // construtor de cópia
    ~listaEnc();
    void insereNoFim(Dado dado);
    void insereNoInicio(Dado dado);
    void funcA();
    void funcB(listaEnc& l);
    void imprime();
};

// constrói uma lista inicialmente vazia
listaEnc::listaEnc() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

// construtor de cópia (Insere no fim tudo que veio da outra lista)
listaEnc::listaEnc(const listaEnc& umalista) {   // umalista = lista que será copiada
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;

    // percorre a lista recebida como parâmetro, copiando os dados
    noh* aux = umalista.primeiro;

    while (aux != NULL) {
        insereNoFim(aux->dado);
        aux = aux->proximo;
    }
}

listaEnc::~listaEnc() {
    removeTodos();
}

void listaEnc::removeTodos() {
    noh* aux = primeiro;
    while (aux != NULL) {
        noh* aux2 = aux->proximo;
        delete aux;
        aux = aux2;
    }
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

bool listaEnc::vazia() {
    return (tamanho == 0);
}

void listaEnc::insereNoFim(Dado dado) {
    noh* novo = new noh(dado);
    if (vazia()) {
        primeiro = novo;
        ultimo = novo;
    } else {
        ultimo->proximo = novo;
        ultimo = novo;
    }
    tamanho++;
}

void listaEnc::insereNoInicio(Dado dado) {
    noh* novo = new noh(dado);
    if (vazia()) {
        primeiro = novo;
        ultimo = novo;
    } else {
        novo->proximo = primeiro;
        primeiro = novo;
    }
    tamanho++;
}

void listaEnc::funcA() {
    noh* noh1 = primeiro;
    noh* noh2 = NULL;
    noh* noh3;
    while (noh1 != NULL) {
        noh3 = noh1->proximo;
        if (noh1->dado % 2 == 0) {
            if (noh2 != NULL) {
                noh2->proximo = noh3;
            } else {
                primeiro = noh1->proximo;
            }
            if (noh3 == NULL) {
                ultimo = noh2;
            }
            delete noh1;
            noh2 = noh1;
        }
        noh1 = noh3;
    }
}

void listaEnc::funcB(listaEnc& l) {
    noh* noh1 = l.primeiro;
    while (noh1 != NULL) {
        noh* noh2 = new noh(noh1->dado);
        if (primeiro == NULL) {
            primeiro = noh2;
            ultimo = noh2;
        } else {
            ultimo->proximo = noh2;
            ultimo = noh2;
        }
        noh1 = noh1->proximo;
    }
}

void listaEnc::imprime() {
    noh* aux = primeiro;
    while (aux != NULL) {
        cout << aux->dado << " ";
        aux = aux->proximo;
    }
    cout << endl;
}

int main() {
    listaEnc lista1;
    listaEnc lista2;

    int t, n;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n;
        lista1.insereNoInicio(n);
    }
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n;
        lista2.insereNoFim(n);
    }
    lista1.funcA();
    lista2.funcA();
    lista2.funcB(lista1);
    lista2.imprime();
    return 0;
}

