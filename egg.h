#ifndef _EGG__H
#define _EGG__H

#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"

class Egg {
public:
    int x=0, y=0;
    int width, height;
    bool active=false;

   // Egg() : x(0), y(0), width(20), height(20), active(false) {}

    void drop(int startX, int startY) {
        x = startX;
        y = startY;
        active = true;
    }

    void updatePosition() {
        if (active) {
            y += 5;  // Điều chỉnh tốc độ rơi của trứng
            if (y > SCREEN_HEIGHT) {
                active = false;  // Vô hiệu hóa trứng khi nó rơi ra ngoài màn hình
            }
        }
    }

    SDL_Rect getRect() const {
        return {x, y, width, height};
    }
};

#endif
