#include <SDL_image.h>
#include <engine/DebugPrint.h>
#include <engine/graphics/Texture.h>

Texture::Texture()
{

}

Texture::~Texture()
{
    unloadAllSheets();
}

void Texture::loadSheet(std::string _id, std::string _path, Vec2 _offset, int _spriteCount, SDL_Renderer *renderer)
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
    
    textureSheets[_id] = newTexture;
    offsets[_id] = _offset;
    spriteCounts[_id] = _spriteCount;
    setTexture(_id, false);
}

void Texture::setTexture(std::string _sheetId, bool _flipHorizontal)
{
    if(_sheetId.compare(currentSheet) != 0)
    {
        currentSheet = _sheetId;
        currentSprites[_sheetId] = 0;
    }

    flipHorizontal = _flipHorizontal;
}

void Texture::nextSprite() 
{
    if(currentSprites[currentSheet] >= spriteCounts[currentSheet] - 1) 
    {
        currentSprites[currentSheet] = 0;
    } else
    {
        currentSprites[currentSheet]++;
    }


    //printf("%d\n", currentSprites[currentSheet]);
}

void Texture::draw(int drawX, int drawY, int width, int height, SDL_Renderer *renderer)
{
    SDL_Rect renderQuad = { drawX, drawY, width, height };
    SDL_Rect clip = { currentSprites[currentSheet] * offsets[currentSheet].x, currentSprites[currentSheet] * offsets[currentSheet].y, width, height };

    SDL_RenderCopyEx(renderer, textureSheets[currentSheet], &clip, &renderQuad, NULL, NULL, flipHorizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Texture::unloadAllSheets()
{
    for(auto const& textureSheet : textureSheets)
    {
        SDL_DestroyTexture(textureSheet.second);
    }

   textureSheets.clear();
}

bool Texture::isLoaded() 
{
    return !textureSheets.empty();
}