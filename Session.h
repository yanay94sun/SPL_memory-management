#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"
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
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    
private:
    std::vector<vector<int>> parseGraph(const string &path);

    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
};

#endif
