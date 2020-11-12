#include "Agent.h"

Agent::Agent() {

}

Agent::~Agent() {}






ContactTracer::ContactTracer() {

}
void ContactTracer::act(Session &session) {}

Agent* ContactTracer::clone() const{ // need to explain yany something here
    return new ContactTracer(*this);
}





Agent* Virus::clone() const{// need to explain yany something here
    return new Virus(*this);
}

Virus::Virus(int nodeInd) : nodeInd(nodeInd) {

}
void Virus::act(Session &session) {

}

