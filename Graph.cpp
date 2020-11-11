#include "Graph.h"


Graph::Graph(std::vector<std::vector<int>> matrix) {
    edges = matrix;

//    for (std::vector<int> row : edges)
//    {
//        for (int col : row)
//        {
//            std::cout << col << ",";
//        }
//        std::cout << std::endl;
//    }
}

void Graph::infectNode(int nodeInd) {}
bool Graph::isInfected(int nodeInd) {return true;}
