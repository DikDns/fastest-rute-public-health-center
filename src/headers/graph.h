#ifndef GRAPH_H_clwzpelo800010cjq4k4f6m0k
#define GRAPH_H_clwzpelo800010cjq4k4f6m0k

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

const long long unsigned int INFINITY = LONG_LONG_MAX;

// Struct to represent a vertex in a graph
struct Vertex
{
  std::string district;
  std::string urbanVillage;
  std::string publicHealthCenter;

  // Constructor Function to initialize the vertex
  Vertex(const std::string &district, const std::string &urbanVillage, const std::string &publicHealthCenter)
      : district(district), urbanVillage(urbanVillage), publicHealthCenter(publicHealthCenter) {}
};

// Struct to represent an edge in a graph
struct Edge
{
  Vertex *firstVertex;
  Vertex *secondVertex;
  long long unsigned int distance;

  // Constructor Function to initialize the edge
  Edge(Vertex *firstVertex, Vertex *secondVertex, long long unsigned int edgeDistance)
      : firstVertex(firstVertex), secondVertex(secondVertex), distance(edgeDistance) {}
};

// Struct to represent a graph
struct Graph
{
  std::vector<Vertex *> vertices;
  std::vector<Edge *> edges;

  // Method/Function to add a vertex to the graph
  bool addVertex(Vertex *vertex)
  {
    for (Vertex *v : vertices)
    {
      if (v->urbanVillage == vertex->urbanVillage)
      {
        return false;
      }
    }

    vertices.push_back(vertex);

    return true;
  }

  Vertex *updateVertex(Vertex *vertex, Vertex *newVertex)
  {
    for (Vertex *v : vertices)
    {
      if (v->urbanVillage == vertex->urbanVillage)
      {
        v->district = newVertex->district;
        v->urbanVillage = newVertex->urbanVillage;
        v->publicHealthCenter = newVertex->publicHealthCenter;
        return v;
      }
    }

    return nullptr;
  }

  Vertex *getVertex(const std::string &urbanVillageName)
  {
    for (Vertex *vertex : vertices)
    {
      if (vertex->urbanVillage == urbanVillageName)
      {
        return vertex;
      }
    }
    return nullptr;
  }

  bool deleteVertex(Vertex *vertex)
  {
    for (auto &edge : edges)
    {
      if (edge->firstVertex == vertex || edge->secondVertex == vertex)
      {
        deleteEdge(edge->firstVertex, edge->secondVertex);
      }
    }

    vertices.erase(std::remove(vertices.begin(), vertices.end(), vertex), vertices.end());

    return true;
  }

  // Method/Function to add a directional edge to the graph
  bool addEdge(Vertex *firstVertex, Vertex *secondVertex, int edgeWeight)
  {
    for (Edge *edge : edges)
    {
      if ((edge->firstVertex == firstVertex && edge->secondVertex == secondVertex) || (edge->firstVertex == secondVertex && edge->secondVertex == firstVertex))
      {
        return false;
      }
    }
    Edge *firstEdge = new Edge(firstVertex, secondVertex, edgeWeight);

    edges.push_back(firstEdge);

    return true;
  }

  bool deleteEdge(Vertex *firstVertex, Vertex *secondVertex)
  {
    for (auto &edge : edges)
    {
      if ((edge->firstVertex == firstVertex && edge->secondVertex == secondVertex) || (edge->firstVertex == secondVertex && edge->secondVertex == firstVertex))
      {
        edges.erase(std::remove(edges.begin(), edges.end(), edge), edges.end());
        return true;
      }
    }

    return false;
  }

  void reverseEdges()
  {
    for (const auto &edge : edges)
    {
      Vertex *temp = edge->firstVertex;
      edge->firstVertex = edge->secondVertex;
      edge->secondVertex = temp;
    }

    //  Reverse the vector
    std::reverse(edges.begin(), edges.end());
  }

  void printSingleEdges()
  {
    const std::string RIGHT_ARROW = " -> ";
    const std::string SQUARE = "🔹";

    int i = 0;
    for (auto &edge : edges)
    {
      if (i == 0)
      {
        if (edge->firstVertex->publicHealthCenter != "None")
        {
          std::cout << SQUARE << edge->firstVertex->publicHealthCenter;
          std::cout << " (" << edge->firstVertex->urbanVillage << ") ";
        }
        else
        {
          std::cout << SQUARE << edge->firstVertex->urbanVillage;
        }

        std::cout << RIGHT_ARROW;

        if (edge->secondVertex->publicHealthCenter != "None")
        {
          std::cout << SQUARE << edge->secondVertex->publicHealthCenter;
          std::cout << " (" << edge->secondVertex->urbanVillage << ") ";
        }
        else
        {
          std::cout << SQUARE << edge->secondVertex->urbanVillage;
        }
      }
      else
      {
        std::cout << RIGHT_ARROW;

        if (edge->secondVertex->publicHealthCenter != "None")
        {
          std::cout << SQUARE << edge->secondVertex->publicHealthCenter;
          std::cout << " (" << edge->secondVertex->urbanVillage << ") ";
        }
        else
        {
          std::cout << SQUARE << edge->secondVertex->urbanVillage;
        }
      }
      i++;
    }
  }

  // Method/Function to get all the edges of a vertex
  std::vector<Edge *> getEdges(Vertex *vertex)
  {
    std::vector<Edge *> vertexEdges;
    for (Edge *edge : edges)
    {
      if (edge->firstVertex == vertex || edge->secondVertex == vertex)
      {
        vertexEdges.push_back(edge);
      }
    }

    for (Edge *edge : vertexEdges)
    {
      if (edge->firstVertex != vertex)
      {
        Vertex *temp = edge->firstVertex;
        edge->firstVertex = edge->secondVertex;
        edge->secondVertex = temp;
      }
    }
    return vertexEdges;
  }

  // Method/Function to find shortest path between two vertices with Dijkstra's Algorithm
  std::pair<Graph, long long unsigned int> findShortestPath(Vertex *startVertex, Vertex *endVertex)
  {
    // MAIN DIJKSTRA'S ALGORITHM
    std::map<Vertex *, std::pair<Vertex *, long long unsigned int>> shortestDistance;

    for (const auto &vertex : vertices)
    {
      shortestDistance[vertex] = std::make_pair(nullptr, INFINITY);
    }

    std::vector<Vertex *> visitedVertices;

    Vertex *currentVertex = startVertex;
    shortestDistance[currentVertex] = std::make_pair(currentVertex, 0);

    while (currentVertex != endVertex)
    {
      visitedVertices.push_back(currentVertex);

      std::vector<Edge *> currentEdges = getEdges(currentVertex);

      for (const auto &edge : currentEdges)
      {
        Vertex *destinationVertex = edge->secondVertex;

        long long unsigned int distance = shortestDistance[currentVertex].second + edge->distance;

        if (distance < shortestDistance[destinationVertex].second)
        {
          shortestDistance[destinationVertex] = std::make_pair(currentVertex, distance);
        }
      }

      long long unsigned int minDistance = INFINITY;

      for (const auto &vertex : vertices)
      {
        if (shortestDistance[vertex].second < minDistance && shortestDistance[vertex].first != vertex && std::find(visitedVertices.begin(), visitedVertices.end(), vertex) == visitedVertices.end())
        {
          minDistance = shortestDistance[vertex].second;
          currentVertex = vertex;
        }
      }

      if (minDistance == INFINITY)
      {
        Graph emptyGraph;
        return std::make_pair(emptyGraph, INFINITY);
      }
    }

    const long long unsigned int totalDistance = shortestDistance[endVertex].second;

    Graph shortestPath;

    while (currentVertex != startVertex)
    {
      shortestPath.addVertex(currentVertex);
      Vertex *previousVertex = shortestDistance[currentVertex].first;

      for (const auto &edge : edges)
      {
        if ((edge->firstVertex == currentVertex && edge->secondVertex == previousVertex) || (edge->firstVertex == previousVertex && edge->secondVertex == currentVertex))
        {
          shortestPath.addEdge(currentVertex, previousVertex, edge->distance);
          break;
        }
      }

      currentVertex = previousVertex;
    }

    shortestPath.addVertex(startVertex);

    shortestPath.reverseEdges();

    return std::make_pair(shortestPath, totalDistance);
  };
};

#endif // GRAPH_H_clwzpelo800010cjq4k4f6m0k