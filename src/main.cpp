#include <iostream>

#include "image.h"

int main()
{
    Image i("test.ppm");

    for (int idY=i.height() - 1; idY>=0; --idY)
    {
        for (int idX=0; idX<i.width(); ++idX)
        {
            float r = idX / static_cast<float>(i.width());
            float g = idY / static_cast<float>(i.height());
            float b = 0.2f;
            Color c(r, g, b);
            i.write(c);
        }
    }

    return 0;
}
