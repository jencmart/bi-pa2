//
// Created by jencmart on 3/3/17.
//

#include <iostream>
#include <cmath>

class Complex {
private :
        int re, im;

public:
    Complex(int re, int im){
        this->re = re;
        this->im = im;
    }

    Complex() {
        this->re = 0;
        this->im = 0;
    }

    int getRe() const {
        return this->im;
    }

    int getIm() const {
        return this->im;
    }

    float abs(){
        return sqrtf(this->re*this->re + this->im*this->im);
    }

    void print(){
        if ( this->re == 0) {
             if (this->im == 0)
                std::cout << '0' << std::endl;
            else
                 std::cout << im << 'i' << std::endl;
        }

        else if (this->im == 0)
            std::cout << re << std::endl;

        else{
            if (this->im < 0)
                std::cout << re << im << 'i' << std::endl;
            else
               std::cout << re << '+' << im << 'i' << std::endl;
        }
    }

    Complex add(const Complex &x) const {
        return Complex(this->re+x.getRe() , im + x.getIm());

    }

    Complex diff(const Complex &x) const {
        Complex z(this->re-x.getRe() , this->im - x.getIm());
        return z;
    }

};