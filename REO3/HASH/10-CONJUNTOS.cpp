#include<iostream>

using namespace std;

const int TAMANHOARRANJO = 101;
const int INVALIDO = -1;
const int POSINVALIDA = -1;
const int REMOVIDO = -2;

typedef int dado;

class hashEA {
private:
    unsigned posicao(const int& chave);
    dado* vetDados;
    int capacidade;
    int tam;
    int buscaChave(const int& chave);
public:
    hashEA();
    ~hashEA();
    void imprime();
    void adiciona(int valor);
    void remove(const int& chave);
    int membro(const int& chave);
    int tamanho();
};


hashEA::hashEA() {
    // ** implementar! **
    // => não se esqueça de marcar os dados em cada posição da tabela como inválidos
    capacidade = TAMANHOARRANJO;
    vetDados = new dado[TAMANHOARRANJO];
    for (int i = 0; i < TAMANHOARRANJO; i++) {
        vetDados[i] = INVALIDO;
    }
    tam = 0;
}

hashEA::~hashEA() {
    delete[] vetDados;
}

unsigned hashEA::posicao(const int& chave) {
    return chave % TAMANHOARRANJO;
}

int hashEA::buscaChave(const int& chave) {
    int pos = posicao(chave);
    int posFinal = pos;
    dado umDado;
    do {
        umDado = vetDados[pos];
        if (umDado == INVALIDO) {
            return POSINVALIDA;
        } else if (umDado == chave) {
            return pos;
        }
        pos = (pos + 1) % capacidade;
    } while (pos != posFinal);
    return -1;
}

int hashEA::membro(const int& chave) {
    // ** implementar! **
        // Retorna a posicao em que uma chave está armazenada na estrutura
        // Retorna POSINVALIDA quando chave não está na tabela hash
    int pos = posicao(chave);
    int posFinal = pos;
    dado umDado;
    do {
        umDado = vetDados[pos];
        if (umDado == INVALIDO) {
            return POSINVALIDA;
        } else if (umDado == chave) {
            return 1;
        }
        pos = (pos + 1) % capacidade;
    } while (pos != posFinal);
    return -1;

}

void hashEA::adiciona(int valor) {
    if (capacidade == tam) {
        return; //tabela cheia
    }
    if (membro(valor) != POSINVALIDA) {
        return; //item já está na tabela
    }
    int pos = posicao(valor);
    while (vetDados[pos] != INVALIDO and vetDados[pos] != REMOVIDO) {
        pos = (pos + 1) % capacidade;
    }
    vetDados[pos] = valor;
    tam++;
}

void hashEA::remove(const int& chave) {
    // ** implementar! **
        // Remove um dado com determinada chave da tabela hash
    if (tam == 0) {
        return; //remoçao lista vazia
    }
    int pos = buscaChave(chave);
    if (pos == POSINVALIDA) {
        return; //chave não encontrada
    }
    vetDados[pos] = REMOVIDO;
    tam--;
}

void hashEA::imprime() {
    for (int i = 0; i < TAMANHOARRANJO; i++) {
        if (vetDados[i] != INVALIDO and vetDados[i] != REMOVIDO and vetDados[i] != POSINVALIDA) {
            cout << vetDados[i] << " ";
        }
    }
    cout << endl;
}

int hashEA::tamanho() {
    return tam;
}

int main() {
    hashEA tabela;
    int elem;
    for (int i = 0; i < 10; i++) {
        cin >> elem;
        tabela.adiciona(elem);
    }
    for (int i = 0; i < 3; i++) {
        cin >> elem;
        tabela.remove(elem);
    }
    for (int i = 0; i < 2; i++) {
        cin >> elem;
        cout << tabela.membro(elem) << endl;
    }

    tabela.imprime();

    for (int i = 0; i < 3; i++) {
        cin >> elem;
        tabela.adiciona(elem);
    }

    tabela.imprime();
    return 0;
}