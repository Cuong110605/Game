#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "defs.h"
#include "graphics.h"
#include "enemy.h"
#include "game.h"
#include "egg.h"

using namespace std;

bool checkCollision(SDL_Rect a, SDL_Rect b) {
    if (a.x + a.w <= b.x || b.x + b.w <= a.x || a.y + a.h <= b.y || b.y + b.h <= a.y) {
        return false;
    }
    return true;
}


void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
//vector<Enemy> enemy(8);
vector<Eg> eggs(8);
Enemy enemy[8]={{0},{1},{2},{3},{4},{5},{6},{7}} ;


bool quit = false;

int main(int argc, char *argv[])
{
    bool _alive = 1;

    srand(time(0));
    Graphics graphics;
    graphics.init();

    int point = 0;
    TTF_Font* font = graphics.loadFont("Starcraft Normal.ttf", 20);
    SDL_Color color = {255, 255, 0, 0};
    SDL_Texture* helloText = graphics.renderText(to_string(point).c_str(), font, color);
    //graphics.renderTexture(helloText, 200, 200);
    Mix_Music *gamemusic = graphics.loadMusic("gamemusic.mp3");

    SDL_Texture* Player = graphics.loadTexture("Player.png");
    SDL_Event event;
    int x, y;
    SDL_Texture* bullet = graphics.loadTexture("Fire.png");

    SDL_Texture* chicken = graphics.loadTexture("chicken.png");
    SDL_Texture* egg = graphics.loadTexture("eggs.png");


    bool bs = false;
    int xb,yb;




    int _map = 0;
    bool changedmap = 0;
    SDL_Texture* backgroundmenu = graphics.loadTexture("menu.jpg");
    SDL_Texture* background = graphics.loadTexture("bgroundgame.png");
    SDL_Texture* backgroundlos = graphics.loadTexture("gameover.jpg");

    SDL_ShowCursor(1);
    int _time = 0;

    while (!quit) {


switch(_map)
{
graphics.play(gamemusic);
    case 0:
{


        SDL_PollEvent(&event);
        graphics.prepareScene(backgroundmenu);

        graphics.presentScene();
        SDL_GetMouseState(&x,&y);

        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                if(x>=460&&x<=612&&y>=288&&y<=439)
                {
                    _map = 1;
                    _alive = 1;
                }
                if(x>=887&&x<=1080 &&y>=621&&y<=677)
                {
                    quit = true;
                }
                break;

            case SDL_MOUSEBUTTONUP:
             break;

        }
        SDL_Delay(50);
        break;
}
    case 1:
{


        SDL_PollEvent(&event);
        SDL_ShowCursor(0);
        graphics.prepareScene(background);


        SDL_GetMouseState(&x, &y);

        SDL_Rect charect;
        if (x>=SCREEN_WIDTH-50)
        {
            x =SCREEN_WIDTH-50;
        }
        if (y>=SCREEN_HEIGHT-50)
        {
            y = SCREEN_HEIGHT-50;
        }
        charect.x = x ;
        charect.y = y ;
        charect.w = 20;
        charect.h = 25;
        graphics.renderTexture(Player, x, y);

        SDL_Texture* scText = graphics.renderText("Score : ", font, color);
        SDL_Texture* helloText = graphics.renderText(to_string(point).c_str(), font, color);
        graphics.renderTexture(helloText, 540, 30);
        graphics.renderTexture(scText, 430, 30);

        for (int i = 0; i < eggs.size(); i ++)
        {
             if(_time==0)
   {
                   enemy[i].y = 0 - 55- (i * 100);

                  eggs[i].x = enemy[i].x;
                    eggs[i].y = enemy[i].y+5;
                    eggs[i].createrect();
                    eggs[i].isalive = 1;

   }
            if(enemy[i].alive == true)
            {

                SDL_Rect chicken_rect = enemy[i].getRect();
                SDL_RenderCopy(graphics.renderer, chicken,NULL, &chicken_rect);

                            if (inside(x,y,enemy[i].getRect()))
                            {
                                //quit = true;
                                _map=2;
                                _alive = 0;
                            }
                enemy[i].updateposition(i);
                if(bs == true && inside(xb, yb, chicken_rect))
                {
                    bs = false;
                    enemy[i].alive = false;
                    point++;

                }

            }
        }


        _time++;
        for (int i =0;i<8;i++)
        {
            if (eggs[i].isalive)
            {
                graphics.renderTexture(egg,eggs[i].x,eggs[i].y);
            }

            if (eggs[i].y>=SCREEN_HEIGHT)
            {
                eggs[i].y = enemy[i].y;
                eggs[i].x = enemy[i].x;

            }
            eggs[i].updatey();
            eggs[i].createrect();
            if (inside(x,y,eggs[i].eggrect))
            {
                _map = 2;
                _alive = 0;
            }
        }

       /* if (_time%50 ==0)
        {
            for (int i =0;i<8;i++)
            {
                if(enemy[i].alive==0)
                {
                enemy[i].alive = 1;
                enemy[i].y = 0- (rand()%100)-30;
                enemy[i]. x = rand() % (1100 -55);
                if (eggs[i].isalive==false)
                {
                    eggs[i].x = enemy[i].x;
                    eggs[i].y = enemy[i].y+5;
                    eggs[i].createrect();
                    eggs[i].isalive =1;
                }
                }
            }
        }*/
        if (_time % 50 == 0) {
                    for (int i = 0; i < 8; i++) {
                        if (enemy[i].alive == 0) {
                            bool collision;
                            do {
                                collision = false;
                                enemy[i].y = 0 - (rand() % 100) - 30;
                                enemy[i].x = rand() % (SCREEN_WIDTH - 55);


                                for (int j = 0; j < 8; j++) {
                                    if (j != i && enemy[j].alive && checkCollision(enemy[i].getRect(), enemy[j].getRect())) {
                                        collision = true;
                                        break;
                                    }
                                }
                            } while (collision);

                            enemy[i].alive = 1;
                            if (eggs[i].isalive == false) {
                                eggs[i].x = enemy[i].x;
                                eggs[i].y = enemy[i].y + 5;
                                eggs[i].createrect();
                                eggs[i].isalive = 1;
                            }
                        }
                    }
                }
        if (bs)
        {
            yb -= 20;
            graphics.renderTexture(bullet, xb, yb);
        }
        graphics.presentScene();

        switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            if (!bs)
            {
               bs = true;
               yb = y;
               xb = x;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            break;
        case SDL_QUIT:
            quit = true;
            break;
        }
        if (yb  <= 0)
        {
            bs = false;

        }
        if (_alive==0){
            for (int i=0;i<8;i++) {
                enemy[i].generatelocation();
                eggs[i].y=enemy[i].y;
                eggs[i].x=enemy[i].x;
                point =0;

            }
        }
        break;
}
    case 2:
{
        SDL_ShowCursor(1);

        SDL_PollEvent(&event);
        graphics.prepareScene(backgroundlos);

        graphics.presentScene();
        SDL_GetMouseState(&x,&y);

        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:

                if(x>=454&&x<=537&&y>=500&&y<=533)
                {

                    _map = 0;
                    _alive = 1;
                }
                if(x>=600&&x<=667 &&y>=500&&y<=533)
                {
                    quit = true;
                }
                break;

            case SDL_MOUSEBUTTONUP:
             break;

        }
        SDL_Delay(50);
        break;
}

}


    }

    graphics.quit();
    return 0;


}

