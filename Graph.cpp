#include "Graph.h"
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;


//empty constructor
Graph::Graph() {
    //do nothing
}

Graph::Graph(string airportsFile) {
    ifstream airportsLines(airportsFile);    
    string eachLine;                                        
    if(airportsLines) {
        while (getline (airportsLines, eachLine)){ 
            vector<string> airport;
            string info;
            stringstream eachLine2(eachLine);
            while (getline(eachLine2, info, ',')) {
                airport.push_back(info);
            }
            int id;
            stringstream newID(airport[0]);
            newID >> id;
            double latitude;
            double longitude;
            stringstream newLatitude(airport[6]);
            newLatitude >> latitude;
            stringstream newLongitude(airport[7]);
            newLongitude >> longitude;
            Airport newAirport(id, airport[1], airport[2], airport[3], airport[4], airport[5],latitude, longitude);
            airports[id] = newAirport;
        }
    } else {
        cout <<"no such file" << endl;
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
        return airports[id].airportName +' '+ airports[id].cityName +' '+ airports[id].countryName +' '+ airports[id].IATA;
    }
}
