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
    clear();
    //*cout << "I am in the destractur "  << endl;
    //*cout << "I Am node:" << this->node << endl;
    //*for(int i=0; i<children.size(); i++){
       //* delete children[i];
       //* children[i] = nullptr;

//        cout << "num of children: " << children.size() << endl;
//        cout << "I am about to delete node:" << child->node << endl;
//        cout << "\n" << endl;
//        cout << child->node << " has been deleted!" << endl;
    //*}
    //*cout << "clearing" << endl;
    //*children.clear() ; //size of children vector is now zero --- yanay


}

void Tree::clear()
{
    for (Tree* child : children)
    {
        delete child;
    }

    children.clear();
}

Tree::Tree(const Tree &other) : node(other.node) { // copy constructor -- ASK for HELP!!!
    for(auto child : other.children){
        this->addChild(child->clone());
    }
}
 Tree& Tree::operator=(const Tree& other) {
    if (this != &other){
        clear();
        for (const auto  &otherTree : other.children ){
            this->addChild(otherTree->clone());

            node = other.node;
        }
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
    else if (session.getTreeType() == Root) {
        newTree = new RootTree(rootLabel);
    }
    else if (session.getTreeType() == Cycle) {
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

//vector<Tree*> Tree::getChildren(){
//    return children;
//};


//CycleTree ------------------------------------

//CycleTree constructor --- Yanay
CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(){}



int CycleTree::traceTree() {   //yanay add ------- Hope its works
    int counter = 0;
    Tree* tempRoot = nullptr;
    vector<Tree*> tempChildVec = getChildrenVec();
    while (counter <=  currCycle && !tempChildVec.empty()){
        tempRoot = tempChildVec[0];
        tempChildVec = tempRoot->getChildrenVec();
        counter++;
    }

    return getNodeInd(*tempRoot);
}


Tree* CycleTree::clone() const {
    return new CycleTree(*this);
}

vector<Tree *> Tree::getChildrenVec() const {
    return this->children;
}

int CycleTree::getCurrCycle(){
    return currCycle;
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

int& MaxRankTree::getChildrenNumRef()  {
    int childrenSize = this->children.size();
    return childrenSize;
}
// yanay add
int MaxRankTree::getMaxRankNode() {

}

//vector<MaxRankTree*> MaxRankTree::getChildren(){
//    return children;
//}

//yanay add
//int MaxRankTree::traceTree() {
////    int tempMaxNode = node;
////    int tempMaxChildSize = children.size();
////    Tree* tempRoot = this;
////    vector<Tree*> tempChildVec = tempRoot->getChildrenVec();
////    while (tempChildVec.empty()){
////        for (int i = 0; i < tempChildVec.size(); ++i) {
////            if(tempChildVec[i]->getChildrenVec().size() > tempMaxChildSize)
////                tempMaxNode = tempChildVec[i]->getNodeInd();
////        }
////
////        tempRoot = tempChildVec[0];
////
////        counter++;
////    }
////    delete tempRoot;
////    return getNodeInd(*tempRoot); //TODO need to delete copy!! dont know where. --- yanay
//
//}

//int MaxRankTree::traceTree() {
//    int maxRankNode = this->traceTreeRec(*this, this->getChildrenNum(), 0, 0, node);
//    return maxRankNode;
//}
//
//int MaxRankTree::traceTreeRec(MaxRankTree curTree, int childrenSize, int counter, int levelTree, int retNodeInd){
//        if (counter == curTree.children.size())
//    {
//        counter = 0;
//        levelTree--;
//        return retNodeInd;
//    }
//    if(children.empty())
//        return -1;
//    if (curTree.children.size() > childrenSize)
//        retNodeInd = curTree.getNodeInd();
//
//
//    if ((traceTreeRec(reinterpret_cast<MaxRankTree &&>(curTree.children[counter]), curTree.getChildrenNum(), counter + 1, levelTree, retNodeInd)) == -1){
//        return traceTreeRec(reinterpret_cast<MaxRankTree &&>(curTree.children[counter + 1]), curTree.getChildrenNum(), counter + 1, levelTree, retNodeInd);
//    }
//    return traceTreeRec(reinterpret_cast<MaxRankTree &&>(curTree.children[counter]), curTree.getChildrenNum(), counter + 1, levelTree, retNodeInd);
//
//
//}

Tree* MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}
int MaxRankTree::traceTree() {
    int childrenSize = children.size();
    int maxRankNode = this->traceTreeRec(*this, childrenSize, node);
    return maxRankNode;
}

int MaxRankTree::traceTreeRec(MaxRankTree curTree, int &childrenSize, int retNodeInd){
    for (int i = curTree.getChildrenNum() - 1; i >= 0; --i) {
        if (curTree.getChildrenNum() >= childrenSize){
            retNodeInd = curTree.getNodeInd();
            childrenSize = curTree.getChildrenNum();
        }
        retNodeInd = traceTreeRec(reinterpret_cast<MaxRankTree &&>(*(curTree.children[i])), childrenSize, retNodeInd);
    }
    return retNodeInd;
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

