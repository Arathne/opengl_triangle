#include <GL/glew.h>
#include <GL/freeglut.h>

unsigned int vbo[2];
unsigned int vao[2];
int i = 0;

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
    
    glBindVertexArray( vao[i] );
    glEnableVertexAttribArray(0);
    
    glDrawArrays( GL_TRIANGLES, 0, 3 );

    glFlush();
}

void setup (void)
{
    glClearColor( 0.5, 0.5, 0.5, 1.0 );
    
    glGenVertexArrays( 2, vao );
    glGenBuffers( 2, vbo );
    
    glBindVertexArray( vao[0] );

    glBindBuffer( GL_ARRAY_BUFFER, vbo[0] );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*) 0 );

    glBindVertexArray( vao[1] );

    glBindBuffer( GL_ARRAY_BUFFER, vbo[1] );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*) 0 );
}

void keyboard (unsigned char key, int x, int y)
{
    if( key == 27 )
    {
        exit(0);
    }
    else if( key == 13 )
    {
        if( i == 0 ) 
            i = 1;
        else
            i = 0;
    }
    
    glutPostRedisplay();
}

int main( int argc, char** argv )
{
    glutInit( &argc, argv );
    glutInitContextVersion( 4, 3 );
    glutInitContextProfile( GLUT_COMPATIBILITY_PROFILE );
    
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
    glutInitWindowPosition( 100, 100 );
    glutInitWindowSize( 500, 500 );
    
    glutCreateWindow( "vertex array objects" );
    glutDisplayFunc( draw );
    glutKeyboardFunc( keyboard );
    
    glewInit();
    
    setup();
    glutMainLoop();
    
    return 0;
}





