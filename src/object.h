#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "game.h"

typedef struct {
    int x, y, w, h;    

    SDL_Rect rect;
    SDL_Renderer* renderer;
} Object;

Object init_object(SDL_Renderer* renderer, int x, int y, int w, int h);

void render_object(Object* object);

#endif
