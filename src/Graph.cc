#include "Graph.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <stack>
#include "math.h"
#define pi 3.1415926535897932384626433832795
#define EARTH_RADIUS 6378.137
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
    if (airports.find(start) != airports.end() && airports.find(end) != airports.end()) {
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
        // for (auto pair : airports[id]->destinations) {
        //     cout << "target airpots: " << airports[pair.first]->airportName << ", number of routes: " << to_string(pair.second) << endl;
        // }
        cout << airports[id]->airportName +' '+ airports[id]->cityName +' '+ 
        airports[id]->countryName +' '+ airports[id]->IATA + ' ' + 
        airports[id]->ICAO + ' ' + to_string(airports[id]->Latitude) + ' ' + to_string(airports[id]->Longitude) << endl;
        return "number of targets: " + to_string(airports[id]->destinations.size());
    }
}

void Graph::Dijkstra(int start1, int end1) {
    //need to check the airports exist or segmentfault
    
    vector<Airport *> outcome; 
    stack<Airport *> dfs;
    _setInitial();
    Airport * start = airports[start1];
    start->distance = 0;
    start->LastNode = -1;
    dfs.push(start);
    while (!dfs.empty()) {
        Airport * airport = dfs.top();
        dfs.pop();
        if(airport->isTravel) {
            continue;
        }
        airport->isTravel = true;
        vector<Airport *> sortAirport;
        for(auto target : airport -> destinations) {
            Airport * targetPort = airports[target.first];
            if(!targetPort->isTravel) {
                double curDistance = _findDistance(airport->uniqueID, target.first) + airport->distance;
                if (targetPort->distance == -1 || targetPort->distance > curDistance) {
                    targetPort->distance = curDistance;
                    targetPort->LastNode = airport->uniqueID;
                    unsigned long i = 0;
                    for(; i < sortAirport.size(); i++) {
                        Airport * compare = sortAirport[i];
                        if(compare->distance > curDistance) {
                            break;
                        }
                    }
                    sortAirport.insert(sortAirport.begin() + i, targetPort);
                }
            }
        }
        for(int i = sortAirport.size() - 1; i >= 0; i--) {
            dfs.push(sortAirport[i]);
        }
    }
    
    Airport * end = airports[end1];
    if(end->distance == -1) {
        cout << "no connection between two airports" << endl;
    } else {
        Airport * curAirport = end;
        while (curAirport->LastNode != -1) {
            outcome.push_back(curAirport);
            curAirport = airports[curAirport->LastNode];
        }
        cout << "start" << endl;
        getInformation(start1);
        for(int i = outcome.size() - 1; i >= 0; i--) {
            getInformation(outcome[i]->uniqueID);
        }
    }
}
void Graph::_setInitial() {
    for(auto airport : airports) {
         airport.second->distance = -1;
         airport.second->LastNode = 0;
         airport.second->isTravel = false;
    }
}

double Graph::_findDistance(int a, int b) {
    Airport * start = airports[a];
    Airport * end = airports[b];
    return _fakeDistance(start->Latitude, start->Longitude, end->Latitude, end->Longitude);
}

double Graph::_rad(double d) {
    return d * pi /180.0;
}
double Graph::_fakeDistance(double la1,double lo1,double la2,double lo2) {
   	double radLat1 = _rad(la1);
    double radLat2 = _rad(la2);
    double a = radLat1 - radLat2;
    double b = _rad(lo1) - _rad(lo2);
    double s = 2 * asin(sqrt(pow(sin(a/2),2) + cos(radLat1)*cos(radLat2)*pow(sin(b/2),2)));
    return s;
}