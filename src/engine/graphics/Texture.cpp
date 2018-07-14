#include <SDL_image.h>
#include <engine/DebugPrint.h>
#include <engine/graphics/Texture.h>

Texture::Texture()
{
    lastId = 0;
    alpha = 255;
}

Texture::~Texture()
{
    unloadAllSheets();
}

void Texture::loadSheet(std::string _name, std::string _path, Vec2 _offset, int _spritesInRow, int _spriteCount, SDL_Renderer *renderer)
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(_path.c_str());
    if(loadedSurface == NULL)
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", _path.c_str(), IMG_GetError() );
        return;
    }

    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if(newTexture == NULL)
    {
        printf( "Unable to create texture from %s! SDL Error: %s\n", _path.c_str(), SDL_GetError() );
    }

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
    
    unsigned int sheetId = ++lastId;

    nameToIdMap[_name] = sheetId;
    textureSheets[sheetId] = newTexture;
    offsets[sheetId] = _offset;
    spriteCounts[sheetId] = _spriteCount;
    spritesInRow[sheetId] = _spritesInRow;
    currentRows[sheetId] = 1;
    currentSpritesInRows[sheetId] = 0;
    setTexture(sheetId, false, false);
}

void Texture::setTextureByName(std::string _sheetName, bool _flipHorizontal, bool _playOnce)
{
    setTexture(nameToIdMap[_sheetName], _flipHorizontal, _playOnce);
}

void Texture::setTextureById(unsigned int _sheetId, bool _flipHorizontal, bool _playOnce)
{
    setTexture(_sheetId, _flipHorizontal, _playOnce);
}

void Texture::setTexture(unsigned int _sheetId, bool _flipHorizontal, bool _playOnce)
{
    lastSheet = currentSheet; 
    lastFlipHorizontal = flipHorizontal;

    if(_sheetId != currentSheet)
    {
        currentSheet = _sheetId;
        currentSprites[_sheetId] = 0;
    }

    flipHorizontal = _flipHorizontal;
    playOnce = _playOnce;
}


void Texture::nextSprite() 
{
    if(currentSprites[currentSheet] >= spriteCounts[currentSheet] - 1) 
    {
        currentSprites[currentSheet] = 0;
        currentRows[currentSheet] = 1;
        currentSpritesInRows[currentSheet] = 0;

        if(playOnce)
        {
            setTexture(lastSheet, lastFlipHorizontal, false);
        }
    } else
    {
        currentSprites[currentSheet]++;
        currentSpritesInRows[currentSheet]++;

        if(currentSpritesInRows[currentSheet] >= spritesInRow[currentSheet])
        {
            currentRows[currentSheet]++;
            currentSpritesInRows[currentSheet] = 0;
        }
    }
}

void Texture::draw(int drawX, int drawY, int width, int height, SDL_Renderer *renderer)
{
    SDL_Rect renderQuad = { drawX, drawY, width, height };
    SDL_Rect clip = { currentSpritesInRows[currentSheet] * offsets[currentSheet].x, (currentRows[currentSheet] - 1) * offsets[currentSheet].y, width, height };

    SDL_SetTextureAlphaMod(textureSheets[currentSheet], alpha);
    SDL_RenderCopyEx(renderer, textureSheets[currentSheet], &clip, &renderQuad, NULL, NULL, flipHorizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Texture::unloadAllSheets()
{
    for(auto const& textureSheet : textureSheets)
    {
        SDL_DestroyTexture(textureSheet.second);
    }

   textureSheets.clear();
   offsets.clear();
   spriteCounts.clear();
   spritesInRow.clear();
   currentSprites.clear();
   currentRows.clear();
   currentSpritesInRows.clear();
}

bool Texture::isLoaded() 
{
    return !textureSheets.empty();
}

bool Texture::isFlippedHorizontal()
{
    return flipHorizontal;
}

uint8_t Texture::getAlpha() 
{
    return alpha;
}

void Texture::setAlpha(uint8_t _alpha)
{
    if(_alpha < 0)
        _alpha = 0;
    if(_alpha > 255)
        _alpha = 255;

    this->alpha = _alpha;
}

