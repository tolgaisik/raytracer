#include <iostream>
#include <math.h>
#include "parser.h"
#include "ppm.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
typedef unsigned char RGB[3];

vec3 get_center_of_image_plane(const parser::Camera &camera)
{
    return vec3(camera.position) + vec3(camera.gaze) * camera.near_distance;
}

vec3 get_top_left_of_image_plane(const parser::Camera &camera, const vec3 &center, vec3 &cross_product_vector, vec3 &up)
{
    vec3 topleft = center + cross_product_vector * camera.near_plane.x + up * camera.near_plane.y;
    return topleft;
}
color *calculate_color(const parser::Camera &camera, const ray &ray, const parser::Scene &scene)
{
    color *retval = new color(static_cast<unsigned char>(255), static_cast<unsigned char>(255), static_cast<unsigned char>(255));
    return retval;
}
int main(int argc, char *argv[])
{
    parser::Scene scene;
    scene.loadFromXml(argv[1]);
    int numberofcameras = scene.cameras.size();
    for (int camera_index = 0; camera_index < numberofcameras; ++camera_index)
    {
        int image_width = scene.cameras[camera_index].image_width;
        int image_height = scene.cameras[camera_index].image_height;
        unsigned char *image = new unsigned char[image_width * image_height * 3];
        parser::Camera camera = scene.cameras[camera_index];
        int index = 0;
        vec3 gaze(camera.gaze);
        vec3 up(camera.up);
        vec3 cross_product_vector = vec3::cross(-gaze, up);
        vec3 center_of_image_plane = get_center_of_image_plane(camera);
        vec3 top_left_of_image_plane = get_top_left_of_image_plane(camera, center_of_image_plane, cross_product_vector, up);

        float pixel_width, pixel_height;
        pixel_width = (camera.near_plane.x - camera.near_plane.y) / image_width;
        pixel_height = (camera.near_plane.w - camera.near_plane.z) / image_height;

        for (int y = 0; y < image_height; ++y)
        {
            for (int x = 0; x < image_width; ++x)
            {
                float s_u = (x + 0.5f) * pixel_width;
                float s_v = (y + 0.5f) * pixel_height;
                vec3 image_plane_point = top_left_of_image_plane + cross_product_vector * s_u + up * s_v;
                vec3 direction = image_plane_point - vec3(camera.position);
                ray ray(camera.position, direction);
                color *color = calculate_color(camera, ray, scene);
                image[index++] = color->r;
                image[index++] = color->g;
                image[index++] = color->b;
                delete color;
            }
        }

        write_ppm(camera.image_name.data(), image, image_width, image_height);
        delete[] image;
    }
}
