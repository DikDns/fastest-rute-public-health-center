#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;
namespace fs = std::filesystem;

const string STORAGE_DIR = "./storage/";

json readStorage(const string &filename)
{
  string path = STORAGE_DIR + filename;

  ifstream file(path);
  if (!file.is_open())
  {
    if (!fs::exists(STORAGE_DIR))
    {
      fs::create_directories(STORAGE_DIR);
    }

    ofstream createFile(path);
    if (!createFile.is_open())
    {
      cerr << "Could not create the file!" << endl;
      return nullptr;
    }
    createFile << "[]";
    createFile.close();
    return json::array();
  }

  file.seekg(0, std::ios::end);
  if (file.tellg() == 0)
  {
    return json::array();
  }

  file.seekg(0, std::ios::beg);

  json j;
  file >> j;
  return j;
}

void writeStorage(const string &filename, const json &data)
{
  string path = STORAGE_DIR + filename;

  if (!fs::exists(STORAGE_DIR))
  {
    fs::create_directories(STORAGE_DIR);
  }

  ofstream file(path);
  if (!file.is_open())
  {
    cerr << "Could not create the file!" << endl;
    return;
  }

  if (data.empty())
  {
    file << "[]";
  }
  else
  {
    file << data.dump(4);
  }
}