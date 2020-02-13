#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

bool wireframe = false;

void draw( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
    
    if( wireframe )
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glLineWidth( 200 );
    }
    else
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }
    
    glBegin( GL_TRIANGLES );
    
    glVertex3f( 0.0, 0.5, 0.0 );
    glVertex3f( 0.5, -0.5, 0.0 );
    glVertex3f( -0.5, -0.5, 0.0 );

    glEnd();

    glFlush();
}

void input( unsigned char key, int x, int y )
{
    if( key == 27 )
    {
        exit(0);
    }
    else
    {
        wireframe = !wireframe;
    }

    glutPostRedisplay();
}

int main( int argc, char** argv )
{
    glutInit( &argc, argv );

    glutInitContextVersion( 4, 3 );
    glutInitContextProfile( GLUT_COMPATIBILITY_PROFILE );

    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
    glutInitWindowPosition( 300, 300 );
    glutInitWindowSize( 500, 500 );

    glutCreateWindow( "wireframe triangle" );
    glClearColor( 0.5, 0.5, 0.5, 1.0 );
    
    glutDisplayFunc( draw );
    glutKeyboardFunc( input );

    glutMainLoop();

    return 0;
}
