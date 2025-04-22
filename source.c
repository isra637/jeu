#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

Enigme enigmes[MAX_QUESTIONS];
int total_questions = 0;

void load_questions() {
    strcpy(enigmes[0].question, "What is the capital of France?");
    strcpy(enigmes[0].answers[0], "Paris");
    strcpy(enigmes[0].answers[1], "London");
    strcpy(enigmes[0].answers[2], "Rome");
    enigmes[0].correct_answer = 0;

    strcpy(enigmes[1].question, "What is 2 + 2?");
    strcpy(enigmes[1].answers[0], "3");
    strcpy(enigmes[1].answers[1], "4");
    strcpy(enigmes[1].answers[2], "5");
    enigmes[1].correct_answer = 1;

    strcpy(enigmes[2].question, "What color is the sky?");
    strcpy(enigmes[2].answers[0], "Blue");
    strcpy(enigmes[2].answers[1], "Green");
    strcpy(enigmes[2].answers[2], "Red");
    enigmes[2].correct_answer = 0;

    strcpy(enigmes[3].question, "Which is a fruit?");
    strcpy(enigmes[3].answers[0], "Carrot");
    strcpy(enigmes[3].answers[1], "Potato");
    strcpy(enigmes[3].answers[2], "Apple");
    enigmes[3].correct_answer = 2;

    strcpy(enigmes[4].question, "Which one is a programming language?");
    strcpy(enigmes[4].answers[0], "Python");
    strcpy(enigmes[4].answers[1], "Snake");
    strcpy(enigmes[4].answers[2], "Lizard");
    enigmes[4].correct_answer = 0;

    total_questions = 5;
}

void display_random_question(SDL_Surface *screen, TTF_Font *font, int question_index) {
    SDL_Color textColor = {255, 255, 255};
    SDL_Surface *text_surface;
    SDL_Rect text_position = {50, 50};

    char display_text[256];
    snprintf(display_text, sizeof(display_text), "Q: %s", enigmes[question_index].question);
    text_surface = TTF_RenderText_Solid(font, display_text, textColor);
    SDL_BlitSurface(text_surface, NULL, screen, &text_position);
    SDL_FreeSurface(text_surface);

    for (int i = 0; i < MAX_ANSWERS; i++) {
        char answer_text[256];
        sprintf(answer_text, "%c. %s", 'A' + i, enigmes[question_index].answers[i]);

        text_position.y += 40;
        text_surface = TTF_RenderText_Solid(font, answer_text, textColor);
        SDL_BlitSurface(text_surface, NULL, screen, &text_position);
        SDL_FreeSurface(text_surface);
    }
}

void handle_input_enigme(SDL_Event *event, int *score, int *user_answer, int *question_index) {
    switch (event->key.keysym.sym) {
        case SDLK_a:
            *user_answer = 0;
            break;
        case SDLK_b:
            *user_answer = 1;
            break;
        case SDLK_c:
            *user_answer = 2;
            break;
        default:
            return;
    }

    check_answer(*user_answer, score, *question_index);
    (*question_index)++;
}

void check_answer(int user_answer, int *score, int question_index) {
    if (user_answer == enigmes[question_index].correct_answer) {
        (*score)++;
        printf("Correct! Score: %d\n", *score);
    } else {
        printf("Wrong! Correct answer: %c\n", 'A' + enigmes[question_index].correct_answer);
    }
}

void display_background_and_button(SDL_Surface *screen, SDL_Surface *background, SDL_Surface *button, SDL_Rect button_pos) {
    SDL_BlitSurface(background, NULL, screen, NULL);
    SDL_BlitSurface(button, NULL, screen, &button_pos);
}

void init_sounds() {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    // Load music/effects here if needed
}

void clean_up_sounds() {
    Mix_CloseAudio();
}

