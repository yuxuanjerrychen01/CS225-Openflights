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
    Graph graph("./data/airports_data_final_new.csv", "./data/routes_data_final.csv");

    std::cout << " " << std::endl;
    std::cout << "Hello! This is SPYE01000001 OpenFlights Data Analysis." << std::endl;
    std::cout << "get airport information -- enter 1." << std::endl;
    std::cout << "get shortest path between two airports -- enter 2." << std::endl;
    std::cout << "get important airports txt -- enter 3." << std::endl;
    std::cout << "get traversal txt -- enter 4." << std::endl;
    std::cout << "graph visualization of shortest path -- enter 5." << std::endl;
    std::cout << "graph visualization of destinations -- enter 6." << std::endl;

    int number;
    std::cin >> number;
    std::cout << " " << std::endl;

    if (number < 1 || number > 6) {
        std::cout << "Not a valid choice! Must be an integer from 0 to 5." << std::endl;
        return 0;
    }

    if (number == 1) {
        std::cout << "Enter airport ID: " << std::endl;
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
        std::cout << "IATA: " << info[4] << std::endl;
        std::cout << "ICAO: " << info[5] << std::endl;
        std::cout << "Latitude: " << info[6] << std::endl;
        std::cout << "Longitude: " << info[7] << std::endl;
        return 0;
    }

    if (number == 2) {
        std::cout << "Enter source airport ID: " << std::endl;
        int source_airport_id;
        std::cin >> source_airport_id;
        std::cout << " " << std::endl;

        std::cout << "Enter destination airport ID: " << std::endl;
        int dest_airport_id;
        std::cin >> dest_airport_id;
        std::cout << " " << std::endl;

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

    if (number == 3) {
        std::cout << "Variable tolerance is a double from (0,1)." << std::endl;
        std::cout << "Enter tolerance for PageRank Algorithm: " << std::endl;
        double tolerance;
        std::cin >> tolerance;
        std::cout << " " << std::endl;
        if (tolerance <= 0 || tolerance >= 1) {
            std::cout << "Incorrect tolerance, tolerance must be in (0,1)." << std::endl;
            return 0;
        }

        std::cout << "Variable iteration can be value 10 or value 100 (may take 5 min)." << std::endl;
        std::cout << "Enter iteration for PageRank Algorithm: " << std::endl;
        int iteration;
        std::cin >> iteration;
        std::cout << " " << std::endl;
        if (iteration != 10 && iteration != 100) {
            std::cout << "Incorrect iteration, iteration must be either 10 or 100." << std::endl;
            return 0;
        }

        graph.pagerank(tolerance, iteration);
        std::cout << "Output has been stored as ./output/airports_importance" << std::endl;
        return 0;
    }

    if (number == 4) {
        std::cout << "Enter airport ID: " << std::endl;
        int airport_id;
        std::cin >> airport_id;
        std::cout << " " << std::endl;

        graph.BFS_all(airport_id);
        std::cout << "The traversal information has been stored as ./output/BFS_traversal.txt" << std::endl;
        return 0;
    }

    if (number == 5) {
        std::cout << "Enter source airport ID: " << std::endl;
        int source_airport_id;
        std::cin >> source_airport_id;
        std::cout << " " << std::endl;

        std::cout << "Enter destination airport ID: " << std::endl;
        int dest_airport_id;
        std::cin >> dest_airport_id;
        std::cout << " " << std::endl;

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
        std::cout << "The graph visualization has been stored as ./output/outcome_dijkstra.png" << std::endl;
        return 0;
    }

    if (number == 6) {
        std::cout << "Enter airport ID:" << std::endl;
        int airport_id;
        std::cin >> airport_id;
        std::cout << " " << std::endl;

        Draw draw("Equirectangular_projection_SW.png");
        draw.drawDestinations(graph, airport_id);
        std::cout << "The graph visualization has been stored as ./output/outcome_destination.png" << std::endl;
        return 0;
    }
    return 0;
    
}
