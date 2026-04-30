#include <iostream>
#include "Sphere.hpp"
#include "Plane.hpp"

//tested by gerardinho
int main()
{
    RayTracer::Sphere sphere({0, 0, -3}, 1.0, {255, 0, 0});

    // ray pointing straight at the sphere → should hit
    RayTracer::Ray rayHit({0,0,0}, {0,0,-1});
    RayTracer::HitRecord rec1 = sphere.intersect(rayHit, 0.001, 1e9);
    std::cout << "--- SPHERE TESTING ---" << std::endl;
    if (rec1.hit)
        std::cout << "HIT at t=" << rec1.t << "\n";
    else
        std::cout << "NO HIT\n";

    // ray pointing away from sphere → should NOT hit
    RayTracer::Ray rayMiss({0,0,0}, {0,0,1});
    RayTracer::HitRecord rec2 = sphere.intersect(rayMiss, 0.001, 1e9);
    std::cout << "--- PLANE TESTING ---" << std::endl;
    if (rec2.hit)
        std::cout << "HIT at t=" << rec2.t << "\n";
    else
        std::cout << "NO HIT\n";

    // ray going down toward a Y plane at position -3 → should hit at t=3
    RayTracer::Plane plane("Y", -3.0, {0, 255, 0});
    RayTracer::Ray rayDown({0,0,0}, {0,-1,0});
    RayTracer::HitRecord rec3 = plane.intersect(rayDown, 0.001, 1e9);
    if (rec3.hit)
        std::cout << "Plane HIT at t=" << rec3.t << "\n";
    else
        std::cout << "Plane NO HIT\n";

    // ray parallel to the plane → should NOT hit
    RayTracer::Ray rayParallel({0,0,0}, {1,0,0});
    RayTracer::HitRecord rec4 = plane.intersect(rayParallel, 0.001, 1e9);
    if (rec4.hit)
        std::cout << "Plane HIT at t=" << rec4.t << "\n";
    else
        std::cout << "Plane NO HIT\n";
    return 0;
}
