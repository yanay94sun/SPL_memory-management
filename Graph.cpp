#include "Graph.h"
#include <vector>
using namespace std;



Graph::Graph(std::vector<std::vector<int>> matrix) {
    edges = matrix; // CHECK !!!! ?????????????????????????????????????????????????????
    infectedVec = std::vector<int>  (edges.size());


//    for (std::vector<int> row : edges)
//    {
//        for (int col : row)
//        {
//            std::cout << col << ",";
//        }
//        std::cout << std::endl;
//    }
}

void Graph::infectNode(int nodeInd) {
    infectedVec[nodeInd] = 1;

}

bool Graph::isInfected(int nodeInd) {
    if (infectedVec[nodeInd] == 1)
        return true;
    return false;

}


Tree*  Graph::BFSScan(int nodeInd, const Session& session){
    Tree* retTree = Tree::createTree(session, nodeInd);
//    auto retTree = currTree;
    // Visited vector to so that
    // a vertex is not visited more than once
    // Initializing the vector to false as no
    // vertex is visited at the beginning
    int vertexNum = edges.size();
    vector<bool> visited(vertexNum, false);
    vector<Tree*> q;
    q.push_back(retTree);

    // Set source as visited
    visited[nodeInd] = true;

    int vis;
    while (!q.empty()) {
        vis = q[0]->getNodeInd();
        Tree* currTree = q[0]; //TODO creat new Tree , realy move the next node ??????????????????????????????????????????????????????????????????
        // Print the current node
//        cout << vis << " "; // REMOVE !!!!!!!!!!!!!!!!!!!!!

        // For every adjacent vertex to the current vertex
        for (int i = 0; i < vertexNum; i++) {
            if (edges[vis][i] == 1 && (!visited[i])) {

                Tree* tempChild = Tree::createTree(session, i);
                //----currTree->addChild(Tree::createTree(session, i));
                currTree->addChild(tempChild);

                // Push the adjacent node to the queue
                q.push_back(tempChild);

                // Set
                visited[i] = true;
            }
        }
        currTree->sortChildrenVec(currTree); // rafael add - but think here need to send an address but impassible ??????????????????????
        q.erase(q.begin()); //dequeue ---- dont know if the data of currTree is earase too ??????????????
    }
    return retTree;
}

std::vector<std::vector<int>> Graph::getEdges() { // rafael add
    return edges;
}

std::vector<std::vector<int>>& Graph::getEdgesReference(){
    return edges;
}

std::vector<int> Graph::getInfectedVec(){
    return infectedVec;
}