#ifndef ANRI_TEXTURE_H
#define ANRI_TEXTURE_H

#include <SDL_render.h>
#include <map>
#include <engine/math/Vec2.h>
#include <vector>

class Texture
{
    public:
        Texture();
        virtual ~Texture();

        void loadSheet(std::string _id, std::string _path, Vec2 _offset, int _spriteCount, SDL_Renderer *renderer);
        void setTexture(std::string _sheetId, bool _flipHorizontal);
        void draw(int drawX, int drawY, int width, int height, SDL_Renderer *renderer);
        void nextSprite();

        void unloadAllSheets();
        bool isLoaded();

    private:
        std::map<std::string, SDL_Texture*> textureSheets;
        std::map<std::string, Vec2> offsets;
        std::map<std::string, int> spriteCounts;
        std::map<std::string, int> currentSprites;

        std::string currentSheet;
        Vec2 currentOffset;

        bool flipHorizontal;


};


#endif //ANRI_TEXTURE_H
