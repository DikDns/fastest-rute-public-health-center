#ifndef STORAGE_H_clwzpelo800010cjq4k4f6m0k
#define STORAGE_H_clwzpelo800010cjq4k4f6m0k

#include <string>
#include "../nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

json readStorage(const string &filename);
void writeStorage(const string &filename, const json &data);

#endif