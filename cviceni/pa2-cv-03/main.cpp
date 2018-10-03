#include <stdlib.h>
#include <iostream>

using namespace std;

#include "fronta.h"

int main() {
    Fronta kladna, zaporna;
    int cislo;

    cout << "zadejte radu celych cisel zakoncenou nulou" << endl;
    cin >> cislo;

    while (cislo) {
        if (cislo > 0) kladna.vloz(cislo);
        else zaporna.vloz(cislo);
        cin >> cislo;
    }

    kladna.print();
    zaporna.print();

    cout << "kladna cisla:" << endl;
    while (!kladna.jePrazdna() ) {
        cislo = kladna.odeber();
        cout << cislo << ' ';
    }

    cout << "\nzaporna cisla:" << endl;
    while (!zaporna.jePrazdna()) {
        cislo = zaporna.odeber();
        cout << cislo << ' ';
    }

    cout << endl;

    return 0;
}
