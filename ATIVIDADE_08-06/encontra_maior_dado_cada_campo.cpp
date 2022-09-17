#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>

using namespace std;

struct Campos {
    long id;
    char name[109];
    char city[23];
    char sport[26];
    char event[88];
    char noc[4];
};

int confereOMaiorDadoNoCampo(int& campo, int tamanho) {
    if (tamanho > campo) {
        campo = tamanho;
    }
}

int main() {
    ifstream arquivocsv("data_athlete_event.csv");
    fstream arquivobi("csv_em_binario.dat", ios::binary | ios::out | ios::trunc);
    ofstream arquivotxt("data_athlete_event.txt");
    int maiorDadoId, maiorDadoName, maiorDadoCity, maiorDadoSport, maiorDadoEvent, maiorDadoNoc;
    maiorDadoId = maiorDadoName = maiorDadoCity = maiorDadoSport = maiorDadoEvent = maiorDadoNoc = 0;
    Campos auxiliar;
    string dadoCampo;
    int posicaoDoDelimitador = 0;
    string campo;
    getline(arquivocsv, campo); // le primeira linha
    int contador = 0;
    while (getline(arquivocsv, campo)) {
        //obter primeiro  campo 
        posicaoDoDelimitador = campo.find(",");
        dadoCampo = campo.substr(0, posicaoDoDelimitador);
        arquivotxt << dadoCampo << ",";
        campo.erase(0, posicaoDoDelimitador + 1);
        auxiliar.id = stoi(dadoCampo);

        if (auxiliar.id == 27903) {
            cout << "ID: " << auxiliar.id << endl;
        }


        //obter segundo campo
        if (campo[0] == '\"') {
            posicaoDoDelimitador = campo.find("\",");
            dadoCampo = campo.substr(0, posicaoDoDelimitador + 1);
            campo.erase(0, posicaoDoDelimitador + 2);
            strcpy(auxiliar.name, dadoCampo.c_str());
            arquivotxt << auxiliar.name << ",";
        } else {
            posicaoDoDelimitador = campo.find(",");
            dadoCampo = campo.substr(0, posicaoDoDelimitador);
            campo.erase(0, posicaoDoDelimitador + 1);
            strcpy(auxiliar.name, dadoCampo.c_str());
            arquivotxt << auxiliar.name << ",";
        }

        //obter terceiro campo
        posicaoDoDelimitador = campo.find(",");
        dadoCampo = campo.substr(0, posicaoDoDelimitador);
        campo.erase(0, posicaoDoDelimitador + 1);
        strcpy(auxiliar.city, dadoCampo.c_str());
        arquivotxt << auxiliar.city << ",";

        //obter quarto campo
        posicaoDoDelimitador = campo.find(",");
        dadoCampo = campo.substr(0, posicaoDoDelimitador);
        campo.erase(0, posicaoDoDelimitador + 1);
        strcpy(auxiliar.sport, dadoCampo.c_str());
        arquivotxt << auxiliar.sport << ",";

        //obter quinto campo
        if (campo[0] == '\"') {
            posicaoDoDelimitador = campo.find("\",");
            dadoCampo = campo.substr(0, posicaoDoDelimitador + 1);
            campo.erase(0, posicaoDoDelimitador + 2);
            strcpy(auxiliar.event, dadoCampo.c_str());
            arquivotxt << auxiliar.event << ",";
        } else {
            posicaoDoDelimitador = campo.find(",");
            dadoCampo = campo.substr(0, posicaoDoDelimitador);
            campo.erase(0, posicaoDoDelimitador + 1);
            strcpy(auxiliar.event, dadoCampo.c_str());
            arquivotxt << auxiliar.event << ",";
        }

        //obter sexto campo
        posicaoDoDelimitador = campo.find(",");
        dadoCampo = campo.substr(0, posicaoDoDelimitador);
        campo.erase(0, posicaoDoDelimitador + 1);
        strcpy(auxiliar.noc, dadoCampo.c_str());
        arquivotxt << auxiliar.noc << endl;

        if (auxiliar.id == 27903) {
            cout << "Nome: " << auxiliar.name << endl;
            cout << "Cidade: " << auxiliar.city << endl;
            cout << "Esporte: " << auxiliar.sport << endl;
            cout << "Evento: " << auxiliar.event << endl;
            cout << "NOC: " << auxiliar.noc << endl;
        }

        arquivobi.write((char*)&auxiliar, sizeof(auxiliar));
        cout << contador << endl;
        contador++;
    }
    //escreve no arquivo txt o tamanho dos maiores campos
    /*arquivotxt << endl
    << "maiorDadoId: " << maiorDadoId << endl
    << "maiorDadoName: " << maiorDadoName << endl
    << "maiorDadoCity: " << maiorDadoCity << endl
    << "maiorDadoSport: " << maiorDadoSport << endl
    << "maiorDadoEvent: " << maiorDadoEvent << endl
    << "maiorDadoNoc: " << maiorDadoNoc << endl;*/
    arquivocsv.close();
    arquivobi.close();
    arquivotxt.close();

    cout << "Fim" << endl;
    getchar();
    arquivobi.open("csv_em_binario.dat", ios::binary | ios::in);
    if (!arquivobi.is_open()) {
        cout << "Arquivo não existe" << endl;
    }
    Campos aux;


    arquivobi.read((char*)&aux, sizeof(aux));
    ofstream novoTxt("comparacao.txt");
    while (!arquivobi.eof()) {
        novoTxt << aux.id << "," << aux.name << "," << aux.city << "," << aux.sport << "," << aux.event << "," << aux.noc << endl;
        arquivobi.read((char*)&aux, sizeof(aux));
    }

    arquivobi.close();
    return 0;

}