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

class CKnife
{
  public:
    // CKnife ( bladeLength );
};

class CClothes
{
  public:
    // CClothes ( desc );
};

class CShoes
{
  public:
    // CShoes ();
};

class CMobile
{
  public:
    // CMobile ( manufacturer, model );
};
  
class CSuitcase
{
  public:
    // CSuitcase ( w, h, d )
    // Add
    // Weight
    // Count
    // Danger
    // IdenticalContents
    // operator <<
};

class CBackpack
{
  public:
    // CBackpack ()
    // Add
    // Weight
    // Count
    // Danger
    // IdenticalContents
    // operator <<
};

class CBag
{
  public:
    // CBag ( brand )
    // Add
    // Weight
    // Count
    // Danger
    // IdenticalContents
    // operator <<
};

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
  assert ( os . str () ==
           "Suitcase 1x2x3\n"
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
  assert ( os . str () ==
           "Suitcase 1x2x3\n"
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
  assert ( os . str () ==
           "Backpack\n"
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
  assert ( os . str () ==
           "Backpack\n"
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




    ///*****************************************************************************************************************
  y . Add ( w );
  y . Add ( x );

  z . Add ( x );
  z . Add ( w );

  w . Add ( CShoes () );
  x . Add ( CKnife ( 12 ) );
  os . str ( "" );
  os << w;
  assert ( os . str () ==
           "Suitcase 1x2x3\n"
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
  assert ( os . str () ==
           "Backpack\n"
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


///********************************************************************************************************************

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

///********************************************************************************************************************

  assert ( y . Count () == 22 );
  assert ( y . Weight () == 11800 );
  assert ( y . Danger () );
  os . str ( "" );
  os << z;
  assert ( os . str () ==
           "Suitcase 3x2x1\n"
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
  assert ( !w . IdenticalContents ( x ) );
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
