#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>



using namespace std;

class CNameException{
public:
  std::string m_name;

   CNameException(const std::string name) : m_name(name){};

   friend std::ostream &operator << (std::ostream & os, const CNameException & x)
   {
      os << "'" << x.m_name<< "': "<< "unknown" << std::endl;
      return  os;
   }
};

struct TStop
{
public:
   TStop *m_Next;
   TStop *m_Prev;
   std::string m_Name;

   TStop(const std::string &name) : m_Next(NULL), m_Prev(NULL), m_Name(name)
   {};
};


class TTrip
{
private:
   TStop * m_begin;
   TStop * m_end;
   bool m_rightWay;
   int m_distance;


   /// CALCULATE DISTANCE
   void calculateStops()
   {
      TStop * it ;
      int i = 1;
      if(m_rightWay)
      {

         it = m_begin;
         while (it != m_end)
         {
            i++;
            it = it->m_Next;
         }
      }

      else
      {
         it = m_begin;
         while (it != m_end)
         {
            i++;
            it = it->m_Prev;
         }
      }

      m_distance = i;
   }

public:

   TTrip(TStop * begin, TStop * end, bool way) : m_begin(begin), m_end(end), m_rightWay(way)
   {
      calculateStops();
   };

   int Stops() const
   { return  m_distance; }


   friend std::ostream & operator << (std::ostream & os, const TTrip & x)
   {
      TStop * it = x.m_begin;

      if(x.m_rightWay)
      {
         while(it != x.m_end)
         {
            os << it->m_Name << std::endl;
            it = it->m_Next;
         }
         os << it->m_Name << std::endl;
      }

      else
      {
         while(it != x.m_end)
         {
            os << it->m_Name << std::endl;
            it = it->m_Prev;
         }
         os << it->m_Name << std::endl;
      }

      return os;
   }

};

class CBusLine
{
private:
   TStop *m_Terminal1;
   TStop *m_Terminal2;

   ///FIND STOP
   TStop * findStop(const std::string stopName) const
   {
      TStop * it = m_Terminal1;
      while(it)
      {
         if(it->m_Name == stopName)
            return  it;
         else
            it = it->m_Next;
      }

      throw CNameException(stopName);
   }


   bool foundOnRight(TStop * fromStop, TStop * toStop) const
   {
      TStop * it = fromStop;
      while(it)
      {
         if(it == toStop)
            return true;
         else
            it = it->m_Next;
      }

      return false;
   }

   ///ADD STOP
   void addStop(const std::string stopName)
   {
      TStop * tmp = new TStop(stopName);

      /// both null
      if(! m_Terminal1 || ! m_Terminal2 )
      { m_Terminal1 = m_Terminal2 = tmp; }

      /// both same more...
      else
      {
         m_Terminal2->m_Next = tmp;
         tmp->m_Prev = m_Terminal2;
         m_Terminal2 = tmp;
      }
   }


   ///REMOVE STOP
   void removeStop (const std::string stopName)
   {
      TStop * tmp = findStop(stopName);

      ///last stop left....
      if(m_Terminal1 == m_Terminal2 && m_Terminal1 == tmp)
      {
         m_Terminal1 = m_Terminal2 = NULL;
         delete tmp;
      }

      /// first stop
      else if (m_Terminal1 == tmp)
      {
         m_Terminal1 = m_Terminal1->m_Next;
         m_Terminal1->m_Prev = NULL;
         delete tmp;
      }
      /// last stop
      else if (m_Terminal2 == tmp)
      {
         m_Terminal2 = m_Terminal2->m_Prev;
         m_Terminal2->m_Next = NULL;
         delete tmp;
      }

      ///between stop...
      else
      {
         (tmp->m_Prev)->m_Next = tmp->m_Next;
         (tmp->m_Next)->m_Prev = tmp->m_Prev;
         delete tmp;
      }

   }

public:

   ///CONSTRUCTOR
   CBusLine(std::istream & is) : m_Terminal1(NULL), m_Terminal2(NULL)
   {
      for (std::string str ;std::getline(is, str) ; )
      {
         if(str.size() )
         {
            try
            {
               findStop(str);
            }
            catch (CNameException &x)
            {
               addStop(str);
            }

         }

      }

   }

   /// DESTRUCTOR
   ~CBusLine()
   {
      while (m_Terminal1)
      {
         TStop * tmpNext = m_Terminal1->m_Next;
         delete m_Terminal1;
         m_Terminal1 = tmpNext;
      }
   }

   ///REMOVE
   inline void Remove(const std::string stopName) { removeStop(stopName); }


   TTrip Trip (const std::string & from, const std::string & to) const
   {
      TStop * fromStop =  findStop(from);
      TStop * toStop =    findStop(to);

      /// try ty find it on the right
      return TTrip(fromStop, toStop, foundOnRight(fromStop, toStop));
   }

   ///lada vagner CLASS
   friend class CTester;
};



int main ()
{
   istringstream is;
   int            l;
   is.clear ();
   is.str ("New Hampton\nLondon\nNew York\n\nPrague");
   CBusLine a(is);
   l = a . Trip ("London", "Prague").Stops(); //l = 3
   cout << a . Trip ("London", "Prague");
   cout << l <<endl << endl;

/* ------------------------------------
London
  -> New York
  -> Prague
------------------------------------ */


   l = a . Trip ("New York", "New Hampton").Stops(); //l = 3
   cout << a . Trip ("New York", "New Hampton");
   cout << l <<endl << endl;

/* ------------------------------------
New York
  -> London
  -> New Hampton
------------------------------------ */


   l = a . Trip ("London", "London").Stops(); //l = 1
   cout << a . Trip ("London", "London");
   cout << l <<endl << endl;

/* ------------------------------------
London
------------------------------------ */

   a . Remove("London");
   l = a . Trip ("New York", "New Hampton").Stops(); //l = 3
   cout << a . Trip ("New York", "New Hampton");
   cout << l <<endl << endl;

/* ------------------------------------
New York
  -> New Hampton
------------------------------------ */
   is.clear ();
   is.str ("New Hampton\nLondon\n\n\n\nLondon\nLondon\nNew York\n\nPrague");
   CBusLine b(is);
   l = b . Trip ("New Hampton", "New York").Stops(); //l = 3
   cout << b . Trip ("New Hampton", "New York");
   cout << l <<endl << endl;

/* ------------------------------------
New Hampton
  -> London
  -> London
  -> London
  -> New York
------------------------------------ */
}
