#include <GL/glew.h>
#include <GL/freeglut.h>

unsigned int VBO;

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
};

void draw (void)
{
    glClear( GL_COLOR_BUFFER_BIT );

    glDrawArrays( GL_TRIANGLES, 0, 3 );

    glFlush();
}

void keyboard ( unsigned char key, int x, int y )
{
    if( key == 27 )
        exit(0);
}

void setup (void)
{
    glClearColor( 0.5, 0.5, 0.5, 1.0 );

    glGenBuffers( 1, &VBO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, 9*sizeof(float), vertices, GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*) 0 );
    glEnableVertexAttribArray(0);
}   

int main (int argc, char** argv)
{
    glutInit( &argc, argv );

    glutInitContextVersion( 4, 3 );
    glutInitContextProfile( GLUT_COMPATIBILITY_PROFILE );
    
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
    glutInitWindowSize( 500, 500 );
    glutInitWindowPosition( 100, 100 );

    glutCreateWindow("VBO");
    glutDisplayFunc( draw );
    glutKeyboardFunc( keyboard );

    glewInit();
    
    setup();
    glutMainLoop();

    return 0;
}
