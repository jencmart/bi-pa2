#include <iostream>
#include <cstdlib>
#include <ostream>

using namespace std;

class CFraction {
    int m_num, m_denom;
    void Reduce();

public:
    CFraction(int num = 0, int denom = 1);

    friend std::ostream & operator << (std::ostream & os, CFraction x);

    bool IsEqual(CFraction r) const; // == rovnost
    CFraction Difference(CFraction r) const; // -  rozdil
    CFraction Quotient(CFraction r) const; // /  podil
};

int GCD (int l, int r){
    int rem = l % r;
    while (rem != 0) { l = r; r = rem; rem = l % r; }
    return r;
}



CFraction::CFraction(int num, int denom) : m_num(num), m_denom(denom) { Reduce(); }

void CFraction::Reduce() {
    int gcd  = GCD(m_num, m_denom);
    m_num /= gcd;
    m_denom /= gcd;
}

bool CFraction::IsEqual(CFraction r) const {
    return m_num == r.m_num && m_denom == r.m_denom ;
}

CFraction CFraction::Difference(CFraction r) const {
    return CFraction(m_num - r.m_num, m_denom - r.m_denom);
}

CFraction CFraction::Quotient(CFraction r) const {
    return CFraction(m_num * r.m_denom , m_denom * r.m_num);
}

std::ostream &operator<<(std::ostream &os, CFraction x) {
    os << x.m_num << " / " << x.m_denom;
    return os;
}

int main() {
    CFraction a(3,-5), b(-5,9), c;
    cout << "a= " << a << ", b = " << b << endl;
    c = a.Quotient (CFraction (9,2)).Difference (b);
    cout << "c = (3/-5) / (9/2) - (-5/9) = " << c << endl;
    cout << boolalpha << c.IsEqual (CFraction (19, 45)) << endl;
    return 0;
}