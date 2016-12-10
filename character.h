#ifndef CHARACTER_H
#define CHARACTER_H

#include "header.h"

class Character
{
    public: // Métodos
        Character(ALLEGRO_BITMAP* sprite, Point startingPos, Bounds bounds);
        ~Character(){};

        Point getPos();
        void setVelocity(Velocity v);

        void updatePosition();
        void draw();

    protected:
        Point pos;
        Bounds bounds;
        Velocity velocity;

        ALLEGRO_BITMAP* characterSprite;

};

#endif // CHARACTER_H
