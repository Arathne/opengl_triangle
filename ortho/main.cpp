#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut.h>

void draw( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
    
    glBegin( GL_TRIANGLES );
    
    glVertex3f( -75, -75, 0 );
    glVertex3f( 75, -75, 0 );
    glVertex3f( 0, 75, 0 );
    
    glEnd();
    
    glFlush();
}

void resize( int width, int height )
{
    glOrtho( -100, 100, -100, 100, -1, 1 );
}

int main( int argc, char** argv )
{
    glutInit( &argc, argv );
    
    glutInitContextVersion( 4, 3 );
    glutInitContextProfile( GLUT_COMPATIBILITY_PROFILE );

    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
    glutInitWindowPosition( 300, 300 );
    glutInitWindowSize( 500, 500 );
    
    glutCreateWindow( "ortho triangle" );
    glutDisplayFunc( draw );
    glutReshapeFunc( resize );
    
    glClearColor( 0.5, 0.5, 0.5, 1.0 );
    
    glutMainLoop();

    return 0;
}
