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

void Save(std::ofstream &file, std::unordered_map<std::string , std::string>& map);
void GenerateData();
void Load(std::ifstream &file , std::unordered_map<std::string , std::string>& map);