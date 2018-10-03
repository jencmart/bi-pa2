//
// Created by jencmart on 3/4/17.
//

#ifndef COMPLEX_H
#define COMPLEX_H

class Complex{

private:
    int m_re;
    int m_im;

public:
    Complex(int re=0, int img=0);
    Complex const add(Complex x);
    Complex const diff(Complex x);
    int const getRe();
    int const getIm();
    float const abs();
    void const print();
};

Complex add(Complex x, Complex y);
Complex diff(Complex x, Complex y);

#endif //COMPLEX_H
