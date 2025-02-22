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
    Session(Session&& other);

    Session& operator=(Session&& other);

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
    Graph&  getGraphReference();
    // yanay add
    const Graph& getGraph() const;

    std::vector<std::vector<int>> getEdges(); // rafael add

    int getCycleCounter() const; // rafael add

    std::vector<int> getInfectedQ(); // rafael add

    std::vector<int> getNonVirusFreeVec(); // rafael add

    bool findInNonVirusFreeVec(const int &nodeInd) const ; // rafael add

    Session& operator=(const Session& session);

    void clear();

    void addVirusToVec(int nodeInd);

    void removeVirusFromVec(int nodeInd);

    void output();

private:
    void parseJson(const string &path);

    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;

    int cycleCounter = 0;
    std::vector<int> infectedQ; // rafael add

    std::vector<int> nonVirusFreeVec; // rafael add

    void print();
};

#endif
