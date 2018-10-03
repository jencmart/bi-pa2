#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <list>
#include <memory>
#include <set>

using namespace std;
#endif /* __PROGTEST_ */


///*********************************************************************************************************************
///********************************************  ITEM  *****************************************************************
///*********************************************************************************************************************

class CItem {
public:
    CItem(int weight, bool bag = false) : m_weight(weight), m_bag(bag) {};

    virtual ~CItem() {};

    friend ostream &operator<<(ostream &os, const CItem &x)
    {
        x.Print(os);
        return os;
    }

    virtual void Print(ostream &os) const = 0;

    virtual void Print(ostream & os, const string &strLugage ,const string & str) const {};

    bool operator == (const CItem &other) const
    {
            return m_weight == other.m_weight ? Equals(other) : false;
   }

    virtual bool Equals(const CItem &other) const = 0;

    virtual bool Dangerous() const = 0;

    virtual int ItemWeight() const { return m_weight; }

    virtual int PureItemWeight() const { return m_weight; }

    virtual int NumOfElements() const = 0;

    bool IsBag() const {return m_bag;}

protected:
    int m_weight;
    bool m_bag;
};

///*********************************************  KNIFE  **************************************************************
class CKnife : public CItem {
    int m_bladeLength;
public:
    CKnife(int bladeLength) : CItem(100), m_bladeLength(bladeLength) {};

    CKnife(const CKnife &x) : CItem(100), m_bladeLength(x.m_bladeLength) {};

    ~CKnife() {};

    void Print(ostream &os) const override { os << "-Knife, blade: " << m_bladeLength << " cm"; }

    bool Equals(const CItem &other) const override { return m_bladeLength == ((const CKnife &) other).m_bladeLength; }

    bool Dangerous() const override { return m_bladeLength > 7; }

    int NumOfElements() const override {return 1; }

};

///*********************************************  CLOTHES  *************************************************************
class CClothes : public CItem {
    string m_description;
public:
    CClothes(const string &description) : CItem(500), m_description(description) {}

    CClothes(const CClothes &x) : CItem(500), m_description(x.m_description) {}

    ~CClothes() {};

    void Print(ostream &os) const override { os << "-Clothes (" << m_description << ")"; }

    bool Equals(const CItem &other) const override { return m_description == ((const CClothes &) other).m_description; }

    bool Dangerous() const override { return false; }

    int NumOfElements() const override {return 1; }
};

///*********************************************  SHOES  ***************************************************************
class CShoes : public CItem {
public:
    CShoes() : CItem(750) {};

    ~CShoes() {};

    void Print(ostream &os) const override { os << "-Shoes"; }

    bool Equals(const CItem &other) const override { return true; }

    bool Dangerous() const override { return false; }

    int NumOfElements() const override {return 1; }
};

///*********************************************  MOBILE  **************************************************************
class CMobile : public CItem {
    string m_brand;
    string m_type;
public:
    CMobile(const string &brand, const string &type) : CItem(150), m_brand(brand), m_type(type) {};

    CMobile(const CMobile &x) : CItem(150), m_brand(x.m_brand), m_type(x.m_type) {};

    ~CMobile() {};

    void Print(ostream &os) const override { os << "-Mobile " << m_type << " by: " << m_brand; }

    bool Equals(const CItem &other) const override
    {
        return m_brand == ((const CMobile &) other).m_brand &&
               m_type  == ((const CMobile &) other).m_type;
    }

    bool Dangerous() const override { return m_brand == "Samsung" && m_type == "Galaxy Note S7"; }

    int NumOfElements() const override {return 1; }
};

///*********************************************************************************************************************
///**************************************** LUGGAGE ********************************************************************
///*********************************************************************************************************************




class CLuggage : public CItem {
public:
    CLuggage(int weight) : CItem(weight, true), m_content(), m_contentMultiset(), m_contentWeight(0), m_dangerousContent(false), m_numOfElements(0) {}
    CLuggage(const CLuggage & other) : CItem(other.m_weight , true) { copyContent(other); }
    virtual ~CLuggage() {};


    ///*******************************ITEM INTERFACE
    int NumOfElements() const override {return m_numOfElements; } ///Item interface
    int ItemWeight() const override { return Weight(); }  ///Item interface (luggage + content)
    bool Dangerous() const override  { return Danger() ; }  ///Item interface
    bool Equals(const  CItem & other) const override { return true ; } // Nedeje se....

    void Print(ostream & os) const override ///Item interface //TODO !!!!
    {
        PrintType(os);
        os << endl;
        char c;
        for (size_t i = 0; i < m_content.size(); ++i) {
            c = (char) (i + 1 < m_content.size() ? '+' : '\\');
            os << c << *(m_content[i]) << endl;
        }
    }

    void Print(ostream & os, const string & strLugage ,const string & str)  const override {
        os << strLugage;
        PrintType(os);
        os << endl;
        char c;
        for (size_t i = 0; i < m_content.size(); ++i) {
            c = (char) (i + 1 < m_content.size() ? '+' : '\\');

                if(m_content[i]->IsBag())
                {
                    if (i + 1 < m_content.size() )
                        (m_content[i])->Print(os, str + "+-"  , str + "| " );
                    else
                        (m_content[i])->Print(os, str + "\\-" , str + "  " );

                    continue;
                }

            os << str << c << *(m_content[i]) << endl;
        }

    }

    ///*******************************LUGGAGE INTERFACE
    virtual CLuggage &Add(const CItem &item); /// Luggage Interface
    int Weight() const { return m_weight + m_contentWeight; } /// Luggage Interface
    bool Danger() const { return m_dangerousContent; } /// Luggage Interface
    int Count() const { return m_numOfElements; } /// Luggage Interface


    bool IdenticalContents(const CLuggage &other) const {



        if(m_contentMultiset.size() != other.m_contentMultiset.size())
            return false;

        for(auto const & x : m_contentMultiset){
            bool found = false;
            for(auto const & y : other.m_contentMultiset)
                if( *x == *y)
                    found = true;
            if (! found)
                return false;
        }

        for(auto const & x : other.m_contentMultiset){
            bool found = false;
            for(auto const & y : m_contentMultiset)
                if( *x == *y)
                    found = true;
            if (! found)
                return false;
        }



        return true;

    } ///Luggage Interface

    friend ostream &operator<<(ostream &os, const CLuggage &other)  ///Luggage Interface TODO !!!!
    {
        other.Print(os, "","");
        return os;
    }
    ///******************************

protected:
    struct CompareShit
    {
        bool operator () (const unique_ptr<CItem> &a , const unique_ptr<CItem> &b) const  { return *a == *b; }
    };

    std::vector<unique_ptr<CItem>> m_content;
    std::multiset< unique_ptr<CItem>, CompareShit> m_contentMultiset;
    int m_contentWeight;
    bool m_dangerousContent;
    int m_numOfElements;

    void copyContent( const CLuggage & other);
    virtual void PrintType(ostream &os) const = 0;
};

///******************************************  SUITCASE  ***************************************************************
struct CSuitcase : public CLuggage {

    CSuitcase(int w, int h, int d) : CLuggage(2000), m_w(w), m_h(h), m_d(d) {}

    CSuitcase(const CSuitcase &other) : CLuggage(other), m_w(other.m_w), m_h(other.m_h), m_d(other.m_d)  {}

    ~CSuitcase() {};

    CSuitcase & operator = (const CSuitcase &other) {
        if (this != &other) {
            m_w = other.m_w;
            m_h = other.m_h;
            m_d = other.m_d;
            copyContent(other);
        }

        return *this;
    }
    
    void PrintType(ostream &os) const override { os << "Suitcase " << m_w << "x" << m_h << "x" << m_d ; }

private:
    int m_w, m_h, m_d;
};

///******************************************  BACKPACK  ***************************************************************
struct CBackpack : public CLuggage {

    CBackpack() : CLuggage(1000) {}

    CBackpack(const CBackpack &other) : CLuggage(other) {}

    ~CBackpack() {};

    CBackpack & operator = (const CBackpack & other) {
        if (this != &other)
            copyContent(other);

        return *this;
    }

    void PrintType(ostream &os) const override { os << "Backpack"; }
};

///****************************************** BAG **********************************************************************
class CBag : public CLuggage {
public:
    CBag(const string & brand) : CLuggage(500), m_brand(brand) {}

    CBag(const CBag &other) : CLuggage(other), m_brand(other.m_brand)  {}

    ~CBag() {};

    CBag & operator = (const CBag &other) {
        if (this != &other) {
            m_brand = other.m_brand;
            copyContent(other);
        }

        return *this;
    }
    
    void PrintType(ostream &os) const override { os << "Bag by: " << m_brand ; }

private:
    string m_brand;
};








///*********************************** LUGGAGE COPY CONTENT ************************************************************
void CLuggage::copyContent(const CLuggage &other) {
    m_contentWeight = other.m_contentWeight;
    m_dangerousContent = other.m_dangerousContent;
    m_numOfElements = other.m_numOfElements;

    m_content.clear();

    m_contentMultiset.clear(); ///nevim jak se to bude libit unique ptr...



    for (auto const &x : other.m_content) {
        if (x->PureItemWeight() == 100)
            m_content.push_back(unique_ptr<CItem>(new CKnife((CKnife &) *x)));
        else if (x->PureItemWeight() == 500 && ! x->IsBag())
            m_content.push_back(unique_ptr<CItem>(new CClothes((CClothes &) *x)));
        else if (x->PureItemWeight() == 150)
            m_content.push_back(unique_ptr<CItem>(new CMobile((CMobile &) *x)));
        else if (x->PureItemWeight() == 750)
            m_content.push_back(unique_ptr<CItem>(new CShoes()));
        else if (x->PureItemWeight() == 2000)
            m_content.push_back(unique_ptr<CItem>(new CSuitcase((const CSuitcase &) *x)));
        else if (x->PureItemWeight() == 1000)
            m_content.push_back(unique_ptr<CItem>(new CBackpack((const CBackpack &) *x)));
        else if (x->PureItemWeight() == 500)
            m_content.push_back(unique_ptr<CItem>(new CBag((const CBag &) *x)));
    }



    ///MULTISET COPY
    for (auto const &x : other.m_contentMultiset) {
        if (x->PureItemWeight() == 100)
            m_contentMultiset.insert(unique_ptr<CItem>(new CKnife((CKnife &) *x)));
        else if (x->PureItemWeight() == 500)
            m_contentMultiset.insert(unique_ptr<CItem>(new CClothes((CClothes &) *x)));
        else if (x->PureItemWeight() == 150)
            m_contentMultiset.insert(unique_ptr<CItem>(new CMobile((CMobile &) *x)));
        else if (x->PureItemWeight() == 750)
            m_contentMultiset.insert(unique_ptr<CItem>(new CShoes()));
    }


}






///*********************************** LUGGAGE ADD ITEM ************************************************************
CLuggage &CLuggage::Add(const CItem &item) {



    if (item.PureItemWeight() == 100) {
        m_content.push_back(unique_ptr<CItem>(new CKnife((CKnife &) item)));
        m_contentMultiset.insert(unique_ptr<CItem>(new CKnife((CKnife &) item)));
    }
    else if (item.PureItemWeight() == 500 && !item.IsBag()) {
        m_content.push_back(unique_ptr<CItem>(new CClothes((CClothes &) item)));
        m_contentMultiset.insert(unique_ptr<CItem>(new CClothes((CClothes &) item)));
    }
    else if (item.PureItemWeight() == 150) {
        m_content.push_back(unique_ptr<CItem>(new CMobile((CMobile &) item)));
        m_contentMultiset.insert(unique_ptr<CItem>(new CMobile((CMobile &) item)));
    }
    else if (item.PureItemWeight() == 750) {
        m_content.push_back(unique_ptr<CItem>(new CShoes()));
        m_contentMultiset.insert(unique_ptr<CItem>(new CShoes((CShoes &) item)));
    }




    else if (item.PureItemWeight() == 2000) { ///ADD SUITCASE
        m_content.push_back(unique_ptr<CItem>(new CSuitcase((CSuitcase &) item)));

        for (auto const &x : ((CSuitcase &) item).m_contentMultiset) {
            if (x->PureItemWeight() == 100)
                m_contentMultiset.insert(unique_ptr<CItem>(new CKnife((CKnife &) *x)));
            else if (x->PureItemWeight() == 500)
                m_contentMultiset.insert(unique_ptr<CItem>(new CClothes((CClothes &) *x)));
            else if (x->PureItemWeight() == 150)
                m_contentMultiset.insert(unique_ptr<CItem>(new CMobile((CMobile &) *x)));
            else if (x->PureItemWeight() == 750)
                m_contentMultiset.insert(unique_ptr<CItem>(new CShoes()));
        }
    }
    else if (item.PureItemWeight() == 1000) { ///ADD BACKPACK

        m_content.push_back(unique_ptr<CItem>(new CBackpack((CBackpack &) item)));
        for (auto const &x : ((CBackpack &) item).m_contentMultiset) {
            if (x->PureItemWeight() == 100)
                m_contentMultiset.insert(unique_ptr<CItem>(new CKnife((CKnife &) *x)));
            else if (x->PureItemWeight() == 500)
                m_contentMultiset.insert(unique_ptr<CItem>(new CClothes((CClothes &) *x)));
            else if (x->PureItemWeight() == 150)
                m_contentMultiset.insert(unique_ptr<CItem>(new CMobile((CMobile &) *x)));
            else if (x->PureItemWeight() == 750)
                m_contentMultiset.insert(unique_ptr<CItem>(new CShoes()));
        }
    }
    else { ///ADD BAG
        m_content.push_back(unique_ptr<CItem>(new CBag((CBag &) item)));
        for (auto const &x : ((CBag &) item).m_contentMultiset) {
            if (x->PureItemWeight() == 100)
                m_contentMultiset.insert(unique_ptr<CItem>(new CKnife((CKnife &) *x)));
            else if (x->PureItemWeight() == 500)
                m_contentMultiset.insert(unique_ptr<CItem>(new CClothes((CClothes &) *x)));
            else if (x->PureItemWeight() == 150)
                m_contentMultiset.insert(unique_ptr<CItem>(new CMobile((CMobile &) *x)));
            else if (x->PureItemWeight() == 750)
                m_contentMultiset.insert(unique_ptr<CItem>(new CShoes()));
        }
    }

    m_dangerousContent = m_dangerousContent ? m_dangerousContent : m_content.back()->Dangerous();
    m_contentWeight += m_content.back()->ItemWeight();
    m_numOfElements += item.NumOfElements();
    return *this;
}





///*********************************************************************************************************************
///********************************************  TESTING ***************************************************************
///*********************************************************************************************************************
///*********************************************************************************************************************

#ifndef __PROGTEST__
int main ( void )
{
    CSuitcase w ( 1, 2, 3 );
    CBackpack x;
    CBag y ( "An Ordinary Bag (TM)" );
    CSuitcase z ( 3, 2, 1 );
    ostringstream os;
    w . Add ( CKnife ( 7 ) );
    w . Add ( CClothes ( "red T-shirt" ) );
    w . Add ( CClothes ( "black hat" ) );
    w . Add ( CShoes () );
    w . Add ( CClothes ( "green pants" ) );
    w . Add ( CClothes ( "blue jeans" ) );
    w . Add ( CMobile ( "Samsung", "J3" ) );
    w . Add ( CMobile ( "Tamtung", "Galaxy Note S7" ) );
    os . str ( "" );
    os << w;
    assert ( os . str () == "Suitcase 1x2x3\n"
            "+-Knife, blade: 7 cm\n"
            "+-Clothes (red T-shirt)\n"
            "+-Clothes (black hat)\n"
            "+-Shoes\n"
            "+-Clothes (green pants)\n"
            "+-Clothes (blue jeans)\n"
            "+-Mobile J3 by: Samsung\n"
            "\\-Mobile Galaxy Note S7 by: Tamtung\n" );
    assert ( w . Count () == 8 );
    assert ( w . Weight () == 5150 );
    assert ( !w . Danger () );
    w . Add ( CKnife ( 8 ) );
    os . str ( "" );
    os << w;
    assert ( os . str () == "Suitcase 1x2x3\n"
            "+-Knife, blade: 7 cm\n"
            "+-Clothes (red T-shirt)\n"
            "+-Clothes (black hat)\n"
            "+-Shoes\n"
            "+-Clothes (green pants)\n"
            "+-Clothes (blue jeans)\n"
            "+-Mobile J3 by: Samsung\n"
            "+-Mobile Galaxy Note S7 by: Tamtung\n"
            "\\-Knife, blade: 8 cm\n" );
    assert ( w . Count () == 9 );
    assert ( w . Weight () == 5250 );
    assert ( w . Danger () );
    x . Add ( CKnife ( 7 ) )
            . Add ( CClothes ( "red T-shirt" ) )
            . Add ( CShoes () );
    x . Add ( CMobile ( "Samsung", "Galaxy Note S7" ) );
    x . Add ( CShoes () );
    x . Add ( CClothes ( "blue jeans" ) );
    x . Add ( CClothes ( "black hat" ) );
    x . Add ( CClothes ( "green pants" ) );
    os . str ( "" );
    os << x;
    assert ( os . str () == "Backpack\n"
            "+-Knife, blade: 7 cm\n"
            "+-Clothes (red T-shirt)\n"
            "+-Shoes\n"
            "+-Mobile Galaxy Note S7 by: Samsung\n"
            "+-Shoes\n"
            "+-Clothes (blue jeans)\n"
            "+-Clothes (black hat)\n"
            "\\-Clothes (green pants)\n" );
    assert ( x . Count () == 8 );
    assert ( x . Weight () == 4750 );
    assert ( x . Danger () );
    x . Add ( CMobile ( "Samsung", "J3" ) );
    x . Add ( CMobile ( "Tamtung", "Galaxy Note S7" ) );
    x . Add ( CKnife ( 8 ) );
    os . str ( "" );
    os << x;
    assert ( os . str () == "Backpack\n"
            "+-Knife, blade: 7 cm\n"
            "+-Clothes (red T-shirt)\n"
            "+-Shoes\n"
            "+-Mobile Galaxy Note S7 by: Samsung\n"
            "+-Shoes\n"
            "+-Clothes (blue jeans)\n"
            "+-Clothes (black hat)\n"
            "+-Clothes (green pants)\n"
            "+-Mobile J3 by: Samsung\n"
            "+-Mobile Galaxy Note S7 by: Tamtung\n"
            "\\-Knife, blade: 8 cm\n" );
    assert ( x . Count () == 11 );
    assert ( x . Weight () == 5150 );
    assert ( x . Danger () );
    assert ( !w . IdenticalContents ( x ) );
    assert ( !x . IdenticalContents ( w ) );
    w . Add ( CMobile ( "Samsung", "Galaxy Note S7" ) );
    assert ( !w . IdenticalContents ( x ) );
    assert ( !x . IdenticalContents ( w ) );
    w . Add ( CShoes () );
    assert ( w . IdenticalContents ( x ) );
    assert ( x . IdenticalContents ( w ) );
    assert ( x . IdenticalContents ( x ) );
    assert ( w . IdenticalContents ( w ) );
    y . Add ( w );
    y . Add ( x );
    z . Add ( x );
    z . Add ( w );
    w . Add ( CShoes () );///************************************************** W LAST ADD
    x . Add ( CKnife ( 12 ) ); /// **************************************** X LAST ADD


    assert ( !w . IdenticalContents ( x ) );


    os . str ( "" );
    os << w;
    assert ( os . str () == "Suitcase 1x2x3\n"
            "+-Knife, blade: 7 cm\n"
            "+-Clothes (red T-shirt)\n"
            "+-Clothes (black hat)\n"
            "+-Shoes\n"
            "+-Clothes (green pants)\n"
            "+-Clothes (blue jeans)\n"
            "+-Mobile J3 by: Samsung\n"
            "+-Mobile Galaxy Note S7 by: Tamtung\n"
            "+-Knife, blade: 8 cm\n"
            "+-Mobile Galaxy Note S7 by: Samsung\n"
            "+-Shoes\n"
            "\\-Shoes\n" );
    assert ( w . Count () == 12 );
    assert ( w . Weight () == 6900 );
    assert ( w . Danger () );
    os . str ( "" );
    os << x;
    assert ( os . str () == "Backpack\n"
            "+-Knife, blade: 7 cm\n"
            "+-Clothes (red T-shirt)\n"
            "+-Shoes\n"
            "+-Mobile Galaxy Note S7 by: Samsung\n"
            "+-Shoes\n"
            "+-Clothes (blue jeans)\n"
            "+-Clothes (black hat)\n"
            "+-Clothes (green pants)\n"
            "+-Mobile J3 by: Samsung\n"
            "+-Mobile Galaxy Note S7 by: Tamtung\n"
            "+-Knife, blade: 8 cm\n"
            "\\-Knife, blade: 12 cm\n" );
    assert ( x . Count () == 12 );
    assert ( x . Weight () == 5250 );
    assert ( x . Danger () );
    os . str ( "" );
    os << y;

    assert ( os . str () ==
             "Bag by: An Ordinary Bag (TM)\n"
            "+-Suitcase 1x2x3\n"
            "| +-Knife, blade: 7 cm\n"
            "| +-Clothes (red T-shirt)\n"
            "| +-Clothes (black hat)\n"
            "| +-Shoes\n"
            "| +-Clothes (green pants)\n"
            "| +-Clothes (blue jeans)\n"
            "| +-Mobile J3 by: Samsung\n"
            "| +-Mobile Galaxy Note S7 by: Tamtung\n"
            "| +-Knife, blade: 8 cm\n"
            "| +-Mobile Galaxy Note S7 by: Samsung\n"
            "| \\-Shoes\n"
            "\\-Backpack\n"
            "  +-Knife, blade: 7 cm\n"
            "  +-Clothes (red T-shirt)\n"
            "  +-Shoes\n"
            "  +-Mobile Galaxy Note S7 by: Samsung\n"
            "  +-Shoes\n"
            "  +-Clothes (blue jeans)\n"
            "  +-Clothes (black hat)\n"
            "  +-Clothes (green pants)\n"
            "  +-Mobile J3 by: Samsung\n"
            "  +-Mobile Galaxy Note S7 by: Tamtung\n"
            "  \\-Knife, blade: 8 cm\n" );


    assert ( y . Count () == 22 );
    assert ( y . Weight () == 11800 );
    assert ( y . Danger () );
    os . str ( "" );
    os << z;
    assert ( os . str () == "Suitcase 3x2x1\n"
            "+-Backpack\n"
            "| +-Knife, blade: 7 cm\n"
            "| +-Clothes (red T-shirt)\n"
            "| +-Shoes\n"
            "| +-Mobile Galaxy Note S7 by: Samsung\n"
            "| +-Shoes\n"
            "| +-Clothes (blue jeans)\n"
            "| +-Clothes (black hat)\n"
            "| +-Clothes (green pants)\n"
            "| +-Mobile J3 by: Samsung\n"
            "| +-Mobile Galaxy Note S7 by: Tamtung\n"
            "| \\-Knife, blade: 8 cm\n"
            "\\-Suitcase 1x2x3\n"
            "  +-Knife, blade: 7 cm\n"
            "  +-Clothes (red T-shirt)\n"
            "  +-Clothes (black hat)\n"
            "  +-Shoes\n"
            "  +-Clothes (green pants)\n"
            "  +-Clothes (blue jeans)\n"
            "  +-Mobile J3 by: Samsung\n"
            "  +-Mobile Galaxy Note S7 by: Tamtung\n"
            "  +-Knife, blade: 8 cm\n"
            "  +-Mobile Galaxy Note S7 by: Samsung\n"
            "  \\-Shoes\n" );
    assert ( z . Count () == 22 );
    assert ( z . Weight () == 13300 );
    assert ( z . Danger () );
    assert ( y . IdenticalContents ( z ) );
    y . Add ( z );
    os . str ( "" );
    os << y;
    assert ( os . str () == "Bag by: An Ordinary Bag (TM)\n"
            "+-Suitcase 1x2x3\n"
            "| +-Knife, blade: 7 cm\n"
            "| +-Clothes (red T-shirt)\n"
            "| +-Clothes (black hat)\n"
            "| +-Shoes\n"
            "| +-Clothes (green pants)\n"
            "| +-Clothes (blue jeans)\n"
            "| +-Mobile J3 by: Samsung\n"
            "| +-Mobile Galaxy Note S7 by: Tamtung\n"
            "| +-Knife, blade: 8 cm\n"
            "| +-Mobile Galaxy Note S7 by: Samsung\n"
            "| \\-Shoes\n"
            "+-Backpack\n"
            "| +-Knife, blade: 7 cm\n"
            "| +-Clothes (red T-shirt)\n"
            "| +-Shoes\n"
            "| +-Mobile Galaxy Note S7 by: Samsung\n"
            "| +-Shoes\n"
            "| +-Clothes (blue jeans)\n"
            "| +-Clothes (black hat)\n"
            "| +-Clothes (green pants)\n"
            "| +-Mobile J3 by: Samsung\n"
            "| +-Mobile Galaxy Note S7 by: Tamtung\n"
            "| \\-Knife, blade: 8 cm\n"
            "\\-Suitcase 3x2x1\n"
            "  +-Backpack\n"
            "  | +-Knife, blade: 7 cm\n"
            "  | +-Clothes (red T-shirt)\n"
            "  | +-Shoes\n"
            "  | +-Mobile Galaxy Note S7 by: Samsung\n"
            "  | +-Shoes\n"
            "  | +-Clothes (blue jeans)\n"
            "  | +-Clothes (black hat)\n"
            "  | +-Clothes (green pants)\n"
            "  | +-Mobile J3 by: Samsung\n"
            "  | +-Mobile Galaxy Note S7 by: Tamtung\n"
            "  | \\-Knife, blade: 8 cm\n"
            "  \\-Suitcase 1x2x3\n"
            "    +-Knife, blade: 7 cm\n"
            "    +-Clothes (red T-shirt)\n"
            "    +-Clothes (black hat)\n"
            "    +-Shoes\n"
            "    +-Clothes (green pants)\n"
            "    +-Clothes (blue jeans)\n"
            "    +-Mobile J3 by: Samsung\n"
            "    +-Mobile Galaxy Note S7 by: Tamtung\n"
            "    +-Knife, blade: 8 cm\n"
            "    +-Mobile Galaxy Note S7 by: Samsung\n"
            "    \\-Shoes\n" );
    assert ( y . Count () == 44 );
    assert ( y . Weight () == 25100 );
    assert ( y . Danger () );
    y . Add ( w );
    os . str ( "" );
    os << y;
    assert ( os . str () ==
             "Bag by: An Ordinary Bag (TM)\n"
                     "+-Suitcase 1x2x3\n"
                     "| +-Knife, blade: 7 cm\n"
                     "| +-Clothes (red T-shirt)\n"
                     "| +-Clothes (black hat)\n"
                     "| +-Shoes\n"
                     "| +-Clothes (green pants)\n"
                     "| +-Clothes (blue jeans)\n"
                     "| +-Mobile J3 by: Samsung\n"
                     "| +-Mobile Galaxy Note S7 by: Tamtung\n"
                     "| +-Knife, blade: 8 cm\n"
                     "| +-Mobile Galaxy Note S7 by: Samsung\n"
                     "| \\-Shoes\n"
                     "+-Backpack\n"
                     "| +-Knife, blade: 7 cm\n"
                     "| +-Clothes (red T-shirt)\n"
                     "| +-Shoes\n"
                     "| +-Mobile Galaxy Note S7 by: Samsung\n"
                     "| +-Shoes\n"
                     "| +-Clothes (blue jeans)\n"
                     "| +-Clothes (black hat)\n"
                     "| +-Clothes (green pants)\n"
                     "| +-Mobile J3 by: Samsung\n"
                     "| +-Mobile Galaxy Note S7 by: Tamtung\n"
                     "| \\-Knife, blade: 8 cm\n"
                     "+-Suitcase 3x2x1\n"
                     "| +-Backpack\n"
                     "| | +-Knife, blade: 7 cm\n"
                     "| | +-Clothes (red T-shirt)\n"
                     "| | +-Shoes\n"
                     "| | +-Mobile Galaxy Note S7 by: Samsung\n"
                     "| | +-Shoes\n"
                     "| | +-Clothes (blue jeans)\n"
                     "| | +-Clothes (black hat)\n"
                     "| | +-Clothes (green pants)\n"
                     "| | +-Mobile J3 by: Samsung\n"
                     "| | +-Mobile Galaxy Note S7 by: Tamtung\n"
                     "| | \\-Knife, blade: 8 cm\n"
                     "| \\-Suitcase 1x2x3\n"
                     "|   +-Knife, blade: 7 cm\n"
                     "|   +-Clothes (red T-shirt)\n"
                     "|   +-Clothes (black hat)\n"
                     "|   +-Shoes\n"
                     "|   +-Clothes (green pants)\n"
                     "|   +-Clothes (blue jeans)\n"
                     "|   +-Mobile J3 by: Samsung\n"
                     "|   +-Mobile Galaxy Note S7 by: Tamtung\n"
                     "|   +-Knife, blade: 8 cm\n"
                     "|   +-Mobile Galaxy Note S7 by: Samsung\n"
                     "|   \\-Shoes\n"
                     "\\-Suitcase 1x2x3\n"
                     "  +-Knife, blade: 7 cm\n"
                     "  +-Clothes (red T-shirt)\n"
                     "  +-Clothes (black hat)\n"
                     "  +-Shoes\n"
                     "  +-Clothes (green pants)\n"
                     "  +-Clothes (blue jeans)\n"
                     "  +-Mobile J3 by: Samsung\n"
                     "  +-Mobile Galaxy Note S7 by: Tamtung\n"
                     "  +-Knife, blade: 8 cm\n"
                     "  +-Mobile Galaxy Note S7 by: Samsung\n"
                     "  +-Shoes\n"
                     "  \\-Shoes\n" );
    assert ( y . Count () == 56 );
    assert ( y . Weight () == 32000 );
    assert ( y . Danger () );
    y . Add ( x );
    os . str ( "" );
    os << y;
    assert ( os . str () == "Bag by: An Ordinary Bag (TM)\n"
            "+-Suitcase 1x2x3\n"
            "| +-Knife, blade: 7 cm\n"
            "| +-Clothes (red T-shirt)\n"
            "| +-Clothes (black hat)\n"
            "| +-Shoes\n"
            "| +-Clothes (green pants)\n"
            "| +-Clothes (blue jeans)\n"
            "| +-Mobile J3 by: Samsung\n"
            "| +-Mobile Galaxy Note S7 by: Tamtung\n"
            "| +-Knife, blade: 8 cm\n"
            "| +-Mobile Galaxy Note S7 by: Samsung\n"
            "| \\-Shoes\n"
            "+-Backpack\n"
            "| +-Knife, blade: 7 cm\n"
            "| +-Clothes (red T-shirt)\n"
            "| +-Shoes\n"
            "| +-Mobile Galaxy Note S7 by: Samsung\n"
            "| +-Shoes\n"
            "| +-Clothes (blue jeans)\n"
            "| +-Clothes (black hat)\n"
            "| +-Clothes (green pants)\n"
            "| +-Mobile J3 by: Samsung\n"
            "| +-Mobile Galaxy Note S7 by: Tamtung\n"
            "| \\-Knife, blade: 8 cm\n"
            "+-Suitcase 3x2x1\n"
            "| +-Backpack\n"
            "| | +-Knife, blade: 7 cm\n"
            "| | +-Clothes (red T-shirt)\n"
            "| | +-Shoes\n"
            "| | +-Mobile Galaxy Note S7 by: Samsung\n"
            "| | +-Shoes\n"
            "| | +-Clothes (blue jeans)\n"
            "| | +-Clothes (black hat)\n"
            "| | +-Clothes (green pants)\n"
            "| | +-Mobile J3 by: Samsung\n"
            "| | +-Mobile Galaxy Note S7 by: Tamtung\n"
            "| | \\-Knife, blade: 8 cm\n"
            "| \\-Suitcase 1x2x3\n"
            "|   +-Knife, blade: 7 cm\n"
            "|   +-Clothes (red T-shirt)\n"
            "|   +-Clothes (black hat)\n"
            "|   +-Shoes\n"
            "|   +-Clothes (green pants)\n"
            "|   +-Clothes (blue jeans)\n"
            "|   +-Mobile J3 by: Samsung\n"
            "|   +-Mobile Galaxy Note S7 by: Tamtung\n"
            "|   +-Knife, blade: 8 cm\n"
            "|   +-Mobile Galaxy Note S7 by: Samsung\n"
            "|   \\-Shoes\n"
            "+-Suitcase 1x2x3\n"
            "| +-Knife, blade: 7 cm\n"
            "| +-Clothes (red T-shirt)\n"
            "| +-Clothes (black hat)\n"
            "| +-Shoes\n"
            "| +-Clothes (green pants)\n"
            "| +-Clothes (blue jeans)\n"
            "| +-Mobile J3 by: Samsung\n"
            "| +-Mobile Galaxy Note S7 by: Tamtung\n"
            "| +-Knife, blade: 8 cm\n"
            "| +-Mobile Galaxy Note S7 by: Samsung\n"
            "| +-Shoes\n"
            "| \\-Shoes\n"
            "\\-Backpack\n"
            "  +-Knife, blade: 7 cm\n"
            "  +-Clothes (red T-shirt)\n"
            "  +-Shoes\n"
            "  +-Mobile Galaxy Note S7 by: Samsung\n"
            "  +-Shoes\n"
            "  +-Clothes (blue jeans)\n"
            "  +-Clothes (black hat)\n"
            "  +-Clothes (green pants)\n"
            "  +-Mobile J3 by: Samsung\n"
            "  +-Mobile Galaxy Note S7 by: Tamtung\n"
            "  +-Knife, blade: 8 cm\n"
            "  \\-Knife, blade: 12 cm\n" );
    assert ( y . Count () == 68 );
    assert ( y . Weight () == 37250 );
    assert ( y . Danger () );
    y . Add ( y );
    os . str ( "" );
    os << y;
    assert ( os . str () == "Bag by: An Ordinary Bag (TM)\n"
            "+-Suitcase 1x2x3\n"
            "| +-Knife, blade: 7 cm\n"
            "| +-Clothes (red T-shirt)\n"
            "| +-Clothes (black hat)\n"
            "| +-Shoes\n"
            "| +-Clothes (green pants)\n"
            "| +-Clothes (blue jeans)\n"
            "| +-Mobile J3 by: Samsung\n"
            "| +-Mobile Galaxy Note S7 by: Tamtung\n"
            "| +-Knife, blade: 8 cm\n"
            "| +-Mobile Galaxy Note S7 by: Samsung\n"
            "| \\-Shoes\n"
            "+-Backpack\n"
            "| +-Knife, blade: 7 cm\n"
            "| +-Clothes (red T-shirt)\n"
            "| +-Shoes\n"
            "| +-Mobile Galaxy Note S7 by: Samsung\n"
            "| +-Shoes\n"
            "| +-Clothes (blue jeans)\n"
            "| +-Clothes (black hat)\n"
            "| +-Clothes (green pants)\n"
            "| +-Mobile J3 by: Samsung\n"
            "| +-Mobile Galaxy Note S7 by: Tamtung\n"
            "| \\-Knife, blade: 8 cm\n"
            "+-Suitcase 3x2x1\n"
            "| +-Backpack\n"
            "| | +-Knife, blade: 7 cm\n"
            "| | +-Clothes (red T-shirt)\n"
            "| | +-Shoes\n"
            "| | +-Mobile Galaxy Note S7 by: Samsung\n"
            "| | +-Shoes\n"
            "| | +-Clothes (blue jeans)\n"
            "| | +-Clothes (black hat)\n"
            "| | +-Clothes (green pants)\n"
            "| | +-Mobile J3 by: Samsung\n"
            "| | +-Mobile Galaxy Note S7 by: Tamtung\n"
            "| | \\-Knife, blade: 8 cm\n"
            "| \\-Suitcase 1x2x3\n"
            "|   +-Knife, blade: 7 cm\n"
            "|   +-Clothes (red T-shirt)\n"
            "|   +-Clothes (black hat)\n"
            "|   +-Shoes\n"
            "|   +-Clothes (green pants)\n"
            "|   +-Clothes (blue jeans)\n"
            "|   +-Mobile J3 by: Samsung\n"
            "|   +-Mobile Galaxy Note S7 by: Tamtung\n"
            "|   +-Knife, blade: 8 cm\n"
            "|   +-Mobile Galaxy Note S7 by: Samsung\n"
            "|   \\-Shoes\n"
            "+-Suitcase 1x2x3\n"
            "| +-Knife, blade: 7 cm\n"
            "| +-Clothes (red T-shirt)\n"
            "| +-Clothes (black hat)\n"
            "| +-Shoes\n"
            "| +-Clothes (green pants)\n"
            "| +-Clothes (blue jeans)\n"
            "| +-Mobile J3 by: Samsung\n"
            "| +-Mobile Galaxy Note S7 by: Tamtung\n"
            "| +-Knife, blade: 8 cm\n"
            "| +-Mobile Galaxy Note S7 by: Samsung\n"
            "| +-Shoes\n"
            "| \\-Shoes\n"
            "+-Backpack\n"
            "| +-Knife, blade: 7 cm\n"
            "| +-Clothes (red T-shirt)\n"
            "| +-Shoes\n"
            "| +-Mobile Galaxy Note S7 by: Samsung\n"
            "| +-Shoes\n"
            "| +-Clothes (blue jeans)\n"
            "| +-Clothes (black hat)\n"
            "| +-Clothes (green pants)\n"
            "| +-Mobile J3 by: Samsung\n"
            "| +-Mobile Galaxy Note S7 by: Tamtung\n"
            "| +-Knife, blade: 8 cm\n"
            "| \\-Knife, blade: 12 cm\n"
            "\\-Bag by: An Ordinary Bag (TM)\n"
            "  +-Suitcase 1x2x3\n"
            "  | +-Knife, blade: 7 cm\n"
            "  | +-Clothes (red T-shirt)\n"
            "  | +-Clothes (black hat)\n"
            "  | +-Shoes\n"
            "  | +-Clothes (green pants)\n"
            "  | +-Clothes (blue jeans)\n"
            "  | +-Mobile J3 by: Samsung\n"
            "  | +-Mobile Galaxy Note S7 by: Tamtung\n"
            "  | +-Knife, blade: 8 cm\n"
            "  | +-Mobile Galaxy Note S7 by: Samsung\n"
            "  | \\-Shoes\n"
            "  +-Backpack\n"
            "  | +-Knife, blade: 7 cm\n"
            "  | +-Clothes (red T-shirt)\n"
            "  | +-Shoes\n"
            "  | +-Mobile Galaxy Note S7 by: Samsung\n"
            "  | +-Shoes\n"
            "  | +-Clothes (blue jeans)\n"
            "  | +-Clothes (black hat)\n"
            "  | +-Clothes (green pants)\n"
            "  | +-Mobile J3 by: Samsung\n"
            "  | +-Mobile Galaxy Note S7 by: Tamtung\n"
            "  | \\-Knife, blade: 8 cm\n"
            "  +-Suitcase 3x2x1\n"
            "  | +-Backpack\n"
            "  | | +-Knife, blade: 7 cm\n"
            "  | | +-Clothes (red T-shirt)\n"
            "  | | +-Shoes\n"
            "  | | +-Mobile Galaxy Note S7 by: Samsung\n"
            "  | | +-Shoes\n"
            "  | | +-Clothes (blue jeans)\n"
            "  | | +-Clothes (black hat)\n"
            "  | | +-Clothes (green pants)\n"
            "  | | +-Mobile J3 by: Samsung\n"
            "  | | +-Mobile Galaxy Note S7 by: Tamtung\n"
            "  | | \\-Knife, blade: 8 cm\n"
            "  | \\-Suitcase 1x2x3\n"
            "  |   +-Knife, blade: 7 cm\n"
            "  |   +-Clothes (red T-shirt)\n"
            "  |   +-Clothes (black hat)\n"
            "  |   +-Shoes\n"
            "  |   +-Clothes (green pants)\n"
            "  |   +-Clothes (blue jeans)\n"
            "  |   +-Mobile J3 by: Samsung\n"
            "  |   +-Mobile Galaxy Note S7 by: Tamtung\n"
            "  |   +-Knife, blade: 8 cm\n"
            "  |   +-Mobile Galaxy Note S7 by: Samsung\n"
            "  |   \\-Shoes\n"
            "  +-Suitcase 1x2x3\n"
            "  | +-Knife, blade: 7 cm\n"
            "  | +-Clothes (red T-shirt)\n"
            "  | +-Clothes (black hat)\n"
            "  | +-Shoes\n"
            "  | +-Clothes (green pants)\n"
            "  | +-Clothes (blue jeans)\n"
            "  | +-Mobile J3 by: Samsung\n"
            "  | +-Mobile Galaxy Note S7 by: Tamtung\n"
            "  | +-Knife, blade: 8 cm\n"
            "  | +-Mobile Galaxy Note S7 by: Samsung\n"
            "  | +-Shoes\n"
            "  | \\-Shoes\n"
            "  \\-Backpack\n"
            "    +-Knife, blade: 7 cm\n"
            "    +-Clothes (red T-shirt)\n"
            "    +-Shoes\n"
            "    +-Mobile Galaxy Note S7 by: Samsung\n"
            "    +-Shoes\n"
            "    +-Clothes (blue jeans)\n"
            "    +-Clothes (black hat)\n"
            "    +-Clothes (green pants)\n"
            "    +-Mobile J3 by: Samsung\n"
            "    +-Mobile Galaxy Note S7 by: Tamtung\n"
            "    +-Knife, blade: 8 cm\n"
            "    \\-Knife, blade: 12 cm\n" );
    assert ( y . Count () == 136 );
    assert ( y . Weight () == 74500 );
    assert ( y . Danger () );
    y . Add ( y );
    os . str ( "" );
    os << y;
    assert ( os . str () == "Bag by: An Ordinary Bag (TM)\n"
            "+-Suitcase 1x2x3\n"
            "| +-Knife, blade: 7 cm\n"
            "| +-Clothes (red T-shirt)\n"
            "| +-Clothes (black hat)\n"
            "| +-Shoes\n"
            "| +-Clothes (green pants)\n"
            "| +-Clothes (blue jeans)\n"
            "| +-Mobile J3 by: Samsung\n"
            "| +-Mobile Galaxy Note S7 by: Tamtung\n"
            "| +-Knife, blade: 8 cm\n"
            "| +-Mobile Galaxy Note S7 by: Samsung\n"
            "| \\-Shoes\n"
            "+-Backpack\n"
            "| +-Knife, blade: 7 cm\n"
            "| +-Clothes (red T-shirt)\n"
            "| +-Shoes\n"
            "| +-Mobile Galaxy Note S7 by: Samsung\n"
            "| +-Shoes\n"
            "| +-Clothes (blue jeans)\n"
            "| +-Clothes (black hat)\n"
            "| +-Clothes (green pants)\n"
            "| +-Mobile J3 by: Samsung\n"
            "| +-Mobile Galaxy Note S7 by: Tamtung\n"
            "| \\-Knife, blade: 8 cm\n"
            "+-Suitcase 3x2x1\n"
            "| +-Backpack\n"
            "| | +-Knife, blade: 7 cm\n"
            "| | +-Clothes (red T-shirt)\n"
            "| | +-Shoes\n"
            "| | +-Mobile Galaxy Note S7 by: Samsung\n"
            "| | +-Shoes\n"
            "| | +-Clothes (blue jeans)\n"
            "| | +-Clothes (black hat)\n"
            "| | +-Clothes (green pants)\n"
            "| | +-Mobile J3 by: Samsung\n"
            "| | +-Mobile Galaxy Note S7 by: Tamtung\n"
            "| | \\-Knife, blade: 8 cm\n"
            "| \\-Suitcase 1x2x3\n"
            "|   +-Knife, blade: 7 cm\n"
            "|   +-Clothes (red T-shirt)\n"
            "|   +-Clothes (black hat)\n"
            "|   +-Shoes\n"
            "|   +-Clothes (green pants)\n"
            "|   +-Clothes (blue jeans)\n"
            "|   +-Mobile J3 by: Samsung\n"
            "|   +-Mobile Galaxy Note S7 by: Tamtung\n"
            "|   +-Knife, blade: 8 cm\n"
            "|   +-Mobile Galaxy Note S7 by: Samsung\n"
            "|   \\-Shoes\n"
            "+-Suitcase 1x2x3\n"
            "| +-Knife, blade: 7 cm\n"
            "| +-Clothes (red T-shirt)\n"
            "| +-Clothes (black hat)\n"
            "| +-Shoes\n"
            "| +-Clothes (green pants)\n"
            "| +-Clothes (blue jeans)\n"
            "| +-Mobile J3 by: Samsung\n"
            "| +-Mobile Galaxy Note S7 by: Tamtung\n"
            "| +-Knife, blade: 8 cm\n"
            "| +-Mobile Galaxy Note S7 by: Samsung\n"
            "| +-Shoes\n"
            "| \\-Shoes\n"
            "+-Backpack\n"
            "| +-Knife, blade: 7 cm\n"
            "| +-Clothes (red T-shirt)\n"
            "| +-Shoes\n"
            "| +-Mobile Galaxy Note S7 by: Samsung\n"
            "| +-Shoes\n"
            "| +-Clothes (blue jeans)\n"
            "| +-Clothes (black hat)\n"
            "| +-Clothes (green pants)\n"
            "| +-Mobile J3 by: Samsung\n"
            "| +-Mobile Galaxy Note S7 by: Tamtung\n"
            "| +-Knife, blade: 8 cm\n"
            "| \\-Knife, blade: 12 cm\n"
            "+-Bag by: An Ordinary Bag (TM)\n"
            "| +-Suitcase 1x2x3\n"
            "| | +-Knife, blade: 7 cm\n"
            "| | +-Clothes (red T-shirt)\n"
            "| | +-Clothes (black hat)\n"
            "| | +-Shoes\n"
            "| | +-Clothes (green pants)\n"
            "| | +-Clothes (blue jeans)\n"
            "| | +-Mobile J3 by: Samsung\n"
            "| | +-Mobile Galaxy Note S7 by: Tamtung\n"
            "| | +-Knife, blade: 8 cm\n"
            "| | +-Mobile Galaxy Note S7 by: Samsung\n"
            "| | \\-Shoes\n"
            "| +-Backpack\n"
            "| | +-Knife, blade: 7 cm\n"
            "| | +-Clothes (red T-shirt)\n"
            "| | +-Shoes\n"
            "| | +-Mobile Galaxy Note S7 by: Samsung\n"
            "| | +-Shoes\n"
            "| | +-Clothes (blue jeans)\n"
            "| | +-Clothes (black hat)\n"
            "| | +-Clothes (green pants)\n"
            "| | +-Mobile J3 by: Samsung\n"
            "| | +-Mobile Galaxy Note S7 by: Tamtung\n"
            "| | \\-Knife, blade: 8 cm\n"
            "| +-Suitcase 3x2x1\n"
            "| | +-Backpack\n"
            "| | | +-Knife, blade: 7 cm\n"
            "| | | +-Clothes (red T-shirt)\n"
            "| | | +-Shoes\n"
            "| | | +-Mobile Galaxy Note S7 by: Samsung\n"
            "| | | +-Shoes\n"
            "| | | +-Clothes (blue jeans)\n"
            "| | | +-Clothes (black hat)\n"
            "| | | +-Clothes (green pants)\n"
            "| | | +-Mobile J3 by: Samsung\n"
            "| | | +-Mobile Galaxy Note S7 by: Tamtung\n"
            "| | | \\-Knife, blade: 8 cm\n"
            "| | \\-Suitcase 1x2x3\n"
            "| |   +-Knife, blade: 7 cm\n"
            "| |   +-Clothes (red T-shirt)\n"
            "| |   +-Clothes (black hat)\n"
            "| |   +-Shoes\n"
            "| |   +-Clothes (green pants)\n"
            "| |   +-Clothes (blue jeans)\n"
            "| |   +-Mobile J3 by: Samsung\n"
            "| |   +-Mobile Galaxy Note S7 by: Tamtung\n"
            "| |   +-Knife, blade: 8 cm\n"
            "| |   +-Mobile Galaxy Note S7 by: Samsung\n"
            "| |   \\-Shoes\n"
            "| +-Suitcase 1x2x3\n"
            "| | +-Knife, blade: 7 cm\n"
            "| | +-Clothes (red T-shirt)\n"
            "| | +-Clothes (black hat)\n"
            "| | +-Shoes\n"
            "| | +-Clothes (green pants)\n"
            "| | +-Clothes (blue jeans)\n"
            "| | +-Mobile J3 by: Samsung\n"
            "| | +-Mobile Galaxy Note S7 by: Tamtung\n"
            "| | +-Knife, blade: 8 cm\n"
            "| | +-Mobile Galaxy Note S7 by: Samsung\n"
            "| | +-Shoes\n"
            "| | \\-Shoes\n"
            "| \\-Backpack\n"
            "|   +-Knife, blade: 7 cm\n"
            "|   +-Clothes (red T-shirt)\n"
            "|   +-Shoes\n"
            "|   +-Mobile Galaxy Note S7 by: Samsung\n"
            "|   +-Shoes\n"
            "|   +-Clothes (blue jeans)\n"
            "|   +-Clothes (black hat)\n"
            "|   +-Clothes (green pants)\n"
            "|   +-Mobile J3 by: Samsung\n"
            "|   +-Mobile Galaxy Note S7 by: Tamtung\n"
            "|   +-Knife, blade: 8 cm\n"
            "|   \\-Knife, blade: 12 cm\n"
            "\\-Bag by: An Ordinary Bag (TM)\n"
            "  +-Suitcase 1x2x3\n"
            "  | +-Knife, blade: 7 cm\n"
            "  | +-Clothes (red T-shirt)\n"
            "  | +-Clothes (black hat)\n"
            "  | +-Shoes\n"
            "  | +-Clothes (green pants)\n"
            "  | +-Clothes (blue jeans)\n"
            "  | +-Mobile J3 by: Samsung\n"
            "  | +-Mobile Galaxy Note S7 by: Tamtung\n"
            "  | +-Knife, blade: 8 cm\n"
            "  | +-Mobile Galaxy Note S7 by: Samsung\n"
            "  | \\-Shoes\n"
            "  +-Backpack\n"
            "  | +-Knife, blade: 7 cm\n"
            "  | +-Clothes (red T-shirt)\n"
            "  | +-Shoes\n"
            "  | +-Mobile Galaxy Note S7 by: Samsung\n"
            "  | +-Shoes\n"
            "  | +-Clothes (blue jeans)\n"
            "  | +-Clothes (black hat)\n"
            "  | +-Clothes (green pants)\n"
            "  | +-Mobile J3 by: Samsung\n"
            "  | +-Mobile Galaxy Note S7 by: Tamtung\n"
            "  | \\-Knife, blade: 8 cm\n"
            "  +-Suitcase 3x2x1\n"
            "  | +-Backpack\n"
            "  | | +-Knife, blade: 7 cm\n"
            "  | | +-Clothes (red T-shirt)\n"
            "  | | +-Shoes\n"
            "  | | +-Mobile Galaxy Note S7 by: Samsung\n"
            "  | | +-Shoes\n"
            "  | | +-Clothes (blue jeans)\n"
            "  | | +-Clothes (black hat)\n"
            "  | | +-Clothes (green pants)\n"
            "  | | +-Mobile J3 by: Samsung\n"
            "  | | +-Mobile Galaxy Note S7 by: Tamtung\n"
            "  | | \\-Knife, blade: 8 cm\n"
            "  | \\-Suitcase 1x2x3\n"
            "  |   +-Knife, blade: 7 cm\n"
            "  |   +-Clothes (red T-shirt)\n"
            "  |   +-Clothes (black hat)\n"
            "  |   +-Shoes\n"
            "  |   +-Clothes (green pants)\n"
            "  |   +-Clothes (blue jeans)\n"
            "  |   +-Mobile J3 by: Samsung\n"
            "  |   +-Mobile Galaxy Note S7 by: Tamtung\n"
            "  |   +-Knife, blade: 8 cm\n"
            "  |   +-Mobile Galaxy Note S7 by: Samsung\n"
            "  |   \\-Shoes\n"
            "  +-Suitcase 1x2x3\n"
            "  | +-Knife, blade: 7 cm\n"
            "  | +-Clothes (red T-shirt)\n"
            "  | +-Clothes (black hat)\n"
            "  | +-Shoes\n"
            "  | +-Clothes (green pants)\n"
            "  | +-Clothes (blue jeans)\n"
            "  | +-Mobile J3 by: Samsung\n"
            "  | +-Mobile Galaxy Note S7 by: Tamtung\n"
            "  | +-Knife, blade: 8 cm\n"
            "  | +-Mobile Galaxy Note S7 by: Samsung\n"
            "  | +-Shoes\n"
            "  | \\-Shoes\n"
            "  +-Backpack\n"
            "  | +-Knife, blade: 7 cm\n"
            "  | +-Clothes (red T-shirt)\n"
            "  | +-Shoes\n"
            "  | +-Mobile Galaxy Note S7 by: Samsung\n"
            "  | +-Shoes\n"
            "  | +-Clothes (blue jeans)\n"
            "  | +-Clothes (black hat)\n"
            "  | +-Clothes (green pants)\n"
            "  | +-Mobile J3 by: Samsung\n"
            "  | +-Mobile Galaxy Note S7 by: Tamtung\n"
            "  | +-Knife, blade: 8 cm\n"
            "  | \\-Knife, blade: 12 cm\n"
            "  \\-Bag by: An Ordinary Bag (TM)\n"
            "    +-Suitcase 1x2x3\n"
            "    | +-Knife, blade: 7 cm\n"
            "    | +-Clothes (red T-shirt)\n"
            "    | +-Clothes (black hat)\n"
            "    | +-Shoes\n"
            "    | +-Clothes (green pants)\n"
            "    | +-Clothes (blue jeans)\n"
            "    | +-Mobile J3 by: Samsung\n"
            "    | +-Mobile Galaxy Note S7 by: Tamtung\n"
            "    | +-Knife, blade: 8 cm\n"
            "    | +-Mobile Galaxy Note S7 by: Samsung\n"
            "    | \\-Shoes\n"
            "    +-Backpack\n"
            "    | +-Knife, blade: 7 cm\n"
            "    | +-Clothes (red T-shirt)\n"
            "    | +-Shoes\n"
            "    | +-Mobile Galaxy Note S7 by: Samsung\n"
            "    | +-Shoes\n"
            "    | +-Clothes (blue jeans)\n"
            "    | +-Clothes (black hat)\n"
            "    | +-Clothes (green pants)\n"
            "    | +-Mobile J3 by: Samsung\n"
            "    | +-Mobile Galaxy Note S7 by: Tamtung\n"
            "    | \\-Knife, blade: 8 cm\n"
            "    +-Suitcase 3x2x1\n"
            "    | +-Backpack\n"
            "    | | +-Knife, blade: 7 cm\n"
            "    | | +-Clothes (red T-shirt)\n"
            "    | | +-Shoes\n"
            "    | | +-Mobile Galaxy Note S7 by: Samsung\n"
            "    | | +-Shoes\n"
            "    | | +-Clothes (blue jeans)\n"
            "    | | +-Clothes (black hat)\n"
            "    | | +-Clothes (green pants)\n"
            "    | | +-Mobile J3 by: Samsung\n"
            "    | | +-Mobile Galaxy Note S7 by: Tamtung\n"
            "    | | \\-Knife, blade: 8 cm\n"
            "    | \\-Suitcase 1x2x3\n"
            "    |   +-Knife, blade: 7 cm\n"
            "    |   +-Clothes (red T-shirt)\n"
            "    |   +-Clothes (black hat)\n"
            "    |   +-Shoes\n"
            "    |   +-Clothes (green pants)\n"
            "    |   +-Clothes (blue jeans)\n"
            "    |   +-Mobile J3 by: Samsung\n"
            "    |   +-Mobile Galaxy Note S7 by: Tamtung\n"
            "    |   +-Knife, blade: 8 cm\n"
            "    |   +-Mobile Galaxy Note S7 by: Samsung\n"
            "    |   \\-Shoes\n"
            "    +-Suitcase 1x2x3\n"
            "    | +-Knife, blade: 7 cm\n"
            "    | +-Clothes (red T-shirt)\n"
            "    | +-Clothes (black hat)\n"
            "    | +-Shoes\n"
            "    | +-Clothes (green pants)\n"
            "    | +-Clothes (blue jeans)\n"
            "    | +-Mobile J3 by: Samsung\n"
            "    | +-Mobile Galaxy Note S7 by: Tamtung\n"
            "    | +-Knife, blade: 8 cm\n"
            "    | +-Mobile Galaxy Note S7 by: Samsung\n"
            "    | +-Shoes\n"
            "    | \\-Shoes\n"
            "    \\-Backpack\n"
            "      +-Knife, blade: 7 cm\n"
            "      +-Clothes (red T-shirt)\n"
            "      +-Shoes\n"
            "      +-Mobile Galaxy Note S7 by: Samsung\n"
            "      +-Shoes\n"
            "      +-Clothes (blue jeans)\n"
            "      +-Clothes (black hat)\n"
            "      +-Clothes (green pants)\n"
            "      +-Mobile J3 by: Samsung\n"
            "      +-Mobile Galaxy Note S7 by: Tamtung\n"
            "      +-Knife, blade: 8 cm\n"
            "      \\-Knife, blade: 12 cm\n" );
    assert ( y . Count () == 272 );
    assert ( y . Weight () == 149000 );
    assert ( y . Danger () );
    assert ( w . IdenticalContents ( w ) );





//    assert ( !w . IdenticalContents ( x ) );


    assert ( !w . IdenticalContents ( y ) );
    assert ( !x . IdenticalContents ( w ) );
    assert ( x . IdenticalContents ( x ) );
    assert ( !x . IdenticalContents ( y ) );
    assert ( !y . IdenticalContents ( w ) );
    assert ( !y . IdenticalContents ( x ) );
    assert ( y . IdenticalContents ( y ) );
    return 0;
}
#endif /* __PROGTEST__ */
