/*
/*
Implemente uma estrutura de dados do tipo pilha com as operações básicas de empilhar e desempilhar. Faça um método adicional que retorne o menor valor da pilha sem que haja quebra da estrutura e sem ordenar seus elementos. Faça um programa com suporte as seguintes operações:

e - empilhar um valor X passado como parâmetro.
d - desempilhar um valor, que deve ser impresso. Se a pilha estiver vazia, imprimir "VAZIA".
m - retornar o menor valor armazenado na pilha. Se a pilha estiver vazia, imprimir "VAZIA".
s - imprimir todos os valores armazenados na pilha e encerrar.
DICA: A solução utiliza duas pilhas: a pilha principal e uma pilha auxiliar para que haja o intercâmbio de elementos entre elas.
*/

#include <iostream>
#include <string>
using namespace std;

//implement a pilha class
class pilha {
public:
    pilha();
    ~pilha();
    void emp(int);
    int desemp();
    int espia();
    bool estaVazia();
    void imprimePilha();
private:
    struct Noh {
        int data;
        Noh* next;
    };
    Noh* top;
    int menorElemento;
};

pilha::pilha() {
    top = NULL;
    menorElemento = -1000;
}

pilha::~pilha() {
    while (top != NULL) {
        Noh* temp = top;
        top = top->next;
        delete temp;
    }
}

void pilha::emp(int data) {

    Noh* temp = new Noh;
    temp->data = data;
    temp->next = top;
    top = temp;
}

bool pilha::estaVazia() {
    return top == NULL;
}

int pilha::desemp() {
    if (estaVazia()) {
    } else {
        Noh* temp = top;
        top = top->next;
        int data = temp->data;
        delete temp;
        return data;
    }
}

int pilha::espia() {
    if (estaVazia()) {
        cout << "VAZIA" << endl;
        return -1;
    }
    return top->data;
}

void pilha::imprimePilha() {
    Noh* temp = top;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int retornaMenor(pilha& p) {
    //encontra menor elemento da pilha
    pilha aux;
    int outroDesemp;
    int menor = p.desemp();
    aux.emp(menor);
    while (!(p.estaVazia())) {
        outroDesemp = p.desemp();
        aux.emp(outroDesemp);
        if (menor > outroDesemp) {
            menor = outroDesemp;
        }
    }
    while (!(aux.estaVazia())) {
        p.emp(aux.desemp());
    }
    return menor;
}

int main() {
    char opcao;
    pilha p;

    do {
        cin >> opcao;
        switch (opcao) {
        case 'e':
            int valor;
            cin >> valor;
            p.emp(valor);
            break;
        case 'd':
            if (p.estaVazia()) {
                cout << "VAZIA" << endl;
            }
            cout << p.desemp() << endl;
            break;
        case 'm':
            cout << retornaMenor(p) << endl;
            break;
        case 's':
            p.imprimePilha();
            break;
        default:
            cout << "opcao invalida" << endl;
            break;
        }

    } while (opcao != 's');
    return 0;
}