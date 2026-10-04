#include "ReadFile.hpp"
#include "WriteRead.hpp"

std::string Name;
std::string Id;

std::string Read_User;
std::string Read_Id;

void Save(std::string& File_Name, std::unordered_map<std::string , std::string>& map){
    
    std::ofstream file (File_Name , std::ios::app);

    if(!(file.is_open()))
    {
        throw std::runtime_error("Couldnt Open File");
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

    std::ifstream file (File_Name, std::ios::in);


    if(file.is_open()){

        std::cout << "Success";
        while(std::getline(file,Read_User)){

            if(!(std::getline(file,Read_Id)))
            {
                throw std::runtime_error("Incorrect formating of Data");
            }

            if(Read_Id.empty())
            {
                throw std::runtime_error("Empty Password");
            }

            std::getline(file, Read_Id);

            (map)[Read_User] = Read_Id;
        }
    }
    else
    {
        throw std::runtime_error("Couldnt Open File");
    }
    file.close();

    return;
}


void GenerateData(std::string& File_Name)
{    
    std::ofstream file(File_Name , std::ios::app);

    if(file.is_open())
    {
        for(size_t i = 0 ; i < 10000 ; i+=2){

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

void DeleteData(int LowerBound , int UpperBound, std::string& File_Name)
{
    if(KEYVALUEPAIR_STORAGE.empty())
    {
        Load(File_Name,KEYVALUEPAIR_STORAGE);
    }
    
    std::ifstream Current_File (File_Name);

    if(!(Current_File.is_open()))
    {
        throw std::runtime_error("File Didnt open");
    }

    std::ofstream New_File ("NewFile.txt" , std::ios::out);
    
    std::string User{};

    int line_num{1};

    while(std::getline(Current_File,line_num))
    {
        if(line_num > LowerBound && line_num < UpperBound)
        {
            KEYVALUEPAIR_STORAGE.erase(User);
        }
    }
    
    //rename file to data.txt and delete the old file or rename it as a backup
    Load(New_File , KEYVALUEPAIR_STORAGE);


}
