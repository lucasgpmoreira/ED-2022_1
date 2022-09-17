#include <iostream>

using namespace std;

typedef int Dado;

class noh {
    friend class lista;
private:
    const Dado dado;
    noh* proximo;
public:
    noh(Dado d = 0);
};

noh::noh(Dado d) : dado(d) {
    proximo = NULL;
}

class lista {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    bool listaVazia() { return tamanho == 0; };
public:
    lista();
    ~lista();
    void insere(Dado dado);
    void insere(Dado dado, int pos);
    void remove(int posicao);
    int procura(Dado valor);
    void imprime();
    inline bool vazia();
};

// constrói uma lista inicialmente vazia
lista::lista() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

lista::~lista() {
    noh* iter = primeiro;
    noh* proximo = NULL;
    while (iter != NULL) {
        proximo = iter->proximo;
        delete iter;
        iter = proximo;
    }
}

// método básico que *percorre* a lista, imprimindo seus elementos
void lista::imprime() {
    noh* aux = primeiro;
    while (aux != NULL) {
        cout << aux->dado << " ";
        aux = aux->proximo;
    }
    cout << endl;
}

// insere por padrão no final da lista
void lista::insere(Dado dado) {
    // * primeiro criamos o novo no
    noh* novo = new noh(dado);

    // * agora inserimos o na na lista
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

// insere um dado em uma determinada posição da lista
void lista::insere(Dado dado, int posicao) {
    // * primeiro criamos o novo no
    noh* novo = new noh(dado);

    // * agora inserimos o no na lista
    // verificamos antes se e possivel inserir na posicao
    if ((posicao <= tamanho) and (posicao >= 0)) {
        if (vazia()) { // ou (primeiro == NULL) ou (tamanho ==0))
            primeiro = novo;
            ultimo = novo;
        } else if (posicao == 0) { // Insere no Inicio
            novo->proximo = primeiro;
            primeiro = novo;
        } else if (posicao == tamanho) { // Insere no Fim
            ultimo->proximo = novo;
            ultimo = novo;
        } else { // insere no meio da lista
            noh* aux = primeiro;
            int posAux = 0;
            // chegando na posicao da lista
            while (posAux < (posicao - 1)) {  
                aux = aux->proximo;
                posAux++;
            }
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }
        tamanho++;
    } else {
        cerr << "Posicao Inexistente!" << endl;
        exit(EXIT_FAILURE);
    }
}

// remove o item da posição passada por parâmetro
// Atenção - o código deve tratar de posição inválidas
void lista::remove(int posicao) {
    if(listaVazia()) {
        //cerr << "Lista Vazia!" << endl;
        exit(EXIT_FAILURE);
    } else if (posicao < 0 or posicao >= tamanho) {
        cerr << "Posicao Inexistente!" << endl;
        exit(EXIT_FAILURE);
    } else {
        noh *aux = primeiro;
        noh *ante = NULL;
        while (aux != NULL and posicao > 0) {
            ante = aux;
            aux = aux->proximo;
            posicao--;
        }
        if (aux != NULL) {
            if (aux == primeiro) {
                primeiro = aux->proximo;
                if (vazia()) {
                    ultimo = NULL;
                }
            } else if (aux == ultimo) {
                if (ante == NULL) {
                    primeiro = NULL;
                } else {
                    ante->proximo = NULL;
                }
                ultimo = ante;
            } else {
                ante->proximo = aux->proximo;
            }
            delete aux;
            tamanho--;
        }
    }
}

// procura por um elemento e retorna a posição ou -1 se não encontrado
int lista::procura(Dado valor) {
    int pos = 0;
    noh* aux = primeiro;
    while (aux != NULL) {
        if (aux->dado == valor) {
            return pos;
        } else {
            aux = aux->proximo;
            pos++;
        }
    }
    return -1;
}

// verifica se a lista está vazia
inline bool lista::vazia() {
    return tamanho == 0;
}

int main() { // NÃO MODIFIQUE!
    lista minhaLista;
    char opcao;
    int valor, pos;
    cin >> opcao;
    while (opcao != 'Q') {
        switch (opcao) {
        case 'I':
            cin >> valor;
            minhaLista.insere(valor);
            break;
        case 'W':
            cin >> valor;
            cin >> pos;
            minhaLista.insere(valor, pos);
            break;
        case 'P':
            cin >> valor;
            cout << minhaLista.procura(valor) << endl;
            break;
        case 'R':
            cin >> pos;
            minhaLista.remove(pos);
            break;
        case 'V':
            cout << minhaLista.vazia() << endl;
            break;
        }
        cin >> opcao;
    }
    minhaLista.imprime();
    return 0;
}
