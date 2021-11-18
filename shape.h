#ifndef __SHAPE_H__
#define __SHAPE_H__
#include "vec3.h"
#include "parser.h"

class triangle
{
public:
    int material_id;
    parser::Face indices;
    vec3 normal;
    triangle(const parser::Triangle &t) : indices(t.indices), material_id(t.material_id) {}
    triangle(const parser::Face &indices__, int material_id) : material_id(material_id)
    {
        indices.v0_id = indices__.v0_id;
        indices.v1_id = indices__.v1_id;
        indices.v2_id = indices__.v2_id;
    }
    triangle(const triangle &t) : indices(t.indices), normal(t.normal), material_id(t.material_id) {}
    void set_normal(vec3 n)
    {
        this->normal = vec3(n);
    }
    void calculate_normal(const parser::Scene &scene)
    {
        vec3 a = vec3(scene.vertex_data[this->indices.v0_id - 1]);
        vec3 b = vec3(scene.vertex_data[this->indices.v1_id - 1]);
        vec3 c = vec3(scene.vertex_data[this->indices.v2_id - 1]);
        vec3 normal = vec3::cross((c - b), (a - b));
        set_normal(normal);
    }
};
class sphere
{
public:
    int material_id;
    float radius;
    int center_vertex_id;
    sphere(const parser::Sphere &s)
    {
        radius = s.radius;
        center_vertex_id = s.center_vertex_id;
    }
};
#endif