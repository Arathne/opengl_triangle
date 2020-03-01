#ifndef Shader_h
#define Shader_h

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

class Shader
{
    private:
        Shader (void);
        void setCode (std::string file);
        void compile (void) const;
        
        unsigned int type;   
        char* code;
        unsigned int shader;
        
    public:
        Shader (unsigned int type, std::string file);
        ~Shader (void);
        void attach (unsigned int program) const;
};

#endif
