QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    Engine/Algebra/LinealAlgebra.cpp \
    Engine/Algebra/Point2D.cpp \
    Engine/Geometry/Polygons/ConvexPolygon.cpp \
    Engine/Geometry/Polygons/Polygon.cpp \
    Engine/Geometry/Polygons/RegularPolygon.cpp \
    Engine/Geometry/Mesh/CreateMesh.cpp \
    Engine/Geometry/Polygons/StarPolygon.cpp

HEADERS += \
    MyGraphicsView.h \
    MyGraphicsViewHull.h \
    mainwindow.h \
    ProjectInfo.h \
    Engine/Algebra/LinealAlgebra.h \
    Engine/Algebra/Point2D.h \
    Engine/Geometry/Polygons/ConvexPolygon.h \
    Engine/Geometry/Polygons/Polygon.h \
    Engine/Geometry/Polygons/RegularPolygon.h \
    Engine/Geometry/Mesh/CreateMesh.h \
    Engine/Geometry/Polygons/StarPolygon.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
