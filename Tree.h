#ifndef TREE_H_
#define TREE_H_
#include <vector>
//#include "Session.h"
using namespace std;

class Session; // ASK SOMEONE !!!!!!!

class Tree{
public:
    Tree(int rootLabel); // constructor

    virtual ~ Tree(); // distructor

    Tree(const Tree&); // copy constructor

    void addChild(const Tree& child); // dolav says that it have to be implement , but not realy use

    void addChild(Tree* child); // rafael add -- help us in the BFS func

    void addNeighbor(); // rafael add

    static Tree* createTree(const Session& session, int rootLabel); // CHECK!

    virtual int traceTree()=0;

    virtual Tree* clone() const = 0; // NEED to check -- think its necessary -- **maybe just here** -- rafael add

    virtual int getChildrenNum (); //yanay add for cycle tree

    virtual const Tree& getChildAt(int childInd) const;  //yanay add

    virtual int getNodeInd(Tree& tree) const;  //yanay add

    vector<Tree*> getChildrenVec() const;




protected:
    int node;

    vector<Tree*> children;
};

//---------------------------------------------------

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);

    virtual int traceTree();

    virtual Tree* clone() const; // NEED to check -- think its necessary -- rafael add






private:
    int currCycle;
};

//---------------------------------------------------

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);

    virtual int traceTree();

    virtual Tree* clone() const; // NEED to check -- think its necessary -- rafael add
};

//---------------------------------------------------

class RootTree: public Tree{
public:
    RootTree(int rootLabel);

    virtual int traceTree();

    virtual Tree* clone() const; // NEED to check -- think its necessary -- rafael add **** Yes its necessary for addChildren function. ****
};

#endif
