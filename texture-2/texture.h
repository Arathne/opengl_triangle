#ifndef Material_h
#define Material_h

#include <GL/glew.h>
#include <string>
#include <iostream>

class Texture
{
    private:
        Texture (void);
        
        unsigned int id;
        unsigned char* data;
        int width;
        int height;
        int channels;
 
    public:
        Texture (std::string file, unsigned int image_rgb, unsigned int opengl_rgb);
        ~Texture (void);
};

#endif
