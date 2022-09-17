// Na lógica de lista DUPLAMENTE encadeada, cada nói tem um ponteiro para o pŕoximo e para o anterior
// Esse anterior é uma mão na roda para remover no final, etc

#include <iostream>
#include <cstdlib>
using namespace std;

typedef string Dado;

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
    void inverte(); // inverte a lista
    void insereNoFim(Dado dado);
    void imprime();
    void imprimeReverso();
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

void listaDupla::inverte() {
    noh* aux = primeiro;
    noh* aux2;

    while (aux != NULL) {
        aux2 = aux->anterior;
        aux->anterior = aux->proximo;
        aux->proximo = aux2;
        aux = aux->anterior;
    }

    if (primeiro != NULL) {
        ultimo = primeiro;
    }
    
    if (aux2 != NULL) {
        primeiro = aux2->anterior;
    }

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

void listaDupla::imprimeReverso() {
    noh* aux = ultimo;
    while (aux != NULL) {
        cout << aux->dado << ' ';
        aux = aux->anterior;
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
    listaDupla lista;
    char comando;
    string palavra;
    do {
        cin >> comando;
        switch (comando) {
        case 'I':
            cin >> palavra;
            lista.insereNoFim(palavra);
            break;
        case 'X':
            lista.inverte();
            break;
        case 'P':
            lista.imprime();
            break;
        case 'R':
            lista.imprimeReverso();
            break;
        case 'Q':
            lista.imprime();
            lista.imprimeReverso();
            break;
        }
    } while (comando != 'Q');
    return 0;

}

