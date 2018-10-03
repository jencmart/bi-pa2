#ifndef __PROGTEST__

#include <cstring>

//#include <cstdlib>
//#include <cstdio>
//#include <cctype>
//#include <climits>
#include <cmath>
#include <cfloat>
#include <cassert>
//#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <complex>
#include <vector>
#include <algorithm>
#include <memory>

#include <string>


using namespace std;
#endif /* __PROGTEST__ */



static string prom = "x";

class CPolynomial {
private:
    vector<double> m_data;

public:

    CPolynomial(vector<double> x) : m_data(x.size(), 0) {

        for(size_t i = 0; i < x.size();++i )
            m_data[i] = x[i];

    }; //muj spesl konstruktor

    vector<double> const getData() const { return m_data; }

    CPolynomial(double a = 0) : m_data(1,a) {}; // implicitni konstruktor



    CPolynomial(const CPolynomial & val) : m_data(val.m_data)
    {    };


    ~CPolynomial(){}; //destruktor
    void operator = (const CPolynomial &other) {
        if(*this == other)
            return ;
        this->m_data.assign(other.m_data.begin(),other.m_data.end() );
    } // operator prirazeni

    CPolynomial operator + (const CPolynomial & other) const; // operator + ;  secteni polynomu
    CPolynomial operator - (const CPolynomial & other) const;  // operator - ; odecteni polynomu
    CPolynomial operator * (const CPolynomial & other) const; // operator * (polynomial, double)
    bool operator == (const CPolynomial & other) const; // operator == ; presna shoda polynom
    bool operator != (const CPolynomial & other) const; // operator != presna shoda polynomu
    double operator ()(const double x) const; //vyhodnoti polynom pro zadane cislo double
    unsigned Degree() const;    // Degree (), stupen polynomu = nejvyssi mocnina
    double operator [] (const unsigned i) const; // zjistit  hodnotu KOEFICIENTU pro zadanou mocninu
    double& operator [] (const unsigned i); // nastavi hodnotu KOEFICIENTU pro zadanou mocninu

    friend ostream & operator << (ostream & ost, const CPolynomial & val); // operator <<
};

bool equal(double a, double b) {
/**
 * @cite http://floating-point-gui.de/errors/comparison/
 */
    double absA = fabs(a);
    double absB = fabs(b);
    double diff = fabs(a - b);
    double epsilon = 0.00000001;

    if (a == b)
        return true;
    else if (a == 0 || b == 0 || diff < DBL_MIN)
        return diff < (epsilon * DBL_MIN);
    else
        return diff / min((absA + absB), DBL_MAX) < epsilon;
}

bool CPolynomial::operator==(const CPolynomial &other) const {
    if (m_data.size() == other.m_data.size()) {
        for (size_t i = 0; i < m_data.size(); ++i)
            if (!equal(m_data[i], other.m_data[i]))
                return false;
    }

    else if (m_data.size() > other.m_data.size()) {
        for (size_t i = 0; i < other.m_data.size(); ++i)
            if (!equal(m_data[i], other.m_data[i]))
                return false;
        for(size_t i = other.m_data.size() ;  i < m_data.size(); ++i)
            if( !equal(m_data[i], 0.0))
                return false;
    }

    else {
        for (size_t i = 0; i < m_data.size(); ++i)
            if (!equal(m_data[i], other.m_data[i]))
                return false;
        for(size_t i = m_data.size() ;  i < other.m_data.size(); ++i)
            if( !equal(other.m_data[i], 0.0))
                return false;
    }

    return true;
}

bool CPolynomial::operator!=(const CPolynomial &other) const {
    return  ! operator==(other);
}

CPolynomial CPolynomial::operator+(const CPolynomial &other) const {
    const CPolynomial * const longerOne = m_data.size() > other.m_data.size() ? this : &other;
    const CPolynomial * const shorterOne = m_data.size() > other.m_data.size() ? &other : this;
    vector<double> sum;

    for (size_t i = 0; i < longerOne->m_data.size(); ++i) {
        if (i < shorterOne->m_data.size())
            sum.push_back(longerOne->m_data[i] + shorterOne->m_data[i]);
        else
            sum.push_back(longerOne->m_data[i]);
    }
    return CPolynomial(sum);
}

CPolynomial CPolynomial::operator-(const CPolynomial &other) const {
    vector<double> sum;

    if (m_data.size() > other.m_data.size()) {
        for (size_t i = 0; i < m_data.size(); ++i) {
            if (i < other.m_data.size())
                sum.push_back(m_data[i] - other.m_data[i]);
            else
                sum.push_back(this->m_data[i]);
        }
    } else {
        for (size_t i = 0; i < other.m_data.size(); ++i) {
            if (i < m_data.size())
                sum.push_back(m_data[i] - other.m_data[i]);
            else
                sum.push_back(-other.m_data[i]);
        }
    }
    return CPolynomial(sum);
}

CPolynomial CPolynomial::operator*(const CPolynomial &other) const {

    unsigned a = Degree();
    unsigned b = other.Degree();
    unsigned c;
    if(a == 1 || b == 1)
        c = a+b;
    else
        c = a+b+1;

    vector<double> product(c, 0);

    for(size_t i = 0; i <= a ; ++i )
        for(size_t j = 0 ; j <= b ; ++j) {
            if( !i && j )
                product[j] += m_data[i] * other.m_data[j];
            else if ( i && !j)
                product[i] += m_data[i] * other.m_data[j];
            else
            product[i + j] += m_data[i] * other.m_data[j];
        }
    CPolynomial abc(product);
    return abc;

}

double CPolynomial::operator()(const double x) const {
    double value=0;

    for(size_t i = 0; i < this->m_data.size() ;++i)
        value += m_data[i] * pow(x,(double)i);

    return value;
}

unsigned CPolynomial::Degree() const {

    for(long i = m_data.size() -1 ; i >= 0 ; --i)
        if ( ! equal( fabs(m_data[i]) , 0.0) )
            return (unsigned)i;

    return 0;
}

double CPolynomial::operator[](const unsigned i) const { // read
    return i >= m_data.size() ? 0 :  m_data[i];
}

double & CPolynomial::operator[](const unsigned i) { // write
    if (i >= m_data.size())
        m_data.resize(i+1, 0);

    return m_data[i];
}

ostream &operator<<(ostream &ost, const CPolynomial &val) {
    bool printed = false;

    for (long i = val.m_data.size() - 1; i >= 0; --i) {
        if (equal(val.m_data[i], 0))
            continue;

        if (!printed) {

            if (!equal(fabs(val.m_data[i]), 1.0)){
                if (val.m_data[i] > 0)
                    ost << val.m_data[i] << "*";
                else
                    ost << "- " << fabs(val.m_data[i]) << "*";
            }
            else {
                if (val.m_data[i] < 0)
                    ost << "- " ;
            }

            if (i > 1)
                ost << prom << '^' << i;
            else if (i == 1)
                ost << prom;

            printed = true;
        } else {
            if (val.m_data[i] > 0) {
                ost << " + ";
                if (!equal(fabs(val.m_data[i]), 1.0))
                    ost << val.m_data[i];

            } else {
                ost << " - ";
                if (!equal(fabs(val.m_data[i]), 1.0))
                    ost << fabs(val.m_data[i]);
            }
            if (i >= 1)
                ost << '*' << prom << '^' << i;
        }
    }

    if (!printed)
        ost << '0';

    return ost;
}
//---------------------------------------------------------------------------------------

#ifndef __PROGTEST__

bool smallDiff(double a,
               double b) {
   return equal(a,b);
}

bool dumpMatch(const CPolynomial &x,
               const vector<double> &ref) {


    if(x.getData().size() != ref.size())
        return false;

    for(size_t i = 0 ; i < x.getData().size(); ++i){
        if (! equal(x.getData()[i], ref[i]))
            return false;
    }
    return true;
}


ios_base &dummy_polynomial_manipulator(ios_base &x) {
    const int  idx = std::ios_base::xalloc();
    x.pword(idx) = *x;
    return x;
}

ios_base &( *( polynomial_variable(const string &varName))  )(ios_base &x) {
    prom = varName;
    //static_cast<mystream<charT,traits>&>(os).myfn();
    return  dummy_polynomial_manipulator( std::ios_base::xalloc() );
}

int main(void) {
    CPolynomial a, b, c;
    ostringstream out;

    a[0] = -10;
    a[1] = 3.5;
    a[3] = 1;
    assert (smallDiff(a(2), 5));
    out.str("");
    out << a;
    assert (out.str() == "x^3 + 3.5*x^1 - 10");
    a = a * -2;
    assert (a.Degree() == 3
            && dumpMatch(a, vector<double>{20.0, -7.0, -0.0, -2.0}));
    out.str("");
    out << a;
    assert (out.str() == "- 2*x^3 - 7*x^1 + 20");
    out.str("");
    out << b;
    assert (out.str() == "0");
    b[5] = -1;
    out.str("");
    out << b;
    assert (out.str() == "- x^5");
    c = a + b;
    assert (c.Degree() == 5
            && dumpMatch(c, vector<double>{20.0, -7.0, 0.0, -2.0, 0.0, -1.0}));

    out.str("");
    out << c;
    assert (out.str() == "- x^5 - 2*x^3 - 7*x^1 + 20");
    c = a - b;
    assert (c.Degree() == 5
            && dumpMatch(c, vector<double>{20.0, -7.0, -0.0, -2.0, -0.0, 1.0}));

    out.str("");
    out << c;
    assert (out.str() == "x^5 - 2*x^3 - 7*x^1 + 20");
    c = a * b;
    assert (c.Degree() == 8);
    assert (dumpMatch(c, vector<double>{0.0, -0.0, 0.0, -0.0, -0.0, -20.0, 7.0, 0.0, 2.0}));

    out.str("");
    out << c;
    assert (out.str() == "2*x^8 + 7*x^6 - 20*x^5");
    assert (a != b);
    b[5] = 0;
    assert (!(a == b));
    a = a * 0;
    assert (a.Degree() == 0);

    //assert( dumpMatch(a, vector<double>{0.0}));

    assert (a == b);


    a[2] = 4;
    a[1] = -3;
    b[3] = 7;
    out.str("");
    out << polynomial_variable("y") << "a=" << a << ", b=" << b;
 //   assert (out.str() == "a=4*y^2 - 3*y^1, b=7*y^3");


   out.str("");
//   out << polynomial_variable("test") << c;
//   assert (out.str() == "2*test^8 + 7*test^6 - 20*test^5");


    return 0;
}

#endif /* __PROGTEST__ */
