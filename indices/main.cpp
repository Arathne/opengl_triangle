#include <GL/glew.h>
#include <GL/freeglut.h>

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0
};

unsigned int indices[] = { 0, 1, 2 };

void draw (void)
{
    glClear( GL_COLOR_BUFFER_BIT );
    
    glDrawElements( GL_TRIANGLE_STRIP, 3, GL_UNSIGNED_INT, indices );

    glFlush();
}

void keyboard ( unsigned char key, int x, int y )
{
    if( key == 27 )
        exit(0);
}

void setup (void)
{
    glClearColor( 0.5, 0.5, 0.5, 1 );

    glEnableClientState( GL_VERTEX_ARRAY );
    
    glVertexPointer( 3, GL_FLOAT, 0, vertices );
}

int main( int argc, char** argv )
{
    glutInit( &argc, argv );

    glutInitContextVersion( 4,3 );
    glutInitContextProfile( GLUT_COMPATIBILITY_PROFILE );

    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
    glutInitWindowSize( 500, 500 );
    glutInitWindowPosition( 100, 100 );

    glutCreateWindow( "Vertex Array Object" );
    
    glutDisplayFunc( draw );
    glutKeyboardFunc( keyboard );
    glewInit();
    
    setup();
    glutMainLoop();

    return 0;
}
