/* 
    viveiro.cpp - aplicação para desenvolvimento de atividade
    de Tipo Abstrado de Dados

    Atividade de  GCC216 - Estruturas de Dados, 2020

    Solução de: INSIRA AQUI SEU NOME
*/

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

struct planta {
    string nomeDaEspecie;
    string nomeFamilia;  
    string epocaDePlantio;
    planta();       
};

planta::planta() {
    nomeDaEspecie.clear();
    nomeFamilia.clear();
    epocaDePlantio.clear();
}


class viveiro {
    private:
        // *** AVISO: Não altere os atributos privados da classe *** 
        planta* listaDePlantas;
        int quantidadeDePlantas;
        int capacidadeMaxima;
    public:
        viveiro(int capacidade);
        //viveiro(const viveiro &viv);
        ~viveiro();
        void inserirNovaPlanta(const planta& umaPlanta);
        bool buscarPlanta(const string& umNome, planta& umaPlanta);
        void redimensionarCapacidade();
        friend void simularMudancaDePlantio(viveiro umaPlanta, string umaFamilia, string novaEpoca);
};

viveiro::viveiro(int capacidade) {
    quantidadeDePlantas = 0;
    capacidadeMaxima = capacidade;
    listaDePlantas = new planta[capacidadeMaxima];
}


viveiro::viveiro(const viveiro &viv) {
    cout << "contrutor de copia" << endl;
    capacidadeMaxima = viv.capacidadeMaxima;
    quantidadeDePlantas = viv.quantidadeDePlantas;
    listaDePlantas = new planta[capacidadeMaxima];
    copy(viv.listaDePlantas, viv.listaDePlantas + capacidadeMaxima, listaDePlantas);
}

viveiro::~viveiro() {
    cout << "destrutor" << endl;
    delete [] listaDePlantas;
}

void viveiro::inserirNovaPlanta(const planta& umaPlanta) {
    if (quantidadeDePlantas == capacidadeMaxima) { // vetor cheio, precisa redimensionar
        redimensionarCapacidade();
    }
    listaDePlantas[quantidadeDePlantas] = umaPlanta;
    quantidadeDePlantas++;
}

bool viveiro::buscarPlanta(const string& nome, planta& umaPlanta) {
    int posicaoAtual = 0;

    while (posicaoAtual < quantidadeDePlantas and 
           listaDePlantas[posicaoAtual].nomeDaEspecie != nome) 
        posicaoAtual++;

    // se posicaoAtual não for menor que quantidade de plantas, é porque não encontrou
    if (posicaoAtual < quantidadeDePlantas) {
        umaPlanta = listaDePlantas[posicaoAtual];
        return true;
    }

    return false;
}

void viveiro::redimensionarCapacidade() {
    capacidadeMaxima += ceil(capacidadeMaxima*0.2);
    planta* novaLista = new planta[capacidadeMaxima];
    copy(listaDePlantas, listaDePlantas + quantidadeDePlantas, novaLista);
    delete [] listaDePlantas;
    listaDePlantas = novaLista;
}

void simularMudancaDePlantio(viveiro umViveiro, string umaFamilia, string novaEpoca) {
    // *** AVISO: Não altere esta função *** 
    for (int i = 0; i < umViveiro.quantidadeDePlantas; i++) {
        if (umViveiro.listaDePlantas[i].nomeFamilia == umaFamilia)
        cout << umViveiro.listaDePlantas[i].nomeDaEspecie << " " 
             << umViveiro.listaDePlantas[i].nomeFamilia << " " 
             << novaEpoca << endl;
    }
    cout << endl;
}


int main() {
    // *** AVISO: Não altere a função principal, o main() *** 
    int capacidadeInicial;

    cout << "Viveiro de Plantas\nAplicativo para simular a listagem de plantas com mudança de plantio \n" 
         << "\nEntre com capacidade máxima inicial do viveiro: ";
    cin >> capacidadeInicial;

    viveiro meuViveiro(capacidadeInicial);

    cout << "Plantas - Escolha a Opção:\n"
         << "i - inserir nova planta\n"
         << "b - buscar por dados de uma planta a partir da especie\n"
         << "r - simular mudança na época de plantio\n"
         << "s - para sair do programa" << endl;

    char opcaoDoMenu;
    planta umaPlanta;
    string nomePlanta;
    string umaFamilia;
    string novaEpoca;

    cin >> opcaoDoMenu;

    while (opcaoDoMenu != 's') {
        switch(opcaoDoMenu) {
            case 'i' : 
                cout << "Entre com dados da planta (nome da especie, família a que pertence e época de plantio (mes(es)):" << endl;
                cin >> umaPlanta.nomeDaEspecie
                    >> umaPlanta.nomeFamilia>>umaPlanta.epocaDePlantio;
                meuViveiro.inserirNovaPlanta(umaPlanta);
                break;

            case 'b' :
                cout << "Entre com nome da planta para busca: ";
                cin >> nomePlanta;
                
                if (meuViveiro.buscarPlanta(nomePlanta, umaPlanta)) 
                    cout << umaPlanta.nomeDaEspecie<< " "
                         << umaPlanta.nomeFamilia << " " <<  umaPlanta.epocaDePlantio << endl << endl;
                else 
                    cout << "Planta não encontrada!" << endl << endl;
                break;

            case 'r' : 
                cout << "Entre com a família desejada: ";
                cin >> umaFamilia;
                cout<< "Entre com a nova época de plantio: ";
                cin>>novaEpoca;
                simularMudancaDePlantio(meuViveiro,umaFamilia, novaEpoca);
                break;

            case 's' : // não faz nada, espera retorno ao while para sair 
                break;

            default:
                cout << "Opção inválida!" << endl;
                break;

        }
    cout << "Plantas - Escolha a Opção:\n"
         << "i - inserir nova planta\n"
         << "b - buscar por dados de uma planta a partir da especie\n"
         << "r - simular mudança na época de plantio\n"
         << "s - para sair do programa" << endl;
    cin >> opcaoDoMenu;
    }

    return 0;
}
