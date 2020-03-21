#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture (void) {}

Texture::~Texture (void)
{
    delete[] data;
}

Texture::Texture (std::string file, unsigned int image_rgb, unsigned int opengl_rgb) 
{
    glGenTextures( 1, &id );
    glBindTexture( GL_TEXTURE_2D, id );
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    
    data = stbi_load( file.c_str(), &width, &height, &channels, 0 );
    
    if( data )
    {
        glTexImage2D( GL_TEXTURE_2D, 0, image_rgb, width, height, 0, opengl_rgb, GL_UNSIGNED_BYTE, data );
        glGenerateMipmap( GL_TEXTURE_2D );
    }
    else
    {
        std::cout << "FAILED TO LOAD TEXTURE" << std::endl;
    }

    stbi_image_free( data );
}
