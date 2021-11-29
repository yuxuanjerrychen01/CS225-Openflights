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
using namespace std;

/////////////////////////testcase
TEST_CASE("Graph Constructor airports")
{
    Graph graph("data/airports_data_final.csv", "data/routes_data_final.csv");
    REQUIRE(graph.size() == 6683);

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
