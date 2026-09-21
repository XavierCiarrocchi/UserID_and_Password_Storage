#include "ReadFile.hpp"
#include "Write&Read.hpp"

std::string Name;
std::string Id;

std::string Read_User;
std::string Read_Id;

void Save(std::ofstream &file, std::unordered_map<std::string , std::string>& map){
    
    if(!file.is_open()){

        std::cerr<<"error";
        return;
    }

    std::cout<<"success";

    for(const auto& pair : map){

        file << pair.first << "\n";
        file << pair.second << "\n";
    }

    file.close();
    return;
}

void Load(std::ifstream &file , std::unordered_map<std::string , std::string>& map){

    std::string Name;
    std::string Id;
    file.open("data.txt" , std::ios::app);
    if(!file.is_open())
    {
        std::cerr << "error";
        return;
    }

    if(file.is_open()){

        std::cout << "Success";
        while(getline(file,Read_User)){

            std::getline(file, Read_Id);

            (map)[Read_User] = Read_Id;
        }
    }
}


void GenerateData()
{
    
    for(size_t i = 0 ; i < 10000 ; i++){

        std::string Id = std::to_string(i);

        std::string Password = std::to_string(i/2);
        
        addPair(Id , Password , KEYVALUEPAIR_STORAGE);
    }

    return;
}