#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"
#include <queue>
using namespace std;

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const string& path);

    virtual ~Session();

    //yanay copy constructor
    Session(const Session& other);
    
    void simulate();

    bool isTermination();

    void addAgent(const Agent& agent); // for example after virus infect other node.. need to create new instance

    void setGraph(const Graph& graph);
//    Graph getGraph(); // rafael did
    
    void enqueueInfected(int); // rafael add

    void setInfected(int); // Dolav suggestion

    int dequeueInfected(); // rafael add

    TreeType getTreeType() const;

    // yanay add
    Graph& getGraphReference();
    // yanay add
    const Graph& getGraph() const;

    std::vector<std::vector<int>> getEdges(); // rafael add

    int getCycleCounter() const; // rafael add

    std::vector<int> getInfectedQ(); // rafael add

    std::vector<int> getNonVirusFreeVec(); // rafael add

    bool findInNonVirusFreeVec(const int &nodeInd) const ; // rafael add



private:
    std::vector<vector<int>> parseGraph(const string &path);

    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;

    int cycleCounter; // rafael add
    std::vector<int> infectedQ; // rafael add

    std::vector<int> nonVirusFreeVec; // rafael add

};

#endif
