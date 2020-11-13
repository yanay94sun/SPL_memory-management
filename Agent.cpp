#include "Agent.h"

Agent::Agent() {

}

Agent::~Agent() {}



//--------------------------

ContactTracer::ContactTracer() {

}
void ContactTracer::act(Session &session) {
    Tree* bfs = g.BFSScan(session.dequeueInfected(), session); // rafael add
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
    session.enqueueInfected(nodeInd);
    for (int i = 0; i < session.getEdges().size(); ++i) {

    }

}
//
