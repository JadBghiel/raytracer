#include <iostream>
#include "Sphere.hpp"
#include "Plane.hpp"

// tested by gerardinho

int main()
{
    std::cout << "========================================\n";
    std::cout << "        PRIMITIVE INTERSECTION TESTS    \n";
    std::cout << "========================================\n\n";

    // --- SPHERE ---
    RayTracer::Sphere sphere({0, 0, -3}, 1.0, {255, 0, 0});

    std::cout << "--- SPHERE TESTS ---\n";

    RayTracer::Ray rayHit({0,0,0}, {0,0,-1});
    RayTracer::HitRecord rec1 = sphere.intersect(rayHit, 0.001, 1e9);
    std::cout << "[direct hit]  expected: HIT t=2  | got: ";
    std::cout << (rec1.hit ? "HIT t=" + std::to_string(rec1.t) : "NO HIT") << "\n";

    RayTracer::Ray rayMiss({0,0,0}, {0,0,1});
    RayTracer::HitRecord rec2 = sphere.intersect(rayMiss, 0.001, 1e9);
    std::cout << "[wrong dir]   expected: NO HIT   | got: ";
    std::cout << (rec2.hit ? "HIT t=" + std::to_string(rec2.t) : "NO HIT") << "\n";

    // --- PLANE ---
    RayTracer::Plane plane("Y", -3.0, {0, 255, 0});

    std::cout << "\n--- PLANE TESTS ---\n";

    RayTracer::Ray rayDown({0,0,0}, {0,-1,0});
    RayTracer::HitRecord rec3 = plane.intersect(rayDown, 0.001, 1e9);
    std::cout << "[direct hit]  expected: HIT t=3  | got: ";
    std::cout << (rec3.hit ? "HIT t=" + std::to_string(rec3.t) : "NO HIT") << "\n";

    RayTracer::Ray rayParallel({0,0,0}, {1,0,0});
    RayTracer::HitRecord rec4 = plane.intersect(rayParallel, 0.001, 1e9);
    std::cout << "[parallel]    expected: NO HIT   | got: ";
    std::cout << (rec4.hit ? "HIT t=" + std::to_string(rec4.t) : "NO HIT") << "\n";

    std::cout << "\n========================================\n";
    return 0;
}
