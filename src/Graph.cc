#include "Graph.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;


//empty constructor
Graph::Graph() {
    //do nothing
}

Graph::Graph(string airportsFile, string airRoutesFile) {
    ifstream airportsLines(airportsFile);    
    string eachLine;                                    
    if(airportsLines.is_open()) {
        //skip header
        getline (airportsLines, eachLine);
        //each airport
        while (getline (airportsLines, eachLine)){
            vector<string> airport;
            string info;
            stringstream eachLine2(eachLine);
            //each feature
            //0 = Airport ID,1 = Name,2 = City,3 = Country,4 = IATA,5 = ICAO,6 = Latitude,7 = Longitude
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
            //airport new pointer
            Airport * newAirport = new Airport(id, airport[1], airport[2], airport[3], airport[4], airport[5],latitude, longitude);
            airports[id] = newAirport;
        }
        cout <<"airports finished" << endl;
    } else {
        cout <<"no such file" << endl;
    }
    size_ = airports.size();
    
   // edges with weights
   ifstream airRoutes(airRoutesFile);
    string eachRoute;
    if (airRoutes.is_open()) {
        getline(airRoutes, eachRoute);
        while (getline(airRoutes,eachRoute)) {
            vector<string> airroutes;
            string seg;
            stringstream eachLine2(eachRoute);
            while (getline(eachLine2, seg, ',')) {
                airroutes.push_back(seg);
            }
            //airroutes[3]=source airport ID airroutes[5]=destination airport ID
            if (!airroutes[3].empty() && !airroutes[5].empty()) {
                _getAirline(stoi(airroutes[3]), stoi(airroutes[5])); 
            }
        }
        cout <<"airlines finished" << endl;
    } else {
        cout <<"no such file" << endl;
    }
}

void Graph::_getAirline(int start, int end) {
    // check whether it is repeated;
    if (airports.find(start) != airports.end()) {
        for(pair<int, int> & check : airports[start]->destinations) {
            if(end == check.first) {
                check.second++;
                return;
            }
        }
        airports[start]->destinations.push_back(pair<int, int>(end,1));
    }
}

Graph::~Graph() {
    for(auto airport : airports) {
        delete airport.second;
    }
}

string Graph::getInformation(int id) {
    auto iterator = airports.find(id);
    if(iterator == airports.end()) {
        return "no according airport found";
    } else {
        for (auto pair : airports[id]->destinations) {
            cout << "target airpots: " << to_string(airports[pair.first]->uniqueID) << ", number of routes: " << to_string(pair.second) << endl;
        }
        cout << to_string(airports[id]->uniqueID) +' '+ airports[id]->cityName +' '+ 
        airports[id]->countryName +' '+ airports[id]->IATA + ' ' + 
        airports[id]->ICAO + ' ' + to_string(airports[id]->Latitude) + ' ' + to_string(airports[id]->Longitude) << endl;
        return "number of targets: " + to_string(airports[id]->destinations.size());
    }
}
