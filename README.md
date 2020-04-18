# Ford-Fulkerson Algorithm for Maximum Flow

Implementation of Ford-Fulkerson algorithm to find Maximum Flow and its application in Minimum Cut and Bipartite Graph Matching problems

## Algorithm 

* [Ford–Fulkerson Algorithm](https://en.wikipedia.org/wiki/Ford%E2%80%93Fulkerson_algorithm) with runtime *O(Ef)*

where E = number of edges in the given graph, f = maximum flow in the graph

## Results on Bipartite Graphs for Matching Problem
The datasets for large graphs have been taken from [this](http://konect.uni-koblenz.de/networks/) page.

dataset|num_verts|num_edges|time (μs)|ans
-|-|-|-|-
brunson_southern-women|10|14|632|5
opsahl-southernwomen|32|89|1857|14
moreno_crime_crime|1380|1476|1124792|451
opsahl-collaboration|38741|58595|1106549523|12652

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