#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>

#include "headers/fptree.h"
#include "headers/graph.h"
#include "headers/queue.h"
#include "headers/utils.h"
#include "headers/storage.h"

using namespace std;

void createPublicHealthCenter(Graph &mainRoute)
{
  const string DISTRICTS_FILE = "districts.json";

  while (true)
  {
    clearTerminal();

    println("Create Public Health Center");
    println("Type '<' to go back\n");

    string district = inputln("District name: ");

    if (district == "<")
    {
      return;
    }

    // Validate district name
    if (district.empty())
    {
      println("District name cannot be empty!", true);
      clearConfirmation();
      continue;
    }

    string urbanVillage = inputln("Urban Village name: ");

    if (urbanVillage == "<")
    {
      return;
    }

    // Validate urban village name
    if (urbanVillage.empty())
    {
      println("Urban Village name cannot be empty!", true);
      clearConfirmation();
      continue;
    }

    string publicHealthCenter = "None";
    string isPublicHealthCenter = inputln("Is there a public health center in this urban village? (y) ");

    if (isPublicHealthCenter == "<")
    {
      return;
    }

    if (isPublicHealthCenter == "y")
    {
      publicHealthCenter = inputln("Public Health Center name: ");

      if (publicHealthCenter == "<")
      {
        return;
      }

      // Validate public health center name
      if (publicHealthCenter.empty())
      {
        println("Public Health Center name cannot be empty!", true);
        clearConfirmation();
        continue;
      }
    }

    Vertex *newVertex = new Vertex(district, urbanVillage, publicHealthCenter);

    if (mainRoute.addVertex(newVertex))
    {
      if (publicHealthCenter != "None")
      {
        println("District " + district + ", Urban Village " + urbanVillage + ", and Public Health Center " + publicHealthCenter + " has been added");
      }
      else
      {
        println("District " + district + " and Urban Village " + urbanVillage + " has been added");
      }

      json savedDistricts = readStorage(DISTRICTS_FILE);

      savedDistricts.push_back({
          {"district", district},
          {"urban_village", urbanVillage},
          {"public_health_center", publicHealthCenter},
      });

      writeStorage(DISTRICTS_FILE, savedDistricts);

      clearConfirmation();
      return;
    }
    else
    {
      println("Urban Village " + urbanVillage + " already exists!", true);
    }

    clearConfirmation();
  }
}

void viewPublicHealthCenter(Graph &mainRoute)
{
  const string SQUARE = "🔹";

  clearTerminal();

  cout << "====================================================================" << endl;
  delay(64);
  cout << "                     Public Health Center List                      " << endl;
  delay(64);
  cout << "====================================================================" << endl;
  delay(64);

  int i = 1;
  for (const auto &vertex : mainRoute.vertices)
  {
    cout << setw(3) << right << i << " |";
    cout << setw(1) << right << SQUARE << " ";
    cout << vertex->publicHealthCenter << " (" << vertex->urbanVillage << ") ";
    cout << endl;
    delay(64);
    i++;
  }

  cout << "====================================================================" << endl;
  delay(64);
  cout << " Total: " << mainRoute.vertices.size() << endl;
  delay(64);
  cout << "====================================================================" << endl;

  cout << endl;

  clearConfirmation();
}

void createRoute(Graph &mainRoute)
{
  const string ROUTES_FILE = "routes.json";
  while (true)
  {
    clearTerminal();

    println("Create Route");
    println("Type '<' to go back\n");

    string startVertexName = inputln("Start Urban Village: ");

    if (startVertexName == "<")
    {
      return;
    }

    // Validate start vertex name
    if (startVertexName.empty())
    {
      println("Start Urban Village cannot be empty!", true);
      clearConfirmation();
      continue;
    }

    Vertex *startVertex = mainRoute.getVertex(startVertexName);

    if (!startVertex)
    {
      println("Urban Village " + startVertexName + " not found!", true);
      clearConfirmation();
      continue;
    }

    string endVertexName = inputln("End Urban Village: ");

    if (endVertexName == "<")
    {
      return;
    }

    // Validate end vertex name

    if (endVertexName.empty())
    {
      println("End Urban Village cannot be empty!", true);
      clearConfirmation();
      continue;
    }

    Vertex *endVertex = mainRoute.getVertex(endVertexName);

    if (!endVertex)
    {
      println("Urban Village " + endVertexName + " not found!", true);
      clearConfirmation();
      continue;
    }

    if (startVertex == endVertex)
    {
      println("Start Urban Village and End Urban Village cannot be the same!", true);
      clearConfirmation();
      continue;
    }

    unsigned long long distance = stoull(inputln("Distance (in meter): "));

    if (distance == 0)
    {
      println("Distance cannot be 0!", true);
      clearConfirmation();
      continue;
    }

    if (mainRoute.addEdge(startVertex, endVertex, distance))
    {
      println("Route from " + startVertexName + " to " + endVertexName + " has been added");

      json savedRoutes = readStorage(ROUTES_FILE);

      savedRoutes.push_back({
          {"urban_village_1", startVertexName},
          {"urban_village_2", endVertexName},
          {"distance", distance},
      });

      writeStorage(ROUTES_FILE, savedRoutes);

      clearConfirmation();
      return;
    }
    else
    {
      println("Route from " + startVertexName + " to " + endVertexName + " already exists!", true);
    }

    clearConfirmation();
  }
}

void findFastestRoute(Graph &mainRoute, Queue &fastestRouteHistory)
{
  const string HISTORY_FILE = "history.json";

  while (true)
  {
    clearTerminal();

    println("Find Fastest Route");
    println("Type '<' to go back\n");

    string startInput = inputln("Start Urban Village: ");

    if (startInput == "<")
    {
      return;
    }

    Vertex *startVertex = mainRoute.getVertex(startInput);

    if (!startVertex)
    {
      println("Urban Village " + startInput + " not found!", true);
      clearConfirmation();
      continue;
    }

    vector<Transaction> transactions;

    for (const auto &graph : fastestRouteHistory.graphs)
    {
      vector<Item> items;
      for (const auto &vertex : graph.vertices)
      {
        items.push_back(vertex->urbanVillage);
      }
      transactions.push_back(items);
    }

    const uint64_t minimum_support_threshold = 2;

    const FPTree fptree{transactions, minimum_support_threshold};

    const std::set<Pattern> patterns = fptree_growth(fptree);

    std::set<Pattern> recomendedPatterns;

    uint64_t maxCount = 0;

    for (const auto &pattern : patterns)
    {
      // Find urban village in the pattern set
      if (pattern.first.find(startInput) != pattern.first.end())
      {
        // Skip if the pattern only contains the start urban village
        if (pattern.first.size() == 1 && pattern.first.find(startInput) != pattern.first.end())
        {
          continue;
        }

        // Add the pattern to the recommended patterns set
        if (pattern.second > maxCount)
        {
          maxCount = pattern.second;
          recomendedPatterns.clear();
          recomendedPatterns.insert(pattern);
        }
        else if (pattern.second == maxCount)
        {
          recomendedPatterns.insert(pattern);
        }
      }
    }

    map<string, uint64_t> patternMap;

    if (!recomendedPatterns.empty())
    {
      for (const auto &pattern : recomendedPatterns)
      {
        for (const auto &urbanVillage : pattern.first)
        {
          if (urbanVillage == startInput)
          {
            continue;
          }

          if (patternMap[urbanVillage] > 0)
          {
            patternMap[urbanVillage] += 1;
          }
          else
          {
            patternMap[urbanVillage] = 1;
          }
        }
      }

      int maxCount = 0;
      vector<string> recommendedUrbanVillages;

      for (const auto &pattern : patternMap)
      {
        if (pattern.second > maxCount)
        {
          maxCount = pattern.second;
          recommendedUrbanVillages.clear();
          recommendedUrbanVillages.push_back(pattern.first);
        }
        else if (pattern.second == maxCount)
        {
          recommendedUrbanVillages.push_back(pattern.first);
        }
      }

      if (recommendedUrbanVillages.size() > 1)
      {
        println("Recommended Destination Urban Villages: \n");

        int i = 1;
        for (const auto &urbanVillage : recommendedUrbanVillages)
        {
          cout << "   " << i << " " << urbanVillage << endl;
          i++;
        }
        cout << endl;
      }
      else
      {
        println("Recommended Destination Urban Village: " + recommendedUrbanVillages[0]);
      }
    }

    cout << endl;

    string destinationInput = inputln("Destination Urban Village: ");

    if (destinationInput == "<")
    {
      return;
    }

    Vertex *destinationVertex = mainRoute.getVertex(destinationInput);

    if (!destinationVertex)
    {
      println("Urban Village " + destinationInput + " not found!", true);
      clearConfirmation();
      continue;
    }

    if (startVertex == destinationVertex)
    {
      println("Start Urban Village and Destination Urban Village cannot be the same!", true);
      clearConfirmation();
      continue;
    }

    pair<Graph, unsigned long long> result = mainRoute.findShortestPath(startVertex, destinationVertex);

    Graph fastestRoute = result.first;
    unsigned long long totalDistance = result.second;

    cout << endl;

    if (totalDistance == INFINITY)
    {
      println("No route found!", true);
      clearConfirmation();
      continue;
    }

    fastestRoute.printSingleEdges();

    cout << endl;
    cout << endl;

    cout << "Total Distance: " << totalDistance << " meter" << endl;

    cout << endl;

    fastestRouteHistory.addGraph(fastestRoute);

    json savedHistory = readStorage(HISTORY_FILE);

    savedHistory.push_back({
        {"districts", json().array()},
        {"routes", json().array()},
    });

    for (const auto &vertex : fastestRoute.vertices)
    {
      savedHistory.back()["districts"].push_back({
          {"district", vertex->district},
          {"urban_village", vertex->urbanVillage},
          {"public_health_center", vertex->publicHealthCenter},
      });
    }

    for (const auto &edge : fastestRoute.edges)
    {
      savedHistory.back()["routes"].push_back({
          {"urban_village_1", edge->firstVertex->urbanVillage},
          {"urban_village_2", edge->secondVertex->urbanVillage},
          {"distance_in_meter", edge->distance},
      });
    }

    writeStorage(HISTORY_FILE, savedHistory);

    println("Fastest route has been saved to history\n");

    clearConfirmation();

    break;
  };
}

void viewFastestRouteHistory(Queue &fastestRouteHistory)
{
  clearTerminal();

  println("Fastest Route History");
  delay(64);

  long long unsigned int i = 1;

  for (auto &graph : fastestRouteHistory.graphs)
  {
    cout << setw(3) << right << i << " |";
    graph.printSingleEdges();
    cout << endl;
    delay(64);
    i++;
  }

  cout << endl;

  cout << endl;

  clearConfirmation();
}

void exitOutput()
{
  for (int i = 0; i < 4; i++)
  {
    println("Exiting");
    delay(256);
    clearTerminal();
    println("Exiting.");
    delay(256);
    clearTerminal();
    println("Exiting..");
    delay(256);
    clearTerminal();
    println("Exiting...");
    delay(256);
    clearTerminal();
  }
  delay(4000);
  clearTerminal();
}
