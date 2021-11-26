#include "Graph.hpp"
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
            Airport newAirport(id, airport[1], airport[2], airport[3], airport[4], airport[5],latitude, longitude);
            airports[id] = newAirport;
        }
    } else {
        cout <<"no such file" << endl;
    }
    size = airports.size();
    
   // edges with weights
}

void Graph::getAirline(vector<string> data) {
    //not finish
    (void) data;
}
string Graph::getInformation(int id) {
    auto iterator = airports.find(id);
    if(iterator == airports.end()) {
        return "no according airport found";
    } else {
        return airports[id].airportName +' '+ airports[id].cityName +' '+ 
        airports[id].countryName +' '+ airports[id].IATA + ' ' + 
        airports[id].ICAO + ' ' + to_string(airports[id].Latitude) + ' ' + to_string(airports[id].Longitude);
    }
}
