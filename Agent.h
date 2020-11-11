#ifndef AGENT_H_
#define AGENT_H_
#include <vector>
#include "Session.h"
class Agent{
public:
    Agent();
    virtual ~Agent();
    virtual Agent* clone() = 0; // dolav says this method  very necessary.. if need to implement: Agent* currAgent = otherVec[0];   Agent* newAgnet = curAgent->clone()
    virtual void act(Session& session)=0;
};

class ContactTracer: public Agent{
public:
    ContactTracer();
    virtual void act(Session& session);
};


class Virus: public Agent{
public:
    Virus(int nodeInd);
    
    virtual void act(Session& session);
private:
    const int nodeInd;
};

#endif
