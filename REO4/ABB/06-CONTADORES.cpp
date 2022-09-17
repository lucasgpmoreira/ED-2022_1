#include <iostream>

using namespace std;

typedef int Dado;

class Noh {
    friend class ABB;
public:
    Noh(Dado d);
    void imprimeAtributos();
    void contaDistancia();
private:
    int numPosicoes;
    int dist;
    Dado valor;
    Noh* esq;
    Noh* dir;
    Noh* pai;
};
// === Classe Noh ==============================================================
Noh::Noh(Dado d) {
    // implementar
    numPosicoes = 0;
    valor = d;
    esq = NULL;
    dir = NULL;
    pai = NULL;
}

void Noh::imprimeAtributos() {
    contaDistancia();
    cout << valor << "(" << numPosicoes << ")/" << dist << " ";
}

void Noh::contaDistancia() {
    dist = 0;
    Noh* atual = this;
    while (atual->pai != NULL) {
        dist++;
        atual = atual->pai;
    }

}

class ABB {
public:
    ABB() { raiz = NULL; }
    ~ABB();
    // Insere um dado na Ã¡rvore.
    void Inserir(Dado d);
    void removeAux(Dado d);
    void remove(Dado d);
    void preOrdem();
private:
    Noh* raiz;
    // Retorna um ponteiro para o nÃ³ de uma chave, ou NULL.
    Noh* Busca(Dado d);
    Noh* InserirAux(Noh* umNoh, Dado umValor);
    void posOrdemDel(Noh* raiz);
    void transplanta(Noh* antigo, Noh* novo);
    Noh* minimoAux(Noh* raizSubArvore);
    void preOrdemAux(Noh* umNoh);
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
    Noh* busca = Busca(d);
    if (busca == NULL) {
        raiz = InserirAux(raiz, d);
        busca = Busca(d);
        busca->numPosicoes = 1;
    } else {
        busca->numPosicoes++;
    }
}

void ABB::remove(Dado d) {
    Noh* busca = Busca(d);
    if (busca != NULL) {
        if (busca->numPosicoes > 1) {
            busca->numPosicoes--;
        } else {
            removeAux(d);
        }
    }
}

void ABB::removeAux(Dado d) {
    Noh* nohRemover = Busca(d);
    if (nohRemover == NULL) {
        //cerr << "Erro: chave nao encontrada" << endl;
        return;
    } else {
        if (nohRemover->esq == NULL) {
            transplanta(nohRemover, nohRemover->dir);
        } else if (nohRemover->dir == NULL) {
            transplanta(nohRemover, nohRemover->esq);
        } else {
            Noh* sucessor = minimoAux(nohRemover->dir);
            if (sucessor->pai != nohRemover) {
                transplanta(sucessor, sucessor->dir);
                sucessor->dir = nohRemover->dir;
                sucessor->dir->pai = sucessor;
            }
            transplanta(nohRemover, sucessor);
            sucessor->esq = nohRemover->esq;
            sucessor->esq->pai = sucessor;
        }
    }
    delete nohRemover;
}

void ABB::transplanta(Noh* antigo, Noh* novo) {
    if (raiz == antigo) {
        raiz = novo;
    } else if (antigo == antigo->pai->esq) {
        antigo->pai->esq = novo;
    } else {
        antigo->pai->dir = novo;
    }
    if (novo != NULL) {
        novo->pai = antigo->pai;
    }
}

Noh* ABB::minimoAux(Noh* raizSubArvore) {
    while (raizSubArvore->esq != NULL) {
        raizSubArvore = raizSubArvore->esq;
    }
    return raizSubArvore;
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

void ABB::preOrdem() {
    preOrdemAux(raiz);
    cout << endl;
}

void ABB::preOrdemAux(Noh* umNoh) {
    if (umNoh != NULL) {
        preOrdemAux(umNoh->esq);
        umNoh->imprimeAtributos();
        preOrdemAux(umNoh->dir);
    }
}

// === Programa ================================================================
int main() {
    int cont = 0;
    ABB arvore;
    Dado chave;
    /*
    10 valores a serem inseridos na árvore
5 valores a serem removidas da árvore
10 valores a serem inseridos na árvore
5 valores a serem removidas da árvore*/
    while (cont < 10) {
        cin >> chave;
        arvore.Inserir(chave);
        cont++;
    }
    arvore.preOrdem();
    cont = 0;
    while (cont < 5) {
        cin >> chave;
        arvore.remove(chave);
        cont++;
    }
    arvore.preOrdem();
    cont = 0;
    while (cont < 10) {
        cin >> chave;
        arvore.Inserir(chave);
        cont++;
    }
    arvore.preOrdem();
    cont = 0;
    while (cont < 5) {
        cin >> chave;
        arvore.remove(chave);
        cont++;
    }
    arvore.preOrdem();
    return 0;
}