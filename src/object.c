#include "object.h"

Object init_object(SDL_Renderer* renderer, int x, int y, int w, int h) {
    Object obj;

    obj.rect.x = x;
    obj.rect.y = y;
    obj.rect.w = w;
    obj.rect.h = h;

    obj.renderer = renderer;

    return obj;
}

void render_object(Object* object) {
    SDL_SetRenderDrawColor(object->renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderFillRect(object->renderer, &object->rect);
}
