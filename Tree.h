#ifndef TREE_H_
#define TREE_H_
#include <vector>
//#include "Session.h"
using namespace std;

class Session; // ASK SOMEONE !!!!!!!

class Tree{
public:

    //*************************************** Rule Of Five ************************************************


    //Constructor
    Tree(int rootLabel);

    //Distructor
    virtual ~Tree();

    //Copy Constructor
    Tree(const Tree&);

    //Move Constructor
    Tree(Tree&& other);

    //Copy Assignment Operator
    Tree & operator=(Tree &&other);

    //move Assigment
    Tree& operator=(const Tree& tree);


    //************************************* Rule Of Five End ***************************************************





    void clear();



    void addChild(const Tree& child); // dolav says that it have to be implement , but not realy use

    void addChild(Tree* child); // rafael add -- help us in the BFS func

    //void addNeighbor(); // rafael add

    static Tree* createTree(const Session& session, int rootLabel); // CHECK!

    virtual int traceTree()=0;

    virtual Tree* clone() const = 0; // NEED to check -- think its necessary -- **maybe just here** -- rafael add

    //virtual const Tree& getChildAt(int childInd) const;  //yanay add

    virtual int getNodeInd(Tree* tree) const;  //yanay add

    virtual int getNodeInd() const;

    vector<Tree*> getChildrenVec() const;

    void sortChildrenVec(Tree *curTree);






protected:
    int node;

    vector<Tree*> children;

    void sort(vector<Tree *>::iterator iterator, vector<Tree *>::iterator iterator1);
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

    virtual int traceTreeRec(MaxRankTree curTree, int childrenSize, int retNodeInd);

    virtual Tree* clone() const; // NEED to check -- think its necessary -- rafael add

    virtual int getMaxRankNode(); //yanay add

    virtual int getChildrenNum (); //yanay add for MaxRankTree
};

//---------------------------------------------------

class RootTree: public Tree{
public:
    RootTree(int rootLabel);

    virtual int traceTree();

    virtual Tree* clone() const; // NEED to check -- think its necessary -- rafael add **** Yes its necessary for addChildren function. ****


};

#endif
