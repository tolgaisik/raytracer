#ifndef __COLOR_H__
#define __COLOR_H__
typedef unsigned char RGB[3];

class color
{
public:
    int r, g, b;
    color() : r(0), g(0), b(0){};
    color(int r, int g, int b) : r(r), g(g), b(b){};
    color(RGB const &r) : r(r[0]), g(r[1]), b(r[2]){};
    color(const parser::Vec3f &c) : r(c.x), g(c.y), b(c.z) {}
    void setRGB(int r, int g, int b);
    color &operator*(color &c);
    color operator*(int scalar);
    color &operator-(color &c);
    friend std::ostream &operator<<(std::ostream &os, const color &c);
};
void color::setRGB(int R, int G, int B)
{
    this->r = R;
    this->g = G;
    this->b = B;
}

color color::operator*(int scalar)
{
    return color(r * scalar, g * scalar, b * scalar);
}
std::ostream &operator<<(std::ostream &os, const color &c)
{
    os << c.r << ", " << c.g << ", " << c.b << std::endl;
    return os;
}
#endif