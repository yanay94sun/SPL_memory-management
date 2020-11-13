#include "Agent.h"

Agent::Agent() {

}

Agent::~Agent() {}




//--------------------------

ContactTracer::ContactTracer() {

}
void ContactTracer::act(Session &session) {
    Tree* bfs =
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

}

