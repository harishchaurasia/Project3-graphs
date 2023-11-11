// main.cpp

#include "main.h"
#include "graph.h"
#include "data_structures.h"
#include "heap.h"
#include "util.h"
#include "graph.h"
#include "stack.h"
#include <iostream>
#include <fstream>
#include <cstdlib> // for atoi
#include <string>
#include <vector>
#include <limits>

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

    // returning number of vertices and edges
    int numVertices, numEdges;
    inputFile >> numVertices >> numEdges;

    Graph graph(numVertices, isDirected);

    for (int i = 0; i < numEdges; ++i)
    {
        int edgeIndex, start, end;
        double weight;
        inputFile >> edgeIndex >> start >> end >> weight;
        graph.addEdge(start, end, weight, flag);
    }
    inputFile.close();

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
            // This will compute the path from source to destination.
            graph.SinglePair(source, destination);
        }
        else if (command == "SingleSource")
        {
            int source;
            std::cin >> source;
            graph.SingleSource(source); // This should compute paths from source to all vertices.
        }
        else if (command == "PrintLength")
        {
            int s, t;
            std::cin >> s >> t;
            graph.printLength(s, t);
        }
        else if (command == "PrintPath")
        {
            int s, t;
            std::cin >> s >> t;
            graph.printPath(s, t);
        }

        else
        {
            handleInvalidInstruction();
        }
    }

    return 0;
}
