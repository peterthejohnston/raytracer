
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

int main(int, char const**)
{
    std::cout << "hello, sfml";
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
