#include <iostream>

using namespace std;

typedef int Dado;

class Noh {
    friend class ABB;
public:
    Noh(Dado d);
    // Verifica se um nÃ³ Ã© filho da direita do pai.
    Dado MenorRecursivo();
    void atualizaListaPosicoes(int pos);
private:
    Dado valor;
    Noh* esq;
    Noh* dir;
    Noh* pai;
};
// === Classe Noh ==============================================================
Noh::Noh(Dado d) {
    // implementar
    valor = d;
    esq = NULL;
    dir = NULL;
    pai = NULL;
}


class ABB {
public:
    ABB() { raiz = NULL; }
    ~ABB();
    // Insere um dado na Ã¡rvore.
    void Inserir(Dado d);
    void emOrdem(int& numDeNos, int& dif);
private:
    Noh* raiz;
    // Retorna um ponteiro para o nÃ³ de uma chave, ou NULL.
    Noh* Busca(Dado d);
    Noh* InserirAux(Noh* umNoh, Dado umValor);
    void posOrdemDel(Noh* raiz);
    void emOrdemAux(Noh* umNoh, int& numDeNos, int &dif);
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


void ABB::Inserir(Dado d) {
    raiz = InserirAux(raiz, d);
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

void ABB::emOrdem(int& numDeNos, int& dif) {
    emOrdemAux(raiz, numDeNos, dif);
}

//em ordem com contagem de nos e subarvore esqueda e direita
void ABB::emOrdemAux(Noh* umNoh, int& numDeNos, int &dif) {
    if (umNoh != NULL) {
        emOrdemAux(umNoh->esq, numDeNos, dif);
        if (umNoh->valor < raiz->valor) {
            dif++;
        } else if (umNoh->valor > raiz->valor) {
            dif--;
        }
        numDeNos++;
        emOrdemAux(umNoh->dir, numDeNos, dif);
    }
}

// === Programa ================================================================
int main() {
    ABB arvore;
    Dado chave;
    do {
        cin >> chave;
        if (chave != -1) {
            arvore.Inserir(chave);
        }
    } while (chave != -1);
    int numDeNos = 0;
    int diferenca = 0;
    arvore.emOrdem(numDeNos, diferenca);
    cout << numDeNos << " " << diferenca << endl;
    return 0;
}