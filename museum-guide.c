#include "main.h"

list_item items[MAX_ITEMS];
int item_count = 0;

bool init_font(SDL_Window *window){
    if(!TTF_Init()){
		printf("Could not initialize SDL_TTF: %s\n", SDL_GetError());
		return false;
	}

    title_font = TTF_OpenFont("src/font/freesansbold.ttf", TITLE_SIZE);
	if(title_font == NULL){
		printf("Failed to loading font: %s\n", SDL_GetError());
		return false;
	}

    desc_font = TTF_OpenFont("src/font/freesansbold.ttf", DESC_SIZE);
	if(desc_font == NULL){
		printf("Failed to loading font: %s\n", SDL_GetError());
		return false;
	}

    SDL_GetWindowSizeInPixels(window, &curr_screen_width, &curr_screen_height);

    return true;
}

bool create_title(SDL_Renderer *renderer, const char *title){
    if (!title) {
        printf("create_title: title is NULL\n");
        return false;
    }
    SDL_Surface *title_surf = TTF_RenderText_Blended(title_font, title, 0, TEXT_COLOR);
	if(title_surf == NULL){
		printf("Failed rendering text to surface: %s\n", SDL_GetError());
		return false;
	}

    title_prop.title_rect.w = (float)title_surf->w;
    title_prop.title_rect.h = (float)title_surf->h;
    title_prop.title_img = SDL_CreateTextureFromSurface(renderer, title_surf);;
    SDL_DestroySurface(title_surf);
    title_surf = NULL;

    if (!title_prop.title_img){
		printf("Failed creating texture from surface: %s\n", SDL_GetError());
		return false;
    }

    return true;
}

bool create_description(SDL_Renderer *renderer, const char *description){
    if (!description) {
        printf("create_description: description is NULL\n");
        return false;
    }
    int description_width = (curr_screen_width / 4) - (2 * (curr_screen_width / 100));

    SDL_Surface *desc_surf = TTF_RenderText_Blended_Wrapped(desc_font, description, 0, TEXT_COLOR, description_width);
	if(desc_surf == NULL){
		printf("Failed rendering text to surface: %s\n", SDL_GetError());
		return false;
	}

    desc_prop.desc_rect.w = (float)desc_surf->w;
    desc_prop.desc_rect.h = (float) desc_surf->h;
    desc_prop.desc_img = SDL_CreateTextureFromSurface(renderer, desc_surf);

    SDL_DestroySurface(desc_surf);
    desc_surf = NULL;

    if (!desc_prop.desc_img){
		printf("Failed creating texture from surface: %s\n", SDL_GetError());
		return false;
    }

    return true;
}

void create_list_item(int id, char *name, char * age) {
    if (item_count >= MAX_ITEMS) {
        printf("Item list is full!\n");
        return;
    }
    
    items[item_count].id = id;
    items[item_count].name = name;
    items[item_count].age = age;
    items[item_count].pos.x = 0;
    items[item_count].pos.y = 0;
    items[item_count].pos.w = 0;
    items[item_count].pos.h = 0;
    
    item_count++;
}

void fill_item_list(void) {
    item_count = 0;
    
    create_list_item(1, "Kaäba: Zwarte kubus", "1400");
    create_list_item(2, "Pyramide: van Gizeh", "4500");

}

void destroy_font(void){
    if (title_prop.title_img){
        SDL_DestroyTexture(title_prop.title_img);
        title_prop.title_img = NULL;
    }

    if (desc_prop.desc_img){
        SDL_DestroyTexture(desc_prop.desc_img);
        desc_prop.desc_img = NULL;
    }
    
    if(title_font){
		TTF_CloseFont(title_font);
        title_font = NULL;
	}

    if(desc_font){
		TTF_CloseFont(desc_font);
        desc_font = NULL;
	}
}
