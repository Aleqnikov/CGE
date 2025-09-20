#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include "./Engine/Geometry/Polygons/ConvexPolygon.h"

#include <iostream>

ConvexPolygon polygon(30); // создаём один раз глобально

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);

    glBegin(GL_LINE_LOOP); // автоматически замыкает контур
    for (auto& v : polygon.vertices) {
        glVertex2d(v.x, v.y);
    }
    glEnd();

    glutSwapBuffers();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // двойной буфер + RGB
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("CGE");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glutDisplayFunc(display);
    

    glutMainLoop();
    return 0;
}
