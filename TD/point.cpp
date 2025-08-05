#include "point.h"

std::istream& operator>>(std::istream& iDev, point& rpoint) {
    int x, y, c;
    iDev >> x >> y >> c;
    rpoint.setX(x);
    rpoint.setY(y);
    rpoint.setC(c);

    return iDev;
}

