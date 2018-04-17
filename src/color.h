#ifndef RAYTRACING_COLOR_H
#define RAYTRACING_COLOR_H


class Color
{

private:
    float c[3];

public:
    Color() : c{0, 0, 0} {}
    Color(int r, int g, int b): c{r / 255.0f, g / 255.0f, b / 255.0f} {}
    Color(float r, float g, float b): c{r, g, b} {}
    ~Color() = default;

    inline float r() const { return c[0]; }
    inline float g() const { return c[1]; }
    inline float b() const { return c[2]; }
};


#endif //RAYTRACING_COLOR_H
