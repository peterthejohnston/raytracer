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
    Vector3<T>& operator *= (const T &f) {
        x *= f, y *= f, z *= f; return *this;
    }
    T magnitude() const {
        return sqrt(x * x + y * y + z * z);
    }
    T dot(const Vector3<T> &v) const {
        return x * v.x + y * v.y + z * v.z;
    }
    Vector3<T>& normalize() {
        T magnitude = this->magnitude();
        if (magnitude > 0) {
            (*this) *= ((T)1 / magnitude);
        }
        return *this;
    }
};

typedef Vector3<float> Vector3f;

bool solve_quadratic(const float &a, const float &b, const float &c, float &x0, float &x1) {
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

class Sphere {
public:
    Vector3f center;
    float radius;
    Vector3<uint8_t> color;
    
    Sphere(Vector3f center, float radius, Vector3<uint8_t> color):
        center(center), radius(radius), color(color) {}
    
    bool intersect(Vector3f origin, Vector3f dir, float &t) {
        Vector3f l = origin - center;

        float a = dir.dot(dir);
        float b = 2 * dir.dot(l);
        float c = l.dot(l) - radius * radius;
        
        float x0, x1;
        if (!solve_quadratic(a, b, c, x0, x1)) return false;
        if (x0 < 0) {
            x0 = x1;
            if (x0 < 0) return false;
        }
        
        t = x0;
        return true;
    }
};

float deg2rad(float deg) {
    return deg * M_PI / 180;
}

void render(vector<Sphere> &spheres, int width, int height, vector<unsigned char> &image) {
    // for each pixel
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            // construct primary ray
            Vector3f prim_ray_orig = Vector3f(col, row, 0);
            Vector3f prim_ray_dir = Vector3f(0, 0, 1);
            
            // cast the ray and trace it back and loop thru all the objects
            float min_dist = INFINITY;
            const Sphere* sphere = NULL;
            float t;
            for (int i = 0; i < spheres.size(); i++) {
                // test for intersection, find min distance
                if (spheres[i].intersect(prim_ray_orig, prim_ray_dir, t)) {
                    if (t < min_dist) {
                        min_dist = t;
                        sphere = &spheres[i];
                    }
                }
            }
            
            // if there is an object, compute color
            if (!sphere) {
                image[row * width * 4 + col * 4] = 0; // r
                image[row * width * 4 + col * 4 + 1] = 0; // g
                image[row * width * 4 + col * 4 + 2] = 0; // b
                image[row * width * 4 + col * 4 + 3] = 255; // a
            }
            else {
                uint8_t r = sphere->color.x;
                uint8_t g = sphere->color.y;
                uint8_t b = sphere->color.z;
                uint8_t a = 255;
                
                // set brightness
                Vector3f hit_point = prim_ray_orig + prim_ray_dir * min_dist;
                Vector3f light = Vector3f(-100, -100, 0);
                Vector3f hit_normal = hit_point - sphere->center;
                hit_normal.normalize();
                Vector3f light_to_hit = hit_point - light;
                light_to_hit.normalize();
                float angle = acos(light_to_hit.dot(hit_normal));
                float brightness = angle / M_PI;
                r = min((uint8_t)((float)r * brightness), (uint8_t)255);
                g = min((uint8_t)((float)g * brightness), (uint8_t)255);
                b = min((uint8_t)((float)b * brightness), (uint8_t)255);
                
                // figure out if there's a shadow
                // trace shadow ray
                /*
                Vector3f light_dir = light - hit_point;
                float d = 0;
                for (int i = 0; i < spheres.size(); i++) {
                    // test for intersection
                    if (spheres[i].intersect(hit_point, light_dir, d)) {
                        r = 0;
                        g = 0;
                        b = 0;
                        break;
                    }
                }
                */
                
                // reflection
                
                // add to image[]
                image[row * width * 4 + col * 4] = r;
                image[row * width * 4 + col * 4 + 1] = g;
                image[row * width * 4 + col * 4 + 2] = b;
                image[row * width * 4 + col * 4 + 3] = a;
            }
        }
    }
}

int main()
{
    // fill up list with random spheres
    vector<Sphere> spheres;
    int num_spheres = 20;
    srand(time(NULL));
    for (int i = 0; i < num_spheres; i++) {
        float x = rand() % 1000;
        float y = rand() % 1000;
        float z = rand() % 1000;
        float radius = rand() % 100 + 20;
        uint8_t r = rand() % 255;
        uint8_t g = rand() % 255;
        uint8_t b = rand() % 255;
        spheres.push_back(Sphere(Vector3f(x, y, z), radius, Vector3<uint8_t>(r, g, b)));
    }
    
    // render them
    int width = 800;
    int height = 600;
    vector<unsigned char> image;
    image.resize(width * height * 4);
    render(spheres, width, height, image);
    
    // save pixels to .png
    unsigned error = lodepng::encode("img.png", image, width, height);
    if(error) cout << "encoder error " << error << ": "<< lodepng_error_text(error) << endl;
    
    return 0;
}
