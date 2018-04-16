#include <iostream>
#include <fstream>


class Image
{

private:
    std::string filename;
    std::ofstream output_file;

public:
    Image() = delete;
    Image(const std::string &filename);
    ~Image();

};


Image::Image(const std::string &filename) : filename{filename}
{
    output_file.open(filename);
}


Image::~Image()
{
    output_file.close();
}

