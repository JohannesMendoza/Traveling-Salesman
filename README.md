This is a C++ Application that will solve the Traveling Salesman Problem through the use of a genetic algorithm.

The prompt for the problem is as follows: given a list of cities, and the distances between each, find the sequence in which you can travel through each city exactly one time, and end back up at the city you started in.
For this particular problem, I have created an adjacency matrix of this instance's parameter

-   2   11  3   18  14  20  12  5
2   -   13  10  5   3   8   20  17
11  13  -   5   19  21  2   5   8
3   10  5   -   6   4   12  15  1
18  5   19  6   -   12  6   9   7
14  3   21  4   12  -   19  7   4
20  8   2   12  6   19  -   21  13
12  20  5   15  9   7   21  -   6
5   17  8   1   7   4   13  6   -



The AI will implement a genetic algorithm that will take many possible sequences