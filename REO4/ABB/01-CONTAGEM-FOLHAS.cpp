#include <iostream>
#include <queue>
#include <stdexcept>

using namespace std;

typedef int Dado;

enum Posicao { DIR, ESQ };

class Noh {
    friend class ABB;
public:
    Noh(Dado d);
    ~Noh();
    unsigned NroDeFolhas() const;
private:
    Dado valor;
    Noh* esq;
    Noh* dir;
    Noh* pai;
};

Noh::Noh(Dado d) {
    valor = d;
    esq = NULL;
    dir = NULL;
    pai = NULL;
}

Noh::~Noh() {
    // implemente o Destrutor recursivo!
}

class ABB {
public:
    ABB();
    ~ABB();
    // Escreve uma Ã¡rvore nÃ­vel a nÃ­vel.
    // Pode ser Ãºtil para depurar o programa.
    void EscreverNivelANivel(std::ostream& saida);
    // Insere um dado na Ã¡rvore.
    void Inserir(Dado d);
    // Retorna o nro de folhas na Ã¡rvore.
    unsigned NroDeFolhas();
private:
    int numeroDeFolhas;
    Noh* raiz;
    Noh* InserirAux(Noh* umNoh, Dado d);
    void posOrdemDel(Noh* umNoh);
    void posOrdem(Noh* umNoh);
};

ABB::~ABB() {
    posOrdemDel(raiz);
}

ABB::ABB() {
    // implemente
    raiz = NULL;
    numeroDeFolhas = 0;
}

void ABB::posOrdemDel(Noh* umNoh) {
    if (umNoh != NULL) {
        posOrdemDel(umNoh->esq);
        posOrdemDel(umNoh->dir);
        delete umNoh;
    }
}

void ABB::posOrdem(Noh* umNoh) {
    if (umNoh != NULL) {
        posOrdem(umNoh->esq);
        posOrdem(umNoh->dir);
        if (umNoh->esq == NULL && umNoh->dir == NULL) {
            numeroDeFolhas++;
        }
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

unsigned ABB::NroDeFolhas() {
    posOrdem(raiz);
    return numeroDeFolhas;
}

void ABB::EscreverNivelANivel(ostream& saida) {
    queue<Noh*> filhos;
    Noh aux = Dado();
    Noh* fimDeNivel = &aux; // marcador especial para fim de nivel
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

int main() {
    unsigned qtde;
    cin >> qtde;
    ABB arvore;
    Dado valor;
    for (unsigned i = 0; i < qtde; ++i) {
        cin >> valor;
        arvore.Inserir(valor);
    }
    cout << arvore.NroDeFolhas() << endl;
    return 0;
}