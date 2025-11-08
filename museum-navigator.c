#include "main.h"
#include <string.h>

enum user_position hall_navigate(void *app_state){
    AppStateData *state_data = (AppStateData *)app_state;

    destroy_object_texture();

    state_data->nav_handler.curr_pos = HALL;

    state_data->window.title = "Keuzehal";
    state_data->window.desc = "Kies een monument.";
    state_data->current_obj = NULL;

    create_title(renderer, state_data->window.title);
    create_description(renderer, state_data->window.desc);

    fill_item_list();

    return HALL;
}

enum user_position mecca_navigate(void *app_state){
    AppStateData *state_data = (AppStateData *)app_state;

    state_data->nav_handler.curr_pos = MECCA;
    state_data->window.title = "Kaäba";
    state_data->window.desc = "De Kaäba in Mekka is een heilige kubusvormige structuur. "
                              "Elk jaar draaien miljoenen pelgrims eromheen tijdens de hadj. "
                              "Het is simpel, symmetrisch en enorm symbolisch.";
    state_data->current_obj = &mecca_object;
    
    init_object_texture(renderer, &mecca_object);

    create_title(renderer, state_data->window.title);
    create_description(renderer, state_data->window.desc);
    
    return MECCA;
}

enum user_position pyramide_navigate(void *app_state){
    AppStateData *state_data = (AppStateData *)app_state;

    state_data->nav_handler.curr_pos = PYRAMIDE;
    state_data->window.title = "Pyramide van Gizeh";
    state_data->window.desc = "De Grote Pyramide van Gizeh is een van de zeven wereldwonderen. En is volledig met de hand gemaakt";
    state_data->current_obj = &pyramide_object;
    
    init_object_texture(renderer, &pyramide_object); 

    create_title(renderer, state_data->window.title);
    create_description(renderer, state_data->window.desc);
    
    return PYRAMIDE;
}

enum user_position (*navigate[])(void *app_state) = {
    hall_navigate,
    mecca_navigate,
    pyramide_navigate
};
