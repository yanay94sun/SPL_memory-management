#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"


class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const std::string& path);
    virtual ~Session();
    
    void simulate();
    void addAgent(const Agent& agent); // for example after virus infect other node.. need to create new instance
    void setGraph(const Graph& graph);
    
    void enqueueInfected(int);
    void setInfected(int); // Dolav suggestion
    int dequeueInfected();
    TreeType getTreeType() const;
    
private:
    std::vector<std::vector<int>> parseGraph(const std::string &path);

    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
};

#endif
