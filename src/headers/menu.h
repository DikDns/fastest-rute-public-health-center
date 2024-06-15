#ifndef MENU_H_clwzpxyi800000cjj254ydnzi
#define MENU_H_clwzpxyi800000cjj254ydnzi

#include "graph.h"
#include "queue.h"

void createPublicHealthCenter(Graph &mainRoute);
void viewPublicHealthCenter(Graph &mainRoute);
void createRoute(Graph &mainRoute);
void findFastestRoute(Graph &mainRoute, Queue &fastestRouteHistory);
void viewFastestRouteHistory(Queue &fastestRouteHistory);
void exitOutput();

#endif // MENU_H_clwzpxyi800000cjj254ydnzi