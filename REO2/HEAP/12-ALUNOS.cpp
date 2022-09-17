#include <iostream>   
#include <string>
#include <algorithm>
#include <stdexcept>

struct Atividade {
    int nota;
    int tentativas;
};

class Aluno {
public:
    Aluno();
    Aluno(unsigned matr, const std::string& n, unsigned capAtiv);
    Aluno(const Aluno& umAluno); // construtor de cópia para evitar problemas
    // com atributos dinâmicos
    ~Aluno();
    void InserirAtividade(const Atividade& a);
    std::string Nome() const { return nome; }
    unsigned Matricula() { return matricula; }
    float Media() const;
    int Tentativas() const;
    Aluno& operator=(const Aluno& umAluno); // sobrecarga do operador de atribuição
    // para evitar problemas com atributos dinâmicos
private:
    unsigned matricula;
    std::string nome;
    unsigned capAtividades;
    Atividade* vetAtividades;
    unsigned nroAtividades;
};

Aluno::Aluno()
    : matricula(0), nome(""), capAtividades(0), nroAtividades(0) {
    vetAtividades = NULL;
}

Aluno::Aluno(unsigned matr, const std::string& n, unsigned capAtiv)
    : matricula(matr), nome(n), capAtividades(capAtiv), nroAtividades(0) {
    vetAtividades = new Atividade[capAtiv];
}

Aluno::Aluno(const Aluno& umAluno) {
    matricula = umAluno.matricula;
    nome = umAluno.nome;
    capAtividades = umAluno.capAtividades;
    nroAtividades = umAluno.nroAtividades;
    vetAtividades = new Atividade[capAtividades];
    std::copy(umAluno.vetAtividades, umAluno.vetAtividades + capAtividades, vetAtividades);
}

Aluno::~Aluno() {
    delete[] vetAtividades;
}

Aluno& Aluno::operator=(const Aluno& umAluno) {
    matricula = umAluno.matricula;
    nome = umAluno.nome;
    capAtividades = umAluno.capAtividades;
    nroAtividades = umAluno.nroAtividades;
    delete[] vetAtividades;
    vetAtividades = new Atividade[capAtividades];
    std::copy(umAluno.vetAtividades, umAluno.vetAtividades + capAtividades, vetAtividades);
    return *this;
}

void Aluno::InserirAtividade(const Atividade& a) {
    vetAtividades[nroAtividades] = a;
    nroAtividades++;
}

float Aluno::Media() const {
    float soma = 0.0f;
    for (unsigned i = 0; i < nroAtividades; i++)
        soma += float(vetAtividades[i].nota);
    return soma / float(nroAtividades);
}

int Aluno::Tentativas() const {
    int tentativas = 0;
    for (unsigned i = 0; i < nroAtividades; i++)
        tentativas += vetAtividades[i].tentativas;
    return tentativas;
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
    bool comparaSeEhMaior(TDado aE, TDado aD);
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

bool Heap::comparaSeEhMaior(TDado aE, TDado aD) {
    // Compara se aE é maior que aD
    bool retorno;

    if (aE.Media() == aD.Media()) {
        if (aE.Tentativas() < aD.Tentativas()) {
            retorno = true;
        } else if (aE.Tentativas() > aD.Tentativas()) {
            retorno = false;
        } else {
            if (aE.Nome() < aD.Nome()) {
                retorno = true;
            } else {
                retorno = false;
            }
        }
    } else if (aE.Media() < aD.Media()) {
        retorno = false;
    } else {
        retorno = true;
    }

    return retorno;
}

void Heap::corrigeDescendo(int i) {
    // Arruma as posicoes de i para baixo.
    int esq = Esquerdo(i);
    int dir = Direito(i);
    int maior = i;

    if (esq < mTamanho and comparaSeEhMaior(mVetDados[esq], mVetDados[maior])) {
        maior = esq;
    }
    if (dir < mTamanho and comparaSeEhMaior(mVetDados[dir], mVetDados[maior])) {
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
    if (pai >= 0 and comparaSeEhMaior(mVetDados[i], mVetDados[pai])) {
        swap(mVetDados[i], mVetDados[pai]);
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

int retorno () {
    
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
    for (unsigned i = 0; i < qtdeAlunos; i++) {
        cin >> matricula >> nome;
        Aluno aluno(matricula, nome, qtdeAtividades);
        for (unsigned i = 0; i < qtdeAtividades; i++) {
            cin >> atividade.nota >> atividade.tentativas;
            aluno.InserirAtividade(atividade);
        }
        heap.Inserir(aluno);
    }
    Aluno alunoDestaque(heap.Retirar());
    cout << '[' << alunoDestaque.Matricula() << "] " << alunoDestaque.Nome() << endl;
    return 0;
}
