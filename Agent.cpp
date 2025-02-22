#include "Agent.h"
#include "Tree.h"


Agent::Agent() = default;

Agent::~Agent() = default;



//*************************************** ContactTracer ************************************************

ContactTracer::ContactTracer() = default;


void ContactTracer::act(Session &session) {
    if(session.getInfectedQ().empty())
        return;
    Tree* bfs = session.getGraphReference().BFSScan(session.dequeueInfected(), session); // rafael add
    int infectedNodeInd = bfs->traceTree();
    cout << "my line should be zero " << infectedNodeInd << endl;
    delete bfs;
    for (int i = 0; i < session.getEdges().size(); i++){
        session.getGraphReference().getEdgesReference()[infectedNodeInd][i] = 0;
        session.getGraphReference().getEdgesReference()[i][infectedNodeInd] = 0;
    }
}

Agent* ContactTracer::clone() const{
    return new ContactTracer(*this);
}


//*************************************** Virus ************************************************


Agent* Virus::clone() const{
    return new Virus(*this);
}

Virus::Virus(int nodeInd) : nodeInd(nodeInd) {
}


void Virus::act(Session &session) {
    if (!session.getGraphReference().isInfected(nodeInd)) {
        session.getGraphReference().infectNode(nodeInd);
        session.removeVirusFromVec(nodeInd);
        session.enqueueInfected(nodeInd);
    }
    for (int i = 0; i < session.getEdges().size(); i++) {
        if (session.findInNonVirusFreeVec(i) || session.getEdges()[nodeInd][i] == 0 || session.getGraphReference().isInfected(i))
            continue;
//        else if(session.getEdges()[nodeInd][i] == 0)
//            continue;
//            auto newVirus = this->clone();
        session.addAgent(Virus(i)); //???????????????????????????????????????????????????????????????????
        session.addVirusToVec(i);
        return; //not sure
    }

}

