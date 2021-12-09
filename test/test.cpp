/**
 * this file is used to test the data
 * not related to the project
*/

/* due to incorrect code, "make test" will not work until there is a change in "test.cpp" */
/* usually make the change of number in "getInformation" */
#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

//////////////////////////includes
#include <fstream>
#include <iostream>
#include "../src/Graph.hpp"
#include "../src/Draw.hpp"
using namespace std;

/////////////////////////testcase

Graph graph("data/airports_data_final.csv", "data/routes_data_final.csv");

TEST_CASE("Graph Size")
{
    REQUIRE(graph.size() == 6683);
    graph.pagerank();
}

TEST_CASE("Graph Constructor airports")
{
    SECTION("Airport ID 2") {
        //destination of airport ID 2
        vector<pair<int, int>> expected_2;
        expected_2.push_back(make_pair<int, int>(1, 1));
        expected_2.push_back(make_pair<int, int>(3, 1));
        expected_2.push_back(make_pair<int, int>(4, 1));
        expected_2.push_back(make_pair<int, int>(6, 2));
        expected_2.push_back(make_pair<int, int>(5430, 1));
        expected_2.push_back(make_pair<int, int>(5, 1));
        expected_2.push_back(make_pair<int, int>(5436, 1));
        REQUIRE(graph.getDestination(2).size() == 7);
        REQUIRE(graph.getDestination(2) == expected_2);
    }

    SECTION("Airport ID 2972") {
        //destination of airport ID 2972
        vector<pair<int, int>> expected_2972;
        expected_2972.push_back(make_pair<int, int>(2975, 2));
        expected_2972.push_back(make_pair<int, int>(6160, 2));
        expected_2972.push_back(make_pair<int, int>(2958, 1));
        expected_2972.push_back(make_pair<int, int>(4078, 3));
        expected_2972.push_back(make_pair<int, int>(4029, 2));
        expected_2972.push_back(make_pair<int, int>(2985, 1));
        expected_2972.push_back(make_pair<int, int>(6147, 1));
        expected_2972.push_back(make_pair<int, int>(6138, 1));
        expected_2972.push_back(make_pair<int, int>(4111, 1));
        REQUIRE(graph.getDestination(2972).size() == 9);
        REQUIRE(graph.getDestination(2972) == expected_2972);

    }

}


TEST_CASE("Dijkstra's Algorithm")
{
    // Shanghai Pudong --> Ha'il Airport (Saudi Arabia)
    SECTION("Airport ID 3406 to Airport ID 2069") {
        //checking if deterministic
        int source_airport_id = 3406;
        int dest_airport_id = 2069;
        vector<int> paths = graph.Dijkstra(source_airport_id, dest_airport_id);
        Draw png("./Equirectangular_projection_SW.png");
        png.drawAirport(graph,paths);
        REQUIRE(paths[0] == source_airport_id);
        for (int i = 1; i < int(paths.size()) -1; i++) {
            vector<int> sub_path = {paths.begin() + i, paths.end()};
            REQUIRE(graph.Dijkstra(paths[i], dest_airport_id) == sub_path);
        }
        REQUIRE(paths[int(paths.size()) - 1] == dest_airport_id);
    }

    // Shanghai Hongqiao --> UIUC Willard
    SECTION("Airport ID 3391 to Airport ID 4049") {
        //checking if deterministic
        int source_airport_id = 3391;
        int dest_airport_id = 4049;
        vector<int> paths = graph.Dijkstra(source_airport_id, dest_airport_id);
        REQUIRE(paths[0] == source_airport_id);
        for (int i = 1; i < int(paths.size()) -1; i++) {
            vector<int> sub_path = {paths.begin() + i, paths.end()};
            REQUIRE(graph.Dijkstra(paths[i], dest_airport_id) == sub_path);
        }
        REQUIRE(paths[int(paths.size()) - 1] == dest_airport_id);
    }

    // JFK New York --> Fuzhou Changle
    SECTION("Airport ID 3797 to Airport ID 3385") {
        //checking if deterministic
        int source_airport_id = 3797;
        int dest_airport_id = 3385;
        vector<int> paths = graph.Dijkstra(source_airport_id, dest_airport_id);
        REQUIRE(paths[0] == source_airport_id);
        for (int i = 1; i < int(paths.size()) -1; i++) {
            vector<int> sub_path = {paths.begin() + i, paths.end()};
            REQUIRE(graph.Dijkstra(paths[i], dest_airport_id) == sub_path);
        }
        REQUIRE(paths[int(paths.size()) - 1] == dest_airport_id);
    }

    // Léopold Sédar Senghor International Airport (Senegal) --> Murtala Muhammed International Airport (Nigeria)
    SECTION("Airport ID 1084 to Airport ID 273") {
        //checking if it is direct flight
        int source_airport_id = 1084;
        int dest_airport_id = 273;
        vector<int> paths = graph.Dijkstra(source_airport_id, dest_airport_id);
        REQUIRE(paths[0] == source_airport_id);
        REQUIRE(paths[1] == dest_airport_id);
        REQUIRE(paths.size() == 2);
    }

    // Alicante International Airport --> Alicante International Airport (to itself)
    SECTION("Airport ID 1212 to itself") {
        //checking if it is not a flight path
        int source_airport_id = 1212;
        int dest_airport_id = 1212;
        vector<int> paths = graph.Dijkstra(source_airport_id, dest_airport_id);
        REQUIRE(paths[0] == source_airport_id);
        REQUIRE(paths.size() == 1);
    }

    // Nonexisting Airport ID 1266 --> Nonexisting Airport ID 1267
    SECTION("Nonexisting Airport ID 1266 to Nonexisting Airport ID 1267") {
        //checking if it is not a flight path
        int source_airport_id = 1266;
        int dest_airport_id = 1267;
        vector<int> paths = graph.Dijkstra(source_airport_id, dest_airport_id);
        REQUIRE(paths[0] == -1);
        REQUIRE(paths.size() == 1);
    }

}

TEST_CASE("Airports Information")
{
    SECTION("Nonexisting Airport ID 682") {
        vector<string> airport_info = graph.getInformation(682);
        vector<string> expected_airport_info;
        expected_airport_info.push_back("no according airport found");
        REQUIRE(airport_info.size() == 1);
        REQUIRE(airport_info == expected_airport_info);
    }

    SECTION("getInformation Airport ID 351") {
        // 351,Berlin-Tegel Airport,Berlin,Germany,TXL,EDDT,52.5597,13.2877
        vector<string> airport_info = graph.getInformation(351);
        vector<string> expected_airport_info;
        expected_airport_info.push_back(to_string(351));
        expected_airport_info.push_back("Berlin-Tegel Airport");
        expected_airport_info.push_back("Berlin");
        expected_airport_info.push_back("Germany");
        expected_airport_info.push_back("TXL");
        expected_airport_info.push_back("EDDT");
        expected_airport_info.push_back(to_string(double(52.5597)));
        expected_airport_info.push_back(to_string(double(13.2877)));
        REQUIRE(airport_info.size() == 8);
        REQUIRE(airport_info == expected_airport_info);
    }

}

