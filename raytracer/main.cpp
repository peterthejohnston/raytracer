// #include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "lodepng.h"
#include <math.h>
using namespace std;

template<typename T>
class Vector3 {
public:
    T x, y, z;
    Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
    Vector3(T x) : x(x), y(x), z(x) {}
    Vector3<T> operator - (const Vector3<T> &v) const {
        return Vector3<T>(x - v.x, y - v.y, z - v.z);
    }
    Vector3<T> operator + (const Vector3<T> &v) const {
        return Vector3<T>(x + v.x, y + v.y, z + v.z);
    }
    Vector3<T> operator * (const Vector3<T> &v) const {
        return Vector3<T>(v.x * x, v.y * y, v.z * z);
    }
    Vector3<T> operator * (const T &f) const {
        return Vector3<T>(x * f, y * f, z * f);
    }
    T dot(const Vector3<T> &v) const {
        return x * v.x + y * v.y + z * v.z;
    }
};

bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1) {
    float discr = b * b - 4 * a * c;
    // case 1: no solutions
    if (discr < 0)
        return false;
    // case 2: one solution
    else if (discr == 0)
        x0 = - b / (2 * a);
    // case 3: two solutions
    else {
        float q = (b >= 0) ?
            - 0.5 * (b + sqrt(discr)) :
            - 0.5 * (b - sqrt(discr));
        x0 = q / a;
        x1 = c / q;
    }
    if (x0 > x1) swap(x0, x1);
    
    return true;
}

typedef Vector3<float> Vector3f;

class Sphere {
public:
    Vector3f center;
    float radius;
    Vector3f color;
    
    Sphere(Vector3f center, float radius, Vector3f color):
        center(center), radius(radius), color(color) {}
    
    bool intersect(Vector3f origin, Vector3f dir, float &t) {
        Vector3f l = origin - center;

        float a = dir.dot(dir);
        float b = 2 * dir.dot(l);
        float c = l.dot(l) - radius * radius;
        
        float x0, x1;
        if (!solveQuadratic(a, b, c, x0, x1)) return false;
        if (x0 < 0) {
            x0 = x1;
            if (x0 < 0) return false;
        }
        
        t = x0;
        return true;
    }
};

Vector3f trace() {
    
}

void render() {
    
}

int main(int, char const**)
{
    Sphere sphere = Sphere(Vector3<float>(0), 100, Vector3<float>(0, 0, 0));
    Vector3<float> ray_origin = Vector3<float>(-200, 0, 0);
    Vector3<float> ray_dir = Vector3<float>(1, 0, 0);
    float t = 0;
    bool hit = sphere.intersect(ray_origin, ray_dir, t);
    float x = ray_origin.x + ray_dir.x * t;
    float y = ray_origin.y + ray_dir.y * t;
    float z = ray_origin.z + ray_dir.z * t;
    
    if (hit)
        cout << "The ray intersects the sphere at x = " + to_string(x) + ", y = " + to_string(y) + ", z = " + to_string(z);
    else cout << "The ray does not intersect the sphere.";
    
    // print checkerboard to .png
    int width = 200;
    int height = 200;
    std::vector<unsigned char> image;
    for (int row = 0; row < width; row++) {
        for (int col = 0; col < height; col++) {
            if ((row % 20 < 10 && col % 20 < 10) || (row % 20 >= 10 && col % 20 >= 10)) {
                image.push_back((unsigned char)0); // r
                image.push_back((unsigned char)0); // g
                image.push_back((unsigned char)0); // b
                image.push_back((unsigned char)255); // a
            }
            else {
                image.push_back((unsigned char)255); // r
                image.push_back((unsigned char)255); // g
                image.push_back((unsigned char)255); // b
                image.push_back((unsigned char)255); // a
            }
        }
    }
    
    unsigned error = lodepng::encode("img.png", image, width, height);
    
    // if there's an error, display it
    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
    
    return 0;

    /*
    for (int j = 0; j < imageHeight; ++j) {
        for (int i = 0; i < imageWidth; ++i) {
            // compute primary ray direction
            Ray primRay;
            computePrimRay(i, j, &primRay);
            // shoot prim ray in the scene and search for intersection
            Point pHit;
            Normal nHit;
            float minDist = INFINITY;
            Object object = NULL;
            for (int k = 0; k < objects.size(); ++k) {
                if (Intersect(objects[k], primRay, &pHit, &nHit)) {
                    float distance = Distance(eyePosition, pHit);
                    if (distance < minDistance) {
                        object = objects[k];
                        minDistance = distance; // update min distance
                    }
                }
            }
            if (object != NULL) {
                // compute illumination
                Ray shadowRay;
                shadowRay.direction = lightPosition - pHit;
                bool isShadow = false;
                for (int k = 0; k < objects.size(); ++k) {
                    if (Intersect(objects[k], shadowRay)) {
                        isInShadow = true;
                        break;
                    }
                }
            }
            if (!isInShadow)
                pixels[i][j] = object->color * light.brightness; 
            else 
                pixels[i][j] = 0;
        } 
    }
     */
}
