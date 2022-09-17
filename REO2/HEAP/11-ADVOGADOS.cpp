#include <iostream>   // Pode usar varias coisas prontas
#include <vector>     // mas e' preciso completar a classe
#include <limits>     // classe Heap. E' permitido fazer
#include <string>     // alteracoes na classe Heap.
#include <stdexcept>
#include <cstdlib> 

using namespace std;

struct Processo {
    int id;
    int prioridade;
};


class Heap {
    // classe Heap (max-heap, o maior fica na raiz/inicio)
public:
    // Criar heap sem dados e com capacidade informada
    Heap(int cap);
    // Destruttor
    ~Heap();
    // Inserir um dado na heap
    bool Inserir(Processo processo);
    // Retira e retorna a raiz
    bool Retira(Processo& processo);
    // Verifica se a heap está vazia
    bool Vazia();
private:
    void corrigeDescendo(int i);
    void corrigeSubindo(int i);
    int Direito(int i);
    int Esquerdo(int i);
    int Pai(int i);

    int capacidade;
    int tamanho;
    Processo* dados;
};

using namespace std;

Heap::Heap(int cap) {
    // Criar heap sem dados e com capacidade informada
    capacidade = cap;
    tamanho = 0;
    dados = new Processo[capacidade];
}

Heap::~Heap() {
    // Destrutor
    delete[] dados;
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

bool Heap::Retira(Processo& processo) {
    // Retira um codigo/prioridade, retornando os dois valores.
    // Retorna falso se o heap estiver vazio.
    if (tamanho == 0) {
        return false;
    }
    processo = dados[0];
    swap(dados[0], dados[tamanho - 1]);
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

bool Heap::Inserir(Processo processo) {
    // Insere um codigo/prioridade no heap.
    // Retorna falso se o heap estiver cheio.
    if (tamanho == capacidade) {
        throw runtime_error("Heap cheio");
        abort();
    }
    dados[tamanho] = processo;
    corrigeSubindo(tamanho);
    tamanho++;
    return true;
}

void Heap::corrigeSubindo(int i) {
    // Corrige a posicao i para cima.
    int pai = Pai(i);
    if (pai >= 0 and dados[pai].prioridade < dados[i].prioridade) {
        swap(dados[pai], dados[i]);
        corrigeSubindo(pai);
    }
}

void Heap::corrigeDescendo(int i) {
    // Corrige a posicao i para baixo.
    int esquerdo = Esquerdo(i);
    int direito = Direito(i);
    int maior = i;
    if (esquerdo < tamanho and dados[esquerdo].prioridade > dados[i].prioridade) {
        maior = esquerdo;
    }
    if (direito < tamanho and dados[direito].prioridade > dados[maior].prioridade) {
        maior = direito;
    }
    if (maior != i) {
        swap(dados[i], dados[maior]);
        corrigeDescendo(maior);
    }
}

int main() {
    unsigned capacidade;
    cin >> capacidade;
    Heap heap(capacidade);
    char comando;
    do {
        cin >> comando;
        switch (comando) {
        case 'i': // inserir um processo no heap
            Processo processo;
            cin >> processo.id >> processo.prioridade;
            heap.Inserir(processo);
            break;
        case 'o': // obter um processo do heap
            Processo processoAuxSaida;
            if (heap.Retira(processoAuxSaida))
                cout << processoAuxSaida.id << ' ' << processoAuxSaida.prioridade << endl;
            else
                cout << "Nao encontrado" << endl;
            break;
        case 's': //sair
            break;
        }
    } while (comando != 's');
    return 0;
}
