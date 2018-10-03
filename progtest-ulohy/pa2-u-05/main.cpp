#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
//#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>

using namespace std;

class CDate {
private:
    int16_t m_Year;
    int8_t m_Month;
    int8_t m_Day;

public:
    CDate(int y, int m, int d) : m_Year(y), m_Month(m), m_Day(d) {}

    int Compare(const CDate &x) const {
        if (m_Year != x.m_Year)
            return m_Year - x.m_Year;

        if (m_Month != x.m_Month)
            return m_Month - x.m_Month;

        return m_Day - x.m_Day;

    }

    int Year(void) const { return m_Year; }

    int Month(void) const { return m_Month; }

    int Day(void) const { return m_Day; }

    friend ostream &operator<<(ostream &os, const CDate &x) {
        char oldFill = os.fill();
        return os << setfill('0') << setw(4) << x.m_Year << "-"
                  << setw(2) << (int) x.m_Month << "-"
                  << setw(2) << (int) x.m_Day
                  << setfill(oldFill);
    }
};

#endif /* __PROGTEST__ */
enum invoiceIs {
    INVOICE_MATCHED, INVOICE_UNMATCHED, INVOICE_NOT_PRESENT
};


size_t hashAlgorithm(const string & x) {
    ///@cite http://www.cse.yorku.ca/~oz/hash.html
    size_t hash = 5381;

    for (unsigned int i = 0; i < x.length() && i < 16; i++)
        hash = ((hash << 5) + hash) + (int) x[i];

    return hash;
}

///*************************************************************************************************
///******************************************  SORT OP  ********************************************
///*************************************************************************************************

struct pairSortOp{
    pairSortOp(const int key, bool ascending) : m_key(key), m_ascending(ascending) {}
    const int m_key;
    bool m_ascending;
    bool operator == (const pairSortOp &other) const {
        return m_key == other.m_key;
    }
};

class CSortOpt {
private:


    list<pairSortOp> sortOptions;

public:
    static const int BY_DATE = 0;
    static const int BY_BUYER = 1;
    static const int BY_SELLER = 2;
    static const int BY_AMOUNT = 3;
    static const int BY_VAT = 4;

    CSortOpt(void) : sortOptions() {}
    CSortOpt & AddKey(int key, bool ascending = true) {
        pairSortOp newSortOp(key,ascending);
        list<pairSortOp>::const_iterator itFinder = find(sortOptions.begin(), sortOptions.end(), newSortOp);

        if(itFinder != sortOptions.end()) {
            sortOptions.erase(itFinder);
        }
        sortOptions.push_back(newSortOp);

        return *this;
    }

    const list<pairSortOp> & getSortOptions() const {
        return sortOptions;
    }

};

///*************************************************************************************************
///******************************************  INVOICE  ********************************************
///*************************************************************************************************
bool equal(double a, double b)  {

    double diff =  a > b ? a - b : b - a;
    double epsilon = 0.00000001;

    if (a == b)
        return true;
    else
        return diff / (a + b) < epsilon;
}

class CInvoice {
private:
    CDate m_date;
    string m_seller;
    string m_buyer;
    int m_amount;
    double m_VAT;
    size_t m_registredNum;
    string m_sellerOptimized;
    string m_buyerOptimized;

    string m_sellerLowercase;
    string m_buyerLowercase;

public:
    CInvoice(const CDate &date,
             const string &seller,
             const string &buyer,
             int amount,
             double VAT,
             size_t registredNum = 0,
             string optimizedSeller = "",
             string optimizedBuyer = "",
             string sellerLowercase = "",
             string buyerLowercase = ""
    )

            : m_date(date.Year(), date.Month(), date.Day()),
              m_seller(seller),
              m_buyer(buyer),
              m_amount(amount),
              m_VAT(VAT),
              m_registredNum(registredNum),
              m_sellerOptimized(optimizedSeller),
              m_buyerOptimized(optimizedBuyer),
              m_sellerLowercase(sellerLowercase),
              m_buyerLowercase(buyerLowercase)
    {
    }

    bool operator==(CInvoice const &other) const {

        bool istrue = false;

        if( m_date.Compare(other.m_date) == 0 &&

               m_sellerOptimized == (other.m_sellerOptimized) &&

               m_buyerOptimized == (other.m_buyerOptimized) &&

               m_amount == other.m_amount  &&

                equal ( m_VAT ,  other.m_VAT  ) )

            istrue = true;

        return istrue;
    }

    CDate Date(void) const { return m_date; }

    string Buyer(void) const { return m_buyer; }

    string Seller(void) const { return m_seller; }

    string  OptimizedBuyer(void) const { return m_buyerOptimized; }

    string  OptimizedSeller(void) const { return m_sellerOptimized; }


    string  LowercaseBuyer(void) const { return m_buyerLowercase; }

    string  LowercaseSeller(void) const { return m_sellerLowercase; }

    int Amount(void) const { return m_amount; }

    double VAT(void) const { return m_VAT; }

    size_t registerNum(void) const { return m_registredNum; }

    friend ostream &operator << (ostream & os, CInvoice & inv){

        os << inv.m_date.Year() << ", " <<  inv.m_date.Month() << ", " << inv.m_date.Day() << ", " << inv.m_seller
           << " " << inv.m_buyer << ", " << inv.m_amount << ",  " << inv.m_VAT << endl;

           return os;
    }
};

///*************************************************************************************************
///******************************************  COMPANY  ********************************************
///*************************************************************************************************
struct hashCInvoice {

    string createString ( const CInvoice &invoice )const {
        string newString =  ( invoice.OptimizedBuyer() );
        newString +=  ( invoice.OptimizedSeller() );
       // newString += invoice.Amount();
       // newString += invoice.Date().Year();
      //  newString += invoice.Date().Month();
      //  newString += invoice.Date().Day();
        return newString;
    }
    size_t operator()(const CInvoice * const & invoice) const {
        return hashAlgorithm(createString(*invoice));
    }
};

struct compareInvoice {
    bool operator()(const CInvoice *const &a, const CInvoice * const &b) const {
        return *a == *b;
    }
};

class CCompany {
private:
  static string optimizeName(const string &name){
      string nameCopy;
      size_t i;

      ///remove spaces from beginig
      for (i = 0; i < name.size(); ++i) {
          if (name[i] != ' ')
              break;
      }

      ///remove spaces from middle and end
      for (; i < name.size(); ++i) {

          if (name[i] != ' ')
              nameCopy += name[i];

          else {
              while (++i < name.size()) { if (name[i] != ' ') break; }

              /// if there are still some character  left, add it
              if (i < name.size()) {
                  nameCopy += ' ';
                  nameCopy += name[i];
              }
          }
      }
      transform(nameCopy.begin(), nameCopy.end(), nameCopy.begin(), ::tolower);
      return nameCopy;

  }

    static string toLower(const string & name){
        string nameCopy = name;
        transform(nameCopy.begin(), nameCopy.end(), nameCopy.begin(), ::tolower);
        return nameCopy;
    }

public:
    unordered_set<const CInvoice *, hashCInvoice, compareInvoice> m_matched;
    unordered_set<const CInvoice *, hashCInvoice, compareInvoice> m_unmatched;
    unordered_set<const CInvoice *, hashCInvoice, compareInvoice> m_unmatched_from_others;


    string m_nameOfficial;
    string m_nameOptimized;

    string m_nameLowercase;

    CCompany(const string &name) : m_nameOfficial(name), m_nameOptimized(optimizeName(name) ) , m_nameLowercase(toLower(name))   {}

    inline void addToMatched(const CInvoice *invoice) { m_matched.insert(invoice); }
    inline void addToUnmatched(const CInvoice *invoice) { m_unmatched.insert(invoice); }
    inline void addToUnmatchedFromOthers(const CInvoice *invoice) { m_unmatched_from_others.insert(invoice); } //todo DONE add to Unmatched from others

    const CInvoice *haveInvoiceMatched(const CInvoice *invoice) const;
    const CInvoice *haveInvoiceUnmatched(const CInvoice * invoice) const;
  //  const CInvoice *haveInvoiceUnmatchedFromOthers(const CInvoice * invoice) const; //todo DO I NEED THIS ??? MOST PROBABLY NOT; Have Unmatched from others


    void UnmatchedToMatched(const CInvoice *invoice);
    void MatchedToUnmatched(const CInvoice *invoice);


    void removeUnmatched(const CInvoice *invoice);
    void removeMatched(const CInvoice *invoice) {  m_matched.erase ( m_matched.find(invoice) );  }
    void removeUnmatchedFromOthers(const CInvoice *invoice)  {  m_unmatched_from_others.erase ( m_unmatched_from_others.find(invoice) );  } //todo DONE remove Unmatched from others
};


///************************************** COMPANY FUNCTIONS ****************************************
///*************************************************************************************************

const CInvoice * CCompany::haveInvoiceMatched(const CInvoice *invoice) const {
    unordered_set<const CInvoice *, hashCInvoice, compareInvoice>::const_iterator it;

    if ( (it = m_matched.find(invoice)) == m_matched.end() )
        return NULL;

    else
        return *it;
}

const CInvoice * CCompany::haveInvoiceUnmatched(const CInvoice * invoice) const {

    unordered_set<const CInvoice *, hashCInvoice, compareInvoice>::const_iterator it;

    if ( (it = m_unmatched.find(invoice)) == m_unmatched.end() )
        return NULL;

    else
        return *it;
}

void CCompany::UnmatchedToMatched(const CInvoice *invoice) {
    m_matched.insert(invoice);
    m_unmatched.erase ( m_unmatched.find(invoice) );
}

void CCompany::MatchedToUnmatched(const CInvoice *invoice) {
    m_unmatched.insert(invoice);
    m_matched.erase ( m_matched.find(invoice) );
}

void CCompany::removeUnmatched(const CInvoice *invoice) {
    unordered_set<const CInvoice *, hashCInvoice, compareInvoice>::const_iterator it = m_unmatched.find(invoice);
    const CInvoice * invoiceToDelete = *it;
    m_unmatched.erase ( it );
    delete invoiceToDelete;
}


///*************************************************************************************************
///*****************************************  REGISTER  ********************************************
///*************************************************************************************************
class CVATRegister {
private:
    ///custom HASHING functor
    struct hashCCompany{
        size_t operator()(const CCompany * const & company) const{
            return hashAlgorithm( company->m_nameOptimized );
        }
    };

///custom COMPARE functor ; compares by OPTIMIZED NAME
    struct compareCCompany{
        bool operator()(const CCompany * const & company, const CCompany * const & other) const{
            return company->m_nameOptimized == other->m_nameOptimized;
        }
    };

    unordered_set<CCompany *, hashCCompany, compareCCompany> m_companies;
    unordered_set<const CInvoice *, hashCInvoice, compareInvoice> m_allInvoices_dele_purpose;

    size_t m_noInvoiceID;
    
public:
    ///special data structure
    struct DoubleTriple {
        struct Quaternion{
            invoiceIs m_markedAs;
            unordered_set<CCompany *, hashCCompany, compareCCompany>::const_iterator m_itCompany;
            const CInvoice * m_pInvoice;
        };
        Quaternion m_buyer, m_seller;
        bool badCompanies;
    };

    CVATRegister(void): m_companies(), m_noInvoiceID(0) {}


    ~CVATRegister(void) {
        for (auto a : m_allInvoices_dele_purpose) {
            delete a;
        }

        for (auto a : m_companies) {
            delete a;
        }

    }

    bool RegisterCompany(const string &name);
    bool AddIssued(const CInvoice &x);
    bool AddAccepted(const CInvoice &x);
    bool DelIssued(const CInvoice &x);
    bool DelAccepted(const CInvoice &x);
    list <CInvoice> Unmatched(const string &company, const CSortOpt &sortBy) const;
    DoubleTriple getCompanyAndInvoiceInfo(const CInvoice & invoice) const;
    void getInfoAboutInvoice(const unordered_set<CCompany *, hashCCompany, compareCCompany>::const_iterator & itCompany,
                             const CInvoice * const & tempInvoice,
                             invoiceIs & m_markedAs,
                             const CInvoice *& m_pInvoice
    ) const;
};


///************************************** REGISTER COMPANY ************************************************
bool CVATRegister::RegisterCompany(const string &name) {
    CCompany *newCompany = new CCompany(name);

    if (m_companies.find(newCompany) != m_companies.end()) {
        delete newCompany;
        return false;
    }


    m_companies.insert(newCompany);
    return true;
}

///************************************** GET INFO INVOICE *******************************************************
void CVATRegister::getInfoAboutInvoice(
        const unordered_set<CCompany *, hashCCompany, compareCCompany>::const_iterator & itCompany,
        const CInvoice * const & tempInvoice,
        invoiceIs & m_markedAs,
        const CInvoice *& m_pInvoice  ) const
{


    const CInvoice * Invoice;


    if ((Invoice = (*itCompany)->haveInvoiceMatched(tempInvoice))) {
        m_markedAs = INVOICE_MATCHED;
        m_pInvoice = Invoice;
    }


    else if ((Invoice = (*itCompany)->haveInvoiceUnmatched(tempInvoice))) {
        m_markedAs = INVOICE_UNMATCHED;
        m_pInvoice = Invoice;
    }
    else {
        m_markedAs = INVOICE_NOT_PRESENT;
        m_pInvoice = NULL;
    }

    return;
}

///******************************** GET INFO COMPANY + INVOICE *******************************************
CVATRegister::DoubleTriple CVATRegister::getCompanyAndInvoiceInfo(const CInvoice &invoice) const {

    ///temp Companies for finding
    CCompany *tmpSeller = new CCompany(invoice.Seller()); ///tmp seller i buyer maji ted dobra jmena
    CCompany *tmpBuyer = new CCompany(invoice.Buyer());


//    unordered_set<CCompany *, hashCCompany, compareCCompany>::const_iterator itSeller, itBuyer;
    DoubleTriple info;

    ///firstly check for companies existence and difference
    if ( ( info.m_seller.m_itCompany   =   m_companies.find(tmpSeller) )    ==   m_companies.end() ||
         ( info.m_buyer.m_itCompany    =   m_companies.find(tmpBuyer)  )    ==   m_companies.end() ||
          info.m_seller.m_itCompany ==  info.m_buyer.m_itCompany
       )
    {
        info.badCompanies = true;
        delete tmpBuyer; delete tmpSeller;

        return info;
    }

    ///temp Invoice for finding
    info.badCompanies = false;
    const CInvoice *tempInvoice = new CInvoice(invoice.Date(),
                                               (* info.m_seller.m_itCompany)->m_nameOfficial,
                                               (* info.m_buyer.m_itCompany)->m_nameOfficial,
                                               invoice.Amount(),
                                               invoice.VAT(),
                                               666,
                                               (* info.m_seller.m_itCompany)->m_nameOptimized,
                                               (* info.m_buyer.m_itCompany)->m_nameOptimized )
                                                ;

    ///next find info about SELLERs invoice
    getInfoAboutInvoice( info.m_seller.m_itCompany, tempInvoice,  info.m_seller.m_markedAs ,   info.m_seller.m_pInvoice);

    ///next find info about BUYERs invoice
    getInfoAboutInvoice( info.m_buyer.m_itCompany,  tempInvoice,  info.m_buyer.m_markedAs ,    info.m_buyer.m_pInvoice );


    delete tempInvoice;
    delete tmpSeller;
    delete tmpBuyer;

    return info;
}

///**************************************** ADD ISUED ************************************************
bool CVATRegister::AddIssued(const CInvoice &x) {
    DoubleTriple invoiceInfo = getCompanyAndInvoiceInfo(x);

    /// buyer+seller exist && differ && seller dont have this invoice
    if (invoiceInfo.badCompanies || invoiceInfo.m_seller.m_markedAs != INVOICE_NOT_PRESENT)
        return false;

    /// If buyer HAVE this invoice --->  Link invoice from buyer --->  Let buyer mark invoice as matched
    if (invoiceInfo.m_buyer.m_markedAs != INVOICE_NOT_PRESENT) {
        (*invoiceInfo.m_seller.m_itCompany)->addToMatched(invoiceInfo.m_buyer.m_pInvoice);
        (*invoiceInfo.m_buyer.m_itCompany)->UnmatchedToMatched(invoiceInfo.m_buyer.m_pInvoice);
        //seller uz nebude mit unmatched from others todo new
        (*invoiceInfo.m_seller.m_itCompany)->removeUnmatchedFromOthers(invoiceInfo.m_buyer.m_pInvoice);
        return true;
    }

    /// otherwise ---> create new Invoice with correct credentials --->  and add it to sellers unmatched invoices
    const CInvoice *newInvoice = new CInvoice(x.Date(),
                                        (*invoiceInfo.m_seller.m_itCompany)->m_nameOfficial,
                                        (*invoiceInfo.m_buyer.m_itCompany)->m_nameOfficial,
                                        x.Amount(), x.VAT(), m_noInvoiceID++,
                                         ((*invoiceInfo.m_seller.m_itCompany)->m_nameOptimized),
                                         ((*invoiceInfo.m_buyer.m_itCompany)->m_nameOptimized),
                                                ((*invoiceInfo.m_seller.m_itCompany)->m_nameLowercase),
                                        ((*invoiceInfo.m_buyer.m_itCompany)->m_nameLowercase)
    )
                                        ;
    (*invoiceInfo.m_seller.m_itCompany)->addToUnmatched(newInvoice);
    ///to buyer add it to the unmatched todo new
    (*invoiceInfo.m_buyer.m_itCompany)->addToUnmatchedFromOthers(newInvoice);

    m_allInvoices_dele_purpose.insert( newInvoice); //todo NEW ULTRA SHIT

    return true;
}


///**************************************** ADD ACCEPTED ************************************************
bool CVATRegister::AddAccepted(const CInvoice &x) {
    DoubleTriple invoiceInfo = getCompanyAndInvoiceInfo(x);

    /// buyer+seller exist && must differ &&  Buyer dont have this invoice
    if (invoiceInfo.badCompanies || invoiceInfo.m_buyer.m_markedAs != INVOICE_NOT_PRESENT)
        return false;

    /// If seller have this invoice --> Link invoice from seller  ---> Let seller mark invoice as matched
    if (invoiceInfo.m_seller.m_markedAs != INVOICE_NOT_PRESENT) {
        (*invoiceInfo.m_buyer.m_itCompany)->addToMatched(invoiceInfo.m_seller.m_pInvoice);
        (*invoiceInfo.m_seller.m_itCompany)->UnmatchedToMatched(invoiceInfo.m_seller.m_pInvoice);
        //buyer uz nebude mit unmatched ze sellera todo new
        (*invoiceInfo.m_buyer.m_itCompany)->removeUnmatchedFromOthers(invoiceInfo.m_seller.m_pInvoice);
        return true;
    }

    /// otherwise ---> create new Invoice with correct credentials ---> add it to buyers unmatched invoices
    const CInvoice *newInvoice = new CInvoice(x.Date(),
                                        (*invoiceInfo.m_seller.m_itCompany)->m_nameOfficial,
                                        (*invoiceInfo.m_buyer.m_itCompany)->m_nameOfficial,
                                        x.Amount(), x.VAT(), m_noInvoiceID++,
                                         ((*invoiceInfo.m_seller.m_itCompany)->m_nameOptimized),
                                         ((*invoiceInfo.m_buyer.m_itCompany)->m_nameOptimized),

                                        ((*invoiceInfo.m_seller.m_itCompany)->m_nameLowercase),
                                        ((*invoiceInfo.m_buyer.m_itCompany)->m_nameLowercase)

    )
                                        ;
    (*invoiceInfo.m_buyer.m_itCompany)->addToUnmatched(newInvoice);
    ///add to unmatched from Others todo new
    (*invoiceInfo.m_seller.m_itCompany)->addToUnmatchedFromOthers(newInvoice);

    m_allInvoices_dele_purpose.insert(newInvoice); //todo NEW ULTRA SHIT

    return true;
}


///**************************************** DEL ISSUED ************************************************
bool CVATRegister::DelIssued(const CInvoice &x) {
    DoubleTriple invoiceInfo = getCompanyAndInvoiceInfo(x);

    /// Companies in invoice must exist &&  must differ  &&  Seller must  have this invoice
    if (invoiceInfo.badCompanies || invoiceInfo.m_seller.m_markedAs == INVOICE_NOT_PRESENT)
        return false;

    ///if seller have invoice between matched ---> delete from sellers entry from matched --- > let buyer mark invoice from matched to unmatched
    if (invoiceInfo.m_seller.m_markedAs == INVOICE_MATCHED) {
        (*invoiceInfo.m_seller.m_itCompany)->removeMatched(invoiceInfo.m_seller.m_pInvoice);
        //seller bude mit nematchlou z buyera todo new
        (*invoiceInfo.m_seller.m_itCompany)->addToUnmatchedFromOthers(invoiceInfo.m_seller.m_pInvoice);

        (*invoiceInfo.m_buyer.m_itCompany)->MatchedToUnmatched(invoiceInfo.m_buyer.m_pInvoice); //TODO check pointers --> snad OK
        return true;
    }

    /// otherwise -- > delete from sellers unmatched
    //but first - buyer uz nebude mit nematchlou ze sellera todo new
    (*invoiceInfo.m_buyer.m_itCompany)->removeUnmatchedFromOthers(invoiceInfo.m_seller.m_pInvoice);

    m_allInvoices_dele_purpose.erase (   m_allInvoices_dele_purpose.find( invoiceInfo.m_seller.m_pInvoice  ) ); //TODO NEW ULTRA SHIT

    (*invoiceInfo.m_seller.m_itCompany)->removeUnmatched(invoiceInfo.m_seller.m_pInvoice);



    return true;
}


///**************************************** DEL ACCEPTED ************************************************
bool CVATRegister::DelAccepted(const CInvoice &x) {
    DoubleTriple invoiceInfo = getCompanyAndInvoiceInfo(x);

    /// Companies in invoice must exist && must differ  && Buyer must  have this invoice
    if (invoiceInfo.badCompanies || invoiceInfo.m_buyer.m_markedAs == INVOICE_NOT_PRESENT)
        return false;

    ///if buyer have invoice between matched ---> delete from buyers entry from matched ---> let seller mark invoice from matched to unmatched
    if (invoiceInfo.m_buyer.m_markedAs == INVOICE_MATCHED) {
        (*invoiceInfo.m_buyer.m_itCompany)->removeMatched(invoiceInfo.m_buyer.m_pInvoice);
        ///buyer bude mit nematchlou ze sellera todo new
        (*invoiceInfo.m_buyer.m_itCompany)->addToUnmatchedFromOthers(invoiceInfo.m_buyer.m_pInvoice);
        (*invoiceInfo.m_seller.m_itCompany)->MatchedToUnmatched(invoiceInfo.m_seller.m_pInvoice); //todo check pointers  --> snad OK
        return true;
    }
    /// otherwise ---> delete from buyers entry unmatched
    ///but first - seller uz nebude mit nematchlou od buyera todo new
    (*invoiceInfo.m_seller.m_itCompany)->removeUnmatchedFromOthers(invoiceInfo.m_buyer.m_pInvoice);

    m_allInvoices_dele_purpose.erase (   m_allInvoices_dele_purpose.find( invoiceInfo.m_buyer.m_pInvoice ) ); //TODO NEW ULTRA SHIT

    (*invoiceInfo.m_buyer.m_itCompany)->removeUnmatched(invoiceInfo.m_buyer.m_pInvoice);


    return true;
}


///******************************** RETURN LIST OF  UNMATCHED ************************************************

struct CompareSort{
    list<pairSortOp> sortOptions;

    CompareSort(const CSortOpt & sortBy): sortOptions(sortBy.getSortOptions()) {};

    bool operator () (const CInvoice &  a, const CInvoice & b  ) {

        int AcompareB = 0;

        ///iterate through options; most important at beggining
        list<pairSortOp>::const_iterator it;
        for(it = sortOptions.begin(); it != sortOptions.end() ; ++it) {
            ///match find option
            for(int i = 0 ; i < 5 ; ++i) {
                if(i == it->m_key)
                {
                  if(  (AcompareB = compareByOption(i, a, b, it)) < 0 ) {
                      return true;
                  }
                    else if( AcompareB > 0)
                      return false;
                }
            }
        }

        if(AcompareB == 0)
            return a.registerNum() < b.registerNum();

        ///newer here !
        return true;
    }

private:

    int compareByOption(int i, const CInvoice &  a, const CInvoice & b, list<pairSortOp>::const_iterator & it ){
        int value ;
        switch (i) {
            case 0:
                /// BY_DATE = 0
                value = compareDate(a.Date(), b.Date(), it->m_ascending);
                break;
            case 1:
                /// BY_BUYER = 1
                value = compareString( a.LowercaseBuyer() , b.LowercaseBuyer(), it->m_ascending );
                break;
            case 2:
                //// BY_SLLER = 2
                value = compareString( a.LowercaseSeller(), b.LowercaseSeller(), it->m_ascending);
                break;
            case 3:
                /// BY_AMMOUT = 3
                value = compareAmmount( a.Amount(), b.Amount(), it->m_ascending);
                break;
            case 4:
                /// BY_VAT = 4
                value = compareVAT( a.VAT(), b.VAT(), it->m_ascending);
                break;
            default:
                value = 0;
                break;
        }
        return value;
    }

    int compareVAT(double a, double b , bool ascending )  {  /// -1(a<b) 0(a==b) 1(a>b)
        if(equal(a,b))
            return 0;
        if ( ascending){
            if (a < b)
                return -1;
            return 1;
        }
        else
        {
            if (b < a)
                return -1;
            return 1;
        }
    }

    int compareAmmount(int a, int b, bool ascending) const{ /// -1(a<b) 0(a==b) 1(a>b)
        if ( a == b )
            return 0;

        if ( ascending)
            return a - b;
        else
            return b - a;
    }

    int compareDate(const CDate & a, const CDate & b, bool ascending) const { /// -1(a<b) 0(a==b) 1(a>b)
        if ( ascending)
            return a.Compare(b);
        else
            return b.Compare(a);
    }

    int compareString(const string &a,const  string &b, bool ascending) const {
        if (ascending)
            return a.compare(b);
        else
            return b.compare(a);
    }
};

list <CInvoice> CVATRegister::Unmatched(const string &company, const CSortOpt &sortBy) const {

    ///find CCompany
    CCompany * tmpFindingCompany = new CCompany(company);
    const unordered_set< CCompany *, hashCCompany, compareCCompany>::const_iterator itCompany =  m_companies.find(tmpFindingCompany);

    /// if company did not exist return empty list
    if(itCompany == m_companies.end()) {
        list <CInvoice> a;
        return a;
    }

    ///copy unmatched CInvoices to Vector
    vector<CInvoice> invoicesToSort;
    unordered_set<const CInvoice *, hashCInvoice, compareInvoice>::const_iterator itInvoices;
    for(itInvoices =  (*itCompany)->m_unmatched.begin(); itInvoices != (*itCompany)->m_unmatched.end() ; ++itInvoices ) {
        invoicesToSort.push_back(**itInvoices);
    }
    ///copy Unmatched from others
    for(itInvoices =  (*itCompany)->m_unmatched_from_others.begin(); itInvoices != (*itCompany)->m_unmatched_from_others.end() ; ++itInvoices ) {
        invoicesToSort.push_back(**itInvoices);
    }


    ///sort all invoices
     sort(invoicesToSort.begin(), invoicesToSort.end(), CompareSort(sortBy));

 // for(auto &a : invoicesToSort){
   //     cout << a;
   // }

  //  cout << endl << "*********************************************************************************" << endl;

    ///return list copied from vector
    delete tmpFindingCompany;
    return list<CInvoice> (invoicesToSort.begin(), invoicesToSort.end());
}


///*************************************************************************************************
///******************************************  TESTING  ********************************************
///*************************************************************************************************

#ifndef __PROGTEST__

bool equalLists(const list <CInvoice> &a, const list <CInvoice> &b) {

    list<CInvoice>::const_iterator itA, itB;

    for(itA = a.begin() , itB = b.begin() ; itA != a.end() || itB != b.end(); ++itA, ++itB){
      if(  (*itA).Amount() ==  (*itB).Amount() ){
          if (  (*itA).Date().Compare(  (*itB).Date() ) == 0 ) {
              if ( (*itA).VAT() ==  (*itB).VAT()   ){
                  if( (*itA).Seller() ==  (*itB).Seller() ){
                      if( (*itA).Buyer() ==  (*itB).Buyer()  ){
                          cout << "rovnaji se" << endl;
                          continue;
                      }
                      cout << "nerovnaji se v buyeru " << endl;
                      return false;
                  }
                  cout << "nerovnaji se v selleru " << endl;
                  return false;
              }
              cout << "nerovnaji se v VAT " << endl;
              return false;
          }
          cout << "nerovnaji se v Date " << endl;
          return false;
      }
        cout << "nerovnaji se v Ammount " << endl;
        return false;
    }

    return true;
}

int main ( void )
{
    CVATRegister r;
    assert ( r . RegisterCompany ( "first Company" ) );
    assert ( r . RegisterCompany ( "Second     Company" ) );
    assert ( r . RegisterCompany ( "ThirdCompany, Ltd." ) );
    assert ( r . RegisterCompany ( "Third Company, Ltd." ) );
    assert ( !r . RegisterCompany ( "Third Company, Ltd." ) );
    assert ( !r . RegisterCompany ( " Third  Company,  Ltd.  " ) );
    assert ( r . AddIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 100, 20 ) ) );
    assert ( r . AddIssued ( CInvoice ( CDate ( 2000, 1, 2 ), "FirSt Company", "Second Company ", 200, 30 ) ) );
    assert ( r . AddIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 100, 30 ) ) );
    assert ( r . AddIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 300, 30 ) ) );
    assert ( r . AddIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );
    assert ( r . AddIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "Second Company ", "First Company", 300, 30 ) ) );
    assert ( r . AddIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "Third  Company,  Ltd.", "  Second    COMPANY ", 400, 34 ) ) );

    assert ( !r . AddIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 300, 30 ) ) );

    assert ( !r . AddIssued ( CInvoice ( CDate ( 2000, 1, 4 ), "First Company", "First   Company", 200, 30 ) ) );
    assert ( !r . AddIssued ( CInvoice ( CDate ( 2000, 1, 4 ), "Another Company", "First   Company", 200, 30 ) ) );
    assert ( equalLists ( r . Unmatched ( "First Company", CSortOpt () . AddKey ( CSortOpt::BY_SELLER, true ) . AddKey ( CSortOpt::BY_BUYER, false ) . AddKey ( CSortOpt::BY_DATE, false ) ),
                          std::list<CInvoice>
                          {
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 )
                          } ) );
    assert ( equalLists ( r . Unmatched ( "First Company", CSortOpt () . AddKey ( CSortOpt::BY_DATE, true ) . AddKey ( CSortOpt::BY_SELLER, true ) . AddKey ( CSortOpt::BY_BUYER, true ) ),
                          std::list<CInvoice>
                          {
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 )
                          } ) );
    assert ( equalLists ( r . Unmatched ( "First Company",
                                          CSortOpt () . AddKey ( CSortOpt::BY_VAT, true ) .
                                                  AddKey ( CSortOpt::BY_AMOUNT, true ) .
                                                  AddKey ( CSortOpt::BY_DATE, true ) .
                                                  AddKey ( CSortOpt::BY_SELLER, true ) .
                                                  AddKey ( CSortOpt::BY_BUYER, true ) ),
                          std::list<CInvoice>
                          {
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 )
                          } ) );
    assert ( equalLists ( r . Unmatched ( "First Company", CSortOpt () ),
                          std::list<CInvoice>
                          {
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 )
                          } ) );
    assert ( equalLists ( r . Unmatched ( "second company", CSortOpt () . AddKey ( CSortOpt::BY_DATE, false ) ),
                          std::list<CInvoice>
                          {
                                  CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "Third Company, Ltd.", "Second     Company", 400, 34.000000 )
                          } ) );
    assert ( equalLists ( r . Unmatched ( "last company", CSortOpt () . AddKey ( CSortOpt::BY_VAT, true ) ),
                          std::list<CInvoice>
                          {
                          } ) );
    assert ( r . AddAccepted ( CInvoice ( CDate ( 2000, 1, 2 ), "First Company", "Second Company ", 200, 30 ) ) );
    assert ( r . AddAccepted ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );
    assert ( r . AddAccepted ( CInvoice ( CDate ( 2000, 1, 1 ), "Second company ", "First Company", 300, 32 ) ) );
    assert ( equalLists ( r . Unmatched ( "First Company", CSortOpt () . AddKey ( CSortOpt::BY_SELLER, true ) . AddKey ( CSortOpt::BY_BUYER, true ) . AddKey ( CSortOpt::BY_DATE, true ) ),
                          std::list<CInvoice>
                          {
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
                          } ) );
    assert ( !r . DelIssued ( CInvoice ( CDate ( 2001, 1, 1 ), "First Company", "Second Company ", 200, 30 ) ) );
    assert ( !r . DelIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "A First Company", "Second Company ", 200, 30 ) ) );
    assert ( !r . DelIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Hand", 200, 30 ) ) );
    assert ( !r . DelIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company", 1200, 30 ) ) );
    assert ( !r . DelIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company", 200, 130 ) ) );
    assert ( r . DelIssued ( CInvoice ( CDate ( 2000, 1, 2 ), "First Company", "Second Company", 200, 30 ) ) );
    assert ( equalLists ( r . Unmatched ( "First Company", CSortOpt () . AddKey ( CSortOpt::BY_SELLER, true ) . AddKey ( CSortOpt::BY_BUYER, true ) . AddKey ( CSortOpt::BY_DATE, true ) ),
                          std::list<CInvoice>
                          {
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
                          } ) );
    assert ( r . DelAccepted ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );
    assert ( equalLists ( r . Unmatched ( "First Company", CSortOpt () . AddKey ( CSortOpt::BY_SELLER, true ) . AddKey ( CSortOpt::BY_BUYER, true ) . AddKey ( CSortOpt::BY_DATE, true ) ),
                          std::list<CInvoice>
                          {
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
                          } ) );
    assert ( r . DelIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );
    assert ( equalLists ( r . Unmatched ( "First Company", CSortOpt () . AddKey ( CSortOpt::BY_SELLER, true ) . AddKey ( CSortOpt::BY_BUYER, true ) . AddKey ( CSortOpt::BY_DATE, true ) ),
                          std::list<CInvoice>
                          {
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
                                  CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
                          } ) );
    return 0;
}
#endif /* __PROGTEST__ */