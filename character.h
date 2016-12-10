#ifndef CHARACTER_H
#define CHARACTER_H

#include "header.h"

class Character
{
    protected:
        ALLEGRO_BITMAP* characterSprite;
        Point pos;
        Bounds bounds;
        Velocity velocity;

    public: // Métodos
        Character(ALLEGRO_BITMAP* sprite, Point startingPos, Bounds bounds);
        ~Character();

        Point getPos();
        void setVelocity(Velocity v);

        void updatePosition();
        void draw();
};

#endif // CHARACTER_H
