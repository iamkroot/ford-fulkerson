# Ford-Fulkerson Algorithm for Maximum Flow
Implementation of Ford-Fulkerson algorithm to find Maximum Flow and its application in Minimum Cut and Bipartite Graph Matching problems

## Algorithm 
* [Ford–Fulkerson Algorithm](https://en.wikipedia.org/wiki/Ford%E2%80%93Fulkerson_algorithm) with runtime *O(Ef)*

where *E* = number of edges in the given graph, *f* = maximum flow of the graph

## Results on Graphs for Maximum Flow Problem
The datasets for these graphs are available in /datasets/maxflow folder.

dataset|num_verts|num_edges|time (μs)|ans
-|-|-|-|-
small_graph1|6|10|82|23
small_graph2|8|13|508|26
large_graph|4752|34247|2758163|251

## Results on Bipartite Graphs for Matching Problem
The datasets for these graphs are available in /datasets/bipartite folder.
These datasets have been taken from [this](http://konect.uni-koblenz.de/networks/) page.

dataset|num_verts|num_edges|time (μs)|ans
-|-|-|-|-
brunson_southern-women|10|14|632|5
opsahl-southernwomen|32|89|1857|14
moreno_crime_crime|1380|1476|1124792|451
opsahl-collaboration|38741|58595|1106549523|12652

## Issues in Coding
* Figuring out how to represent Graph as to make it efficient for Ford-Fulkerson was tricky and challenging
* Residual graph implementation was difficult

## General Discussion on Ford-Fulkerson Algorithm
[Maximum Flow](https://en.wikipedia.org/wiki/Maximum_flow_problem) is a very well known problem in the world of Computer Science. Ford-Fulkerson Algorithm is a greedy algorithm that computes this maximum flow in a flow network. The name "Ford–Fulkerson" is often used for the [Edmonds–Karp algorithm](https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm), which is a fully defined implementation of the Ford–Fulkerson Algorithm. 

The idea behind the algorithm is as follows: as long as there is a path from the source (start node) to the sink (end node), with available capacity on all edges in the path, we send flow along one of the paths. Then we find another path, and so on. A path with available capacity is called an augmenting path. 

Assuming the capacities to be integers provides a very intuitive view of the problem and the beauty of this algorithm, which suprisingly runs in polynomial time, can be fully appreciated.

## Time Analysis of Ford-Fulkerson Algorithm
Let *E* = number of edges in the given graph, *V* = number of nodes in the given graph and *f* = maximum flow of the graph
* The while loop runs for at most *f* iterations
* For each iteration -
  * As we have used Adjacency-List to represent the Graph, finding a path P using BFS takes *O(V+E)* time i.e. *O(E)* 
  * Agument takes *O(V)* as it goes over at most *V-1* edges
  * Constructing a new residual graph takes *O(E)*
  
Thus, overall time complexity is *O(Ef)*

## References
* [Original Paper by L. R. Ford, Jr. and D. R. Fulkerson](http://www.cs.yale.edu/homes/lans/readings/routing/ford-max_flow-1956.pdf)
* [Introduction to Algorithms](https://en.wikipedia.org/wiki/Introduction_to_Algorithms) (CLRS) pg. 651–664
* [Algorithm Design](https://www.cs.princeton.edu/~wayne/kleinberg-tardos/pdf/07NetworkFlowI.pdf)

## Running
### Main
The project uses a cmake build system and targets C++ 20. After compilation using cmake, the executable can be run from the terminal:
```
Usage:
ford_fulkerson [maxflow|maxmatch] DATASET_PATH [DATASET_PATH...]

maxflow -       For each graph, find the maximum flow from source to sink and print the flow in each edge to stdout
mincut -        For each graph, find a partition of its vertices which minimizes total weight of edges between them and print the two sets to stdout
maxmatch -      For each bipartite graph, find the maximum matching and print the matching to stdout

DATASET_PATH -  Should be a path (no spaces) to a file containing details of the directed graph.
        For maxflow or mincut:
                        The first line of the file should have: numberOfEdges sourceVert sinkVert
                        The following numberOfEdges lines should have the edges from A to B in the form: fromVert toVert capacity

        For maxmatch:
                        The first line of the file should have: numberOfEdges numberOfVerticesInA numberOfVerticesInB
                        The following numberOfEdges lines should have the edges from A to B in the form: vertInA vertInB
                        where 1 <= vertInA <= numberOfVerticesInA and 1 <= vertInB <= numberOfVerticesInB
```

## Authors
1. 2017A7PS0184H Krut Patel
2. 2017A7PS0130H Niral Khambhati
3. 2017A7PS1722H Arnav Buch
4. 2017A7PS0137H Shantanu Gupta