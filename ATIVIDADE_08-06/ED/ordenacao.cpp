/*
Grupo 4:
 - Beatriz Fernandes Teixeira
 - Dênis de Souza Cordeiro
 - Ronald de Souza Galdino
 * 
Ordenação:  Name (1º), Id (2º), crescente.
----------- data_athlete_game.7z ------------

*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include "conversao.cpp"
#include <cmath>

// EXECUTAR ESSE ARQUIVO PARA ORDENAR!!!!!!
using namespace std;

fstream arquivo_binLer;
ofstream arquivoOrig;

struct arquivo { // Estrutura para gerenciar a escrita e leitura de arquivos temporários
	fstream f;  // Recebe um arquivo temporário
	jogador_string *buffer; // Alocará memória para armazenar os registros já totalmenteordenados.
	int maxReg, pos;
	//bool estado; 
	int tamanho, posBin; // Tamanho do arquivo. E posBin é a posição no arquivo após a escrita de registros no arquivo
};

int retornaTamanhoarq(char *nome) { // Retorna o tamanho do arquivo em bytes
	arquivo_binLer.open(nome, ios::binary | ios::in);
	int tam;
	arquivo_binLer.seekg (0, ios::end); // Posiciona no início do arquivo
	tam = arquivo_binLer.tellg();       // Armazena o tamanho;
	arquivo_binLer.seekg (0, ios::beg); // Posiciona no fim do arquivo
	arquivo_binLer.close();
	return tam;
}

// Retorna a primeira letra do nome de cada jogador
char retornaPrimLetra(string nome){ 
	int i = 0;
	int valorChar = (int) nome[0]; // Armazenar o valor em ASCII do primeiro caractere
	if (valorChar <= 34){       // 34 é o valor em ASCII que define as ASPAS
		while (valorChar <= 34){ 
			i++;                // Percorre o nome até encontrar um caractere que seja uma letra
			valorChar = nome[i];
		}
		return toupper(nome[i]); // Retorna a letra em maiúsculo
	}

	return toupper(nome[i]); // Se o primeiro caractere é uma letra, retorna em maiúsculo
}

// Algoritmo que ordena os arquivos temporários
void intercala(jogador_string vetJogador[], int inicio, int meio, int fim) { 
	int i = inicio, j = meio+1;
	int tamanho = fim - inicio + 1;
	char letraUm, letraDois;
	jogador_string auxVetJgdr[tamanho];  // vetor auxiliar
	for (int k=0; k < tamanho; k++) {
		if ((i <= meio) and (j <= fim)){
			letraUm = retornaPrimLetra(vetJogador[i].nome);  // Armazena as primeiras letras de dois registros
			letraDois = retornaPrimLetra(vetJogador[j].nome);
			if (letraUm < letraDois){ // Comparação entre letras de nomes de jogadores e os classifica em ordem alfabética
				auxVetJgdr[k] = vetJogador[i]; 
				i++; 
			} 
			else if (letraUm == letraDois){ // A primeira letra é igual
				if(vetJogador[i].id <= vetJogador[j].id){ // Verificar o segundo critério de ordenação, o ID.
					auxVetJgdr[k] = vetJogador[i];  
					i++;
				}
				else {
					auxVetJgdr[k] = vetJogador[j]; 
					j++; 
				}
			}
			else {
				auxVetJgdr[k] = vetJogador[j]; 
				j++; 
			}
	}
		else if (i > meio){
			auxVetJgdr[k] = vetJogador[j];
			j++;
		}else {
			auxVetJgdr[k] = vetJogador[i];
			i++;
		}
	}

	for (int k=0; k < tamanho; k++){
		vetJogador[inicio + k] = auxVetJgdr[k]; // Copia o vetor de jogadores
	}
}

// Aplica mergeSort ao vetor de Jogadores usando a função intercala
void mergesort(jogador_string vetJogador[], int inicio, int fim){ 
	int meio;
	meio = (inicio + fim)/2;
	if (inicio < fim) {
		meio = (inicio + fim)/2;
		mergesort(vetJogador, inicio, meio);
		mergesort(vetJogador, meio+1, fim);
		intercala(vetJogador,inicio,meio,fim);
	}
}

// Auxiar de MergeSort: Define início e fim.
void mergesortAux(jogador_string vetJogador[], int total){
	int inicio = 0, fim = total -1;
	mergesort(vetJogador, inicio, fim);
}
// Última etapa da ordenação: salva cada registro no arquivo binário FINAL. 
void salvaOrdenado(char *nome, jogador_string vetJogador[], int tam, bool primeiro){
	if (primeiro == false){ // Controla se já foi escrito o primeiro registro, para que os próximos sejam acrescentados no fim
		arquivoOrig.open("data_athlete_game.bin", ios::binary | ios::out | ios::app); // ios::append para acrescentar.
		for (int i=0; i < tam; i++){
			arquivoOrig.write((char*) (&vetJogador[i]), sizeof(jogador_string)) << endl;
		}
	}
	else { // Escreve o primeiro registro
		arquivoOrig.open("data_athlete_game.bin", ios::binary | ios::out); 
		for (int i=0; i < tam; i++){
			arquivoOrig.write((char*) (&vetJogador[i]), sizeof(jogador_string)) << endl;
		}
	}  
	arquivoOrig.close(); 
    
}

// Salva os registros em arquivos TEMPORÁRIOS
void salvaArquivo(char *nome, jogador_string vetJogador[], int tam, int linha){ 
    //int i;
	if (linha != 1){
		fstream arquivoTemp;
		arquivoTemp.open(nome, ios::binary | ios::out);
		for (int i=0; i < tam-1; i++){
			arquivoTemp.write((char*) (&vetJogador[i]), sizeof(jogador_string)) << endl;
		}
		if (linha == 0){
		arquivoTemp.write((char*) (&vetJogador[tam-1]), sizeof(jogador_string));
		}
		else{
			arquivoTemp.write((char*) (&vetJogador[tam-1]), sizeof(jogador_string)) << endl ;
		}
		arquivoTemp.close();
	}
}

// Lê o arquivo binário já convertido e armazena os registros em N arquivos binários: quebra o arquivo binário em N partes.
int geraArquivosOrdenados (string nome, int N){ // N é o numero máximo de registros por arquivo temporário.
	int cont = 0, total = 0, i=0;
	jogador_string vetJogador[N]; 
	char novo[20];
	char nomeOrig[36] = "data_athlete_game.bin";
	int tamanho = retornaTamanhoarq(nomeOrig);
	arquivo_binLer.open(nome, ios::binary | ios::in);
	while(i < tamanho){
		arquivo_binLer.seekp(i); // Função para percorrer o arquivo lendo e armazenando registros.
		arquivo_binLer.read((char*) (&vetJogador[total]), sizeof(jogador_string));
		total++;
		if (total == N){ // 
			cont++;         // Conta a quantidade de arquivos criados.
			sprintf(novo, "Temp%d.bin", cont); // Define os nomes dos arquivos temporários
			mergesortAux(vetJogador, total);
			salvaArquivo(novo, vetJogador, total, 0);
			total = 0;
		}
		i= i + 126; // Posiciona para o próximo registro: 126 = Tamanho da struct jogador_string
	}
	if (total > 0){ // Se restar registros no arquivo original
		cont++; 
		sprintf(novo, "Temp%d.bin", cont); // Cria mais arquivos temporários com o restante dos registros
		mergesortAux(vetJogador, total);
		salvaArquivo(novo, vetJogador, total, 0);
	}
	arquivo_binLer.close();
	return cont; // Retorna a quantidade de arquivos criados.
}

void preencheBuffer (struct arquivo* arq, int K){ // K guarda o número máximo de registros por buffer.
	int posBin = arq->posBin;   // Pos do arq binário: para controlar os prox registros a serem lidos e armazenados no buffer
	jogador_string registroJgdr;
	if (not (arq->f.is_open())){
		return;
	}
	arq->pos = 0;
	arq->maxReg = 0;
	for (int i=0; i <K; i++){  // Preenche o buffer com K arquivos
		if(posBin <= arq->tamanho){  // Verifica se chegou ao final do arquivo
		arq->f.seekp(posBin);
			arq->f.read((char*) &registroJgdr, sizeof(jogador_string));
			arq->buffer[arq->maxReg] = registroJgdr;
			arq->maxReg++; // Incrementa a última posição válida do buffer
		}
		else{ 
			arq->f.close(); // Fecha o arquivo porque o a posição atual é maior que o tamanho do arquivo.
		}
		posBin = posBin + 126; // Direciona para o próximo registro
	}
	arq->posBin = posBin; // Atualiza a posicao no arquivo binário. 
}

// Compara todos os primeiros registros de cada arquivo e obtém o MENOR, conforme a ordem alfabética ou ID.
int procuraMenor(struct arquivo* arq, int numArqs, int K, jogador_string *menor){
	int i, idx = -1; // idx controla a posição de cada registro no buffer
	char letraUm, letraDois; 
	for (i=0; i<numArqs; i++){ // Percorre a primeira posição de todos os arqs temporários
		if (arq[i].pos < arq[i].maxReg){ // Compara a posição atual e a última no Buffer.
			if (idx == -1){
				idx = i;
			}
			else{
				letraUm = retornaPrimLetra(arq[i].buffer[arq[i].pos].nome);   
				letraDois = retornaPrimLetra(arq[idx].buffer[arq[idx].pos].nome);               // Verifica o segundo critério: ID
				if (letraUm < letraDois or (letraUm == letraDois and arq[i].buffer[arq[i].pos].id < arq[idx].buffer[arq[idx].pos].id)){
					idx = i; // Salva a posição do registro no buffer
				}
			}
		}
	}
    
	if (idx != -1){ // Encontrou um nome menor
		*menor = arq[idx].buffer[arq[idx].pos]; // Atribui por referência o menor registro
		arq[idx].pos++; // Incrementa posição no arq p/ avançar para o próximo registro, já que esse será salvo
		if (arq[idx].pos == arq[idx].maxReg){ // Percorreu toda a quantidade de posições definidas pelo valor K.
			preencheBuffer(&arq[idx], K); // Preenche o menor no buffer
		}
		return 1;
	}
	else{
		return 0;
	}
}

void merge(string nome, int numArqs, int K){
	char novo[20];
	char novoNome [50] = "data_athlete_game.bin";
	int i=0;
	jogador_string *buffer = new jogador_string[K]; // Aloca memoria para o buffer, que armazena registros ordenados;
	struct arquivo *arq = new arquivo[numArqs]; // Armazena cada arquivo temporário
	for (i=0; i<numArqs; i++){
		sprintf(novo, "Temp%d.bin", i+1);
		arq[i].f.open(novo, ios::binary | ios::in); // Abre cada arquivo temporário criado
		arq[i].maxReg = 0;                          // Zera as posições atuais e última posição do arquivo
		arq[i].pos = 0;
		arq[i].tamanho = retornaTamanhoarq(novo); // Para limitar a escrita e leitura de dados, o tamanho é definido
		arq[i].posBin = 0;                          // Define qual registro, segundo sua posição binária, vai ser lido.
		arq[i].buffer = new jogador_string [K];     // Armazena os K registros ordenados de cada arquivo p/ serem escritos.
		preencheBuffer (&arq[i], K);
        
	}
	int qtdBuffer = 0;
	jogador_string menor;
	int quantRegistros = 0;
	bool primeiro = true;
	while (procuraMenor(arq, numArqs, K, &menor) == 1){ // Enquanto houver arquivos com registros, procura o menor e salva.
		buffer[qtdBuffer] = menor; // Passado por referência para a função.
		qtdBuffer++;
		if (qtdBuffer == K){
			salvaOrdenado(novoNome, buffer, K, primeiro);
			primeiro = false;
			qtdBuffer = 0;
			quantRegistros++;
		}
        
	}
	if (qtdBuffer != 0){ // Se ainda restaram registros, são salvos no 
		salvaOrdenado(novoNome, buffer, qtdBuffer, primeiro);
	}

	for (i=0; i<numArqs; i++){
		delete arq[i].buffer; // Libera memória dos buffers temporários criados.
	}

}

void mergeSortExterno(string nome){
	cout << "Ordenando..." << endl;
	char novo[22] = "data_athlete_game.bin" ;
	int N = 1000; 
	int numArqs = geraArquivosOrdenados(novo, N); // N = QUANTIDADE DE REGISTROS EM CADA ARQUIVO
	int k = 600; // Escolhemos dividir os buffers em 600 registros cada
	merge("data_athlete_game.bin", numArqs, k);
}


int main() {
	cout << "Convertendo arquivo csv em .bin..." << endl;
	conversao(); // Chamar p/ converter arquivo csv -> bin
	cout << "A conversao foi concluida. " << endl;
	mergeSortExterno("data_athlete_game.bin"); // Chamar mergeSortExterno para ordenar o arquivo binário
	cout << "Ordenacao concluida." << endl;        
}

