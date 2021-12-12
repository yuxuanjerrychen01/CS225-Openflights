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
    Graph graph("data/airports_data_final_new.csv", "data/routes_data_final.csv");

    std::cout << "Hello! This is SPYE01000001 Openflights Data Analysis." << std::endl;
    std::cout << "get airport information -- enter 0." << std::endl;
    std::cout << "get shortest path between two airports -- enter 1." << std::endl;
    std::cout << "get important airports -- enter 2." << std::endl;
    std::cout << "get traversal txt -- enter 3." << std::endl;
    std::cout << "graph visualization of shortest path -- enter 4." << std::endl;
    std::cout << "graph visualization of destinations -- enter 5." << std::endl;

    int number;
    std::cin >> number;

    if (number < 0 || number > 5) {
        std::cout << "Not a valid choice! Must be an integer from 0 to 5." << std::endl;
        return 0;
    }

    if (number == 0) {
        std::cout << "Enter airport ID:" << std::endl;
        int airport_id;
        std::cin >> airport_id;
        std::vector<std::string> info = graph.getInformation(airport_id);
        if (info.size() == 1) {
            std::cout << info[0] << std::endl;
            return 0;
        }

        std::cout << "Airport name: " << info[1] << std::endl;
        std::cout << "Airport ID: " << info[0] << std::endl;
        std::cout << "City: " << info[2] << std::endl;
        std::cout << "Country: " << info[3] << std::endl;
        std::cout << "IATA: " << info[0] << std::endl;
        std::cout << "ICAO: " << info[0] << std::endl;
        std::cout << "Latitude: " << info[1] << std::endl;
        std::cout << "Longitude: " << info[1] << std::endl;
        return 0;
    }

    if (number == 1) {
        std::cout << "Enter source airport ID:" << std::endl;
        int source_airport_id;
        std::cin >> source_airport_id;

        std::cout << "Enter destination airport ID:" << std::endl;
        int dest_airport_id;
        std::cin >> dest_airport_id;

        std::vector<int> path = graph.Dijkstra(source_airport_id, dest_airport_id);
        
        //edge case
        if (path.size() == 1) {
            int val = path[0];
            if (val == -1) {
                std::cout << "Airport ID does not exist." << std::endl;
                return 0;
            } else {
                std::cout<< "This is the same airport." << std::endl;
                return 0;
            }
        }
        
        for (auto id : path) {
            std::vector<std::string> info = graph.getInformation(id);
            std::cout<< info[1] << " (" << info[0] << ") " << std::endl;
        }
        return 0;
    }

    if (number == 2) {
        return 0;
    }

    if (number == 3) {
        return 0;
    }

    if (number == 4) {
        std::cout << "Enter source airport ID:" << std::endl;
        int source_airport_id;
        std::cin >> source_airport_id;

        std::cout << "Enter destination airport ID:" << std::endl;
        int dest_airport_id;
        std::cin >> dest_airport_id;

        std::vector<int> path = graph.Dijkstra(source_airport_id, dest_airport_id);
        
        //edge case
        if (path.size() == 1) {
            int val = path[0];
            if (val == -1) {
                std::cout << "Airport ID does not exist." << std::endl;
                return 0;
            } else {
                std::cout<< "This is the same airport." << std::endl;
                return 0;
            }
        }
        
        Draw draw("Equirectangular_projection_SW.png");
        draw.drawDijkstra(graph,path);
        return 0;
    }

    if (number == 5) {
        std::cout << "Enter airport ID:" << std::endl;
        int airport_id;
        std::cin >> airport_id;

        Draw draw("Equirectangular_projection_SW.png");
        draw.drawDestinations(graph, airport_id);
        return 0;
    }
    return 0;
    
//     //graph part
//     Graph graph("data/airports_data_final_new.csv", "data/routes_data_final.csv");
//     /**
//      * @brief given two uniqueID of airport, Dijkstra will find the shorest path.
//      * Example: Shanghai Pudong (3406)--> Ha'il Airport (2069)
//      * Example: Shanghai Hongqiao (3391) --> UIUC Willard (4049)
//      * return: a vector of ID for the airports in the path
//      */
//     int source_airport_id = 3406;
//     int dest_airport_id = 2069;
//     std::vector<int> path = graph.Dijkstra(source_airport_id, dest_airport_id);
//     //print the outcome of Dijkstra
//     for (auto id : path) {
//         for(auto info : graph.getInformation(id)){
//             std::cout<< info;
//         }
//         //std::endl;
//     }
    
//     //draw part
//     Draw draw("Equirectangular_projection_SW.png");
//     /**
//      * @brief given the graph and the path of Dijkstra, drawDijkstra will draw a path in the world map.
//      * The user can get Dijkstra path by running Dijkstra function above.
//      * return: a PNG picture called "outcome_dijkstra.png"
//      */
//     draw.drawDijkstra(graph,path);
//     /**
//      * @brief given the graph and the uniqueID of a airport, drawDestinations will draw the position of given airport and all other airport it can reach in the world map.
//      * Example: Shanghai Pudong (3406)
//      * Example: Shanghai Hongqiao (3391)
//      * Example: John F Kennedy International Airport (3797)
//      * return: a PNG picture called "outcome_destination.png"
//      * There are two example png called "example_destination_3406.png" and "example_dijkstra_3406to2069.png".
//      */
//     draw.drawDestinations(graph, 3406);
//     return 0;
}
