/**
 * this file is used to test the data
 * not related to the project
*/

/* due to incorrect code, "make test" will not work until there is a change in "test.cpp" */
/* usually make the change of number in "getInformation" */
#include <fstream>
#include <iostream>
#include "Graph.cpp"
using namespace std;
int main()
{
    Graph graph("data/airports_data_useful.csv");
    cout << graph.getInformation(3332) << endl;
    return 0;
}
