#include <iostream>
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Cylinder.hpp"

// tested by gerardinho
// compile with:
//  g++ -std=c++17 -I include test/test_primitives.cpp src/Sphere.cpp src/Plane.cpp src/Cylinder.cpp -o test_primitives && ./test_primitives

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

    // --- CYLINDER ---
    // cylinder at (0,0,-5), radius=1, height=4
    RayTracer::Cylinder cylinder({0, 0, -5}, 1.0, 4.0, {0, 0, 255});

    std::cout << "\n--- CYLINDER TESTS ---\n";

    // ray pointing straight at the body → should hit
    RayTracer::Ray rayBody({0,0,0}, {0,0,-1});
    RayTracer::HitRecord rec5 = cylinder.intersect(rayBody, 0.001, 1e9);
    std::cout << "[body hit]    expected: HIT t=4  | got: ";
    std::cout << (rec5.hit ? "HIT t=" + std::to_string(rec5.t) : "NO HIT") << "\n";

    // ray pointing at top cap from above → should hit
    RayTracer::Ray rayTop({0, 5, -5}, {0,-1,0});
    RayTracer::HitRecord rec6 = cylinder.intersect(rayTop, 0.001, 1e9);
    std::cout << "[top cap]     expected: HIT t=3  | got: ";
    std::cout << (rec6.hit ? "HIT t=" + std::to_string(rec6.t) : "NO HIT") << "\n";

    // ray pointing at bottom cap from below → should hit
    RayTracer::Ray rayBot({0, -5, -5}, {0,1,0});
    RayTracer::HitRecord rec7 = cylinder.intersect(rayBot, 0.001, 1e9);
    std::cout << "[bot cap]     expected: HIT t=3  | got: ";
    std::cout << (rec7.hit ? "HIT t=" + std::to_string(rec7.t) : "NO HIT") << "\n";

    // ray missing completely → should NOT hit
    RayTracer::Ray rayMiss2({5,0,0}, {0,0,-1});
    RayTracer::HitRecord rec8 = cylinder.intersect(rayMiss2, 0.001, 1e9);
    std::cout << "[miss]        expected: NO HIT   | got: ";
    std::cout << (rec8.hit ? "HIT t=" + std::to_string(rec8.t) : "NO HIT") << "\n";

    std::cout << "\n========================================\n";
    return 0;
}