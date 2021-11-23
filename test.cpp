/**
 * this file is used to test the data
 * not related to the project
*/
#include <fstream>
#include <iostream>
#include "Graph.cpp"
using namespace std;
int main()
{
    ifstream data("data/airports_data_useful.csv");     //try to read data from the csv
    string line;                                        //store each line of data
    vector<string> data2;
    if(data) {
        while (getline (data, line)){ 
            data2.push_back(line);
        }
    } else {
        cout <<"no such file" << endl;
    }
    Graph graph(data2);
    cout << graph.getInformation(333) << endl;
    return 0;
}