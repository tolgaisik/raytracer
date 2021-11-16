
#ifndef __RAY__
#define __RAY__
class ray
{
public:
    vec3 *origin, *direction;
    const parser::Scene *scene;
    int x, y;
    ray() : origin(new vec3()), direction(new vec3()){};
    ray(const parser::Vec3f &origin__, const vec3 &direction__, const parser::Scene *scene__)
    {
        direction = new vec3(direction__);
        origin = new vec3(origin__);
        scene = scene__;
    };
    bool intersect(const parser::Sphere &sphere) const;
    bool intersect(const parser::Triangle &triangle) const;
    bool intersect(const parser::Mesh &mesh) const;
};

bool ray::intersect(const parser::Sphere &sphere) const
{
    vec3 center = vec3(this->scene->vertex_data[sphere.center_vertex_id]);
    float radius = sphere.radius;

    return false;
}
bool ray::intersect(const parser::Triangle &triangle) const
{
    parser::Vec3f first = this->scene->vertex_data[triangle.indices.v0_id];
    parser::Vec3f second = this->scene->vertex_data[triangle.indices.v1_id];
    parser::Vec3f third = this->scene->vertex_data[triangle.indices.v2_id];

    return false;
}
#endif