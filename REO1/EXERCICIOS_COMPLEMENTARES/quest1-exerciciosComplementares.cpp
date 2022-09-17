#include <iostream>

using namespace std;

enum tipo { fib, fet, ric };

class FFR {
private:
    tipo meuTipo;
    int termo1, termo2;
    long calculaFib(int n);
    long calculaFet(int n);
    long calculaRic(int n);
    long* calculaSeqFib(int n);
    long* calculaSeqFet(int n);
    long* calculaSeqRic(int n);
public:
    FFR(tipo t); // construtor para Fibonacci
    FFR(tipo t, int t1, int t2); // construtor para Fettuccine e Ricci
    long calculaTermo(int n); //calcula o n-esimo termo
    long* calculaSequencia(int n); // retorna um vetor com os 
    // n primeiros termos
};

FFR::FFR(tipo tipoT) {
    meuTipo = tipoT;
}

FFR::FFR(tipo tipoT, int t1, int t2) {
    meuTipo = tipoT;
    termo1 = t1;
    termo2 = t2;
}

long FFR::calculaFib(int termo) {
    if (termo <= 1)
        return termo;
    return calculaFib(termo - 1) + calculaFib(termo - 2);
}

long FFR::calculaFet(int termo) {
    long num1 = termo1, num2 = termo2;
    long valorTermo;
    for (int i = 0; i < (termo - 2); i++) {
        if (i % 2 == 0)
            valorTermo = num2 - num1; //para i par.	
        else
            valorTermo = num2 + num1; //para i impar
        num1 = num2;
        num2 = valorTermo;
    }
    return valorTermo;
}


long FFR::calculaRic(int termo) {
    long num1 = termo1, num2 = termo2;
    long valorTermo;
    cout << num1 << " " << num2 << " ";
    for (int i = 0; i < (termo - 2); i++) {
        valorTermo = num2 + num1;
        num1 = num2;
        num2 = valorTermo;
        cout << valorTermo << " ";
    }
    return valorTermo;
}


long FFR::calculaTermo(int termo) {
    long resultado = -1;
    if (meuTipo == fib)
        resultado = calculaFib(termo);
    else if (meuTipo == fet)
        resultado = calculaFet(termo);
    else
        resultado = calculaRic(termo);
    return resultado;
}

long* FFR::calculaSequencia(int tam) {
    long* resultado;
    resultado = new long[tam];
    for (int i = 0; i < tam; i++) {
        if (meuTipo == fib)
            resultado[i] = calculaFib(i);
        else if (meuTipo == fet)
            resultado[i] = calculaFet(i);
        else
            resultado[i] = calculaRic(i);
    }
    return resultado;
}

int main() {
    int opcDeSerie;
    char opcDeCalculo;
    int termo;
    tipo tipoEscolhido;
    do {
        cout << "Escolha qual tipo de serie: [1] = Fibonacci | [2] = Fettuccine | [3] = Ricci \n[4] = Sair" << endl;
        cin >> opcDeSerie;
        if (opcDeSerie != 4) {
            cout << "-> Para calcular o n-esimo termo entre com [A]\n->Para mostrar toda a serie ate o termo n entre com [B] " << endl;
            cin >> opcDeCalculo;
            switch (opcDeSerie) {
            case 1:
            {
                tipoEscolhido = fib; //pergunta: tipo inteiro não pode ser atribuido a uma entidade do tipo "tipo"
                FFR fibo(tipoEscolhido);
                if (opcDeCalculo == 'A' or opcDeCalculo == 'a') {
                    cout << "Qual termo deseja calcular?" << endl;
                    cin >> termo;
                    cout << "O numero na sequencia fibonacci nessa posicao e " << fibo.calculaTermo(termo) << endl
                        << "======================================================================" << endl;
                } else if (opcDeCalculo == 'B' or opcDeCalculo == 'b') {
                    int tam;
                    cout << "Quantos termos deseja mostrar? ";
                    cin >> tam;
                    cout << "A sequencia e: ";
                    long* vet = fibo.calculaSequencia(tam);
                    for (int i = 0; i < tam; i++) {
                        cout << "[" << *vet << "] ";
                        vet++;
                    }
                    cout << endl;
                }
                break;
            }
            case 2:
            {
                tipoEscolhido = fet; //pergunta: tipo inteiro não pode ser atribuido a uma entidade do tipo "tipo"
                int t1, t2;
                cout << "Quais serao os termos iniciais da sequencia?" << endl;
                cin >> t1 >> t2;
                FFR fetu(tipoEscolhido, t1, t2);
                if (opcDeCalculo == 'A' or opcDeCalculo == 'a') {
                    cout << "Qual termo deseja calcular?" << endl;
                    cin >> termo;
                    cout << "O numero na sequencia fettuccine nessa posicao e " << fetu.calculaTermo(termo) << endl
                        << "======================================================================" << endl;
                }
                break;
            }
            case 3:
            {
                tipoEscolhido = ric; //pergunta: tipo inteiro não pode ser atribuido a uma entidade do tipo "tipo"
                int t1, t2;
                cout << "Quais serao os termos iniciais da sequencia?" << endl;
                cin >> t1 >> t2;
                FFR ricc(tipoEscolhido, t1, t2);
                if (opcDeCalculo == 'A' or opcDeCalculo == 'a') {
                    cout << "Qual termo deseja calcular?" << endl;
                    cin >> termo;
                    cout << "O numero na sequencia fettuccine nessa posicao e " << ricc.calculaTermo(termo) << endl
                        << "======================================================================" << endl;
                }
                break;
            }
            }
        }
    } while (opcDeSerie != 4);

    return 0;
}
