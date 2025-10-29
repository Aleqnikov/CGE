QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    src/CGE/Algebra/LinealAlgebra.cpp \
    src/CGE/Algebra/Point2D.cpp \
    src/CGE/Geometry/Polygons/ConvexPolygon.cpp \
    src/CGE/Geometry/Polygons/RegularPolygon.cpp \
    src/CGE/Geometry/Polygons/StarPolygon.cpp \
    src/CGE/Geometry/Polygons/PolygonAlgorithms.cpp \
    src/CGE/Geometry/Hull/HullAlgorithms.cpp \

HEADERS += \
    MyGraphicsView.h \
    MyGraphicsViewHull.h \
    mainwindow.h \
    ProjectInfo.h \
    src/CGE/Algebra/LinealAlgebra.h \
    src/CGE/Algebra/Point2D.h \
    src/CGE/Geometry/Polygons/ConvexPolygon.h \
    src/CGE/Geometry/Polygons/Polygon.h \
    src/CGE/Geometry/Polygons/RegularPolygon.h \
    src/CGE/Geometry/Polygons/StarPolygon.h \
    src/CGE/Geometry/Polygons/PolygonAlgorithms.h \
    src/CGE/Geometry/Hull/HullAlgorithms.h \
    src/CGE/Geometry/Hull/Hull.h


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
