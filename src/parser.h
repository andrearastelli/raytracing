#ifndef RAYTRACING_PARSER_H
#define RAYTRACING_PARSER_H


#include <string>


struct Parameter
{
    int width = 200;
    int height = 100;
    int samples = 8;
    std::string output_path = "temp.ppm";
};


Parameter parser(int argc, char *argv[])
{
    Parameter out_param;

    for(auto idx=0; idx<argc; ++idx)
    {
        std::string arg(argv[idx]);
        std::size_t pos = 0;

        while((pos = arg.find('=')) != std::string::npos)
        {
            auto param = arg.substr(0, pos);
            auto value = arg.substr(pos+1, arg.length());

            if (param == "--output")
                out_param.output_path = value;

            if (param == "--width")
                out_param.width = std::stoi(value);

            if (param == "--height")
                out_param.height = std::stoi(value);

            if (param == "--samples")
                out_param.samples = std::stoi(value);

            arg.erase(0, pos + 1);
        }
    }

    return out_param;
}


#endif //RAYTRACING_PARSER_H
