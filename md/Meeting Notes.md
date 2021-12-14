# Weekly Meeting Notes
## Nov. 16th
#### Data preparation
-Data cleaning &nbsp; &nbsp; &nbsp; &nbsp; -duplicates &nbsp; &nbsp; &nbsp; &nbsp; -inconsistent  &nbsp; &nbsp; &nbsp; &nbsp; -dictionary  &nbsp; &nbsp; &nbsp; &nbsp; -missing/NA &nbsp; &nbsp; &nbsp; &nbsp; -optimal dated data  &nbsp; &nbsp; &nbsp; &nbsp; -outlier detection
#### on Jupyter, colab(API: pandas, numpy)
#### Datasets used
Airports: airport_id, city, country, latitude, longitude, IATA, ICAO  
Airlines: airline_id, airline_name, country  
#### Text file -> Data frame/excel/CSV(using c++ or SQL to solve proficiency problem)

## Nov. 23rd
#### What we still need to do
	Graph Constructor: 
	(1) Try Catch (Make sure input files are correct format)
	(2) Combine Route, Airline, and Airport data together to finish the construction of directed graph. Change getAirline function to a helper function for the constructor
	(3) Add more features to the inner struct Airport, like latitude and longitude
	(4) Change the passing argument of the Graph constructor from vector to file names
	Data Cleaning and Data Prep
#### Assignment before next Meeting:
	Kangyu and Patrick: finish the Directed Graph constructor 
	Yuxuan and Ruozhen: finish the data cleaning and prep
	Everyone should be familiar with each data file

## Nov. 26th
#### Graphs data structure
 - Use "new" on Airports struct  
 - include destructor  
 - change destination to vector<pair<int,int>>  
 The first int will represent destination airport ID, and the second int will be the number of paths from source airport to destination airport.
  - Consider airlines dataset in the future
#### Data filtering
 - finish routes_data filter  
remove \N data (rows) of *routes_useful_stops0.csv*.

## Dec. 9th
#### PageRank current problems
 - Complexity (too slow)   
 - PR value too small (edit: fixed, changed divison into double)  
 - May consider using matrix multiplication  
 - There are 3631 airport data with no source airport ID and destination airport ID in airlines_data_final.csv  
#### Notes and Goals
 - do a new airports filter  
 - continue with test cases  
 - We have finished dfs traversal, dijkstra's algorithm, currently working on PageRank, done graph visuals  
 - makefile and main  
