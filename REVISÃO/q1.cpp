#include <iostream>

using namespace std;

bool ehPrimo(int num) {
    int numDivs = 0;
    for (int i = 1; i <= num; i++) {
        if (num % i == 0)
            numDivs++;
    }
    if (numDivs == 2) {
        return true;
    }
    return false;
}

int main() {
    int num;
    for (int i = 0; i < 9; i++) {
        cin >> num;
        if (ehPrimo(num)) {
            cout << num << " " << i << endl;
        }
    }
    return 0;
}