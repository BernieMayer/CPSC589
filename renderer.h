#ifndef RENDERER_H
#define RENDERER_H

#include <QWidget>
#include <QOpenGLWidget>
#include <math.h>
#include <vector>
#include <glm/glm.hpp>
#include <common/shader.hpp>
#include <iostream>
#include <fstream>



#define PI 3.1415926


#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL.h>

//#include <OpenGL/glew.h>
#else
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#endif

class Renderer : public QOpenGLWidget
{
public:
    // constructor
    Renderer(QWidget *parent = 0);

    void setBig_R_value(double R);
    void setSmall_r_value(double r);

protected:
    // override fundamental drawing functions

    // Called when OpenGL is first initialized
    void initializeGL();

    // Called when the window is resized
    void resizeGL(int w, int h);

    // Called when the window needs to be redrawn
    void paintGL();

private:
    GLuint programID;
    GLuint graphVbo;
    double R,r;
    std::vector<glm::vec3> graphLines;

};

#endif // RENDERER_H
