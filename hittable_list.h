//
// Created by HeshmatiRød on 8/23/2020.
//

#ifndef RAY_TRACING_HITTABLE_LIST_H
#define RAY_TRACING_HITTABLE_LIST_H

#include "hittable.h"
#include <memory>
#include <vector>
#include <iostream>

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable {
public:
    HittableList() {}
    HittableList(shared_ptr<Hittable> object) {add(object);}

    void clear() {objects.clear();}
    void add(shared_ptr<Hittable> object) {objects.push_back(object);}

    virtual bool hit(
            const ray& r, double tmin, double tmax, hit_record& rec) const override;

public:
    std::vector<shared_ptr<Hittable>> objects;
};

bool HittableList::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

#endif //RAY_TRACING_HITTABLE_LIST_H
