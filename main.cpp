#include <iostream>
#include <fstream>
#include "ReadFile.hpp"
#include "Write&Read.hpp"


std::unordered_map<std::string , std::string> KEYVALUEPAIR_STORAGE {};
std::ifstream into_file{"data.txt", std::ios::app};
std::ofstream outof_file{"data.txt", std::ios::app};

int main (){

    std::string Search_Name{};
    
    GenerateData();

    Load(into_file,KEYVALUEPAIR_STORAGE);

    std::cout<<"\nEnter Name to search: ";
    std::cin >> Search_Name;

    LookUpName(Search_Name , KEYVALUEPAIR_STORAGE);
}
