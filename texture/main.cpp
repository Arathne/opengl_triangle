#include <GL/glew.h>
#include <GL/freeglut.h>
#include "shader.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned int vao;
unsigned int vbo;
unsigned int shaderProgram;

unsigned int texture1;

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
    glGenTextures( 1, &texture1 );
    glBindTexture( GL_TEXTURE_2D, texture1 );
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    
    int imgWidth, imgHeight, nrChannels;
    unsigned char *data = stbi_load( "container.jpg", &imgWidth, &imgHeight, &nrChannels, 0 );
    
    if( data )
    {
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
        glGenerateMipmap( GL_TEXTURE_2D );
    }
    else
    {
        std::cout << "FAILED TO LOAD TEXTURE" << std::endl;
    }

    stbi_image_free( data );
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
