#include <iostream>
#include <cstdlib>
using namespace std;

typedef int Dado; // Typedef permite criar novos tipos a partir de outros (criamos basicamente um "apelido" para int)

class noh {
    friend class lista;
private:
    const Dado dado; // poderia ser outro tipo de variavel (const para nao ser alterado)
    noh* proximo;

public:
    noh(Dado d = 0); // Cosntrutor padrao
};

noh::noh(Dado d) : dado(d) {
    proximo = NULL;
}

// lista dinamicamente encadeada
class lista {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista
public:
    // construtores e destrutor
    lista();
    lista(const lista& umalLista);   // construtor de copia
    lista& operator=(const lista& umalista); // sobrecarga do operador de atribuicao
    ~lista();
    void insereNoFim(Dado dado);
    void imprime();
    bool vazia();
    void removeNoInicio();
    void removeNoFim();
};

// constroi uma lista inicialmente vazia
lista::lista() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

// construtor de copia (Insere no fim tudo que veio da outra lista)
lista::lista(const lista& umalista) {   // umalista = lista que ser� copiada
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;

    // percorre a lista recebida como parametro, copiando os dados
    noh* aux = umalista.primeiro;
    while (aux != NULL) {
        insereNoFim(aux->dado);
        aux = aux->proximo;
    }
}

// destrutor da lista (chama funcao privada auxiliar)
lista::~lista() {
    removeTodos();
}

// remove todos os elementos da lista
void lista::removeTodos() {
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

lista& lista::operator=(const lista& umalista){
  // limpa a lista atual
  removeTodos();
  // percorre a lista recebida como parametro, copiando os dados
  noh* aux = umalista.primeiro;
  while (aux != NULL){
    insereNoFim(aux->dado);
    aux = aux->proximo;
  }
  return *this;   // Retorna a referencia do objeto atual
}

void lista::insereNoFim(Dado dado) {
    // * primeiro criamos o novo no
    noh* novo = new noh(dado);

    // * agora inserimos o no na lista
    // se a lista estiver vazia, inserimos o primeiro no
    if (vazia()) { // ou (primeiro == NULL) ou (tamanho ==0 )
        primeiro = novo;
        ultimo = novo;
    } else { // ja tem elementos na lista, insere no final
        ultimo->proximo = novo;
        ultimo = novo;
    }
    tamanho++;
}

//metodo basico que *percorre* uma lista, imprimindo seus elementos
// poderia percorrer fazendo outra acao (multiplicando valores, por exemplo)
void lista::imprime() {
    noh* aux = primeiro;

    while (aux != NULL) {
        cout << aux->dado << ' ';
        aux = aux->proximo;
    }
    cout << endl;
}

// Para imprimir REVERSO, usaremos PILHA DE RECURSAO
// Para isso, precisa de uma funcao auxiliar

// Verifica se a lista esta vazia
bool lista::vazia() {
    return (primeiro == NULL);
}

void lista::removeNoInicio(){
  if(vazia()){ // verifica lista vazia
    cerr << "Remocao em lista vazia" << endl;
    exit(EXIT_FAILURE);
  }

  noh* removido = primeiro;
  primeiro = primeiro -> proximo;
  delete removido;
  tamanho--;

  // se a lista ficou vazia
  if(tamanho == 0){
    ultimo = NULL;
  }
}

void lista::removeNoFim() {
    if (vazia()) { // verifica lista vazia
        cerr << "Remocao em lista vazia" << endl;
        exit(EXIT_FAILURE);
    }

    noh* aux = primeiro;
    noh* anterior;
    while (aux->proximo != NULL) {  // Aux para no ULTIMO
        anterior = aux;
        aux = aux->proximo;
    }
    delete ultimo;  // apagou aquele que aux aponta
    anterior->proximo = NULL;
    ultimo = anterior;

    if (vazia()) {  // Verifica se a lista ficou vazia com isso
        primeiro = NULL;
    }
    tamanho--;
}

int main() {
    lista minhalista;
    lista resto;
    int tamanho;
    int valor;
    cin >> tamanho;
    for (int i = 0; i < tamanho; i++) {
        cin >> valor;
        minhalista.insereNoFim(valor);
    }

    int quantSeparada;
    cin >> quantSeparada;

    if (quantSeparada >= tamanho) {
        minhalista.imprime();
        cout << -1 << endl;
    } else  if ((quantSeparada + 1) == tamanho) {
        minhalista.imprime();
        cout << endl;
    } else {
        resto = minhalista;
        for (int i = 0; i < quantSeparada - 1; i++) {
            minhalista.removeNoFim();
        }
        for (int i = 0; i < quantSeparada + 1; i++) {
            resto.removeNoInicio();
        }
        minhalista.imprime();
        resto.imprime();
    }

    return 0;
}
