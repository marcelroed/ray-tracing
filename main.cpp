#include "common.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

#include <iostream>
#include <chrono>

using std::chrono::duration_cast;

color ray_color(const ray& r, const Hittable& world, int depth){
    hit_record rec;

    if (depth <= 0)
        return color(0, 0, 0);

    if (world.hit(r, 0.001, inf, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return color(0, 0, 0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main(int argc, char** argv) {

    // Image
    const double aspect_ratio = 16. / 9.;
    const int image_height = atoi(argv[1]);
    const int image_width = static_cast<int>(aspect_ratio * image_height);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // World
    HittableList world;

    auto material_ground = make_shared<Metal>(color(81./255, 76./255, 91./255), 0.00002);
    auto material_center = make_shared<Lambertian>(color(.7, .3, .3));
    auto material_left = make_shared<Metal>(color(0.8, 0.8, 0.8), 0);
    auto material_right = make_shared<Metal>(color(0.8, 0.6, 0.2), 0);

    world.add(make_shared<Sphere>(point3(0, -100.5, -1), 100, material_ground));
    world.add(make_shared<Sphere>(point3(0, 0, -1), 0.5, material_center));
    world.add(make_shared<Sphere>(point3(-1., 0, -1), 0.5, material_left));
    world.add(make_shared<Sphere>(point3(1., 0, -1), 0.5, material_right));


    // Camera
    Camera cam;


    // Render

    std::cerr << image_height << ' ' << image_width << '\n';

    std::cout << "P3\n" << image_width << ' ' << image_height <<  "\n255\n";

    auto prev = std::chrono::system_clock::now();
    for (int j = image_height - 1; j >= 0; --j) {
        auto now = std::chrono::system_clock::now();
        std::cerr << "\rScanlines remaining: " << j << ' '
                  << "Time: " << ((j == image_height - 1) ? 0. : duration_cast<std::chrono::milliseconds>(now - prev).count()*j) / 1000. << std::flush;
        prev = now;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s){
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone\n";

    return 0;
}
