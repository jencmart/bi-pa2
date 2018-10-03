//
// Created by jencmart on 3/8/17.
//

#include <cstdlib>
#include <iostream>
#include "fronta.h"

Fronta::Fronta()
{
    m_head = m_tail = NULL;
}

Fronta::~Fronta()
{
    if(m_head != NULL) {
        while (m_head != m_tail) {
            Lst *tmp = m_head->m_next;
            delete m_head;
            m_head = tmp;
        }

        delete m_head;
    }
}
bool Fronta::jePrazdna() const{
    return !m_head && !m_tail;
}

void Fronta::print() const {
      Lst *iterator = m_head;
      if(iterator != NULL) {
        while (iterator != m_tail) {
            std::cout << iterator->m_value << ' ' ;
            iterator = iterator->m_next;
        }
            std::cout << iterator->m_value << std::endl;
      }
}

void Fronta::vloz(int x) {
    if (!m_head) {
        m_head = new Lst(x, NULL);
        m_tail = m_head;
    }

    else {
        Lst *tmp = new Lst(x, NULL);
        m_tail->m_next = tmp;
        m_tail = tmp;
    }
}

int Fronta::odeber() {

    if(m_head != m_tail) {
        int val = m_head->m_value;
        Lst *tmp = m_head->m_next;
        delete m_head;
        m_head = tmp;
        return val;
    }

    else if (m_head == m_tail) {
        int tmp = m_head->m_value;
        delete  m_head;
        m_head = m_tail = NULL;
        return tmp;
    }

    else
        return 0;
}