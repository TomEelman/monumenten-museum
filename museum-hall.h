#ifndef MUSEUM_HALL_H
#define MUSEUM_HALL_H

#include "museum-guide.h"

#define TITLE_SIZE 40
#define DESC_SIZE  13
#define TEXT_COLOR (SDL_Color){0, 0, 0, 255}

extern float padding;
extern float text_spacing;

typedef struct {
    SDL_Surface *title_surf;
    SDL_Texture *title_img;
    SDL_FRect    title_rect;
} title_properties;

typedef struct {
    SDL_Surface *desc_surf;
    SDL_Texture *desc_img;
    SDL_FRect    desc_rect;
} description_properties;

typedef struct {
    SDL_Surface *item_surf;
    SDL_Texture *item_img;
    SDL_FRect    item_rect;
    SDL_FRect    item_name_rect;
} list_item_properties;

SDL_AppResult plot_background(SDL_Renderer *renderer);
void plot_title(SDL_Renderer *renderer);
void plot_description(SDL_Renderer *renderer);

void plot_list_item_details(SDL_Renderer *renderer, list_item *item);
SDL_AppResult plot_list_item(SDL_Renderer *renderer);
void plot_list(SDL_Renderer *renderer);

void calculate_item_positions(void);
void plot_text(SDL_Window *window, SDL_Renderer *renderer);
void plot_controls(SDL_Renderer *renderer, int curr_pos);

#endif
