#include "json.hpp"
#include <iostream> // Remove!!!!!
#include "Session.h"
#include <fstream>
#include <sstream>
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
void Session::parseJson(const string &path)
{
    ifstream file(path);
    json j;
    file >> j;
    vector<vector<int>> res;

    // **** Parse graph ****
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
    g = Graph(res);

    // **** Parse tree ****
    string type = j["tree"].get<string>();
    if (type == "R")
        treeType = Root;
    else if (type == "M")
        treeType = MaxRank;
    else if (type == "C")
        treeType = Cycle;


    // **** Parse agents ****
    auto agentsJ = j["agents"];
    for (auto agent : agentsJ)
    {
       string agentType = agent[0].get<string>();
        if (agentType == "V")
            agents.push_back(new Virus(agent[1].get<int>()));
        else if (agentType == "C")
            agents.push_back(new ContactTracer());
    }
}

//not sure about it - yanay
Session::Session(const std::string &path) : g({}), treeType() {
    parseJson(path);
   // agents.push_back(new Virus(2));
    //cout << treeType << endl ;
    //std::cout << g << std::endl;
    //for(auto & agent : agents)
      //  cout << agent << endl ;
}

Session::~Session() {
    clear();
}

void Session::clear()
{
    for (Agent *agent : agents)
        delete agent;

    agents.clear();
}

//copy constructor --- need to implmant clone() in each agent.S
Session::Session(const Session& other):g(other.g), treeType(other.treeType), agents() {
    for(auto agent : other.agents){
        agents.push_back(agent->clone());
    }
}
//copy assignment oprator

Session& Session::operator=(const Session& other)
{
    if (this != &other)
    {
        clear();
        for (const auto &otherAgent : other.agents)
            agents.push_back(otherAgent->clone());

        g = Graph(other.g);
        treeType = other.treeType;
        cycleCounter = other.cycleCounter;
        infectedQ = other.infectedQ;
        nonVirusFreeVec = other.nonVirusFreeVec;
    }

    return *this;
}


// Move Constructor
Session::Session(Session&& other) : g(std::move(other.g))
{

    if (this != &other){
    clear();
    agents = std::move(other.agents);
    treeType = other.treeType;
    cycleCounter = other.cycleCounter;
    infectedQ = std::move(other.infectedQ);
    nonVirusFreeVec = std::move(other.nonVirusFreeVec);
        }
}

//move assignment oprator
Session& Session::operator=(Session&& other)
{
    if (this != &other)
    {
        clear();
        agents = std::move(other.agents);
        treeType = other.treeType;
        cycleCounter = other.cycleCounter;
        infectedQ = std::move(other.infectedQ);
        nonVirusFreeVec = std::move(other.nonVirusFreeVec);
    }

    return *this;
}


//  need to get inside session, not sure how  //Yanay
void Session::simulate(){
    int size = agents.size();
    for (int i = 0 ; i < size ; i++) {
        agents[i]->act(*this);
    }
    while (!isTermination()) {
        size = agents.size();
        for (int i = 0 ; i < size ; i++) {
            agents[i]->act(*this);
        }
        cycleCounter++;
    }

    print();
}

bool Session::isTermination() {
    for (int i = 0; i < g.getEdges().size(); i++) {
        if (g.isInfected(i)){
            // I am infected, now check if my neighbers are not infected
            for (int j = 0; j < g.getEdges().size(); j++) {
                if ((g.getEdges()[i][j] == 1) && (!g.isInfected(j)))
                    return false;
            }
        }
        // I am not infected, now check if my neighbers are infected
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
    int res = infectedQ.back();
    infectedQ.pop_back();
    return res;
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

void Session::print() {
    json j;

    ofstream os("out.json");
    stringstream ss;
    ss << g;
    cout << ss.str();
   // j = json::parse(g.getEdges());
}

//test 11111111111111111111111


