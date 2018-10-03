#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

///EXCEPTION
class CStarBaseException
{
private:
   std::string m_name;
public:
   CStarBaseException(const std::string & name) : m_name(name) {};

   friend std::ostream &operator << ( std::ostream &os, const CStarBaseException & x)
   {

      os << x.m_name << ": Not found" << std::endl;
      return os;
   }
};



///BASE
struct TStarBase
{
   std::string m_Name;
   TStarBase * m_Next;
   TStarBase(const std::string & name) : m_Name(name), m_Next(NULL) {};

};


///PATH
class Path
{
private:


   TStarBase * m_from;
   TStarBase * m_to;
   TStarBase * m_teleport;
   bool m_teleportUsed;
   int m_totalTime;


   /// COMPUTE PATH
   void computePath()
   {
      int time = 0;
      int timeWithTeleport = 3;

      TStarBase * it = m_from;

      while(it != m_to)
      {
         if(it == m_teleport)
            timeWithTeleport += time;

         time++;
         it = it->m_Next;
      }


      if(timeWithTeleport < time)
      {
         m_totalTime = timeWithTeleport;
         m_teleportUsed = true;
      }

      else
      {
         m_totalTime = time;
         m_teleportUsed = false;
      }
   }

public:

   ///CONSTRUCTOR
   Path(TStarBase * from, TStarBase * to, TStarBase * teleport) : m_from(from),
                                                                  m_to(to),
                                                                  m_teleport(teleport),
                                                                  m_teleportUsed(false),
                                                                  m_totalTime(0)
   {
      computePath();
   };


   ///OSTREAM PRINT
   friend std::ostream &operator << ( std::ostream & os, const Path & x)
   {

      TStarBase * it = x.m_from;

      while (it != x.m_to)
      {
         os << it->m_Name;
         if(it == x.m_teleport && x.m_teleportUsed)
         {
          os << "~>" ;
            break;
         }
         else
         {
            os << "->" ;
         }

         it = it->m_Next;

      }
      os << x.m_to->m_Name << std::endl;

      return os;
   }


   int StarDays() const
   {
      return m_totalTime;
   }
};


///STAR LINER
class CStarLiner
{
private:
   TStarBase * m_StarBases;
   TStarBase * m_lastBase;
   TStarBase * m_teleport;
   std::string m_teleportName;


   ///ADD BASE
   void addBase(const std::string & name)
   {
      TStarBase * tmp = new TStarBase(name);

      /// No starbases yet ...
      if(m_StarBases == NULL  || m_lastBase == NULL)
      {
         m_StarBases = m_lastBase = tmp;
         m_StarBases->m_Next = m_StarBases;
      }

      /// one or more bases...
      else
      {
         m_lastBase ->m_Next = tmp;
         tmp->m_Next = m_StarBases;
         m_lastBase = tmp;
      }
   }

   ///FIND BASE
   TStarBase * findBase(const std::string name)
   {
      if(m_StarBases == NULL)
         throw CStarBaseException(name);

      if(m_StarBases->m_Name == name)
         return  m_StarBases;

      if(m_lastBase->m_Name == name)
         return  m_lastBase;

      TStarBase * it = m_StarBases;

      while(it != m_lastBase)
      {
         if(it->m_Name == name)
            return  it;
         it = it->m_Next;
      }

      throw CStarBaseException(name);
   }


   void deleteBases()
   {
      if(m_StarBases == NULL)
         ;
      else
      {
         TStarBase * it = m_StarBases;

         while(it != m_lastBase)
         {
            TStarBase * tmp = it->m_Next;
            delete it;
            it = tmp;
         }
         delete it;
      }
   }

public:
   CStarLiner(const std::string & teleport) : m_StarBases(NULL),
                                              m_lastBase(NULL),
                                              m_teleport(NULL),
                                              m_teleportName(teleport) {};

   CStarLiner(CStarLiner &other)
   {
      m_teleportName = other.m_teleportName;
      if( other.m_StarBases == NULL)
         ;

      else
      {
         TStarBase * it = other.m_StarBases;
         while (it != other.m_lastBase)
         {
            addBase(it->m_Name);
            it = it->m_Next;
         }
         addBase(it->m_Name);
      }
   }

   CStarLiner & operator = (const CStarLiner & other)
   {
      if ( this == &other)
         return *this;
      else
      {
         deleteBases();
         m_teleportName = other.m_teleportName;
         if( other.m_StarBases == NULL)
            ;

         else
         {
            TStarBase * it = other.m_StarBases;
            while (it != other.m_lastBase)
            {
               addBase(it->m_Name);
               it = it->m_Next;
            }
            addBase(it->m_Name);
         }
      }
      return *this;
   }


   ~CStarLiner()
   {
     deleteBases();
   }


   void Add(std::istream & is)
   {
      for(std::string str; std::getline(is,str); )
      {
         if(str.size())
            addBase(str);
         if(m_lastBase->m_Name == m_teleportName)
            m_teleport = m_lastBase;
      }
   }

   Path Trip(const std::string & fromBase, const std::string & toBase)
   {
      TStarBase * from = findBase(fromBase);
      TStarBase * to =   findBase(toBase);

      return Path(from, to, m_teleport);
   }

   friend class CTester;
};


int main()
{
   istringstream is;
   int           days;
   CStarLiner a ( "Earth Spacedock" );
   is . clear ();
   is . str ( "Earth Spacedock\nFarpoint Station\nCorinth IV\nLya III\nDeep Space 9\n" );
   a . Add ( is );
   days = a . Trip ( "Farpoint Station", "Lya III" ) . StarDays (); // days = 2
   cout << a . Trip ( "Farpoint Station", "Lya III" );
   /*
   --8<----8<----8<----8<----8<----8<----8<--
   Farpoint Station
    -> Corinth IV
    -> Lya III
   --8<----8<----8<----8<----8<----8<----8<--
   */

   days = a . Trip ( "Corinth IV", "Farpoint Station" ) . StarDays (); // days = 4
   cout << a . Trip ( "Corinth IV", "Farpoint Station" );
   /*
   --8<----8<----8<----8<----8<----8<----8<--
   Corinth IV
    -> Lya III
    -> Deep Space 9
    -> Earth Spacedock
    -> Farpoint Station
   --8<----8<----8<----8<----8<----8<----8<--
   */

   days = a . Trip ( "Lya III", "Lya III" ) . StarDays (); // days = 0
   cout << a . Trip ( "Lya III", "Lya III" );
   /*
   --8<----8<----8<----8<----8<----8<----8<--
   Lya III
   --8<----8<----8<----8<----8<----8<----8<--
   */

   days = a . Trip ( "Earth Spacedock", "Lya III" ) . StarDays (); // days = 3
   cout << a . Trip ( "Earth Spacedock", "Lya III" );
   /*
   --8<----8<----8<----8<----8<----8<----8<--
   Earth Spacedock
    -> Farpoint Station
    -> Corinth IV
    -> Lya III
   --8<----8<----8<----8<----8<----8<----8<--
   */

   days = a . Trip ( "Earth Spacedock", "Deep Space 9" ) . StarDays (); // days = 3
   cout << a . Trip ( "Earth Spacedock", "Deep Space 9" );
   /*
   --8<----8<----8<----8<----8<----8<----8<--
   Earth Spacedock
    ~> Deep Space 9
   --8<----8<----8<----8<----8<----8<----8<--
   */

   is . clear ();
   is . str ( "Starbase Earhart\nEmpok Nor\n" );
   a . Add ( is );
   days = a . Trip ( "Corinth IV", "Earth Spacedock" ) . StarDays (); // days = 5
   cout << a . Trip ( "Corinth IV", "Earth Spacedock" );
   /*
   --8<----8<----8<----8<----8<----8<----8<--
   Corinth IV
    -> Lya III
    -> Deep Space 9
    -> Starbase Earhart
    -> Empok Nor
    -> Earth Spacedock
   --8<----8<----8<----8<----8<----8<----8<--
   */

   days = a . Trip ( "Empok Nor", "Starbase Earhart" ) . StarDays (); // days = 4
   cout << a . Trip ( "Empok Nor", "Starbase Earhart" );
   /*
   --8<----8<----8<----8<----8<----8<----8<--
   Empok Nor
    -> Earth Spacedock
    ~> Starbase Earhart
   --8<----8<----8<----8<----8<----8<----8<--
   */

   try { cout << a . Trip ( "Berengaria VII", "Earth Spacedock" ); }
   catch ( const CStarBaseException & e ) { cout << e; }
   /*
   --8<----8<----8<----8<----8<----8<----8<--
   Unknown star base 'Berengaria VII'
   --8<----8<----8<----8<----8<----8<----8<--
   */

   CStarLiner b ( "Terok Nor" );
   is . clear ();
   is . str ( "Earth Spacedock\nFarpoint Station\n\n\nCorinth IV\nLya III\nStarbase 375\n" );
   b . Add ( is );
   days = b . Trip ( "Farpoint Station", "Lya III" ) . StarDays (); // days = 2
   cout << b . Trip ( "Farpoint Station", "Lya III" );
   /*
   --8<----8<----8<----8<----8<----8<----8<--
   Farpoint Station
    -> Corinth IV
    -> Lya III
   --8<----8<----8<----8<----8<----8<----8<--
   */

   is . clear ();
   is . str ( "Empok Nor\nEmpok Nor\nTerok Nor" );
   b . Add ( is );
   days = b . Trip ( "Corinth IV", "Terok Nor" ) . StarDays (); // days = 5
   cout << b . Trip ( "Corinth IV", "Terok Nor" );
   /*
   --8<----8<----8<----8<----8<----8<----8<--
   Corinth IV
    -> Lya III
    -> Starbase 375
    -> Empok Nor
    -> Empok Nor
    -> Terok Nor
   --8<----8<----8<----8<----8<----8<----8<--
   */

   days = b . Trip ( "Farpoint Station", "Earth Spacedock" ) . StarDays (); // days = 7
   cout << b . Trip ( "Farpoint Station", "Earth Spacedock" );
   /*
   --8<----8<----8<----8<----8<----8<----8<--
   Farpoint Station
    -> Corinth IV
    -> Lya III
    -> Starbase 375
    -> Empok Nor
    -> Empok Nor
    -> Terok Nor
    -> Earth Spacedock
   --8<----8<----8<----8<----8<----8<----8<--
   */

   CStarLiner c ( "Starbase Allen" );
   is . clear ();
   is . str ( "Earth Spacedock\nFarpoint Station\n\n\nCorinth IV\nLya III\nStarbase 375\n" );
   c . Add ( is );
   CStarLiner d = c;
   is . clear ();
   is . str ( "Starbase Earhart\nStarbase Montgomery\nTerok Nor\nEmpok Nor\n" );
   c . Add ( is );
   is . clear ();
   is . str ( "Starbase Allen\nBerengaria VII\nEmpok Nor\n" );
   d . Add ( is );
   days = c . Trip ( "Starbase 375", "Farpoint Station" ) . StarDays (); // days = 6
   cout << c . Trip ( "Starbase 375", "Farpoint Station" );
   /*
   --8<----8<----8<----8<----8<----8<----8<--
   Starbase 375
    -> Starbase Earhart
    -> Starbase Montgomery
    -> Terok Nor
    -> Empok Nor
    -> Earth Spacedock
    -> Farpoint Station
   --8<----8<----8<----8<----8<----8<----8<--
   */

   days = d . Trip ( "Starbase 375", "Farpoint Station" ) . StarDays (); // days = 4
   cout << d . Trip ( "Starbase 375", "Farpoint Station" );
   /*
   --8<----8<----8<----8<----8<----8<----8<--
   Starbase 375
    -> Starbase Allen
    ~> Farpoint Station
   --8<----8<----8<----8<----8<----8<----8<--
   */
}