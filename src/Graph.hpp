#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include "Airport.hpp"
#include <iostream>
#include <fstream>
using namespace std;
class Graph{
    private:
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
    vector<string> getInformation(int id);                              //test function that make sure all the data is in the graph
    long long size() {return size_;};                                   //the size of airports(nodes).
    vector<pair<int, int>> getDestination(int source) {return airports[source]->getDestinations();};
    vector<int> Dijkstra(int start, int end);                           //dijkstra to find the stortest path to travel depened on distance
    // void traversal(int start, vector<bool>& visited);                   //using Depth First Search based on recursion, visited is to record the aiport being visited
    // vector<vector<int>> route_adjaMat;                                  //use a route adjacency matric to store all routes here. We use row to represent departure airpot and column to 
    // //respresent arrival.
    // vector<int> getEdges(int srcID);                                    //get the edges given specific srcID
    // bool ifAdjacent(int srcID, int destID);
    void pagerank() {
        long double PR_initial = 1.0 / (double) 6683;
        for (auto & airport : airports) {
            airport.second->PR_value = PR_initial;
        }

        unordered_map<int, unordered_map<int, int>> adj_matrix;

        for (auto i : airports) {
            unordered_map<int, int> temp_dis;
            for (auto des : i.second->getDestinations()) {
                temp_dis[des.first] = des.second;
                i.second->total_lines+=des.second;
            }
            adj_matrix[i.first] = temp_dis;
        }

        //iteration 100 times for updating new pagevalue
        for (int i = 0; i < 10; ++i) {
            for (auto & air : airports) {
                long double temp = 0.0;
                for (auto & map : adj_matrix) {
                    if (map.second.find(air.first) != map.second.end()) {
                         temp += airports[map.first]->PR_value / (double) airports[map.first]->total_lines * (double) map.second[air.first];
                    }
                }
                air.second->PR_value = temp;
            }
            std::cout<<i<<std::endl;
        }
        ofstream fts("airports_importance.txt");
        for (auto p : airports) {
            fts<<p.second->getAirportName() + "," + to_string(p.second->PR_value)<<endl;
        }
    };
};
