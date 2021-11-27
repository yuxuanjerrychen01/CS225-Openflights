# Development Log
## Nov. 21st
#### OpenFlights dataset cleaning and filtering
This week, we have been focusing on the OpenFlights dataset cleaning and filtering. Current progress so far:  
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
This week, we have finished the first part of the graph constructor, especially converting the airports.csv file into the inner airport struct and storing it into an unordered map, Makefile, and several test cases. We also separated the test, object, header, and source files into different folders.
 -Unordered map
    1. We decided to use an unordered map mainly because the airport ID is not successive, and the BigO of unordered maps find is O1.
 -Vector of pairs to store destination
    1. Because we want to implement a weighted directed map, we decided to use vector<pair<int, int>> in airport struct to store destinations and the number of airlines with the same source airports and destination airports.
 -MakeFile
    1. We used clang++ and c++11 first and will change them into c++20 in the future
 -Testcase
    1. We finished the graph's inner function getInformation and getSize to test if we correctly convert each line of the cvs into struct airport.
  
Filtered file routes.csv:
    1. For the codeshare and equipment in the routes.csv, When we are processing routes, we found that all NaN codeshare do not influence the whole route calculation and result, so we dropped this column. Also, the equipment only represent the physical plane used, which has nothing deal with route calculation and we dropped this column also. 
    2. For the stop column in the routes.csv, we filtered all the rows whose stops are greater than 0. We did this since if we keep the routes whose stops are greater than 0, we cannot calculate the routes length in total without given the specific location of the stops. Also, it is unrealistic if we do not consider the time taken of each route. We dropped the row whose airport id is /N since the null airport id would not help us find specific airport node.
