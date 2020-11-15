#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <iostream> // FIXME: REMOVE IT
//#include "Session.h"
class Session;
#include "Tree.h"

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);


    //dolav did it like that ------- yanay
    Tree* BFSScan(int nodeInd, const Session& session);


    void infectNode(int nodeInd);

    bool isInfected(int nodeInd);

    friend std::ostream& operator<<(std::ostream &os, const Graph &graph); // avital func

    std::vector<std::vector<int>> getEdges(); // rafael add

    std::vector<std::vector<int>>& getEdgesReference();

private:
    std::vector<std::vector<int>> edges;

    std::vector<int> infectedVec;
};

#endif
