#include <iostream>
#include <fstream>


#include "color.h"


class Image
{

private:
    std::string filename;
    std::ofstream output_file;

    int size_x;
    int size_y;

public:
    Image() = delete;
    explicit Image(const std::string &filename, int size_x = 200, int size_y = 100);
    ~Image();

    void write(const Color &color);

    inline int width() const { return size_x; }
    inline int height() const { return size_y; }
};


Image::Image(const std::string &filename, int size_x, int size_y) : filename{filename}, size_x{size_x}, size_y{size_y}
{
    output_file.open(filename);
    output_file << "P3\n";
    output_file << size_x << " " << size_y << "\n";
    output_file << "255\n";
}


Image::~Image()
{
    output_file.close();
}


void Image::write(const Color &color)
{
    output_file << static_cast<int>(color.r() * 255.99) << " "
                << static_cast<int>(color.g() * 255.99) << " "
                << static_cast<int>(color.b() * 255.99) << "\n";
}

