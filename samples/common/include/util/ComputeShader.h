#pragma once

#include <GL/glew.h>
#include <memory>
#include "util/FileIO.h"

namespace coment
{
    struct ShaderDeleter
    {
        typedef GLuint pointer;

        void operator()(GLuint shader)
        {
            glDeleteShader(shader);
        }
    };

    struct ShaderProgramDeleter
    {
        typedef GLuint pointer;

        void operator()(GLuint program)
        {
            glDeleteProgram(program);
        }
    };

    struct ComputeShader
    {
        ComputeShader(std::initializer_list<const char*> files)
        {
            std::unique_ptr<GLuint, ShaderDeleter> shader;

            // Create shader program
            shaderProgram.reset(glCreateProgram());

            // Create shader
            shader.reset(glCreateShader(GL_COMPUTE_SHADER));

            // Load files
            auto sources = coment::readFiles(files);

            // Set shader source
            glShaderSource(shader.get(), sources.size(), glStrings(sources).get(), nullptr);

            // Compile shader
            glCompileShader(shader.get());

            // Get shader status
            int result;
            glGetShaderiv(shader.get(), GL_COMPILE_STATUS, &result);

            if (!result)
            {
                char log[1024];
                GLsizei length;
                glGetShaderInfoLog(shader.get(), 1023, &length, log);

                fprintf(stderr, "Failed to compile shader\n%s\n", log);

                shaderProgram.reset();

                throw std::runtime_error("Failed to compile shader");
            }

            // Link shader
            glAttachShader(shaderProgram.get(), shader.get());
            glLinkProgram(shaderProgram.get());
            
            // Get shader program status
            glGetProgramiv(shaderProgram.get(), GL_LINK_STATUS, &result);

            if (!result)
            {
                char log[1024];
                GLsizei length;
                glGetProgramInfoLog(shaderProgram.get(), 1023, &length, log);

                fprintf(stderr, "Failed to link program\n%s\n", log);

                shaderProgram.reset();

                throw std::runtime_error("Failed to link program");
            }
        }

        std::unique_ptr<GLuint, ShaderDeleter> shaderProgram;
    };
}