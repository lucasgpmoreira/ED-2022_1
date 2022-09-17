#include <iostream>

using namespace std;

const int CAPACIDADE = 23;

struct dado {
    string palavra;
    string significado;
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
    dado retorno = { "NAOENCONTRADO", "" };
    noh* aux = inicio;
    if (inicio == NULL)
        return retorno;
    while (aux != NULL) {
        if (aux->Dado.palavra == valor) {
            return aux->Dado;
        }
        aux = aux->proximo;
    }
    if (aux == NULL)
        return retorno;
    return retorno;
}

class Hash {
private:
    int capacidade;
    lista* tabela;
    int calculaHash(string chave);
    int tamanho;
    void redimensiona();
public:
    Hash();
    ~Hash();
    void insereELemento(dado d);
    string buscaElemento(string chave);
    void remove(int chave);
    void imprime();

};

Hash::Hash() {
    capacidade = CAPACIDADE;
    tabela = new lista[capacidade];
    tamanho = 0;
}

Hash::~Hash() {
    delete tabela;
}

int Hash::calculaHash(string chave) {
    return chave.size() % capacidade;
}

void Hash::insereELemento(dado d) {
    int pos = calculaHash(d.palavra);
    if (tabela[pos].busca(d.palavra).palavra == "NAOENCONTRADO") {
        tabela[pos].adicionaAoFim(d);
        tamanho++;
    } else {
        //throw runtime_error("item ja esta na tabela");
    }
}

string Hash::buscaElemento(string chave) {
    int pos = calculaHash(chave);
    dado elem = tabela[pos].busca(chave);
    if (elem.palavra == "NAOENCONTRADO") {
        return " NULL";
    }
    return elem.significado;
}

int main() {
    string palavra;
    Hash tabela;
    dado d;
    int qtd;
    cin >> qtd;
    for (int i = 0; i < qtd; i++) {
        cin >> d.palavra;
        getline(cin, d.significado);
        tabela.insereELemento(d);
    }
    do {
        cin >> palavra;
        if (palavra != "-1") {
            cout << "[" << palavra << "] =>" <<
            tabela.buscaElemento(palavra) << endl;
        }
    } while (palavra != "-1");
    return 0;
}