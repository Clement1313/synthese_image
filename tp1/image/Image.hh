#pragma once;

using namespace std;

#include <vector>;
#include <string>;

#include "Color.hh";

class Image
{
public:
    int width;
    int height;
    vector<Color> pixels; 

    Image(int w, int h);
    
    void setPixel(int x, int y, Color& c);
    void savePPM(const string& path);
};