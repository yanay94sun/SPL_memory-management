#include "Agent.h"

Agent::Agent() {

}

Agent::~Agent() {}



//--------------------------

ContactTracer::ContactTracer() {

}
void ContactTracer::act(Session &session) {
    Tree* bfs = session.getGraphReference().BFSScan(session.dequeueInfected(), session); // rafael add
}

Agent* ContactTracer::clone() const{
    return new ContactTracer(*this);
}


//-------------------


Agent* Virus::clone() const{
    return new Virus(*this);
}

Virus::Virus(int nodeInd) : nodeInd(nodeInd) {


}
void Virus::act(Session &session) {
//    bool flag = true;
//    for (int i = 0; i < session.getInfectedQ().size(); ++i) {
//        if (session.getInfectedQ()[i] == nodeInd)
//            flag = false;
//    }
//    if (flag)
//        session.enqueueInfected(nodeInd);

    session.getGraphReference().infectNode(nodeInd);
    session.enqueueInfected(nodeInd);
    for (int i = 0; i < session.getEdges().size(); ++i) {

        if (session.findInNonVirusFreeVec(nodeInd))
            continue;
        else if(session.getEdges()[nodeInd][i] == 0)
            continue;
        else{

            auto newVirus = this->clone();
            session.addAgent(newVirus);
            break;
        }


    }

}
//
