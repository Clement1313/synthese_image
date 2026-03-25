#pragma once

#include <vector>

#include "../object/Object.hh"
#include "../light/Light.hh"
#include "../camera/Camera.hh"

class Scene
{
public:
    std::vector<Object*> objects;
    std::vector<Light*> ligths;
    Camera camera;
    
    Scene(std::vector<Object*> objects, std::vector<Light*> ligths, Camera camera): objects(objects), ligths(ligths), camera(camera) {}
    Scene();
};