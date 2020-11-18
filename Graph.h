#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <iostream> // FIXME: REMOVE IT
//#include "Session.h"
class Session; //??????????????????????????????????????????
#include "Tree.h"
using namespace std;

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);


    //dolav did it like that ------- yanay
    Tree* BFSScan(int nodeInd, const Session& session);


    void infectNode(int nodeInd);

    bool isInfected(int nodeInd);

    friend std::ostream& operator<<(std::ostream &os, const Graph &graph); // avital func

    vector<vector<int>> getEdges(); // rafael add

    vector<vector<int>>& getEdgesReference();

    vector<int> getInfectedVec();

private:
    vector<vector<int>> edges;

    vector<int> infectedVec;
};

#endif
