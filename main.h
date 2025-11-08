#ifndef MAIN_H
#define MAIN_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "museum-hall.h"
#include "museum-guide.h"
#include "museum-object.h"
#include "museum-exhibit.h"
#include "museum-navigator.h"

#include "src/obj_geometry/kaaba.h"
#include "src/obj_geometry/pyramide.h"

#define WINDOW_TITLE   "Monumetum museum"
#define SCREEN_WIDTH   1024
#define SCREEN_HEIGHT  576

extern SDL_Window  *window;
extern SDL_Renderer *renderer;
extern SDL_WindowFlags window_flags;
extern char *renderer_driver;
extern int curr_screen_width;
extern int curr_screen_height;

extern TTF_Font *title_font;
extern TTF_Font *desc_font;
extern title_properties title_prop;
extern description_properties desc_prop;
extern list_item_properties item_prop;

typedef struct {
     char *title;
     char *desc;
} window_detail;

typedef struct {
    window_detail window;
    struct navigation_handler nav_handler;
    selected_object *current_obj;
    bool auto_rotate;
    float auto_rotate_speed_x;  
} AppStateData;

#endif
