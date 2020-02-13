#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

void drawScene( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
    
    glBegin( GL_TRIANGLES );
       
       glVertex3f( 0, 0.5, 0.0 );
       glVertex3f( 0.5, -0.5, 0.0 );
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
    glutInitWindowPosition( 100, 100 );
    
    glutCreateWindow( "basic triangle" );
    glutDisplayFunc( drawScene );

    glewExperimental = GL_TRUE;
    glewInit();
    
    glClearColor( 0.5, 0.5, 0.5, 0.0 );
    glutMainLoop();

    return 0;
}
