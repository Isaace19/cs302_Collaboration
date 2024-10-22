Project 04: Path Finding
========================

This project implements a [Dijkstra's Algorithm] to perform rudimentary path
finding on a 2D tile-based map.

To benchmark the dijkstra's algorithm, we used a /usr/bin/time -al to find all the relvant information regarding memory usage and time to complete program in terms of real time, user time, and system time to compute. All results are below.

Results for elapsed time are real time, which is just what we experience the program to take. 


memory usage is grabbed from maximum resident set size used by the 
usr/bin/time -al

| N    | Elapsed Time | Memory Usage |
|------|--------------|--------------|
| 10   |       0.26s  |   1114112kb  |
| 20   |       0.00s  |   1130496kb  |
| 50   |       0.00s  |   1294336kb  |
| 100  |       0.01s  |   1343488kb  |
| 200  |       0.06s  |   1949696kb  |
| 500  |       0.39s  |   5570560kb  |
| 1000 |       1.43s  |   18808832kb |
|------------------------------------|

brief summary of their individual contributions:
Colton Coughlin - Reading in information, printing out infomration, and helped with main algorithm
Isaac - Time and Memory testing, configuring makefile for testing, main algorithm, and class correction. 


1. How did you represent the map as a graph? Explain which graph representation you
   used and how you determined the relationship between vertices include the edges
   and their weights.

   Answer: we created a graph implementation with a node representation in struct node. And than we used a priority queue to store the vertecies

   We used 2D vectors of pairs in order to store distances, and we set those distances to infinity at the start. Than we created a parent data structure in order to hold visited and known nodes. 

2. What is complexity of your implementation of Dijkstra's Algorithm? Explain this
   by describing which data structures you used and how you used them to implement
   path finding.

   Answer: The Running time of a dijkstra's algorithm running on a minimum heap (std::priority queue) is found by taking the number of verticies and the total number of edges. Which in best case is O(ElogV)

   This is because the edge E is processed just once, which is O(E) time. And than inserting the Vertex into the priority queue runs twice  for insertion and deletions. which is O(logV)

   Adding together is O(ElogV)


3. How well does your implementation scale? Explain what effect did N (ie. the
   size of the map) have on the performance of your dijkstras path finding
   component in terms of execution time and memory usage?

   Answer: According to our testing, it scaled pretty well. The running time was fast as we expected, as we did not hit a worst case scenario where V^2 becomes
   an issue. However we did experience that there was a scaling issue of memory being rampantly used according to usr/bin/time -al.

   All tests were performed on a macbook m1 w/ 8gbs of ram. Probably lots of the overhead and CPU/RAM usage was from the compilation, generation of maps, benchmarking, and output writing happening all in one command run-benchmark flag. 

