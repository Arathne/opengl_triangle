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
    
    float radius = 5.0f;
    float camX = sin(time) * radius;
    float camZ = cos(time) * radius;
    
    glm::vec3 position = glm::vec3( camX, 0.0f, camZ );
    glm::vec3 target = glm::vec3( 0.0f, 0.0f, 0.0f );
    glm::vec3 up = glm::vec3( 0.0f, 1.0f, 0.0f );

    glm::mat4 view = glm::lookAt( position, target, up );
    glm::mat4 projection = glm::perspective( glm::radians(45.0f), 500.0f/600.0f, 0.1f, 100.0f  );
    
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
    if( key == 27 )
        exit(0);
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
