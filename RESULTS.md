# Project Results
## Openflights Dataset Cleaning and Filtering Results   
For the OpenFlights Dataset, we wrote three python files to clean and filter airports_data, airlines_data, and routes_data, respectively. We downloaded the corresponding txt files from the OpenFlights Dataset website (https://openflights.org/data.html), used python Pandas library to transform them into csv files, and proceeded to clean and filter them.  
  
<details>
  <summary> <b> Below are some interesting information we discovered while conducting the cleaning and filtering (click to expand) </b> </summary>  

 - __airports_data__
    1. We obtain the subset of airports_data by keeping the columns "Airport ID, Name, City, Country, IATA, ICAO, Latitude, Longitude, Altitude".  
    2. The largest airport ID is 14110, but there are only 7698 rows/airports (original data).  
    3. The only column with NaN is City, and most of these data represent military bases. They are irrelevant with our project goals, and we have removed these data rows.  
    4. There is only one data row that has "ICAO" attribute as NULL, which is "Sun Island Resort and SPA". We have removed this data, as it does not have an airport in reality.  
    5. We have removed all airports data with "Name" not containing the word "Airport", as nearly all of these data are military bases, heliports, etc.  
    6. There were no duplicates in the original data.  
 - __airlines_data__
    1. We obtain a subset of airlines_data by only using the "Airline ID, Name, Country, Active" attributes.  
    2. We removed all data rows that contained "NaN".  
    3. There were no duplicates in the original data.  
 - __routes_data__
    1. For the "Stops" column in the *routes.csv*, we filtered all the rows whose stops are greater than 0. After this filtering, all remaining data have "0" as the "Stops" value, so we deleted the "Stops" column.  
    2. The subset attributes we decided to use are "Airline (IATA or ICAO),Airline ID,Source Airport,Source Airport ID,Destination Airport,Destination Airport ID".  
    3. We dropped the data rows whose airport id is \N since the null airport id would not help us find specific airport node.  
 - __Combination of the three filtered data__
    1. We discovered that there exists airports data in the *airports_data_final.csv* where they do not have any corresponding routes data in *routes_data_final.csv*. In other words, there were some airports that are neither source airports or destination ariports. Relating to our graph structure, these data would have no effect on any functions we were implementing, take up space, and even affect our PageRank Algorithm implementation. We therefore deleted these airports data from the *airports_data_final.csv*, creating a new file named *airports_data_final_new.csv*.  
    2. The new airports data file contains 3052 different airports, all which are either source ariports or destination airports.  

 </details>
 
## Algorithm Results  
We previously have set up 4 main algorithm goals to accomplish (GOALS.md). We have successfully accomplished all 4 algorithms. The following are the results and interesting discoveries.  
### BFS Traversal  

Our BFS traversal implementation consists of two functions, namely *BFS_all()* and *BFS_all_helper()*. Given an airport ID as the input, *BFS_all* will output a txt file of airport traverses starting with the given input airport.  

<details>
  <summary> <b> <i> BFS_all() </i> code implementation (click to expand) </b> </summary>
  
  ```
 vector<string> Graph::BFS_all(int source_airport) {
    vector<string> output;
    if (airports.find(source_airport) == airports.end()) {
        std::cout << "Nonexisting airport ID." << std::endl;
        output.push_back("Nonexisting airport ID");
        return output;
    }
    vector<string> temp;

    _setInitial();
    queue<int> queue;
    temp = BFS_all_helper(source_airport, queue);
    for (auto str : temp) {output.push_back(str);}

    for (auto it : airports) {
        if (it.second -> isTravel == false) {
            temp = BFS_all_helper(it.first, queue);
            for (auto str : temp) {output.push_back(str);}
        }
    }
    
    ofstream fts("./output/BFS_traversal.txt");
    for (auto str : output) {
        fts << str << endl;
    }
    return output;
 }
  ```
 
 </details>
 
<details>
  <summary> <b> <i> BFS_all_helper() </i> code implementation (click to expand) </b> </summary>
  
  ```
 vector<string> Graph::BFS_all_helper(int airport_id, queue<int> queue) {
    vector<string> output;

    queue.push(airport_id);
    int current_airport = airport_id;
    if(airports.find(airport_id) != airports.end()){
        airports[airport_id] -> isTravel = true;
        
        while(!queue.empty()) {
            current_airport = queue.front();
            Airport * airport_temp = airports[current_airport];
            output.push_back(airport_temp->getAirportName());
            
            for(auto id : airport_temp->getDestinations()) {
                if(airports[id.first] -> isTravel == false) {
                    queue.push(id.first);
                    airports[id.first] -> isTravel = true;
                }
            }
            queue.pop();
        } 
        
    }
    return output;
 }
  ```
 
  </details>  
  

The function *BFS_all_helper()* is a helper function with the goal of obtaining all connected airports (vertices) of a specific airport using Breadth First Search. We call *BFS_all_helper()* multiple times to make sure all airports have been signaled as travelled, since the airport-airline graph data structure is a multiple-component graph structure.  
  
The running time of *BFS_all()* is O(M + N), where M is the number of edges (valid routes), and N is the number of vertices (valid airports). The input for this traversal algorithm will be a source airport ID, and the output will be in txt file with every airport generated from the BFS traversal. The output will be stored as "./output/BFS_traversal.txt".  

In the provided test case, we have checked that this BFS traversal implementation indeed traverses all airports (vertices).  
  
<details>
  <summary> <b> Here is an example of running this algorithm in <i> main() </i> function (click to expand) </b> </summary>  

  ```
  Hello! This is SPYE01000001 OpenFlights Data Analysis.
  get airport information -- enter 1.
  get shortest path between two airports -- enter 2.
  get important airports txt -- enter 3.
  get traversal txt -- enter 4.
  graph visualization of shortest path -- enter 5.
  graph visualization of destinations -- enter 6.
  4
   
  Enter airport ID: 
  3406
   
  The traversal information has been stored as ./output/BFS_traversal.txt
  ```
  This is the example output txt file, where Shanghai Pudong International Airport is at line 1, and Gobernador Castello Airport is at line 3052.  
  ```
  Shanghai Pudong International Airport
  Chongqing Jiangbei International Airport
  Chengdu Shuangliu International Airport
  ...
  ...
  Ovda International Airport
  Aviador C. Campos Airport
  Gobernador Castello Airport
  ```
  </details>  
  
  
### Dijkstra's Algorithm  
Our implementation of Dijkstra's Algorithm takes in a source airport ID and a destination airport ID, calculates the shortest paths needed for one to travel from the source airport to the destination airport, and outputs a vector containing all of the airport IDs of the shortest path.  

<details>
  <summary> <b> <i> Dijkstra() </i> code implementation (click to expand) </b> </summary>  
 
  ```
 vector<int> Graph::Dijkstra(int start1, int end1) {
    vector<int> paths;
    if ((getInformation(start1).size() == 1) || (getInformation(end1).size() == 1)) {
        paths.push_back(-1);
        return paths;
    }

    if(start1 == end1) {
        paths.push_back(start1);
        return paths;
    }

    vector<Airport *> outcome; 
    priority_queue<pair<double, Airport*>, vector<pair<double, Airport*>>, std::greater<pair<double, Airport*>>> check;
    _setInitial();
    Airport * start = airports[start1];
    start->distance = 0;
    start->LastNode = -1;
    check.push({0.0,start});
    while (!check.empty()) {
        Airport * airport = check.top().second;
        check.pop();
        airport->isTravel = true;
        for(pair<int, int> & target : airport -> getDestinations()) {
            Airport * targetPort = airports[target.first];
            if(!targetPort->isTravel) {
                double curDistance = _findDistance(airport->getUniqueID(), target.first) + airport->distance;
                if (targetPort->distance > curDistance) {
                    targetPort->distance = curDistance;
                    check.push(pair<double, Airport*> (curDistance,targetPort));
                    targetPort->LastNode = airport->getUniqueID();
                }
            }
        }
    }
    
    Airport * end = airports[end1];
    if(end->distance == -1) {
        cout << "no connection between two airports" << endl;
    } else {
        Airport * curAirport = end;
        while (curAirport->LastNode != -1) {
            outcome.push_back(curAirport);
            curAirport = airports[curAirport->LastNode];
        }
        paths.push_back(start1);
        for(int i = outcome.size() - 1; i >= 0; i--) {
            paths.push_back(outcome[i]->getUniqueID());
        }
    }
    return paths;
 }
  ```
 
</details>  
   

### PageRank Algorithm
    1. code  
 
 
### Graph Visualization
    1. code  

### Leading Question Results  
We
