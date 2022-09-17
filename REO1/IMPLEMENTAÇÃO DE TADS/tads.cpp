/*
* Lucas Gabriel Pereira Moreira - 202110677
* Estruturas de Dados
* 15/06/2022
* Enunciado 5

* O programa foi feito com base em uma classe cadastro, principal, que pode levar o usuario a 
* escolher adicionar um novo esporte que, para cada esporte podem ser adicionados uma lista de
* atletas e patrocinadores. Além disso, no inicio pode ser adicionado um patrocinador geral do evento.
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>

using namespace std;

struct Patrocinador {
    string nome;
    string setor;
    string pais;
    string sede;
    float valorInvestido;
    string inicioContrato;
    string prazoContrato;
};

struct Atleta {
    string nacionalidade;
    float altura;
    float peso;
    string nome;
    string dataNascimento;
};

struct Esporte {
    Atleta atleta;
    Patrocinador patrocinador;
    vector<Atleta> vetorAtletas;
    vector<Patrocinador> vetorPatrocinadores;
    string nomeEsporte;
    string nomeAtividade;
    string diasEHorarios;
};

class cadastro {
private:
    Esporte esporte;
    vector<Esporte> vetEsportes;
    vector<Patrocinador> vetPatrocinadoresGerais;
    void cadastraAtleta(Esporte& esporte);
    void cadastraPatrocinio(Esporte& esporte);
    void cadastraPatrocinio();
    int buscaEsporte(string nome);
    void listaDados(int posicaoDoDado);
public:
    void cadastrar(int opcao);
    void buscar(int opcao);

};

void cadastro::cadastrar(int opcao) {
    if (opcao == 1) {
        cout << "Escolha qual deseja cadastrar, um: \n[1] Novo esporte \n[2] Novo atleta a um esporte existente \n[3] Novo patrocinador a um esporte" << endl;
        cin >> opcao;
        if (opcao == 1) {
            cout << "Para cadastrar um novo esporte preencha os dados que serao requisitados.\n\nNome do Esporte: ";
            getline(cin >> ws, esporte.nomeEsporte);
            cout << "\nNome da atividade: ";
            getline(cin >> ws, esporte.nomeAtividade);
            cout << "\nDias e horarios: ";
            getline(cin >> ws, esporte.diasEHorarios);
            cout << "\nDeseja cadastrar um atleta para este esporte? (S/N)";
            char alt;
            do {
                cin >> alt;
                if (alt == 'S' or alt == 's') {
                    cadastraAtleta(esporte);
                    cout << "Deseja cadastrar um novo atleta? (S/N)" << endl;
                }
            } while (alt == 'S' or alt == 's');

            cout << "Deseja cadastrar um patrocinador para este esporte? (S/N)";
            do {
                cin >> alt;
                if (alt == 'S' or alt == 's') {
                    cadastraPatrocinio(esporte);
                    cout << "Deseja cadastrar um novo patrocinador? (S/N)" << endl;
                }
            } while (alt == 'S' or alt == 's');
            vetEsportes.push_back(esporte);
            cout << "Para prosseguir pressione qualquer tecla. " << endl;
            getchar();

        } else if (opcao == 2 or opcao == 3) {
            if (vetEsportes.empty()) {
                cout << "Nenhum esporte foi cadastrado ainda" << endl;
            } else {
                string nomeEsporte;
                cout << "Digite o nome do esporte para fazer a busca: " << endl;
                getline(cin >> ws, nomeEsporte);
                int posicaoDoDado = buscaEsporte(nomeEsporte);
                if (posicaoDoDado == -1) {
                    cout << "Esporte nao encontrado." << endl;
                    cout << "Para prosseguir pressione qualquer tecla. " << endl;
                    getchar();
                } else {
                    if (opcao == 2)
                        cadastraAtleta(vetEsportes[posicaoDoDado]);
                    if (opcao == 3)
                        cadastraPatrocinio(vetEsportes[posicaoDoDado]);
                }
            }
        }
    } else {
        cadastraPatrocinio();
    }
}

void cadastro::cadastraAtleta(Esporte& esporte) {
    cout << "\nDigite a nacionalidade do atleta: ";
    getline(cin >> ws, esporte.atleta.nacionalidade);
    cout << "\nDigite a altura do atleta(m): ";
    cin >> esporte.atleta.altura;
    cout << "\nDigite o peso do atleta(kg): ";
    cin >> esporte.atleta.peso;
    cout << "\nDigite o nome do atleta: ";
    getline(cin >> ws, esporte.atleta.nome);
    cout << "\nDigite a data de nascimento do atleta(dd/mm/aaaa): ";
    getline(cin >> ws, esporte.atleta.dataNascimento);
    esporte.vetorAtletas.push_back(esporte.atleta);
}

void cadastro::cadastraPatrocinio(Esporte& esporte) { //adiciona patrocinador especifico
    cout << "Digite o nome do patrocinador: ";
    getline(cin >> ws, esporte.patrocinador.nome);
    cout << "\nDigite o setor do patrocinador: ";
    getline(cin >> ws, esporte.patrocinador.setor);
    cout << "\nDigite o pais do patrocinador: ";
    getline(cin >> ws, esporte.patrocinador.pais);
    cout << "\nDigite a sede do patrocinador: ";
    getline(cin >> ws, esporte.patrocinador.sede);
    cout << "\nDigite o valor investido: ";
    cin >> esporte.patrocinador.valorInvestido;
    cout << "\nDigite o inicio do contrato: ";
    getline(cin >> ws, esporte.patrocinador.inicioContrato);
    cout << "\nDigite o prazo do contrato: ";
    getline(cin >> ws, esporte.patrocinador.prazoContrato);
    esporte.vetorPatrocinadores.push_back(esporte.patrocinador);
}

void cadastro::cadastraPatrocinio() { //adiciona patrocinador geral
    Patrocinador patrocinador;
    cout << "Digite o nome do patrocinador: ";
    getline(cin >> ws, patrocinador.nome);
    cout << "\nDigite o setor do patrocinador: ";
    getline(cin >> ws, patrocinador.setor);
    cout << "\nDigite o pais do patrocinador: ";
    getline(cin >> ws, patrocinador.pais);
    cout << "\nDigite a sede do patrocinador: ";
    getline(cin >> ws, patrocinador.sede);
    cout << "\nDigite o valor investido: ";
    cin >> patrocinador.valorInvestido;
    cout << "\nDigite o inicio do contrato: ";
    getline(cin >> ws, patrocinador.inicioContrato);
    cout << "\nDigite o prazo do contrato: ";
    getline(cin >> ws, patrocinador.prazoContrato);
    vetPatrocinadoresGerais.push_back(patrocinador);
}

int cadastro::buscaEsporte(string nome) {
    for (int i = 0; i < vetEsportes.size(); i++) {
        if (vetEsportes[i].nomeEsporte == nome) {
            return i;
        }
    }
    return -1;
}

void cadastro::buscar(int opcao) {
    string nomeEsporte;
    if (opcao == 1) {
        cout
            << "Voce pode fazer a busca por esporte, digite o nome do mesmo abaixo e serao" << endl
            << "listados todos os dados dele, seus atletas e patrocinadores e as suas" << endl
            << "respectivas informacoes" << endl;
        getline(cin >> ws, nomeEsporte);
        int posicaoDadoNoVetor = buscaEsporte(nomeEsporte);
        if (posicaoDadoNoVetor == -1) {
            cout << "Esse nome nao foi encontrado nos registros." << endl;
        } else {
            listaDados(posicaoDadoNoVetor);
        }
        cout << "Para prosseguir pressione qualquer tecla. " << endl;
        getchar();
    } else {
        cout << "Lista dos patrocinadores gerais: " << endl;
        if (vetPatrocinadoresGerais.empty()) {
            cout << "Nenhum patrocinador cadastrado.";
        } else {
            for (int i = 0; i < vetPatrocinadoresGerais.size(); i++) {
                cout
                    << "\nNome: " << vetPatrocinadoresGerais[i].nome << endl
                    << "Setor: " << vetPatrocinadoresGerais[i].setor << endl
                    << "Pais: " << vetPatrocinadoresGerais[i].pais << endl
                    << "Sede: " << vetPatrocinadoresGerais[i].sede << endl
                    << "Valor investido: " << vetPatrocinadoresGerais[i].valorInvestido << endl
                    << "Inicio Contrato: " << vetPatrocinadoresGerais[i].inicioContrato << endl
                    << "Prazo Contrato: " << vetPatrocinadoresGerais[i].prazoContrato << endl << endl;
            }
        }
        cout << "Para prosseguir pressione qualquer tecla. " << endl;
        getchar();
    }
}

void cadastro::listaDados(int pos) {
    Esporte esporteNaPos = vetEsportes[pos];
    cout << "Esporte: "
        << esporteNaPos.nomeEsporte << endl
        << "Nome da Atividade: "
        << esporteNaPos.nomeAtividade << endl
        << "Dias e horarios deste: "
        << esporteNaPos.diasEHorarios << endl;
    cout << "\nAtletas: " << endl;
    if (esporteNaPos.vetorAtletas.empty())
        cout << "Nenhum atleta cadastrado!" << endl;
    else {
        for (int i = 0; i < esporteNaPos.vetorAtletas.size(); i++) {
            cout
                << "Nome: " << esporteNaPos.vetorAtletas[i].nome << endl
                << "Nacionalidade: " << esporteNaPos.vetorAtletas[i].nacionalidade << endl
                << "Altura: " << esporteNaPos.vetorAtletas[i].altura << endl
                << "Peso: " << esporteNaPos.vetorAtletas[i].peso << endl
                << "Data de Nascimento: " << esporteNaPos.vetorAtletas[i].dataNascimento << endl << endl;
        }
    }

    cout << "Patrocinadores: " << endl;
    if (esporteNaPos.vetorPatrocinadores.empty())
        cout << "Nenhum patrocinador cadastrado!" << endl;
    else {
        for (int i = 0; i < esporteNaPos.vetorPatrocinadores.size(); i++) {
            cout
                << "Nome: " << esporteNaPos.vetorPatrocinadores[i].nome << endl
                << "Setor: " << esporteNaPos.vetorPatrocinadores[i].setor << endl
                << "Pais: " << esporteNaPos.vetorPatrocinadores[i].pais << endl
                << "Sede: " << esporteNaPos.vetorPatrocinadores[i].sede << endl
                << "Valor investido: " << esporteNaPos.vetorPatrocinadores[i].valorInvestido << endl
                << "Inicio Contrato: " << esporteNaPos.vetorPatrocinadores[i].inicioContrato << endl
                << "Prazo Contrato: " << esporteNaPos.vetorPatrocinadores[i].prazoContrato << endl << endl;
        }
    }
}

void impressaoInicio() {
    string linha;
    ifstream arquivo;
    arquivo.open("inicio.txt");
    if (arquivo.is_open()) {
        while (getline(arquivo, linha)) {
            cout << linha << endl;
        }
    } else {
        cout << "HOUVE UM ERRO NA LEITURA DO ARQUIVO QUE DEVERIA ESTAR AQUI." << endl
            << "VERIFIQUE SE O ARQUIVO \"inicio.txt\" ENCONTRA-SE NO MESMO DIRETORIO QUE ESTE CODIGO.\a" << endl;
    }
}

int main() {
    cadastro esportes;
    int opcao;
    char alternativa;
    do {
        impressaoInicio();
        cin >> opcao;
        if ((opcao < 1 or opcao > 2) and opcao != 3) {
            cout << "Invalido, escolha 1, 2 ou 3\a" << endl;
        }
        if (opcao == 1 or opcao == 2) {
            cout << "Para prosseguir escolha, \n[A] PARA CADASTRAR  ou  [B] PARA LISTAR E BUSCAR\n";
            cin >> alternativa;
            if (alternativa == 'A' or alternativa == 'a')
                esportes.cadastrar(opcao);
            else
                esportes.buscar(opcao);
        }
    } while ((opcao > 0 or opcao < 3) and opcao != 3);
    return 0;
}