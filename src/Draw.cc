#include "Draw.hpp"
#include "Graph.hpp"
#include <string>

using namespace cs225;

Draw::Draw(std::string const & fileName) {
    background.readFromFile(fileName);
    
}
PNG Draw::drawAirport(Graph & graph, std::vector<int> info) {
    PNG outcome(background);
    std::vector<std::pair<int,int>> routes;
    for(int id : info) {
        vector<string> airport = graph.getInformation(id);
        double latitude = stod(airport[6]);
        double longitude = stod(airport[7]);
        std::pair<int,int> position = _getXY(latitude,longitude);
        routes.push_back(position);
        for(int i = -2; i < 3; i++) {
            for(int j = -2; j < 3; j++) {
                unsigned int x = position.first + i;
                unsigned int y = position.second + j;
                if(x >= outcome.width() || x < 0 || y >= outcome.height() || y < 0) {
                    continue;
                }
                HSLAPixel & pixel = outcome.getPixel(x,y);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
        }
    }
    outcome.writeToFile("outcome.png");
    return outcome;
}

std::pair<int, int> Draw::_getXY(double la, double lo) {
    //need to be implemented

    int x = 2044/2 + lo/180 * (1022);
    int y = 1022/2 - la/90 * 511;

    return {x,y};
}

// void Draw::_drawAirline(PNG & png,std::vector<std::pair<int,int>> routes) {
//     for(int i = 1; i < routes.size(); i++) {
//         std::pair<int,int> start = routes[i-1];
//         std::pair<int,int> end = routes[i];
//         //need to be implemented
//     }
// }
Draw::~Draw() {
    //dothing
}