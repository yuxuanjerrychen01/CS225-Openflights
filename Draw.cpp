#include "Draw.hpp"
#include "Graph.hpp"
#include <string>
#include <stdlib.h> 

using namespace cs225;
/**
 * @param fileName: the name of background picture, png format
 * The constructor.
 **/
Draw::Draw(std::string const & fileName) {
    background.readFromFile(fileName);
    
}
/**
 * @param graph: the graph we use to get the data
 * @param info: a vector that store the path of shortest path
 * draw the path on the background picture, return as "outcome_dijkstra.png"
 **/
void Draw::drawDijkstra(Graph & graph, std::vector<int> info) {
    //edge case
    if (info.size() == 1) {
        std::cout << "Cannot draw; airport id is inaccurate." << std::endl;
        return;
    }
    
    PNG outcome(background);
    std::vector<std::pair<int,int>> routes;
    for(int id : info) {
        vector<string> airport = graph.getInformation(id);
        double latitude = stod(airport[6]);
        double longitude = stod(airport[7]);
        std::pair<int,int> position = _getXY(latitude,longitude);
        routes.push_back(position);
        _drawAirport(outcome, position);
    }
    for(unsigned long i = 1; i < routes.size(); i++) {
        _drawAirline(outcome, routes[i-1], routes[i]);
    }
    outcome.writeToFile("output/outcome_dijkstra.png");
}

/**
 * @param graph: the graph we use to get the data
 * @param id: the uniqueID of airport
 * draw the given airport and all destination airports it has 
 **/
void Draw::drawDestinations(Graph & graph, int id) {
    PNG outcome(background);
    std::vector<std::pair<int,int>> routes;
    vector<string> startairport = graph.getInformation(id);
    
    // edge case
    if (startairport.size() == 1) {
        std::cout << "Cannot draw; airport id is inaccurate." << std::endl;
        return;
    }
    
    double latitude = stod(startairport[6]);
    double longitude = stod(startairport[7]);
    std::pair<int,int> startposition = _getXY(latitude,longitude);
    _drawAirport(outcome, startposition);
    std::vector<std::pair<int, int>> destination = graph.getDestination(id);
    for(auto port : destination) {
        vector<string> airport = graph.getInformation(port.first);
        double latitude = stod(airport[6]);
        double longitude = stod(airport[7]);
        std::pair<int,int> position = _getXY(latitude,longitude);
        routes.push_back(position);
        _drawAirport(outcome, position);
    }
    for(unsigned long i = 0; i < routes.size(); i++) {
        _drawAirline(outcome,startposition,routes[i]);
    }
    outcome.writeToFile("output/outcome_destination.png");
}
/**
 * @param la: the latitude of airport
 * @param lo: the longitude of airport
 * @return: the pair of x/y posiiton in the picture.
 * given the latitude and longitude of airport, return the position of the airport in the picture
 **/
std::pair<int, int> Draw::_getXY(double la, double lo) {
    //need to be implemented

    int x = 2044/2 + lo/180 * (1022);
    int y = 1022/2 - la/90 * 511;

    return {x,y};
}
/**
 * @param png: the picture we will draw
 * @param start: the position of start airport
 * @param end: the position of end airport
 * draw the airline between the start and end airport
 **/
void Draw::_drawAirline(PNG & png, std::pair<int,int> start, std::pair<int,int> end) {
    int deltaH = abs(end.second - start.second);
    int deltaW = abs(end.first - start.first);
    double coff = (double (end.second - start.second))/(double (end.first - start.first));
    if(deltaH > deltaW) {  //using y to draw 
        if(end.second < start.second) {
            for(int i = 0; i < deltaH; i++) {
                HSLAPixel & pixel = png.getPixel(end.first + i/coff ,end.second + i);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
        } else {
            for(int i = 0; i < deltaH; i++) {
                HSLAPixel & pixel = png.getPixel(start.first + i/coff ,start.second + i);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
        }
    } else {
        if(end.first < start.first) {
            for(int i = 0; i < deltaW; i++) {
                HSLAPixel & pixel = png.getPixel(end.first + i ,end.second + i * coff);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
        } else {
            for(int i = 0; i < deltaW; i++) {
                HSLAPixel & pixel = png.getPixel(start.first + i ,start.second + i * coff);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
        }
    }
}
/**
 * @param png: the picture we will draw
 * @param position: the position of given airport
 * draw the point of airport in the picture
 **/
void Draw::_drawAirport(PNG & png, std::pair<int, int> position) {
    for(int i = -2; i < 3; i++) {
        for(int j = -2; j < 3; j++) {
            unsigned int x = position.first + i;
            unsigned int y = position.second + j;
            if(x >= png.width() || y >= png.height()) {
                continue;
            }
            HSLAPixel & pixel = png.getPixel(x,y);
            pixel.h = 0;
            pixel.s = 1;
            pixel.l = 0.5;
            pixel.a = 1;
        }
    }
}
Draw::~Draw() {
    //dothing
}
