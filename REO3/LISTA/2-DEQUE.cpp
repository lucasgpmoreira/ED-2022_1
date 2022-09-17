// Na lógica de lista DUPLAMENTE encadeada, cada nói tem um ponteiro para o pŕoximo e para o anterior
// Esse anterior é uma mão na roda para remover no final, etc

#include <iostream>
#include <cstdlib>
using namespace std;

typedef string Dado;

class noh {
    friend class deque;
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
class deque {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    int capacidade;
    void removeTodos(); // remove todos os elementos da lista

public:
    // construtores e destrutor
    deque(int cap);
    deque(const deque& umalLista);   // construtor de cópia
    ~deque();
    // sobrecarga do operador de atribuição
    // inserção, remoção e procura
    void insere(Dado dado);
    void insereNoFim(Dado dado);
    bool vazia();
    bool dequeEstaCheio();
    Dado removeNoInicio();
    Dado removeNoFim();
};

// constrói uma lista inicialmente vazia
deque::deque(int cap) {
    tamanho = 0;
    capacidade = cap;
    primeiro = NULL;
    ultimo = NULL;
}

// construtor de cópia (Insere no fim tudo que veio da outra lista)
deque::deque(const deque& umalista) {   // umalista = lista que será copiada
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
deque::~deque() {
    removeTodos();
}

// remove todos os elementos da lista
void deque::removeTodos() {
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

void deque::insereNoFim(Dado dado) {
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

// Verifica se a lista está vazia
bool deque::vazia() {
    return (tamanho == 0);
}

bool deque::dequeEstaCheio() {
    return (tamanho == capacidade);
}

// Remove no início
Dado deque::removeNoInicio() {
    Dado retorno;
    if (vazia()) { // verifica lista vazia
        return "lista vazia";
    }

    noh* removido = primeiro;
    primeiro = primeiro->proximo;
    if (primeiro != NULL) {
        primeiro->anterior = NULL;
    }
    retorno = removido->dado;
    delete removido;
    tamanho--;

    // se a lista ficou vazia
    if (vazia()) {
        ultimo = NULL;
    }
    return retorno;
}

Dado deque::removeNoFim() {
    Dado retorno;
    if (vazia()) { // verifica lista vazia
        return "Lista vazia";
    }

    noh* removido = ultimo;
    ultimo = ultimo->anterior;
    if (ultimo != NULL) {
        ultimo->proximo = NULL;
    }
    retorno = removido->dado;
    delete removido;
    tamanho--;

    // se a lista ficou vazia
    if (vazia()) {
        ultimo = NULL;
    }
    return retorno;
}

int main() {
    int capacidade;
    cin >> capacidade;
    deque meuDeque(capacidade);
    string comando;
    do {
        getline(cin >> ws, comando);
        if (comando != "sair") {
            if (comando != "undo") {
                if (not(meuDeque.dequeEstaCheio())) {
                    meuDeque.insereNoFim(comando);
                } else {
                    cout << "esqueci: "<< meuDeque.removeNoInicio() << endl;
                    meuDeque.insereNoFim(comando);
                }
            } else {
                if (meuDeque.vazia()) {
                    cout << "ERRO" << endl;
                } else {
                    cout << "desfazer: " << meuDeque.removeNoFim() << endl;
                }
            }
        }
    } while (comando != "sair");
    

    return 0;

}
