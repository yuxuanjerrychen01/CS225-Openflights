#include "Draw.hpp"
#include "Airport.hpp"
#include "Graph.hpp"
#include <iostream>

/**
 * @brief This file is used to experience the fuction of the project for user.
 * 
 * @return int 
 */

int main() {
    
    //graph part
    Graph graph("data/airports_data_final.csv", "data/routes_data_final.csv");
    /**
     * @brief given two uniqueID of airport, Dijkstra will find the shorest path.
     * Example: Shanghai Pudong (3406)--> Ha'il Airport (2069)
     * Example: Shanghai Hongqiao (3391) --> UIUC Willard (4049)
     * return: a vector of ID for the airports in the path
     */
    int source_airport_id = 3406;
    int dest_airport_id = 2069;
    std::vector<int> path = graph.Dijkstra(source_airport_id, dest_airport_id);
    //print the outcome of Dijkstra
    for (auto id : path) {
        for(auto info : graph.getInformation(id)){
            std::cout<< info;
        }
        //std::endl;
    }
    
    //draw part
    Draw draw("Equirectangular_projection_SW.png");
    /**
     * @brief given the graph and the path of Dijkstra, drawDijkstra will draw a path in the world map.
     * The user can get Dijkstra path by running Dijkstra function above.
     * return: a PNG picture called "outcome_dijkstra.png"
     */
    draw.drawDijkstra(graph,path);
    /**
     * @brief given the graph and the uniqueID of a airport, drawDestinations will draw the position of given airport and all other airport it can reach in the world map.
     * Example: Shanghai Pudong (3406)
     * Example: Shanghai Hongqiao (3391)
     * Example: John F Kennedy International Airport (3797)
     * return: a PNG picture called "outcome_destination.png"
     * There are two example png called "example_destination_3406.png" and "example_dijkstra_3406to2069.png".
     */
    draw.drawDestinations(graph, 3406);
    return 0;
}