#ifndef _GAME_H
#define _GAME_H

bool inside(int x, int y, SDL_Rect r) {
    return x >= r.x && x <= r.x+r.w && y >= r.y && y <= r.y+r.h;
}

bool overlap(const SDL_Rect& r1, const SDL_Rect& r2) {
    return inside(r1.x, r1.y, r2) || inside(r1.x + r1.w, r1.y, r2) ||
            inside(r1.x, r1.y+r1.h, r2) || inside(r1.x+r1.w, r1.y+r1.h, r2);
}

#endif // GAME_H
