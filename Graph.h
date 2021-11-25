#pragma once
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;
class Graph{
    private:
    struct Airport
    {
        /* data */
        int uniqueID;
        string airportName;             //Name of airport. May or may not contain the city name.
        string cityName;
        string countryName;
        string IATA;
        string ICAO;
        double Latitude;
        double Longitude;
        Airport() {}
        Airport(int id, string airport, string city, string country, string iata, string icao, double latitude, double longitude)
         : uniqueID(id), airportName(airport), cityName(city), countryName(country), IATA(iata), ICAO(icao), Latitude(latitude), Longitude(longitude) {}
    };
    unordered_map<int, Airport> airports;
    public:
    Graph();                                    //empty constructor
    Graph(string airportsFile);                 //for the project, we assume the given data is a vector of string for each line, create the airport as node
    void getAirline(vector<string> data);       //given a vector of airline information, fuction will assign each airline as edage to the node
    string getInformation(int id);              //test function that make sure all the data is in the graph
};
