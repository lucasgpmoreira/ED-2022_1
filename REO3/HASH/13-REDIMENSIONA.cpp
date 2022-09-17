#include <iostream>
#include <string>

using namespace std;

const int PORCENTAGEM = 90;

struct dado {
    string valor;
    int  chave;
};

struct noh {
    dado Dado;
    noh* proximo;
    noh(dado d) {
        Dado = d;
        proximo = NULL;
    }
};

class lista {
private:
    noh* inicio;
    int tam;
public:
    lista();
    void adicionaAoFim(dado d);
    dado busca(string valor);
    dado busca(int chave);
    bool remove(int chave);
    dado removeNoInicio();
    int retornaTamaho();
    void imprime(int i);
};

lista::lista() {
    inicio = NULL;
    tam = 0;
}

void lista::adicionaAoFim(dado d) {
    noh* novo = new noh(d);
    if (inicio == NULL) {
        inicio = novo;
    } else {
        noh* atual = inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }
    tam++;
}

dado lista::busca(string valor) {
    dado retorno = { "NAOENCONTRADO", 0 };
    noh* aux = inicio;
    if (inicio == NULL)
        return retorno;
    while (aux->proximo != NULL) {
        if (aux->Dado.valor == valor) {
            return aux->Dado;
        }
        aux = aux->proximo;
    }
    if (aux == NULL)
        return retorno;
    return retorno;
}

dado lista::busca(int chave) {
    dado retorno = { "NAOENCONTRADO", 0 };
    noh* aux = inicio;
    if (inicio == NULL)
        throw "ERRO";
    while (aux->proximo != NULL) {
        if (aux->Dado.chave == chave) {
            return aux->Dado;
        }
        aux = aux->proximo;
    }
    if (aux == NULL)
        throw "ERRO";
    return retorno;
}

bool lista::remove(int chave) {
    noh* aux = inicio;
    noh* ante;
    while (aux != NULL and aux->Dado.chave != chave) {
        ante = aux;
        aux = aux->proximo;
    }
    if (aux == NULL) {
        return false;
    }
    if (aux == inicio) {
        noh* auxIni = inicio;
        inicio = auxIni->proximo;
        delete auxIni;
    } else if (aux->proximo == NULL) {
        noh* auxFim = aux;
        ante->proximo = NULL;
        delete auxFim;
    } else {
        ante->proximo = aux->proximo;
        delete aux;
    }
    tam--;
    return true;
}

dado lista::removeNoInicio() {
    noh* aux = inicio;
    if (aux == NULL)
        exit(1);
    dado retorno = aux->Dado;
    inicio = aux->proximo;
    delete aux;
    tam--;
    return retorno;
}

int lista::retornaTamaho() {
    return tam;
}

void lista::imprime(int i) {
    cout << "Posicao " << i << ": ";
    noh* aux = inicio;
    if (aux != NULL) {
        cout << aux->Dado.chave << " " << aux->Dado.valor;
        if (aux->proximo != NULL)
            cout << "\nLista de colisao: ";
        while (aux != NULL) {
            aux = aux->proximo;
            if (aux != NULL) {
                cout << aux->Dado.chave << " " << aux->Dado.valor;
                if (aux->proximo != NULL)
                    cout << ", ";
            }
        }

    }
    cout << endl;
}

class Hash {
private:
    int capacidade;
    lista* tabela;
    int calculaHash(int chave);
    int tamanho;
    void redimensiona();
public:
    Hash(int c);
    ~Hash();
    void insereELemento(dado d);
    string buscaElemento(int chave);
    void remove(int chave);
    void imprime();

};

Hash::Hash(int c) {
    capacidade = c;
    tabela = new lista[capacidade];
    tamanho = 0;
}

Hash::~Hash() {
    delete tabela;
}

int Hash::calculaHash(int chave) {
    return chave % capacidade;
}

void Hash::redimensiona() {
    int capacidadeAnt = capacidade;
    capacidade *= 2;
    lista* tabelaAux = new lista[capacidade];
    for (int i = 0; i < capacidadeAnt; i++) {
        for (int j = tabela[i].retornaTamaho(); j > 0; j--) {
            dado removido = tabela[i].removeNoInicio();
            int novaPos = calculaHash(removido.chave);
            tabelaAux[novaPos].adicionaAoFim(removido);
        }
    }
    delete tabela;
    tabela = tabelaAux;
}

void Hash::insereELemento(dado d) {
    if ((tamanho * 100) / (capacidade) > PORCENTAGEM) {
        redimensiona();
    } else {
        int pos = calculaHash(d.chave);
        if (tabela[pos].busca(d.valor).valor == "NAOENCONTRADO") {
            tabela[pos].adicionaAoFim(d);
            tamanho++;
        } else {
            //throw runtime_error("item ja esta na tabela");
        }
    }
}

string Hash::buscaElemento(int chave) {
    int pos = calculaHash(chave);
    dado elem = tabela[pos].busca(chave);
    if (elem.chave == -1) {
        return "ERRO";
    }
    return elem.valor;
}

void Hash::remove(int chave) {
    int pos = calculaHash(chave);
    if (tabela[pos].remove(chave)) {
        tamanho--;
    } else {
        cout << "ERRO" << endl;
    }

}

void Hash::imprime() {
    for (int i = 0; i < capacidade; i++) {
        tabela[i].imprime(i);
    }
    cout << "-----------------------" << endl;
}

int main() {
    dado dadoAux;
    int cap, chave;
    cin >> cap;
    Hash hash(cap);
    char op;
    do {
        cin >> op;
        switch (op) {
        case 'I':
            cin >> dadoAux.chave >> dadoAux.valor;
            hash.insereELemento(dadoAux);
            break;
        case 'R':
            cin >> chave;
            hash.remove(chave);
            break;
        case 'B':
            cin >> chave;
            cout << hash.buscaElemento(chave);
            break;
        case 'P':
            hash.imprime();
            break;

        }
    } while (op != 'S');

    return 0;
}