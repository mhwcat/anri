#include <game/Color.h>

Color::Color(ColorName _colorName)
{
    switch(_colorName)
    {
        case ColorName::RED:
            r = 255;
            g = 0;
            b = 0;
            break;
        case ColorName::GREEN:
            r = 0;
            g = 255;
            b = 0;
            break;
        case ColorName::BLUE:
            r = 0;
            g = 0;
            b = 255;
            break;
        case ColorName::BLACK:
            r = 0;
            g = 0;
            b = 0;
            break;
        case ColorName::WHITE:
            r = 255;
            g = 255;
            b = 255;
            break;
    }
}

uint8_t Color::getR()
{
    return r;
}

uint8_t Color::getG()
{
    return g;
}

uint8_t Color::getB()
{
    return b;
}

