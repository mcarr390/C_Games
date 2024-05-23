#include <SDL2/SDL.h>
#include <stdio.h>

// Player structure to store position
typedef struct {
    int x;
    int y;
    int speed;
} Player;

// Player structure to store position
typedef struct {
    int x;
    int y;
    int speed;
} Ball;

const int WIDTH = 1280;
const int HEIGHT = 960;

Player UpdatePlayerPosition(SDL_Event *e, Player *player);

int main(int argc, char* argv[]) {
    // try to initialize the video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
   
    SDL_Window *win = SDL_CreateWindow("Simple Game", 500, 500, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL) {
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // MAIN GAME LOOP
    SDL_Event e;
    int quit = 0;



    // Initialize player
    Player player = {320, 240, 5};

    Ball ball = {100, 100, 30};

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN) {
                player = UpdatePlayerPosition(&e, &player);
            }
        }

        // RENDERING
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        // Draw ball
        SDL_Rect ballRect = { ball.x, ball.y, 30, 30 };
        SDL_SetRenderDrawColor(ren, 0, 255, 0, 255); // Red color
        SDL_RenderFillRect(ren, &ballRect);

        // Draw player square
        SDL_Rect playerRect = { player.x, player.y, 30, 30 };
        SDL_SetRenderDrawColor(ren, 255, 0, 0, 255); // Red color
        SDL_RenderFillRect(ren, &playerRect);

        // Draw a white rectangle
        SDL_Rect rect = { 200, 150, 240, 180 };
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderFillRect(ren, &rect);

        SDL_RenderPresent(ren);
        // RENDERING END
    }

    // END MAIN GAME LOOP

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}

Player UpdatePlayerPosition(SDL_Event *e, Player *player) {
    switch ((*e).key.keysym.sym) {
        case SDLK_w:
            (*player).y -= (*player).speed;
            break;
        case SDLK_s:
            (*player).y += (*player).speed;
            break;
        case SDLK_a:
            (*player).x -= (*player).speed;
            break;
        case SDLK_d:
            (*player).x += (*player).speed;
            break;

    }
    return (*player);
}
