#include <string>
#include <iostream>
#include <stdexcept>

class Info {
    friend class Noh;
    friend class ABB;
public:
    bool operator == (const Info& i) { return chave == i.chave; }
    bool operator < (const Info& i) { return chave < i.chave; }
    int chave;
    std::string valor;
};

class Noh {
    friend class ABB;
public:
    Noh(Info d);
private:
    Info dados;
    Noh* esq;
    Noh* dir;
};

Noh::Noh(Info d) {
    dados = d;
    esq = NULL;
    dir = NULL;
}

class ABB {
public:
    ABB() { raiz = NULL; }
    ~ABB();
    // Insere um Info na Ã¡rvore.
    void Inserir(Info i);
    Info Busca(Info i);
    void emOrdem();
private:
    Noh* raiz;
    Noh* InserirAux(Noh* umNoh, Info umValor);
    void posOrdemDel(Noh* raiz);
    void emOrdemAux(Noh* umNoh);
};

using namespace std;

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

void ABB::Inserir(Info i) {
    raiz = InserirAux(raiz, i);
}

Noh* ABB::InserirAux(Noh* umNoh, Info umValor) {
    if (umNoh == NULL) {
        Noh* novo = new Noh(umValor);
        return novo;
    } else {
        if (umValor < umNoh->dados) {
            umNoh->esq = InserirAux(umNoh->esq, umValor);
        } else {
            umNoh->dir = InserirAux(umNoh->dir, umValor);
        }
    }
    return umNoh;
}

Info ABB::Busca(Info i) {
    Noh* atual = raiz;
    while (atual != NULL) {
        if (atual->dados == i) {
            return atual->dados;
        } else if (atual->dados < i) {
            atual = atual->dir;
        } else {
            atual = atual->esq;
        }
    }
    throw runtime_error("");
}

void ABB::emOrdem() {
    emOrdemAux(raiz);
    cout << endl;
}

void ABB::emOrdemAux(Noh* umNoh) {
    if (umNoh != NULL) {
        emOrdemAux(umNoh->esq);
        cout << "(" << umNoh->dados.chave << "," << umNoh->dados.valor << ")";
        emOrdemAux(umNoh->dir);
    }
}

int main() {
    ABB arvore;
    Info info;
    char operacao;
    do {
        cin >> operacao;
        switch (operacao) {
        case 'i': // Inserir
            cin >> info.chave >> info.valor;
            arvore.Inserir(info);
            break;
        case 'b': // Buscar
            try {
                cin >> info.chave; // ler a chave
                info = arvore.Busca(info);
                cout << info.valor << endl;
            }
            catch (runtime_error& e) {
                cout << "INEXISTENTE" << endl;
            }
            break;
        case 'e': // Escrever tudo
            arvore.emOrdem();
            break;
        case 'f': // Finalizar execução
            break;
        default:
            cerr << "Comando invalido!\n";
        }
    } while (operacao != 'f');
    return 0;
}
