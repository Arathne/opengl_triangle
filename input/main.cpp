#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

float offsetY = 0;
float offsetX = 0;

float increment = 0.05;

void drawScene( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
    
    glBegin( GL_TRIANGLES );
    
    float x = 0.5;
    float y = 0.5;

    glBegin( GL_TRIANGLES );
        
    glVertex3f( 0.0 + offsetX, y + offsetY, 0.0 );
    glVertex3f( x + offsetX, -y + offsetY, 0.0 );
    glVertex3f( -x + offsetX, -y + offsetY, 0.0 );

    glEnd();

    glFlush();
}

void keyInput( unsigned char key, int x, int y )
{
    if( key == 'a' )
    {
        offsetX = offsetX - increment;
    }
    else if( key == 'd' )
    {
        offsetX = offsetX + increment;
    }
    else if( key == 'w' )
    {
        offsetY = offsetY + increment;
    }
    else if( key == 's' )
    {
        offsetY = offsetY - increment;
    }
    else if( key == 27 )
    {
        exit(0);
    }

    glutPostRedisplay();
}

int main( int argc, char** argv )
{
    glutInit( &argc, argv );

    glutInitContextVersion( 4,3 );
    glutInitContextProfile( GLUT_COMPATIBILITY_PROFILE );

    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
    glutInitWindowSize( 500, 500 );
    glutInitWindowPosition( 100, 100 );

    glutCreateWindow( "input triangle" );
    glutDisplayFunc( drawScene );
    glutKeyboardFunc( keyInput );

    glClearColor( 0.5, 0.5, 0.5, 1 );
    glutMainLoop();

    return 0;
}
