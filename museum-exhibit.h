#ifndef MUSEUM_EXHIBIT_H
#define MUSEUM_EXHIBIT_H

SDL_AppResult init_object_texture(SDL_Renderer *renderer, selected_object *selected_obj);
void plot_object(SDL_Window *window, SDL_Renderer *renderer, selected_object *selected_obj);
void destroy_object_texture(void); 

#endif
