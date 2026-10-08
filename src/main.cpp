#include <iostream>
#include <fstream>
#include "ReadFile.hpp"
#include "WriteRead.hpp"


extern std::unordered_map<std::string , std::string> KEYVALUEPAIR_STORAGE {};
//std::ifstream into_file{"data.txt", std::ios::app};
//std::ofstream outof_file{"data.txt", std::ios::app};
//
std::string File_Name {"data.txt"};

int main (){

    std::string Command{};
    std::string Function{};
    std::string Target{};

    char buf1{};
    char buf2{};

    std::cin >> Command;

    std::stringstream ss (Command);

    ss >> Function >> Target;




}
