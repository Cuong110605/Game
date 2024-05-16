#ifndef _ENEMY__H
#define _ENEMY__H
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"

struct Enemy {

    int x, y, width, height;
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
   /* while(x<=150 ||x>=1000)
    {
         x = rand() % 1100 - width;
    }*/
    y = 0 - height - (index * 100);

}
void updateposition(int index)
{
    y ++;

    if ( y > SCREEN_HEIGHT || alive == false)
    {

          x = rand() % (1100-width) ;
          /*while(x<=150 ||x>=1000)
          {
           x = rand() % 1100 ;
          }*/
          alive = 1;
          y = 0 - height - (index * 100);
    }
}

};

    /*int x, y, width, height;
    bool alive;

    Enemy() : x(0), y(0), width(44), height(44), alive(true) {}

    void reset(int index) {
        x = rand() % 800 + 100 - width;
        y = 0 - height - (index * 100);
        alive = true;
    }

    void updateposition(int index) {
        y ++;

        if ( y > SCREEN_HEIGHT)
        {
        x = rand() % 800 ;
        y = 0 - height - (index*100);
        }

    }

    SDL_Rect getRect() const {
        return {x, y, width, height};
    }
*/

struct Eg {
  int x;
  int y;
  bool isalive=0;
  bool isfalling = 0;
  SDL_Rect eggrect;
  void updatey()
  {
     y+=2;
     eggrect.y+=2;
  }
  void createrect()
  {
      eggrect.x =x-40;
      if (x<=0)
      {
          x=0;
      }
      eggrect.y = y;
      eggrect.w = 100 ;
      eggrect.h =35;
  }
  SDL_Rect getrect()
  {
      return eggrect;
  }
};
#endif
