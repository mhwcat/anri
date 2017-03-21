#ifndef ANRI_COLOR_H
#define ANRI_COLOR_H

#include <cstdint>

class Color 
{
	public:
		enum ColorName { RED, GREEN, BLUE, BLACK, WHITE };

		Color(ColorName _colorName);
		uint8_t getR();
		uint8_t getG();
		uint8_t getB();

	private:
		uint8_t r;
		uint8_t g;
		uint8_t b;
};

#endif