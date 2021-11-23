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
        string airportName;             //Name of airport. May or may not contain the city name.
        Airport() {}
        Airport(string name) : airportName(name) {}
    };
    unordered_map<int, Airport> airports;
    public:
    Graph();                                    //empty constructor
    Graph(vector<string> data);                 //for the project, we assume the given data is a vector of string for each line, create the airport as node
    void getAirline(vector<string> data);       //given a vector of airline information, fuction will assign each airline as edage to the node
    string getInformation(int id);              //test function that make sure all the data is in the graph
};