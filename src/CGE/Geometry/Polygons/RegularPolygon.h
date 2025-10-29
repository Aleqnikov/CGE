#ifndef REGULAR_POLUGON_H
#define REGULAR_POLUGON_H

#include "Polygon.h"
class RegularPolygon : public Polygon{
public:
    RegularPolygon(int, InPolygonChecker);
    RegularPolygon();

    void  Regenerate() override;
};

#endif //REGULAR_POLUGON_H
