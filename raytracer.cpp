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
vec3 get_top_left_image_plane(const parser::Camera &camera)
{
    vec3 result = vec3::cross(vec3(camera.gaze), vec3(camera.up));
    std::cout << result;
    return vec3();
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
