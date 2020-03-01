#include "shader.h"

Shader::Shader( unsigned int type, std::string file )
{
    this-> type = type;
    Shader::setCode( file );
    shader = glCreateShader( type );
    Shader::compile();
}

Shader::~Shader() 
{
    if( code != nullptr )
        delete[] code;
 
    glDeleteShader( shader );
}

void Shader::setCode (std::string file)
{
    std::ifstream input( file );
    std::stringstream buffer;
    buffer << input.rdbuf();
    input.close();

    std::string strCode = buffer.str();
    this-> code = new char[ strCode.length()+1 ];
    std::strcpy( code, strCode.c_str() );
}

void Shader::compile (void) const
{
    glShaderSource( shader, 1, &code, NULL );
    glCompileShader( shader );
    
    char infoLog[512];
    int success;
    glGetShaderiv( shader, GL_COMPILE_STATUS, &success );
    if( !success )
    {
        glGetShaderInfoLog( shader, 512, NULL, infoLog );
        std::cout << "ERROR::SHADER::COMPILATION::FAILED\n" << infoLog;
    }
}

void Shader::attach (unsigned int program) const
{
    glAttachShader( program, shader );
}
