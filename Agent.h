#ifndef AGENT_H_
#define AGENT_H_
#include <vector>
#include "Session.h"
#include "Graph.h" // rafel add


class Agent{
public:
    Agent();
    virtual ~Agent();  //need defult Distruct, for no warnning
    //virtual int getNodeInt();
    virtual Agent* clone() const = 0; // dolav says this method  very necessary.. if need to implement: Agent* currAgent = otherVec[0];   Agent* newAgnet = curAgent->clone()
    virtual void act(Session& session)=0;
    //need to start like this: ||||  Tree* bfs = graph.BFSSCan(infected, session); ||||    ------------------- yanay

//protected: // rafael add ?????
//    Graph g; // rafael add
};

class ContactTracer: public Agent{
public:
    ContactTracer();

    virtual Agent* clone() const; //need by dolav
    virtual void act(Session& session);
};


class Virus: public Agent{
public:
    Virus(int nodeInd);

    virtual Agent* clone() const; //need by dolav
    virtual void act(Session& session);

    int statusInt; // rafael add - 0 if just added and need to wait for the next round. 1 if ready to act
private:
    const int nodeInd;
};

#endif
