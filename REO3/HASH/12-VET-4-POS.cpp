#include <iostream>
#include <typeinfo>

using namespace std;

const int TAMANHOARRANJO = 4;

struct reg {
    string valor;
    int chave;
    int tamanho;
    reg() {
        tamanho = 0;
        valor = "";
        chave = -1;
    }
};

typedef struct reg dado;

class HashArr {
private:
    dado** array;
    int tam;
    int calculaHash(int chave) { chave% tam; };
public:
    HashArr(int tamanho);
    bool insere(dado d);
    string busca(int chave);
    void imprime();
    ~HashArr();
};

HashArr::HashArr(int tamanho) {
    tam = tamanho;
    array = new dado * [tamanho];
    for (int i = 0; i < tamanho; i++) {
        array[i] = new dado[TAMANHOARRANJO];
    }

    //percorre a matriz dando cout
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < TAMANHOARRANJO; j++) {
            cout << "[" << array[i][j].chave << "/" << array[i][j].valor << "] ";
        }
        cout << endl;
    }
}

HashArr::~HashArr() {
    //percorre matriz deletando
    for (int i = 0; i < tam; i++) {
        delete[] array[i];
    }
    delete[] array;
}

bool HashArr::insere(dado d) {
    int pos = calculaHash(d.chave);
    int i = 0;
    while (array[pos][i].chave != -1 and i < TAMANHOARRANJO) {
        i++;
    }
    if (i == TAMANHOARRANJO) {
        return false;
    } else {
        array[pos][i] = d;
    }
    return true;
}

string  HashArr::busca(int chave) {
    int pos = calculaHash(chave);
    int i = 0;
    while (array[pos][i].chave != chave and i < TAMANHOARRANJO) {
        i++;
    }
    if (i == TAMANHOARRANJO) {
        return "NAOENCONTRADO";
    } else {
        return array[pos][i].valor;
    }
}

void HashArr::imprime() {
    //percorre a matriz dando cout
    for (int i = 0; i < tam; i++) {
        cout << i << ": ";
        for (int j = 0; j < TAMANHOARRANJO; j++) {
            cout << "[" << array[i][j].chave << "/" << array[i][j].valor << "] ";
        }
        cout << endl;
    }
}

int main() {
    int tam, qtd;
    cin >> tam >> qtd;
    HashArr hash(tam);
    for (int i = 0; i < qtd; i++) {
        int chave, valor;
        dado dadoAux;
        cin >> dadoAux.chave;
        cin >> dadoAux.valor;
        if(!(hash.insere(dadoAux))) {
            cout << "NÚMERO MÁXIMO DE COLISÕES PARA CHAVE!" << endl;
        }
    }

    for(int i = 0; i < 4; i++) {
        int chave;
        cin >> chave;
        cout << hash.busca(chave) << endl;
    }

    return 0;
}