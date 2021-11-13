#include <iostream>
#include "parser.h"
#include "ppm.h"
typedef unsigned char RGB[3];
class Ray
{
public:
    parser::Vec3f origin, direction;
    Ray(const parser::Vec3f &origin, const parser::Vec3f &direction)
    {
        this->origin.x = origin.x;
        this->origin.y = origin.y;
        this->origin.z = origin.z;
        this->direction.x = direction.x;
        this->direction.y = direction.y;
        this->direction.z = direction.z;
    }
    unsigned char *calculate_color(const Ray &ray, int pixel_x, int pixel_y) const
    {
        unsigned char *color = new RGB;
        return color;
    }
};
int main(int argc, char *argv[])
{
    // Sample usage for reading an XML scene file
    parser::Scene scene;
    std::cout << argv[1] << std::endl;
    scene.loadFromXml(argv[1]);

    // The code below creates a test pattern and writes
    // it to a PPM file to demonstrate the usage of the
    // ppm_write function.
    //
    // Normally, you would be running your ray tracing
    // code here to produce the desired image.
    int numberofcameras = scene.cameras.size();
    for (int camera_index = 0; camera_index < numberofcameras; ++camera_index)
    {
        int image_width = scene.cameras[camera_index].image_width;
        int image_height = scene.cameras[camera_index].image_height;
        unsigned char *image = new unsigned char[image_width * image_height * 3];
        parser::Camera camera = scene.cameras[camera_index];
        for (int x = 0; x < image_width; ++x)
        {
            for (int y = 0; y < image_height; ++y)
            {
                Ray ray(camera.position, camera.gaze);
                unsigned char *color = ray.calculate_color(ray, x, y);
                int index = x * y + y;
                image[index++] = color[0];
                image[index++] = color[1];
                image[index] = color[2];
            }
        }

        write_ppm("test.ppm", image, image_width, image_height);
        delete[] image;
    }
}
