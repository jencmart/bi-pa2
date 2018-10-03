//
// Created by jencmart on 3/8/17.
//

#ifndef PA2_CV_03_FRONTA_H
#define PA2_CV_03_FRONTA_H

class Fronta{
private:
    struct Lst
    {
        int m_value;
        Lst * m_next;
        Lst(int value, Lst *next):m_value(value), m_next(next) {}
    };

    Lst *m_head;
    Lst *m_tail;

public:
    Fronta();
    ~Fronta();
    void vloz(int x);
    int odeber();
    bool  jePrazdna() const;
    void print() const;
};

#endif //PA2_CV_03_FRONTA_H
