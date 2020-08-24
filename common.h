//
// Created by HeshmatiRød on 8/23/2020.
//

#ifndef RAY_TRACING_COMMON_H
#define RAY_TRACING_COMMON_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <cstdlib>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double pi = M_PI;
const double inf = std::numeric_limits<double>::infinity();

// Utility Functions
inline double deg2rad(double degrees){
    return degrees * pi / 180.;
}

inline double random_double() {
    // Returns a random real in [0, 1)
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min, max)
    return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

#include "ray.h"
#include "vec3.h"

#endif //RAY_TRACING_COMMON_H
