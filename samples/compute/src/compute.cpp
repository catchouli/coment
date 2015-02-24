#include <iostream>
#include <ctime>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "gl/Texture.h"
#include "util/SDLWindow.h"
#include "util/ComputeShader.h"
#include "util/MemoryLeakDetection.h"
#include "resources/Mesh.h"

//#include <assimp/Importer.hpp>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

const float ASPECT = (float)WINDOW_HEIGHT / (float)WINDOW_WIDTH;

const int LOCAL_BLOCK_WIDTH = 32;

const int DISPATCH_BLOCK_WIDTH = (WINDOW_WIDTH + LOCAL_BLOCK_WIDTH - 1) / LOCAL_BLOCK_WIDTH;
const int DISPATCH_BLOCK_HEIGHT = (WINDOW_HEIGHT + LOCAL_BLOCK_WIDTH - 1) / LOCAL_BLOCK_WIDTH;

bool checkGlError();

int entry(int argc, char** argv)
{
    bool running = true;
    int sphereCount = 0;
    
    // Seed RNG
    srand((unsigned int)time(0));

    // Set up memory leak detection
    coment::setupMemoryLeakDetection();

    // SDL stuff
    coment::SDLWindow sdlWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Compute");

    // Capture mouse
    SDL_SetRelativeMouseMode(SDL_TRUE);

    // Load mesh
    coment::Mesh mesh("miku.md2");
    const coment::SubMesh* miku = mesh.getSubMesh(0);

    // Allocate textures
    coment::Texture2D renderTexture(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA32F);

    coment::Texture1D sphereTex;
    coment::Texture1D velocityTex;

    coment::Texture1D meshTex(miku->vertices.size() * 2, GL_RGBA32F, GL_RGBA, GL_FLOAT, (void*)miku->vertices.data());

    // Load shaders
    coment::ComputeShader cs({
        "shaders/version430.glsl",
        "shaders/constants.glsl",
        "shaders/raycast.glsl",
        "shaders/raycast_spheres.glsl",
        "shaders/raycast_mesh.glsl",
        "shaders/render.cs.glsl"
    });

    coment::ComputeShader gravity({
        "shaders/version430.glsl",
        "shaders/gravity.cs.glsl",
    });

    coment::ComputeShader movement({
        "shaders/version430.glsl",
        "shaders/movement.cs.glsl",
    });

    // Camera transform
    GLuint eyePosLoc = glGetUniformLocation(cs.shaderProgram.get(), "eye_position");
    GLuint eyeRotationLoc = glGetUniformLocation(cs.shaderProgram.get(), "eye_rotation");

    glm::vec3 eyePos(72, 0, 17), eyeRot(0.15f, -1.0f, 0);

    glm::mat4 eyeRotation;

    glm::vec3 eyeForward;
    glm::vec3 eyeLeft;
    glm::vec3 eyeUp;

    auto updateEyeTransform = [&]()
    {
        eyeRotation =
            glm::translate(eyePos) *
            glm::rotate(eyeRot.x, glm::vec3(1.0f, 0.0f, 0.0f)) *
            glm::rotate(eyeRot.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::rotate(eyeRot.z, glm::vec3(0.0f, 0.0f, 1.0f));

        eyeForward = glm::vec3(glm::vec4(0.0f, 0.0f, -1.0f, 0.0f) * eyeRotation);
        eyeLeft = glm::vec3(glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f) * eyeRotation);
        eyeUp = glm::vec3(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f) * eyeRotation);
    };

    {
        // Generate spheres
        std::vector<glm::vec4> spheres;
        std::vector<glm::vec4> velocities;

        for (int i = 0; i < sphereCount; ++i)
        {
            auto randf = []() { return rand() / (float)RAND_MAX; };

            const float MIN_RADIUS = 3.0f;
            const float MAX_RADIUS = 7.0f;
            const float RADIUS_RANGE = MAX_RADIUS - MIN_RADIUS;

            float x = randf() * 500.0f - 250.0f;
            float y = randf() * 500.0f - 250.0f;
            float z = randf() * 500.0f - 250.0f;
            float r = randf() * RADIUS_RANGE + MIN_RADIUS;

            spheres.push_back(glm::vec4(x, y, z, r));
            velocities.push_back(glm::vec4());
        }

        // Upload to GPU
        sphereTex.create(sphereCount, GL_RGBA32F, GL_RGBA, GL_FLOAT, (void*)spheres.data());
        velocityTex.create(sphereCount, GL_RGBA32F, GL_RGBA, GL_FLOAT, (void*)velocities.data());
    }

    // Main loop
    while (running)
    {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // Handle window closure
            if ((event.type == SDL_QUIT) ||
                (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
            {
                // Let the program exit after this iteration ends
                running = false;
            }
        }

        // Update frame timer
        static int frames = 0;
        static int fps = 0;
        static Uint32 lastUpdate = SDL_GetTicks();
        static Uint32 lastFpsUpdate = SDL_GetTicks();

        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastUpdate) / 1000.0f;
        lastUpdate = currentTime;

        frames++;
        if (currentTime - lastFpsUpdate >= 1000)
        {
            lastFpsUpdate = currentTime;
            fps = frames;
            frames = 0;
        }

        // Update title
        std::ostringstream os;
        os << fps;
        os << " [" << eyePos.x << ", " << eyePos.y << ", " << eyePos.z << "]";

        SDL_SetWindowTitle(sdlWindow.getSDLWindow(), os.str().c_str());

        // Update eye transform
        const float MOVE_SPEED = 60.0f;

        int dx, dy;
        const Uint8* keyState = SDL_GetKeyboardState(nullptr);
        SDL_GetRelativeMouseState(&dx, &dy);

        eyeRot.y += dx * 0.005f;
        eyeRot.x = glm::clamp(eyeRot.x + dy * 0.005f, -1.0f, 1.0f);;

        updateEyeTransform();

        if (keyState[SDL_SCANCODE_W])
            eyePos += eyeForward * deltaTime * MOVE_SPEED;
        if (keyState[SDL_SCANCODE_A])
            eyePos += eyeLeft * deltaTime * MOVE_SPEED;
        if (keyState[SDL_SCANCODE_S])
            eyePos += -eyeForward * deltaTime * MOVE_SPEED;
        if (keyState[SDL_SCANCODE_D])
            eyePos += -eyeLeft * deltaTime * MOVE_SPEED;
        if (keyState[SDL_SCANCODE_Q])
            eyePos += -eyeUp * deltaTime * MOVE_SPEED;
        if (keyState[SDL_SCANCODE_E])
            eyePos += eyeUp * deltaTime * MOVE_SPEED;

        // Update mesh position
        mesh.transform(glm::rotate(currentTime / 1000.0f, glm::vec3(0, 1, 0)));
        meshTex.create(miku->vertices.size() * 2, GL_RGBA32F, GL_RGBA, GL_FLOAT, (void*)miku->vertices.data());
 
        // Update sphere positions
        glBindImageTexture(0, sphereTex, 0, false, 0, GL_READ_WRITE, GL_RGBA32F);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_1D, velocityTex);
        glUseProgram(movement.shaderProgram.get());

        // Set time
        glUniform1f(0, deltaTime);

        // Update movement
        glDispatchCompute(sphereCount, 1, 1);

        // Update sphere gravity and collision
        glBindImageTexture(0, sphereTex, 0, false, 0, GL_READ_WRITE, GL_RGBA32F);
        glBindImageTexture(1, velocityTex, 0, false, 0, GL_READ_WRITE, GL_RGBA32F);
        glUseProgram(gravity.shaderProgram.get());

        // Set time
        glUniform1f(0, deltaTime);

        // Update - iterate intersections and gravity
        glDispatchCompute(sphereCount, sphereCount, 1);

        // Render
        glUseProgram(cs.shaderProgram.get());
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_1D, sphereTex);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_1D, meshTex);
        glBindImageTexture(0, renderTexture, 0, false, 0, GL_WRITE_ONLY, GL_RGBA32F);
        glUniform3fv(eyePosLoc, 1, (float*)&eyePos);
        glUniformMatrix4fv(eyeRotationLoc, 1, GL_FALSE, (float*)&eyeRotation);

        glDispatchCompute(
            DISPATCH_BLOCK_WIDTH,
            DISPATCH_BLOCK_HEIGHT,
            1);

        // Render full screen quad
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glUseProgram(0);
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, renderTexture);

        const float FULLSCREEN_QUAD[] =
        {
            // position,  texture coords
            -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 0.0f, 1.0f
        };

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(2, GL_FLOAT, 4 * sizeof(float), FULLSCREEN_QUAD);
        glTexCoordPointer(2, GL_FLOAT, 4 * sizeof(float), &FULLSCREEN_QUAD[2]);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        //// Render triangle
        //glMatrixMode(GL_PROJECTION);
        //glm::mat4 proj = glm::infinitePerspective(1.5f, ASPECT, 1.0f);
        //glLoadMatrixf((float*)&proj);

        //glDisable(GL_TEXTURE_2D);
        //glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        //glColor3f(1.0f, 1.0f, 1.0f);
        //glVertexPointer(3, GL_FLOAT, 4 * sizeof(float), meshVertices.data());
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        // Flip buffers
        SDL_GL_SwapWindow(sdlWindow.getSDLWindow());

#ifdef _DEBUG
        if (running)
            running = checkGlError();
#endif
    }

    return 0;
}

bool checkGlError()
{
    // Check for opengl errors
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        fprintf(stderr, "opegnl error: %s\n", gluErrorString(err));
        system("pause");
        return false;
    }

    return true;
}