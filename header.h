#ifndef HEADER_H
#define HEADER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#define MAX_QUESTIONS 5
#define MAX_ANSWERS 3

typedef struct {
    char question[256];
    char answers[MAX_ANSWERS][256];
    int correct_answer;
} Enigme;

extern Enigme enigmes[MAX_QUESTIONS];
extern int total_questions;

void load_questions();
void display_random_question(SDL_Surface *screen, TTF_Font *font, int question_index);
void handle_input_enigme(SDL_Event *event, int *score, int *user_answer, int *question_index);
void display_background_and_button(SDL_Surface *screen, SDL_Surface *background, SDL_Surface *button, SDL_Rect button_pos);
void init_sounds();
void clean_up_sounds();
void display_result(SDL_Surface *screen, TTF_Font *font, int score, int total_questions);
int mainenigme();
#endif

