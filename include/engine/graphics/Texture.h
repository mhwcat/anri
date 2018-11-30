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

        void loadSheet(std::string _name, std::string _path, Vec2f _offset, int _spritesInRow, int _spriteCount, SDL_Renderer *renderer);
        void setTextureByName(std::string _sheetName, bool _flipHorizontal, bool _playOnce);
        void setTextureById(unsigned int _sheetId, bool _flipHorizontal, bool _playOnce);
        void draw(int drawX, int drawY, int width, int height, double angle, SDL_Renderer *renderer);
        void nextSprite();
        uint8_t getAlpha();
        void setAlpha(uint8_t _alpha);

        void unloadAllSheets();
        bool isLoaded();
        bool isFlippedHorizontal();

    private:
        void setTexture(unsigned int _sheetId, bool _flipHorizontal, bool _playOnce);

        std::map<std::string, unsigned int> nameToIdMap;
        std::map<unsigned int, SDL_Texture*> textureSheets;
        std::map<unsigned int, Vec2f> offsets;
        std::map<unsigned int, unsigned int> spriteCounts;
        std::map<unsigned int, unsigned int> spritesInRow;
        std::map<unsigned int, unsigned int> currentSprites;
        std::map<unsigned int, unsigned int> currentSpritesInRows;
        std::map<unsigned int, unsigned int> currentRows;

        unsigned int lastId;
        unsigned int currentSheet;
        unsigned int lastSheet;
        Vec2f currentOffset;

        bool flipHorizontal;
        bool lastFlipHorizontal;
        uint8_t alpha;
        bool playOnce;


};


#endif //ANRI_TEXTURE_H
