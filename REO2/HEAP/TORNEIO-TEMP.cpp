#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

const int INVALIDO = -1;

struct elemento {
    int valorSub;
    int valorBase;
};

typedef elemento dado;

class Torneio {
private:
    dado* Heap;
    int Capacidade;
    int Tamanho;
    int InicioDados; // Prineiro n� folha
    inline int Pai(int i);
    inline int Esquerdo(int i);
    inline int Direito(int i);
    void Arruma();    // heapify (constroi o heap e arruma com corrige descendo da metade pra cima)   // auxiliar
    void CopiaMaior(int i);  // auxiliar
    void CopiaSubindo(int i);   // auxiliar
    dado aux;
public:
    Torneio(dado vet[], int tam);   // construtor com tamanho
    ~Torneio();
    void Imprimir();    // Imprimir o vetor do heap "ESSA � APENAS DID�TICA"
    dado RetiraRaiz();
    void Inserir(dado d);
};


Torneio::Torneio(dado vet[], int tam) {

    Capacidade = 1;
    while (Capacidade < tam) {
        Capacidade *= 2;
    }
    //cout << endl << "Capacidade aqui: " << Capacidade << endl;
    Capacidade = (Capacidade - 1) + Capacidade;
    Heap = new dado[Capacidade];
    for (int i = 0; i < Capacidade; i++) {
        Heap[i].valorBase = INVALIDO;
        Heap[i].valorSub = INVALIDO;
    }
    InicioDados = (Capacidade) / 2;

    //cout << "InicioDados: " << InicioDados << endl;
    //cout << "capacidade: " << Capacidade << endl;
    int iniAux = InicioDados;
    for (int i = 0; i < tam; i++) {
        int val;
        cin >> val;
        Heap[iniAux].valorBase = val;
        Heap[iniAux].valorSub = val;
        iniAux++;
    }
    //memcpy(&Heap[InicioDados], vet, tam * sizeof(dado));

    Tamanho = tam;
    Arruma();

    /*
    for(int i = 0; i<tam; i++){   // for de copia  "memcpy" faz a c�pia mais eficientemente
      Heap[i] = vet[i];
    }
    */
}

Torneio::~Torneio() {
    delete[] Heap;
}

void Torneio::Arruma() {
    // Aplica recebe maior na primeira metade dos elementos
    //cout << "arruma" << InicioDados - 1 << endl;
    for (int i = InicioDados - 1; i >= 0; i--) {
        CopiaMaior(i);
    }
}

int Torneio::Pai(int i) {  // m�todo que retorna o pai
    return (i - 1) / 2;

}

int Torneio::Esquerdo(int i) {   // m�todo que retorna esquerdo
    return 2 * i + 1;
}

int Torneio::Direito(int i) {    // m�todo que retorna o direito
    return 2 * i + 2;
}

void Torneio::CopiaMaior(int i) {   // m�todo CorrigeDescendo
    int esq = Esquerdo(i);
    int dir = Direito(i);
    int maior = INVALIDO;
    //cout << " i: " << i << " e: " << esq << " d: " << dir << endl;
    if (esq < Capacidade) {
        int subtracao;
        if (Heap[dir].valorSub == INVALIDO and Heap[esq].valorSub == INVALIDO) {
            Heap[i].valorBase = INVALIDO;
            Heap[i].valorSub = INVALIDO;
        } else if (Heap[dir].valorSub == INVALIDO) {
            Heap[i] = Heap[esq];
        } else if (Heap[esq].valorSub == INVALIDO) {
            Heap[i] = Heap[dir];
        } else {
            if ((dir < Capacidade) and (Heap[dir].valorSub > Heap[esq].valorSub)) {    // verifica o tamanho primeiro pra n�o acessar mem�ria indevida
                subtracao = Heap[dir].valorSub - Heap[esq].valorSub;
                maior = dir;
            } else {
                for (int i =0; i < Capacidade; i++) {
                    cout << Heap[i].valorSub << " ";
                }
                cout << endl;
                subtracao = Heap[esq].valorSub - Heap[dir].valorSub;
                maior = esq;
            }
            Heap[i] = Heap[maior];
            Heap[i].valorSub = subtracao;
        }
    } else {
        Heap[i].valorSub = INVALIDO;
    }

}

void Torneio::CopiaSubindo(int i) {    // m�todo corrige subindo
    int p = Pai(i);
    if (Heap[i].valorSub > Heap[p].valorSub) {
        Heap[p] = Heap[i];
        CopiaSubindo(p);
    }
}

/*
dado Torneio::EspiaRaiz(){
  return Heap[0];
}
*/

/*
dado Torneio::RetiraRaiz(){
  if( Tamanho == 0 ){
    cerr << "Erro ao retirar raiz" << endl;
    exit( EXIT_FAILURE);
  }
  dado aux = Heap[0];
  swap(Heap[0], Heap[Tamanho-1]);
  Tamanho--;    // tem que decrementar o tamanho para que a corrige descendo n�o mecha onde vc acabou de inserir
  CorrigeDescendo(0);
  return aux;
}
*/

void Torneio::Imprimir() {
    cout << Heap[0].valorBase << endl;
}

void Torneio::Inserir(dado d) {
    if (Tamanho == Capacidade) {
        cerr << "Erro ao inserir" << endl;
        exit(EXIT_FAILURE);
    }
    Heap[Tamanho + InicioDados] = d;
    CopiaSubindo(Tamanho + InicioDados);
    Tamanho++;
}

int main() {

    int tam;
    cin >> tam;
    dado vet1[tam];
    Torneio torneio(vet1, tam);
    torneio.Imprimir();


    return 0;

}