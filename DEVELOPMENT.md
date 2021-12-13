# Development Log
## Nov. 21st
#### OpenFlights dataset cleaning and filtering: Airports_data
This week, we have been focusing on the OpenFlights dataset cleaning and filtering. Current progress:  
 - Created "data" folder  
The "data" folder will store any data we will use throughout the project, such as *airports.dat.txt*, *airports_data.csv*, and *airports_data_useful.csv*. It currently also contains openflights_data_filter.py.  
 - Created *openflights_data_filter.py*  
The *openflights_data_filter.py* uses the Python module "Pandas" to generate csv files from txt files downloaded from OpenFlights dataset. Currently focusing on the airports dataset cleaning and filtering, and will include the airlines dataset cleaning and filtering. The following csv files are files generated from *openflights_data_filter.py*:  
    1. *airports_data.csv*:  
    The csv file from *airports.dat.txt*. Contains original airports data.  
    2. *airports_data_NaN_city.csv*:  
    Every data (row) with city as NaN.  
    3. *airports_data_useful.csv*:  
    A subset of *airports_data.csv*. Contains only the Airport ID, Name, City, Country, IATA, ICAO, Latitude, and Longitude.  
    4. *airports_data_useful_null_IATA.csv*:  
    Every data (row) with IATA as NULL (which is \N in *airports_data_useful.csv*).  
    5. *airports_data_useful_null_ICAO.csv*:  
    Every data (row) with ICAO as NULL (which is \N in *airports_data_useful.csv*).  
 - Notes
    1. The largest airport ID is 14110, but there are only 7698 rows/airports (original data).  
    2. The only column with NaN is City. Reason: most of these data represent military bases. We will consider removing these data, as they are irrelevant with our project goals.  
    3. There is only one row that has ICAO as NULL, which is "Sun Island Resort and SPA". We will consider removing this data, as it seems to not have an airport in reality.  
    4. We will check all data with Names that do not end with "Airport", to see if they are truly airports.  
## 

## Nov. 26th
#### Graph Constructor, Makefile, and Testcase  
This week, we have finished the first part of the graph constructor, especially converting the *airports.csv* file into the inner Airport struct and storing it into an unordered map, creating a Makefile, and writing several test cases. We also separated the test, object, header, and source files into different folders. Before the next meeting, we need to finish the whole constructor, building the graph of vertexs(airports) and edges(airlines).
 - Unordered map  
    1. We decided to use an unordered map mainly because the airport ID is not successive.  
    2. the BigO of unordered map find is O(1).  
 - Vector of pairs to store destination  
    1. Because we want to implement a weighted directed map, we have decided to use __vector<pair<int, int>>__ in Airport struct.  
    2. The first integer represents the destination Airport ID.  
    3. The second integer represents the number of airlines from the current source airport to the destination airport.  
 - MakeFile  
    1. We used clang++ and c++11 first and will change them into c++20 in the future.  
 - Testcase:  
    1. We finished the graph's inner function getInformation and getSize to test if we could correctly convert each line of the csv's into Airport struct.  
#### OpenFlights dataset cleaning and filtering: Airports_data
 - Created "airports-data" folder  
The "airports-data" folder will store any data related to airports dataset or generated from *openflights_airport_data_filter.py*.  
 - Renamed *openflights_data_filter.py* to *openflights_airport_data_filter.py*  
 - Moved previous airport-related filtered data into the "airports-data" folder  
 - Generated new filtered airports data files  
    1. *airports_data_useful_nonAirport.csv*:  
    All data (rows) that do not contain the string "Airport" in "Name". The airport data in this file are mostly airbases, military air stations, airstrips, heliports and so on, which are not related to our project goals.  
    2. *airports_data_useful_nonAirport_improved.csv*:  
    An improved version of *airports_data_useful_nonAirport.csv*. A further filtering.  
    3. *airports_data_useful_drop_city_ICAO.csv*:  
    Data (rows) that drop NaN cities and \N ICAOs. This is a subset of *airports_data_useful.csv*.  
    4. __*airports_data_useful_drop_city_ICAO_nonAirport.csv*__:  
    Data (rows) that drop NaN cities, \N ICAOs, and non "Airport" names. This is a subset of *airports_data_useful.csv*, and will currently be the filtered airports data file we will use in the future.  
#### OpenFlights dataset cleaning and filtering: Airlines_data
 - Created "airlines-data" folder  
The "airlines-data" folder will store any data related to airlines dataset or generated from *openflights_airline_data_filter.py*.  
 - Created *openflights_airline_data_filter.py*. The following csv files are files generated from *openflights_data_filter.py*:  
    1. *airlines_data.csv*:  
    The csv file from *airlines.dat.txt*. Contains original airlines data.  
    2. *airlines_data_NaN.csv*:  
    All data (rows) that have NaN.  
    3. __*airlines_data_useful.csv*__:  
    A subset of *airlines_data.csv*. Contains only the Airline ID, Name, Country, and Active. This will currently be the filtered airlines data file we will use in the future.  
    4. *airlines_data_useful_NaN.csv*:  
    Contains all data from *airlines_data_useful.csv* that have NaN.  
    5. *airlines_data_useful_drop_NaN.csv*:  
    Drops any data with NaN in *airlines_data_useful.csv*.  
#### OpenFlights dataset cleaning and filtering: Routes_data
 - Created "routes-data" folder  
The "routes-data" folder will store any data related to routes dataset or generated from *openflights_route_data_filter.py*.  
 - Created *openflights_route_data_filter.py*. The following csv files are files generated from *openflights_data_filter.py*:  
    1. *routes_data.csv*:  
    The csv file from *routes.dat.txt*. Contains original routes data.  
    2. *routes_data_codeshareY.csv*:  
    All data (rows) that have Codeshare as "Y".  
    3. *routes_data_stops1.csv*:  
    All data (rows) that have Stops greater than 0. Here we discover that all of the data in this file have Stops being 1.  
    4. *routes_data_stops0.csv*:  
    A subset datafile of *routes_data.csv*, where we only contain data that have Stops as 0.  
    5. *routes_data_useful_stops0.csv*:  
    A subset datafile of *routes_data_stops0.csv*, where we drop the Codeshare, Stops, and Equipment column.  
 - Notes
    1. When we were processing *routes_data.csv*, we found that all NaN Codeshare do not influence the whole routes calculation and result, so we dropped the Codeshare column.  
    2. The Equipment column only represents the airplane model, which has nothing to deal with route calculation, so we dropped the Equipment column.   
    3. For the stop column in the routes.csv, we filtered all the rows whose stops are greater than 0. If we kept the routes whose stops are greater than 0, we cannot calculate the routes length in total without given the specific location of the stops. Also, it is unrealistic if we do not consider the time taken of each route.  
    4. We will work on dropping the data (rows) whose airport id is \N since the null airport id would not help us find specific airport node.  
##

## Nov. 27th  
#### Graph Constructor, Destructor, and helpfuction  
We decided to use the pointer to store the data in the map. 
 - Constructor:Using data from Routes, we connect each airports with weights using vector<pair<int, int>>.
 - Destructor: we delete all the Airports node, and there is no memory leak after we build the destructor.
 - Help function: finish getAirline which get the information of airports ID and put them into the node airports as edges. Polished getAirline function by detecting not find before adding new destinations for each airport.
##

## Nov. 28th  
#### Constructor and Testcase
We fix the constructor, and provide more information in getInformation
 - constructor: fix line 61 to make the right if statement.
 - getInformation: add the airlines information, including the airport id of target airports, the number of routes.
 - Finished tesecase of graph constructor by checking graph's size and airport ID 2 and airport 2972's destinations.


##

## Nov. 30th  
#### Dijkstra Algorithm
We implement Dikstra Algorithm to calculate the shortest path between two path.
 - using priority_queue to store the order of node that will be visited
 - distance: the distance between the start point and given node
 - is_Traval: check whether the node being visited
 - LastNode: store the lastnode depend on the shortest path
 - _findDistance, _fakeDistance, and _rad are the help fuction to calculate distance
 - _setInitial are the help function to set the data

##


## Dec. 2th  
#### Traversal  
We use the Depth-First_Search and recursion as the basis for our traversal  
 - use a vector<bool>& visited to store all the visited airports  
 - getEdges(int srcID) to get the edges given the uniqueID of the source airport  
 - adjacentMatrix: use this adjacent matrix to see if two airports are adjacent to each other directly  
 - bool ifAdjacent: to see if two airports(given by the unique source ID and destination ID) are adjacent

## 

## Dec. 3rd  
#### Modified Dijkstra's Algorithm
We modified our implementation of Dijkstra's Algorithm such that it correctly calculates the shortest path between two airports.  
 - Graph::Dijkstra returns a vector<int>, where int represents the airport id of the airport nodes.  
 - Changed getInformation(); will return information of airports as a vector<string>.  
 - Added test cases, tested edge cases of Dijkstra's Algorithm, and checked whether the paths are deterministic or not.  
 
##
## Dec. 9th
#### PageRank
 We implemented the PageRank Algorithm and trying to find the most important airports. Since we need more than 50 times iteration to traverse the airports and edges, we decided to use a matrix implemented by unordered map to store all destinations for each airports.
 - Rank Leak and Rank Sink: Because many airports from the data file have no in-links or out-links, even both of them, which will cause Rank Leak and Rank Sink, we need to find an approach to solve these problems. After serious consideration, we decided to remove the airports with no in-links and out-links in the airport file. An airport with no in link means there are no routes' destinations is this airport, and an airport with no out link means there is no routes' source airport is this airport. We think both of these circumstances are caused by a lack of data. We do not want to rank airports' importance by data with problems, so we filtered these data before we did the page rank.
 - Normalization: After each iteration, the sum of page rank numbers will decrease or increase unstable, so we decided to normalize each airport's page rank value by page rank value/page rank-sum to keep the probability space to be 1.
 - Output: Since finishing running the PageRank algorithm might take a long time, and the size of the airports file is large, we decided to save the output (airports name with importance) as a CSV file, which is also easy for future data analysis use.
#### Graph Visualization
 
##
## Dec. 11th
#### Fixed makefile
 Each group member developed locally in previous development, but we met linker problems when running our program on ews. We then decided to utilize the cs225 makefile template for the makefile. We divide our program into main and test. The test is for locally testing, while the main file is what users will run.
#### Main
#### BFS_all traverse
