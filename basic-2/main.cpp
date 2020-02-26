#include <GL/glew.h>
#include <GL/freeglut.h>

#include <fstream> // for reading file
#include <sstream> // for converting file to string
#include <cstring> // for converting string to char array

unsigned int vbo;
unsigned int vao;
unsigned int shaderProgram;

static float vertices[] =
{
    -0.5f, -0.5f,
     0.5f, -0.5f,
     0.0f,  0.5f
};

void draw (void)
{
    glClear( GL_COLOR_BUFFER_BIT );
    
    glUseProgram( shaderProgram );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*) 0 );

    glDrawArrays( GL_TRIANGLES, 0, 3 );

    glFlush();
}

char* file_to_char (std::string fileName, char* content)
{
    std::ifstream input( fileName );
    std::stringstream buffer;
    buffer << input.rdbuf();
    input.close();

    std::string str_content = buffer.str();
    content = new char[ str_content.length()+1  ];
    
    std::strcpy( content, str_content.c_str() );
    
    return content;
}

void file_to_shader ( std::string vertexFile, std::string fragmentFile )
{
    char* src_vertex;
    char* src_fragment;
    
    src_vertex = file_to_char( vertexFile, src_vertex );  // convert file to a character array
    src_fragment = file_to_char( fragmentFile, src_fragment );

    unsigned int vertexShader = glCreateShader( GL_VERTEX_SHADER );  // create shaders
    unsigned int fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );

    glShaderSource( vertexShader, 1, &src_vertex, NULL );  // give shader data
    glShaderSource( fragmentShader, 1, &src_fragment, NULL );
    
    glCompileShader( vertexShader );  // compile shaders
    glCompileShader( fragmentShader );

    shaderProgram = glCreateProgram();
    
    glAttachShader( shaderProgram, vertexShader ); // attach shaders to a program
    glAttachShader( shaderProgram, fragmentShader );
    glLinkProgram( shaderProgram );
    
    glUseProgram( shaderProgram ); // use program with shaders attached to it

    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );
}

void setup (void)
{
    glClearColor( 0.5, 0.5, 0.5, 1.0 );
    file_to_shader( "vertex.shader", "fragment.shader" );
    
    glGenVertexArrays( 1, &vao );  // vao is required with core profile
    glBindVertexArray( vao );

    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

    glEnableVertexAttribArray(0);
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
    glutInitContextProfile( GLUT_CORE_PROFILE );

    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
    glutInitWindowSize( 500, 500 );
    glutInitWindowPosition( 100, 100 );
    
    glutCreateWindow( "basic 2" );
    glutDisplayFunc( draw );
    glutKeyboardFunc( keyboard );

    glewInit();
    setup();
    glutMainLoop();

    return 0;
}
