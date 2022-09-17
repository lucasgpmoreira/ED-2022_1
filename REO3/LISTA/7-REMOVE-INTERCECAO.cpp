#include <iostream>
#include <cstdlib>
using namespace std;

typedef int Dado;

class noh {
    friend class listadup;
private:
    const Dado dado; // poderia ser outro tipo de variável (é const para não ser alterado)
    noh* proximo;
    noh* anterior;

public:
    noh(Dado d = 0); // Cosntrutor padrão
};

noh::noh(Dado d) : dado(d) {		// tem que usar esse "dado(d)" porque é ponteiro; Assim é mais rápido e pq é const;
    // Mas é como se fosse um "dado = d";
    proximo = NULL;
    anterior = NULL;
}

// lista duplamente encadeada
class listadup {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista

public:
    // construtores e destrutor
    listadup();
    ~listadup();
    void insereNoFim(Dado dado);
    void removeNoFim();
    void removeNoInicio();
    void removeValor(Dado valor);
    void removeInterc(listadup& l2);
    void imprime();
    bool vazia();
};

listadup::listadup() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

// destrutor da lista (chama função privada auxiliar)
listadup::~listadup() {
    removeTodos();
}

// remove todos os elementos da lista
void listadup::removeTodos() {
    noh* aux = primeiro;
    noh* temp;

    while (aux != NULL) {
        temp = aux;
        aux = aux->proximo;
        delete temp;
    }
    // redirecionando ponteiros (Pois agora tudo foi deletado)
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

void listadup::insereNoFim(Dado dado) {
    // * primeiro criamos o novo nó
    noh* novo = new noh(dado);

    // * agora inserimos o nó na lista
    // se a lista estiver vazia, inserimos o primeiro nó
    if (vazia()) { // ou (primeiro == NULL) ou (tamanho ==0 )
        primeiro = novo;
        ultimo = novo;
    } else { // já tem elementos na lista, insere no final
        ultimo->proximo = novo;
        novo->anterior = ultimo;	// DIFERENÇA COM A DINAMICAMENTE ENCADEADA
        ultimo = novo;
    }
    tamanho++;
}

void listadup::removeNoInicio() {
    if (vazia()) { // verifica lista vazia
        cerr << "Remoção em lista vazia" << endl;
        exit(EXIT_FAILURE);
    }

    noh* removido = primeiro;
    primeiro = primeiro->proximo;
    if (primeiro != NULL) {
        primeiro->anterior = NULL;
    }
    delete removido;
    tamanho--;

    // se a lista ficou vazia
    if (vazia()) {
        ultimo = NULL;
    }
}

// Remove no Fim
void listadup::removeNoFim() {
    if (vazia()) { // verifica lista vazia
        cerr << "Remoção em lista vazia" << endl;
        exit(EXIT_FAILURE);
    }

    noh* removido = ultimo;
    ultimo = ultimo->anterior;
    if (ultimo != NULL) {
        ultimo->proximo = NULL;
    }
    delete removido;
    tamanho--;

    // se a lista ficou vazia
    if (vazia()) {
        ultimo = NULL;
    }
}

void listadup::removeValor(Dado valor) {
    // Código de busca primeiro
    noh* aux = primeiro;
    noh* ante;
    while ((aux != NULL) and (aux->dado != valor)) {
        ante = aux;
        aux = aux->proximo;
    }
    if (aux != NULL) {
        if (aux == primeiro) {
            removeNoInicio();
        } else if (aux == ultimo) {
            removeNoFim();
        } else {
            ante->proximo = aux->proximo;
            aux->proximo->anterior = ante;
            delete aux;
            tamanho--;
        }
    }
    tamanho--;
    if (vazia()) {
        primeiro = NULL;
        ultimo = NULL;
    }
}

void listadup::removeInterc(listadup& l2) {
    noh* auxl1 = primeiro;
    noh* temp;

    while (auxl1 != NULL) {
        noh* auxl2 = l2.primeiro;
        bool elemEncontrado = false;
        while (auxl2 != NULL and not(elemEncontrado)) {
            if (auxl2->dado == auxl1->dado) {
                int dado = auxl1->dado;
                auxl1 = auxl1->anterior;
                removeValor(dado);
                elemEncontrado = true;
            } else {
                auxl2 = auxl2->proximo;
            }
        }
        if (auxl1 == NULL) {
            auxl1 = primeiro;
        } else {
            auxl1 = auxl1->proximo;
        }
    }
}

void listadup::imprime() {
    if (vazia()) {
        cout << -1 << endl;
    } else {
        noh* aux = primeiro;

        while (aux != NULL) {
            cout << aux->dado << ' ';
            aux = aux->proximo;
        }
        cout << endl;

        aux = ultimo;
        while (aux != NULL) {
            cout << aux->dado << ' ';
            aux = aux->anterior;
        }
        cout << endl;
    }
}

bool listadup::vazia() {
    return (primeiro == NULL and ultimo == NULL);
}

int main() {
    listadup l1;
    listadup l2;
    int nElementos1, nElementos2;
    cin >> nElementos1;
    for (int i = 0; i < nElementos1; i++) {
        int dado;
        cin >> dado;
        l1.insereNoFim(dado);
    }
    cin >> nElementos2;
    for (int i = 0; i < nElementos2; i++) {
        int dado;
        cin >> dado;
        l2.insereNoFim(dado);
    }
    l1.removeInterc(l2);
    l1.imprime();
    return 0;
}