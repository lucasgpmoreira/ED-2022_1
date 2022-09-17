#include <iostream>

using namespace std;

// Classe fila circular
class FilaCircular {
private:
    int* fila;
    int inicio;
    int fim;
    int tamanho;
    int tamanhoMaximo;
public:
    FilaCircular(int tamanhoMaximo);
    ~FilaCircular();
    void enfileirar(int elemento);
    void desenfileirar();
    void imprimeAtributos();
};

FilaCircular::FilaCircular(int tamMax) {
    fila = new int[tamanhoMaximo];
    inicio = 0;
    fim = 0;
    tamanho = 0;
    tamanhoMaximo = tamMax;
    for (int i = 0; i < tamMax; i++) {
        fila[i] = 0;
    }
}

FilaCircular::~FilaCircular() {
    delete[] fila;
}

void FilaCircular::enfileirar(int elemento) {
    if (tamanho < tamanhoMaximo) {
        if (tamanho == 0) {
            fila[tamanho] = elemento;
            tamanho++;
        } else if (tamanho > 0 and fim == tamanhoMaximo - 1) {
            fim = 0;
            fila[fim] = elemento;
            tamanho++;
        } else if (tamanho > 0 and not(fim == tamanhoMaximo - 1)) {
            fila[tamanho] = elemento;
            fim = tamanho;
            tamanho++;
        }
    } else {
        cout << "Fila cheia" << endl;
    }
}

    void FilaCircular::desenfileirar() {
        int elementoRetorno;
        if (inicio < fim) { // se inicio for menor que fim, apenas retorna o elemento do inicio
            elementoRetorno = fila[inicio];
            inicio++;
            tamanho--;
            cout << elementoRetorno << endl;
        } else if (inicio > fim and inicio == tamanhoMaximo - 1) { //se inicio for igual ao tamanho maximo - 1, entao o inicio volta para o inicio da fila
            elementoRetorno = fila[inicio];
            inicio = 0;
            tamanho--;
            cout << elementoRetorno << endl;
        } else if (inicio > fim and not(inicio == tamanhoMaximo - 1)) { //se inicio nao for igual ao tamanho maximo - 1, entao o inicio incrementa
            elementoRetorno = fila[inicio];
            inicio++;
            tamanho--;
            cout << elementoRetorno << endl;
        } else if (inicio == fim) { //se inicio e fim forem iguais retorna inicio e fim para 0 e tamanho diminui
            elementoRetorno = fila[inicio];
            inicio = 0;
            fim = 0;
            tamanho--;
            cout << elementoRetorno << endl;
        }
    }

    //tamanho=3 capacidade=3 inicio=0 fim=2
    void FilaCircular::imprimeAtributos() {
        cout << "tamanho=" << tamanho << " " << "capacidade=" << tamanhoMaximo << " "
            << "inicio=" << inicio << " " << "fim=" << fim << endl;
        for (int i = 0; i < tamanho; i++) {
            cout << fila[i] << " ";
        }
    }

    /*
    Depois, o programa lê códigos de comandos a executar. Sempre um caractere identificando o comando seguido dos parâmetros necessários para executar o comando, se houverem. Os códigos de comandos são:

    t - para terminar a execução do programa
    e - para enfileirar um valor - seguido do valor (número inteiro)
    d - para desenfileirar um valor
    i - para escrever as informações da fila (atributos e conteúdo)
    */
    int main() {
        int tamanhoMaximo;
        cin >> tamanhoMaximo;
        FilaCircular fila(tamanhoMaximo);
        char comando;
        do {
            cin >> comando;
            switch (comando) {
            case 't':
                break;
            case 'e':
                int enfileirar;
                cin >> enfileirar;
                fila.enfileirar(enfileirar);
                break;
            case 'd':
                fila.desenfileirar();
                break;
            case 'i':
                fila.imprimeAtributos();
                /*for (int i = 0; i < fila.tamanhoFila(); i++) {
                    int elemento = fila.desenfileirar();
                    cout << elemento << " ";
                    fila.enfileirar(elemento);
                }*/
                cout << endl;
                break;
            }
        } while (comando != 't');
        return 0;
    }