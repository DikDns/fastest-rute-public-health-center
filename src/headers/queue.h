#ifndef QUEUE_H_clwzqjreq00000cmd674n4lht
#define QUEUE_H_clwzqjreq00000cmd674n4lht

#include <string>
#include <vector>
#include "graph.h"

// Struct to represent a queue
struct Queue
{
  std::vector<Graph> graphs;

  // Method/Function to add a graph to the queue
  void addGraph(const Graph &graph) { graphs.push_back(graph); }

  // Method/Function to remove first graph from the queue
  void removeGraph() { graphs.erase(graphs.begin()); }
};

#endif // QUEUE_H_clwzqjreq00000cmd674n4lht