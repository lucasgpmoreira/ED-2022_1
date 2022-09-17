#include <iostream>
#include <cstdlib>
using namespace std;

//----------------------------------------------------------------------------------------------------------------------

struct Passageiro {
    int assento;
    string cpf;
    string nome;
    string telefone;
};

struct listaDeEspera {
    Passageiro passageiro;
    listaDeEspera* proximo;
    listaDeEspera(Passageiro p);
};

listaDeEspera::listaDeEspera(Passageiro p) {
    passageiro = p;
    proximo = NULL;
}


typedef Passageiro Dado;

//----------------------------------------------------------------------------------------------------------------------

class noh {
    friend class lista;
private:
    int tamListaDeEspera;
    listaDeEspera* inicio;
    Dado dado;
    noh* proximo;
public:
    noh(Dado d);
};

noh::noh(Dado d) : dado(d), tamListaDeEspera(0) {
    proximo = NULL;
    inicio = NULL;
}

//---------------------------------------------------------------------------------------------------------------------
class lista {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista
    bool elementoExiste(int assento);
    void adicionaAListaDeEspera(Dado dado);
    Dado removeDoFimDaListaDeEspera(noh* posicao, string cpf);
    void removeDaListaDePassageiros(string cpf);
    Dado removeDoInicio();
    void removeDoFim();
public:
    // construtores e destrutor
    lista();
    lista(const lista& umalista);   // construtor de copia
    ~lista();
    void inserePassageiro(Dado dado);
    void imprime();
    bool vazia();
    void cancelaPassageiro(string CPF);
    int checaReservas(int assento);
    int retornaTamanho();
};

lista::lista() {
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

lista::~lista() {
    noh* aux = primeiro;
    while (aux != NULL) {
        noh* aux2 = aux->proximo;
        delete aux;
        aux = aux2;
    }
}


bool lista::elementoExiste(int assento) {
    noh* aux = primeiro;
    while (aux != NULL) {
        if (aux->dado.assento == assento) {
            return true;
        }
        aux = aux->proximo;
    }
    return false;
}

void lista::adicionaAListaDeEspera(Dado dado) {
    noh* aux = primeiro;
    bool elemEncontrado = false;
    while (aux != NULL and not(elemEncontrado)) {
        if (aux->dado.assento == dado.assento) {
            elemEncontrado = true;
        } else {
            aux = aux->proximo;
        }
    }
    if (aux != NULL) {
        listaDeEspera* novo = new listaDeEspera(dado);
        if (aux->tamListaDeEspera <= 0) {
            novo->proximo = NULL;
            aux->inicio = novo;
        } else {
            listaDeEspera* aux2 = aux->inicio;
            while (aux2->proximo != NULL) {
                aux2 = aux2->proximo;
            }
            aux2->proximo = novo;
            novo->proximo = NULL;
        }
        aux->tamListaDeEspera++;
    }

}

Dado lista::removeDoFimDaListaDeEspera(noh* posicao, string cpf) {
    Dado retorno;
    listaDeEspera* aux = posicao->inicio;
    listaDeEspera* ante;
    while (aux != NULL) {
        ante = aux;
        aux = aux->proximo;
    }
    retorno = ante->passageiro;
    ante->proximo = NULL;
    delete aux;
    posicao->tamListaDeEspera--;
    if (posicao->tamListaDeEspera == 0) {
        posicao->inicio = NULL;
    }
    return retorno;
}

void lista::inserePassageiro(Dado dado) {
    if (not(elementoExiste(dado.assento))) {
        noh* novo = new noh(dado);
        if (vazia()) {
            primeiro = novo;
            ultimo = novo;
        } else {
            ultimo->proximo = novo;
            ultimo = novo;
        }
        tamanho++;
    } else {
        adicionaAListaDeEspera(dado);
    }
}

void lista::removeDoFim() {
    if (vazia()) { // verifica lista vazia
        cerr << "Remocao em lista vazia" << endl;
        exit(EXIT_FAILURE);
    }
    noh* aux = primeiro;
    noh* anterior;
    while (aux->proximo != NULL) {  // Aux para no ULTIMO
        anterior = aux;
        aux = aux->proximo;
    }
    delete ultimo;  // apagou aquele que aux aponta
    anterior->proximo = NULL;
    ultimo = anterior;
    if (vazia()) {  // Verifica se a lista ficou vazia com isso
        primeiro = NULL;
    }
    tamanho--;
}

Dado lista::removeDoInicio() {
    Dado retorno;
    if (vazia()) { // verifica lista vazia
        cerr << "Remocao em lista vazia" << endl;
        exit(EXIT_FAILURE);
    }
    noh* removido = primeiro;
    primeiro = primeiro->proximo;
    retorno = removido->dado;
    delete removido;
    tamanho--;
    // se a lista ficou vazia
    if (tamanho == 0) {
        ultimo = NULL;
    }
    return retorno;
}

void lista::removeDaListaDePassageiros(string cpf) {
    // Percorre a lista de passageiros e remove o passageiro com o CPF informado
    noh* aux = primeiro;
    noh* anterior;
    while (aux != NULL and aux->dado.cpf != cpf) {
        anterior = aux;
        aux = aux->proximo;
    }

    if (aux != NULL) {
        if (aux == primeiro) {
            removeDoInicio();
        } else if (aux == ultimo) {
            removeDoFim();
        } else {
            anterior->proximo = aux->proximo;
            delete aux;
            tamanho--;
        }
    }
}

void lista::cancelaPassageiro(string CPF) {
    noh* aux = primeiro;
    noh* temp;
    bool elemEncontrado = false;
    while (aux != NULL and not(elemEncontrado)) {
        if (aux->dado.cpf == CPF) {
            elemEncontrado = true;
        } else {
            listaDeEspera* aux2 = aux->inicio;
            while (aux2 != NULL and not(elemEncontrado)) {
                if (aux2->passageiro.cpf == CPF) {
                    elemEncontrado = true;
                } else {
                    aux2 = aux2->proximo;
                }
            }
        }
        if (not(elemEncontrado)) {
            aux = aux->proximo;
        }
    }
    if (aux != NULL) {
        if (aux->tamListaDeEspera <= 0) {
            removeDaListaDePassageiros(CPF);
        } else {
            aux->dado = removeDoFimDaListaDeEspera(aux, CPF);
        }
    }
}

int lista::checaReservas(int assento) {
    noh* aux = primeiro;
    int retorno = -1;
    bool elemEncontrado = false;
    while (aux != NULL and not(elemEncontrado)) {
        if (aux->dado.assento == assento) {
            elemEncontrado = true;
            retorno = aux->tamListaDeEspera;
        } else {
            aux = aux->proximo;
        }
    }
    return retorno;
}

int lista::retornaTamanho() {
    return tamanho;
}

void recebeDados(Passageiro& passageiro) {
    string nome_e_telefone, nomeAux = "", telefAux = "";
    cin >> passageiro.assento;
    cin >> passageiro.cpf;
    getline(cin >> ws, nome_e_telefone); // pega nome e telefone juntos
    int j = 0;
    for (int i = nome_e_telefone.length(); i >= 0; i--) { // separa os dados nome e telefone
        if (j <= 8) {
            telefAux.insert(0, string(1, nome_e_telefone[i])); // pega os 8 últimos números e já os insere em
        } else {                                                     // ordem em telefone auxiliar.
            nomeAux.insert(0, string(1, nome_e_telefone[i])); // insere o resto em nome auxiliar.
        }
        j++;
    }
    passageiro.nome = nomeAux;
    passageiro.telefone = telefAux;
}

bool lista::vazia() {
    return (tamanho == 0);
}

int main() {
    lista listaDeReservas;
    Passageiro passageiro;

    int assentoAux;
    string cpfAux;

    int opcao;
    do {
        cin >> opcao;
        switch (opcao) {
        case 1:
            recebeDados(passageiro);
            listaDeReservas.inserePassageiro(passageiro);
            break;
        case 2:
            cin >> cpfAux;
            listaDeReservas.cancelaPassageiro(cpfAux);
            break;
        case 3:
            cin >> assentoAux;
            int ocupacao = listaDeReservas.checaReservas(assentoAux);
            if (ocupacao == -1) {
                cout << "Disponível" << endl;
            } else {
                cout << "Ocupado - Espera: " << ocupacao << endl;
            }
            break;
        }
    } while (opcao > 0 and opcao < 4);


    return 0;
}

