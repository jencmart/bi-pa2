#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <sstream>
using namespace std;
#endif /* __PROGTEST__ */


class CAccount {
private:
    struct CAcc {
    private:
        size_t m_RefCnt;
    public:
        long m_initialState;
        long m_currentState;
        const char *m_ID;
        char *history;

        void riseRefCnt();

        void reduceRefCnt();

        size_t getRefCnt() { return m_RefCnt; }
    };

    void attach(CAcc *ptr) {
      m_CAccPtr = ptr;
      m_CAccPtr->riseRefCnt();
    }

    void detach() {
      m_CAccPtr->reduceRefCnt();
    }

public:
    CAcc *m_CAccPtr;

    CAccount();

    CAccount(CAccount &other);

    void operator=(const CAccount &other);

    ~CAccount();

    long Balance() const;

    void Trim();

    void SendPayment(int ammount, const char *to, const char *signature);

    void RecievePayment(int ammount, const char *from, const char *signature);


    friend ostream &operator<<(ostream &os, const CAccount &other);
};




///*****************************************CBAN********************************************************

template <typename T>
class simpleVector<T>{

private:
    T * m_buffer;
    size_t m_capacity;
    size_t m_size;

    ///dynamically resizes buffer
    void resize(){
        if( m_capacity == 0){
            m_capacity = 20;
            m_buffer = new T [m_capacity];
            return;
        }
        m_capacity *=2;
        T * newBuffer = new T [m_capacity];
        for(size_t i = 0; i < m_size; ++i){
            newBuffer[i] = m_buffer[i];
        }
        delete [] m_buffer;
        m_buffer = newBuffer;
    }
public:

    simpleVector() : m_buffer(NULL), m_capacity(0), m_size(0){};
    ~simpleVector(){ delete [] m_buffer; }

    ///returns currenty allocated as number of type elements
    inline size_t  capacity() { return m_capacity; }

    ///returns number of type elements currently stored in vector
    inline size_t size() { return m_size; }

    ///adds element to back of the vector
    inline void pushBack(T & element){
        if(m_size == m_capacity)
            resize();
        m_buffer[m_size++] = element;
    }

    ///return writable type at index
    inline T & operator [] (size_t index) { return m_buffer[index]; }

    ///return read-only type at index
    inline const T & operator  [] (size_t index) const { return m_buffer[index]; }
};

struct CBan {
private:

    ///reference counter
    size_t m_RefCnt;

public:
    ///array of CAccounts
    CAccount *m_arrAccounts;
    size_t m_capacity;
    size_t m_size;
    simpleVector<CAccount * > array;

    ///rise this(CBan) refCnt ; rise refCnt on all CAcc
    void riseRefCnt() ;

    ///reduce this(CBan) refCnt ; todo also reduce CAcc ????? when delete???
    void reduceRefCnt();

    inline size_t getRefCnt() const { return m_RefCnt; }

    CBan() : m_arrAccounts(NULL), m_capacity(0), m_size(0), m_RefCnt(1) {};

    //todo copy constructor which copy CAccounts array
    CBan(CBan &other) : m_arrAccounts(NULL) {
        m_capacity = other.m_capacity;
        m_size = other.m_size;
        m_RefCnt = 1;
        m_arrAccounts = new CAccount[m_capacity];

        //todo is needed to rise CAcc refCnt?????
        ///copy the data (pointers to CAccount
        for (int i = 0; i < m_size; ++i) {
            m_arrAccounts[i] = other.m_arrAccounts[i];
        }
    };

    //todo nevim
    ~CBan() {
        //haha udelej hodne prace proste
    }

    void add(const char *accID, int initialBalance) {
      ///create new CAccount and CAcc

        ///put it to m_CAccounts

    };
};

void CBan::riseRefCnt() {
        ///rise nuber of references here (on CBan)
        m_RefCnt++;

        //todo rise references on all CAcc


}

void CBan::reduceRefCnt() {
        ///reduce nuber of references here (on CBan)
        m_RefCnt--;

        //todo reduce nuber of references on all CAcc ; if referece on Cacc is 0, delete it;
        for (size_t i = 0; i < m_size; ++i) {
            m_arrAccounts->
        }
        //todo if m_RefCnt here is zero; dele this (CBan)



}

///*****************************************CBANK*******************************************************

class CBank {
private:

    ///pointer to CBan
    CBan *m_CBanPtr;

    ///attach pointer to CBan
    inline void attach(CBan *ptr) { m_CBanPtr = ptr; m_CBanPtr->riseRefCnt(); }

    ///detach pointer to CBan
    inline void detach() { m_CBanPtr->reduceRefCnt(); }

public:

    /// default constructor calls CBan constructor and link to it
    CBank() { m_CBanPtr = new CBan(); } //todo ted CBan konstruktor automaticky nastavi link na 1. ale nemel bych spsi oddelit -> resit pomoci attach ?

    ///preform shallow copy
    CBank(const CBank &other) { attach(other.m_CBanPtr); }

    ///destructor detaches CBan; CBan resolve the rest by number of left over references ; even delete itself
    ~CBank() { detach(); }

    ///preform shallow copy
    void operator=(const CBank &other) { if (this == &other) return;detach();attach(other.m_CBanPtr); }

    ///creates new CAccount object and set initial value
    bool NewAccount(const char *accID, int initialBalance);

    ///substract amount from debAccID, add to credAccID, add to history to both accounts
    bool Transaction(const char *debAccID, const char *credAccID, int amount, const char *signature);

    ///delete history from account, set initialState to currentState
    bool TrimAccount(const char *accID);

    ///return account if found, rise exception otherwise
    CAccount &Account(const char *accID) const;
};


///*********************************************************************************************
///*************************************CBANK METHODS*******************************************
///*********************************************************************************************

/**
 * @param accID
 * @param initialBalance
 * @return
 */
bool CBank::NewAccount(const char *accID, int initialBalance) {

  ///account must not exist yet
  try {
    Account(accID);
  } catch (int x) {

    ////in case of shallow copy, preform copy on write CBan (CAcc remains the same)
    if (m_CBanPtr->getRefCnt() > 1) {
      CBan *tmp = m_CBanPtr;
      detach();
      m_CBanPtr = new CBan(*tmp);
    }

    ///add new account
    m_CBanPtr->add(accID, initialBalance);
    return true;
  }

  ///account allready exist
  return false;
}

/**
 * @param debAccID
 * @param credAccID
 * @param amount
 * @param signature
 * @return
 */
bool CBank::Transaction(const char *debAccID, const char *credAccID, int amount, const char *signature) {
  CAccount *from;
  CAccount *to;

  ///sender must differ from recipient && amount must not be negative && signature must exist
  if (!strcmp(debAccID, credAccID) || amount < 0 || signature == NULL)
    return false;

  ///both account must exist
  try {
    from = &Account(debAccID);
    to = &Account(credAccID);
  } catch (int x) {
    return false;
  }

  ///in case of shallow copy, preform copy on write
  if (from->m_CAccPtr->getRefCnt() > 1) {

    ///if CBan is shallow copy, preform copy on write CBan (CAcc remains the same)
    if (m_CBanPtr->getRefCnt() > 1) {
      CBan *tmp = m_CBanPtr;
      detach();
      m_CBanPtr = new CBan(*tmp);
    }

    //todo make deep copy of both accounts
  }

  ///transfer money
  from->SendPayment(amount, credAccID, signature);
  to->RecievePayment(amount, debAccID, signature);
  return true;
}

/**
 * @param accID
 * @return
 */
bool CBank::TrimAccount(const char *accID) {
  CAccount *account;

  ///account must exist
  try {
    account = &Account(accID);
  } catch (int x) {
    return false;
  }

  ///in case of shallow copy, preform copy on write
  if (account->m_CAccPtr->getRefCnt() > 1) {

    ///if CBan is shallow copy, preform copy on write CBan (CAcc remains the same)
    if (m_CBanPtr->getRefCnt() > 1) {
      CBan *tmp = m_CBanPtr;
      detach();
      m_CBanPtr = new CBan(*tmp);
    }

    //todo make deep copy of both accounts
    //detach current CAccounts, create new ones with new CAcc and link them to the
  }

  ///delete transaction history
  account->Trim();
  return true;
}

/**
 * @param accID
 * @return
 */
CAccount & CBank::Account(const char *accID) const {

  ///find Account by accID in list of CBan accounts and return it
  for (int i = 0; i < m_CBanPtr->m_size; ++i)
    if (!strcmp(m_CBanPtr->m_arrAccounts[i].m_CAccPtr->m_ID, accID))
      return m_CBanPtr->m_arrAccounts[i];

  ///Account not found
  throw -1;
}

///*********************************************************************************************
///*********************************************************************************************
///*********************************************************************************************

#ifndef __PROGTEST__
int main ( void )
{
  ostringstream os;
  char accCpy[100], debCpy[100], credCpy[100], signCpy[100];


  CBank x0;
  assert ( x0 . NewAccount ( "123456", 1000 ) );
  assert ( x0 . NewAccount ( "987654", -500 ) );
  assert ( x0 . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" ) );
  assert ( x0 . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" ) );
  assert ( x0 . NewAccount ( "111111", 5000 ) );
  assert ( x0 . Transaction ( "111111", "987654", 290, "Okh6e+8rAiuT5=" ) );
  assert ( x0 . Account ( "123456" ). Balance ( ) ==  -2190 );
  assert ( x0 . Account ( "987654" ). Balance ( ) ==  2980 );
  assert ( x0 . Account ( "111111" ). Balance ( ) ==  4710 );
  os . str ( "" );
  os << x0 . Account ( "123456" );
  assert ( ! strcmp ( os . str () . c_str (), "123456:\n   1000\n - 300, to: 987654, sign: XAbG5uKz6E=\n - 2890, to: 987654, sign: AbG5uKz6E=\n = -2190\n" ) );
  os . str ( "" );
  os << x0 . Account ( "987654" );
  assert ( ! strcmp ( os . str () . c_str (), "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 290, from: 111111, sign: Okh6e+8rAiuT5=\n = 2980\n" ) );
  os . str ( "" );
  os << x0 . Account ( "111111" );
  assert ( ! strcmp ( os . str () . c_str (), "111111:\n   5000\n - 290, to: 987654, sign: Okh6e+8rAiuT5=\n = 4710\n" ) );
  assert ( x0 . TrimAccount ( "987654" ) );
  assert ( x0 . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" ) );
  os . str ( "" );
  os << x0 . Account ( "987654" );
  assert ( ! strcmp ( os . str () . c_str (), "987654:\n   2980\n + 123, from: 111111, sign: asdf78wrnASDT3W\n = 3103\n" ) );



  CBank x2;
  strncpy ( accCpy, "123456", sizeof ( accCpy ) );
  assert ( x2 . NewAccount ( accCpy, 1000 ));
  strncpy ( accCpy, "987654", sizeof ( accCpy ) );
  assert ( x2 . NewAccount ( accCpy, -500 ));
  strncpy ( debCpy, "123456", sizeof ( debCpy ) );
  strncpy ( credCpy, "987654", sizeof ( credCpy ) );
  strncpy ( signCpy, "XAbG5uKz6E=", sizeof ( signCpy ) );
  assert ( x2 . Transaction ( debCpy, credCpy, 300, signCpy ) );
  strncpy ( debCpy, "123456", sizeof ( debCpy ) );
  strncpy ( credCpy, "987654", sizeof ( credCpy ) );
  strncpy ( signCpy, "AbG5uKz6E=", sizeof ( signCpy ) );
  assert ( x2 . Transaction ( debCpy, credCpy, 2890, signCpy ) );
  strncpy ( accCpy, "111111", sizeof ( accCpy ) );
  assert ( x2 . NewAccount ( accCpy, 5000 ));
  strncpy ( debCpy, "111111", sizeof ( debCpy ) );
  strncpy ( credCpy, "987654", sizeof ( credCpy ) );
  strncpy ( signCpy, "Okh6e+8rAiuT5=", sizeof ( signCpy ) );
  assert ( x2 . Transaction ( debCpy, credCpy, 2890, signCpy ) );
  assert ( x2 . Account ( "123456" ). Balance ( ) ==  -2190 );
  assert ( x2 . Account ( "987654" ). Balance ( ) ==  5580 );
  assert ( x2 . Account ( "111111" ). Balance ( ) ==  2110 );
  os . str ( "" );
  os << x2 . Account ( "123456" );
  assert ( ! strcmp ( os . str () . c_str (), "123456:\n   1000\n - 300, to: 987654, sign: XAbG5uKz6E=\n - 2890, to: 987654, sign: AbG5uKz6E=\n = -2190\n" ) );
  os . str ( "" );
  os << x2 . Account ( "987654" );
  assert ( ! strcmp ( os . str () . c_str (), "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 2890, from: 111111, sign: Okh6e+8rAiuT5=\n = 5580\n" ) );
  os . str ( "" );
  os << x2 . Account ( "111111" );
  assert ( ! strcmp ( os . str () . c_str (), "111111:\n   5000\n - 2890, to: 987654, sign: Okh6e+8rAiuT5=\n = 2110\n" ) );
  assert ( x2 . TrimAccount ( "987654" ) );
  strncpy ( debCpy, "111111", sizeof ( debCpy ) );
  strncpy ( credCpy, "987654", sizeof ( credCpy ) );
  strncpy ( signCpy, "asdf78wrnASDT3W", sizeof ( signCpy ) );
  assert ( x2 . Transaction ( debCpy, credCpy, 123, signCpy ) );
  os . str ( "" );
  os << x2 . Account ( "987654" );
  assert ( ! strcmp ( os . str () . c_str (), "987654:\n   5580\n + 123, from: 111111, sign: asdf78wrnASDT3W\n = 5703\n" ) );



  CBank x4;
  assert ( x4 . NewAccount ( "123456", 1000 ) );
  assert ( x4 . NewAccount ( "987654", -500 ) );
  assert ( !x4 . NewAccount ( "123456", 3000 ) );
  assert ( !x4 . Transaction ( "123456", "666", 100, "123nr6dfqkwbv5" ) );
  assert ( !x4 . Transaction ( "666", "123456", 100, "34dGD74JsdfKGH" ) );
  assert ( !x4 . Transaction ( "123456", "123456", 100, "Juaw7Jasdkjb5" ) );
  try
  {
    x4 . Account ( "666" ). Balance ( );
    assert ( "Missing exception !!" == NULL );
  }
  catch ( ... )
  {
  }
  try
  {
    os << x4 . Account ( "666" ). Balance ( );
    assert ( "Missing exception !!" == NULL );
  }
  catch ( ... )
  {
  }
  assert ( !x4 . TrimAccount ( "666" ) );

  CBank x6;
  assert ( x6 . NewAccount ( "123456", 1000 ) );
  assert ( x6 . NewAccount ( "987654", -500 ) );
  assert ( x6 . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" ) );
  assert ( x6 . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" ) );
  assert ( x6 . NewAccount ( "111111", 5000 ) );
  assert ( x6 . Transaction ( "111111", "987654", 2890, "Okh6e+8rAiuT5=" ) );
  CBank x7 ( x6 );
  assert ( x6 . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" ) );
  assert ( x7 . Transaction ( "111111", "987654", 789, "SGDFTYE3sdfsd3W" ) );
  assert ( x6 . NewAccount ( "99999999", 7000 ) );
  assert ( x6 . Transaction ( "111111", "99999999", 3789, "aher5asdVsAD" ) );
  assert ( x6 . TrimAccount ( "111111" ) );
  assert ( x6 . Transaction ( "123456", "111111", 221, "Q23wr234ER==" ) );
  os . str ( "" );
  os << x6 . Account ( "111111" );
  assert ( ! strcmp ( os . str () . c_str (), "111111:\n   "
          "-1802\n "
          "+ 221, from: 123456, sign: Q23wr234ER==\n "
          "= -1581\n" ) );
  os . str ( "" );
  os << x6 . Account ( "99999999" );
  assert ( ! strcmp ( os . str () . c_str (), "99999999:\n   7000\n + 3789, from: 111111, sign: aher5asdVsAD\n = 10789\n" ) );
  os . str ( "" );
  os << x6 . Account ( "987654" );
  assert ( ! strcmp ( os . str () . c_str (), "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 2890, from: 111111, sign: Okh6e+8rAiuT5=\n + 123, from: 111111, sign: asdf78wrnASDT3W\n = 5703\n" ) );
  os . str ( "" );
  os << x7 . Account ( "111111" );
  assert ( ! strcmp ( os . str () . c_str (), "111111:\n   5000\n - 2890, to: 987654, sign: Okh6e+8rAiuT5=\n - 789, to: 987654, sign: SGDFTYE3sdfsd3W\n = 1321\n" ) );
  try
  {
    os << x7 . Account ( "99999999" ). Balance ( );
    assert ( "Missing exception !!" == NULL );
  }
  catch ( ... )
  {
  }
  os . str ( "" );
  os << x7 . Account ( "987654" );
  assert ( ! strcmp ( os . str () . c_str (), "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 2890, from: 111111, sign: Okh6e+8rAiuT5=\n + 789, from: 111111, sign: SGDFTYE3sdfsd3W\n = 6369\n" ) );

  CBank x8;
  CBank x9;
  assert ( x8 . NewAccount ( "123456", 1000 ) );
  assert ( x8 . NewAccount ( "987654", -500 ) );
  assert ( x8 . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" ) );
  assert ( x8 . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" ) );
  assert ( x8 . NewAccount ( "111111", 5000 ) );
  assert ( x8 . Transaction ( "111111", "987654", 2890, "Okh6e+8rAiuT5=" ) );
  x9 = x8;
  assert ( x8 . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" ) );
  assert ( x9 . Transaction ( "111111", "987654", 789, "SGDFTYE3sdfsd3W" ) );
  assert ( x8 . NewAccount ( "99999999", 7000 ) );
  assert ( x8 . Transaction ( "111111", "99999999", 3789, "aher5asdVsAD" ) );
  assert ( x8 . TrimAccount ( "111111" ) );
  os . str ( "" );
  os << x8 . Account ( "111111" );
  assert ( ! strcmp ( os . str () . c_str (), "111111:\n   -1802\n = -1802\n" ) );
  os . str ( "" );
  os << x9 . Account ( "111111" );
  assert ( ! strcmp ( os . str () . c_str (), "111111:\n   5000\n - 2890, to: 987654, sign: Okh6e+8rAiuT5=\n - 789, to: 987654, sign: SGDFTYE3sdfsd3W\n = 1321\n" ) );

  return 0;
}
#endif /* __PROGTEST__ */
