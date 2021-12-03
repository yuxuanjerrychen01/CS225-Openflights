#pragma once

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
class Graph{
    private:
    struct Airport
    {
        /* data */
        int uniqueID;                                                   //Unique OpenFlights identifier for this airport.
        string airportName;                                             //Name of airport. May or may not contain the city name.
        string cityName;                                                //Main city served by airport. May be spelled differently from Name.
        string countryName;                                             //Country or territory where airport is located.
        string IATA;                                                    //3-letter IATA code.
        string ICAO;                                                    //4-letter ICAO code.
        double Latitude;                                                
        double Longitude;
        double distance;
        int LastNode;
        bool isTravel;
        vector<pair<int, int>> destinations;                            //first integer store the targe airport ID, second integer store the number of airline in given route 
        Airport() {}
        Airport(int id, string airport, string city, string country, string iata, string icao, double latitude, double longitude)
         : uniqueID(id), airportName(airport), cityName(city), countryName(country), IATA(iata), ICAO(icao), Latitude(latitude), Longitude(longitude) {}
    };
    unordered_map<int, Airport *> airports;                             //store the airports, the key store airport ID, the value is the pointer of airports.
    vector<Airport> airports_set; //the set of total airports
    long long size_ = 0;
    void _getAirline(int a, int b);                                     //help fuction, given airline information, fuction will assign each airline as edage to the node.
    void _setInitial();                                                 //help fuction to set distance, LastNode, isTraval in airports node.
    double _findDistance(int a, int b);                                 //help fuction to calculate the distance of two airports.
    double _rad(double a);                                              //help fuction to find the radiance.
    double _fakeDistance(double a, double b, double c, double d);       //help fuction, this is fake because it do not times the radius of earth.
    public:
    Graph();                                                            //empty constructor
    ~Graph();                                                           //destructor
    Graph(string airportsFile, string airRoutesFile);                   //given data is a file of airport information, create the airport as node
    string getInformation(int id);                                      //test function that make sure all the data is in the graph
    long long size() {return size_;};                                   //the size of airports(nodes).
    vector<pair<int, int>> getDestination(int source) {return airports[source]->destinations;};
    void Dijkstra(int start, int end);                                  //dijkstra to find the stortest path to travel depened on distance
    void traversal(int start, vector<bool>& visited);                   //using Depth First Search based on recursion, visited is to record the aiport being visited
    vector<vector<int>> route_adjaMat;                                  //use a route adjacency matric to store all routes here. We use row to represent departure airpot and column to 
    //respresent arrival.
    vector<int> getEdges(int srcID);                                    //get the edges given specific srcID
    bool ifAdjacent(int srcID, int destID);
};
