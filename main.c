#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "header.h"

int mainenigme() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1) {
        printf("Failed to initialize TTF: %s\n", TTF_GetError());
        return 1;
    }

    init_sounds();

    SDL_Surface *screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
    if (!screen) {
        printf("Failed to set video mode: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *background = IMG_Load("pg.png");
    SDL_Surface *button = IMG_Load("q.png");
    if (!background || !button) {
        printf("Failed to load images.\n");
        return 1;
    }

    TTF_Font *font = TTF_OpenFont("font.ttf", 24);
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return 1;
    }

    SDL_Rect button_pos = {50, 500};

    load_questions();

    int running = 1;
    SDL_Event event;
    int player_score = 0;
    int user_answer = -1;
    int current_question_index = 0;

    while (running) {
        SDL_FillRect(screen, NULL, 0); // Clear screen before each render
        display_background_and_button(screen, background, button, button_pos);
        display_random_question(screen, font, current_question_index);
        SDL_Flip(screen);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                handle_input_enigme(&event, &player_score, &user_answer, &current_question_index);

                if (event.key.keysym.sym == SDLK_ESCAPE)
                    running = 0;
            }
        }

        SDL_Delay(100);
    }

    TTF_CloseFont(font);
    SDL_FreeSurface(background);
    SDL_FreeSurface(button);
    TTF_Quit();
    clean_up_sounds();
    SDL_Quit();

    return 0;
}

