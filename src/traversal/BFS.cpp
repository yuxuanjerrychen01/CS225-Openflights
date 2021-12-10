#include "BFS.h"
#include "Graph.hpp"
#include <climits>

BFS::BFS(Airport graph) {
    airport_graph = graph;
}
/**
 * returns a vector of strings of the traversed airpots in BFS algorithms
 * if there is no traversal between the two, returns an empty vector
 **/
vector<string> BFS::BFS_traverse(int source_airport, int dest_airport) {
    vector<string> output;
    //this is a vector of boolean(set default as false) covering all the airports filtered
    vector<bool> visited(14109, false);

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
        for(int i = 0; i < (int)route_adjaMat.size(); i++)
    } 
}