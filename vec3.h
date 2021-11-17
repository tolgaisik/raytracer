#ifndef __VEC3__H
#define __VEC3__H
class vec3
{
public:
    float x, y, z;
    vec3() : x(0), y(0), z(0){};
    vec3(float x, float y, float z) : x(x), y(y), z(z){};
    vec3(const parser::Vec3f v) : x(v.x), y(v.y), z(v.z){};
    vec3(const vec3 &v) : x(v.x), y(v.y), z(v.z){};
    vec3 operator*(float scalar) const;
    vec3 operator-(const vec3 &v) const;
    vec3 operator+(const vec3 &v) const;
    vec3 operator-() const;
    static double dot(const vec3 &first, const vec3 &second);
    static vec3 cross(const vec3 &first, const vec3 &second);
    float norm()
    {
        return sqrt(x * x + y * y + z * z);
    }
    friend std::ostream &operator<<(std::ostream &os, const vec3 &v);
};
std::ostream &operator<<(std::ostream &os, const vec3 &v)
{
    os << '(' << v.x << ',' << v.y << ',' << v.z << ')' << std::endl;
    return os;
}
vec3 vec3::operator-(const vec3 &v) const
{
    return vec3(x - v.x, y - v.y, z - v.z);
}
vec3 vec3::operator*(float scalar) const
{
    return vec3(x * scalar, y * scalar, z * scalar);
}
vec3 vec3::operator+(const vec3 &v) const
{
    return vec3(x + v.x, y + v.y, z + v.z);
}
vec3 vec3::operator-() const
{
    return vec3(-x, -y, -z);
}
double vec3::dot(const vec3 &first, const vec3 &second)
{
    double retval = first.x * second.x + first.y * second.y + first.z * second.z;
    return retval;
}
vec3 vec3::cross(const vec3 &f, const vec3 &s)
{
    float cx = f.y * s.z - f.z * s.y;
    float cy = f.z * s.x - f.x * s.z;
    float cz = f.x * s.y - f.y * s.x;
    return vec3(cx, cy, cz);
}
#endif