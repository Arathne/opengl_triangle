#include <GL/glew.h>
#include <GL/freeglut.h>

static float vertices[] =
{
    -0.5f, -0.5f,
     0.5f, -0.5f,
     0.0f,  0.5f
};

static float color[] =
{
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 1.0
};

void draw (void)
{
    glClear( GL_COLOR_BUFFER_BIT );
    
    glDrawArrays( GL_TRIANGLES, 0, 3 );

    glFlush();
}

void setup (void)
{
    glClearColor( 0.5, 0.5, 0.5, 1.0 );

    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 2, GL_FLOAT, 2*sizeof(float), vertices );

    glEnableClientState( GL_COLOR_ARRAY );
    glColorPointer( 3, GL_FLOAT, 3*sizeof(float), color );
}

void keyboard (unsigned char key, int x, int y)
{
    if( key == 27 )
        exit(0);
}

int main (int argc, char** argv)
{
    glutInit( &argc, argv );   
    
    glutInitContextVersion( 4, 3 );
    glutInitContextProfile( GLUT_COMPATIBILITY_PROFILE );
    
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
    glutInitWindowSize( 500, 500 );
    glutInitWindowPosition( 100, 100 );
    
    glutCreateWindow( "color 2" );
    glutDisplayFunc( draw );
    glutKeyboardFunc( keyboard );
    
    glewInit();
    setup();
    glutMainLoop();
    
    return 0;
}
