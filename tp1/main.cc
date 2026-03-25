#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

#include "camera/Camera.hh"
#include "image/Image.hh"
#include "light/PointLight.hh"
#include "object/Sphere.hh"
#include "scene/Scene.hh"
#include "texture/UniformTexture.hh"
#include "vector3/Vector3.hh"

Colors trace(Ray& ray, Scene& scene, int depth = 0)
{
    if (depth > 6)
        return Colors(0, 0, 0);

    float distMin = std::numeric_limits<float>::infinity();
    Object* nearestObj = nullptr;

    for (size_t k = 0; k < scene.objects.size(); k++)
    {
        float distTemp = std::numeric_limits<float>::infinity();
        if (scene.objects[k]->intersect(ray, distTemp) && distTemp > 0.0f)
        {
            if (distTemp < distMin)
            {
                distMin = distTemp;
                nearestObj = scene.objects[k];
            }
        }
    }

    if (nearestObj == nullptr)
    {
        return Colors(0, 0, 100);
    }

    Vector3 p = ray.origin - ray.direction * (-distMin);
    Vector3 normal = nearestObj->normal(p).normalized();
    MaterialInfo mat = (*nearestObj).getMaterial(p);
    const float ambientStrength = 0.12f;
    float accR = mat.color.r * ambientStrength;
    float accG = mat.color.g * ambientStrength;
    float accB = mat.color.b * ambientStrength;

    for (size_t k = 0; k < scene.ligths.size(); k++)
    {
        Vector3 l = (scene.ligths[k]->getPosition() - p).normalized();
        float cosNL = std::max(0.f, normal.dot(l));

        float specularContribution = 0.f;
        if (cosNL > 0.f)
        {
            Vector3 v = (ray.direction * -1.0f).normalized();
            Vector3 r = (normal * (2.f * normal.dot(l)) - l).normalized();
            float cosAlpha = std::max(0.f, v.dot(r));
            float specular = std::pow(cosAlpha, mat.ns);
            specularContribution = 255.f * mat.ks * specular;
        }

        Vector3 toLight = scene.ligths[k]->getPosition() - p;
        float distLight = toLight.norm();
        Vector3 normalized = toLight.normalized();

        const float eps = 1e-4f;
        Ray shadow = Ray(normalized, p - normal * (-eps));
        bool hidden = false;
        for (Object* obj : scene.objects) {
            if (obj == nearestObj) {
                continue;
            }
            float distShadow = 0;
            if (obj->intersect(shadow, distShadow) && distShadow > eps && distShadow < distLight - eps) {
                hidden = true;
                break;
            }
        }
        if (hidden) continue;

        accR += mat.color.r * mat.kd * cosNL + specularContribution;
        accG += mat.color.g * mat.kd * cosNL + specularContribution;
        accB += mat.color.b * mat.kd * cosNL + specularContribution;
    }

    const float kr = mat.ks;
    Vector3 d = ray.direction.normalized();

    Vector3 n = normal;
    if (d.dot(n) > 0.0f)
    {
        n = n * -1.0f;
    }

    Vector3 reflectedDir = (d - n * (2.0f * d.dot(n))).normalized();

    const float eps = 1e-4f;
    Vector3 reflectedOrigin = p - n * (-eps);

    Ray reflectedRay(reflectedDir, reflectedOrigin);
    Colors reflected = trace(reflectedRay, scene, depth + 1);

    accR += kr * reflected.r;
    accG += kr * reflected.g;
    accB += kr * reflected.b;

    accR = std::clamp(accR, 0.f, 255.f);
    accG = std::clamp(accG, 0.f, 255.f);
    accB = std::clamp(accB, 0.f, 255.f);

    Colors c = Colors(accR, accG, accB);
    return c;
}

void raycast(Image& image, Scene& scene)
{
    for (int j = 0; j < image.height; j++)
    {
        for (int i = 0; i < image.width; i++)
        {
            Vector3 pixelCenter =
                scene.camera.pixelCenter(i, j, image.width, image.height);
            Ray ray = Ray((pixelCenter - scene.camera.C).normalized(),
                          scene.camera.C);

            Colors c = trace(ray, scene);
            image.setPixel(c, i, j);
        }
    }
}

int main()
{
    Camera camera = Camera(Vector3(0., 0., -5.), Vector3(0., 0., 0.),
                           Vector3(0., 1., 0.), 1.0472f, 0.7854f, 1.0f);

    std::vector<Object*> objects;
    
    MaterialInfo material =
        MaterialInfo(0.8f, 0.3f, 32.0f, Colors(204, 51, 51));
    UniformTexture texture = UniformTexture(material);
    Sphere sphere = Sphere(Vector3(-2.3, 0., 0.), 1., &texture);
    
    MaterialInfo material2 =
        MaterialInfo(0.8f, 0.3f, 32.0f, Colors(0, 200, 0));
    UniformTexture texture2 = UniformTexture(material2);
    Sphere sphere2 = Sphere(Vector3(-0., 0., 0.), 1., &texture2);


    MaterialInfo material3 =
        MaterialInfo(0.8f, 0.3f, 32.0f, Colors(0, 100, 150));
    UniformTexture texture3 = UniformTexture(material3);
    Sphere sphere3 = Sphere(Vector3(2.3, 0., 0.), 1., &texture3);


    objects.push_back(&sphere);
    objects.push_back(&sphere2);
    objects.push_back(&sphere3);


    std::vector<Light*> lights;
    PointLight light = PointLight(Vector3(3., 2., -5.));
    PointLight light2 = PointLight(Vector3(5., 4., 7.));
    lights.push_back(&light);
    lights.push_back(&light2);

    Scene scene = Scene(objects, lights, camera);

    Image image = Image(800, 600);

    raycast(image, scene);

    image.savePPM("result.ppm");

    return 0;
}