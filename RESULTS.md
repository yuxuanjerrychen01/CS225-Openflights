## Project Results
### Openflights Dataset Cleaning and Filtering Results   
For the OpenFlights Dataset, we wrote three python files to clean and filter airports_data, airlines_data, and routes_data, respectively. We downloaded the corresponding txt files from the OpenFlights Dataset website (https://openflights.org/data.html), used python Pandas library to transform them into csv files, and proceeded to clean and filter them. Below were some interesting information we discovered while conducting the cleaning and filtering.  
 - __airports_data__
    1. The attributes of airports_data are "Airport ID, Name, City, Country, IATA, ICAO, Latitude, Longitude, Altitude, Timezone, DST, Tz timezone, Type, Source". We obtain the subset of airports_data by removing the attribute columns "Altitude, Timezone, DST, Tz timezone, Type, Source", as they are irrelevant information for our project.  
    2. The largest airport ID is 14110, but there are only 7698 rows/airports (original data).  
    3. The only column with NaN is City, and most of these data represent military bases. They are irrelevant with our project goals, and we have removed these data rows.  
    4. There is only one data row that has "ICAO" attribute as NULL, which is "Sun Island Resort and SPA". We have removed this data, as it seems to not have an airport in reality.  
    5. We have removed all airports data with "Name" not containing the word "Airport", as nearly all of these data are military bases, heliports, etc.  
    6. There were no duplicates in the original data.  
 - __airlines_data__
    1. We obtain a subset of airlines_data by only using the "Airline ID, Name, Country, Active" attributes.  
    2. We removed all data rows that contained "NaN".  
    3. There were no duplicates in the original data.  
 - __routes_data__
    1. When we were processing *routes_data.csv*, we found that "NaN" data from the "Codeshare" column do not influence the whole routes calculation and result, so we dropped the "Codeshare" column.  
    2. The "Equipment" column only represents the airplane model, which has nothing to deal with route calculation, so we dropped the "Equipment" column.  
    3. For the "Stops" column in the *routes.csv*, we filtered all the rows whose stops are greater than 0. If we kept the routes whose stops are greater than 0, we cannot calculate the routes length in total without given the specific location of the stops. Also, it is unrealistic if we do not consider the time taken of each route. After this filtering, all remaining data have "0" as the "Stops" value, so we deleted the "Stops" column.  
    4. The subset attributes we decided to use are "Airline (IATA or ICAO),Airline ID,Source Airport,Source Airport ID,Destination Airport,Destination Airport ID".  
    5. We dropped the data rows whose airport id is \N since the null airport id would not help us find specific airport node.  
 - __Combination of the three filtered data__
    1. We discovered that there exists airports data in the *airports_data_final.csv* where they do not have any corresponding routes data in *routes_data_final.csv*. In other words, there were some airports that are neither source airports or destination ariports. Relating to our graph structure, these data would have no effect on any functions we were implementing, take up space, and even affect our PageRank Algorithm implementation. We therefore deleted these airports data from the *airports_data_final.csv*, creating a new file named *airports_data_final_new.csv*.  
    2. The new airports data file contains 3052 different airports, all which are either source ariports or destination airports.  

### Algorithm Results  
We previously have set up 4 main algorithm goals to accomplish (GOALS.md). We have successfully accomplished all 4 algorithms. The following are the results and interesting discoveries.  
 - __BFS Traversal__  
    1. code  
 - __Dijkstra's Algorithm__  
    1. code  
 - __PageRank Algorithm__
    1. code  
 - __Graph Visualization__
    1. code  

### Leading Question Results  
We
