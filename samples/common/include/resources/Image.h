#pragma once

#include <string.h>
#include <GL/glew.h>
#include <stdint.h>
#include <vector>

namespace coment
{
	class Image
	{
	public:

        Image();
		Image(const char* filename);

		bool load(const char* filename);
		inline void unload();

		GLuint genGlTexture();

		inline int32_t getWidth() const;
		inline int32_t getHeight() const;

		inline int* getPointer();

	private:
		std::vector<int> mPixels;
        int mWidth, mHeight;
	};

	void Image::unload()
	{
        mPixels.clear();
	}

	int Image::getWidth() const
	{
		return mWidth;
	}

    int Image::getHeight() const
	{
		return mHeight;
	}
}