#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>

typedef int TChave;
typedef int TValor;

class Arvore {
    friend std::ostream& operator << (std::ostream& saida, const Arvore& arv);
public:
    Arvore();
    Arvore(const Arvore& arv);
    ~Arvore(); // Destrutor recursivo!
    // Retorna o valor associado a uma chave.
    TValor& Buscar(const TChave& chave);
    // Escreve uma Ã¡rvore nÃ­vel a nÃ­vel.
    void EscreverNivelANivel(std::ostream& saida);
    // Insere um chave/valor numa Ã¡rvore.
    void Inserir(const TChave& chave, const TValor& valor);
    // Remove chave da Ã¡rvore. Retorna falso se nÃ£o foi possÃ­vel remover.
    bool Remover(const TChave& chave);
    // Verifica se uma Ã¡rvore Ã© vazia.
    bool Vazia() { return mVazia; }
private:
    // Retorna ponteiro para a subÃ¡rvore com a chave de menor valor.
    Arvore* Menor();
    // Substitui chave/valor da raiz de uma Ã¡rvore pela chave/valor da raiz de uma subÃ¡rvore. A raiz da subÃ¡rvore Ã© removida.
    // Usado na remoÃ§Ã£o de chaves/valores em que uma subÃ¡rvore Ã© vazia.
    void SubstituirPor(Arvore* ptArv);

    bool mVazia;
    TChave mChave;
    TValor mValor;
    Arvore* mPtEsq;
    Arvore* mPtDir;
};

using namespace std;

Arvore::Arvore() {
    mVazia = true;
    mPtDir = NULL;
    mPtEsq = NULL;
}

Arvore::Arvore(const Arvore& arv) {
    //#warning COMPLETE AQUI
}

Arvore::~Arvore() {
    //#warning COMPLETE AQUI COM O DESTRUTOR RECURSIVO
}

Arvore* Arvore::Menor() {
    //#warning COMPLETE AQUI
}

// Substitui chave/valor da raiz de uma Ã¡rvore pela chave/valor da raiz de uma subÃ¡rvore. A raiz da subÃ¡rvore Ã© removida.
// Usado na remoÃ§Ã£o de chaves/valores em que uma subÃ¡rvore Ã© vazia.
void Arvore::SubstituirPor(Arvore* ptArv) {
    //#warning COMPLETE AQUI
}

TValor& Arvore::Buscar(const TChave& chave) {
    //#warning COMPLETE AQUI
}

void Arvore::Inserir(const TChave& chave, const TValor& valor) {
    Arvore* novo = new Arvore;
    novo->mChave = chave;
    novo->mValor = valor;
    if (mVazia) {
        mValor = valor;
        mChave = chave;
        mVazia = false;
    } else {
        Arvore* atual = this;
        Arvore* ante;
        while (atual != NULL) {
            ante = atual;
            if (atual->mChave > chave) {
                atual = atual->mPtEsq;
            } else {
                atual = atual->mPtDir;
            }
        }
        if (ante->mChave > chave) {
            ante->mPtEsq = novo;
        } else {
            ante->mPtDir = novo;
        }

    }
}

bool Arvore::Remover(const TChave& chave) {
}

ostream& operator << (ostream& saida, const Arvore& arv) {
    if (arv.mVazia)
        saida << "()";
    else
        saida << '(' << arv.mChave << '/' << arv.mValor << ' '
        << *arv.mPtEsq << ' ' << *arv.mPtDir << ')';
    return saida;
}

void Arvore::EscreverNivelANivel(ostream& saida) {
    queue<Arvore*> filhos;
    Arvore aux;
    Arvore* fimDeNivel = &aux; // marcador especial para fim de nivel
    filhos.push(this);
    filhos.push(fimDeNivel);
    while (not filhos.empty()) {
        Arvore* ptArv = filhos.front();
        filhos.pop();
        if (ptArv == fimDeNivel) {
            saida << "\n";
            if (not filhos.empty())
                filhos.push(fimDeNivel);
        } else {
            saida << '[';
            if (not ptArv->mVazia) {
                saida << ptArv->mChave << '/' << ptArv->mValor;
                filhos.push(ptArv->mPtEsq);
                filhos.push(ptArv->mPtDir);
            }
            saida << ']';
        }
    }
}

int main() {
    Arvore arvore;
    TChave chave;
    TValor valor;
    int operacao;
    do {
        cin >> operacao;
        switch (operacao) {
        case 1: // Inserir
            cin >> chave >> valor;
            arvore.Inserir(chave, valor);
            break;
        case 2: // Remover
            cin >> chave;
            if (not arvore.Remover(chave))
                cerr << "Impossível remover. A chave não existe." << endl;
            break;
        case 3: // Buscar
            try {
                cin >> chave;
                valor = arvore.Buscar(chave);
                cout << valor << endl;
            }
            catch (runtime_error& e) {
                cerr << e.what() << endl;
            }
            break;
        case 4: // Escrever tudo
            cout << arvore << endl;
            break;
        case 5: // Escrever nivel a nivel
            arvore.EscreverNivelANivel(cout);
            break;
        }
    } while (operacao > 0);
    return 0;
}