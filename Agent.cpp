#include "Agent.h"

Agent::Agent() {

}

Agent::~Agent() {}



ContactTracer::ContactTracer() {

}
void ContactTracer::act(Session &session) {}

ContactTracer::Agent* clone() const{
    return new ContactTracer(*this);
}

Virus::Agent* clone() const{
    return new Virus(*this);
}

Virus::Virus(int nodeInd) : nodeInd(nodeInd) {

}
void Virus::act(Session &session) {

}

