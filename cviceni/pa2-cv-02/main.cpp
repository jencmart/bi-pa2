#include <iostream>
#include "complex.h"

using namespace std ;

int main(void) {

    Complex x(1,1), y(2,2), z;
    float a;
    cout << "x="; x.print(); cout << endl;
    cout << "y="; y.print(); cout << endl;
    z = x.add(y);
    cout << "x+y="; z.print(); cout << endl;
    z = x.diff(y);
    cout << "x-y="; z.print(); cout << endl;
    a = x.abs();
    cout << "abs(x)=" << a << endl;
    return 0;


}
