#ifndef __PROGTEST__

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;
#endif /* __PROGTEST__ */

template<typename T>
class simpleVector {

private:
    T *m_buffer;
    size_t m_capacity;
    size_t m_size;

    ///dynamically resizes buffer
    void resize() {
        if (m_capacity == 0) {
            m_capacity = 20;
            m_buffer = new T[m_capacity];
            return;
        }
        m_capacity += 1;
        T *newBuffer = new T[m_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            newBuffer[i] = m_buffer[i];
        }
        delete[] m_buffer;
        m_buffer = newBuffer;
    }

public:

    simpleVector() : m_buffer(NULL), m_capacity(0), m_size(0) {};

    ~simpleVector() {
        delete[] m_buffer;
    }

    void clear() {

        delete[] m_buffer;

        m_buffer = NULL;
        m_capacity = 0;
        m_size = 0;
    }

    ///returns number of type elements currently stored in vector
    inline size_t size() const { return m_size; }

    ///adds element to back of the vector
    inline void pushBack(T &element) {
        if (m_size == m_capacity)
            resize();
        m_buffer[m_size++] = element;
    }

    ///return writable type at index
    inline T &operator[](size_t index) { return m_buffer[index]; }

    ///return read-only type at index
    inline const T &operator[](size_t index) const { return m_buffer[index]; }
};

struct HistoryRecord {
private:
    unsigned m_refCnt;
public:
    int m_amount;
    bool m_sent;
    char *m_account;
    char *m_signature;


    HistoryRecord(int amount, bool sent, const char *account, const char *signature) : m_refCnt(1), m_amount(amount),
                                                                                       m_sent(sent) {
        m_account = new char[strlen(account) + 1];
        strcpy(m_account, account);

        m_signature = new char[strlen(signature) + 1];
        strcpy(m_signature, signature);
    }

    ~HistoryRecord() {
        delete[] m_account;
        delete[] m_signature;
    }

    void riseRefCnt() {
        m_refCnt++;
    }

    void reduceRefCnt() {
        --m_refCnt;
        if (m_refCnt == 0 ) /// KITTEN_KILLER fix
            delete this;
    }

    friend ostream &operator<<(ostream &os, const HistoryRecord &other);
};

ostream &operator<<(ostream &os, const HistoryRecord &other) {
    os << " ";

    if (other.m_sent)
        os << "- " << other.m_amount << ", to: ";
    else
        os << "+ " << other.m_amount << ", from: ";


    os << other.m_account << ", sign: " << other.m_signature << "\n";
    return os;
}

///*****************************************************************************************************
///**************************************   CACCOUNT  **************************************************
///*****************************************************************************************************

class CAccount {
private:
    size_t m_RefCnt;

    ///CAccount data
    long m_initBal;
    long m_currBal;

    simpleVector<HistoryRecord *> history;

public:
    char *m_ID;

    ///default constructor
    CAccount(const char *accID, int initBal) : m_RefCnt(1), m_initBal(initBal), m_currBal(initBal), history(),
                                               m_ID(NULL) {
        m_ID = new char[strlen(accID) + 1];
        strcpy(m_ID, accID);
    };

    ///copy constructor - DEEPCOPY !!!  NOT SO DEEP
    CAccount(const CAccount &other) : m_RefCnt(1), m_initBal(other.m_initBal), m_currBal(other.m_currBal), history(),
                                      m_ID(NULL) {

        ///copy other account ID
        m_ID = new char[strlen(other.m_ID) + 1];
        strcpy(m_ID, other.m_ID);

        ///copy other account history; TED UZ TO NENI DEEP COPY
        for (size_t i = 0; i < other.history.size(); ++i) {
            //HistoryRecord * newRecord = new  HistoryRecord(other.history[i]->m_amount, other.history[i]->m_sent, other.history[i]->m_account, other.history[i]->m_signature) ;

            HistoryRecord *newOne = (other.history[i]);


            history.pushBack(newOne);
        }
    }

    ///default destructor ; 1. trim history, 2. delete char * ID
    ~CAccount() {
        Trim();

        delete[] m_ID;
    }

    ///compare by ID
    inline bool equals(const char *accID) const { return !strcmp(m_ID, accID); }

    bool operator==(const CAccount &other) {

        return !strcmp(m_ID, other.m_ID);
    }

    ///increase ref counter
    inline void riseRefCnt() {
        m_RefCnt++;
        for (size_t i = 0; i < history.size(); ++i)
            history[i]->riseRefCnt();
    }

    ///decrease ref counter ; if counter zero delete yourself ; reduce also history counter
    inline void reduceRefCnt() {
        --m_RefCnt;

        for (size_t i = 0; i < history.size(); ++i)
            history[i]->reduceRefCnt(); //tady uz muze nejaky historyRecord zaniknout....

        if (m_RefCnt == 0) {
            delete this;
        }
    }

    ///decrease ref counter ; if counter zero delete yourself
    inline void reduceRefCnt_notHistory() {
        --m_RefCnt;

        if (m_RefCnt == 0) { //fix 1
            delete this;
        }
    }


    ///true if more then one reference
    inline bool moreReferences() const { return m_RefCnt > 1; }

    ///return current balanace
    inline long Balance() const { return m_currBal; }

    ///delete history
    void Trim();

    ///substract from current balance and write record to History
    void SendPayment(int ammount, const char *to, const char *signature);

    ///add to current balance and write record to History
    void RecievePayment(int ammount, const char *from, const char *signature);

    ///send account info to output
    friend ostream &operator<<(ostream &os, const CAccount &other);
};

///*********************************************************************************************
///******************************    CACCOUNT METHODS   ****************************************
///*********************************************************************************************

ostream &operator<<(ostream &os, const CAccount &other) {
    os << other.m_ID << ":\n   " << other.m_initBal << "\n";

    for (size_t i = 0; i < other.history.size(); ++i)
        os << (*other.history[i]);

    os << " = " << other.m_currBal << endl;
    return os;
}

void CAccount::Trim() {

    if (moreReferences())
        throw;

    for (size_t i = 0; i < history.size(); ++i) {
        //  delete history[i];
        history[i]->reduceRefCnt();
    }

    history.clear();

    m_initBal = m_currBal;
}

void CAccount::SendPayment(int ammount, const char *to, const char *signature) {
    m_currBal -= ammount;
    HistoryRecord *newRecord = new HistoryRecord(ammount, true, to, signature);
    history.pushBack(newRecord);
}

void CAccount::RecievePayment(int ammount, const char *from, const char *signature) {
    m_currBal += ammount;
    HistoryRecord *newRecord = new HistoryRecord(ammount, false, from, signature);
    history.pushBack(newRecord);
}


///*****************************************************************************************************
///**************************************   CBAN   *****************************************************
///*****************************************************************************************************

struct CBan {
private:
    size_t m_RefCnt;

public:
    simpleVector<CAccount *> m_Accounts;

    ///default constructor
    CBan() : m_RefCnt(1), m_Accounts() {};

    ///copy constructor which copy CAccounts array
    CBan(CBan &other) : m_RefCnt(1), m_Accounts() {
        for (size_t i = 0; i < other.m_Accounts.size(); ++i) {
            m_Accounts.pushBack(other.m_Accounts[i]);
        }
        ///not rising CAcc refCnt because it was allready risen when shallow copy of Cbank was made...
    };

    ///destructor will this call simpleVector destructor ???
    ~CBan() {}

    ///rise this(CBan) refCnt ; rise refCnt on all CAcc
    void riseRefCnt();

    ///reduce this(CBan) refCnt only
    void reduceRefCnt_onlyCBan();

    ///reduce this(CBan) refCnt AND reduce CAcc refCnt ( deleting CBank )
    void reduceRefCnt_accounts_and_history();

    void reduceRefCnt_CBan_Accounts_notHistory();

    inline bool moreReferences() const { return m_RefCnt > 1; }

    void add(const char *accID, int initialBalance);

    CAccount *deepCopyAccount(CAccount &account);

};

///*********************************************************************************************
///**********************************    CBAN METHODS   ****************************************
///*********************************************************************************************

void CBan::riseRefCnt() {

    ///rise nuber of references here (on CBan)
    m_RefCnt++;

    ///rise of references on all CAcc
    for (size_t i = 0; i < m_Accounts.size(); ++i) {
        m_Accounts[i]->riseRefCnt();
    }
}

void CBan::reduceRefCnt_CBan_Accounts_notHistory() {
    ///reduce nuber of references here (on CBan)
    m_RefCnt--;

    ///reduce nuber of references on all CAcc ; if referece on Cacc is 0, it'll dele itself
    for (size_t i = 0; i < m_Accounts.size(); ++i) {
        m_Accounts[i]->reduceRefCnt_notHistory();
    }

    ///if m_RefCnt is zero delete yourself (CBan)
    if (m_RefCnt == 0)
        delete this;
}

void CBan::reduceRefCnt_accounts_and_history() {
    ///reduce nuber of references here (on CBan)
    m_RefCnt--;

    ///reduce nuber of references on all CAcc ; if referece on Cacc is 0, it'll dele itself
    for (size_t i = 0; i < m_Accounts.size(); ++i) {
        m_Accounts[i]->reduceRefCnt();
    }

    ///if m_RefCnt is zero delete yourself (CBan)
    if (m_RefCnt == 0)
        delete this;
}

void CBan::reduceRefCnt_onlyCBan() {

    ///reduce nuber of references here (on CBan)
    m_RefCnt--;

    ///if m_RefCnt is zero delete yourself (CBan)
    if (m_RefCnt == 0)
        delete this;
}

void CBan::add(const char *accID, int initialBalance) {
    CAccount *newAccount = new CAccount(accID, initialBalance);
    m_Accounts.pushBack(newAccount);
}

CAccount *CBan::deepCopyAccount(CAccount &account) {

///NOT SO DEEP COPY; history reamains the same
    CAccount *newAccount = new CAccount(account);
    account.reduceRefCnt_notHistory();  /// history remains Same

    for (size_t i = 0; i < m_Accounts.size(); ++i) {
        if (*m_Accounts[i] == *newAccount) {
            m_Accounts[i] = newAccount;
            return m_Accounts[i];
        }
    }
    return NULL;
}

///*****************************************************************************************************
///**************************************   CBANK   ****************************************************
///*****************************************************************************************************

class CBank {
private:

    ///pointer to CBan
    CBan *m_CBanPtr;

    ///attach pointer to CBan
    inline void attach(CBan *ptr) {
        m_CBanPtr = ptr;
        m_CBanPtr->riseRefCnt();
    }

    ///detach pointer to CBan + reduce refCnt on all Caccounts
    inline void detach() { m_CBanPtr->reduceRefCnt_CBan_Accounts_notHistory(); } //hope doying it right

    inline void detach_all() { m_CBanPtr->reduceRefCnt_accounts_and_history(); } //hope doying it right

    ///detach CBan, create wery own CBan, but CAccount left same
    void deepCopyCBan() {
        CBan *tmp = m_CBanPtr;
        m_CBanPtr->reduceRefCnt_onlyCBan();
        m_CBanPtr = new CBan(*tmp);
    }

public:

    /// default constructor - calls CBan constructor and link to it
    CBank() { m_CBanPtr = new CBan(); }

    ///preform shallow copy
    CBank(const CBank &other) { attach(other.m_CBanPtr); }

    ///destructor deteach_all == CBAn + all ACCounts + all its History ;
    ~CBank() {

        for (size_t i = 0; i < m_CBanPtr->m_Accounts.size(); ++i)
            TrimAccount(m_CBanPtr->m_Accounts[i]->m_ID);

        detach_all();

    }

    ///preform shallow copy ; detach only CBan
    void operator=(const CBank &other) {
        if (this->m_CBanPtr == other.m_CBanPtr)
            return;
        detach();
        attach(other.m_CBanPtr);
    }

    ///creates new CAccount object and set initial value
    bool NewAccount(const char *accID, int initialBalance);

    ///substract amount from debAccID, add to credAccID, add to history to both accounts
    bool Transaction(const char *debAccID, const char *credAccID, int amount, const char *signature);

    ///delete history from account, set initialState to currentState
    bool TrimAccount(const char *accID);

    ///return account if found, rise exception otherwise
    CAccount &Account(const char *accID) const;

    friend ostream &operator<<(ostream &os, CBank &other);
};

///*********************************************************************************************
///*************************************CBANK METHODS*******************************************
///*********************************************************************************************

CAccount &CBank::Account(const char *accID) const {

    ///find Account by accID in list of CBan accounts and return it
    for (size_t i = 0; i < m_CBanPtr->m_Accounts.size(); ++i)
        if (m_CBanPtr->m_Accounts[i]->equals(accID))
            return *(m_CBanPtr->m_Accounts[i]);

    ///Account not found
    throw -1;
}

bool CBank::NewAccount(const char *accID, int initialBalance) {

    ///account must not exist yet
    try {
        Account(accID);
        return false;

    } catch (int x) {

        ////in case of shallow copy, deep copy CBan (CAcc remains the same)
        if (m_CBanPtr->moreReferences())
            deepCopyCBan();

        ///add new account
        m_CBanPtr->add(accID, initialBalance);
        return true;
    }
}

bool CBank::Transaction(const char *debAccID, const char *credAccID, int amount, const char *signature) {
    CAccount *from, *to;

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

    ///in case of shallow copy, preform copy on write//
    if (from->moreReferences() || to->moreReferences()) {

        ///if CBan is shallow copy, deep copy CBan  (CAcc remains the same)
        if (m_CBanPtr->moreReferences())
            deepCopyCBan();


        if (from->moreReferences())
            from = m_CBanPtr->deepCopyAccount(*from);
        if (to->moreReferences())
            to = m_CBanPtr->deepCopyAccount(*to);
    }

    ///transfer money
    from->SendPayment(amount, credAccID, signature);
    to->RecievePayment(amount, debAccID, signature);
    return true;
}

bool CBank::TrimAccount(const char *accID) {
    CAccount *account;

    ///account must exist
    try {
        account = &Account(accID);
    } catch (int x) {
        return false;
    }

    ///in case of shallow copy, preform copy on write
    if (account->moreReferences()) {

        ///if CBan is shallow copy, deep copy CBan  (CAcc remains the same)
        if (m_CBanPtr->moreReferences())
            deepCopyCBan();

        /// make deep copy of CAccount
        account = m_CBanPtr->deepCopyAccount(*account);
    }

    ///delete transaction history
    account->Trim();
    return true;
}

ostream &operator<<(ostream &os, CBank &other) {
    for (size_t i = 0; i < other.m_CBanPtr->m_Accounts.size(); ++i) {

        os << "account number:  " << i << endl;
        os << *(other.m_CBanPtr->m_Accounts[i]) << endl;
        os << "--------------------------------------" << endl;
    }

    os << "***************************" << endl;
    os << "***************************" << endl;
    return os;
}

///*********************************************************************************************
///*********************************************************************************************
///*********************************************************************************************

#ifndef __PROGTEST__

int main(void) {
    ostringstream os;
    char accCpy[100], debCpy[100], credCpy[100], signCpy[100];


    CBank x0;
    assert (x0.NewAccount("123456", 1000));
    assert (x0.NewAccount("987654", -500));
    assert (x0.Transaction("123456", "987654", 300, "XAbG5uKz6E="));
    assert (x0.Transaction("123456", "987654", 2890, "AbG5uKz6E="));
    assert (x0.NewAccount("111111", 5000));
    assert (x0.Transaction("111111", "987654", 290, "Okh6e+8rAiuT5="));
    assert (x0.Account("123456").Balance() == -2190);
    assert (x0.Account("987654").Balance() == 2980);
    assert (x0.Account("111111").Balance() == 4710);
    os.str("");
    os << x0.Account("123456");

    assert (!strcmp(os.str().c_str(),
                    "123456:\n   1000\n - 300, to: 987654, sign: XAbG5uKz6E=\n - 2890, to: 987654, sign: AbG5uKz6E=\n = -2190\n"));
    os.str("");
    os << x0.Account("987654");
    assert (!strcmp(os.str().c_str(),
                    "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 290, from: 111111, sign: Okh6e+8rAiuT5=\n = 2980\n"));
    os.str("");
    os << x0.Account("111111");
    assert (!strcmp(os.str().c_str(), "111111:\n   5000\n - 290, to: 987654, sign: Okh6e+8rAiuT5=\n = 4710\n"));
    assert (x0.TrimAccount("987654"));
    assert (x0.Transaction("111111", "987654", 123, "asdf78wrnASDT3W"));
    os.str("");
    os << x0.Account("987654");
    assert (!strcmp(os.str().c_str(), "987654:\n   2980\n + 123, from: 111111, sign: asdf78wrnASDT3W\n = 3103\n"));


    CBank x2;
    strncpy(accCpy, "123456", sizeof(accCpy));
    assert (x2.NewAccount(accCpy, 1000));
    strncpy(accCpy, "987654", sizeof(accCpy));
    assert (x2.NewAccount(accCpy, -500));
    strncpy(debCpy, "123456", sizeof(debCpy));
    strncpy(credCpy, "987654", sizeof(credCpy));
    strncpy(signCpy, "XAbG5uKz6E=", sizeof(signCpy));
    assert (x2.Transaction(debCpy, credCpy, 300, signCpy));
    strncpy(debCpy, "123456", sizeof(debCpy));
    strncpy(credCpy, "987654", sizeof(credCpy));
    strncpy(signCpy, "AbG5uKz6E=", sizeof(signCpy));
    assert (x2.Transaction(debCpy, credCpy, 2890, signCpy));
    strncpy(accCpy, "111111", sizeof(accCpy));

    assert (x2.NewAccount(accCpy, 5000));
    strncpy(debCpy, "111111", sizeof(debCpy));
    strncpy(credCpy, "987654", sizeof(credCpy));
    strncpy(signCpy, "Okh6e+8rAiuT5=", sizeof(signCpy));
    assert (x2.Transaction(debCpy, credCpy, 2890, signCpy));
    assert (x2.Account("123456").Balance() == -2190);
    assert (x2.Account("987654").Balance() == 5580);
    assert (x2.Account("111111").Balance() == 2110);
    os.str("");
    os << x2.Account("123456");
    assert (!strcmp(os.str().c_str(),
                    "123456:\n   1000\n - 300, to: 987654, sign: XAbG5uKz6E=\n - 2890, to: 987654, sign: AbG5uKz6E=\n = -2190\n"));
    os.str("");
    os << x2.Account("987654");
    assert (!strcmp(os.str().c_str(),
                    "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 2890, from: 111111, sign: Okh6e+8rAiuT5=\n = 5580\n"));
    os.str("");
    os << x2.Account("111111");
    assert (!strcmp(os.str().c_str(), "111111:\n   5000\n - 2890, to: 987654, sign: Okh6e+8rAiuT5=\n = 2110\n"));
    assert (x2.TrimAccount("987654"));
    strncpy(debCpy, "111111", sizeof(debCpy));
    strncpy(credCpy, "987654", sizeof(credCpy));
    strncpy(signCpy, "asdf78wrnASDT3W", sizeof(signCpy));
    assert (x2.Transaction(debCpy, credCpy, 123, signCpy));
    os.str("");
    os << x2.Account("987654");
    assert (!strcmp(os.str().c_str(), "987654:\n   5580\n + 123, from: 111111, sign: asdf78wrnASDT3W\n = 5703\n"));


    CBank x4;
    assert (x4.NewAccount("123456", 1000));
    assert (x4.NewAccount("987654", -500));
    assert (!x4.NewAccount("123456", 3000));
    assert (!x4.Transaction("123456", "666", 100, "123nr6dfqkwbv5"));
    assert (!x4.Transaction("666", "123456", 100, "34dGD74JsdfKGH"));
    assert (!x4.Transaction("123456", "123456", 100, "Juaw7Jasdkjb5"));
    try {
        x4.Account("666").Balance();
        assert ("Missing exception !!" == NULL);
    }
    catch (...) {
    }
    try {
        os << x4.Account("666").Balance();
        assert ("Missing exception !!" == NULL);
    }
    catch (...) {
    }
    assert (!x4.TrimAccount("666"));


    CBank x6;
    assert (x6.NewAccount("123456", 1000));
    assert (x6.NewAccount("987654", -500));
    assert (x6.Transaction("123456", "987654", 300, "XAbG5uKz6E="));
    assert (x6.Transaction("123456", "987654", 2890, "AbG5uKz6E="));
    assert (x6.NewAccount("111111", 5000));


    assert (x6.Transaction("111111", "987654", 2890, "Okh6e+8rAiuT5="));  //prvni
    CBank x7(x6);


    assert (x6.Transaction("111111", "987654", 123, "asdf78wrnASDT3W")); //druha


    assert (x7.Transaction("111111", "987654", 789, "SGDFTYE3sdfsd3W"));

    assert (x6.NewAccount("99999999", 7000));
    assert (x6.Transaction("111111", "99999999", 3789, "aher5asdVsAD")); //treti


    assert (x6.TrimAccount("111111"));


    assert (x6.Transaction("123456", "111111", 221, "Q23wr234ER==")); //prvni

    os.str("");
    os << x6.Account("111111");

    assert (!strcmp(os.str().c_str(), "111111:\n   -1802\n + 221, from: 123456, sign: Q23wr234ER==\n = -1581\n"));
    os.str("");
    os << x6.Account("99999999");
    assert (!strcmp(os.str().c_str(), "99999999:\n   7000\n + 3789, from: 111111, sign: aher5asdVsAD\n = 10789\n"));
    os.str("");
    os << x6.Account("987654");
    assert (!strcmp(os.str().c_str(),
                    "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 2890, from: 111111, sign: Okh6e+8rAiuT5=\n + 123, from: 111111, sign: asdf78wrnASDT3W\n = 5703\n"));
    os.str("");
    os << x7.Account("111111");


    cout << x7.Account("111111");
    assert (!strcmp(os.str().c_str(),
                    "111111:\n   5000\n - 2890, to: 987654, sign: Okh6e+8rAiuT5=\n - 789, to: 987654, sign: SGDFTYE3sdfsd3W\n = 1321\n"));
    try {
        os << x7.Account("99999999").Balance();
        assert ("Missing exception !!" == NULL);
    }
    catch (...) {
    }
    os.str("");
    os << x7.Account("987654");
    assert (!strcmp(os.str().c_str(),
                    "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 2890, from: 111111, sign: Okh6e+8rAiuT5=\n + 789, from: 111111, sign: SGDFTYE3sdfsd3W\n = 6369\n"));

    CBank x8;
    CBank x9;
    assert (x8.NewAccount("123456", 1000));
    assert (x8.NewAccount("987654", -500));
    assert (x8.Transaction("123456", "987654", 300, "XAbG5uKz6E="));
    assert (x8.Transaction("123456", "987654", 2890, "AbG5uKz6E="));
    assert (x8.NewAccount("111111", 5000));
    assert (x8.Transaction("111111", "987654", 2890, "Okh6e+8rAiuT5="));
    x9 = x8;
    assert (x8.Transaction("111111", "987654", 123, "asdf78wrnASDT3W"));
    assert (x9.Transaction("111111", "987654", 789, "SGDFTYE3sdfsd3W"));
    assert (x8.NewAccount("99999999", 7000));
    assert (x8.Transaction("111111", "99999999", 3789, "aher5asdVsAD"));
    assert (x8.TrimAccount("111111"));
    os.str("");
    os << x8.Account("111111");
    assert (!strcmp(os.str().c_str(), "111111:\n   -1802\n = -1802\n"));
    os.str("");
    os << x9.Account("111111");
    assert (!strcmp(os.str().c_str(),
                    "111111:\n   5000\n - 2890, to: 987654, sign: Okh6e+8rAiuT5=\n - 789, to: 987654, sign: SGDFTYE3sdfsd3W\n = 1321\n"));

    return 0;
}

#endif /* __PROGTEST__ */
