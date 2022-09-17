#include <iostream>
#include <fstream>

using namespace std;

int main() {
    fstream file;
    file.open("my_file.txt", ios_base::out | ios_base::in);  // will not create file
    if (file.is_open()) {
        cout << "Warning, file already exists, proceed?";
        if (cin.get() == 'y') {
            file.close();
            // throw something
            cout << "File closed" << endl;
        }
    } else {
        file.clear();
        cout << "hello" << endl;
        /*
        file.open("my_file.txt", ios_base::out);  // will create if necessary
        */
    }
}