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
