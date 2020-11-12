#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <iostream> // FIXME: REMOVE IT
class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);


    //dolav did it like that ------- yanay
    Tree* BFSSCAN(int nodeInd, const Session& session);


    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);

    friend std::ostream& operator<<(std::ostream &os, const Graph &graph);
private:
    std::vector<std::vector<int>> edges;
};

#endif
