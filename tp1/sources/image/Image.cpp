#include <algorithm>
#include <cmath>
#include <fstream>

#include "Image.hh"

namespace {
int toByte(float channel) {
    // Accept either [0,1] or [0,255] input ranges.
    float scaled = (channel <= 1.0f) ? (channel * 255.0f) : channel;
    scaled = std::clamp(scaled, 0.0f, 255.0f);
    return static_cast<int>(std::round(scaled));
}
}

Image::Image(int w, int h) : width(w), height(h), pixels(static_cast<size_t>(w * h)) {}

void Image::setPixel(int x, int y, const Color& c) {
    if (x < 0 || y < 0 || x >= width || y >= height) {
        return;
    }
    pixels[static_cast<size_t>(y * width + x)] = c;
}

void Image::savePPM(const std::string& path) {
    std::ofstream file(path);
    file << "P3\n";
    file << width << " " << height << "\n";
    file << "255\n";

    for (const Color& c : pixels) {
        file << toByte(c.r) << " " << toByte(c.g) << " " << toByte(c.b) << "\n";
    }
}
