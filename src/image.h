/**
 * Image.
 *
 * Class used for handling the image generation process into a file.
 * The current implementation allows the creation of images in the PPM
 * ASCII format.
 */

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

    int line_counter;

public:
    /**
     * Deleted default empty constructor.
     */
    Image() = delete;

    /**
     * Filename and image size constructor.
     *
     * Will open the output image stream.
     *
     * @param filename Output image filename
     * @param size_x Width of the image
     * @param size_y Height of the image
     */
    explicit Image(const std::string &filename, int size_x = 200, int size_y = 100);

    /**
     * Destructor.
     *
     * Will close the output image stream.
     */
    ~Image();


    /**
     * Write into the image, appending the color information.
     *
     * @param color Color to add into the image.
     */
    void write(const Color &color);

    /**
     * Returns the width of the image.
     *
     * @return Width of the image.
     */
    inline int width() const { return size_x; }

    /**
     * Returns the height of the image.
     *
     * @return Height of the image.
     */
    inline int height() const { return size_y; }
};


Image::Image(const std::string &filename, int size_x, int size_y) : filename{filename}, size_x{size_x}, size_y{size_y}
{
    output_file.open(filename);
    output_file << "P3\n";
    output_file << size_x << " " << size_y << "\n";
    output_file << "255\n";
    line_counter = 0;
}


Image::~Image()
{
    if (line_counter != (size_x * size_y))
    {
        std::cout << "WARNING!" << std::endl;
        std::cout << "Line count is " << line_counter << ", and does not match the expected total line count ";
        std::cout << "that should be " << (size_x * size_y) << "." << std::endl;
    }

    output_file.close();
}


void Image::write(const Color &color)
{
    auto write_color = color;

    if (std::isnan(color.r()) || std::isnan(color.g()) || std::isnan(color.b()))
        write_color = Color(0.0f, 0.0f, 0.0f);

    output_file << write_color << "\n";

    ++line_counter;
}

