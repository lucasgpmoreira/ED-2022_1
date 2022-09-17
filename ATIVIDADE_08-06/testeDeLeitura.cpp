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

int main() {
    ifstream arquivobi("csv_em_binario.dat", ios::binary);
    Campos aux;
    arquivobi.read((char*)&aux, sizeof(aux));
    ofstream novoTxt("comparacaoNOVO.txt");
    while (!arquivobi.eof()) {
        novoTxt << aux.id << "," << aux.name << "," << aux.city << "," << aux.sport << "," << aux.event << "," << aux.noc << endl;
        arquivobi.read((char*)&aux, sizeof(aux));
    }
    return 0;
}