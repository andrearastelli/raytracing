#include <cmath>

class vec3
{
private:
    float v[3];

public:
    vec3(float x, float y, float z): v{x, y, z} {}
    vec3(): v{0.0f, 0.0f, 0.0f} {}

    float x() { return v[0]; }
    float y() { return v[1]; }
    float z() { return v[2]; }
};
