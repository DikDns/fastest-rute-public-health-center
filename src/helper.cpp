#include <iostream>
#include "headers/graph.h"
#include "headers/queue.h"
#include "headers/storage.h"

void readMainRoute(Graph *mainRoute)
{
  const string DISTRICTS_FILENAME = "districts.json";
  const string ROUTES_FILENAME = "routes.json";
  json districts = readStorage(DISTRICTS_FILENAME);

  for (const auto &district : districts)
  {
    Vertex *vertex = new Vertex(district["district"], district["urban_village"], district["public_health_center"]);

    mainRoute->addVertex(vertex);
  }

  json routes = readStorage(ROUTES_FILENAME);

  for (const auto &route : routes)
  {
    Vertex *firstVertex = mainRoute->getVertex(route["urban_village_1"]);
    Vertex *secondVertex = mainRoute->getVertex(route["urban_village_2"]);

    long long unsigned int distance = route["distance_in_meter"];

    mainRoute->addEdge(firstVertex, secondVertex, distance);
  }
}

void readHistory(Queue *fastestRouteHistory, Graph *mainRoute)
{
  const string HISTORY_FILENAME = "history.json";
  json history = readStorage(HISTORY_FILENAME);

  for (const auto &item : history)
  {
    Graph *fastestRoute = new Graph();

    for (const auto &district : item["districts"])
    {
      Vertex *v = new Vertex(district["district"], district["urban_village"], district["public_health_center"]);

      fastestRoute->addVertex(v);
    }

    for (const auto &route : item["routes"])
    {
      Vertex *firstVertex = fastestRoute->getVertex(route["urban_village_1"]);
      Vertex *secondVertex = fastestRoute->getVertex(route["urban_village_2"]);

      long long unsigned int distance = route["distance_in_meter"];

      fastestRoute->addEdge(firstVertex, secondVertex, distance);
    }

    fastestRouteHistory->addGraph(*fastestRoute);
  }
}