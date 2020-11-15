#include "json.hpp"
#include <iostream> // Remove!!!!!
#include "Session.h"
#include <fstream>
#include "Agent.h"

using json = nlohmann::json;
using namespace std;

// aviital func
ostream& operator<<(ostream &os, const Graph &graph)
{
    for (std::vector<int> row : graph.edges)
    {
        for (int col : row)
        {
            os << col << ",";
        }
        os << std::endl;
    }
    return os;
}

// aviital func
vector<vector<int>> Session::parseGraph(const string &path)
{
    ifstream file(path);
    json j;
    file >> j;
    vector<vector<int>> res;

    auto graph = j["graph"];
    for (size_t i = 0; i < graph.size(); i++)
    {
        auto row = graph[i];
        res.push_back(std::vector<int>());
        for (auto & k : row)
        {
            res[i].push_back(k.get<int>());
        }
    }
    string type = j["tree"].get<string>();
    if (type == "R")
        treeType = Root;
    else if (type == "M")
        treeType = MaxRank;
    else if (type == "C")
        treeType = Cycle;


// avital func
    auto agentsJ = j["agents"];
    for (auto agent : agentsJ)
    {
        for (size_t z = 0; z < agent.size(); z++)
        {
           string agentType = agent[0].get<string>();
            if (agentType == "V")
                agents.push_back(new Virus(agent[1].get<int>()));
            else if (agentType == "C")
                agents.push_back(new ContactTracer());
        }
    }

    return res;
}

//not sure about it - yanay
Session::Session(const std::string &path) : g(parseGraph(path)), treeType(), agents() {
    std::cout << g << std::endl;
}

Session::~Session() {
    for (Agent *agent : agents)
        delete agent;
}

//copy constructor --- need to implmant clone() in each agent.S
Session::Session(const Session& other):g(other.g), treeType(other.treeType), agents() {
    for(int i=0; i < other.agents.size(); i++){
        agents.push_back(other.agents[i]->clone());
    }
}

// Move Constructor
//Session::Session(Session&& other) : g(other.g), treeType(other.treeType), agents() // TODO need to get inside session, not sure how  //Yanay
//{
//    other.g  = 0;
//    other.treeType = 0;
//    other.agents = nullptr;
//}

// TODO need to get inside session, not sure how  //Yanay
void Session::simulate(){
    while (!isTermination()) {
        int size = agents.size();
        for (auto &elem:agents) {
            elem->act(*this);
        }
        cycleCounter++;
    }
}

bool Session::isTermination() {
    for (int i = 0; i < g.getEdges().size(); i++) {
        if (g.isInfected(i)){
            for (int j = 0; j < g.getEdges().size(); j++) {
                if (g.getEdges()[i][j] == 1 && !g.isInfected(j))
                    return false;
            }
        }
        else{
            for (int k = 0; k < g.getEdges().size(); k++) {
                if (g.getEdges()[i][k] == 1 && g.isInfected(k))
                    return false;

            }
        }
    }
    return true;
}

void Session::addAgent(const Agent& agent) {
    agents.push_back(agent.clone()); //TODO need to delete copy!!! dont know where. --- yanay
}

void Session::setGraph(const Graph& graph) {
    g = graph;
}


//yanay add
Graph& Session::getGraphReference(){
    return g;
}
const Graph& Session::getGraph() const {
    return g;
}


void Session::enqueueInfected(int node) { // rafael add
    infectedQ.push_back(node);
}

int Session::dequeueInfected() { // rafael add
    infectedQ.pop_back();
}

TreeType Session::getTreeType() const {
    return treeType;
}

std::vector<std::vector<int>> Session::getEdges() { // rafael add
    return g.getEdges();
}

int Session::getCycleCounter() const {
    return cycleCounter;
}

std::vector<int> Session::getInfectedQ() { // rafael add
    return infectedQ;
}

std::vector<int> Session::getNonVirusFreeVec(){
    return nonVirusFreeVec;
}

bool Session::findInNonVirusFreeVec(const int &nodeInd) const {
    bool flag = false;
    for (int i : nonVirusFreeVec) {
        if (i == nodeInd)
            flag = true;
    }
    return flag;
}


