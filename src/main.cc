#pragma once

#include "Graph.hpp"
#include "Draw.hpp"
#include "Airport.hpp"

std::string lowercase(std::string input) {
    for (unsigned i = 0; i < input.length(); ++i) {
        if (input[i] >= 'A' && input[i] <= 'Z') {
            input[i] = input[i] + 32;
        }
    }
    return input;
};


int main(int argc, char **argv) {
    cout<<“”<<endl;
    cout<<“CS225 Final Project: OpenFlights”<<endl;
    cout<<“Team member: ruozhen2, xx19, kangyuf2, yuxuan19”<<endl;

    // operations: 
    cout<<“Enter a number to select an operation:”<<endl;
    cout<<“0. Use the BFS to traverse the graph until a destination airport from a given airport”<<endl;
    cout<<“1. Use the page rank to find the most popular airports”<<endl;
    cout<<“2. Calculate the shortest path between two airports using Dijkstra”<<endl;

    int mode;
    cin>>mode;

    bool validSource = false;

        std::string operation = "";
        for (int i = 0; i < argc; ++i) {
            operation += lowercase(argv[i]);
        }

        if (operation == "dfs"){}
        if (operation == "bfs"){
            bool valid_Airport = false;
		    while(valid_Airport == false) {
			    cout<<“Enter a source airport ID:”<<endl;
			    int source_Airport;
			    cin>>source_Airport;
			
		    }
        }
        if (operation == "pagerank"){}
        //dijkstra
        if (operation == "dijkstra"){
        }
    }