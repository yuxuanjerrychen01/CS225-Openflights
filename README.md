# CS225 Fall 2021 Final Project -- OpenFlights Data Analysis
## Team SPYE01000001  
## Team members: Yuxuan Chen, Kangyu Feng, Ruozhen Yang, Xueqiang Xu

### Code Introduction  
This is a project focused on the data analysis of OpenFlights dataset (https://openflights.org/data.html).  
 - __Airport.hpp__  
The Airport Class, containing all necessary information obtained from airports_data, and is part of the main graphs structure.    
 - __Graph.hpp, Graph.cpp__  
The main graphs structure, connects the airports_data, airlines_data, and routes_data. Contains implemented function *getInformation()*, implemented least distance algorithm *Dijkstra()*, implemented BFS traversal *BFS_all()*, and implemented importance airports function *pagerank()*.  
 - __Draw.hpp, Draw.cpp, Equirectangular_projection_SW.png__  
The main graph visualization structure. Allows user to draw least distance paths onto a world map using *drawDijkstra()*, and draw destination airports given a source airport using *drawDestinations()*. The *Equirectangular_projection_SW.png* provides source background world map.  
 - __Main.cpp__  
Allows user interaction. Contains 5 main implemented methods for users to select:  
    1. Given an airport ID from user, get airport information  
    2. Given source airport ID and destination airport ID from user, get shortest path between the two airports  (Dijkstra's Algorithm)  
    3. Given tolerance and iteration from user, get a rank of importance of airports  (PageRank)  
    4. Given a starting airport ID from user, get a list of BFS traversed airports  (BFS Traversal)  
    5. Given source airport ID and destination airport ID from user, get graph visualization of shortest path between the two airports  
    6. Given an airport ID, get graph visualization of destinations for that airport  
 - __./data folder__  
Contains all filtered data from airports_data, airlines_data, and routes_data. Contains the final data used in this project. Contains python files portraying each filtering step we took.  
 - __./tests folder__  
Contains test cases. Users may add their own test cases if they wish to do so.  
 - __./output folder__  
The folder where all output files are stored, including any graph png visualizations, PageRank importance txt, and BFS Traversal txt.  

### Project Build and Description
This project can be built and run in EWS. To build and run this project in EWS, run code:  
```
$ make  
$ ./main  
```
If this is your first time building the project in EWS, run code:  
```
$ module load llvm/6.0.1
$ make
$ ./main
```
When compiled successfully, the following sentences will appear on the terminal:  
```
Hello! This is SPYE01000001 OpenFlights Data Analysis.
get airport information -- enter 1.
get shortest path between two airports -- enter 2.
get important airports txt -- enter 3.
get traversal txt -- enter 4.
graph visualization of shortest path -- enter 5.
graph visualization of destinations -- enter 6.
```
The user may choose which path to proceed by entering the corresponding number (1 to 6) on the terminal and hitting enter. Assuming the user is interested about obtaining a world map of the shortest path from Shanghai Pudong International Airport (ID 3406) to Ha'il Airport (ID 2069), the user would enter:  
```
5
```
The following sentence the appear on the terminal:  
```
Enter source airport ID:
```
The user would then enter:
```
3406
```
The following sentence will then appear on the terminal:  
```
Enter destination airport ID:
```
The user would then enter:  
```
2069
```
The computer will then begin drawing the graph visualization the user is interested about. After code computation, the user will see the following sentence:  
```
The graph visualization has been stored as ./output/outcome_dijkstra.png
```
The user will find the completed graph stored in ./output file, and named as *outcome_dijkstra.png*.  
![example1](https://github-dev.cs.illinois.edu/cs225-fa21/ruozhen2-xx19-kangyuf2-yuxuan19/blob/main/output/example_dijkstra_3406to2069.png)  
This is just a simple example of what the user can obtain from our project code. Check our __RESULTS.md__ for more examples.    
Here is another graph visualization example:
```
Hello! This is SPYE01000001 OpenFlights Data Analysis.
get airport information -- enter 1.
get shortest path between two airports -- enter 2.
get important airports txt -- enter 3.
get traversal txt -- enter 4.
graph visualization of shortest path -- enter 5.
graph visualization of destinations -- enter 6.
6
 
Enter airport ID:
3406
 
The graph visualization has been stored as ./output/outcome_destination.png
```
![example2](https://github-dev.cs.illinois.edu/cs225-fa21/ruozhen2-xx19-kangyuf2-yuxuan19/blob/main/output/example_destination_3406.png)  

### Test Cases  
To build and run the provided test cases, run code:
```
$ make test
$ ./test
```
 - __Graph Construction test cases__  
Tests valid graph construction, checks that airport destinations are correctly added.  
 - __Dijkstra's Algorithm test cases__  
Tests correctness of the Dijkstra's Algorithm implementation. Checks whether least distance paths are deterministic, checks direct flight paths, checks nonexistent airport IDs.  
 - __Airports Information test cases__  
Tests correctness of the function *getInformation()*. Checks nonexistent airport IDs, checks information of specific airports.  
 - __BFS Traversal test cases__  
Tests correctness of BFS traversal implementation. Checks size of BFS output, checks nonexistent airport IDs.  
