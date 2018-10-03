//
// Created by jencmart on 3/4/17.
//
#include <iostream>
#include "complex.h"
#include <cmath>

Complex::Complex(int re, int im) {
    m_re = re;
    m_im = im;
}

Complex const Complex::add(Complex x) {
    return Complex(m_re+x.getRe() , m_im + x.getIm());
}

Complex const Complex::diff(Complex x) {
    return Complex(m_re - x.getRe() , m_im - x.getIm());
}

int const Complex::getRe() {
    return m_re;
}

int const Complex::getIm() {
    return m_im;
}

float const Complex::abs() {
    return (float)sqrt(m_im*m_im + m_re*m_re);
}

void const Complex::print() {
    std::cout << m_re << '+' << m_im << 'i' << std::endl;
}
