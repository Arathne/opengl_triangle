#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "texture.h"

unsigned int vao;
unsigned int vbo;
unsigned int shaderProgram;

Texture container( "container.jpg" );

static float vertices[] =
{
    // positions    // colors            //texture coords
    -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
     0.5f, -0.5f,    0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
     0.0f,  0.5f,    0.0f, 0.0f, 1.0f,    0.5f, 1.0f
};

void draw (void)
{
    glClear( GL_COLOR_BUFFER_BIT );
    
    glDrawArrays( GL_TRIANGLES, 0, 3 );

    glFlush();
}

void matrix (void)
{
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::scale( transform, glm::vec3(0.5, 0.5, 0.5) );   
    transform = glm::rotate( transform, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f) );

    unsigned int uniformLocation = glGetUniformLocation( shaderProgram, "transform" );
    glUniformMatrix4fv( uniformLocation, 1, GL_FALSE, glm::value_ptr(transform) );
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

void texture (void)
{
    container.load( GL_RGB, GL_RGB );
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
    
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*) 0 );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*) (2*sizeof(float)) );
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*) (5*sizeof(float)) );
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    texture();
    matrix();
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
