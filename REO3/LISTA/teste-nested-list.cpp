#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

struct module {

    string name;
    int note;
    struct module* next;

};
typedef struct module module;

struct student {
    string name;
    string adress;
    struct student* next;
    module* head;

};
typedef struct student student;

student* etudiant = NULL;

void addModule(string studentName, string subject, int note) {
    // searching student in the list..
    if (etudiant != NULL) {
        struct student* s = etudiant; //start of the list
        while (s && s->name == studentName)
            s = s->next;
        if (s != NULL) {
            // creating module...
            module* novo = new module;
            novo->name = subject;
            novo->note = note;
            novo->next = NULL;

            //adding module to the front of the module list of student s ...
            module* tmp = s->head;
            s->head = novo;
            novo->next = tmp;
        }
    }
}

void add_student(string name, string adress) {
    student* p = new student;
    p->name = name;
    p->adress = adress;
    p->next = NULL;

    if (etudiant == NULL) {
        etudiant = p;
    } else {
        struct student* q = etudiant;

        while (q->next != NULL) {
            q = q->next;
        }
        q->next = p;
    }
    addModule(p->name, "algo", 15);
}

int main() {
    add_student("A", "XYZ");
    addModule("A", "CS", 1);
    addModule("A", "MECH", 1);

    add_student("B", "PQR");
    addModule("B", "DAA", 1);
    addModule("b", "SE", 1);

    //printing the list...
    student* q = etudiant;
    while (q != NULL) {
        module* p = q->head;
        printf("%s -> ", q->name);
        while (p != NULL) {
            printf("%s ", p->name);
            p = p->next;
        }
        printf("\n");
        q = q->next;
    }
}