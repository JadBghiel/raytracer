#include <iostream>
#include "Sphere.hpp"

//tested by gerardinho
int main()
{
    RayTracer::Sphere sphere({0, 0, -3}, 1.0, {255, 0, 0});

    // ray pointing straight at the sphere → should hit
    RayTracer::Ray rayHit({0,0,0}, {0,0,-1});
    RayTracer::HitRecord rec1 = sphere.intersect(rayHit, 0.001, 1e9);
    if (rec1.hit)
        std::cout << "HIT at t=" << rec1.t << "\n";
    else
        std::cout << "NO HIT\n";

    // ray pointing away from sphere → should NOT hit
    RayTracer::Ray rayMiss({0,0,0}, {0,0,1});
    RayTracer::HitRecord rec2 = sphere.intersect(rayMiss, 0.001, 1e9);
    if (rec2.hit)
        std::cout << "HIT at t=" << rec2.t << "\n";
    else
        std::cout << "NO HIT\n";

    return 0;
}