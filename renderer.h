#ifndef RENDERER_H
#define RENDERER_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <math.h>
#include <vector>
#include <glm/glm.hpp>
#include <common/shader.hpp>
#include <iostream>
#include <fstream>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_2_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QGLFunctions>
#include <GLFW/glfw3.h>

#include <GL/gl.h>

#include <QOpenGLWidget>

#define PI 3.1415926


#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL.h>

//#include <OpenGL/glew.h>
#else
#include <GL/glu.h>
#include <GL/gl.h>
#include <GLFW/glfw3native.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
//#include <GL/glew.h>



#endif


class Renderer : public QOpenGLWidget, protected QOpenGLFunctions
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
