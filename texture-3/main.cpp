#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

#include "shader.h"
#include "texture.h"

unsigned int vao;
unsigned int vbo;
unsigned int shaderProgram;

Texture container( "container.jpg" );
Texture face( "awesomeface.png" );

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
    unsigned int textures[2];
    glGenTextures(2, textures);
    
    container.setId( textures[0] );
    face.setId( textures[1] );

    glActiveTexture( GL_TEXTURE0 );
    container.load( GL_RGB, GL_RGB );

    glActiveTexture( GL_TEXTURE1 );
    face.load( GL_RGBA, GL_RGBA );

    glUniform1i( glGetUniformLocation(shaderProgram, "texture1"), 0 );
    glUniform1i( glGetUniformLocation(shaderProgram, "texture2"), 1 );
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
