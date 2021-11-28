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
    Graph graph("data/airports-data/airports_data_useful_drop_city_ICAO_nonAirport.csv", "data/routes-data/routes_data_useful_stops0.csv");
    cout << graph.getInformation(2) << endl;
}
