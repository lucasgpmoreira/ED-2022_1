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
}

// destrutor da lista
listarranjo::~listarranjo( ) {
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

bool listarranjo::insereListaVazia(dado d)
{
	// se a lista estiver vazia, inserimos o último nó
	posicao ptPosAlocada;
	
	if (alocaPosicao(&ptPosAlocada))
	{
		vetorDados[ptPosAlocada].elemento = d;
		vetorDados[ptPosAlocada].proximo = INVALIDO;
		primeiro = ptPosAlocada;
		ultimo = ptPosAlocada;
	
		return true;
	}
	
	else
	{
		return false;
	}	
}
	

// Insere no início da lista. Retorna um booleano que indica se foi possivel fazer a insercao.
bool listarranjo::insereNoInicio(dado d) 
{
    // verifica se ainda cabe um novo elemento
    if (tamanho >= capacidade)
    {
		return false;
	}

    
    //lista vazia
    if (tamanho == 0)
    {
		insereListaVazia(d);
		tamanho++;
		
		return true;
	}
	    
    // já tem elementos na lista, insere no início
    else
    {
		posicao ptPosAlocada, auxiliar;
		
		if (alocaPosicao(&ptPosAlocada))
		{
			vetorDados[ptPosAlocada].elemento = d;
		}
		
		auxiliar = primeiro;
		vetorDados[primeiro].anterior = ptPosAlocada;
		primeiro = ptPosAlocada;
		vetorDados[primeiro].proximo = auxiliar;
		tamanho++;
		
		return true;
	}
    
}
    

// Insere no final da lista. Retorna um booleano que indica se foi possivel fazer a insercao.
bool listarranjo::insereNoFim(dado d) 
{
    // verifica se ainda cabe um novo elemento
    if (tamanho >= capacidade)
    {
		return false;
	}
	

	//lista vazia
    if (tamanho == 0)
    {
		insereListaVazia(d);
		tamanho++;
		
		return true;
	}
    
    // se já tem elementos na lista, insere no final
    
	else
	{
		posicao ptPosAlocada, auxiliar;
		
		if (alocaPosicao(&ptPosAlocada))
		{
			vetorDados[ptPosAlocada].elemento = d;
		}
		
		vetorDados[ultimo].proximo = ptPosAlocada;
		auxiliar = ultimo;
		ultimo = ptPosAlocada;
		vetorDados[ultimo].anterior = auxiliar;
		vetorDados[ultimo].proximo = INVALIDO;
		tamanho++;
		
		return true;
	}

}

bool listarranjo::removeNoInicio() {

    //verifica se está vazia
    if (tamanho == 0)
    {
		cerr << "LISTA VAZIA" << endl;
		return false;
	}
	
    // remoção simplesmente marca a posição como inválida
    // e diminui tamanho da lista
    
    else
    {
		posicao auxiliar = primeiro;
		
		primeiro = vetorDados[primeiro].proximo;
		vetorDados[auxiliar].elemento = VALOR_PADRAO;
		vetorDados[auxiliar].anterior = INVALIDO;
		vetorDados[auxiliar].proximo = primeiroApagado;
		primeiroApagado = auxiliar;
		
		tamanho--;
		
		// precisa verificar se não está removendo o último
		if (tamanho == 0)
		{
			primeiro = INVALIDO;
			ultimo = INVALIDO;
		}
	}
		
		return true;   
}

bool listarranjo::removeNoFim() {
    //verifica se está vazia
    if (tamanho == 0)
    {
		cerr << "LISTA VAZIA" << endl;
		return false;
	}
	
    // remoção simplesmente marca a posição como inválida
    // e diminui tamanho da minhaLista
    else 
    {
		posicao auxiliar = ultimo;
		
		ultimo = vetorDados[ultimo].anterior;
		vetorDados[auxiliar].elemento = VALOR_PADRAO; 
		vetorDados[auxiliar].anterior = INVALIDO;
		vetorDados[auxiliar].proximo = primeiroApagado;
		primeiroApagado = auxiliar;
		
		tamanho--;

		// precisa verificar se não está removendo o último
		if (tamanho == 0)
		{
			primeiro = INVALIDO;
			ultimo = INVALIDO;
		}
		
		return true;
	}

}

// método básico que *percorre* a lista, imprimindo seus elementos
void listarranjo::imprime() {
    posicao aux = primeiro;

    while (aux != INVALIDO) {
        cout << vetorDados[aux].elemento << " ";
        aux = vetorDados[aux].proximo;
    }
    cout << endl;

    // imprime reverso (para mostrar duplo encadeamento)
    aux = ultimo;
    while (aux != INVALIDO) {
        cout << vetorDados[aux].elemento << " ";
        aux = vetorDados[aux].anterior;
    }
    cout << endl;
}

// método básico que imprime o vetor de dados, para depuração
void listarranjo::depura() {
    cout << tamanho << "/{"<< primeiro << "-" << ultimo << "}/" << primeiroApagado << ":";
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
