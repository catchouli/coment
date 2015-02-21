#include "gl/Texture.h"

#include <gl/glew.h>

namespace coment
{
    /** Create an unitialised opengl texture */
    Texture1D::Texture1D()
    {
    }

    /** Create an unitialised opengl texture */
    Texture2D::Texture2D()
    {
    }

    /** Create an unitialised opengl texture */
    Texture3D::Texture3D()
    {
    }

    /** Create an opengl texture with the given parameters */
    Texture1D::Texture1D(int width,
        GLint internalFormat, GLenum format, GLenum type, void* data)
    {
        create(width, internalFormat, format, type, data);
    }

    /** Create an opengl texture with the given parameters */
    Texture2D::Texture2D(int width, int height,
        GLint internalFormat, GLenum format, GLenum type, void* data)
    {
        create(width, height, internalFormat, format, type, data);
    }

    /** Create an opengl texture with the given parameters */
    Texture3D::Texture3D(int width, int height, int depth,
        GLint internalFormat, GLenum format, GLenum type, void* data)
    {
        create(width, height, depth, internalFormat, format, type, data);
    }

    /** Create an opengl texture with the given parameters */
    void Texture1D::create(int width,
        GLint internalFormat, GLenum format, GLenum type, void* data)
    {
        unload();

        // Generate texture ID
        glGenTextures(1, &mTextureId);
        glBindTexture(GL_TEXTURE_1D, mTextureId);

        // Allocate texture (optionally specifying data)
        glTexImage1D(GL_TEXTURE_1D, 0, internalFormat, width, 0, format, type, data);

        // Set texture parameters
        glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    }

    /** Create an opengl texture with the given parameters */
    void Texture2D::create(int width, int height,
    GLint internalFormat, GLenum format, GLenum type, void* data)
    {
        unload();

        // Generate texture ID
        glGenTextures(1, &mTextureId);
        glBindTexture(GL_TEXTURE_2D, mTextureId);

        // Allocate texture (optionally specifying data)
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, data);

        // Set texture parameters
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    }

    /** Create an opengl texture with the given parameters */
    void Texture3D::create(int width, int height, int depth,
    GLint internalFormat, GLenum format, GLenum type, void* data)
    {
        unload();

        // Generate texture ID
        glGenTextures(1, &mTextureId);
        glBindTexture(GL_TEXTURE_3D, mTextureId);

        // Allocate texture (optionally specifying data)
        glTexImage3D(GL_TEXTURE_3D, 0, internalFormat, width, height, depth, 0, format, type, data);

        // Set texture parameters
        glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    }

    /** Clean up the opengl texture */
    Texture::~Texture()
    {
        unload();
    }

    /** Unload the opengl texture */
    void Texture::unload()
    {
        if (mTextureId != GL_INVALID_VALUE)
        {
            // Unload texture and clean up ID
            glDeleteTextures(1, &mTextureId);
            mTextureId = GL_INVALID_VALUE;
        }
    }
}