#ifndef PROJECTINFO_H
#define PROJECTINFO_H

enum class ModOfAlgorithm {
    DotInpolygon,
    ConstructionConvexHull,
};

enum class Polygons {
    Star,
    Convex,
    Regular,
    None
};

enum class ConvexHullAlgs {
    JarvisMarch,
    GrahamScan,
    AndrewsMonotone,
    None
};

struct ProjectInfo {
    ModOfAlgorithm algMod;
    Polygons polygon;
    ConvexHullAlgs ConvexAlg;

    int n;
};

#endif // PROJECTINFO_H
