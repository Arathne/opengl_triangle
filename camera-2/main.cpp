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

float lastFrame = 0.0f;

float speed = 0.5f;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool depth = true;

Texture container( "container.jpg" );

static float vertices[] =
{
     0.0f,  0.0f,  0.5f,  0.0f, 0.5f,
     0.5f,  0.5f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.0f,  1.0f, 0.0f,

     0.0f,  0.0f,  0.5f,  0.0f, 0.5f,
    -0.5f,  0.5f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f,  0.0f,  1.0f, 0.0f,
     
     0.0f,  0.0f,  0.5f,  0.0f, 0.5f,
    -0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.0f,  1.0f, 0.0f,

     0.0f,  0.0f,  0.5f,  0.0f, 0.5f,
     0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.0f,  1.0f, 0.0f,

     0.5f, -0.5f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.0f,  1.0f, 1.0f,

     0.5f,  0.5f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.0f,  0.0f, 1.0f
};

void draw (void)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
 
    glDrawArrays( GL_TRIANGLES, 0, 18 );

    glFlush();
}

void matrix (void)
{
    float time = glutGet(GLUT_ELAPSED_TIME)/1000.0f;
    
    glm::mat4 model = glm::mat4(1.0f);
    
    glm::mat4 view = glm::lookAt( cameraPos, cameraPos + cameraFront, cameraUp );
    glm::mat4 projection = glm::perspective( glm::radians(45.0f), 500.0f/600.0f, 0.1f, 100.0f  );
    
    model = glm::rotate( model, time * glm::radians(50.0f), glm::vec3(1.0f, 1.0f, 0.0f) );

    unsigned int modelLoc = glGetUniformLocation( shaderProgram, "model" );
    unsigned int viewLoc = glGetUniformLocation( shaderProgram, "view" );
    unsigned int projectionLoc = glGetUniformLocation( shaderProgram, "projection" );

    glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr(model) );
    glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr(view) );
    glUniformMatrix4fv( projectionLoc, 1, GL_FALSE, glm::value_ptr(projection) );
}

void idle (void)
{
    matrix();
    glutPostRedisplay();
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
    
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*) 0 );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*) (3*sizeof(float)) );
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    texture();
    matrix();
    
    glEnable( GL_DEPTH_TEST );
}

void keyboard (unsigned char key, int x, int y)
{
    glm::vec3 cameraRight = glm::cross(cameraFront, cameraUp);
    
    if( key == 27 )
        exit(0);
    else if( key == 119 )
        cameraPos += speed * cameraFront;
    else if( key == 115 )
        cameraPos -= speed * cameraFront;
    else if( key == 97 )
        cameraPos -= glm::normalize(cameraRight) * speed;
    else if( key == 100 )
        cameraPos += glm::normalize(cameraRight) * speed;
}

int main( int argc, char** argv )
{
    glutInit( &argc, argv );

    glutInitContextVersion( 4, 3 );
    glutInitContextProfile( GLUT_CORE_PROFILE );

    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize( 500, 600 );
    glutInitWindowPosition( 100, 100 );
    
    glutCreateWindow( "shader 1" );
    glutDisplayFunc( draw );
    glutKeyboardFunc( keyboard );
    glutIdleFunc( idle );

    glewInit();
    setup();
    glutMainLoop();

    return 0;
}
