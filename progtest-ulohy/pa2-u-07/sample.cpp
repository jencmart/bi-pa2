/***
 *
 * CITEM

CShoes -   hmotnost 750g/ks
CClothes - hmotnost 500g/ks ;   stručný popis (řetězec).
CKnife -   hmotnosti 100g/ks ;  délku čepele (v cm).
CMobile -  hmotnost 150g/ks ;   značka ; model.

 *******************************
 CLUGGAGE

CSuitcase = 2000g
CBackpack = 1000g


 Add
přidat libovolné vybavení výše. (void)

 Weight
hmotnost celého kufru/batohu + obsahu; (cele cislo).

 Danger
 nůž delší než 7 cm || mobilní telefon Samsung Galaxy Note S7. (true/false)

 Count
 která nám zjistí počet věcí v kufru (celé číslo).

 IdenticalContents (x)
nezalezni na zavazadle ; nezalezi na poradi  (true/false)

 Operátor <<
 kterým půjde zobrazit obsah celého kufru/batohu (viz ukázka níže).




 Implementace vyžaduje, abyste využili dědění a
polymorfismu a dále vyžaduje, abyste atributy (členské proměnné) umístili právě jen do těch tříd, které je potřebují.
Rozhodně nebude fungovat pokud všechny atributy umístíte do základní třídy.

 */



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
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <algorithm>
using namespace std;
#endif /* __PROGTEST_ */

///*******************************************************************************
class CItem
{
public:
    CItem(int weight) : m_weight(weight) {};

    //operator <<
    friend ostream & operator << (ostream & os , const CItem & x ) { x.Print(os); return os;}
    ///virtual Print
    virtual void Print(ostream & os) const = 0;

    // operator ==
    bool operator == (const CItem & other) const { return m_weight == other.m_weight ? Equals(other) : false; }
    /// virtual Equals
    virtual bool Equals(const CItem & other) const = 0;

    ///virutal Dangerous
    virtual bool Dangerous() const = 0;

    //Weight
    int Weight() const { return m_weight; }

protected:
    int m_weight;
};

///*******************************************************************************
class CKnife : public  CItem
{
public:
    CKnife (int bladeLength ) : CItem(100), m_bladeLength(bladeLength){};
    void Print(ostream & os) const override { os << "-Knife, blade: " << m_bladeLength << " cm" ; }
    bool Equals(const CItem & other) const override { return m_bladeLength == ((const CKnife &)other).m_bladeLength; }
    bool Dangerous() const override { return m_bladeLength > 7; }

private:
    int m_bladeLength;
};

///*******************************************************************************
class CClothes : public  CItem
{
public:
    CClothes (const string & description ) : CItem(500), m_description(description){};
    void Print(ostream & os) const override { os << "-Clothes (" << m_description << ")" ; }
    bool Equals(const CItem & other) const override { return m_description == ((const CClothes &)other).m_description; }
    bool Dangerous() const override { return false; }
private:
    string m_description;
};

///*******************************************************************************
class CShoes : public  CItem
{
public:
    CShoes () : CItem(750) {};
    void Print(ostream & os) const override { os << "-Shoes" ; }
    bool Equals(const CItem & other) const override { return true; }
    bool Dangerous() const override { return false; }
};

///*******************************************************************************
class CMobile : public  CItem
{
public:
    CMobile (const string & brand, const string & type) : CItem(150), m_brand(brand), m_type(type) {};
    void Print(ostream & os) const override { os << "-Mobile " << m_type << " by: " << m_brand; }
    bool Equals(const CItem & other) const override
    {
      return m_brand == ((const CMobile &)other).m_brand &&
             m_type == ((const CMobile &)other).m_type ;
    }
    bool Dangerous() const override { return m_brand == "Samsung" && m_type == "Galaxy Note S7"; }

private:
    string m_brand;
    string m_type;
};

class CLuggage
{
public:
    CLuggage(int weight) : m_content(), m_weight(weight), m_contentWeight(0), m_dangerousContent(false) {}

    ///WEIGHT
    int Weight() const { return m_weight + m_contentWeight ; }

    ///DANGER
    bool Danger() const { return m_dangerousContent; }

    ///COUNT
    size_t Count() const { return m_content.size(); }

    ///IDENTICAL
    bool IdenticalContents(const CLuggage & other)
    {
      if(m_content.size() != other.m_content.size())
        return false;

      for(  auto const & item : m_content ) {
        bool found = false;

        for ( auto const & itemOther : other.m_content)
          if(item == itemOther)
            found = true;

        if (! found)
          return false;
      }

      return true;
    }

    //COUT
    friend ostream &operator << (ostream & os, const CLuggage & other) { other.Print(os) ; return os;}
    ///virtual PRINT
    virtual void Print(ostream & os) const = 0;

protected:
    std::vector<unique_ptr<CItem>> m_content;
    int m_weight;
    int m_contentWeight;
    bool m_dangerousContent;

};


class CSuitcase : public CLuggage
{
public:
    ///CONSTOR
    CSuitcase(int w, int h, int d) : CLuggage(2000), m_w(w), m_h(h), m_d(d) {}

    ///ADD
    CSuitcase & Add(const CKnife &knife) {
      m_content.push_back(unique_ptr<CItem>(new CKnife(knife)));
      m_dangerousContent =  m_dangerousContent ? m_dangerousContent : m_content.back()->Dangerous();
      m_contentWeight += m_content.back()->Weight();
      return *this;
    }

    CSuitcase & Add(const CClothes &clothes) {
      m_content.push_back(unique_ptr<CItem>(  new CClothes(clothes)));
      m_dangerousContent =  m_dangerousContent ? m_dangerousContent : m_content.back()->Dangerous();
      m_contentWeight += m_content.back()->Weight();
      return *this;
    }

    CSuitcase & Add(const CShoes &shoes) {
      m_content.push_back(unique_ptr<CItem>( new CShoes(shoes))) ;
      m_dangerousContent =  m_dangerousContent ? m_dangerousContent : m_content.back()->Dangerous();
      m_contentWeight += m_content.back()->Weight();
      return *this;
    }

    CSuitcase & Add(const CMobile &mobile) {
      m_content.push_back(unique_ptr<CItem>( new CMobile(mobile)));
      m_dangerousContent =   m_dangerousContent ? m_dangerousContent : m_content.back()->Dangerous();
      m_contentWeight += m_content.back()->Weight();
      return *this;
    }


    ///PRINT
    void Print(ostream & os) const override
    {
      os << "Suitcase " << m_w << "x" << m_h << "x" << m_d << "\n" ;

      for(size_t i = 0; i < m_content.size() ; ++i)
      {
        if(i+1 < m_content.size() )
          os << "+" ;
        else
          os << "\\" ;

        os <<  *(m_content[i]) << endl ;
      }

    }

private:

    int m_w, m_h, m_d;

};

class CBackpack : public CLuggage
{
public:
    ///CONSTOR
    CBackpack() : CLuggage(1000) {}

    ///ADD
    CBackpack & Add(const CKnife &knife) {
      m_content.push_back(unique_ptr<CItem>(new CKnife(knife)));
      m_dangerousContent =   m_dangerousContent ? m_dangerousContent : m_content.back()->Dangerous();
      m_contentWeight += m_content.back()->Weight();
      return *this;
    }

    CBackpack & Add(const CClothes &clothes) {
      m_content.push_back(unique_ptr<CItem>(  new CClothes(clothes)));
      m_dangerousContent =   m_dangerousContent ? m_dangerousContent : m_content.back()->Dangerous();
      m_contentWeight += m_content.back()->Weight();
      return *this;
    }

    CBackpack & Add(const CShoes &shoes) {
      m_content.push_back(unique_ptr<CItem>( new CShoes(shoes))) ;
      m_dangerousContent = m_content.back()->Dangerous();
      m_contentWeight += m_content.back()->Weight();
      return *this;
    }

    CBackpack & Add(const CMobile &mobile) {
      m_content.push_back(unique_ptr<CItem>( new CMobile(mobile)));
      m_dangerousContent = m_dangerousContent ? m_dangerousContent : m_content.back()->Dangerous();
      m_contentWeight += m_content.back()->Weight();
      return *this;
    }

    void Print(ostream & os) const override
    {
      os << "Backpack\n" ;
      for(size_t i = 0; i < m_content.size() ; ++i)
      {
        if(i+1 < m_content.size() )
          os << "+" ;
        else
          os << "\\" ;

        os <<  *(m_content[i]) << endl ;
      }
    }

};

#ifndef __PROGTEST__
int main ( void )
{
  CSuitcase x ( 1, 2, 3 );
  CBackpack y;
  ostringstream os;
  x . Add ( CKnife ( 7 ) );
  x . Add ( CClothes ( "red T-shirt" ) );
  x . Add ( CClothes ( "black hat" ) );
  x . Add ( CShoes () );
  x . Add ( CClothes ( "green pants" ) );
  x . Add ( CClothes ( "blue jeans" ) );
  x . Add ( CMobile ( "Samsung", "J3" ) );
  x . Add ( CMobile ( "Tamtung", "Galaxy Note S7" ) );
  os . str ( "" );
  os << x;
  assert ( os . str () == "Suitcase 1x2x3\n"
          "+-Knife, blade: 7 cm\n"
          "+-Clothes (red T-shirt)\n"
          "+-Clothes (black hat)\n"
          "+-Shoes\n"
          "+-Clothes (green pants)\n"
          "+-Clothes (blue jeans)\n"
          "+-Mobile J3 by: Samsung\n"
          "\\-Mobile Galaxy Note S7 by: Tamtung\n" );
  assert ( x . Count () == 8 );
  assert ( x . Weight () == 5150 );
  assert ( !x . Danger () );
  x . Add ( CKnife ( 8 ) );
  os . str ( "" );
  os << x;
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
  assert ( x . Count () == 9 );
  assert ( x . Weight () == 5250 );
  assert ( x . Danger () );

  y . Add ( CKnife ( 7 ) )
          . Add ( CClothes ( "red T-shirt" ) )
          . Add ( CShoes () );

  y . Add ( CMobile ( "Samsung", "Galaxy Note S7" ) );
  y . Add ( CShoes () );
  y . Add ( CClothes ( "blue jeans" ) );
  y . Add ( CClothes ( "black hat" ) );
  y . Add ( CClothes ( "green pants" ) );
  os . str ( "" );
  os << y;
  assert ( os . str () == "Backpack\n"
          "+-Knife, blade: 7 cm\n"
          "+-Clothes (red T-shirt)\n"
          "+-Shoes\n"
          "+-Mobile Galaxy Note S7 by: Samsung\n"
          "+-Shoes\n"
          "+-Clothes (blue jeans)\n"
          "+-Clothes (black hat)\n"
          "\\-Clothes (green pants)\n" );
  assert ( y . Count () == 8 );
  assert ( y . Weight () == 4750 );

  assert ( y . Danger () );
  y . Add ( CMobile ( "Samsung", "J3" ) );
  y . Add ( CMobile ( "Tamtung", "Galaxy Note S7" ) );
  y . Add ( CKnife ( 8 ) );
  os . str ( "" );
  os << y;
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
  assert ( y . Count () == 11 );
  assert ( y . Weight () == 5150 );
  assert ( y . Danger () );
  assert ( !x . IdenticalContents ( y ) );
  assert ( !y . IdenticalContents ( x ) );
  x . Add ( CMobile ( "Samsung", "Galaxy Note S7" ) );
  assert ( !x . IdenticalContents ( y ) );
  assert ( !y . IdenticalContents ( x ) );
  x . Add ( CShoes () );
  assert ( x . IdenticalContents ( y ) );
  assert ( y . IdenticalContents ( x ) );
  assert ( y . IdenticalContents ( y ) );
  assert ( x . IdenticalContents ( x ) );
  return 0;
}
#endif /* __PROGTEST__ */
