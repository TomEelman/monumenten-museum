#define SDL_MAIN_USE_CALLBACKS 1
#include "main.h"

SDL_Window   *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_WindowFlags window_flags = SDL_WINDOW_RESIZABLE;
char *renderer_driver = "opengl";
static bool positions_calculated = false;

int curr_screen_width;
int curr_screen_height;
TTF_Font *title_font = NULL;
TTF_Font *desc_font = NULL;
title_properties title_prop = {0};
description_properties desc_prop = {0};
list_item_properties item_prop = {0};

SDL_AppResult SDL_AppInit(void **app_state, int argc, char *argv[]) {
    (void)argc, (void)argv;

    AppStateData *state_data = SDL_malloc(sizeof(AppStateData));
    if (!state_data) {
        printf("Could not allocate memory for state_data: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetAppMetadata(WINDOW_TITLE, "1.0", "museum");
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        SDL_free(state_data);
        return SDL_APP_FAILURE;
    }

    window = SDL_CreateWindow(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
    if (!window) {
        printf("Failed to create window ERROR: %s\n", SDL_GetError());
        SDL_free(state_data);
        return SDL_APP_FAILURE;
    }

    renderer = SDL_CreateRenderer(window, renderer_driver);
    if (!renderer) {
        printf("Failed to create renderer ERROR: %s\n", SDL_GetError());
        SDL_free(state_data);
        return SDL_APP_FAILURE;
    }

    if (!init_font(window)) {
        return SDL_APP_FAILURE;
    }

    *app_state = state_data;

    AppStateData *state = (AppStateData *)state_data;
    state->auto_rotate = false;
    state->auto_rotate_speed_x = 0.02f;

    navigate[HALL](state);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *app_state, SDL_Event *event){
	AppStateData *state_data = (AppStateData *)app_state;

    switch(event->type){
		case SDL_EVENT_QUIT:
			return SDL_APP_SUCCESS;
		break;
		case SDL_EVENT_KEY_DOWN:
			if(event->key.scancode == SDL_SCANCODE_ESCAPE){
                if (state_data->nav_handler.curr_pos == HALL) {
				    return SDL_APP_SUCCESS;
                } else {
                    navigate[HALL](state_data);
                }
            }
            if (state_data->current_obj && !state_data->auto_rotate) {
                if (event->key.scancode == SDL_SCANCODE_LEFT) {
                    state_data->current_obj->pos.rotation.x += 0.2f;
                }
                if (event->key.scancode == SDL_SCANCODE_RIGHT) {
                    state_data->current_obj->pos.rotation.x -= 0.2f;
                }
                if (event->key.scancode == SDL_SCANCODE_UP) {
                    state_data->current_obj->pos.rotation.y += 0.2f;
                }
                if (event->key.scancode == SDL_SCANCODE_DOWN) {
                    state_data->current_obj->pos.rotation.y -= 0.2f;
                }
            }            
            if (event->key.scancode == SDL_SCANCODE_R && state_data->current_obj) {
                state_data->auto_rotate = !state_data->auto_rotate;
            }
            
            if (event->key.scancode == SDL_SCANCODE_Q && state_data->current_obj) {
                state_data->current_obj->pos.rotation.x = 0.0f;
                state_data->current_obj->pos.rotation.y = 0.0f;           
            }
        break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if(event->button.button == SDL_BUTTON_LEFT){        
                if(positions_calculated && state_data->nav_handler.curr_pos == HALL){
                    for (int i = 0; i < item_count; i++) {                    
                        if (event->button.x > items[i].pos.x && event->button.x < (items[i].pos.x + items[i].pos.w) &&
                            event->button.y > items[i].pos.y && event->button.y < (items[i].pos.y + items[i].pos.h)) {
                            int clicked_item = items[i].id;
                            navigate[clicked_item](app_state);
                        break;
                        }
                    }
                }
            }
    break;
        case SDL_EVENT_WINDOW_RESIZED:
            create_title(renderer, state_data->window.title);
            create_description(renderer, state_data->window.desc);
            positions_calculated = false;
        break;
	}
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *app_state){
	AppStateData *state_data = (AppStateData *)app_state;
    if (state_data->current_obj && state_data->auto_rotate) {
        state_data->current_obj->pos.rotation.x += state_data->auto_rotate_speed_x;
    }
        
    if (!positions_calculated) {
        calculate_item_positions();
        positions_calculated = true;
    }
    SDL_RenderClear(renderer);
    
    plot_background(renderer);
    plot_text(window, renderer);
    plot_controls(renderer, (int)state_data->nav_handler.curr_pos);

    if (!state_data->current_obj){
        plot_list(renderer);
    } else {
        plot_object(window, renderer, state_data->current_obj);    
    }

    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *app_state, SDL_AppResult result){
    (void)result;
    AppStateData *state_data = (AppStateData *)app_state;

    if (state_data) {
        SDL_free(state_data);
    }

    destroy_font();

    if(renderer){
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    
    if(window){
        SDL_DestroyWindow(window);
        window = NULL;
    }

    TTF_Quit();
    SDL_Quit();
}
