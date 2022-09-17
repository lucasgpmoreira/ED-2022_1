#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

typedef int dado;
const int INVALIDO = -1;

class Torneio {
private:
    dado* Heap;
    int capacidade;
    int Tamanho;
    int InicioDados; // Prineiro n folha
    inline int Pai(int i);
    inline int Esquerdo(int i);
    inline int Direito(int i);
    void Arruma();    // heapify (constroi o heap e arruma com corrige descendo da metade pra cima)   // auxiliar
    void Copia(bool copiaOMaior, int i);  // auxiliar
    void CopiaSubindo(int i);   // auxiliar

public:
    Torneio(dado vet[], int tam);   // construtor com tamanho
    ~Torneio();
    int retornaVencedor();
    void Inserir(dado d);
};


Torneio::Torneio(dado vet[], int tam) {
    capacidade = 1;
    while (capacidade < tam) {
        capacidade *= 2;
    }
    capacidade = capacidade - 1 + tam;

    Heap = new dado[capacidade];
    InicioDados = capacidade - tam;


    memcpy(&Heap[InicioDados], vet, tam * sizeof(dado));

    Tamanho = tam;
    Arruma();

    /*
    for(int i = 0; i<tam; i++){   // for de copia  "memcpy" faz a cpia mais eficientemente
      Heap[i] = vet[i];
    }
    */
}

Torneio::~Torneio() {
    delete[] Heap;
}

void Torneio::Arruma() {
    // Aplica recebe maior na primeira metade dos elementos
    //cout << "arruma" << InicioDados -1 << endl;
    const float D = 2.0;
    int n = ceil(Tamanho / D);
    int cont = 0;

    bool oMaior = true;

    for (int i = InicioDados - 1; i >= 0; i--) {
        if (i < (n - 1)) {
            n = ceil(n / D);
            cont++;
        }
        if (cont % 2 == 0) {
            Copia(oMaior, i);
        } else {
            Copia(not(oMaior), i);
        }
    }
}

int Torneio::Pai(int i) {  // mtodo que retorna o pai
    return (i - 1) / 2;

}

int Torneio::Esquerdo(int i) {   // mtodo que retorna esquerdo
    return 2 * i + 1;
}

int Torneio::Direito(int i) {    // mtodo que retorna o direito
    return 2 * i + 2;
}

void Torneio::Copia(bool copiaOMaior, int i) {   // mtodo CorrigeDescendo
    int esq = Esquerdo(i);
    int dir = Direito(i);
    int maior = INVALIDO;
    int menor = INVALIDO;

    if (esq < capacidade) {
        if (copiaOMaior) {
            if (dir < capacidade and Heap[dir] > Heap[esq]) {
                maior = dir;
            } else {
                maior = esq;
            }
            Heap[i] = Heap[maior];
        } else {
            if (Heap[dir] >= 0 and dir < capacidade and Heap[dir] < Heap[esq]) {
                menor = dir;
            } else {
                menor = esq;
            }
            Heap[i] = Heap[menor];
        }
    } else {
        Heap[i] = INVALIDO;
    }

}

void Torneio::CopiaSubindo(int i) {    // método corrige subindo
    int p = Pai(i);
    if (Heap[i] > Heap[p]) {
        Heap[p] = Heap[i];
        CopiaSubindo(p);
    }
}

void Torneio::Inserir(dado d) {
    if (Tamanho == capacidade) {
        cerr << "Erro ao inserir" << endl;
        exit(EXIT_FAILURE);
    }
    Heap[Tamanho + InicioDados] = d;
    CopiaSubindo(Tamanho + InicioDados);
    Tamanho++;
}

int Torneio::retornaVencedor() {
    return Heap[0];
}

int main() {

    int tam;
    cin >> tam;
    dado vet1[tam];

    for (int i = 0; i < tam; i++) {
        cin >> vet1[i];
    }

    Torneio torneio(vet1, tam);



    cout << torneio.retornaVencedor() << endl;
    return 0;

}