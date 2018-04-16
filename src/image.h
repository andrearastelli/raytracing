#include <iostream>
#include <fstream>
#include <filesystem>

class Image
{
private:
    std::string fileame;
public:
    Image() { std::cout << "Tmp dir: " << std::filesystem::tmp_directoy_path() << std::endl; }
    Image(std::string filename): filename{filename} {}

};

