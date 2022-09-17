#include <iostream>
#include <cstdlib>
using namespace std;

typedef int Dado; // Typedef permite criar novos tipos a partir de outros (criamos basicamente um "apelido" para int)

class noh{
  friend class lista;
  private:
    const Dado dado; // poderia ser outro tipo de vari�vel (� const para n�o ser alterado)
    noh* proximo;

  public:
    noh (Dado d = 0); // Cosntrutor padr�o
};

noh::noh(Dado d) : dado(d){
  proximo = NULL;
}

// lista dinamicamente encadeada
class lista {
  private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos (); // remove todos os elementos da lista
    void imprimeReversoAux(noh* umNoh); // imprime reverso a partir de um n� -> exemplo de uso de recurs�o

  public:
    // construtores e destrutor
    lista();
    lista(const lista& umalLista);   // construtor de c�pia
    ~lista();
    // sobrecarga do operador de atribui��o
    lista& operator=(const lista& umalista);
    // inser��o, remo��o e procura
    inline void insere(Dado dado);
    void insereNoFim(Dado dado);
    void insereNoInicio(Dado dado);
    void insereNaPosicao(int posicao, Dado dado);
    int procura(Dado valor); // retorna a posi��o do n� com determinado valor
    // m�todos adicionais (impress�o, vazia)
    void imprime();
    void imprimeReverso();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
};

// constroi uma lista inicialmente vazia
lista::lista(){
  tamanho = 0;
  primeiro = NULL;
  ultimo = NULL;
}

// construtor de copia (Insere no fim tudo que veio da outra lista)
lista::lista(const lista& umalista){   // umalista = lista que sera copiada
  tamanho = 0;
  primeiro = NULL;
  ultimo = NULL;

  // percorre a lista recebida como parametro, copiando os dados
  noh* aux = umalista.primeiro;
  while (aux != NULL) {
    insereNoFim(aux->dado);
    aux = aux->proximo;
  }
}

// destrutor da lista (chama funcao privada auxiliar)
lista::~lista(){
  removeTodos();
}

// remove todos os elementos da lista
void lista::removeTodos(){
  noh* aux = primeiro;
  noh* temp;

  while(aux != NULL){
     temp = aux;
     aux = aux->proximo;
     delete temp;
  }
  // redirecionando ponteiros (Pois agora tudo foi deletado)
  tamanho = 0;
  primeiro = NULL;
  ultimo = NULL;
}

lista& lista::operator=(const lista& umalista){
  // limpa a lista atual
  removeTodos();
  // percorre a lista recebida como par�metro, copiando os dados
  noh* aux = umalista.primeiro;
  while (aux != NULL){
    insereNoFim(aux->dado);
    aux = aux->proximo;
  }
  return *this;   // Retorna a refer�ncia do objeto atual
}

// insere por padr�o no final da lista
void lista::insere(Dado dado) {
  insereNoFim(dado);
}

void lista:: insereNoFim(Dado dado) {
  // * primeiro criamos o novo n�
  noh* novo = new noh(dado);

  // * agora inserimos o n� na lista
  // se a lista estiver vazia, inserimos o primeiro n�
  if(vazia()){ // ou (primeiro == NULL) ou (tamanho ==0 )
    primeiro = novo;
    ultimo = novo;
  }
  else { // j� tem elementos na lista, insere no final
    ultimo->proximo = novo;
    ultimo = novo;
  }
  tamanho++;
}

// insere no in�cio da lista
void lista::insereNoInicio(Dado dado) {
  // * primeiro criamos o novo n�
  noh* novo = new noh(dado);

  // * agora inserimos o n� na lista
  // se a lista estiver vazia, inserimos o primeiro n�
  if( vazia()){ // ou (primeiro == NULL) ou (tamanho == 0)
    primeiro = novo;
    ultimo = novo;
  }
  else{ // j� tem elementos na lista, insere no inicio
    novo->proximo = primeiro;
    primeiro = novo;    // Primeiro (da lista mesmo) aponta para esse novo
  }
  tamanho++;
}

// insere em uma determinada posi��o da lista
void lista::insereNaPosicao(int posicao, Dado dado){
  // * primeiro criamos o novo n�
  noh* novo = new noh(dado);

  // * agora inserimos o n� na lista
  // verificamos antes se � poss�vel inserir na posi��o
  if ((posicao <= tamanho) and (posicao >= 0)) {
    if ( vazia()){ // ou (primeiro == NULL) ou (tamanho ==0))
      primeiro = novo;
      ultimo = novo;
    }
    else if (posicao == 0){ // Insere no In�cio
      novo-> proximo = primeiro;
      primeiro = novo;
    }
    else if (posicao == tamanho){ // Insere no Fim
      ultimo->proximo = novo;
      ultimo = novo;
    }
    else{ // insere no meio da lista
      noh* aux = primeiro;
      int posAux = 0;

      // chegando na posicao da lista
      while ( posAux < (posicao-1) ) {   // Enquanto n�o chegar na posi��o ANTERIOR � que quer inser��o
        aux = aux->proximo;
        posAux++;
      }
      novo->proximo = aux->proximo;
      aux->proximo = novo;
    }
    tamanho++;
  }
  else {
  cerr << "Posi��o Inexistente!" << endl;
  exit(EXIT_FAILURE);
  }
}

int lista::procura(Dado valor){
  noh* aux = primeiro;
  int posAux = 0;
  while ((aux != NULL) and (aux->dado != valor)){
    posAux++;
    aux = aux->proximo;
  }
  if(aux == NULL){
    posAux = -1;  // -1 = n�o encontrado
  }
  return posAux;
}

//m�todo b�sico que *percorre* uma lista, imprimindo seus elementos
// poderia percorrer fazendo outra a��o (multiplicando valores, por exemplo)
void lista:: imprime(){
  noh* aux = primeiro;

  while (aux != NULL) {
    cout << aux->dado << ' ';
    aux = aux->proximo;
  }
  cout << endl;
}

// Para imprimir REVERSO, usaremos PILHA DE RECURS�O
// Para isso, precisa de uma fun��o auxiliar
void lista::imprimeReverso(){
  imprimeReversoAux(primeiro);
  cout << endl;
}

void lista::imprimeReversoAux(noh* umNoh){
  if(umNoh != NULL) {
    imprimeReversoAux(umNoh->proximo);  // Cada n� chama a impress�o do pr�ximo antes de se imprimir
    cout << umNoh->dado << ' ';
  }
}

// Verifica se a lista est� vazia
inline bool lista::vazia(){
  return (primeiro == NULL);
}

void lista::removeNoFim(){
  if(vazia()){ // verifica lista vazia
    cerr << "Remo��o em lista vazia" << endl;
    exit(EXIT_FAILURE);
  }

  noh* aux =  primeiro;
  noh* anterior;
  while(aux->proximo != NULL){  // Aux para no ULTIMO
    anterior = aux;
    aux = aux->proximo;
  }
  delete ultimo;  // apagou aquele que aux aponta
  anterior -> proximo = NULL;
  ultimo = anterior;

  if(vazia()){  // Verifica se a lista ficou vazia com isso
    primeiro = NULL;
  }
  tamanho--;
}

void lista::removeNoInicio(){
  if(vazia()){ // verifica lista vazia
    cerr << "Remo��o em lista vazia" << endl;
    exit(EXIT_FAILURE);
  }

  noh* removido = primeiro;
  primeiro = primeiro -> proximo;
  delete removido;
  tamanho--;

  // se a lista ficou vazia
  if(tamanho == 0){
    ultimo = NULL;
  }
}

// CASO FOR FAZER REMO��O DE UM VALOR, USAR O M�TODO "BUSCA()" E RESGUARFAR ANTES DE DELETAR (assim como na remo��o no in�cio, salva o anterior)

int main() {
  lista minhalista;

  cout << "*** Teste da Lista ***" << endl;
  cout << "Quantidade de walores a inserir: " << endl;

  int valor;
  int num;
  cin >> num;

  for (int i = 0; i < num; i++) {
    cin >> valor;
    minhalista.insere(valor);
  }
  minhalista.imprime();

  minhalista.insereNoInicio(18);
  minhalista.insereNaPosicao(3,25);
  minhalista.imprime();
  minhalista.imprimeReverso();

  cout << minhalista.procura(0) << endl;
  cout << minhalista.procura(50) << endl;
  cout << minhalista.procura(12) << endl;

  // construtor de c�pia
  cout << "Sobrecarga do construtor de c�pia" << endl;    // Copia a lista
  lista outraLista(minhalista);
  outraLista.imprime();
  outraLista.imprimeReverso();

  // sobrecarga de operador de atribui��o
  cout << "Sobrecarga do operador de atribui��o" << endl;   // Copia a lista
  lista maisUmaLista;   // Cria uma nova lista
  maisUmaLista = outraLista;    // Essa nova lista Recebe o conte�do de outra lista

  maisUmaLista.imprime();
  maisUmaLista.imprimeReverso();

  // Remover no fim alguns elementos
  cout << "Ap�s remocao no fim:" << endl;
  maisUmaLista.removeNoFim();
  maisUmaLista.removeNoFim();

  maisUmaLista.imprime();
  maisUmaLista.imprimeReverso();

  // Remover no fim alguns elementos
  maisUmaLista.removeNoInicio();
  maisUmaLista.removeNoInicio();

  maisUmaLista.imprime();
  maisUmaLista.imprimeReverso();

  return 0;
}
