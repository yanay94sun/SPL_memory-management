#include <string>
#include <algorithm>
#include "Tree.h"
#include "Session.h" // ASK OK ?????????????
#include "Graph.h"

using namespace std;


//*************************************** Rule Of Five ************************************************


//Constructor
Tree::Tree(int rootLabel) : node(rootLabel) { // RULE OF 5 !! --- yanay add node(rootLabel) and children -- not sure
}

//Distructor
Tree::~Tree(){
    clear();
}

//Copy Constructor
Tree::Tree(const Tree &other) : node(other.node) {
    for(auto child : other.children){
        this->addChild(child->clone());
    }
}

//Copy Assignment Oprator
 Tree& Tree::operator=(const Tree& other) {
    if (this != &other){
        clear();
        for (const auto  &otherTree : other.children ){
            this->addChild(otherTree->clone());
            node = other.node;
        }
    }
     return *this;
}

void Tree::clear()
{
    for (Tree *child : children)
        delete child;
    children.clear();
}

//Move Constructor
Tree::Tree(Tree&& other) : node(other.node)
{

    if (this != &other){
        clear();
        children = move(other.children);
    }
}
//Move Assignment Oprator
Tree& Tree::operator=(Tree&& other)
{
    if (this != &other)
    {
        clear();
        children = move(other.children);
        node = other.node;
    }

    return *this;
}


//************************************* Rule Of Five End ***************************************************


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
    else if (session.getTreeType() == Root) {
        newTree = new RootTree(rootLabel);
    }
    else {
        newTree = new CycleTree(rootLabel, session.getCycleCounter());
    }
    return newTree;
}

void Tree::sortChildrenVec(Tree *curTree){ //rafael add - sorting children vecx
    sort(curTree->children.begin(), curTree->children.end());
}


int Tree::getNodeInd(Tree* tree) const {   //yanay add
    return tree->node;
}

int Tree::getNodeInd() const{
    return this->node;
};


//===================================CycleTree=======================================

//CycleTree constructor --- Yanay
CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel) , currCycle(currCycle){}



int CycleTree::traceTree() {   //yanay add ------- Hope its works
    int counter = 0;
    Tree* tempRoot = this;
    vector<Tree*> tempChildVec = getChildrenVec();
    while (counter <  this->currCycle && !tempChildVec.empty()){
        tempRoot = tempChildVec[0];
        tempChildVec = tempRoot->getChildrenVec();
        counter++;
    }
    return getNodeInd(tempRoot);
}


Tree* CycleTree::clone() const {
    return new CycleTree(*this);
}

vector<Tree *> Tree::getChildrenVec() const {
    return this->children;
}


void Tree::sort(vector<Tree *>::iterator iterator, vector<Tree *>::iterator iterator1) {

}

//===================================MaxRankTree=======================================


//MaxRankTree constructor ---- Yanay
MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}


// for MaxRankTree -- Yanay add
int MaxRankTree::getChildrenNum()  {
    return this->children.size();
}
// yanay add
int MaxRankTree::getMaxRankNode() {

}

//refael add
int MaxRankTree::traceTree() {
    int maxRankNode = this->traceTreeRec(*this, this->getChildrenNum(), node);
    return maxRankNode;
}

int MaxRankTree::traceTreeRec(MaxRankTree curTree, int childrenSize, int retNodeInd){
    for (int i = 0; i < curTree.getChildrenNum(); i++) {
        if (curTree.children.empty())
            return -1;
        if (curTree.getChildrenNum() > childrenSize){
            retNodeInd = curTree.getNodeInd();
            childrenSize = curTree.getChildrenNum();
        }
        retNodeInd = traceTreeRec(reinterpret_cast<MaxRankTree &&>(*(curTree.children[i])), curTree.getChildrenNum(), retNodeInd);
    }
    return retNodeInd;
}

Tree* MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}


//===================================RootTree=======================================

//RootTree constructor
RootTree::RootTree(int rootLabel) :Tree(rootLabel) {}


int RootTree::traceTree() {
    return node;
}

Tree* RootTree::clone() const {
    return new RootTree(*this);
}

