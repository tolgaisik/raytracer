#ifndef __COLOR_H__
#define __COLOR_H__
typedef unsigned char RGB[3];

class color
{
public:
    unsigned char r, g, b;
    color() : r(0), g(0), b(0){};
    color(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b){};
    color(RGB const &r) : r(r[0]), g(r[1]), b(r[2]){};
    void setRGB(unsigned char r, unsigned char g, unsigned char b);
    color &operator*(color &c);
    color &operator*(int scalar);
    color &operator-(color &c);
    friend std::ostream &operator<<(std::ostream &os, const color &c);
};
void color::setRGB(unsigned char R, unsigned char G, unsigned char B)
{
    this->r = R;
    this->g = G;
    this->b = B;
}
std::ostream &operator<<(std::ostream &os, const color &c)
{
    os << c.r << ", " << c.g << ", " << c.b << std::endl;
    return os;
}
#endif