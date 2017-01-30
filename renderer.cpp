#include "renderer.h"



// constructor
Renderer::Renderer(QWidget *parent)
    : QOpenGLWidget(parent)
{

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

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){
    QOpenGLFunctions glFuncs(QOpenGLContext::currentContext());

    //QOpenGLContext *m_context = new QOpenGLContext();
    //m_context->makeCurrent(this);
    // Create the shaders
    GLuint VertexShaderID = glFuncs.glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glFuncs.glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open()){
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    }else{
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
        getchar();
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::string Line = "";
        while(getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;


    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glFuncs.glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glFuncs.glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glFuncs.glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glFuncs.glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glFuncs.glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }



    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glFuncs.glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glFuncs.glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glFuncs.glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glFuncs.glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glFuncs.glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }



    // Link the program
    printf("Linking program\n");
    GLuint ProgramID = glFuncs.glCreateProgram();
    glFuncs.glAttachShader(ProgramID, VertexShaderID);
    glFuncs.glAttachShader(ProgramID, FragmentShaderID);
    glFuncs.glLinkProgram(ProgramID);

    // Check the program
    glFuncs.glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glFuncs.glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glFuncs.glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }


    glFuncs.glDetachShader(ProgramID, VertexShaderID);
    glFuncs.glDetachShader(ProgramID, FragmentShaderID);

    glFuncs.glDeleteShader(VertexShaderID);
    glFuncs.glDeleteShader(FragmentShaderID);

    return ProgramID;
}




void Renderer :: initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);




    programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
    glGenBuffers(1, &graphVbo);
    glBindBuffer(GL_ARRAY_BUFFER, graphVbo);

    r = 2.0;
    R = 5.2;

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
        //glVertex3d(x, y, 0.0);
        graphLines.push_back(glm::vec3(x,y, 0));
        theta += 0.05;
    }

    glBufferData(GL_ARRAY_BUFFER, sizeof(graphLines), graphLines.data(), GL_STATIC_DRAW);


}

void Renderer :: paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use the normal shader
    glUseProgram(programID);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, graphVbo);

    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    glDrawArrays(GL_LINE_STRIP, 0, graphLines.size());

    glDisableVertexAttribArray(0);

        // Swap buffers
        //glfwSwapBuffers();
        //glfwPollEvents();











}

void Renderer:: resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,0,0,0,0,0,1,0);

    paintGL();
}
