
#ifndef __RAY__
#define __RAY__
#include "shape.h"
class ray
{
public:
    vec3 *origin, *direction;
    const parser::Scene *scene;
    bool isPrimary = true;
    ray() : origin(new vec3()), direction(new vec3()){};
    ray(const parser::Vec3f &origin__, const vec3 &direction__, const parser::Scene *scene__)
    {
        direction = new vec3(direction__);
        origin = new vec3(origin__);
        scene = scene__;
    };
    ray(const vec3 &origin__, const vec3 &direction__, const parser::Scene *scene__)
    {
        direction = new vec3(direction__);
        origin = new vec3(origin__);
        scene = scene__;
    };
    ray(const ray &r, const parser::Scene *scene__)
    {
        direction = new vec3(*r.direction);
        origin = new vec3(*r.origin);
        scene = scene__;
    }
    float intersect(const parser::Sphere &sphere) const;
    float intersect(const parser::Face &face) const;
    float intersect(triangle &__triangle__) const;
    static float discriminant(float a, float b, float c);
    void notPrimary() {
        this->isPrimary = false;
    }
};
float ray::discriminant(float a, float b, float c)
{
    float retval = b * b - 4 * a * c;
    return retval;
}

float ray::intersect(const parser::Sphere &sphere) const
{
    parser::Vec3f thing = this->scene->vertex_data[sphere.center_vertex_id - 1];
    vec3 center(thing.x, thing.y, thing.z);
    float radius = sphere.radius;
    vec3 ocenter = *(this->origin) - center;
    float a = vec3::dot(*(this->direction), *(this->direction));
    float b = 2.0 * vec3::dot(*(this->direction), ocenter);
    float c = vec3::dot(ocenter, ocenter) - radius * radius;
    float d = ray::discriminant(a, b, c);
    if (d < 0)
        return -1.0;
    float t1 = (-b + sqrt(d)) / (2 * a);
    float t2 = (-b - sqrt(d)) / (2 * a);
    return t1 > t2 ? t2 : t1;
}
float ray::intersect(const parser::Face &face) const
{
    vec3 vp, va, vb, vc;
    vec3 a = vec3(this->scene->vertex_data[face.v0_id - 1]);
    vec3 b = vec3(this->scene->vertex_data[face.v1_id - 1]);
    vec3 c = vec3(this->scene->vertex_data[face.v2_id - 1]);
    vec3 normal = vec3::cross((c - b), (a - b));
    float parallelCheck = vec3::dot(normal, *direction);
    if (fabs(parallelCheck) < scene->shadow_ray_epsilon)
        return -1.0;
    float d = vec3::dot(normal, a);
    float t = (d - vec3::dot(normal, *origin)) / parallelCheck;
    vec3 intersectionPoint = (*origin) + (*direction) * t;
    va = vec3::cross(b - a, intersectionPoint - a);
    if (vec3::dot(va, normal) < 0)
        return -1.0;
    vb = vec3::cross(c - b, intersectionPoint - b);
    if (vec3::dot(vb, normal) < 0)
        return -1.0;
    vc = vec3::cross(a - c, intersectionPoint - c);
    if (vec3::dot(vc, normal) < 0)
        return -1.0;
    return t;
}

float ray::intersect(triangle &__triangle__) const
{
    vec3 vp, va, vb, vc;
    vec3 a = vec3(this->scene->vertex_data[__triangle__.indices.v0_id - 1]);
    vec3 b = vec3(this->scene->vertex_data[__triangle__.indices.v1_id - 1]);
    vec3 c = vec3(this->scene->vertex_data[__triangle__.indices.v2_id - 1]);
    vec3 normal = __triangle__.normal;
    float parallelCheck = vec3::dot(normal, *direction);
    if (fabs(parallelCheck) < scene->shadow_ray_epsilon)
        return -1.0;
    float d = vec3::dot(normal, a);
    float t = (d - vec3::dot(normal, *origin)) / parallelCheck;
    vec3 intersectionPoint = *origin + *direction * t;
    va = vec3::cross(b - a, intersectionPoint - a);
    if (vec3::dot(va, normal) < 0)
        return -1.0;
    vb = vec3::cross(c - b, intersectionPoint - b);
    if (vec3::dot(vb, normal) < 0)
        return -1.0;
    vc = vec3::cross(a - c, intersectionPoint - c);
    if (vec3::dot(vc, normal) < 0)
        return -1.0;
    return t;
}

#endif