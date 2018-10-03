#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cmath>
#include <cfloat>
#include <cassert>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <complex>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

ios_base & dummy_polynomial_manipulator ( ios_base & x )
{ 
  return x;
}

ios_base & ( * ( polynomial_variable ( const string & varName ) ) ) ( ios_base & x )
{
  return dummy_polynomial_manipulator;
}
class CPolynomial
{
  public:
    // default constructor
    // operator +
    // operator -
    // operator * (polynomial, double)
    // operator ==
    // operator !=
    // operator []
    // operator ()
    // operator <<
    // Degree (), returns unsigned value
  private:
    // todo
};

#ifndef __PROGTEST__
bool               smallDiff                               ( double            a,
                                                             double            b )
{
  // DIY 
}

bool               dumpMatch                               ( const CPolynomial & x,
                                                             const vector<double> & ref )
{
  // DIY 
}

int                main                                    ( void )
{
  CPolynomial a, b, c;
  ostringstream out;

  a[0] = -10;
  a[1] = 3.5;
  a[3] = 1;
  assert ( smallDiff ( a ( 2 ), 5 ) );
  out . str ("");
  out << a;
  assert ( out . str () == "x^3 + 3.5*x^1 - 10" );
  a = a * -2;
  assert ( a . Degree () == 3
           && dumpMatch ( a, vector<double>{ 20.0, -7.0, -0.0, -2.0 } ) );

  out . str ("");
  out << a;
  assert ( out . str () == "- 2*x^3 - 7*x^1 + 20" );
  out . str ("");
  out << b;
  assert ( out . str () == "0" );
  b[5] = -1;
  out . str ("");
  out << b;
  assert ( out . str () == "- x^5" );
  c = a + b;
  assert ( c . Degree () == 5
           && dumpMatch ( c, vector<double>{ 20.0, -7.0, 0.0, -2.0, 0.0, -1.0 } ) );

  out . str ("");
  out << c;
  assert ( out . str () == "- x^5 - 2*x^3 - 7*x^1 + 20" );
  c = a - b;
  assert ( c . Degree () == 5
           && dumpMatch ( c, vector<double>{ 20.0, -7.0, -0.0, -2.0, -0.0, 1.0 } ) );

  out . str ("");
  out << c;
  assert ( out . str () == "x^5 - 2*x^3 - 7*x^1 + 20" );
  c = a * b;
  assert ( c . Degree () == 8
           && dumpMatch ( c, vector<double>{ 0.0, -0.0, 0.0, -0.0, -0.0, -20.0, 7.0, 0.0, 2.0 } ) );

  out . str ("");
  out << c;
  assert ( out . str () == "2*x^8 + 7*x^6 - 20*x^5" );
  assert ( a != b );
  b[5] = 0;
  assert ( !(a == b) );
  a = a * 0;
  assert ( a . Degree () == 0
           && dumpMatch ( a, vector<double>{ 0.0 } ) );

  assert ( a == b );

  // bonus
  a[2] = 4;
  a[1] = -3;
  b[3] = 7;
  out . str ("");
  out << polynomial_variable ( "y" ) << "a=" << a << ", b=" << b;
  assert ( out . str () == "a=4*y^2 - 3*y^1, b=7*y^3" );

  out . str ("");
  out << polynomial_variable ( "test" ) << c;
  assert ( out . str () == "2*test^8 + 7*test^6 - 20*test^5" );
  return 0;
}
#endif /* __PROGTEST__ */
