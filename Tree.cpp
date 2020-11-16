#include <string>
#include <algorithm>
#include "Tree.h"
#include "Session.h" // ASK OK ?????????????
#include "Graph.h"

using namespace std;

//constructor -- yanay
Tree::Tree(int rootLabel) : node(rootLabel) { // RULE OF 5 !! --- yanay add node(rootLabel) and children -- not sure
}

//distructor --- yanay
Tree::~Tree(){
    for(auto & child : children){
        delete child;
    }
    children.clear() ; //size of children vector is now zero --- yanay
}

Tree::Tree(const Tree &other) : node(other.node) { // copy constructor -- ASK for HELP!!!
    for(auto child : other.children){
        this->addChild(child->clone());
    }
}

void Tree::addChild(const Tree &child) { // rafael add -- dolav says that it have to be implement , but not realy use
    Tree* copy = child.clone();
    children.push_back(copy);
    //TODO need to delete copy!!!(by dolav) dont know where. --- yanay
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

void Tree::sortChildrenVec(Tree *curTree){ //rafael add - sorting children vecx
    sort(curTree->children.begin(), curTree->children.end());
}



//const Tree &Tree::getChildAt(int childInd) const {
//    return *this->children[childInd];    // yanay add
//}


int Tree::getNodeInd(Tree& tree) const {   //yanay add
    return this->node;
}

int Tree::getNodeInd() const{
    return this->node;
};


//CycleTree ------------------------------------

//CycleTree constructor --- Yanay
CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {}

int CycleTree::traceTree() {   //yanay add ------- Hope its works
    int counter = 0;
    Tree* tempRoot = this;
    vector<Tree*> tempChildVec = tempRoot->getChildrenVec();
    while (counter <= currCycle && !tempChildVec.empty()){
        tempRoot = tempChildVec[0];
        tempChildVec = tempRoot->getChildrenVec();
        counter++;
    }
    delete tempRoot;
    return getNodeInd(*tempRoot); //TODO need to delete copy!! dont know where. --- yanay
}


Tree* CycleTree::clone() const {
    return new CycleTree(*this);
}

vector<Tree *> Tree::getChildrenVec() const {
    return this->children;
}

void Tree::sort(vector<Tree *>::iterator iterator, vector<Tree *>::iterator iterator1) {

}





//MaxRankTree --------------------------------


//MaxRankTRee constructor ---- Yanay
MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}


// for MaxRankTree -- Yanay add
int MaxRankTree::getChildrenNum()  {
    return this->children.size();
}
// yanay add
int MaxRankTree::getMaxRankNode() {

}

//yanay add
int MaxRankTree::traceTree() {

}

Tree* MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}







//rootTree -------------------------------------

//RootTree constructor
RootTree::RootTree(int rootLabel) :Tree(rootLabel) {}

//yanay add
int RootTree::traceTree() {
    return node;
}
// yanay add
Tree* RootTree::clone() const {
    return new RootTree(*this);
}

