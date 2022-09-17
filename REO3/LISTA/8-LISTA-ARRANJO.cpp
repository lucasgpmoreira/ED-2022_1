/*
 * Classe listarranjo, uma lista dinamicamente duplamente encadeada em arranjo
 *
 * by Joukim, 2019, Estruturas de Dados
 *
 */

#include <iostream>
#include <stdexcept>

using namespace std;

// para facilitar a troca de int para outro tipo
// estamos criando um apelido para int chamado dado
// - com isso, destaca-se que a lista pode ser uma
// lista de qualquer objeto, não apenas inteiros...
// ou seja: é uma lista de dados
typedef int dado; // typedef permite criar novos tipos a partir de outros
typedef int posicao;

const posicao INVALIDO = -1;
const dado VALOR_PADRAO = -1;

class noh {
    friend class listarranjo;
private:
    dado elemento; // poderia ser outro tipo de variável
    posicao proximo;
    posicao anterior;
    noh() : elemento(VALOR_PADRAO), proximo(INVALIDO), anterior(INVALIDO) {}
};


// lista dinamicamente encadeada
class listarranjo {
private:
    noh* vetorDados; // vetor para armazenamento da lista
    posicao primeiro;
    posicao ultimo;
    unsigned tamanho;
    posicao primeiroApagado;
    unsigned capacidade;
    // "Aloca" para uso, se houver. Retorna a posicao alocada e informa se foi possível alocar.
    bool alocaPosicao(posicao* ptPosAlocada);
public:
    listarranjo(unsigned cap);
    ~listarranjo();
    bool listaVazia() { return tamanho == 0; }
    // inserção, remoção e procura
    bool insereListaVazia(dado d);
    bool insereNoInicio(dado d);
    bool insereNoFim(dado d);
    bool removeNoInicio();
    bool removeNoFim();
    void imprime();
    void depura();
};



// constrói uma lista inicialmente vazia
listarranjo::listarranjo(unsigned cap) {
    capacidade = cap;
    vetorDados = new noh[cap];
    tamanho = 0;
    primeiro = INVALIDO;
    ultimo = INVALIDO;
    primeiroApagado = 0;
    unsigned ult = cap - 1;
    for (unsigned i = 0; i < ult; ++i)
        vetorDados[i].proximo = i + 1;
    vetorDados[ult].proximo = INVALIDO;
    //for (int i = cap - 1; i > 0; --i)
    //    vetorDados[i].anterior = i - 1;
    //vetorDados[0].anterior = INVALIDO;
}

// destrutor da lista
listarranjo::~listarranjo() {
    delete[] vetorDados;
}

// Retorna uma posicao alocada para uso. Retorna tambem um booleano que indica
// se foi possivel fazer a alocacao.
bool listarranjo::alocaPosicao(posicao* ptPosAlocada) {
    if (tamanho == capacidade)
        return false;
    *ptPosAlocada = primeiroApagado;
    primeiroApagado = vetorDados[primeiroApagado].proximo;
    return true;
}

// Insere no início da lista. Retorna um booleano que indica se foi possivel fazer a insercao.
bool listarranjo::insereNoInicio(dado d) {
    posicao posAlocada;
    // verifica se ainda cabe um novo elemento
    if (!alocaPosicao(&posAlocada))
        return false;
    else {
        // se cabe, insere no inicio
        vetorDados[posAlocada].elemento = d;
        vetorDados[posAlocada].proximo = primeiro;
        vetorDados[posAlocada].anterior = INVALIDO;
        if (primeiro != INVALIDO)
            vetorDados[primeiro].anterior = posAlocada;
        primeiro = posAlocada;
        if (ultimo == INVALIDO)
            ultimo = posAlocada;
        tamanho++;
    }
    // se a lista estiver vazia, inserimos o último nó
    // já tem elementos na lista, insere no início
    return true;
}


// Insere no final da lista. Retorna um booleano que indica se foi possivel fazer a insercao.
bool listarranjo::insereNoFim(dado d) {
    posicao posAlocada;
    // verifica se ainda cabe um novo elemento
    if (!alocaPosicao(&posAlocada))
        return false;
    else {
        vetorDados[posAlocada].elemento = d;
        vetorDados[posAlocada].proximo = INVALIDO;
        vetorDados[posAlocada].anterior = ultimo;
        if (primeiro == INVALIDO and ultimo == INVALIDO) {
            primeiro = posAlocada;
            ultimo = posAlocada;
        } else {
            vetorDados[ultimo].proximo = posAlocada;
            ultimo = posAlocada;
        }

        tamanho++;
    }
    return true;
    // se a lista estiver vazia, inserimos o primeiro nó
    // se já tem elementos na lista, insere no final

}

bool listarranjo::removeNoInicio() { //R
    if (listaVazia())
        return false;
    posicao aux = primeiro;
    primeiro = vetorDados[primeiro].proximo;
    if (primeiro != INVALIDO) {
        vetorDados[primeiro].anterior = INVALIDO;
    }
    //vetorDados[aux].elemento = INVALIDO;
    tamanho--;
    if (listaVazia()) {
        ultimo = INVALIDO;
        primeiro = INVALIDO;
    }
    vetorDados[aux].proximo = primeiroApagado;
    primeiroApagado = aux;

    return true;
    // remoção simplesmente marca a posição como inválida
    // e diminui tamanho da lista
    // precisa verificar se não está removendo o último
}

bool listarranjo::removeNoFim() { //r
    if (listaVazia())
        return false;
    posicao aux = ultimo;
    ultimo = vetorDados[ultimo].anterior;
    if (ultimo != INVALIDO) {
        vetorDados[ultimo].proximo = INVALIDO;
    }
    //vetorDados[aux].elemento = INVALIDO;
    tamanho--;
    if (listaVazia()) {
        ultimo = INVALIDO;
        primeiro = INVALIDO;
    }
    vetorDados[aux].proximo = primeiroApagado;
    primeiroApagado = aux;
    return true;
    // remoção simplesmente marca a posição como inválida
    // e diminui tamanho da minhaLista

    // precisa verificar se não está removendo o último
}

// método básico que *percorre* a lista, imprimindo seus elementos
void listarranjo::imprime() {
    posicao aux = primeiro;

    while (aux != INVALIDO) {
        if (vetorDados[aux].elemento != INVALIDO)
            cout << vetorDados[aux].elemento << " ";
        aux = vetorDados[aux].proximo;
    }
    cout << endl;


    //imprime reverso (para mostrar duplo encadeamento)
    aux = ultimo;
    while (aux != INVALIDO) {
        if (vetorDados[aux].elemento != INVALIDO)
            cout << vetorDados[aux].elemento << " ";
        aux = vetorDados[aux].anterior;
    }
    cout << endl;

}

// método básico que imprime o vetor de dados, para depuração
void listarranjo::depura() {
    cout << tamanho << "/{" << primeiro << "-" << ultimo << "}/" << primeiroApagado << ":";
    for (unsigned i = 0; i < capacidade; i++) {
        cout << "(" << vetorDados[i].anterior
            << ",[" << vetorDados[i].elemento << "],"
            << vetorDados[i].proximo << ")";
    }
    cout << endl;
}


int main() {
    unsigned cap;
    cin >> cap;
    listarranjo minhaLista(cap);
    char operacao;
    dado valor;
    do {
        cin >> operacao;
        switch (operacao) {
        case 'I': // inserir no início
            cin >> valor;
            if (not minhaLista.insereNoInicio(valor))
                cout << "Lista cheia, incapaz de inserir\n";
            break;
        case 'i': // inserir no fim
            cin >> valor;
            if (not minhaLista.insereNoFim(valor))
                cout << "Lista cheia, incapaz de inserir\n";
            break;
        case 'R': // remover no início
            if (not minhaLista.removeNoInicio())
                cout << "Lista vazia, incapaz de remover\n";
            break;
        case 'r': // remove no fim
            if (not minhaLista.removeNoFim())
                cout << "Lista vazia, incapaz de remover\n";
            break;
        case 'p': // mostrar estrutura
            minhaLista.imprime();
            break;
        case 'd': // depura vetor de dados
            minhaLista.depura();
            break;
        case 's': // sair
            // será tratado no while
            break;
        default:
            cout << "Opção inválida!" << endl;
        }
    } while (operacao != 's');

    return 0;
}
