#include "Graph.h"
#include <sstream>
using namespace std;


//empty constructor
Graph::Graph() {
    //do nothing
}

Graph::Graph(vector<string> data){
    for (auto infos1 : data) {
        stringstream info2(infos1);
        vector<string> airport;
        string info;
        while (getline(info2, info, ',')){
            airport.push_back(info);
        }
        stringstream info3(airport[0]);
        int id;
        info3 >> id;
        Airport oneAirport(airport[1]);
        airports[id] = oneAirport;
    }
}

void Graph::getAirline(vector<string> data) {
    //not finish
}
string Graph::getInformation(int id) {
    auto iterator = airports.find(id);
    if(iterator == airports.end()) {
        return "no according airport found";
    } else {
        return airports[id].airportName;
    }
}