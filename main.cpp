// main.cpp
#include "graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // for atoi
#include "data_structures.h"

// Placeholder for handleInvalidInstruction
void handleInvalidInstruction()
{
    std::cerr << "Invalid instruction.\n";
}

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

    std::ifstream inputFile(inputFilename);
    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open file " << inputFilename << "\n";
        return 1;
    }

    int numVertices, numEdges;
    inputFile >> numVertices >> numEdges;

    Graph graph(numVertices, isDirected);

    for (int i = 0; i < numEdges; i++)
    {
        int start, end, edgeIndex;
        double weight;
        inputFile >> edgeIndex >> start >> end >> weight;

        // Assuming that vertices in the input file are 1-indexed and need to be converted to 0-indexed
        graph.addEdge(start - 1, end - 1, weight, flag);
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
            // Implement your SinglePair shortest path function here
        }
        else if (command == "SingleSource")
        {
            int source;
            std::cin >> source;
            // Implement your SingleSource shortest paths function here
        }
        else if (command == "PrintLength")
        {
            int s, t;
            std::cin >> s >> t;
            // Implement the printShortestPathLength function here
        }
        else if (command == "PrintPath")
        {
            int s, t;
            std::cin >> s >> t;
            // Implement the printShortestPath function here
        }
        else
        {
            handleInvalidInstruction();
        }
    }

    return 0;
}
