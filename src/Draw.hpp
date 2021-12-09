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
    PNG drawAirport(Graph & graph, std::vector<int> info);
    //void _drawAirline(PNG & png,std::vector<std::pair<int,int>> routes);
    std::pair<int,int> _getXY(double la, double lo);
};

