/* 
    voos.cpp - aplicação para desenvolvimento de atividade
    de Tipo Abstrado de Dados

    Atividade de  GCC216 - Estruturas de Dados, 2020

    Solução de: LUCAS GABRIEL PEREIRA MOREIRA- 202110677
*/

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

struct bilhete {
    string nomeDoPassageiro;
    string codigoDoVoo;
    string horarioDePartida;
    bilhete();
};

bilhete::bilhete() {
    nomeDoPassageiro.clear();
    codigoDoVoo.clear();
    horarioDePartida.clear();
}

class empresaAerea {
    private:
        // *** AVISO: Não altere os atributos privados da classe *** 
        bilhete* listaDeBilhetes;
        int quantidadeDeBilhetes;
        int capacidadeMaxima;
    public:
        empresaAerea(int capacidade);
        empresaAerea(const empresaAerea &emp);
        ~empresaAerea();
        void inserirNovoBilhete(const bilhete& umBilhete);
        bool buscarBilhete(const string& nome, bilhete& umBilhete);
        void redimensionarCapacidade();
        friend void simularMudancaDeHorario(empresaAerea umaEmpresa, string codigo, string novoHorario);
};

empresaAerea::empresaAerea(int capacidade) {
    quantidadeDeBilhetes = 0;
    capacidadeMaxima = capacidade;
    listaDeBilhetes = new bilhete[capacidadeMaxima];
}

//implementa construtor de copia
empresaAerea::empresaAerea(const empresaAerea &emp) {
    capacidadeMaxima = emp.capacidadeMaxima;
    quantidadeDeBilhetes = emp.quantidadeDeBilhetes;
    listaDeBilhetes = new bilhete[capacidadeMaxima];
    copy(emp.listaDeBilhetes, emp.listaDeBilhetes + capacidadeMaxima, listaDeBilhetes);
}

empresaAerea::~empresaAerea() {
    delete [] listaDeBilhetes;
}

void empresaAerea::inserirNovoBilhete(const bilhete& umBilhete) {
    if (quantidadeDeBilhetes == capacidadeMaxima) { // vetor cheio, precisa redimensionar
        redimensionarCapacidade();
    }
    listaDeBilhetes[quantidadeDeBilhetes] = umBilhete;
    quantidadeDeBilhetes++;
}

bool empresaAerea::buscarBilhete(const string& nome, bilhete& umBilhete) {
    int posicaoAtual = 0;

    while (posicaoAtual < quantidadeDeBilhetes and 
           listaDeBilhetes[posicaoAtual].nomeDoPassageiro != nome) 
        posicaoAtual++;

    // se posicaoAtual não for menor que quantidade de produtos, é porque não encontrou
    if (posicaoAtual < quantidadeDeBilhetes) {
        umBilhete = listaDeBilhetes[posicaoAtual];
        return true;
    }

    return false;
}

void empresaAerea::redimensionarCapacidade() {
    capacidadeMaxima += ceil(capacidadeMaxima*0.8);
    cout << "capacidade maxima de " << capacidadeMaxima << endl;
    bilhete *listaAux;
    listaAux = new bilhete[capacidadeMaxima];
    copy(listaDeBilhetes, listaDeBilhetes+quantidadeDeBilhetes, listaAux);
    delete [] listaDeBilhetes;
    listaDeBilhetes = listaAux;
}

void simularMudancaDeHorario(empresaAerea umaEmpresa, string codigo, string novoHorario) {
    // *** AVISO: Não altere esta função *** 
    for (int i = 0; i < umaEmpresa.quantidadeDeBilhetes; i++) {
        if (umaEmpresa.listaDeBilhetes[i].codigoDoVoo == codigo) {
            cout << umaEmpresa.listaDeBilhetes[i].nomeDoPassageiro << endl;
        }
    }
    cout << endl;
}


int main() {
    // *** AVISO: Não altere a função principal, o main() *** 
    int capacidadeInicial;

    cout << "Voos - Aplicativo para Controlar Passagens Áereas\n" 
         << "Entre com capacidade máxima inicial: ";
    cin >> capacidadeInicial;

    empresaAerea minhaEmpresa(capacidadeInicial);

    cout << "Voos - Escolha a Opção:\n"
         << "i - inserir novo bilhete\n"
         << "b - buscar por um dado bilhete a partir do nome do passageiro\n"
         << "m - simular mudança de horário\n"
         << "s - para sair do programa" << endl;

    char opcaoDoMenu;
    bilhete umBilhete;
    string nome;
    string codigo;
    string novoHorario;

    cin >> opcaoDoMenu;

    while (opcaoDoMenu != 's') {
        switch(opcaoDoMenu) {
            case 'i' : 
                cout << "Entre com dados do bilhete (nome do passageiro, código do vôo e horário):" << endl;
                cin >> umBilhete.nomeDoPassageiro 
                    >> umBilhete.codigoDoVoo
                    >> umBilhete.horarioDePartida;
                minhaEmpresa.inserirNovoBilhete(umBilhete);
                break;

            case 'b' :
                cout << "Entre com nome do passageiro para busca: ";
                cin >> nome;
                
                if (minhaEmpresa.buscarBilhete(nome, umBilhete)) 
                    cout << umBilhete.nomeDoPassageiro << " "
                         << umBilhete.codigoDoVoo << " "
                         << umBilhete.horarioDePartida << endl << endl;
                else 
                    cout << "Bilhete não encontrado!" << endl << endl;
                break;

            case 'm' : 
                cout << "Entre com código do vôo e novo horário: ";
                cin >> codigo >> novoHorario;
                simularMudancaDeHorario(minhaEmpresa,codigo,novoHorario);
                break;

            case 's' : // não faz nada, espera retorno ao while para sair 
                break;

            default:
                cout << "Opção inválida!" << endl;
                break;

        }
        cout << "Voos - Escolha a Opção:\n"
            << "i - inserir novo bilhete\n"
            << "b - buscar por um dado bilhete a partir do nome do passageiro\n"
            << "m - simular mudança de horário\n"
            << "s - para sair do programa" << endl;
        cin >> opcaoDoMenu;
    }

    return 0;
}
