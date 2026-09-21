#include "ReadFile.hpp"




void addPair(std::string& Name , std::string& Id , std::unordered_map<std::string , std::string>& MapRef){

    if (auto it = MapRef.find(Name); it != MapRef.end())
    {
        std::cout << "Name Already Exists";

        return;
    }

    MapRef[Name] = Id;
    
    return;
}

void LookUpName(std::string& Name, std::unordered_map<std::string , std::string>& MapRef){

    
    std::string_view Id = (MapRef)[Name];
    if(Id == "0")
    {
        std::cout<<"Not Found";
    }
    std::cout<<Id;
    return;
    
}



