#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"
#include "Graph.hpp"
#include <vector>
using namespace cs225;
class Draw  
{
private:
    PNG background;
    /* data */
public:
    Draw(string const & fileName);
    ~Draw();
    void drawDijkstra(Graph & graph, std::vector<int> info);
    void _drawAirline(PNG & png,std::pair<int,int> start, std::pair<int,int> end);
    std::pair<int,int> _getXY(double la, double lo);
    void drawDestinations(Graph & graph, int id);
    void _drawAirport(PNG & png, std::pair<int, int> position);
};

