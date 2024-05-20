#ifndef _ENEMY__H
#define _ENEMY__H
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"

struct Enemy {

    int x=0, y=0, width, height;
    bool alive = true;



    SDL_Rect getRect() {
        return {x, y, 55,55};
    }
    void generatelocation()
    {
          x = rand() % (1100 -width) ;
          y = 0 - height - ((rand()%9) * 100);
    }
Enemy(int index)
{

    width = 55;
    height = 55;
    x = rand() % (1100 -width) ;

    y = 0 - height - (index * 100);

}
void updateposition(int index)
{
    y ++;

    if ( y > SCREEN_HEIGHT || alive == false)
    {

          x = rand() % (1100-width) ;
          alive = 1;
          y = 0 - height - (index * 100);
    }
}

};



struct Eg {
  int x=0;
  int y=0;
  int w,h;
  bool isalive=0;

  SDL_Rect eggrect() {
     return {x, y, 35,35};
  }
  void updatey()
  {
     y+=2;

  }

};
#endif
