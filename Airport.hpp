#pragma once
#include <string>
#include <vector>
using namespace std;

class Airport {
            /* data */
        private:
        int uniqueID;                                                   //Unique OpenFlights identifier for this airport.
        string airportName;                                             //Name of airport. May or may not contain the city name.
        string cityName;                                                //Main city served by airport. May be spelled differently from Name.
        string countryName;                                             //Country or territory where airport is located.
        string IATA;                                                    //3-letter IATA code.
        string ICAO;                                                    //4-letter ICAO code.
        double Latitude;                                                
        double Longitude;
        vector<pair<int, int>> destinations;                            //first integer store the targe airport ID, second integer store the number of airline in given route 
        public:
        Airport() {}
        Airport(int id, string airport, string city, string country, string iata, string icao, double latitude, double longitude)
         : uniqueID(id), airportName(airport), cityName(city), countryName(country), IATA(iata), ICAO(icao), Latitude(latitude), Longitude(longitude) {}
        vector<pair<int, int>>  getDestinations(){return destinations;}
        void addAirlines(int airline){
            for(pair<int, int> & check : destinations) {
                if(airline == check.first) {
                    check.second++;
                    return;
                }
            }
        destinations.push_back({airline,1});
        }
        double distance;
        int LastNode;
        bool isTravel;
        int getUniqueID() {return uniqueID;}
        string getAirportName() {return airportName;}
        string getCityName() {return cityName;}
        string getCountryName() {return countryName;}
        string getIATA(){return IATA;}
        string getICAO() {return ICAO;}
        double getLatitude() {return Latitude;}
        double getLongitude() {return Longitude;}
        long double PR_value = 0.0;
        int total_lines = 0;
};