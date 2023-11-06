// main.cpp
#include "graph.h"
#include "util.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // for atoi

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage: ./PJ3 <InputFile> <GraphType> <Flag>\n";
        return 1;
    }

    std::string inputFilename = argv[1];
    std::string graphType = argv[2];
    int flag = std::atoi(argv[3]);
    bool isDirected = (graphType == "DirectedGraph");

    // Read the graph from the input file and build the adjacency lists
    std::ifstream inputFile(inputFilename);
    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open file " << inputFilename << "\n";
        return 1;
    }

    int numVertices, numEdges;
    inputFile >> numVertices >> numEdges;

    Graph graph(numVertices, isDirected);

    for (int i = 0; i < numEdges; ++i)
    {
        int start, end;
        double weight;
        inputFile >> start >> end >> weight;

        if (flag == 1)
        {
            graph.addEdge(start, end, weight, flag);
        }
    }

    inputFile.close();

    // Now handle stdin for graph manipulation and queries
    std::string command;
    while (std::cin >> command)
    {
        if (command == "Stop")
        {
            break;
        }
        else if (command == "PrintADJ")
        {
            graph.printAdjList();
        }
        else if (command == "SinglePair")
        {
            int source, destination;
            std::cin >> source >> destination;
            // You would need to call your SinglePair shortest path function here
            // For example:
            // graph.singlePairShortestPath(source, destination);
        }
        else if (command == "SingleSource")
        {
            int source;
            std::cin >> source;
            // You would need to call your SingleSource shortest paths function here
            // For example:
            // graph.singleSourceShortestPaths(source);
        }
        else if (command == "PrintLength")
        {
            int s, t;
            std::cin >> s >> t;
            // You would need to print the length of the shortest path between s and t
            // For example:
            // graph.printShortestPathLength(s, t);
        }
        else if (command == "PrintPath")
        {
            int s, t;
            std::cin >> s >> t;
            // You would need to print the shortest path between s and t
            // For example:
            // graph.printShortestPath(s, t);
        }
        else
        {
            handleInvalidInstruction();
        }
    }

    return 0;
}
