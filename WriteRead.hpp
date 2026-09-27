#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>

//external file to aviod copies
extern std::ifstream into_file;
extern std::ofstream outof_file;

//function defs

void GenerateData(std::string& File_Name);
void Load(std::string& File_Name , std::unordered_map<std::string , std::string>& map);
void Save(std::string& File_Name, std::unordered_map<std::string , std::string>& map);