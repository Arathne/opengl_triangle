#include <GL/glew.h>
#include <GL/freeglut.h>

unsigned int vbo;

static float vertices1[] =
{
    -0.5f, -0.5f,
     0.5f, -0.5f,
     0.0f,  0.5f
};

static float vertices2[] =
{
    -1.0f,  0.0f,
    -0.5f,  1.0f,
     0.0f,  0.0f
};

void draw (void)
{
    glClear( GL_COLOR_BUFFER_BIT );
    
    glDrawArrays( GL_TRIANGLES, 0, 6 );

    glFlush();
}

void setup (void)
{
    glClearColor( 0.5, 0.5, 0.5, 1.0 );

    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );

    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices1)+sizeof(vertices2), vertices1, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(vertices1), sizeof(vertices2), vertices2 );

    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*) 0 );
    glEnableVertexAttribArray(0);
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
    glutInitContextProfile( GLUT_COMPATIBILITY_PROFILE );

    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
    glutInitWindowSize( 500, 500 );
    glutInitWindowPosition( 100, 100 );
    
    glutCreateWindow( "buffer 3" );
    glutDisplayFunc( draw );
    glutKeyboardFunc( keyboard );

    glewInit();
    
    setup();
    glutMainLoop();

    return 0;
}
