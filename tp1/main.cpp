#include <algorithm>
#include <cmath>
#include <limits>
#include <memory>

#include "Scene.hh"
#include "light/PointLight.hh"
#include "material/UniformTexture.hh"
#include "object/Sphere.hh"
#include "image/Image.hh"

int main() {
    Camera camera(
        Vector3(0.0f, 0.0f, -5.0f),
        Vector3(0.0f, 0.0f, 0.0f),
        Vector3(0.0f, 1.0f, 0.0f),
        1.0472f,
        0.7854f,
        1.0f
    );

    Scene scene(camera);

    auto material = std::make_shared<UniformTexture>(
        MaterialSample(Color(0.8f, 0.2f, 0.2f), 0.8f, 0.3f, 32.0f)
    );

    auto sphere = std::make_shared<Sphere>(
        Vector3(0.0f, 0.0f, 2.0f),
        1.0f,
        material.get()
    );

    auto sphere2 = std::make_shared<Sphere>(
        Vector3(2.0f, 0.0f, 2.0f),
        1.0f,
        material.get()
    );

    auto light = std::make_shared<PointLight>(Vector3(-2.0f, 3.0f, -1.0f));

    scene.addObject(sphere);
    scene.addObject(sphere2);
    scene.addLight(light);

    Image img = Image(800, 600);

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            Vector3 pixel = scene.camera.pixelCenter(x, y, img.width, img.height);
            Vector3 direction = (pixel - scene.camera.C).normalized();
            Ray ray(scene.camera.C, direction);

            float bestT = std::numeric_limits<float>::max();
            std::shared_ptr<Object> bestObject = nullptr;

            for (size_t i = 0; i < scene.objects.size(); i++) {
                float t = 0.0f;
                if (scene.objects[i]->intersect(ray, t) && t < bestT) {
                    bestT = t;
                    bestObject = scene.objects[i];
                }
            }
            

            if (bestObject == nullptr) {
                img.setPixel(x, y, Color(0.1f, 0.1f, 0.2f));
                continue;
            }

            Vector3 hitPoint = ray.origin + ray.direction * bestT;
            Vector3 normal = bestObject->normalAt(hitPoint);
            MaterialSample materialSample = bestObject->material->sample(hitPoint);

            Vector3 lightDirection = (scene.lights[0]->getPosition() - hitPoint).normalized();
            Vector3 viewDirection = (scene.camera.C - hitPoint).normalized();
            Vector3 reflectedDirection = (normal * (2.0f * normal.dot(lightDirection)) - lightDirection).normalized();

            float ambient = 0.1f;
            float diffuse = std::max(0.0f, normal.dot(lightDirection)) * materialSample.kd;
            float specular = std::pow(
                std::max(0.0f, reflectedDirection.dot(viewDirection)),
                materialSample.ns
            ) * materialSample.ks;

            float intensity = ambient + diffuse;

            float r = materialSample.color.r * intensity + specular;
            float g = materialSample.color.g * intensity + specular;
            float b = materialSample.color.b * intensity + specular;

            r = std::clamp(r, 0.0f, 1.0f);
            g = std::clamp(g, 0.0f, 1.0f);
            b = std::clamp(b, 0.0f, 1.0f);

            img.setPixel(x, y, Color(r, g, b));
        }
    }

    img.savePPM("render.ppm");

    return 0;
}