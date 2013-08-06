#ifndef COMENT_COMMON_PIXELBUFFER
#define COMENT_COMMON_PIXELBUFFER

namespace coment
{
	namespace samples
	{
		class PixelBuffer
		{
		public:
			PixelBuffer(unsigned int width = 0, unsigned int height = 0);
			~PixelBuffer();

			// Get pointer to buffer
			const unsigned int* getBuffer() const;
			unsigned int getWidth() const;
			unsigned int getHeight() const;

			// Resize buffer destructively
			void resize(unsigned int width, unsigned int height);

			// Clear buffer to colour
			void clear(int colour);

			// Draw a circle with midpoint circle algorithm
			void drawCircle(int colour, int radius, int cx, int cy);

		protected:
			// Functions used as part of midpoint circle algorithm
			void draw4lines(int colour, int cx, int cy, int x, int y);
			void draw2lines(int colour, int cx, int cy, int x, int y);
			void drawhline(int colour, int x1, int x2, int y);

		private:
			unsigned int* _buffer;
			unsigned int _width, _height;
		};

		inline const unsigned int* PixelBuffer::getBuffer() const
		{
			return _buffer;
		}

		inline unsigned int PixelBuffer::getWidth() const
		{
			return _width;
		}

		inline unsigned int PixelBuffer::getHeight() const
		{
			return _height;
		}
	}
}

#endif /* COMENT_COMMON_PIXELBUFFER */

