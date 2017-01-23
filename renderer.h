#ifndef RENDERER_H
#define RENDERER_H

#include <QWidget>
#include <QOpenGLWidget>
#include <math.h>

#define PI 3.14159265

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <gl/GLU.h>
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
    double R,r;

};

#endif // RENDERER_H
