#ifndef UTILS_H_clwzqqfia00000cjt2za33t9u
#define UTILS_H_clwzqqfia00000cjt2za33t9u

#include <string>

void setConsoleOutputUTF8();
void delay(int milliseconds);
// Function to print a normal message to the console
void println(const std::string &message, bool is_warning = false);
// Function to print a message with input prompt to the console
std::string inputln(const std::string &message, bool is_warning = false);
// Function to clear the terminal
void clearTerminal();
// Function to clear the confirmation message
void clearConfirmation();

void printBanner();

#endif // UTILS_H_clwzqqfia00000cjt2za33t9u