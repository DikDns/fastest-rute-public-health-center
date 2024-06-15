#include <iostream>
#include "headers/menu.h"
#include "headers/utils.h"
#include "headers/helper.h"

using namespace std;

int main(int argc, char const *argv[])
{
  // Set the console output to UTF-8 (For Emoji Support)
  setConsoleOutputUTF8();

  printBanner();

  Graph mainRoute;
  readMainRoute(&mainRoute);

  Queue fastestRouteHistory;
  readHistory(&fastestRouteHistory, &mainRoute);

  do
  {
    clearTerminal();

    println("Fastest Route Public Health Center");
    println("Menu:");
    println("1. Add Public Health Center");
    println("2. View Public Health Center");
    println("3. Add Route");
    println("4. Find Fastest Route");
    println("5. View Fastest Route History");
    println("6. Exit\n");

    // Get user input
    string input = inputln("Choose menu: ");

    // Validate user input
    if (input.find_first_not_of("123456") != string::npos || input.empty())
    {
      input = "0";
    }

    // Handle user input
    switch (stoi(input))
    {
    case 1:
      createPublicHealthCenter(mainRoute);
      continue;
    case 2:
      viewPublicHealthCenter(mainRoute);
      continue;
    case 3:
      createRoute(mainRoute);
      continue;
    case 4:
      findFastestRoute(mainRoute, fastestRouteHistory);
      continue;
    case 5:
      viewFastestRouteHistory(fastestRouteHistory);
      continue;
    case 6:
      exitOutput();
      return 0;
    default:
      println("Invalid menu option! (Choose 1-6)", true);
      clearConfirmation();
      continue;
    }

  } while (true);

  return 0;
}
