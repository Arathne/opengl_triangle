#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GL/freeglut.h>

static float pi = 3.141592;
static float a = 10;
static float b = 20;
static int increment = 3;
static float smoothness =pi / 12;

void drawScene()
{
	glClear( GL_COLOR_BUFFER_BIT );
	glColor3f( 0, 0, 0 );
	glLineWidth(2);

	glBegin( GL_LINE_STRIP );
	for( float angle = 0; angle <= 2*pi; angle = angle + smoothness )
	{
		float x = a * cos(angle) + 50;
		float y = b * sin(angle) + 50;
		glVertex3f(x,y, 0);
	}
	glEnd();

	glFlush();
}

void resize( int width, int height )
{
	glViewport( 0, 0, width, height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, 100, 0, 100, -1, 1 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}

void keyInput( unsigned char key, int x, int y )
{
	if( key == 27 )
		exit(0);
	else if ( key == 119 )
		b = b + increment;
	else if ( key == 115 )
		b = b - increment;
	else if ( key == 97 )
		a = a - increment;
	else if ( key == 100 )
		a = a + increment;
	else if ( key == 102 )
		smoothness = smoothness * 2;
	else if ( key == 114 )
		smoothness = smoothness * 1/2;

	glutPostRedisplay();
}

void setup()
{
	std::cout << "use WASD to change the shape of the ellipse" << std::endl;
	std::cout << "use FR to change smoothness" << std::endl;
}

int main( int argc, char** argv )
{
	glutInit( &argc, argv );
	glutInitContextVersion( 4, 3 );
	glutInitContextProfile( GLUT_COMPATIBILITY_PROFILE );
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
	glutInitWindowSize( 600, 600 );
	glutInitWindowPosition( 0, 0 );
	glutCreateWindow( "Ellipse" );
	
	glutDisplayFunc( drawScene );
	glutReshapeFunc( resize );
	glutKeyboardFunc( keyInput );

	//glewExperimental = GL_TRUE;
	//glewInit();

	glClearColor( 1,1,1,0 );
	
	setup();
	glutMainLoop();

	return 0;
}
