#include "Tree.h"

using namespace std;

Tree::Tree(int rootLabel) { // RULE OF 5 !!

}
void Tree::addChild(const Tree &child) {

}

Tree * Tree::BFS(int startingNode) {


}

Tree * Tree::createTree(const Session &session, int rootLabel) {
    string type = j["tree"].get<string>();
    if (type == "R")
        treeType = Root;
    else if (type == "M")
        treeType = MaxRank;
    else if (type == "C")
        treeType = Cycle;




    // Visited vector to so that
    // a vertex is not visited more than once
    // Initializing the vector to false as no
    // vertex is visited at the beginning
    //vector<bool> visited(v/*??*/, false);
    /*vector<int> q;
    q.push_back(rootLabel);

    // Set source as visited
    visited[rootLabel] = true;

    int vis;
    while (!q.empty()) {
        vis = q[0];

        // Print the current node
        cout << vis << " ";
        q.erase(q.begin());

        // For every adjacent vertex to the current vertex
        for (int i = 0; i < v; i++) {
            if (adj[vis][i] == 1 && (!visited[i])) {

                // Push the adjacent node to the queue
                q.push_back(i);

                // Set
                visited[i] = true;
            }
        }
    }*/



}

int Tree::traceTree() {

}


