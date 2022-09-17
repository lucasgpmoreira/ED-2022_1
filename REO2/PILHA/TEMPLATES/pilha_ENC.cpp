
#include <iostream>
#include <string>
using namespace std;

//implement a stack class
class stack {
public:
    stack();
    ~stack();
    void emp(int);
    int desemp();
    int espia();
    bool estaVazia();
    void imprimePilha();
private:
    struct Noh {
        int data;
        Noh *next;
    };
    Noh *top;
};

stack::stack() {
    top = NULL;
}

stack::~stack() {
    while (top != NULL) {
        Noh *temp = top;
        top = top->next;
        delete temp;
    }
}

void stack::emp(int data) {
    Noh *temp = new Noh;
    temp->data = data;
    temp->next = top;
    top = temp;
}

bool stack::estaVazia() {
    return top == NULL;
}

int stack::desemp() {
    if (estaVazia()) {
        cout << "stack is empty" << endl;
        return -1;
    }
    Noh *temp = top;
    top = top->next;
    int data = temp->data;
    delete temp;
    return data;
}

int stack::espia() {
    if (estaVazia()) {
        cout << "stack is empty" << endl;
        return -1;
    }
    return top->data;
}

void stack::imprimePilha() {
    Noh *temp = top;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    
}