#include <iostream>
#include <math.h>
#include "parser.h"
#include "ppm.h"
typedef unsigned char RGB[3];
class color
{
public:
    unsigned char r, g, b;
    color() : r(0), g(0), b(0){};
    color(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b){};
    color(RGB const &r) : r(r[0]), g(r[1]), b(r[2]){};
    color &operator*(color &c);
    color &operator*(int scalar);
    color &operator-(color &c);
};
class vec3
{
public:
    float x, y, z;
    vec3() : x(0), y(0), z(0){};
    vec3(float x, float y, float z) : x(x), y(y), z(z){};
    vec3(parser::Vec3f v) : x(v.x), y(v.y), z(v.z){};
    vec3 operator*(float scalar);
    vec3 operator-(const vec3 &v);
    vec3 operator+(const vec3 &v);
    float dot(const vec3 &first, const vec3 &second);
    vec3 cross(const vec3 &first, const vec3 &second);
    float norm()
    {
        return sqrt(x * x + y * y + z * z);
    }
};
vec3 vec3::operator*(float scalar)
{
    return vec3(this->x * scalar, this->y * scalar, this->z * scalar);
}
vec3 vec3::operator+(const vec3 &v)
{
    return vec3(this->x + v.x, this->y + v.y, this->z + z);
}
float vec3::dot(const vec3 &first, const vec3 &second)
{
    return first.x * second.x + first.y * second.y + first.z * second.z;
}
vec3 vec3::cross(const vec3 &f, const vec3 &s)
{
    float cx = f.y * s.z - f.z * s.y;
    float cy = f.z * s.x - f.x * s.z;
    float cz = f.x * s.y - f.y * s.x;
    return vec3(cx, cy, cz);
}
class ray
{
public:
    vec3 origin, direction;
    int x, y;
    ray() : origin(vec3()), direction(vec3()){};
    ray(const parser::Vec3f &origin)
    {
        this->origin = vec3(origin);
    }
    ray(const parser::Vec3f &origin, int x, int y)
    {
    }
    color calculate_color(const parser::Camera &camera, const ray &ray);
};
color ray::calculate_color(const parser::Camera &camera, const ray &ray)
{
    return color(static_cast<unsigned char>(255), static_cast<unsigned char>(255), static_cast<unsigned char>(255));
}
vec3 get_center_of_image_plane(const parser::Camera &camera)
{
    return vec3(camera.position) + vec3(camera.gaze) * camera.near_distance;
}
vec3 get_top_left_image_plane(const parser::Camera &camera)
{
    return vec3();
}
class triangle
{
public:
    int material_id;
    parser::Face indices;
    vec3 normal;
};
int main(int argc, char *argv[])
{
    parser::Scene scene;
    std::cout << argv[1] << std::endl;
    scene.loadFromXml(argv[1]);
    int numberofcameras = scene.cameras.size();
    for (int camera_index = 0; camera_index < numberofcameras; ++camera_index)
    {
        int image_width = scene.cameras[camera_index].image_width;
        int image_height = scene.cameras[camera_index].image_height;
        unsigned char *image = new unsigned char[image_width * image_height * 3];
        parser::Camera camera = scene.cameras[camera_index];
        int index = 0;
        std::cout << camera.gaze.x << camera.gaze.y << camera.gaze.z << std::endl;
        vec3 center_of_image_plane = get_center_of_image_plane(camera);
        vec3 top_left_of_image_plane = get_top_left_image_plane(camera);
        for (int y = 0; y < image_height; ++y)
        {
            for (int x = 0; x < image_width; ++x)
            {
                ray ray(camera.position, x, y);
                color color = ray.calculate_color(camera, ray);
                image[index++] = color.r;
                image[index++] = color.g;
                image[index++] = color.b;
            }
        }

        write_ppm("test.ppm", image, image_width, image_height);
        delete[] image;
    }
}
