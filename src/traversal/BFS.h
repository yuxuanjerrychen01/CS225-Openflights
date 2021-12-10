#pragma once
#include "Airport.hpp"
#include <string>
#include <queue>
#include <stack>
#include <unordered_map>
#include <fstream>
#include <vector>
#include "Graph.hpp"

using namespace std;

class BFS {
    public:
        BFS(Airport graph);
        vector<string> BFS_traverse(int source_airport, int dest_airport);
    private:
        Airport airport_graph;
};
