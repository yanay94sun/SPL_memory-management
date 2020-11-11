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
    void addAgent(const Agent& agent); // for example after virus infect other node.. need to create new instance
    void setGraph(const Graph& graph);
    
    void enqueueInfected(int);
    void setInfected(int); // Dolav suggestion
    int dequeueInfected();
    TreeType getTreeType() const;

    // yanay add
    Graph& getGraphReference();
    
private:
    std::vector<vector<int>> parseGraph(const string &path);

    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
};

#endif
