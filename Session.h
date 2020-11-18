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

    //*************************************** Rule Of Five ************************************************

    //Constructor
    Session(const string& path);

    virtual ~Session();

    //Copy Constructor
    Session(const Session& other);

    //Move Constructor Operator
    Session(Session&& other);

    //Move Assigment Operator
    Session& operator=(Session&& other);

    //Copy Assigment
    Session& operator=(const Session& session);


    //************************************* Rule Of Five End ***************************************************




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

    void addVirusToVec(int nodeInd);

    void removeVirusFromVec(int nodeInd);

    void clear();


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
