#pragma once

#include <memory>
#include <vector>

#include "camera/Camera.hh"
#include "light/Light.hh"
#include "object/Objects.hh"

class Object;

class Scene {
public:
    Camera camera;
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<Light>> lights;

    explicit Scene(const Camera& camera) : camera(camera) {}

    void addObject(const std::shared_ptr<Object>& object) {
        objects.push_back(object);
    }

    void addLight(const std::shared_ptr<Light>& light) {
        lights.push_back(light);
    }
};
