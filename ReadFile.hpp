#pragma once
#include <iostream>
#include <unordered_map>
#include <utility>
#include <string>
#include <string_view>


extern std::unordered_map<std::string , std::string> KEYVALUEPAIR_STORAGE;
extern std::ifstream into_file;
extern std::ofstream outof_file;

void addPair(std::string& Name , std::string& Id , 
    std::unordered_map<std::string , std::string>& MapRef);

void LookUpName(std::string& Name, std::unordered_map<std::string 
    , std::string>& MapRef);

