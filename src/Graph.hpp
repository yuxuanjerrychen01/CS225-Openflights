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
        vector<pair<int, int>> destinations;                            //first integer store the targe airport ID, second integer store the number of airline in given route 
        Airport() {}
        Airport(int id, string airport, string city, string country, string iata, string icao, double latitude, double longitude)
         : uniqueID(id), airportName(airport), cityName(city), countryName(country), IATA(iata), ICAO(icao), Latitude(latitude), Longitude(longitude) {}
    };
    unordered_map<int, Airport *> airports;                               //store the airports, the key store airport ID, the value is the pointer of airports.
    long long size = 0;
    
    public:
    Graph();                                    //empty constructor
    ~Graph();                                   //destructor
    Graph(string airportsFile, string airRoutesFile);                 //for the project, we assume the given data is a vector of string for each line, create the airport as node
    void _getAirline(int a, int b);              //given a vector of airline information, fuction will assign each airline as edage to the node
    string getInformation(int id);              //test function that make sure all the data is in the graph
};
