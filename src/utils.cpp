#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include "headers/graph.h"

const std::string MARK = "🟢]";
const std::string MARK_WARNING = "⚠️ ]";
const std::string MARK_OUTPUT = "=| ";
const std::string MARK_INPUT = "===> ";

void setConsoleOutputUTF8()
{
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif
}

void delay(int milliseconds)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

// Function to print a normal message to the console
void println(const std::string &message, bool is_warning = false)
{
  if (is_warning)
  {
    std::cout << MARK_WARNING << MARK_OUTPUT << message << std::endl;
    return;
  }

  std::cout << MARK << MARK_OUTPUT << message << std::endl;
}

// Function to print a message with input prompt to the console
std::string inputln(const std::string &message, bool is_warning = false)
{
  if (is_warning)
  {
    std::cout << MARK_WARNING << MARK_INPUT << message;
  }
  else
  {
    std::cout << MARK << MARK_INPUT << message;
  }

  std::string input;
  std::getline(std::cin, input);

  return input;
}

// Function to clear the terminal
void clearTerminal()
{
  system("cls||clear");
}

// Function to clear the confirmation message
void clearConfirmation()
{
  inputln("Press enter to continue...");
  clearTerminal();
}

void printBanner()
{
  clearTerminal();
  delay(8);
  std::cout << "                            " << "\n";
  delay(16);
  std::cout << " ________  _______     _______  ____  ____   ______  " << "\n";
  delay(24);
  std::cout << "|_   __  ||_   __ \\   |_   __ \\|_   ||   _|.' ___  | " << "\n";
  delay(32);
  std::cout << "  | |_ \\_|  | |__) |    | |__) | | |__| | / .'   \\_|   " << "\n";
  delay(64);
  std::cout << "  |  _|     |  __ /     |  ___/  |  __  | | |          " << "\n";
  delay(80);
  std::cout << " _| |_     _| |  \\ \\_  _| |_    _| |  | |_\\ `.___.'\\ " << "\n";
  delay(96);
  std::cout << "|_____|   |____| |___||_____|  |____||____|`.____ .' " << "\n";
  delay(128);
  std::cout << "\n";
  delay(256);
  std::cout << "|> Fastest Route Public Health Center" << "\n";
  delay(4000);
}