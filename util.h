// util.h
#ifndef UTIL_H
#define UTIL_H

#include "graph.h"
#include <iostream>

void dijkstra(const Graph &graph, int source);
void printPath(const Graph &graph, int source, int destination);
void printLength(const Graph &graph, int source, int destination);
void handleInvalidInstruction();
double getEdgeWeight(const Graph &graph, int source, int destination);

#endif // UTIL_H
