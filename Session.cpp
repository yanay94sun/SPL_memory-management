#include "json.hpp"
#include <iostream> // Remove!!!!!
#include "Session.h"
#include <fstream>
#include "Agent.h"

using json = nlohmann::json;
using namespace std;

std::ostream& operator<<(std::ostream &os, const Graph &graph)
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


vector<vector<int>> Session::parseGraph(const std::string &path)
{
    std::ifstream file(path);
    json j;
    file >> j;
    vector<vector<int>> res;

    auto graph = j["graph"];
    for (size_t i = 0; i < graph.size(); i++)
    {
        auto row = graph[i];
        res.push_back(std::vector<int>());
        for (size_t j = 0; j < row.size(); j++)
        {
            res[i].push_back(row[j].get<int>());
        }
    }

    string type = j["tree"].get<string>();
    if (type == "R")
        treeType = Root;
    else if (type == "M")
        treeType = MaxRank;
    else if (type == "C")
        treeType = Cycle;

    auto agentsJ = j["agents"];
    for (size_t i = 0; i < agentsJ.size(); i++)
    {
        auto agent = agentsJ[i];
        for (size_t j = 0; j < agent.size(); j++)
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


Session::Session(const std::string &path) : g(parseGraph(path)) {
    std::cout << g << std::endl;
}

Session::~Session() {
    for (Agent *agent : agents)
        delete agent;
}

void Session::addAgent(const Agent& agent) {}
void Session::setGraph(const Graph& graph) {}

void Session::enqueueInfected(int) {}
int Session::dequeueInfected() {return 0;}
TreeType Session::getTreeType() const {
    return Cycle;
}
// 1 2 3 4 5 6 7 8