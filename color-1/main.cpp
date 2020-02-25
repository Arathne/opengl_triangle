#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut.h>

void draw( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
    
    glBegin( GL_TRIANGLES );

    glColor3f( 1, 0, 0 );
    glVertex3f( 0.0, 0.5, 0.0 );
    
    glColor3f( 0, 1, 0 );
    glVertex3f( 0.5, -0.5, 0.0 );
    
    glColor3f( 0, 0, 1 );
    glVertex3f( -0.5, -0.5, 0.0 );
    
    glEnd();

    glFlush();
}

int main( int argc, char** argv )
{
    glutInit( &argc, argv );
 
    glutInitContextVersion( 4, 3 );
    glutInitContextProfile( GLUT_COMPATIBILITY_PROFILE );
    
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
    glutInitWindowSize( 500, 500 );
    glutInitWindowPosition( 300, 300 );
    
    glutCreateWindow( "color triangle" );
    glutDisplayFunc( draw );

    glClearColor( 0.5, 0.5, 0.5, 1.0 );
    
    glutMainLoop();

    return 0;
}
