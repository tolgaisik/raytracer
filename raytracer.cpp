#include <iostream>
#include <math.h>
#include "parser.h"
#include "ppm.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "shape.h"
typedef unsigned char RGB[3];

vec3 get_center_of_image_plane(const parser::Camera &camera)
{
    return vec3(camera.position) + vec3(camera.gaze) * camera.near_distance;
}

vec3 get_top_left_of_image_plane(const parser::Camera &camera, const vec3 &center, vec3 &cross_product_vector, vec3 &up)
{
    vec3 topleft = center + cross_product_vector * camera.near_plane.x + up * camera.near_plane.w;
    return topleft;
}
void create_triangles(const parser::Scene &scene, std::vector<triangle> &triangles)
{
    int numberoftriangles = scene.triangles.size();
    for (int i = 0; i < numberoftriangles; ++i)
    {
        triangle __triangle__ = triangle(scene.triangles[i]);
        __triangle__.calculate_normal(scene);
        triangles.push_back(__triangle__);
    }
    int numberofmeshes = scene.meshes.size();
    for (int i = 0; i < numberofmeshes; ++i)
    {
        for (int j = 0; j < scene.meshes[i].faces.size(); ++j)

        {
            parser::Face face = scene.meshes[i].faces[j];
            triangle __triangle__ = triangle(face, scene.meshes[i].material_id);
            __triangle__.calculate_normal(scene);
            triangles.push_back(__triangle__);
        }
    }
}
color *calculate_color(const parser::Camera &camera, const ray &__ray__, const parser::Scene &scene, std::vector<triangle> &triangles)
{
    color *retval = new color();
    sphere *s = nullptr;
    triangle *t = nullptr;
    float tmin = INFINITY;
    int numberofspheres = scene.spheres.size();
    for (int i = 0; i < numberofspheres; ++i)
    {
        float t_sphere = __ray__.intersect(scene.spheres[i]);
        if (t_sphere > 0 && t_sphere < tmin)
        {
            tmin = t_sphere;
            if (s != nullptr)
            {
                delete s;
            }
            s = new sphere(scene.spheres[i]);
        }
    }
    int numberoftriangles = triangles.size();
    for (int i = 0; i < numberoftriangles; ++i)
    {
        float t_triangle = __ray__.intersect(triangles[i]);
        if (t_triangle > 0 && t_triangle < tmin)
        {
            tmin = t_triangle;
            if (t != nullptr)
                delete t;
            t = new triangle(triangles[i]);
            if (s != nullptr)
            {
                delete s;
                s = nullptr;
            }
        }
    }

    if (t != nullptr)
    {
        retval->setRGB(static_cast<unsigned char>(255), static_cast<unsigned char>(255), static_cast<unsigned char>(255));
    }
    if (s != nullptr)
    {
        retval->setRGB(static_cast<unsigned char>(255), static_cast<unsigned char>(255), static_cast<unsigned char>(255));
    }
    delete s;
    delete t;
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
        vec3 cross_product_vector = -vec3::cross(-gaze, up); // TODO cross products is wrong sided
        vec3 center_of_image_plane = get_center_of_image_plane(camera);
        vec3 top_left_of_image_plane = get_top_left_of_image_plane(camera, center_of_image_plane, cross_product_vector, up);

        float pixel_width, pixel_height;
        pixel_width = (camera.near_plane.y - camera.near_plane.x) / image_width;
        pixel_height = (camera.near_plane.w - camera.near_plane.z) / image_height;
        std::vector<triangle> triangles;
        create_triangles(scene, triangles);
        for (int y = 0; y < image_height; ++y)
        {
            for (int x = 0; x < image_width; ++x)
            {
                float s_u = (x + 0.5f) * pixel_width;
                float s_v = (y + 0.5f) * pixel_height;
                vec3 image_plane_point = top_left_of_image_plane + cross_product_vector * s_u - up * s_v;
                vec3 direction = image_plane_point - vec3(camera.position);
                ray __ray__(camera.position, direction, &scene);
                color *color = calculate_color(camera, __ray__, scene, triangles);
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
