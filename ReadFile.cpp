#include "ReadFile.hpp"




void addPair(std::string& Name , std::string& Id , std::unordered_map<std::string , std::string>& MapRef){

    std::ofstream file ("data.txt" , std::ios::app);

    if(file.is_open())
    {
        if (auto it = MapRef.find(Name); it != MapRef.end())
        {
            std::cout << "Name Already Exists";

            return;
        }
    }
    else
    {
        throw std::runtime_error("Couldnt Open File");
    }

    MapRef[Name] = Id;

    file.close();
    return;
}


//fix overload issue then should work
//rename to find
std::optional<std::string> LookUpName(std::string& Name, std::unordered_map<std::string , std::string>& MapRef){

    //ensure only called after Items are loaded into hashmap
    std::string Id = (MapRef)[Name];

    if(Id == "0")
    {
        std::cout<<"Not Found";
        return 0;
    }

    return Id;
    
}



