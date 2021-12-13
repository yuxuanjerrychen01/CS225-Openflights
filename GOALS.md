## Project Goals
### General
Our group selected OpenFlights as our dataset, which covers Airport IDs, Cities, Countries, airlines, routes, longitude, latitude, and so on. Therefore, we believe that by knowing the starting point and the destination, we can solve potential routes that consist of the least distances and create a world map that has the demonstration of different routes.

With these in mind, we decide to implement a BFS traversal that traverses all potential airports, Dijkstra’s Algorithm for determining the least distance routes between destinations, a Pagerank algorithm for determining popular airports and destinations, and a world graph visualization portraying airline routes.

### Data Acquisition and Processing
 - __Dataset__  
OpenFlights (https://openflights.org/data.html). In specific, we will use airports, airlines, and routes dataset as supports for our project, with routes dataset as the connection of the three datasets.  
 - __Download__  
We will download all of the useful datasets from the OpenFlights website and store them in a CSV document type.  
 - __Process__  
When processing our data, the primary programming language we will use is Python, specifically its libraries NumPy, Pandas, and SciPy. Since the datasets we obtained are all raw datasets, given different numeric features, we will need to clean all dirty data, remove duplicates, fix structural errors, and handle outdated, incomplete, as well as inconsistent data (null data, NaN data).  We will also need to check the relationship between datasets are logical and consistent.  

### Algorithms
Before we begin with our implementation of algorithms, we will have finished our data filtering and cleaning, and have constructed a working, logical airports data structure and graphs data structure.  
 - __Goal 1: BFS Traversal__  
We will implement a BFS traversal for our graph data structure. We expect the running time of BFS to be O(M + N), where M is the number of edges (valid routes), and N is the number of vertices (valid airports). The input for this traversal algorithm will be a source airport ID, and the output will be in txt file with every airport generated from the BFS traversal.  
 - __Goal 2: Dijkstra's Algorithm__  
We will implement Dijkstra’s Algorithm to find the shortest path between two airports, with distance as the edge weight. Distance between two airports will be calculated using  longitude and latitude data from the airports dataset. For Dijkstra's Algorithm, the input will be two int numbers, the first representing a source airport ID, the second representing a destination airport ID. The output will be a vector containing information of the necessary airport stops between the two specific airport destinations. We estimate the running time of our implementation of Dijkstra’s Algorithm will be O(N^2), where N is the number of vertices.  
 - __Goal 3: PageRank Algorithm__  
We will implement the PageRank algorithm to find the most important airports/destinations. The input will be information on flights and a tolerance scalar, while the output will be a list of airports sorted based on their importance. We expect the running time will be O(N^2), where N is the number of airports when implementing PageRank.  
 - __Goal 4: Graph Visualization__  
We will implement a graph visualization function structure, with functions focusing on outputting the shortest path airports generated from Dijkstra's Algorithm, and the destination airports of a particular airport. We will continue this project as a bonus goal after we finish our first three goals.  

### Leading Questions
By the end of the project deadline, we hope to be able to at least solve the problems listed below, and if possible, solve more interesting problems:
 - __What is the shortest path from one destination (source airport) to another destination (destination airport)?__  
Achieved by correctly implementing Dijkstra's Algorithm.  
 - __What are some of the popular airports/ destinations?__  
Achieved by correctly implementing PageRank Algorithm.
 - __Given an airport ID, what information can I get?__  
Obtained by a well-constructed airports data structure (with getInformation() method).  
 - __What would the shortest path look like on a world map?__  
Obtained by correctly implementing a graph visualization function.  


### Timeline  
This is a general timeline of our project and we will follow this timeline if there are no special cases. Some adjustments may be made according to the current project progress.  
  - __Nov. 15th__  
    1. Focus on the OpenFlights dataset cleaning and filtering  
  - __Nov. 22nd__  
    1. complete the OpenFlights dataset cleaning and filtering  
    2. construct a general code structure (graph class, necessary functions, DFS traversal)  
    3. implement Dijkstra's Algorithm for finding the shortest path of two airports  
  - __Nov. 29th  (Mid-Project Check-in)__  
    1. complete the general code structure, including the BFS traversal function  
    2. complete the implementation of Dijkstra's Algorithm  
    3. complete MakeFile, create some test cases for current algorithms  
  - __Dec 6th (Final Project Draft)__  
    1. complete the PageRank Algorithm of finding the most important airports  
    2. complete main function 
    3. create some test cases for current algorithms  
    4. create a world graph portraying shortest path routes and destination airport information  
  - __Dec. 13th (Final Project Submission)__  
    1. complete a written report of our project, including goals, development, and results  
    2. complete the presentation slides, speech, and video  
    3. any remaining implementation needed when inspecting code  

 

