#include <vector>
#include <limits>
#include <algorithm>
#include <cmath>

#include "camera/Camera.hh"
#include "vector3/Vector3.hh"
#include "scene/Scene.hh"
#include "object/Sphere.hh"
#include "texture/UniformTexture.hh"
#include "light/PointLight.hh"
#include "image/Image.hh"


Colors trace(Ray *ray, Scene &scene, int depth = 0) {
    
}

void raycast(Image& image, Scene& scene) {
    for (int j = 0; j < image.height; j++) {
        for (int i = 0; i < image.width; i++) {
            Vector3 pixelCenter = scene.camera.pixelCenter(i, j, image.width, image.height);
            Ray ray = Ray((pixelCenter - scene.camera.C).normalized(), scene.camera.C);

            // Colors c = trace(&ray, scene);




            float distMin = std::numeric_limits<float>::infinity();
            Object* nearestObj = nullptr;

            for (size_t k = 0; k < scene.objects.size(); k++) {
                float distTemp = std::numeric_limits<float>::infinity();
                if(scene.objects[k]->intersect(ray, distTemp) && distTemp > 0.0f) {
                    if (distTemp < distMin) {
                        distMin = distTemp;
                        nearestObj = scene.objects[k];
                    }
                }
            }

            if (nearestObj == nullptr) {
                image.setPixel(Colors(0, 0, 0), i, j);
                continue;
            }
            
            Vector3 p = ray.origin - ray.direction * (-distMin);
            Vector3 normal = nearestObj->normal(p).normalized();
            MaterialInfo mat = (*nearestObj).getMaterial(p);
            float accR = 0.f, accG = 0.f, accB = 0.f;
            for (size_t k = 0; k < scene.ligths.size(); k++) {
                Vector3 l = (scene.ligths[k]->getPosition() - p).normalized();
                float cosNL = std::max(0.f, normal.dot(l));

                float specularContribution = 0.f;
                if (cosNL > 0.f) {
                    Vector3 v = (scene.camera.C - p).normalized();
                    Vector3 r = (normal * (2.f * normal.dot(l)) - l).normalized();
                    float cosAlpha = std::max(0.f, v.dot(r));
                    float specular = std::pow(cosAlpha, mat.ns);
                    specularContribution = 255.f * mat.ks * specular;
                }

                accR += mat.color.r * mat.kd * cosNL + specularContribution;
                accG += mat.color.g * mat.kd * cosNL + specularContribution;
                accB += mat.color.b * mat.kd * cosNL + specularContribution;
            }



            accR = std::clamp(accR, 0.f, 255.f);
            accG = std::clamp(accG, 0.f, 255.f);
            accB = std::clamp(accB, 0.f, 255.f);

            Colors c = Colors(accR, accG, accB);
            image.setPixel(c, i, j);
        }
    }
}


int main() {
    Camera camera = Camera(Vector3(0.,0.,-5.),
                           Vector3(0.,0.,0.),
                           Vector3(0.,1.,0.),
                           1.0472f, 0.7854f, 1.0f);

    std::vector<Object*> objects;
    MaterialInfo material = MaterialInfo(0.8f, 0.3f, 32.0f, Colors(204, 51, 51));
    UniformTexture texture = UniformTexture(material);
    Sphere sphere = Sphere(Vector3(-1.,0.,0.), 1., &texture);
    Sphere sphere2 = Sphere(Vector3(1.,0.,0.), 1., &texture);

    objects.push_back(&sphere);
    objects.push_back(&sphere2);

    std::vector<Light*> lights;
    PointLight light = PointLight(Vector3(3.,2.,-5.));
    lights.push_back(&light);

    Scene scene = Scene(objects, lights, camera);

    Image image = Image(800, 600);

    raycast(image, scene);
    
    image.savePPM("result.ppm");

    return 0;
}