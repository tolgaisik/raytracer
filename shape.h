#ifndef __SHAPE_H__
#define __SHAPE_H__
#include "vec3.h"

class triangle
{
public:
    int material_id;
    parser::Face indices;
    vec3 normal;
};
class sphere
{
public:
    float radius;
    vec3 position;
};
#endif