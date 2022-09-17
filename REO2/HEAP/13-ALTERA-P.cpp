#include <iostream>   // Pode usar varias coisas prontas
#include <vector>     // mas e' preciso completar a classe
#include <limits>     // classe Heap. E' permitido fazer
#include <string>     // alteracoes na classe Heap.
#include <stdexcept>
#include <cstdlib> 

using namespace std;

struct Dado {
    int id;
    int prioridade;
};

bool operator>(Dado d1, Dado d2) {
    return d1.prioridade > d2.prioridade;
}

bool operator<(Dado d1, Dado d2) {
    return d1.prioridade < d2.prioridade;
}

ostream& operator<<(ostream& output, const Dado& d) {
    output << "[" << d.id << "/" << d.prioridade << "]";
    return output;
}


class Heap {
    // classe Heap (max-heap, o maior fica na raiz/inicio)
public:
    // Criar heap sem Dados e com capacidade informada
    Heap(int cap);
    // Destruttor
    ~Heap();
    // Inserir um Dado na heap
    bool Inserir(Dado Dado);
    // Retira e retorna a raiz
    bool Retira(Dado& Dado);
    // Verifica se a heap está vazia
    void alteraPrioridade(Dado Dado);
    bool Vazia();
    void imprime();
private:
    void corrigeDescendo(int i);
    void corrigeSubindo(int i);
    int Direito(int i);
    int Esquerdo(int i);
    int Pai(int i);
    void heapify();
    int capacidade;
    int tamanho;
    Dado* Dados;
};

Heap::Heap(int cap) {
    // Criar heap sem Dados e com capacidade informada
    capacidade = cap;
    tamanho = 0;
    Dados = new Dado[capacidade];
}

Heap::~Heap() {
    // Destrutor
    delete[] Dados;
}

int Heap::Pai(int i) {
    // Retorna o indice do pai de i.
    return (i - 1) / 2;
}

int Heap::Esquerdo(int i) {
    // Retorna o indice do filho a esquerda de i.
    return 2 * i + 1;
}

int Heap::Direito(int i) {
    // Retorna o indice do filho a direita de i.
    return 2 * i + 2;
}

bool Heap::Retira(Dado& Dado) {
    // Retira um codigo/prioridade, retornando os dois valores.
    // Retorna falso se o heap estiver vazio.
    if (tamanho == 0) {
        return false;
    }
    Dado = Dados[0];
    swap(Dados[0], Dados[tamanho - 1]);
    tamanho--;
    corrigeDescendo(0);
    return true;
}

bool Heap::Vazia() {
    //Verifica se o heap está vazio.
    bool retorno = true;
    if (tamanho > 0) {
        retorno = false;
    }
    return retorno;
}

bool Heap::Inserir(Dado Dado) {
    // Insere um codigo/prioridade no heap.
    // Retorna falso se o heap estiver cheio.
    if (tamanho == capacidade) {
        throw runtime_error("Heap cheio");
        abort();
    }
    Dados[tamanho] = Dado;
    corrigeSubindo(tamanho);
    tamanho++;
    return true;
}

void Heap::corrigeSubindo(int i) {
    // Corrige a posicao i para cima.
    int pai = Pai(i);
    if (pai >= 0 and Dados[pai].prioridade < Dados[i].prioridade) {
        swap(Dados[pai], Dados[i]);
        corrigeSubindo(pai);
    }
}

void Heap::corrigeDescendo(int i) {
    // Corrige a posicao i para baixo.
    int esquerdo = Esquerdo(i);
    int direito = Direito(i);
    int maior = i;
    if (esquerdo < tamanho and Dados[esquerdo].prioridade > Dados[i].prioridade) {
        maior = esquerdo;
    }
    if (direito < tamanho and Dados[direito].prioridade > Dados[maior].prioridade) {
        maior = direito;
    }
    if (maior != i) {
        swap(Dados[i], Dados[maior]);
        corrigeDescendo(maior);
    }
}

void Heap::heapify() {
    // Corrige a posicao i para baixo.
    for (int i = tamanho / 2 - 1; i >= 0; i--) {
        corrigeDescendo(i);
    }
}

void Heap::imprime() {
    // Imprime o heap.
    for (int i = 0; i < tamanho; i++) {
        cout << Dados[i] << " ";
    }
    cout << endl;
}

void Heap::alteraPrioridade(Dado Dado) {
    // Altera a prioridade de um codigo.
    // Retorna falso se o codigo nao estiver no heap.
    for (int i = 0; i < tamanho; i++) {
        if (Dados[i].id == Dado.id) {
            Dados[i].prioridade = Dado.prioridade;
        }
    }
    heapify();
}

int main() {
    /*
    I seguido de um valor e uma prioridade (ambos inteiros) - insere um Dado no heap
    R retira um elemento da raiz, imprimindo seu valor
    A altera a prioridade de um elemento com um Dado valor
    P imprime os Dados válidos do heap, para depuração
    Q encerra a aplicação
    */
    int capacidade;
    cin >> capacidade;
    Heap meuHeap(capacidade);

    char opcao;
    cin >> opcao;

    while (opcao != 'Q') {
        switch (opcao) {
        case 'I':
            Dado dado;
            cin >> dado.id;
            cin >> dado.prioridade;
            meuHeap.Inserir(dado);
            break;
        case 'R':
            Dado dadoRetirado;
            if (meuHeap.Retira(dadoRetirado)) {
                cout << dadoRetirado.id << endl;
            } else {
                cout << "Heap vazio" << endl;
            }
            break;
        case 'A':
            Dado DadoAltera;
            cin >> DadoAltera.id;
            cin >> DadoAltera.prioridade;
            meuHeap.alteraPrioridade(DadoAltera);
            break;
        case 'P':
            meuHeap.imprime();
            break;
        default:
            cout << "Opção inválida!" << endl;
        }
        cin >> opcao;
    }

}
