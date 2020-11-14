#include <string>
#include "Tree.h"
#include "Session.h" // ASK OK ?????????????


using namespace std;


Tree::Tree(int rootLabel) :   { // RULE OF 5 !!

}

//distructor --- yanay
Tree::~Tree(){
    for(auto & child : children){
        delete child;
    }
    children.clear() ; //size of children vector is now zero --- yanay
}

Tree::Tree(int &other) { // copy constructor -- ASK for HELP

}

void Tree::addChild(const Tree &child) { // rafael add -- dolav says that it have to be implement , but not realy use
    Tree* copy = child.clone();
    children.push_back(copy);
}

void Tree::addChild(Tree *child) {
    children.push_back(child);
}


Tree * Tree::createTree(const Session &session, int rootLabel) {
    Tree *newTree;
    if (session.getTreeType() == MaxRank) {
        newTree = new MaxRankTree(rootLabel);
    }
    if (session.getTreeType() == Root) {
        newTree = new RootTree(rootLabel);
    }
    if (session.getTreeType() == Cycle) {
        newTree = new CycleTree(rootLabel, session.getCycleCounter());
    }
    return newTree;
}

//---------------------------------------------------

CycleTree::CycleTree(int rootLabel, int currCycle): Tree(rootLabel), currCycle(currCycle) {}

