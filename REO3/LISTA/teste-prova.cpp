// Na lógica de lista DUPLAMENTE encadeada, cada nói tem um ponteiro para o pŕoximo e para o anterior
// Esse anterior é uma mão na roda para remover no final, etc

#include <iostream>
#include <cstdlib>
using namespace std;

typedef int Dado;

class noh {
    friend class listaDupla;
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
class listaDupla {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista
    bool vazia(); // verifica se a lista está vazia
public:
    // construtores e destrutor
    listaDupla();
    listaDupla(const listaDupla& umalLista);   // construtor de cópia
    ~listaDupla();
    void insereNoFim(Dado dado);
    void insereNoInicio(Dado dado);
    void funcA();
    void funcB(listaDupla& l);
    void imprime();
};

// constrói uma lista inicialmente vazia
listaDupla::listaDupla() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

// construtor de cópia (Insere no fim tudo que veio da outra lista)
listaDupla::listaDupla(const listaDupla& umalista) {   // umalista = lista que será copiada
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

// destrutor da lista (chama função privada auxiliar)
listaDupla::~listaDupla() {
    removeTodos();
}

bool listaDupla::vazia() {
    return (tamanho == 0);
}

// remove todos os elementos da lista
void listaDupla::removeTodos() {
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

void listaDupla::insereNoFim(Dado dado) {
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

void listaDupla::insereNoInicio(Dado dado) {
    noh* novo = new noh(dado);
    if (vazia()) {
        primeiro = novo;
        ultimo = novo;
    } else {
        primeiro->anterior = novo;
        novo->proximo = primeiro;
        primeiro = novo;
    }
    tamanho++;
}

void listaDupla::funcA() {
    noh* noh1 = primeiro;
    noh* noh2;
    noh* noh3;
    int d = 0;
    while (noh1 != NULL) {
        noh2 = noh1->anterior;
        noh3 = noh1->proximo;
        if (d == 0) {
            if (noh2 != NULL) {
                noh2->proximo = noh3;
            } else {
                primeiro = noh1->proximo;
            }
            if (noh3 != NULL) {
                noh3->anterior = noh2;
            } else {
                ultimo = noh1->anterior;
            }
            delete noh1;
        } else if (d % 2 == 0) {
            if (noh2 != NULL) {
                noh2->proximo = noh3;
            } else {
                primeiro = noh1->proximo;
            }
            if (noh3 != NULL) {
                noh3->anterior = noh2;
            } else {
                ultimo = noh1->anterior;
            }
            delete noh1;
        }
        noh1 = noh3;
        d++;
    }
}

void listaDupla::funcB(listaDupla& l) {
    noh* noh1 = primeiro;
    while (noh1 != NULL) {
        if (noh1->dado % 2 == 0) {
            noh* noh2 = new noh(noh1->dado);
            if (l.primeiro == NULL) {
                l.primeiro = noh2;
                l.ultimo = noh2;
            } else {
                l.ultimo->proximo = noh2;
                noh2->anterior = l.ultimo;
                l.ultimo = noh2;
            }
        }
        noh1 = noh1->proximo;
    }
}

//método básico que *percorre* uma lista, imprimindo seus elementos
// poderia percorrer fazendo outra ação (multiplicando valores, por exemplo)
void listaDupla::imprime() {
    noh* aux = primeiro;
    while (aux != NULL) {
        cout << aux->dado << ' ';
        aux = aux->proximo;
    }
    cout << endl;
}


/*
I: Insere uma palavra na lista original
X: Executa a função inverte
P: Imprime a lista em ordem direta
R: Imprime a lista em ordem reversa
Q: Encerra os comandos
*/

int main() {
    listaDupla lista1;
    listaDupla lista2;

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
    lista2.funcB(lista1);
    lista1.imprime();

    return 0;

}

