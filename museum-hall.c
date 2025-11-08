#include "main.h"

SDL_FRect item_list_rect;
float padding = 8;
float text_spacing = 2;
float title_offset = 0;
float description_offset = 0;

SDL_AppResult plot_background(SDL_Renderer *renderer) {
    static SDL_Texture *bg_texture = NULL;
	SDL_Surface *bg_surface = NULL;
	char *bmp_path = NULL;

	SDL_asprintf(&bmp_path, "%ssrc/bg.bmp", SDL_GetBasePath());

 	bg_surface = SDL_LoadBMP(bmp_path);
	if (!bg_surface) {
		SDL_free(bmp_path);
		SDL_Log("Couldn't load bitmap: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	SDL_free(bmp_path);

	bg_texture = SDL_CreateTextureFromSurface(renderer, bg_surface);
    SDL_DestroySurface(bg_surface);
  	if (!bg_texture) {
  		SDL_Log("Couldn't create static texture: %s", SDL_GetError());
  		return SDL_APP_FAILURE;
  	}
    
    SDL_GetWindowSizeInPixels(window, &curr_screen_width, &curr_screen_height);

	SDL_FRect bg_rect;
	bg_rect.x = 0;
	bg_rect.y = 0;
    bg_rect.w = (float)curr_screen_width;
    bg_rect.h = (float)curr_screen_height;
	SDL_RenderTexture(renderer, bg_texture, NULL, &bg_rect);
	SDL_DestroyTexture(bg_texture);

	return SDL_APP_CONTINUE;
}

void plot_title(SDL_Renderer *renderer){  
    title_prop.title_rect.x = (float)(curr_screen_width / 2 - (int)title_prop.title_rect.w / 2);
    title_prop.title_rect.y = (float)(curr_screen_height / 10);

    SDL_RenderTexture(renderer, title_prop.title_img, NULL, &title_prop.title_rect);
}

void plot_description(SDL_Renderer *renderer){
    desc_prop.desc_rect.x = 1.6f * description_offset + padding;
    desc_prop.desc_rect.y = title_offset + padding;

    SDL_RenderTexture(renderer, desc_prop.desc_img, NULL, &desc_prop.desc_rect);
}

void plot_list_item_details(SDL_Renderer *renderer, list_item *item) {        
    SDL_Surface *name_surf = TTF_RenderText_Blended_Wrapped(desc_font, item->name, 0, TEXT_COLOR, (curr_screen_width / 5) + 20);
    
    char age_buffer[256];
    SDL_snprintf(age_buffer, sizeof(age_buffer), "Leeftijd: %s jaar", item->age);
    SDL_Surface *age_surf = TTF_RenderText_Blended_Wrapped(desc_font, age_buffer, 0, TEXT_COLOR, (curr_screen_width / 5));
        
    float total_height = (float)name_surf->h + (float)age_surf->h + text_spacing;    float available_height = item_prop.item_rect.h - (2 * padding);
    float start_y = item_prop.item_rect.y + padding + (available_height - total_height) / 2;
    
    if (name_surf) {
        SDL_Texture *name_tex = SDL_CreateTextureFromSurface(renderer, name_surf);
        if (name_tex) {
            SDL_FRect name_rect;
            name_rect.w = (float)name_surf->w;
            name_rect.h = (float)name_surf->h;
            name_rect.x = item_prop.item_rect.x + (item_prop.item_rect.w - name_rect.w) / 2;
            name_rect.y = start_y;
            SDL_RenderTexture(renderer, name_tex, NULL, &name_rect);
            SDL_DestroyTexture(name_tex);
        }
        SDL_DestroySurface(name_surf);
    }
    
    if (age_surf) {
        SDL_Texture *age_tex = SDL_CreateTextureFromSurface(renderer, age_surf);
        if (age_tex) {
            SDL_FRect age_rect;
            age_rect.w = (float)age_surf->w;
            age_rect.h = (float)age_surf->h;
            age_rect.x = item_prop.item_rect.x + (item_prop.item_rect.w - age_rect.w) / 2;
            age_rect.y = start_y + (float)age_surf->h + text_spacing;
            SDL_RenderTexture(renderer, age_tex, NULL, &age_rect);
            SDL_DestroyTexture(age_tex);
        }
        SDL_DestroySurface(age_surf);
    }
}

SDL_AppResult plot_list_item(SDL_Renderer *renderer){
    static SDL_Texture *card_texture = NULL;
	SDL_Surface *card_surface = NULL;
	char *card_path = NULL;

	SDL_asprintf(&card_path, "%ssrc/bg.bmp", SDL_GetBasePath());

 	card_surface = SDL_LoadBMP(card_path);
	if (!card_surface) {
		SDL_free(card_path);
		SDL_Log("Couldn't load bitmap: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	SDL_free(card_path);

	card_texture = SDL_CreateTextureFromSurface(renderer, card_surface);
    SDL_DestroySurface(card_surface);
  	if (!card_texture) {
  		SDL_Log("Couldn't create static texture: %s", SDL_GetError());
  		return SDL_APP_FAILURE;
  	}
    
    for (int i = 0; i < item_count; i++){
        item_prop.item_rect.w = items[i].pos.w;
        item_prop.item_rect.h = items[i].pos.h;
        item_prop.item_rect.x = items[i].pos.x;
        item_prop.item_rect.y = items[i].pos.y;
        
        if (card_texture) {
            SDL_RenderTexture(renderer, card_texture, NULL, &item_prop.item_rect);
        }
        
        plot_list_item_details(renderer, &items[i]);
    }

    return SDL_APP_SUCCESS;
}

void plot_list(SDL_Renderer *renderer){
    title_offset = title_prop.title_rect.y + title_prop.title_rect.h + padding;
    description_offset = (float)(curr_screen_width / 15) + padding;    

    item_list_rect.w = (float)curr_screen_width - 1.25f * (2 * description_offset + 2 * title_offset);
    item_list_rect.h = (float)curr_screen_height - 2 * title_offset;
    item_list_rect.x = 2 * description_offset + 2 * title_offset;
    item_list_rect.y = title_offset;
    
    plot_list_item(renderer);
}

void plot_controls(SDL_Renderer *renderer, int curr_pos) {   
    float control_panel_x = 1.6f * description_offset;
    float control_panel_y = (float)curr_screen_height - 150.0f;    
    float control_width = 250;
    float line_height = 20;
    float current_y = control_panel_y;
    
    const char *controls[10];
    int control_count = 0;
    
    if (curr_pos == HALL) {
        controls[control_count++] = "ESC - Sluiten";
        controls[control_count++] = "KLIK - Selecteer object";
    } else if (curr_pos) {
        controls[control_count++] = "ESC - Terug naar hal";
        controls[control_count++] = "Rechts Links pijl - Draai X-as";
        controls[control_count++] = "Omhoog Omlaag pijl - Draai Y-as";
        controls[control_count++] = "R - Auto rotatie";
        controls[control_count++] = "Q - Reset rotatie";
    }
    
    float bg_height = ((float)control_count * line_height) + (padding * 2.0f);
    
    static SDL_Texture *control_bg_texture = NULL;
    SDL_Surface *control_bg_surface = NULL;
    char *bg_path = NULL;

    SDL_asprintf(&bg_path, "%ssrc/bg.bmp", SDL_GetBasePath());
    control_bg_surface = SDL_LoadBMP(bg_path);
    
    if (!control_bg_surface) {
        SDL_free(bg_path);
        SDL_Log("Couldn't load bitmap: %s", SDL_GetError());
    } else {
        SDL_free(bg_path);
        
        control_bg_texture = SDL_CreateTextureFromSurface(renderer, control_bg_surface);
        SDL_DestroySurface(control_bg_surface);
        
        if (!control_bg_texture) {
            SDL_Log("Couldn't create texture: %s", SDL_GetError());
        } else {
            SDL_FRect control_bg = {
                control_panel_x - padding,
                control_panel_y - padding,
                control_width + (padding * 2),
                bg_height
            };
            SDL_RenderTexture(renderer, control_bg_texture, NULL, &control_bg);
            SDL_DestroyTexture(control_bg_texture);
        }
    }
    
    for (int i = 0; i < control_count; i++) {
        SDL_Surface *control_surf = TTF_RenderText_Blended(desc_font, controls[i], 0, TEXT_COLOR);
        if (control_surf) {
            SDL_Texture *control_tex = SDL_CreateTextureFromSurface(renderer, control_surf);
            if (control_tex) {
                SDL_FRect control_rect = {
                    control_panel_x + 2 * padding,
                    current_y,
                    (float)control_surf->w,
                    (float)control_surf->h
                };
                SDL_RenderTexture(renderer, control_tex, NULL, &control_rect);
                SDL_DestroyTexture(control_tex);
            }
            SDL_DestroySurface(control_surf);
        }
        current_y += line_height;
    }
}

void calculate_item_positions(void) {    
    int cols = 2;
    float item_width = item_list_rect.w / (float)cols;
    float item_height = item_list_rect.h / 4;
    float gap_x = 5;
    float gap_y = 5;
    
    for (int i = 0; i < item_count; i++) {
        int col = i % cols;
        int row = i / cols;
        
        items[i].pos.w = item_width - gap_x;
        items[i].pos.h = item_height - gap_y;
        items[i].pos.x = item_list_rect.x + ((float)col * item_width) + gap_x / 2.0f;
        items[i].pos.y = item_list_rect.y + ((float)row * item_height) + gap_y / 2.0f;    }
}

void plot_text(SDL_Window *window, SDL_Renderer *renderer){
    SDL_GetWindowSizeInPixels(window, &curr_screen_width, &curr_screen_height);
    
    plot_title(renderer);
    plot_description(renderer);

    calculate_item_positions();
}
