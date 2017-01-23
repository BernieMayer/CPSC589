#include "renderer.h"



// constructor
Renderer::Renderer(QWidget *parent)
    : QOpenGLWidget(parent)
{
    r = 2.0;
    R = 4.2;
}

void Renderer::setBig_R_value(double R)
{
    this->R = R;
    //update();
}

void Renderer::setSmall_r_value(double r)
{
    this->r = r;
    //update();
}




void Renderer :: initializeGL()
{
    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void Renderer :: paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_LINE_STRIP);
        /*
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-0.5, -0.5, 0);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f( 0.5, -0.5, 0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f( 0.0,  0.5, 0);
        */

        float theta;
        int n;

        theta = 0.0;


        n = 200.0;

        float angleMultiplier = (R - r)/r;

        while (theta < n * PI * 2 )
        {
            glColor3f(1.0, 0.0, 0.0);

            float x = (R - r) * cos(theta) + r * cos(angleMultiplier * theta);
            float y = (R - r) * sin(theta) - r * sin(angleMultiplier * theta);
            glVertex3d(x, y, 0.0);

            theta += 0.05;
        }


    glEnd();

}

void Renderer:: resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,20,0,0,0,0,1,0);

    paintGL();
}
