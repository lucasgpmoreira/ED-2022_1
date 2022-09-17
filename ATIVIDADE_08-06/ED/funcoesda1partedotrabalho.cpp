/*
Grupo 4:
 - Beatriz Fernandes Teixeira
 - Dênis de Souza Cordeiro
 - Ronald de Souza Galdino

----------- data_athlete_game.7z ------------

*/
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include "conversao.cpp"
using namespace std;

fstream arquivo_binLer;

void imprimir_registros(){
    arquivo_binLer.open("data_athlete_game.bin", ios::binary | ios::in );
    jogador_string vetJogador;
    int i=0;
    arquivo_binLer.seekg(i);
    while(arquivo_binLer){
        arquivo_binLer.seekg(i); // funcao para posicionar a leitura dos objetos
        arquivo_binLer.read((char*) (&vetJogador), sizeof(jogador_string));
        cout << "Id: "<<vetJogador.id << " Nome:"<< " " << vetJogador.nome  
        << "\n" << "Jogos:"<<" " << vetJogador.jogos << "\n" << "Time:" 
        <<" " << vetJogador.time << "\n" << "Temporada:" << " " << vetJogador.temporada << " Ano:" << " " << vetJogador.ano << endl;
        cout << endl;
        i= i + 126; // 126 = tamanho da struct jogador_string
    }
    arquivo_binLer.close();
}
void alterar_registro(jogador_string atleta, int pos){
    arquivo_binLer.open("data_athlete_game.bin", ios::binary | ios::in | ios::out);
    arquivo_binLer.seekg(pos*(sizeof(jogador_string)+1));
    arquivo_binLer.write((char*) (&atleta), sizeof(jogador_string)+1); // substituindo o registro com valores de campo alterados.
    arquivo_binLer.close();
}

void listar_atletas(int pos1, int pos2){
    arquivo_binLer.open("data_athlete_game.bin", ios::binary | ios::in | ios::out | ios::app);
    int pos_inicio = (sizeof(jogador_string)+1)*(pos1+1);
    jogador_string vetJogador;
    int tam = pos2 - pos1;
    if (tam<0) tam = tam*(-1);
    int i=1;
    pos1= pos_inicio; // 378
    while (i < tam){
        //cout << "pos1 = " << pos1 << endl;
        arquivo_binLer.seekg(pos1); 
        arquivo_binLer.read((char*) (&vetJogador), sizeof(jogador_string));
        cout << "Id: "<<vetJogador.id << " Nome:"<< " " << vetJogador.nome  
        << "\n" << "Jogos:"<<" " << vetJogador.jogos << "\n" << "Time:" 
        <<" " << vetJogador.time << "\n" << "Temporada:" << " " << vetJogador.temporada << " Ano:" << " " << vetJogador.ano << endl;
        cout << endl;
       pos1 = pos_inicio + ( (sizeof(jogador_string)+1))*i;
       i++;
    }
    arquivo_binLer.close();
}
void trocar_atletas(int pos1, int pos2){
    arquivo_binLer.open("data_athlete_game.bin", ios::binary | ios::in | ios::out);
    int pos1_bin = pos1*(sizeof(jogador_string)+1); // 126*5=630
    int pos2_bin = pos2*(sizeof(jogador_string)+1);
    jogador_string pos1_atlet, pos2_atlet; 
    arquivo_binLer.seekg(pos1_bin);
    arquivo_binLer.read((char*)&pos1_atlet, sizeof(jogador_string));
    arquivo_binLer.seekg(pos2_bin);
    arquivo_binLer.read((char*)&pos2_atlet, sizeof(jogador_string));
    // trocar
    arquivo_binLer.seekg(pos1_bin); // buscar a posicao 1
    arquivo_binLer.write((char*)&pos2_atlet, sizeof(jogador_string));
    arquivo_binLer.seekg(pos2_bin); // buscar a posicao 2
    arquivo_binLer.write((char*)&pos1_atlet, sizeof(jogador_string));
    arquivo_binLer.close();
}
int retorna_tamanho() {
    arquivo_binLer.open("data_athlete_game.bin", ios::binary | ios::in | ios::out);
	int tam;
	arquivo_binLer.seekg (0, ios::end);
	tam = arquivo_binLer.tellg();
	arquivo_binLer.seekg (0, ios::beg);
    arquivo_binLer.close();
    return tam;
}

void inserir_atleta(jogador_string meuJgdr, int pos){
	arquivo_binLer.open("data_athlete_game.bin", ios::binary | ios::in | ios::out);
    pos = pos *(sizeof(jogador_string) + 1);
	long long i = 2;
	long long pos_anterior = 0;
	jogador_string copia;
	//inserir na ultima posicao
	int tam = retorna_tamanho()-(sizeof(jogador_string)*i +i)+sizeof(jogador_string)+1;
	while( tam != pos){
	// ir copiando e colando os arquivos de trás para frente
		arquivo_binLer.seekg(retorna_tamanho()-(sizeof(jogador_string)*i +i)); // penultima posicao
		arquivo_binLer.read((char*) &copia, sizeof(jogador_string));
		arquivo_binLer.seekg(retorna_tamanho()-pos_anterior);
		arquivo_binLer.write((char*) &copia, sizeof(jogador_string)) << endl;
		arquivo_binLer.seekg(retorna_tamanho()-((sizeof(jogador_string)*i +i)));
		arquivo_binLer.write((char*) &meuJgdr, sizeof(jogador_string)) << endl;
		pos_anterior = sizeof(jogador_string)*i +i;
		tam = retorna_tamanho()-(sizeof(jogador_string)*i +i)+sizeof(jogador_string)+1;
		i++;
	}
    arquivo_binLer.seekg(0);
    arquivo_binLer.close();
}
int main() {

	conversao(); // Chamar p/ converter arquivo csv -> bin
	
    cout << "Dados de atletas - arqBinario a Opcao:\n" // inicio menu
         << "i - inserir atleta em nova posicao\n"
         << "v - visualizar os registros entre 2 posicoes\n"
         << "a - alterar dados de um registro em uma posicao\n"
		 << "p - imprimir todos os registros\n"
         << "t - trocar registros de posicao\n"
         << "s - para sair do programa" << endl;

    char opcaoDoMenu;
	jogador_string meuJgdr;
	int pos, pos1, pos2;
    cin >> opcaoDoMenu;
    char id_char[6];
    string *dados;
    dados = new string[6];
 
    while (opcaoDoMenu != 's') {
        switch(opcaoDoMenu) {
            case 'i' :
                cout << "inserir atleta: digite uma posicao " << endl; // inserir atleta em uma posicao especifica
                cin >> id_char; // posicao
                pos = atoi (id_char); // converte char pra int
				cout << "inserir: nome, time, jogos, ano, temporada." << endl;
				dados[0] = strcpy(meuJgdr.id, id_char);
                for(int j = 1; j < 6; j++){
					while(getline(cin, dados[j]))
					if(dados[j] != ""){
						break;
					}
				}
                meuJgdr = escritor(dados);
				inserir_atleta(meuJgdr, pos); // falta implementar a funcao de adicionar entre duas posicoes
                break;
 
            case 'v' :
                cout << "digite duas posicoes para listar os registros contidos " << endl;
                cin >> pos1;
                cin >> pos2;
                listar_atletas(pos1, pos2);
                break;
 
            case 'a' :
                cout << "digite a posicao cujo registro vai ser alterado";
                cin >> id_char;
                pos = atoi (id_char); // converter para inteiro;
                cout << "inserir NOVOS: id, nome, time, jogos, ano, temporada." << endl;
                for(int j = 0; j < 6; j++){
	                while(getline(cin, dados[j])){
						if(dados[j] != ""){
							break;
						}
					}
				}
				meuJgdr = escritor(dados);
				alterar_registro(meuJgdr, pos);
				break;
			case 'p' :
				imprimir_registros();
				break;
			case 't' :
				cout << "digite duas posicoes para trocar os registros de posicao";
				cin >> pos1;
				cin >> pos2;
				trocar_atletas(pos1, pos2);
				break;
			case 's' : // não faz nada
				break;

			default:
				cout << "Opção invalida!" << endl;
				break;
 
		}
		cout << "Dados de atletas - arqBinario a Opcao:\n"
		<< "i - inserir atleta em nova posicao\n"
		<< "v - visualizar os registros entre 2 posicoes\n"
		<< "a - alterar dados de um registro em uma posicao\n"
		<< "p - imprimir todos os registros\n"
		<< "t - trocar registros de posicao\n"
		<< "s - para sair do programa" << endl;
		cin >> opcaoDoMenu;
	}
	return 0;
	
}
