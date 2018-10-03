#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <algorithm>

using namespace std;



struct priceCount
{
   priceCount(int pr, int cn) : price(pr), count(cn) {};
   int price;
   int count;
};

typedef std::map < std::string, std::list<priceCount>> mapOfElems;





class CWarehouse
{
private:
   mapOfElems m_Data;



public:

   ///CONSTRUCTOR
   CWarehouse() : m_Data()
   {};

   ///DESTRUCTOR
   ~CWarehouse(){};




   struct compareIt
   {
      bool operator()(const priceCount & a, const priceCount & b) const
      {
         return a.price > b.price;
      }

   };

   struct comparetoList
   {
      bool operator()(const priceCount & a, const priceCount & b) const
      {
         return ( a.count < b.count ) || (a.price > b.price ) ;
      }

   };


   ///STORE elements
   void Store(std::istream & is)
   {
      std::string str;

      ///parse all lines
      while(std::getline(is, str))
      {
         ///parse one line
         std::string elementName;
         int price, count;
         char a;
         istringstream line(str);
         getline(line, elementName, ';');
         line >> price >> a >> count;

         ///add new item
         mapOfElems::iterator it =  m_Data.find(elementName);
         if(it == m_Data.end())
         {
            m_Data.insert(pair<std::string, std::list<priceCount>>(elementName,std::list<priceCount>{priceCount(price, count)} ));
         }

         ///update count of items
         else
         {
            ((*it).second).push_back(priceCount(price, count));
         }

      }
   }


   ///SELL
   bool Sell( const std::string & name, int cnt, int & price )
   {
      mapOfElems::iterator it = m_Data.find(name);

      bool sellable = false;

      if (it == m_Data.end())
         return false;

      (it->second).sort(compareIt());


      int currentCnt = 0;
      int currentPrice = 0;

      for( auto & x : (it->second))
      {
         if( currentCnt + x.count >= cnt)
         {
            sellable = true;
            break;
         }
      }

      if(sellable)
      {
         currentCnt = 0 ;

         list<priceCount>::iterator iter = (it->second).begin();
         while (iter !=(it->second).end())
         {
            if( currentCnt += iter->count < cnt )
            {
               currentPrice += iter->price * iter->count;

               iter = it->second.erase(iter);
            }

            else
            {
               int tmp =  cnt - currentCnt;
               currentPrice += iter->price *tmp;
               iter->count = tmp;
               break;
            }
         }

         price = currentPrice;
         return true;
      }


      return false;
   }

  ///LIST
  std::list< pair<int,int> > List( const std::string & name)
  {
     mapOfElems::iterator it =  m_Data.find(name);

     (it->second).sort(comparetoList());
     std::list<pair<int,int>> toReturn;

     for (auto & x : (it->second))
     {
        toReturn.push_back(make_pair(x.price, x.count));
     }

     return toReturn;
  };

};


void showList ( const list< pair<int,int> > & l )
{
   for ( list< pair<int,int> >::const_iterator it = l . begin (); it != l . end (); ++it )
      cout << it -> first << " Kc " << it -> second << 'x' << endl;
}

int main()
{
   CWarehouse  w;
   bool        ok;
   int         price;
   istringstream iss;

   iss . clear ();
   iss . str (
           "Saw;300;10\n"
                   "Hammer;100;20\n"
                   "Wire cutters;150;15\n"
                   "Saw;500;3\n"
                   "Hammer;80;14\n"
                   "Saw;100;10\n"
                   "Hammer;120;4\n"
                   "Screw;1;5000\n"
                   "Hammer;100;4\n"
                   "Hammer;80;10\n"
   );
   w . Store ( iss );
   ok = w . Sell ( "Saw", 5, price ); // ok = true, price = 2100
   ok = w . Sell ( "Saw", 10, price ); // ok = true, price = 2600
   ok = w . Sell ( "Wire cutters", 20, price ); // ok = false
   ok = w . Sell ( "Nail", 100, price ); // ok = false
   iss . clear ();
   iss . str (
           "Wire cutters;200;10\n"
                   "Nut;2;800\n"
                   "Hammer;20;100\n"
                   "Saw;305;12\n"
   );
   w . Store ( iss );
   ok = w . Sell ( "Wire cutters", 20, price ); // ok = true, price = 3500
   showList ( w . List ( "Saw" ) );
   /*
   ---8<---8<---8<---8<---8<---8<---
   100 Kc 8x
   305 Kc 12x
   ---8<---8<---8<---8<---8<---8<---
   */
   showList ( w . List ( "Wire cutters" ) );
   /*
   ---8<---8<---8<---8<---8<---8<---
   150 Kc 5x
   ---8<---8<---8<---8<---8<---8<---
   */
   showList ( w . List ( "Hammer" ) );
   /*
   ---8<---8<---8<---8<---8<---8<---
   120 Kc 4x
   100 Kc 24x
   80 Kc 24x
   20 Kc 100x
   ---8<---8<---8<---8<---8<---8<---
   */
}