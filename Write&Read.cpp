#include "ReadFile.hpp"
#include "Write&Read.hpp"

std::string Name;
std::string Id;

std::string Read_User;
std::string Read_Id;

void Save(std::string& File_Name, std::unordered_map<std::string , std::string>& map){
    
    std::ofstream file (File_Name , std::ios::app);

    if(!(file.is_open())){

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

void Load(std::string& File_Name , std::unordered_map<std::string , std::string>& map){

    std::string Read_User{};
    std::string Read_Id {};

    std::ifstream file (File_Name, std::ios::app);


    if(file.is_open()){

        std::cout << "Success";
        while(std::getline(file,Read_User)){

            std::getline(file, Read_Id);

            (map)[Read_User] = Read_Id;
        }
    }

    else{
        std::cerr << "Error";
        return;
    }

    file.close();

    return;
}


void GenerateData(std::string& File_Name)
{
    std::ofstream file(File_Name , std::ios::app);

    if(file.is_open())
    {
        for(size_t i = 0 ; i < 10000 ; i++){

        std::string Id = std::to_string(i);
        std::string Password = std::to_string(i/2);
        addPair(Id , Password , KEYVALUEPAIR_STORAGE);
        }
    }
    else
    {
        std::cerr<<"Error";
        return;
    }
    file.close();
    return;
}