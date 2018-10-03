#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <algorithm>
#include <memory>
#include <bits/unordered_map.h>

using namespace std;

struct CCoord
{
    CCoord   ( int x = 0, int y = 0 ) { m_X = x; m_Y = y; }
    int   m_X;
    int   m_Y;
};
#endif /* __PROGTEST__ */


///*********************************************************************************************************************
///**************************************************  SHAPE  **********************************************************
///*********************************************************************************************************************

struct CCoordinates{
    CCoordinates(size_t cnt,const CCoord * v );
    CCoordinates(vector<CCoord> v );
    vector<CCoord> m_vect;
};

struct CBBox{
    CBBox(vector<CCoord> coords) :

            m_left(coords[0].m_X ,coords[0].m_Y),
            m_bottom(coords[1].m_X ,coords[1].m_Y),
            m_right(coords[2].m_X ,coords[2].m_Y),
            m_top(coords[3].m_X ,coords[3].m_Y)
    {};

    CCoord m_left;
    CCoord m_bottom;
    CCoord m_right;
    CCoord m_top;

    bool Intersect(const CCoord & coord) const //TODO
    {
     return true;
    }
    bool Intersect(const CCoordinates & coordinates) const //TODO
    {
        return true;

    }
};
///*********************************************************************************************************************


///*********************************************************************************************************************

class CShape {
protected:
    int m_ID; ///ID
    CCoordinates m_coordinates; ///COORDINATES
    CBBox m_boundingBox; ///BOUNDUNG BOX
    virtual vector<CCoord> CalculateBoundingBox(void) const = 0; ///CALCULATE BOUNDING BOX

public:
    int GetIt(void) const { return m_ID; } ///RETURN ID

    bool IntersectBBox( const CCoord & coord) const/// POINT X AABB INTERSECTION
    {
        return m_boundingBox.Intersect(coord);
    }

    bool IntersectBBox( const CCoordinates & coordinates) const/// RECTANGLE X AABB INTERSECTION
    {
        return m_boundingBox.Intersect(coordinates);
    }

    virtual bool IntersectShape (const CCoord & coord) const = 0; /// POINT X SHAPE INTERSECTION
};




///*********************************************************************************************************************
///*************************************************  RECTANGE  ********************************************************
///*********************************************************************************************************************
class CRectangle : public CShape {
public:
    CRectangle(int ID,                                                      ///CONSTRUCTOR
               int x1, int y1,
               int x2, int y2) :
                m_ID(ID),
                m_coordinates(CalculateCoordinates(x1,y1,x2,y2)),
                m_boundingBox(CalculateBoundingBox()) {}

    bool IntersectShape(const CCoord & coord) const override                /// POINT X SHAPE INTERSECTION
    {
        return IntersectBBox(coord);
    };

private:
    vector<CCoord> CalculateCoordinates(int x1, int y1, int x2, int y2)     ////COORDINATE CALCULATION
    {
        vector<CCoord> vect;

        if( x1 < x2 && y1 < y2) { ///then it is left down and up right coordinate
            vect.push_back(CCoord(x1,y1));
            vect.push_back(CCoord(x2,y1));
            vect.push_back(CCoord(x2,y2));
            vect.push_back(CCoord(x1,y2));
        }

        else if( x2 < x1 && y2 < y1) { /// swapped - then it is left down and up right coordinate
            vect.push_back(CCoord(x2,y2));
            vect.push_back(CCoord(x1,y2));
            vect.push_back(CCoord(x1,y1));
            vect.push_back(CCoord(x2,y1));
        }

        else if (x1 > x2 && y1 < y2 ) { ///then it is right down and left right coordinate
            vect.push_back(CCoord(x2,y1));
            vect.push_back(CCoord(x1,y1));
            vect.push_back(CCoord(x1,y2));
            vect.push_back(CCoord(x2,y2));
        }

        else {  ///swapped - then it is right down and left right coordinate
            vect.push_back(CCoord(x1,y2));
            vect.push_back(CCoord(x2,y2));
            vect.push_back(CCoord(x2,y1));
            vect.push_back(CCoord(x1,y1));
        }

        return vect;
    }

    vector<CCoord> CalculateBoundingBox(void) const override                ///BOUNDING BOX CALCULATION
    {
        return m_coordinates.m_vect;
    }

};
///*********************************************************************************************************************
///**************************************************  CIRCLE  *********************************************************
///*********************************************************************************************************************

class CCircle : public CShape{

public:
    CCircle(int ID, int x, int y, int r);
/// dalsi Vase implementace
};
///*********************************************************************************************************************
///**************************************************  POLYGON  ********************************************************
///*********************************************************************************************************************

class CPolygon : public CShape{

public:
    CPolygon(int ID, int cnt, const CCoord *v);
/// dalsi Vase implementace
};

///*************************************************  TRIANGLE  ********************************************************
///*********************************************************************************************************************

class CTriangle : public CShape{

public:
    CTriangle(int ID, CCoord a, CCoord b, CCoord c);
/// dalsi Vase implementace
};

///*********************************************************************************************************************
///**********************************************   SCREEN   ***********************************************************
///*********************************************************************************************************************

class CScreen {
private:

    unordered_map<int, unique_ptr<CShape> > m_shapes;
public:
    CScreen(){}; /// CONSTRUCTOR
    ~CScreen(){}; /// DESTRUCTOR

    void Optimize(void); /// OPTIMIZE

    void Test(int x, int y, int &len, int *&list) const; /// TEST


    void Add( const CRectangle & rectangle) {
        m_shapes.insert(make_pair(rectangle.GetIt(), unique_ptr( new CRectangle(rectangle) ) ));
    }           ///ADD RECTANGLE
    void Add( const CCircle & circle)    {
        m_shapes.insert(make_pair(circle.GetIt(), unique_ptr( new CCircle(circle) ) ));
    }              ///ADD CIRCLE
    void Add( const CTriangle & triangle)    {
        m_shapes.insert(make_pair(triangle.GetIt(), unique_ptr( new CTriangle(triangle) ) ));
    }          ///ADD TRIANGLE
    void Add( const CPolygon & polygon)    {
        m_shapes.insert(make_pair(polygon.GetIt(), unique_ptr( new CPolygon(polygon) ) ));
    }            ///ADD POLYGON

};

int main() {
    int   * res, resLen;
    CScreen  S0;
    S0 . Add ( CRectangle ( 1, 10, 20, 30, 40 ) );
    S0 . Add ( CRectangle ( 2, 20, 10, 40, 30 ) );
    S0 . Add ( CTriangle ( 3, CCoord ( 10, 20 ), CCoord ( 20, 10 ), CCoord ( 30, 30 ) ) );
    S0 . Optimize();
    S0 . Test ( 0, 0, resLen, res );
    //// resLen = 0, res = [ ]
    delete [] res;
    S0 . Test ( 21, 21, resLen, res );
    //// resLen = 3, res = [ 1 2 3 ]
    delete [] res;
    S0 . Test ( 16, 17, resLen, res );
    //// resLen = 1, res = [ 3 ]
    delete [] res;
    S0 . Test ( 30, 22, resLen, res );
    //// resLen = 2, res = [ 1 2 ]
    delete [] res;
    S0 . Test ( 35, 25, resLen, res );
    //// resLen = 1, res = [ 2 ]
    delete [] res;

    CScreen  S1;
    S1 . Add ( CCircle ( 1, 10, 10, 15 ) );
    S1 . Add ( CCircle ( 2, 30, 10, 15 ) );
    S1 . Add ( CCircle ( 3, 20, 20, 15 ) );
    S1 . Optimize();
    S1 . Test ( 0, 0, resLen, res );
    //// resLen = 1, res = [ 1 ]
    delete [] res;
    S1 . Test ( 15, 15, resLen, res );
    //// resLen = 2, res = [ 1 3 ]
    delete [] res;
    S1 . Test ( 20, 11, resLen, res );
    //// resLen = 3, res = [ 1 2 3 ]
    delete [] res;
    S1 . Test ( 32, 8, resLen, res );
    //// resLen = 1, res = [ 2 ]
    delete [] res;

    CScreen  S2;
    CCoord  vertex1[4] = { CCoord ( 10, 0 ), CCoord ( 20, 20 ), CCoord ( 30, 20 ), CCoord ( 40, 0 ) };
    S2 . Add ( CPolygon ( 1, 4, vertex1 ) );
    CCoord  vertex2[5] = { CCoord ( 20, 10 ), CCoord ( 10, 20 ), CCoord ( 25, 30 ), CCoord ( 40, 20 ), CCoord ( 30, 10 ) };
    S2 . Add ( CPolygon ( 2, 5, vertex2 ) );
    S2 . Optimize();
    S2 . Test ( 25, 15, resLen, res );
    //// resLen = 2, res = [ 1 2 ]
    delete [] res;
    S2 . Test ( 25, 25, resLen, res );
    //// resLen = 1, res = [ 2 ]
    delete [] res;
    S2 . Test ( 15, 3, resLen, res );
    //// resLen = 1, res = [ 1 ]
    delete [] res;
    S2 . Test ( 11, 10, resLen, res );
    //// resLen = 0, res = [ ]
    delete [] res;
}