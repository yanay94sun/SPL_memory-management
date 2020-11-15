#include "Agent.h"
#include "Tree.h"


Agent::Agent() {

}

Agent::~Agent() {}  // need for def distructor for no warnings



//--------------------------

ContactTracer::ContactTracer() {

}
void ContactTracer::act(Session &session) {
    Tree* bfs = session.getGraphReference().BFSScan(session.dequeueInfected(), session); // rafael add
    int infectedNodeInd = bfs->traceTree();
    for (int i = 0; i < session.getEdges().size(); ++i){
        session.getGraphReference().getEdgesReference()[infectedNodeInd][i] = 0;
        session.getGraphReference().getEdgesReference()[i][infectedNodeInd] = 0;
    }
    delete (bfs);// CHECK if delete here or in the Tree ????????????????????????????????????????????????????????????????
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

        if (session.findInNonVirusFreeVec(nodeInd) || session.getEdges()[nodeInd][i] == 0)
            continue;
//        else if(session.getEdges()[nodeInd][i] == 0)
//            continue;
//            auto newVirus = this->clone();
        session.addAgent(Virus(i)); //???????????????????????????????????????????????????????????????????



    }

}
//
