using namespace std;

#include<iostream>;
#include<fstream>;

#include "Image.hh";

Image::Image(int w, int h): width(w), height(h) {};

void Image::setPixel(int x, int y, Color& c) {
    pixels[y*width+x] = c;
}

void Image::savePPM(const string& path){
    ofstream file(path);
    file << "P6\n";
    file << width << " " << height << "\n";
    file << "255\n";

    for(Color c : pixels) {
        file << c.r << " " << c.g << " " << c.b << "\n";
    }

    file.close();
}
