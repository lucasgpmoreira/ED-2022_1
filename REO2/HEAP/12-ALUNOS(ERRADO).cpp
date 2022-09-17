#include <iostream>   // Pode usar varias coisas prontas
#include <vector>     // mas e' preciso completar a classe
#include <limits>     // classe Heap. E' permitido fazer
#include <string>     // alteracoes na classe Heap.
#include <stdexcept>

using namespace std;

class Atividade {
public:
    int nota;
    int tentativas;
};

class Aluno {
public:
    Aluno();
    Aluno(unsigned matr, const string& n);
    ~Aluno();
    void InserirAtividade(const Atividade& a);
    string Nome() const { return nome; }
    unsigned Matricula() { return matricula; }
    float Media() const;
    int Tentativas() const;
    char retornaPrimeiroChar();
protected:
    unsigned matricula;
    string nome;
    vector<Atividade> vetAtividades;
};

Aluno::Aluno()
    : matricula(0), nome(), vetAtividades() {
}

Aluno::Aluno(unsigned matr, const string& n)
    : matricula(matr), nome(n), vetAtividades() {
}

Aluno::~Aluno() {
}

void Aluno::InserirAtividade(const Atividade& a) {
    vetAtividades.push_back(a);
}

float Aluno::Media() const {
    float soma = 0.0f;
    unsigned nroAtividades = unsigned(vetAtividades.size());
    for (unsigned i = 0; i < nroAtividades; ++i)
        soma += float(vetAtividades.at(i).nota);
    return soma / float(nroAtividades);
}

int Aluno::Tentativas() const {
    int tentativas = 0;
    unsigned nroAtividades = unsigned(vetAtividades.size());
    for (unsigned i = 0; i < nroAtividades; ++i)
        tentativas += vetAtividades.at(i).tentativas;
    return tentativas;
}

char Aluno::retornaPrimeiroChar() {
    char a = nome[0];
    return a;
}

typedef Aluno TDado;

class Heap {
    // classe Heap (max-heap, o maior fica na raiz/inicio)
public:
    // Criar heap sem dados e com capacidade informada
    Heap(int cap);
    // Destruttor
    ~Heap();
    // Inserir um dado na heap
    void Inserir(const TDado& d);
    // Consulta a raiz
    TDado Raiz();
    // Retira e retorna a raiz
    TDado Retirar();
    // Verifica se a heap está vazia
    bool Vazia();
protected:
    void corrigeDescendo(int i);
    void corrigeSubindo(int i);
    inline int Direito(int i);
    inline int Esquerdo(int i);
    inline int Pai(int i);
    int mCapacidade;
    int mTamanho;
    TDado* mVetDados;
};

using namespace std;

Heap::Heap(int cap) {
    // Criar heap sem dados e com capacidade informada
    mCapacidade = cap;
    mTamanho = 0;
    mVetDados = new TDado[cap];
}

Heap::~Heap() {
    // Destrutor
    delete[] mVetDados;
}

void Heap::corrigeDescendo(int i) {
    // Arruma as posicoes de i para baixo.
    int esq = Esquerdo(i);
    int dir = Direito(i);
    int maior = i;
    /*
    if (esq < mTamanho and dir < mTamanho and mVetDados[esq].Media() == mVetDados[dir].Media()) {
        if (mVetDados[esq].Tentativas() > mVetDados[dir].Tentativas()) {
            maior = esq;
        } else if (mVetDados[esq].Tentativas() < mVetDados[dir].Tentativas()) {
            maior = dir;
        } else {
            if (mVetDados[esq].retornaPrimeiroChar() > mVetDados[dir].retornaPrimeiroChar()) {
                maior = esq;
            } else {
                maior = dir;
            }
        }
    }*/
    if (mVetDados[esq].Media() == mVetDados[maior].Media()) {
        if (esq < mTamanho and mVetDados[esq].Tentativas() > mVetDados[maior].Tentativas()) {
            maior = esq;
        } else if (dir < mTamanho and mVetDados[dir].Tentativas() < mVetDados[maior].Tentativas()) {
            maior = dir;
        } else if (mVetDados[esq].Tentativas() == mVetDados[maior].Tentativas()) {
            char pChar = mVetDados[esq].retornaPrimeiroChar();
            char sChar = mVetDados[maior].retornaPrimeiroChar();
            if (pChar > sChar) {
                cout << "true" << endl;
            } else {
                cout << "false" << endl;
            }
            if (pChar > sChar) {
                maior = esq;
            }
            if (pChar < sChar) {
                maior = dir;
            }
        }
    }
    if (esq < mTamanho and mVetDados[esq].Media() > mVetDados[maior].Media()) {
        maior = esq;
    }
    if (dir < mTamanho and mVetDados[dir].Media() > mVetDados[maior].Media()) {
        maior = dir;
    }
    if (maior != i) {
        swap(mVetDados[i], mVetDados[maior]);
        corrigeDescendo(maior);
    }
}

void Heap::corrigeSubindo(int i) {
    // Arruma as posicoes de i para cima.
    int pai = Pai(i);
    if (pai >= 0 and mVetDados[i].Media() == mVetDados[pai].Media()) {
        if (pai >= 0 and mVetDados[i].Tentativas() > mVetDados[pai].Tentativas()) {
            swap(mVetDados[i], mVetDados[pai]);
            corrigeSubindo(pai);
        } else if (pai >= 0 and mVetDados[i].Tentativas() < mVetDados[pai].Tentativas()) {
            swap(mVetDados[i], mVetDados[pai]);
            corrigeSubindo(pai);
        } else {
            if (pai >= 0 and mVetDados[i].retornaPrimeiroChar() > mVetDados[pai].retornaPrimeiroChar()) {
                swap(mVetDados[i], mVetDados[pai]);
                corrigeSubindo(pai);
            } else {
                swap(mVetDados[i], mVetDados[pai]);
                corrigeSubindo(pai);
            }
        }
    }
    if (pai >= 0 and mVetDados[pai].Media() < mVetDados[i].Media()) {
        swap(mVetDados[pai], mVetDados[i]);
        corrigeSubindo(pai);
    }
}

int Heap::Pai(int i) {
    // Retorna o indice do pai de i
    return (i - 1) / 2;
}

int Heap::Esquerdo(int i) {
    // Retorna o indice do filho a esquerda de i
    return 2 * i + 1;
}

int Heap::Direito(int i) {
    // Retorna o indice do filho a direita de i
    return 2 * i + 2;
}

TDado Heap::Raiz() {
    if (mTamanho == 0) {
        cerr << "Heap vazia nao tem raiz." << endl;
        return TDado();
    }
    return mVetDados[0];
}

TDado Heap::Retirar() {
    if (mTamanho == 0) {
        cerr << "Impossivel retirar de heap vazia." << endl;
        return TDado();
    }
    TDado raiz = mVetDados[0];
    swap(mVetDados[0], mVetDados[mTamanho - 1]);
    mTamanho--;
    corrigeDescendo(0);
    return raiz;
}

bool Heap::Vazia() {
    return mTamanho == 0;
}

void Heap::Inserir(const TDado& d) {
    if (mTamanho == mCapacidade) {
        cerr << "Impossivel inserir em heap cheio.\n";
        return;
    }
    mVetDados[mTamanho] = d;
    corrigeSubindo(mTamanho);
    mTamanho++;
}

int main() {
    unsigned qtdeAlunos;
    cin >> qtdeAlunos;
    unsigned qtdeAtividades;
    cin >> qtdeAtividades;
    Heap heap(qtdeAlunos);
    Atividade atividade;
    string nome;
    unsigned matricula;
    for (unsigned i = 0; i < qtdeAlunos; ++i) {
        cin >> matricula >> nome;
        Aluno aluno(matricula, nome);
        for (unsigned i = 0; i < qtdeAtividades; ++i) {
            cin >> atividade.nota >> atividade.tentativas;
            aluno.InserirAtividade(atividade);
        }
        heap.Inserir(aluno);
    }
    Aluno alunoDestaque(heap.Retirar());
    cout << '[' << alunoDestaque.Matricula() << "] " << alunoDestaque.Nome() << endl;
    return 0;
}