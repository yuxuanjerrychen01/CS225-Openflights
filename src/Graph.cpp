#include "Graph.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <queue>
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
        cout <<"no such airports file" << endl;
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
        cout <<"no such airlines file" << endl;
    }
}

void Graph::_getAirline(int start, int end) {
    // check whether it is repeated;
    if (airports.find(start) != airports.end() && airports.find(end) != airports.end()) {
        airports[start]->addAirlines(end);
    }
}

Graph::~Graph() {
    for(auto & airport : airports) {
        delete airport.second;
    }
}

vector<string> Graph::getInformation(int id) {
    vector<string> airport_info;
    auto iterator = airports.find(id);
    if(iterator == airports.end()) {
        airport_info.push_back("no according airport found");
        return airport_info;
    } else {
        // for (auto pair : airports[id]->destinations) {
        //     cout << "target airpots: " << airports[pair.first]->airportName << ", number of routes: " << to_string(pair.second) << endl;
        // }
        // cout << airports[id]->airportName +' '+ airports[id]->cityName +' '+ 
        // airports[id]->countryName +' '+ airports[id]->IATA + ' ' + 
        // airports[id]->ICAO + ' ' + to_string(airports[id]->Latitude) + ' ' + to_string(airports[id]->Longitude) << endl;
        // return "number of targets: " + to_string(airports[id]->destinations.size());
        airport_info.push_back(to_string(id));
        airport_info.push_back(airports[id]->getAirportName());
        airport_info.push_back(airports[id]->getCityName());
        airport_info.push_back(airports[id]->getCountryName());
        airport_info.push_back(airports[id]->getIATA());
        airport_info.push_back(airports[id]->getICAO());
        airport_info.push_back(to_string(airports[id]->getLatitude()));
        airport_info.push_back(to_string(airports[id]->getLongitude()));
        // airport_info.push_back("number of targets: " + to_string(airports[id]->destinations.size()));
        return airport_info;
    }
}

vector<int> Graph::Dijkstra(int start1, int end1) {
    //need to check the airports exist or segmentfault
    vector<int> paths;
    if ((getInformation(start1).size() == 1) || (getInformation(end1).size() == 1)) {
        paths.push_back(-1);
        return paths;
    }

    if(start1 == end1) {
        paths.push_back(start1);
        // paths.push_back(end1);
        return paths;
    }

    vector<Airport *> outcome; 
    priority_queue<pair<double, Airport*>, vector<pair<double, Airport*>>,
      std::greater<pair<double, Airport*>>> check;
    //priority_queue<pair<double,Airport *>> check;
    _setInitial();
    Airport * start = airports[start1];
    start->distance = 0;
    start->LastNode = -1;
    check.push({0.0,start});
    while (!check.empty()) {
        Airport * airport = check.top().second;
        check.pop();
        airport->isTravel = true;
        for(pair<int, int> & target : airport -> getDestinations()) {
            Airport * targetPort = airports[target.first];
            if(!targetPort->isTravel) {
                double curDistance = _findDistance(airport->getUniqueID(), target.first) + airport->distance;
                if (targetPort->distance > curDistance) {
                    targetPort->distance = curDistance;
                    check.push(pair<double, Airport*> (curDistance,targetPort));
                    targetPort->LastNode = airport->getUniqueID();
                }
            }
        }
    }
    
    Airport * end = airports[end1];
    if(end->distance == -1) {
        cout << "no connection between two airports" << endl;
    } else {
        Airport * curAirport = end;
        cout << to_string(curAirport->distance * EARTH_RADIUS) << "KM"<< endl;
        while (curAirport->LastNode != -1) {
            outcome.push_back(curAirport);
            curAirport = airports[curAirport->LastNode];
        }
        cout << "start" << endl;
        paths.push_back(start1);
        for(int i = outcome.size() - 1; i >= 0; i--) {
            paths.push_back(outcome[i]->getUniqueID());
        }
    }
    return paths;
}

void Graph::_setInitial() {
    for(auto & airport : airports) {
         airport.second->distance = double(INT64_MAX);
         airport.second->LastNode = 0;
         airport.second->isTravel = false;
    }
}

double Graph::_findDistance(int a, int b) {
    Airport * start = airports[a];
    Airport * end = airports[b];
    return _fakeDistance(start->getLatitude(), start->getLongitude(), end->getLatitude(), end->getLongitude());
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

void Graph::traversal(int start, vector<bool>& visited) {
    if (visited[(airports_set.at(start)).getUniqueID()] == false) {
        visited[(airports_set.at(start)).getUniqueID()] = true;
        //std::cout << (airports_set.at(start).airportName) << std::endl;

        for(int i = 0; i < (int)route_adjaMat.size(); i++) {
            if(route_adjaMat[(airports_set.at(start)).getUniqueID()][airports_set.at(i).getUniqueID()]>-1 && !visited[(airports_set.at(i)).getUniqueID()]) {
                traversal((airports_set.at(i)).getUniqueID(), visited);
            }
        }
    }
}

vector<int> Graph::getEdges(int srcID) {
    vector<int> edges;
    for (size_t i = 0; i < Graph::route_adjaMat.at(srcID).size(); i++) {
        if (Graph::route_adjaMat.at(srcID).at(i) >= 0) {
            edges.push_back(i);
        }
    }
    return edges;
}

bool Graph::ifAdjacent(int srcID, int destID) {
    return Graph::route_adjaMat.at(srcID).at(destID) >= 0;
}

vector<string> Graph::BFS_traverse(int source_airport, int dest_airport) {
    vector<string> output;
    //this is a vector of boolean(set default as false) covering all the airports filtered
    vector<bool> visited(false);

    queue<int> queue;
    queue.push(source_airport);
    int current_airport = source_airport;
    visited[current_airport] = true;

    while(!queue.empty()) {
        current_airport = queue.front();
        if (current_airport == dest_airport) {
            output.push_back(airport_graph.getAirportName());
            break;
        }
        output.push_back(airport_graph.getAirportName());
        for(int i = 0; i < (int)route_adjaMat.size(); i++) {
            if(visited[i] == false) {
                queue.push(i);
                visited[i] == true;
            }
        }
        queue.pop();
    } 
    if (current_airport != dest_airport) {
        return vector<string>();
    }
    return output;
}