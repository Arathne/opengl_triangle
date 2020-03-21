#ifndef Material_h
#define Material_h

#include <GL/glew.h>
#include <string>
#include <iostream>

class Texture
{
    private:
        Texture (void);
        
        std::string file;
        unsigned int id;
        unsigned char* data;
        int width;
        int height;
        int channels;
 
    public:
        ~Texture (void);
        Texture (std::string file);
        void load (unsigned int image_rgb, unsigned int opengl_rgb) const;
        void bind (void) const;
        void setId (unsigned int id);
};

#endif
