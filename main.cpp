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
    if (a.x+a.w<=b.x || b.x+b.w<= a.x || a.y+a.h<=b.y || b.y+b.h<=a.y) {
        return false;
    }
    return true;
}


void waitUntilKeyPressed() {
    SDL_Event e;
    while (true) {
        if (SDL_PollEvent(&e) !=0 &&(e.type==SDL_KEYDOWN || e.type==SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}


vector<Eg> eggs(8);
Enemy enemy[8] = {{0},{1},{2},{3},{4},{5},{6},{7}};
bool quit = false;
int point =0;
int _map =0;
int _time =0;
bool bs = false;
bool _alive = true;  // trạng thái người chơi
int xb,yb,x,y;

int main(int argc, char* argv[]) {
    srand(time(0));
    Graphics graphics;
    graphics.init();


    TTF_Font* font = graphics.loadFont("Starcraft Normal.ttf", 20);
    SDL_Color color = {255, 255, 0, 0};

    Mix_Music* gamemusic = Mix_LoadMUS("music.mp3");
    Mix_PlayMusic(gamemusic, -1);

    SDL_Texture* Player = graphics.loadTexture("Player.png");
    SDL_Texture* bullet = graphics.loadTexture("Fire.png");
    SDL_Texture* chicken = graphics.loadTexture("chicken.png");
    SDL_Texture* egg = graphics.loadTexture("eggs.png");
    SDL_Texture* backgroundmenu = graphics.loadTexture("Menu.jpg");
    SDL_Texture* background = graphics.loadTexture("backgroundgame.jpg");
    SDL_Texture* backgroundlos = graphics.loadTexture("gameover.jpg");

    SDL_ShowCursor(1);



    while (!quit) {
         SDL_Event event;
        switch (_map) {
            case 0: { 
                SDL_PollEvent(&event);
                graphics.prepareScene(backgroundmenu);
                graphics.presentScene();
                SDL_GetMouseState(&x, &y);

                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    if (x>=400 && x<=714 && y>= 227 && y<=484) {
                        _map = 1;
                        _alive = true;
                    }
                    if (x>=499 && x<=590 && y>=563 && y<=646) {
                        quit = true;
                    }
                }
                SDL_Delay(50);
                break;
            }
            case 1: { 
                SDL_PollEvent(&event);
                SDL_ShowCursor(0);
                graphics.prepareScene(background);

                SDL_GetMouseState(&x, &y);
                SDL_Rect charect = {x, y, 35, 35};
                if (x >= SCREEN_WIDTH - 50) x = SCREEN_WIDTH - 50;
                if (y >= SCREEN_HEIGHT - 50) y = SCREEN_HEIGHT - 50;
                graphics.renderTexture(Player, x, y);

                SDL_Texture* scText = graphics.renderText("Score : ", font, color);
                SDL_Texture* helloText = graphics.renderText(to_string(point).c_str(), font, color);
                graphics.renderTexture(helloText, 540, 30);
                graphics.renderTexture(scText, 430, 30);

                for (int i=0;i<eggs.size();i++) {
                    if (_time == 0) {
                        enemy[i].y = 0 - 55 - (i * 100);
                        eggs[i].x = enemy[i].x;
                        eggs[i].y = enemy[i].y + 5;
                        eggs[i].eggrect();
                        eggs[i].isalive = true;
                    }

                    if (enemy[i].alive) {
                        SDL_Rect chicken_rect = enemy[i].getRect();
                        SDL_RenderCopy(graphics.renderer, chicken, NULL, &chicken_rect);

                        if (overlap(charect, enemy[i].getRect())) {
                            _map = 2;
                            _alive = false;
                        }
                        enemy[i].updateposition(i);
                        if (bs && inside(xb, yb, chicken_rect)) {
                            bs = false;
                            enemy[i].alive = false;
                            point++;
                        }

                    }
                }

                _time++;

                for (int i=0;i<eggs.size();i++) {
                    if (eggs[i].isalive) {

                        graphics.renderTexture(egg, eggs[i].x,eggs[i].y);

                    }
                    if (eggs[i].y >= SCREEN_HEIGHT) {
                        eggs[i].y = enemy[i].y;
                        eggs[i].x = enemy[i].x;

                    }
                    eggs[i].eggrect();
                    eggs[i].updatey();

                    if (overlap(charect, eggs[i].eggrect())) {
                        _map = 2;
                        _alive = false;
                    }
                }

                // Tạo lại gà và trứng sau một khoảng thời gian
                if (_time % 50 ==0) {
                    for (int i=0;i<8;i++) {
                        if (!enemy[i].alive) {
                            bool collision;
                            do {
                                collision = false;
                                enemy[i].y = 0 - (rand() % 100) - 30;
                                enemy[i].x = rand() % (SCREEN_WIDTH - 55);
                                for (int j=0;j<8;j++) {
                                    if (j != i && enemy[j].alive && checkCollision(enemy[i].getRect(), enemy[j].getRect())) {
                                        collision = true;
                                        break;
                                    }
                                }
                            } while (collision);

                            enemy[i].alive = true;
                            if (!eggs[i].isalive) {
                                eggs[i].x = enemy[i].x;
                                eggs[i].y = enemy[i].y + 5;
                                eggs[i].eggrect();
                                eggs[i].isalive = true;
                            }

                        }
                    }
                }

                if (bs) {
                    yb -= 15;
                    graphics.renderTexture(bullet, xb, yb);
                }

                graphics.presentScene();

                if (event.type == SDL_MOUSEBUTTONDOWN && !bs) {
                    bs = true;
                    yb = y;
                    xb = x+20;

                }
                if (event.type == SDL_QUIT) {
                    quit = true;
                }
                if (yb <= 0) {
                    bs = false;
                }
                if (!_alive) {
                    for (int i=0; i<8;i++) {
                        enemy[i].generatelocation();
                        eggs[i].y = enemy[i].y;
                        eggs[i].x = enemy[i].x;
                        point = 0;
                    }
                }
                break;
            }
            case 2: { 
                SDL_ShowCursor(1);
                SDL_PollEvent(&event);
                graphics.prepareScene(backgroundlos);
                graphics.presentScene();
                SDL_GetMouseState(&x, &y);

                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    if (x >= 454 && x <= 537 && y >= 500 && y <= 533) {
                        _map = 0;
                        _alive = true;
                    }
                    if (x >= 600 && x <= 667 && y >= 500 && y <= 533) {
                        quit = true;
                    }
                }
                SDL_Delay(50);
                break;
            }
        }
    }

    if (gamemusic != nullptr) Mix_FreeMusic(gamemusic);
    graphics.quit();
    return 0;
}
