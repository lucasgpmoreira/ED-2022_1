#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
using namespace std;


ifstream arquivo_csv;
ofstream arquivo_bin;
   
struct jogador_string{
	char id[6], nome[65],time[20],jogos[20],ano[4],temporada[10];
};

jogador_string escritor(string dados[]){ // conversão string p/ char
	jogador_string estrutura;
	strcpy(estrutura.id,dados[0].c_str());
	//cout << estrutura.id << " ";
	strcpy(estrutura.nome,dados[1].c_str());
	//cout << estrutura.nome << " ";
	strcpy(estrutura.time,dados[2].c_str());
	//cout << estrutura.time << " ";
		
	strcpy(estrutura.jogos,dados[3].c_str());
	//cout << estrutura.jogos << " ";
		
	strcpy(estrutura.ano,dados[4].c_str());
	//cout << estrutura.ano << " ";
		
	strcpy(estrutura.temporada,dados[5].c_str());
	//cout << estrutura.temporada << " ";
    //cout << estrutura.id << " " << estrutura.nome <<" " << estrutura.jogos <<" " << estrutura.time
    //<< " " << estrutura.temporada << " " << estrutura.ano << endl;
	return estrutura;
}

void conversao (){ // funcao para converter csv para binario
	arquivo_bin.open("data_athlete_game.bin", ios::binary | ios::out);
	arquivo_csv.open("data_athlete_game.csv", ios::in | ios::out);
	string *dados;
	jogador_string estrutura;
    dados = new string[6];
	string line ="";
    arquivo_csv.seekg(31); // pula os bytes
					//começar 31 bytes a frente para nao ler a descrição dos campos
	while(getline(arquivo_csv, line)){
		stringstream inputstring (line);
		for(int j = 0; j < 6; j++){
			getline(inputstring, dados[j],',');
		}
		estrutura = escritor(dados);
		arquivo_bin.write((char *)&estrutura,sizeof(jogador_string)) <<endl;
		line = "";
	}
    arquivo_csv.close();
	arquivo_bin.close();
}
