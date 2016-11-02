// #include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "lodepng.h"
// #include "ResourcePath.hpp"
using namespace std;

template<typename T>
class Vector3 {
public:
    T x, y, z;
};

typedef Vector3<float> Vector3f;

class Sphere {
    Vector3f center;
    float radius;
    Vector3f color;
};

Vector3f trace() {
    
}

void render() {
    
}

int main(int, char const**)
{
    cout << "hello, sfml" << endl;
    
    int width = 200;
    int height = 200;
    std::vector<unsigned char> image;
    for (int row = 0; row < width; row++) {
        for (int col = 0; col < height; col++) {
            if (col % 10 < 5 || row % 10 < 5) {
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
