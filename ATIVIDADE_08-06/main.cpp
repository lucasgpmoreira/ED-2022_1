#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "leCSV.h"
#include "estrutura.h"

using namespace std;

class leCSV {
private:    
public:
    leCSV();
};

leCSV::leCSV() {
    fstream arquivocsv, arquivoBin;
    arquivocsv.open("data_athlete_event.csv");
    arquivoBin.open("csv_em_binario.dat", ios::binary | ios::out);
    cout << "Programa lendo arquivo csv e convertendo para binario ... " << endl;
    try {
        if (!arquivoBin.is_open() or !arquivocsv.is_open()) {
            throw invalid_argument("Erro ao converter arquivo csv para binario! Verifique se todos arquivos necessarios encontram-se na pasta.");
        } else {
            info aux;
            string linha, dadoCampo;
            getline(arquivocsv, linha); // le primeira linha
            int posicaoDoDelimitador = 0;
            while (getline(arquivocsv, linha)) {
                //obter primeiro  campo csv
                posicaoDoDelimitador = linha.find(",");
                dadoCampo = linha.substr(0, posicaoDoDelimitador);
                linha.erase(0, posicaoDoDelimitador + 1);
                aux.id = stoi(dadoCampo);

                //obter segundo campo
                if (linha[0] == '\"') {
                    posicaoDoDelimitador = linha.find("\",");
                    dadoCampo = linha.substr(0, posicaoDoDelimitador + 1);
                    linha.erase(0, posicaoDoDelimitador + 2);
                    strcpy(aux.nome, dadoCampo.c_str());
                    //cout << aux.nome << " - ";
                } else {
                    posicaoDoDelimitador = linha.find(",");
                    dadoCampo = linha.substr(0, posicaoDoDelimitador);
                    linha.erase(0, posicaoDoDelimitador + 1);
                    strcpy(aux.nome, dadoCampo.c_str());
                    //cout << aux.nome << " - ";
                }


                //obter terceiro campo
                posicaoDoDelimitador = linha.find(",");
                dadoCampo = linha.substr(0, posicaoDoDelimitador);
                linha.erase(0, posicaoDoDelimitador + 1);
                strcpy(aux.cidade, dadoCampo.c_str());
                //cout << aux.cidade << " - ";


                //obter quarto campo
                posicaoDoDelimitador = linha.find(",");
                dadoCampo = linha.substr(0, posicaoDoDelimitador);
                linha.erase(0, posicaoDoDelimitador + 1);
                strcpy(aux.esporte, dadoCampo.c_str());
                //cout << aux.esporte << " - ";

                //obter quinto campo
                if (linha[0] == '\"') {
                    posicaoDoDelimitador = linha.find("\",");
                    dadoCampo = linha.substr(0, posicaoDoDelimitador + 1);
                    linha.erase(0, posicaoDoDelimitador + 2);
                    strcpy(aux.evento, dadoCampo.c_str());
                    //cout << aux.evento << " - ";
                } else {
                    posicaoDoDelimitador = linha.find(",");
                    dadoCampo = linha.substr(0, posicaoDoDelimitador);
                    linha.erase(0, posicaoDoDelimitador + 1);
                    strcpy(aux.evento, dadoCampo.c_str());
                    //cout << aux.evento << " - ";
                }

                //obter sexto campo
                posicaoDoDelimitador = linha.find(",");
                dadoCampo = linha.substr(0, posicaoDoDelimitador);
                linha.erase(0, posicaoDoDelimitador + 1);
                strcpy(aux.noc, dadoCampo.c_str());
                //cout << aux.noc << endl;
                arquivoBin.write((char*)&aux, sizeof(aux));
            }
        }
    }
    catch (invalid_argument& e) {
        cout << e.what() << endl;
        abort();
    }
    arquivoBin.close();
    arquivocsv.close();
}

class operacoes {
private:
public:
    void inserir();
    void exibir(int posIni, int posFim, leCSV& csv);
    void buscar();
    void remover();
    void alterar();
};

int main() {
    leCSV arqCSV;
    operacoes op;

    int opcao;
    cout << "O que deseja fazer?: " << endl
        << "1 - Adicionar um elemento no arquivo binario em uma posicao especifica " << endl
        << "2 - Visualizar os registros entre a posicao x e y." << endl
        << "3 - Alterar os dados de um registro em uma posicao especifica." << endl
        << "4 - Trocar dois registros de posicao no arquivo." << endl
        << "5 - Imprimir todos os registros do arquivo binario, na ordem em que estao armazenados." << endl
        << "6 - SAIR" << endl;
    do {
        cin >> opcao;
        cout << "Voce escolheu ";
        switch (opcao) {
        case 1:
            cout << "adicionar um elemento no arquivo binario em uma posicao especifica " << endl;
            break;
        case 2:
            cout << "visualizar os registros entre a posicao x e y." << endl;
            break;
        case 3:
            cout << "alterar os dados de um registro em uma posicao especifica." << endl;
            break;
        case 4:
            cout << "trocar dois registros de posicao no arquivo." << endl;
            break;
        case 5:
            cout << "imprimir todos os registros do arquivo binario, na ordem em que estao armazenados." << endl;
            break;
        case 6:
            cout << "sair" << endl;
            break;
        default:
            cout << "uma opcao invalida" << endl;
            break;
        }
    } while (opcao != 6);
    return 0;
}