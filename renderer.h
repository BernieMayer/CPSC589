#ifndef RENDERER_H
#define RENDERER_H

#include "camera.h"

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <math.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <common/shader.hpp>
#include <iostream>
#include <fstream>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_2_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QMouseEvent>
#include <QTimer>
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


class Renderer : public QOpenGLWidget, protected QOpenGLFunctions_4_2_Core
{
public:
    // constructor
    Renderer(QWidget *parent = 0);

    void setBig_R_value(double R);
    void setSmall_r_value(double r);
    void setN_value(double n);

    void redrawGraph();

protected:
    // override fundamental drawing functions

    // Called when OpenGL is first initialized
    void initializeGL();

    // Called when the window is resized
    void resizeGL(int w, int h);

    // Called when the window needs to be redrawn
    void paintGL();


    // Called when a mouse button is pressed
    virtual void mousePressEvent(QMouseEvent * event);

    // Called when a mouse button is released
    virtual void mouseReleaseEvent(QMouseEvent * event);

    // Called when the mouse moves
    virtual void mouseMoveEvent(QMouseEvent * event);

private:
    Camera* activeCamera;
    GLuint programID;
    GLuint graphVbo;
    GLuint graphVao;
    double R,r;
    int n;
    std::vector<glm::vec3> graphLines;
    glm::mat4 winRatio = mat4(1.f);
    glm::mat4 perspective = glm::perspective(radians(80.f), 1.f, 0.1f, 30.f);
    glm::mat4 modelview = mat4(1.f);

    glm::vec2 mousePos;
    bool leftMousePressed = false;
    bool rightMousePressed = false;
    bool animation = true;
    int t = 0;

    QTimer *m_pGameTimer;

    void generateGraph(float theta, int n, float angleMultiplier);
};

#endif // RENDERER_H
