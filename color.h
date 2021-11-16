#ifndef __COLOR__
#define __COLOR__
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

#endif