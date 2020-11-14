#include "Graph.h"



Graph::Graph(std::vector<std::vector<int>> matrix) {
    edges = matrix;
    std::vector<int> infectedVec (edges.size());


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
    Tree* currTree = Tree::createTree(session, nodeInd);

    // Visited vector to so that
    // a vertex is not visited more than once
    // Initializing the vector to false as no
    // vertex is visited at the beginning
    int vertexNum = edges.size();
    vector<bool> visited(vertexNum, false);
    vector<int> q;
    q.push_back(nodeInd);

    // Set source as visited
    visited[nodeInd] = true;

    int vis;
    while (!q.empty()) {
        vis = q[0];

        // Print the current node
        cout << vis << " "; // REMOVE !!!!!!!!!!!!!!!!!!!!!
        q.erase(q.begin()); //dequeue

        // For every adjacent vertex to the current vertex
        for (int i = 0; i < vertexNum; i++) {
            if (edges[vis][i] == 1 && (!visited[i])) {
                currTree->addChild(Tree::createTree(session, i));

                // Push the adjacent node to the queue
                q.push_back(i);

                // Set
                visited[i] = true;
            }
        }
    }
    return currTree;
}

std::vector<std::vector<int>> Graph::getEdges() { // rafael add
    return edges;
}