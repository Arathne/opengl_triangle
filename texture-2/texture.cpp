#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture (void) {}

Texture::~Texture (void)
{
    if( data == nullptr )
        delete[] data;
}

Texture::Texture (std::string file) 
{
    this-> file = file;
    
    glGenTextures( 1, &id );
    data = stbi_load( file.c_str(), &width, &height, &channels, 0 );
}

void Texture::load (unsigned int image_rgb, unsigned int opengl_rgb) const
{
    glBindTexture( GL_TEXTURE_2D, id );
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    
    if( data )
    {
        glTexImage2D( GL_TEXTURE_2D, 0, image_rgb, width, height, 0, opengl_rgb, GL_UNSIGNED_BYTE, data );
        glGenerateMipmap( GL_TEXTURE_2D );
    }
    else
    {
        std::cout << "FAILED TO LOAD TEXTURE :: " << file << std::endl;
    }
}
