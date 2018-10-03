#ifndef __PROGTEST__

#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <functional>
#include <CLucene/SharedHeader.h>

using namespace std;
#endif /* __PROGTEST__ */

class OrderingDoesNotExistException {};
class DuplicateMatchException {};
class NoContestantsException {};

class OrderingDoesNotExistException_circle {};




///*********************************************************************************************************************
///******************************************  SIMPLE    GRAPH  ********************************************************
///*********************************************************************************************************************

struct SimpleNode{
private:
    string m_name;
public:
    SimpleNode(const string & name) : m_name(name) {};
    const string  & Name(void) const { return m_name;}

    bool operator == (const SimpleNode & other) const { return m_name == other.m_name ; }

    bool operator != (const SimpleNode & other) const { return m_name != other.m_name ; }
};

typedef unordered_map< std::string,  std::list<SimpleNode> > TGraph;

class SimpleGraph{
public:
    TGraph m_graph;
    list<SimpleNode> emptyList;
    std::set<string> m_best;
    std::set<string> m_worst;
    size_t m_numOfCont;

    SimpleGraph(std::set<string> cont , size_t numOfCont) : m_graph(),
                                                            emptyList(),
                                                            m_best(cont),
                                                            m_worst(cont),
                                                            m_numOfCont(numOfCont)
    {
    }

    const list<SimpleNode> & expandNode(const SimpleNode & nodeToExpand) const
    {
        TGraph::const_iterator it;
        if (  (it = m_graph.find( nodeToExpand.Name()) ) == m_graph.end() )
            return emptyList;
        else
            return it->second;
    }


    bool isConnectedTo ( const SimpleNode & A,  const SimpleNode & B) const{

        for ( const auto & expanded : expandNode(A) ) {
            if (expanded == B)
                return true;
        }

        return false;
    }

    SimpleNode getFirstNode() const {
        if (m_best.size() != 1)
            throw 1;

        return  SimpleNode(* m_best.begin() ) ;
    };

    SimpleNode getLastNode() const {
        if (m_worst.size() != 1)
            throw 1;

        return  SimpleNode(* m_worst.begin() ) ;
    };
};


///*********************************************************************************************************************
///**********************************************   GRAPH  *************************************************************
///*********************************************************************************************************************
template<typename _T>
struct Node {
private:
    string m_name;
    _T m_value;

public:
    ///constructor
    Node(const string & contestant2, const _T & matchResult) : m_name(contestant2), m_value(matchResult) {};
    ///Name getter
    const string & Name()const { return m_name ; }
    ///Value getter
    const  _T  & Value()const { return m_value ; }

    friend ostream & operator << (ostream & os,const  Node<_T> & x ) {
        os << x.m_name << endl;
        return os;
    }
};

template<typename _T>
class Graph {
private:
    unordered_map<std::string, std::list<Node<_T>>> m_graph;
    std::set<string> m_Contestants;
public:
///*********************************************************************************************************************
    Graph() : m_graph() {};
///*********************************************************************************************************************
    bool addNode(const string &contest1, const string &contest2, const _T &result);
///*********************************************************************************************************************

    ///throw NoContestantsException if no contestants exists
    ///throw NoOrdereing Exist if nobody is worst  / best
    template<typename _FUNC>
    SimpleGraph * Evaluate(_FUNC && comparator) const {
        if(m_Contestants.size() == 0)
            throw NoContestantsException();

        SimpleGraph * GraphWeighted = new SimpleGraph(m_Contestants, m_Contestants.size());

        ///go through all "nodes in map"
        for( auto &node: m_graph){
            /// go through Nodes in adjecency list
            for( auto &adjecentNode : (node.second ) ) {

                /// evaluate  ( node ; adjecent Node ; Match )
                int val = comparator(adjecentNode.Value());
                std::list<SimpleNode> newList;
                /// if val == 1 Node > adjecent node ; crete edge Node ---> adjecent node
                if (val > 0) {
                    if (  ( GraphWeighted->m_graph.find( node.first) ) == GraphWeighted->m_graph.end())
                        GraphWeighted->m_graph.insert(std::make_pair(node.first, newList));
                    (GraphWeighted->m_graph.find(node.first))->second.push_back( SimpleNode(adjecentNode.Name()) ) ;
                    /// node (winer) cant be worst
                    GraphWeighted->m_worst.erase(node.first);
                    /// adjecent node (looser) cant be best
                    GraphWeighted->m_best.erase(adjecentNode.Name());
                /// if val == -1 Adjecent node > Node ; create edge adjecent node ---> node
                } else if (val < 0) {
                    if (  (GraphWeighted->m_graph.find( adjecentNode.Name() ) ) == GraphWeighted->m_graph.end())
                        GraphWeighted->m_graph.insert(std::make_pair(adjecentNode.Name(), newList));
                    (GraphWeighted->m_graph.find(adjecentNode.Name()))->second.push_back( SimpleNode(node.first) ) ;
                    /// adjecent node (winer) cant be worst
                    GraphWeighted->m_worst.erase(adjecentNode.Name());
                    /// node (looser) cant be best
                    GraphWeighted->m_best.erase(node.first);
                }
            }
        }

        if(GraphWeighted->m_worst.size() != 1 || GraphWeighted->m_best.size() != 1) {
            delete GraphWeighted;
            throw OrderingDoesNotExistException();
        }

        return GraphWeighted;
    }
///*********************************************************************************************************************
};

///*****************************************   GRAPH add node **********************************************************
///*********************************************************************************************************************
template <typename _T>
bool Graph<_T>::addNode(const string &contest1, const string &contest2, const _T &result) {
    typename unordered_map<std::string, std::list<Node<_T> > >::iterator it;

    ///contestant1 present ---> check Match validity
    if ((it = m_graph.find(contest1)) != m_graph.end())
        for (auto &a : it->second)
            if (a.Name() == contest2)
                throw DuplicateMatchException();

    ///contestant2 present ---> check Match validity
    if ((it = m_graph.find(contest2)) != m_graph.end())
        for (auto &a : it->second)
            if (a.Name() == contest1)
                throw DuplicateMatchException();

    ///add edges to conetestant1 and contestatn2
    std::list<Node<_T>> newList;

    ///create contestant1
    if ((m_graph.find(contest1)) == m_graph.end())
        m_graph.insert(std::make_pair(contest1, newList));

    m_Contestants.insert(contest1); ///ty prebytecny by se meli vyrusit zejo ?
    m_Contestants.insert(contest2);
    ///create and add nodes to both contestants
    (m_graph.find(contest1))->second.push_back( Node<_T>(contest2, result) );

    return true;
}




///*********************************************************************************************************************
///*******************************************   CONTEST  **************************************************************
///*********************************************************************************************************************

template<typename _M>
class CContest {
private:
    Graph<_M> m_graph;

public:
    CContest() : m_graph() {};

    CContest &AddMatch(const string &contestant1, const string &contestant2, const _M & result); ///AddMatch

    list<string> findPath( SimpleGraph& graphEvaluated ) const; ///FindPath
    
    template<typename _FUNC>
    bool IsOrdered(_FUNC &&comparator) const; ///IsOrdered
    
    template<typename _FUNC>
    list <string> Results(const _FUNC & comparator) const; ///Results
};


///*******************************************   CONTEST  **************************************************************
///*******************************************  Add Match   ************************************************************
template<typename _M>
CContest<_M> &CContest<_M>::AddMatch(const string &contestant1, const string &contestant2, const  _M  & result) {

    ///add node to graph ; if duplicit, addNode throws DuplicateMatch
    m_graph.addNode(contestant1, contestant2, result);
    return *this;
}


///*******************************************   CONTEST  **************************************************************
///********************************************  Find path  ************************************************************
struct hash_MyHash{
    size_t operator()(const SimpleNode & x) const {
        return std::hash<std::string>{} ( x.Name());
    }
};
template<typename _M>
list <string> CContest<_M> ::findPath(SimpleGraph &graph) const {
    unordered_set<SimpleNode, hash_MyHash> open;
    unordered_set<SimpleNode, hash_MyHash> closed;
    stack<SimpleNode> open_stack;
    stack<SimpleNode> final_stack;

    SimpleNode startNode = graph.getFirstNode();
    open_stack.push(startNode);
    open.insert(startNode);
    SimpleNode current = startNode;

    while(  ! open_stack.empty() )
    {
        ///nastav dalsiho pana na holeni
        current = open_stack.top();

       bool allExpanded = true;
       ///expand all nodes from current node
       for (auto const & expandedNode : graph.expandNode(current) ) {

           ///if node is open ---> circle !!!
           if ( open.find( expandedNode ) != open.end()  )
                throw OrderingDoesNotExistException_circle();

           ///if node is not in closed --> je to novy uzel
           if( closed.find( expandedNode ) == closed.end() ) {
               allExpanded = false;
               open_stack.push(expandedNode);
               open.insert(expandedNode);
               break;
           }
       }

        ///if all nodes of cuurend node are expanded / or no nodes left.... add it to final stack
        if(allExpanded) {
            SimpleNode x = open_stack.top();
            closed.insert(x);
            open.erase(x);
            final_stack.push(x);
            open_stack.pop();
        }

    }


    /// make path
    list<string> listVysledku;
    SimpleNode lastNode = graph.getLastNode();
    while( ! final_stack.empty()) {
        SimpleNode currentNode = final_stack.top();
        final_stack.pop();

        if(currentNode != lastNode &&  ! graph.isConnectedTo(currentNode,final_stack.top() )   )
                throw OrderingDoesNotExistException();

        listVysledku.push_back ( currentNode.Name() );
    }

    if(graph.m_numOfCont != listVysledku.size())
        throw OrderingDoesNotExistException();

    return listVysledku;
}


///*******************************************   CONTEST  **************************************************************
///******************************************  Is Ordered  *************************************************************
template<typename _M>
template <typename _FUNC>
bool CContest<_M>::IsOrdered(_FUNC &&comparator) const {
    SimpleGraph *graph_evaluated;

    ///try evaluate graph
    try { graph_evaluated = m_graph.Evaluate(comparator) ;}
    catch (NoContestantsException &e){ return true; }
    catch (OrderingDoesNotExistException &e){
        return false; }

    ///try find path
    try {findPath(*graph_evaluated); }
    catch (OrderingDoesNotExistException_circle &e) { delete graph_evaluated ; return false;}
    catch (OrderingDoesNotExistException &e) { delete graph_evaluated ; return false;}

    delete graph_evaluated;
    return true;
}

///*******************************************   CONTEST  **************************************************************
///********************************************  Results  **************************************************************
template<typename _M>
template<typename _FUNC>
list <string> CContest<_M>::Results(const _FUNC &comparator) const {
    SimpleGraph *graph_evaluated;
    list <string> resultsList;

    ///try evaluate graph
    try { graph_evaluated = m_graph.Evaluate(comparator) ;}
    catch (NoContestantsException &e){ return resultsList; }
    catch (OrderingDoesNotExistException &e){ throw e; }

    ///try find path
    try {resultsList = findPath(*graph_evaluated) ; }
    catch (OrderingDoesNotExistException_circle &e) { delete graph_evaluated ; throw OrderingDoesNotExistException() ; }
    catch (OrderingDoesNotExistException &e) { delete graph_evaluated ;throw e ;}

    delete graph_evaluated;

    return resultsList;
}




///*********************************************************************************************************************
///**********************************************  TESTING  ************************************************************
///*********************************************************************************************************************


#ifndef __PROGTEST__

struct CMatch {
public:
    CMatch(int a, int b) : m_A(a), m_B(b) {}

    int m_A;
    int m_B;
};

class HigherScoreThreshold {
public:
    HigherScoreThreshold(int diffAtLeast)
            : m_DiffAtLeast(diffAtLeast) {
    }

    int operator()(const CMatch &x) const {
        return (x.m_A > x.m_B + m_DiffAtLeast) - (x.m_B > x.m_A + m_DiffAtLeast);
    }

private:
    int m_DiffAtLeast;
};

int HigherScore(const CMatch &x) {
    return (x.m_A > x.m_B) - (x.m_B > x.m_A);
}

int main(void) {
    CContest<CMatch> x;

    x.AddMatch("C++", "Pascal", CMatch(10, 3))
            .AddMatch("C++", "Java", CMatch(8, 1))
            .AddMatch("Pascal", "Basic", CMatch(40, 0))
            .AddMatch("Java", "PHP", CMatch(6, 2))
            .AddMatch("Java", "Pascal", CMatch(7, 3))
            .AddMatch("PHP", "Basic", CMatch(10, 0));


    assert (!x.IsOrdered(HigherScore));


    try {
        list <string> res = x.Results(HigherScore);
        assert ("Exception missing!" == NULL);
    }
    catch (const OrderingDoesNotExistException &e) {
    }
    catch (...) {
        assert ("Invalid exception thrown!" == NULL);
    }

    x.AddMatch("PHP", "Pascal", CMatch(3, 6));




    assert (x.IsOrdered(HigherScore));


    try {
        list <string> res = x.Results(HigherScore);
        assert ((res == std::list < string > {"C++", "Java", "Pascal", "PHP", "Basic"}));
    }
    catch (...) {
        assert ("Unexpected exception!" == NULL);
    }


    assert (!x.IsOrdered(HigherScoreThreshold(3)));
    try {
        list <string> res = x.Results(HigherScoreThreshold(3));
        assert ("Exception missing!" == NULL);
    }
    catch (const OrderingDoesNotExistException &e) {
    }
    catch (...) {
        assert ("Invalid exception thrown!" == NULL);
    }

    assert (x.IsOrdered( [](const CMatch &x  ) {
        return (x.m_A < x.m_B) - (x.m_B < x.m_A);
    }));
    try {
        list <string> res = x.Results([](const CMatch &x) {
            return (x.m_A < x.m_B) - (x.m_B < x.m_A);
        });
        assert ((res == std::list < string > {"Basic", "PHP", "Pascal", "Java", "C++"}));
    }
    catch (...) {
        assert ("Unexpected exception!" == NULL);
    }

    CContest<bool> y;

    y.AddMatch("Python", "PHP", true)
            .AddMatch("PHP", "Perl", true)
            .AddMatch("Perl", "Bash", true)
            .AddMatch("Bash", "JavaScript", true)
            .AddMatch("JavaScript", "VBScript", true);

    assert (y.IsOrdered([](bool v) { return v ? 10 : -10; }));



    try {
        list <string> res = y.Results([](bool v) {
            return v ? 10 : -10;
        });
        assert ((res == std::list < string > {"Python", "PHP", "Perl", "Bash", "JavaScript", "VBScript"}));
    }
    catch (...) {
        assert ("Unexpected exception!" == NULL);
    }

    y.AddMatch("PHP", "JavaScript", false);
    assert (!y.IsOrdered([](bool v) {
        return v ? 10 : -10;
    }));
    try {
        list <string> res = y.Results([](bool v) {
            return v ? 10 : -10;
        });
        assert ("Exception missing!" == NULL);
    }
    catch (const OrderingDoesNotExistException &e) {
    }
    catch (...) {
        assert ("Invalid exception thrown!" == NULL);
    }

    try {
        y.AddMatch("PHP", "JavaScript", false);
        assert ("Exception missing!" == NULL);
    }
    catch (const DuplicateMatchException &e) {
    }
    catch (...) {
        assert ("Invalid exception thrown!" == NULL);
    }

    try {
        y.AddMatch("JavaScript", "PHP", true);
        assert ("Exception missing!" == NULL);
    }
    catch (const DuplicateMatchException &e) {
    }
    catch (...) {
        assert ("Invalid exception thrown!" == NULL);
    }
    return 0;
}

#endif /* __PROGTEST__ */
