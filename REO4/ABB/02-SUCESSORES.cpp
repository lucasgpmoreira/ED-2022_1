#include <iostream>
#include <queue>

typedef int Dado;

enum Posicao { DIR, ESQ };

class Noh {
    friend class ABB;
public:
    Noh(Dado d);
    // Verifica se um nÃ³ Ã© filho da direita do pai.
    bool FilhoDaDireita();
    // Retorna a menor chave de uma sub-Ã¡rvore.
    Dado MenorRecursivo();
    // Verifica se existe sucessor e retorna o valor sucessor, se existir.
    bool Sucessor(Dado* ptResultado);
private:
    Dado valor;
    Noh* esq;
    Noh* dir;
    Noh* pai;
};

class ABB {
public:
    ABB() { raiz = NULL; }
    ~ABB();
    // Retorna um ponteiro para o nÃ³ de uma chave, ou NULL.
    Noh* Busca(Dado d);
    // Escreve uma Ã¡rvore nÃ­vel a nÃ­vel.
    void EscreverNivelANivel(std::ostream& saida);
    // Insere um dado na Ã¡rvore.
    void Inserir(Dado d);
    // Verifica se um dado tem sucessor e o retorna.
    bool Sucessor(Dado d, Dado* ptResultado);
private:
    Noh* raiz;
    Noh* InserirAux(Noh* umNoh, Dado umValor);
    void posOrdemDel(Noh* raiz);
};

using namespace std;
// === Classe Noh ==============================================================
Noh::Noh(Dado d) {
    // implementar
    valor = d;
    esq = NULL;
    dir = NULL;
    pai = NULL;
}

Dado Noh::MenorRecursivo() {
    // implementar
    if (this->esq == NULL) {
        return this->valor;
    } else {
        return this->esq->MenorRecursivo();
    }
}

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
    // implemente
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

bool ABB::Sucessor(Dado d, Dado* ptResultado) {
    Noh* aux = Busca(d);
    if (aux == NULL) {
        return false;
    } else {
        if (aux->dir != NULL) {
            *ptResultado = aux->dir->MenorRecursivo();
            return true;
        } else {
            Noh* pai = aux->pai;
            while (pai != NULL and aux == pai->dir) {
                aux = pai;
                pai = pai->pai;
            }
            if (pai == NULL) {
                return false;
            } else {
                *ptResultado = pai->valor;
                return true;
            }
        }
    }
    return false;
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

void ABB::EscreverNivelANivel(ostream& saida) {
    queue<Noh*> filhos;
    Noh noh = Dado();
    Noh* fimDeNivel = &noh; // noh especial para fim de nivel
    filhos.push(raiz);
    filhos.push(fimDeNivel);
    while (not filhos.empty()) {
        Noh* ptNoh = filhos.front();
        filhos.pop();
        if (ptNoh == fimDeNivel) {
            saida << "\n";
            if (not filhos.empty())
                filhos.push(fimDeNivel);
        } else {
            saida << '[';
            if (ptNoh != NULL) {
                saida << ptNoh->valor;
                filhos.push(ptNoh->esq);
                filhos.push(ptNoh->dir);
            }
            saida << ']';
        }
    }
}

// === Programa ================================================================
int main() {
    ABB arvore;
    Dado chave;
    char operacao;
    do {
        cin >> operacao;
        switch (operacao) {
        case 'i': // Inserir
            cin >> chave;
            arvore.Inserir(chave);
            break;
        case 'e': // Escrever
            arvore.EscreverNivelANivel(cout);
            break;
        case 's': { // Sucessor
            cin >> chave;
            Dado sucessor;
            while (arvore.Sucessor(chave, &sucessor)) {
                cout << sucessor << ' ';
                chave = sucessor;
            }
            cout << endl;
            break;
        }
        }
    } while (operacao != 'f');
    return 0;
}