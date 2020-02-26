#include <GL/glew.h>
#include <GL/freeglut.h>
#include "shader.h"

unsigned int vao;
unsigned int vbo;
unsigned int shaderProgram;

static float vertices[] =
{
    -0.5f, -0.5f,
     0.5f, -0.5f,
     0.0f,  0.5f
};

void draw (void)
{
    glClear( GL_COLOR_BUFFER_BIT );
    
    glDrawArrays( GL_TRIANGLES, 0, 3 );

    glFlush();
}

void shaders (void)
{
    shaderProgram = glCreateProgram(); 

    Shader vertexShader( GL_VERTEX_SHADER, "vertex.shader" );
    Shader fragmentShader( GL_FRAGMENT_SHADER, "fragment.shader" );
    
    vertexShader.attach( shaderProgram );
    fragmentShader.attach( shaderProgram );
    
    glLinkProgram( shaderProgram );
    glUseProgram( shaderProgram );
}

void setup (void)
{
    glClearColor( 0.5, 0.5, 0.5, 1.0 );
    
    shaders();

    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );
    
    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
    
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*) 0 );
    glEnableVertexAttribArray(0);
}

void keyboard (unsigned char key, int x, int y)
{
    if( key == 27 )
        exit(0);
}

int main( int argc, char** argv )
{
    glutInit( &argc, argv );

    glutInitContextVersion( 4, 3 );
    glutInitContextProfile( GLUT_CORE_PROFILE );

    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
    glutInitWindowSize( 500, 500 );
    glutInitWindowPosition( 100, 100 );
    
    glutCreateWindow( "shader 1" );
    glutDisplayFunc( draw );
    glutKeyboardFunc( keyboard );

    glewInit();
    setup();
    glutMainLoop();

    return 0;
}
