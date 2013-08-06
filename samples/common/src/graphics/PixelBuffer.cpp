#include "graphics/PixelBuffer.h"

#include <stdio.h>

namespace coment
{
	namespace samples
	{
		PixelBuffer::PixelBuffer(unsigned int width, unsigned int height)
			: _buffer(new unsigned int[width * height]), _width(width), _height(height)
		{

		}

		PixelBuffer::~PixelBuffer()
		{
			delete[] _buffer;
		}

		void PixelBuffer::resize(unsigned int width, unsigned int height)
		{
			_width = width;
			_height = height;

			unsigned int* temp = _buffer;
			unsigned int* newBuffer = new unsigned int[width * height];

			_buffer = newBuffer;
			delete[] temp;
		}

		void PixelBuffer::clear(int colour)
		{
			for (unsigned int i = 0; i < _width * _height; ++i)
			{
				_buffer[i] = colour;
			}
		}

		void PixelBuffer::drawCircle(int colour, int radius, int cx, int cy)
		{
			int error = -radius;

			int x = radius;
			int y = 0;

			while (x >= y)
			{
				draw4lines(colour, cx, cy, x, y);

				error += y;
				++y;
				error += y;

				if (error >= 0)
				{
					error -= x;
					--x;
					error -= x;
				}
			}
		}

		void PixelBuffer::draw4lines(int colour, int cx, int cy, int x, int y)
		{
			draw2lines(colour, cx, cy, x, y);
			if (x != y)
				draw2lines(colour, cx, cy, y, x);
		}

		void PixelBuffer::draw2lines(int colour, int cx, int cy, int x, int y)
		{
			drawhline(colour, cx - x, cx + x, cy + y);
			if (x != 0 && y != 0)
				drawhline(colour, cx - x, cx + x, cy - y);
		}

		void PixelBuffer::drawhline(int colour, int x1, int x2, int y)
		{
			int i;
			int length;
			unsigned int* bufferPos;

			// Make sure we aren't drawing out of bounds
			if (x1 < 0)
				x1 = 0;
			else if (x1 >= (int)_width)
				x1 = (int)_width - 1;
			if (x2 < 0)
				x2 = 0;
			else if (x2 >= (int)_width)
				x2 = (int)_width - 1;
			if (y < 0)
				y = 0;
			else if (y >= (int)_height)
				y = (int)_height - 1;

			length = x2 - x1;
			bufferPos = _buffer + y * _width + x1;

			// Draw line
			for (i = 0; i < length; ++i)
			{
				*bufferPos = (unsigned int)colour;
				bufferPos++;
			}
		}
	}
}
