#ifndef RAYTRACING_COLOR_H
#define RAYTRACING_COLOR_H


#include <array>
#include <sstream>
#include <fstream>
#include <iostream>


class Color
{

private:
    /**
     * The internal color representation.
     */
    std::array<float, 3> c;

public:
    /**
     * Default constructor.
     *
     * Will create a black color.
     */
    Color() : c{0, 0, 0} {}

    /**
     * Color int constructor.
     *
     * Will create a color from the int values as inputs.
     * The input values must be in the range [0, 255).
     *
     * @param r Red component.
     * @param g Green component.
     * @param b Blue component.
     */
    Color(int r, int g, int b): c{r / 255.0f, g / 255.0f, b / 255.0f} {}

    /**
     * Color float constructor.
     *
     * Will create a color using floating point values as inputs.
     * The values must be in the range [0, 1).
     *
     * @param r Red component.
     * @param g Green component.
     * @param b Blue component.
     */
    Color(float r, float g, float b): c{r, g, b} {}

    /**
     * Default destructor.
     */
    ~Color() = default;


    inline float r() const { return c[0]; }
    inline float g() const { return c[1]; }
    inline float b() const { return c[2]; }
};


/**
 * Output stream operator overload.
 *
 * Will format the color as to be represented in a string
 * for the default output stream.
 *
 * @param os The output stream.
 * @param color The color to represent.
 *
 * @return The output stream with the color formatted.
 */
inline std::ostream& operator<<(std::ostream &os, const Color &color)
{
    os << static_cast<int>(color.r() * 255.99) << " "
       << static_cast<int>(color.g() * 255.99) << " "
       << static_cast<int>(color.b() * 255.99);
    return os;
}

/**
 * Output file stream operator overload.
 *
 * Will format the color as to be written in an ASCII file.
 *
 * @param ofs The file stream.
 * @param color The color to represent.
 *
 * @return The output file stream into witch format the color.
 */
inline std::ofstream& operator<<(std::ofstream &ofs, const Color &color)
{
    ofs << static_cast<int>(color.r() * 255.99) << " "
        << static_cast<int>(color.g() * 255.99) << " "
        << static_cast<int>(color.b() * 255.99);
    return ofs;
}


#endif //RAYTRACING_COLOR_H
