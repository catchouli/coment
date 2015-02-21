#pragma once

#include <gl/glew.h>
#include <memory>
#include <vector>

namespace coment
{
    /** OpenGL texture wrapper */
    class Texture
    {
    public:

        /** Clean up the opengl texture */
        ~Texture();

        /** Unload the opengl texture */
        void unload();

        /** Convert texture object to opengl texture id */
        operator GLuint() const;

        /** Get opengl texture id */
        GLuint getHandle() const;

    protected:

        Texture() {}
        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        /** The ID of the opengl texture, or GL_INVALID_VALUE if not initialised */
        GLuint mTextureId = GL_INVALID_VALUE;

    };

    class Texture1D
        : public Texture
    {
    public:

        /** Create an unitialised opengl texture */
        Texture1D();

        /** Create a 1d opengl texture with the given parameters */
        Texture1D(
            int width,
            GLint internalFormat = GL_RGBA,
            GLenum format = GL_RGBA,
            GLenum type = GL_UNSIGNED_BYTE,
            void* data = nullptr
        );

        /** Create a 1d opengl texture with the given parameters */
        void create(
            int width,
            GLint internalFormat = GL_RGBA,
            GLenum format = GL_RGBA,
            GLenum type = GL_UNSIGNED_BYTE,
            void* data = nullptr
        );
    };

    class Texture2D
        : public Texture
    {
    public:

        /** Create an unitialised opengl texture */
        Texture2D();

        /** Create a 2d opengl texture with the given parameters */
        Texture2D(
            int width, int height,
            GLint internalFormat = GL_RGBA,
            GLenum format = GL_RGBA,
            GLenum type = GL_UNSIGNED_BYTE,
            void* data = nullptr
        );

        /** Create a 2d opengl texture with the given parameters */
        void create(
            int width, int height,
            GLint internalFormat = GL_RGBA,
            GLenum format = GL_RGBA,
            GLenum type = GL_UNSIGNED_BYTE,
            void* data = nullptr
        );
    };

    class Texture3D
        : public Texture
    {
    public:

        /** Create an unitialised opengl texture */
        Texture3D();

        /** Create a 3d opengl texture with the given parameters */
        Texture3D(
            int width, int height, int depth,
            GLint internalFormat = GL_RGBA,
            GLenum format = GL_RGBA,
            GLenum type = GL_UNSIGNED_BYTE,
            void* data = nullptr
        );

        /** Create a 3d opengl texture with the given parameters */
        void create(
            int width, int height, int depth,
            GLint internalFormat = GL_RGBA,
            GLenum format = GL_RGBA,
            GLenum type = GL_UNSIGNED_BYTE,
            void* data = nullptr
        );
    };

    /** Convert texture object to opengl texture id */
    inline Texture::operator GLuint() const
    {
        return mTextureId;
    }

    /** Get opengl texture id */
    inline GLuint Texture::getHandle() const
    {
        return mTextureId;
    }
}