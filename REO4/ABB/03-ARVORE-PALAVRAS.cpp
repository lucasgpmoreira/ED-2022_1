#include <iostream>
#include <fstream>

using namespace std;

typedef string Dado;

class Noh {
    friend class ABB;
public:
    Noh(Dado d);
    // Verifica se um nÃ³ Ã© filho da direita do pai.
    Dado MenorRecursivo();
    void atualizaListaPosicoes(int pos);
private:
    struct listaPosicoes {
        int pos;
        listaPosicoes* proximo;
        listaPosicoes(int p) : pos(p) {proximo = NULL;}
    };
    listaPosicoes* primeiraPos;
    Dado valor;
    Noh* esq;
    Noh* dir;
    Noh* pai;
    void imprimeListaPos();
};
// === Classe Noh ==============================================================
Noh::Noh(Dado d) {
    // implementar
    valor = d;
    esq = NULL;
    dir = NULL;
    pai = NULL;
    primeiraPos = NULL;
}

void Noh::atualizaListaPosicoes(int pos) {
    listaPosicoes* novo = new listaPosicoes(pos);
    if (primeiraPos == NULL) {
        primeiraPos = novo;
    } else {
        listaPosicoes* aux = primeiraPos;
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }
        aux->proximo = novo;
    }
}

void Noh::imprimeListaPos() {
    if (primeiraPos != NULL) {
        listaPosicoes* aux = primeiraPos;
        while (aux != NULL) {
            cout << aux->pos << " ";
            aux = aux->proximo;
        }
        cout << endl;
    }
}

class ABB {
public:
    ABB() { raiz = NULL; }
    ~ABB();
    // Insere um dado na Ã¡rvore.
    void Inserir(Dado d, int pos);
    bool procuraPosicoes(Dado chave);
private:
    Noh* raiz;
    // Retorna um ponteiro para o nÃ³ de uma chave, ou NULL.
    Noh* Busca(Dado d);
    Noh* InserirAux(Noh* umNoh, Dado umValor);
    void posOrdemDel(Noh* raiz);
};

// === Classe ABB ==============================================================
ABB::~ABB() {
    posOrdemDel(raiz);
}

void ABB::posOrdemDel(Noh* umNoh) {
    if (umNoh != NULL) {
        posOrdemDel(umNoh->esq);
        posOrdemDel(umNoh->dir);
        delete umNoh;
    }
}


void ABB::Inserir(Dado d, int pos) {
    Noh* busca = Busca(d);
    if (busca == NULL) {
        raiz = InserirAux(raiz, d);
        Noh* atualiza = Busca(d);
        atualiza->atualizaListaPosicoes(pos);
    } else {
        busca->atualizaListaPosicoes(pos);
    }
}

Noh* ABB::InserirAux(Noh* umNoh, Dado umValor) {
    if (umNoh == NULL) {
        Noh* novo = new Noh(umValor);
        return novo;
    } else {
        if (umValor < umNoh->valor) {
            umNoh->esq = InserirAux(umNoh->esq, umValor);
            umNoh->esq->pai = umNoh;

        } else {
            umNoh->dir = InserirAux(umNoh->dir, umValor);
            umNoh->dir->pai = umNoh;
        }
    }
    return umNoh;
}


Noh* ABB::Busca(Dado d) {
    Noh* atual = raiz;
    while (atual != NULL) {
        if (atual->valor == d) {
            return atual;
        } else if (atual->valor > d) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }
    return atual;
}

bool ABB::procuraPosicoes(Dado chave) {
    Noh* busca = Busca(chave);
    if (busca == NULL) {
        return false;
    } else {
        //imprime a lista de posicoes daquele no
        busca->imprimeListaPos();
    }
    return true;
}

// === Programa ================================================================
int main() {
    int cont = 1;
    ABB arvore;
    Dado chave;
    ifstream arq("entrada.txt");
    while (arq >> chave) {
        arvore.Inserir(chave, cont);
        cont++;
    }
    cin >> chave;
    //chama o método que retorna um booleano falso caso a chave não seja encontrada
    if (!(arvore.procuraPosicoes(chave))) {
        cout << -1;
    }
    return 0;
}