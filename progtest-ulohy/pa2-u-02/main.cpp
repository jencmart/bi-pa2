#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>

using namespace std;
#endif /* __PROGTEST__ */

class Company {
private:
    std::string m_name;
    std::string m_addr;
    std::string m_id;
    unsigned int m_auditValue;

public:
    Company(const std::string &name, const std::string &addr, const std::string &id) :
            m_name(name), m_addr(addr), m_id(id), m_auditValue(0) {};

    ~Company() {}

    inline void addInvoice(unsigned int val) {
        m_auditValue += val;
        return;
    }

    inline void getAudit(unsigned int &sum) const {
        sum = m_auditValue;
        return;
    }

    inline const std::string &getId() const { return m_id; }

    inline const std::string &getName() const { return m_name; }

    inline const std::string &getAddr() const { return m_addr; }
};

//************************************************************************************
//************************************************************************************
//---------------------------------------HASH SET-------------------------------------

class HashSet {
private:

    struct Bucket {
        unsigned long int m_hash;
        Company *m_value;
        Bucket *m_next;

        Bucket(unsigned long int hash, Company *value) :
                m_hash(hash), m_value(value), m_next(NULL) {};

    };

    vector<Bucket *> m_bucketArray;
    unsigned long int noElements;

    unsigned long hashIt(const string &str1) const;

    bool timeToRehash() {
        if (!noElements)
            return false;
        return 0.75 <= (noElements / ((double) m_bucketArray.capacity()));
    }

    void putBucket(unsigned long int hash, Company *company);

    void putBucket(unsigned long int hash, Bucket *tmp);

    void rehashBy_ID();

    void rehashBy_Name_Addr();

    void unlinkBucket_ID(const string &id, unsigned long hash);

    void unlinkBucket_Name_Addr(const string &name, const string &addr, unsigned long hash);

public:
    HashSet() : m_bucketArray(10000, NULL), noElements(0) {};

    bool containsKey(const string &id) const;

    bool containsKey(const string &name, const string &addr) const;

    bool put(const string &id, Company *company);

    bool put(const string &name, const string &addr, Company *company);

    Company *get(const string &id) const;

    Company *get(const string &name, const string &addr) const;

    bool remove(const string &id);

    bool remove(const string &name, const string &addr);

    void clearAll();

    void clearAll_JustBuckets();
};

unsigned long HashSet::hashIt(const string &str) const {
//@cite http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;

    for (unsigned int i = 0; i < str.length() && i < 16; i++) {
        hash = ((hash << 5) + hash) + (int) str[i];
    }
    return hash % m_bucketArray.size();
}

bool HashSet::containsKey(const string &id) const {
    Bucket *head = m_bucketArray[hashIt(id)];
    while (head) {
        if (head->m_value->getId() == id)
            return true;
        head = head->m_next;
    }
    return false;
}

Company *HashSet::get(const string &id) const {
    Bucket *head = m_bucketArray[hashIt(id)];
    while (head) {
        if (head->m_value->getId() == id)
            return head->m_value;
        head = head->m_next;
    }
    return NULL;
}

bool HashSet::containsKey(const string &name, const string &addr) const {
    Bucket *head = m_bucketArray[hashIt(name + addr)];
    while (head) {
        if (head->m_value->getName() == name && head->m_value->getAddr() == addr)
            return true;
        head = head->m_next;
    }
    return false;
}

Company *HashSet::get(const string &name, const string &addr) const {
    Bucket *head = m_bucketArray[hashIt(name + addr)];
    while (head) {
        if (head->m_value->getName() == name && head->m_value->getAddr() == addr)
            return head->m_value;
        head = head->m_next;
    }
    return NULL;
}

bool HashSet::put(const string &id, Company *company) {
    if (containsKey(id))
        return false;
    if (timeToRehash())
        rehashBy_ID();
    putBucket(hashIt(id), company);

    return true;
}

bool HashSet::put(const string &name, const string &addr, Company *company) {
    if (containsKey(name, addr))
        return false;
    if (timeToRehash())
        rehashBy_Name_Addr();
    putBucket(hashIt(name + addr), company);

    return true;
}

void HashSet::putBucket(unsigned long int hash, Company *company) {
    Bucket *tmp = new Bucket(hash, company);

    if (m_bucketArray[hash] == NULL) {
        m_bucketArray[hash] = tmp;
    } else {
        Bucket *iter = m_bucketArray[hash];
        while (iter->m_next)
            iter = iter->m_next;
        iter->m_next = tmp;
    }
    noElements++;
}

void HashSet::putBucket(unsigned long int hash, Bucket *tmp) {
    if (m_bucketArray[hash] == NULL) {
        m_bucketArray[hash] = tmp;
    } else {
        Bucket *iter = m_bucketArray[hash];
        while (iter->m_next)
            iter = iter->m_next;
        iter->m_next = tmp;
    }
}

bool HashSet::remove(const string &id) {
    Bucket *iter = m_bucketArray[hashIt(id)];

    if (!iter)    //neni linklist
        return false;

    if (iter->m_value->getId() == id) { // je to hend ten prvni
        Bucket *tmp = iter->m_next;
        delete iter;
        m_bucketArray[hashIt(id)] = tmp;
        noElements--;
        return true;
    }

    Bucket *iterNext = iter->m_next;
    while (iterNext) {
        if (iterNext->m_value->getId() == id) {
            Bucket *tmp = iterNext->m_next;
            delete iterNext;
            iter->m_next = tmp;
            noElements--;
            return true;
        }

        iter = iterNext;
        iterNext = iterNext->m_next;
    }

    return false;
}

bool HashSet::remove(const string &name, const string &addr) {
    Bucket *iter = m_bucketArray[hashIt(name + addr)];

    if (!iter)    //neni linklist
        return false;

    if (iter->m_value->getName() == name && iter->m_value->getAddr() == addr) { // je to hend ten prvni
        Bucket *tmp = iter->m_next;
        delete iter;
        m_bucketArray[hashIt(name + addr)] = tmp;
        noElements--;
        return true;
    }

    Bucket *iterNext = iter->m_next;
    while (iterNext) {
        if (iterNext->m_value->getName() == name && iterNext->m_value->getAddr() == addr) {
            Bucket *tmp = iterNext->m_next;
            delete iterNext;
            iter->m_next = tmp;
            noElements--;
            return true;
        }
        iter = iterNext;
        iterNext = iterNext->m_next;
    }
    return false;
}

void HashSet::rehashBy_ID() {
    long int oldSize = m_bucketArray.size();
    unsigned long newHash;
    m_bucketArray.resize(((unsigned) oldSize) * 2, NULL);

    for (std::vector<Bucket *>::iterator it = m_bucketArray.begin(); (it - m_bucketArray.begin()) < oldSize; ++it) {
        Bucket *iterBucket = *it;
        while (iterBucket) {
            Bucket *tmp = iterBucket->m_next;
            if ((newHash = hashIt(iterBucket->m_value->getId())) != iterBucket->m_hash) {
                unlinkBucket_ID(iterBucket->m_value->getId(), iterBucket->m_hash);
                iterBucket->m_hash = newHash;
                putBucket(newHash, iterBucket);
            }
            iterBucket = tmp;
        }
    }
}

void HashSet::unlinkBucket_ID(const string &id, unsigned long hash) {
    Bucket *iter = m_bucketArray[hash];

    if (iter->m_value->getId() == id) { // je to hend ten prvni
        Bucket *tmp = iter->m_next;
        iter->m_next = NULL;
        m_bucketArray[hash] = tmp;
        return;
    }
    Bucket *iterNext = iter->m_next;
    while (iterNext) {
        if (iterNext->m_value->getId() == id) {
            Bucket *tmp = iterNext->m_next;
            iterNext->m_next = NULL;
            iter->m_next = tmp;
            return;
        }

        iter = iterNext;
        iterNext = iterNext->m_next;
    }
}

void HashSet::rehashBy_Name_Addr() {
    long int oldSize = m_bucketArray.size();
    unsigned long newHash;
    m_bucketArray.resize(((unsigned) oldSize) * 2, NULL);

    for (std::vector<Bucket *>::iterator it = m_bucketArray.begin(); (it - m_bucketArray.begin()) < oldSize; ++it) {
        Bucket *iterBucket = *it;

        while (iterBucket) {
            Bucket *tmp = iterBucket->m_next;
            if ((newHash = hashIt(iterBucket->m_value->getName() + iterBucket->m_value->getAddr())) !=
                iterBucket->m_hash) {
                unlinkBucket_Name_Addr(iterBucket->m_value->getName(), iterBucket->m_value->getAddr(),
                                       iterBucket->m_hash);
                iterBucket->m_hash = newHash;
                putBucket(newHash, iterBucket);
            }
            iterBucket = tmp;
        }
    }
}

void HashSet::unlinkBucket_Name_Addr(const string &name, const string &addr, unsigned long hash) {
    Bucket *iter = m_bucketArray[hash];

    if (iter->m_value->getName() == name && iter->m_value->getAddr() == addr) {// je to hend ten prvni
        Bucket *tmp = iter->m_next;
        iter->m_next = NULL;
        m_bucketArray[hash] = tmp;
        return;
    }
    Bucket *iterNext = iter->m_next;
    while (iterNext) {
        if (iterNext->m_value->getName() == name && iterNext->m_value->getAddr() == addr) {
            Bucket *tmp = iterNext->m_next;
            iterNext->m_next = NULL;
            iter->m_next = tmp;
            return;
        }

        iter = iterNext;
        iterNext = iterNext->m_next;
    }
}

void HashSet::clearAll() {
    for (std::vector<Bucket *>::iterator it = m_bucketArray.begin(); it != m_bucketArray.end(); ++it) {
        if ((*it)) {
            Bucket *head = *it;
            while (head) {
                Bucket *tmp = head->m_next;
                delete head->m_value;
                delete head;
                head = tmp;
            }
        }
    }
}

void HashSet::clearAll_JustBuckets() {
    for (std::vector<Bucket *>::iterator it = m_bucketArray.begin(); it != m_bucketArray.end(); ++it) {
        if ((*it)) {
            Bucket *head = *it;
            while (head) {
                Bucket *tmp = head->m_next;
                delete head;
                head = tmp;
            }
        }
    }
}


//************************************************************************************
//************************************************************************************
//------------------------------------CVAT REGISTER-----------------------------------

class CVATRegister {
private:
    HashSet m_companies_ID;
    HashSet m_companies_Name_Addr;
    vector<unsigned int> m_leftHeap;
    vector<unsigned int> m_rightHeap;
    unsigned int m_noInvoices;
    unsigned int m_currentMedian;

    void PushToHeaps(unsigned int amount);

public:
    CVATRegister();

    ~CVATRegister();

    bool NewCompany(const string &name, const string &addr, const string &id);

    bool CancelCompany(const string &id);

    bool CancelCompany(const string &name, const string &addr);

    bool Invoice(const string &id, unsigned int amount);

    bool Invoice(const string &name, const string &addr, unsigned int amount);

    bool Audit(const string &id, unsigned int &sumIncome) const;

    bool Audit(const string &name, const string &addr, unsigned int &sumIncome) const;

    unsigned int MedianInvoice(void) const;
};

CVATRegister::CVATRegister() : m_companies_ID(), m_companies_Name_Addr(),
                               m_leftHeap(), m_rightHeap(), m_noInvoices(0), m_currentMedian(0) {}

CVATRegister::~CVATRegister() {
    m_companies_ID.clearAll();
    m_companies_Name_Addr.clearAll_JustBuckets();
}

bool CVATRegister::NewCompany(const std::string &nameCased, const std::string &addrCased, const std::string &id) {
    string name = nameCased;
    string addr = addrCased;
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    transform(addr.begin(), addr.end(), addr.begin(), ::tolower);

    if (m_companies_ID.containsKey(id) || m_companies_Name_Addr.containsKey(name, addr))
        return false;

    Company *tmp = new Company(name, addr, id);
    m_companies_ID.put(id, tmp);
    m_companies_Name_Addr.put(name, addr, tmp);
    return true;
}

bool CVATRegister::CancelCompany(const std::string &id) {
    Company *tmp = m_companies_ID.get(id);
    if (!tmp)
        return false;

    m_companies_Name_Addr.remove(tmp->getName(), tmp->getAddr());
    m_companies_ID.remove(id);
    delete tmp;
    return true;
}

bool CVATRegister::CancelCompany(const std::string &nameCased, const std::string &addrCased) {
    string name = nameCased;
    string addr = addrCased;
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    transform(addr.begin(), addr.end(), addr.begin(), ::tolower);

    Company *tmp = m_companies_Name_Addr.get(name, addr);
    if (!tmp)
        return false;

    m_companies_ID.remove(tmp->getId());
    m_companies_Name_Addr.remove(tmp->getName(), tmp->getAddr());
    delete tmp;
    return true;
}

bool CVATRegister::Invoice(const string &id, unsigned int amount) {
    Company *tmp = m_companies_ID.get(id);
    if (!tmp)
        return false;

    tmp->addInvoice(amount);
    PushToHeaps(amount);
    return true;
}

bool CVATRegister::Invoice(const string &nameCased, const string &addrCased, unsigned int amount) {
    string name = nameCased;
    string addr = addrCased;
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    transform(addr.begin(), addr.end(), addr.begin(), ::tolower);

    Company *tmp = m_companies_Name_Addr.get(name, addr);
    if (!tmp)
        return false;

    tmp->addInvoice(amount);
    PushToHeaps(amount);
    return true;
}

bool CVATRegister::Audit(const string &id, unsigned int &sum) const {
    Company *tmp = m_companies_ID.get(id);
    if (!tmp)
        return false;

    tmp->getAudit(sum);
    return true;
}

bool CVATRegister::Audit(const string &nameCased, const string &addrCased, unsigned int &sum) const {
    string name = nameCased;
    string addr = addrCased;
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    transform(addr.begin(), addr.end(), addr.begin(), ::tolower);

    Company *tmp = m_companies_Name_Addr.get(name, addr);
    if (!tmp)
        return false;

    tmp->getAudit(sum);
    return true;
}

bool cmpMaxHeap(const unsigned int &a, const unsigned int &b) { return a < b; }

bool cmpMinHeap(const unsigned int &a, const unsigned int &b) { return a > b; }

void CVATRegister::PushToHeaps(unsigned int amount) {
    if (m_noInvoices > 1) {
        if (amount < m_currentMedian) {
            m_leftHeap.push_back(amount);     //pridej vlevo
            push_heap(m_leftHeap.begin(), m_leftHeap.end(), cmpMaxHeap);

            if (m_leftHeap.size() >
                m_rightHeap.size() + 1) {     //v pripade ze je vlevo vic jak o jeden vic, presun root zleva do prava
                pop_heap(m_leftHeap.begin(), m_leftHeap.end(), cmpMaxHeap);
                unsigned int tmp = m_leftHeap.back();
                m_leftHeap.pop_back();

                m_rightHeap.push_back(tmp);
                push_heap(m_rightHeap.begin(), m_rightHeap.end(), cmpMinHeap);
            }
        } else if (amount > m_currentMedian) {
            m_rightHeap.push_back(amount);     //pridej v pravo
            push_heap(m_rightHeap.begin(), m_rightHeap.end(), cmpMinHeap);

            if (m_rightHeap.size() >
                m_leftHeap.size() + 1) {   //v pripade ze je v pravo vic jak o jeden vic, presun root zleva do prava
                pop_heap(m_rightHeap.begin(), m_rightHeap.end(), cmpMinHeap);
                unsigned int tmp = m_rightHeap.back();
                m_rightHeap.pop_back();

                m_leftHeap.push_back(tmp);
                push_heap(m_leftHeap.begin(), m_leftHeap.end(), cmpMaxHeap);
            }
        } else {  // median je shodny s novou hodnotou
            if (m_leftHeap.size() < m_rightHeap.size()) { //pokud je v levo mene, pridej do leva
                m_leftHeap.push_back(amount);     //pridej vlevo
                push_heap(m_leftHeap.begin(), m_leftHeap.end(), cmpMaxHeap);
            } else {
                m_rightHeap.push_back(amount);     //jinak pridej doprava
                push_heap(m_rightHeap.begin(), m_rightHeap.end(), cmpMinHeap);
            }
        }
        if (m_leftHeap.size() <= m_rightHeap.size())  // pokud je prvku v obou stejne NEBO je vpravo vic vem pravy root
            m_currentMedian = m_rightHeap.front();
        else
            m_currentMedian = m_leftHeap.front();
        m_noInvoices++;
        return;
    }
    if (m_noInvoices == 0) {
        m_leftHeap.push_back(amount);
        m_currentMedian = amount;
        m_noInvoices++;
        return;
    }
    if (m_noInvoices == 1) {
        if (amount < m_currentMedian) {
            unsigned int tmp = m_leftHeap.back();
            m_leftHeap.pop_back();
            m_leftHeap.push_back(amount);
            m_rightHeap.push_back(tmp);
            make_heap(m_leftHeap.begin(), m_leftHeap.end(), cmpMaxHeap);
            make_heap(m_rightHeap.begin(), m_rightHeap.end(), cmpMinHeap);
            m_currentMedian = tmp;
        } else {
            m_rightHeap.push_back(amount);
            make_heap(m_leftHeap.begin(), m_leftHeap.end(), cmpMaxHeap);
            make_heap(m_rightHeap.begin(), m_rightHeap.end(), cmpMinHeap);
            m_currentMedian = amount;
        }
        m_noInvoices++;
        return;
    }
}
unsigned int CVATRegister::MedianInvoice(void) const { return m_currentMedian; }

#ifndef __PROGTEST__
int main ( void ) {
    unsigned int sumIncome;
    CVATRegister b1;
    assert ( b1 . NewCompany ( "ACME", "Kolejni", "666/666/666" ) );
    assert ( b1 . NewCompany ( "ACME", "Thakurova", "666/666" ) );
    assert ( b1 . NewCompany ( "Dummy", "Thakurova", "123456" ) );
    assert ( b1 . Invoice ( "666/666", 2000 ) );
    assert ( b1 . MedianInvoice () == 2000 );
    assert ( b1 . Invoice ( "666/666/666", 3000 ) );
    assert ( b1 . MedianInvoice () == 3000 );
    assert ( b1 . Invoice ( "123456", 4000 ) );
    assert ( b1 . MedianInvoice () == 3000 );
    assert ( b1 . Invoice ( "aCmE", "Kolejni", 5000 ) );
    assert ( b1 . MedianInvoice () == 4000 );
    assert ( b1 . Audit ( "ACME", "Kolejni", sumIncome ) && sumIncome == 8000 );
    assert ( b1 . Audit ( "123456", sumIncome ) && sumIncome == 4000 );
    assert ( b1 . CancelCompany ( "ACME", "KoLeJnI" ) );
    assert ( b1 . MedianInvoice () == 4000 );
    assert ( b1 . CancelCompany ( "666/666" ) );
    assert ( b1 . MedianInvoice () == 4000 );
    assert ( b1 . Invoice ( "123456", 100 ) );
    assert ( b1 . MedianInvoice () == 3000 );
    assert ( b1 . Invoice ( "123456", 300 ) );
    assert ( b1 . MedianInvoice () == 3000 );
    assert ( b1 . Invoice ( "123456", 200 ) );
    assert ( b1 . MedianInvoice () == 2000 );
    assert ( b1 . Invoice ( "123456", 230 ) );
    assert ( b1 . MedianInvoice () == 2000 );
    assert ( b1 . Invoice ( "123456", 830 ) );
    assert ( b1 . MedianInvoice () == 830 );
    assert ( b1 . Invoice ( "123456", 1830 ) );
    assert ( b1 . MedianInvoice () == 1830 );
    assert ( b1 . Invoice ( "123456", 2830 ) );
    assert ( b1 . MedianInvoice () == 1830 );
    assert ( b1 . Invoice ( "123456", 2830 ) );
    assert ( b1 . MedianInvoice () == 2000 );
    assert ( b1 . Invoice ( "123456", 3200 ) );
    assert ( b1 . MedianInvoice () == 2000 );
    CVATRegister b2;
    assert ( b2 . NewCompany ( "ACME", "Kolejni", "abcdef" ) );
    assert ( b2 . NewCompany ( "Dummy", "Kolejni", "123456" ) );
    assert ( ! b2 . NewCompany ( "AcMe", "kOlEjNi", "1234" ) );
    assert ( b2 . NewCompany ( "Dummy", "Thakurova", "ABCDEF" ) );
    assert ( b2 . MedianInvoice () == 0 );
    assert ( b2 . Invoice ( "ABCDEF", 1000 ) );
    assert ( b2 . MedianInvoice () == 1000 );
    assert ( b2 . Invoice ( "abcdef", 2000 ) );
    assert ( b2 . MedianInvoice () == 2000 );
    assert ( b2 . Invoice ( "aCMe", "kOlEjNi", 3000 ) );
    assert ( b2 . MedianInvoice () == 2000 );
    assert ( ! b2 . Invoice ( "1234567", 100 ) );
    assert ( ! b2 . Invoice ( "ACE", "Kolejni", 100 ) );
    assert ( ! b2 . Invoice ( "ACME", "Thakurova", 100 ) );
    assert ( ! b2 . Audit ( "1234567", sumIncome ) );
    assert ( ! b2 . Audit ( "ACE", "Kolejni", sumIncome ) );
    assert ( ! b2 . Audit ( "ACME", "Thakurova", sumIncome ) );
    assert ( ! b2 . CancelCompany ( "1234567" ) );
    assert ( ! b2 . CancelCompany ( "ACE", "Kolejni" ) );
    assert ( ! b2 . CancelCompany ( "ACME", "Thakurova" ) );
    assert ( b2 . CancelCompany ( "abcdef" ) );
    assert ( b2 . MedianInvoice () == 2000 );
    assert ( ! b2 . CancelCompany ( "abcdef" ) );
    assert ( b2 . NewCompany ( "ACME", "Kolejni", "abcdef" ) );
    assert ( b2 . CancelCompany ( "ACME", "Kolejni" ) );
    assert ( ! b2 . CancelCompany ( "ACME", "Kolejni" ) );
    return 0;
}
#endif /* __PROGTEST__ */