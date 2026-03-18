#pragma once

#include <string>
#include <vector>

#include "Color.hh"

class Image
{
public:
    int width;
    int height;
    std::vector<Color> pixels;

    Image(int w, int h);

    void setPixel(int x, int y, const Color& c);
    void savePPM(const std::string& path);
};