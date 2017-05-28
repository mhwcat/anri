#ifndef ANRI_I_MOVABLE_H
#define ANRI_I_MOVABLE_H

class IMovable
{
    public:
        virtual ~IMovable() {};
        virtual void move(float deltaTime) = 0;
};

#endif