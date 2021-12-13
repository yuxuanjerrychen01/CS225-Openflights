#include "Graph.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <queue>
#include "math.h"
#define pi 3.1415926535897932384626433832795
#define EARTH_RADIUS 6378.137
using namespace std;


/**
 * @brief default construct a new Graph:: Graph object
 * 
 */
Graph::Graph() {
    //do nothing
}
/**
 * @brief Construct a new Graph:: Graph object
 * 
 * @param airportsFile 
 * @param airRoutesFile 
 */
Graph::Graph(string airportsFile, string airRoutesFile) {
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
            Airport * newAirport = new Airport(id, airport[1], airport[2], airport[3], airport[4], airport[5],latitude, longitude);
            airports[id] = newAirport;
        }
        cout <<"airports finished" << endl;
    } else {
        cout <<"no such airports file" << endl;
    }
    size_ = airports.size();
    
   // edges with weights
   ifstream airRoutes(airRoutesFile);
    string eachRoute;
    if (airRoutes.is_open()) {
        getline(airRoutes, eachRoute);
        while (getline(airRoutes,eachRoute)) {
            vector<string> airroutes;
            string seg;
            stringstream eachLine2(eachRoute);
            while (getline(eachLine2, seg, ',')) {
                airroutes.push_back(seg);
            }
            //airroutes[3]=source airport ID airroutes[5]=destination airport ID
            if (!airroutes[3].empty() && !airroutes[5].empty()) {
                _getAirline(stoi(airroutes[3]), stoi(airroutes[5])); 
            }
        }
        cout <<"airlines finished" << endl;
    } else {
        cout <<"no such airlines file" << endl;
    }
}
/**
 * @brief a getter helper function to return the airline between two airports
 * 
 * @param start 
 * @param end 
 */
void Graph::_getAirline(int start, int end) {
    // check whether it is repeated;
    if (airports.find(start) != airports.end() && airports.find(end) != airports.end()) {
        airports[start]->addAirlines(end);
    }
}
/**
 * @brief Destroy the Graph:: Graph object
 * 
 */
Graph::~Graph() {
    for(auto & airport : airports) {
        delete airport.second;
    }
}

/**
 * @brief return all the information of an airport given its uniqueID
 * 
 * @param id 
 * @return vector<string> 
 */
vector<string> Graph::getInformation(int id) {
    vector<string> airport_info;
    auto iterator = airports.find(id);
    if(iterator == airports.end()) {
        airport_info.push_back("no according airport found");
        return airport_info;
    } else {
        airport_info.push_back(to_string(id));
        airport_info.push_back(airports[id]->getAirportName());
        airport_info.push_back(airports[id]->getCityName());
        airport_info.push_back(airports[id]->getCountryName());
        airport_info.push_back(airports[id]->getIATA());
        airport_info.push_back(airports[id]->getICAO());
        airport_info.push_back(to_string(airports[id]->getLatitude()));
        airport_info.push_back(to_string(airports[id]->getLongitude()));
        // airport_info.push_back("number of targets: " + to_string(airports[id]->destinations.size()));
        return airport_info;
    }
}
/**
 * @brief the dijkstra algorithm to find the shortest path between starting airport to ending airport
 * 
 * @param start1 
 * @param end1 
 * @return vector<int> 
 */
vector<int> Graph::Dijkstra(int start1, int end1) {
    //need to check the airports exist or segmentfault
    vector<int> paths;
    if ((getInformation(start1).size() == 1) || (getInformation(end1).size() == 1)) {
        paths.push_back(-1);
        return paths;
    }

    if(start1 == end1) {
        paths.push_back(start1);
        // paths.push_back(end1);
        return paths;
    }

    vector<Airport *> outcome; 
    priority_queue<pair<double, Airport*>, vector<pair<double, Airport*>>,
      std::greater<pair<double, Airport*>>> check;
    //priority_queue<pair<double,Airport *>> check;
    _setInitial();
    Airport * start = airports[start1];
    start->distance = 0;
    start->LastNode = -1;
    check.push({0.0,start});
    while (!check.empty()) {
        Airport * airport = check.top().second;
        check.pop();
        airport->isTravel = true;
        for(pair<int, int> & target : airport -> getDestinations()) {
            Airport * targetPort = airports[target.first];
            if(!targetPort->isTravel) {
                double curDistance = _findDistance(airport->getUniqueID(), target.first) + airport->distance;
                if (targetPort->distance > curDistance) {
                    targetPort->distance = curDistance;
                    check.push(pair<double, Airport*> (curDistance,targetPort));
                    targetPort->LastNode = airport->getUniqueID();
                }
            }
        }
    }
    
    Airport * end = airports[end1];
    if(end->distance == -1) {
        cout << "no connection between two airports" << endl;
    } else {
        Airport * curAirport = end;
        while (curAirport->LastNode != -1) {
            outcome.push_back(curAirport);
            curAirport = airports[curAirport->LastNode];
        }
        paths.push_back(start1);
        for(int i = outcome.size() - 1; i >= 0; i--) {
            paths.push_back(outcome[i]->getUniqueID());
        }
    }
    return paths;
}

/**
 * @brief set all possible variables as default values
 * 
 */
void Graph::_setInitial() {
    for(auto & airport : airports) {
         airport.second->distance = double(INT64_MAX);
         airport.second->LastNode = 0;
         airport.second->isTravel = false;
    }
}

/**
 * @brief to find the distance between two airports given their uniqueID
 * 
 * @param a 
 * @param b 
 * @return double 
 */
double Graph::_findDistance(int a, int b) {
    Airport * start = airports[a];
    Airport * end = airports[b];
    return _fakeDistance(start->getLatitude(), start->getLongitude(), end->getLatitude(), end->getLongitude());
}

double Graph::_rad(double d) {
    return d * pi /180.0;
}
/**
 * @brief a helper function
 * 
 * @param la1 
 * @param lo1 
 * @param la2 
 * @param lo2 
 * @return double 
 */
double Graph::_fakeDistance(double la1,double lo1,double la2,double lo2) {
    double radLat1 = _rad(la1);
    double radLat2 = _rad(la2);
    double a = radLat1 - radLat2;
    double b = _rad(lo1) - _rad(lo2);
    double s = 2 * asin(sqrt(pow(sin(a/2),2) + cos(radLat1)*cos(radLat2)*pow(sin(b/2),2)));
    return s;
}

/**
 * @brief this is the function using for finding edges given the uniqueID of the source airport
 * 
 * @param srcID 
 * @return vector<int> 
 */
vector<int> Graph::getEdges(int srcID) {
    vector<int> edges;
    for (size_t i = 0; i < Graph::route_adjaMat.at(srcID).size(); i++) {
        if (Graph::route_adjaMat.at(srcID).at(i) >= 0) {
            edges.push_back(i);
        }
    }
    return edges;
}

/**
 * @brief check if two airports are adjacent given their uniqueID
 * 
 * @param srcID 
 * @param destID 
 * @return true 
 * @return false 
 */
bool Graph::ifAdjacent(int srcID, int destID) {
    return Graph::route_adjaMat.at(srcID).at(destID) >= 0;
}

/**
 * @brief here is the traverse function based on BFS traversing all the airports possible
 * 
 * @param source_airport 
 * @return vector<string> 
 */
vector<string> Graph::BFS_all(int source_airport) {
    vector<string> output;
    if (airports.find(source_airport) == airports.end()) {
        std::cout << "Nonexisting airport ID." << std::endl;
        output.push_back("Nonexisting airport ID");
        return output;
    }
    vector<string> temp;

    _setInitial();
    queue<int> queue;
    //output.reserve(output.size() + BFS_all_helper(source_airport, queue).size());
    //output.insert(output.end(), BFS_all_helper(source_airport, queue).begin(), BFS_all_helper(source_airport, queue).end());
    temp = BFS_all_helper(source_airport, queue);
    for (auto str : temp) {output.push_back(str);}

    for (auto it : airports) {
        if (it.second -> isTravel == false) {
            // output.reserve(output.size() + BFS_all_helper(it.first, queue).size());
            // output.insert(output.end(), BFS_all_helper(it.first, queue).begin(), BFS_all_helper(it.first, queue).end());
            temp = BFS_all_helper(it.first, queue);
            for (auto str : temp) {output.push_back(str);}
        }
    }
    
    ofstream fts("./output/BFS_traversal.txt");
    for (auto str : output) {
        fts << str << endl;
    }
    return output;
}
/**
 * @brief this is the helper function for BFS_all
 * 
 * @param airport_id 
 * @param queue 
 * @return vector<string> 
 */
vector<string> Graph::BFS_all_helper(int airport_id, queue<int> queue) {
    vector<string> output;

    queue.push(airport_id);
    int current_airport = airport_id;
    if(airports.find(airport_id) != airports.end()){
        airports[airport_id] -> isTravel = true;
        // cout<< queue.size() << endl;
        while(!queue.empty()) {
            current_airport = queue.front();
            Airport * airport_temp = airports[current_airport];
            output.push_back(airport_temp->getAirportName());
            
            for(auto id : airport_temp->getDestinations()) {
                if(airports[id.first] -> isTravel == false) {
                    queue.push(id.first);
                    airports[id.first] -> isTravel = true;
                }
            }
            queue.pop();
        } 
        
    }
    // cout << output.size() << endl;
    return output;
}
/**
 * @brief the pagerank algorithm to calculate the visiting proportion of each airport
 * 
 * @param tolerance a parameter to check 
 * the changes of Pagerank value sum is with the tolerance
 */

void Graph::pagerank(double tolerance, int iteration) {
    double PR_initial = 1.0 / airports.size();
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
    double page_sum = 1.0;
    double page_sum_temp = 0.0;
    int count = 0;
    while (abs(page_sum - page_sum_temp) > tolerance || count < iteration) {
        if (count != 0) {
            page_sum = page_sum_temp;
        }
        count++;
        //normalize PR_value
        for (auto & air : airports) {
            air.second->PR_value = air.second->PR_value / page_sum;
        }
        //begain to find
        page_sum_temp = 0;
        for (auto & air : airports) {
            page_sum_temp += air.second->PR_value;
            double temp = 0.0;
            for (auto & map : adj_matrix) {
                if (map.second.find(air.first) != map.second.end()) {
                        temp += (airports[map.first]->PR_value / (double) airports[map.first]->total_lines) * (double) map.second[air.first];
                }
            }
            air.second->PR_value = temp;
        }
    }
    for (auto & air : airports) {
        air.second->PR_value = air.second->PR_value / page_sum;
    }
    ofstream fts("./output/airports_importance.txt");
    double sum = 0;
    for (auto &p : airports) {
        sum += p.second->PR_value;
        fts<<p.second->getAirportName() + "," + to_string(p.second->PR_value) <<endl;
    }
}

