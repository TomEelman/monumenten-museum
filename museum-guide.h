#ifndef MUSEUM_GUIDE_H
#define MUSEUM_GUIDE_H

typedef struct {
    int       id;
    char     *name;
    char     *age;
    SDL_FRect pos;
} list_item;

#define MAX_ITEMS 100
extern list_item items[MAX_ITEMS];
extern int item_count;

bool init_font(SDL_Window *window);
bool create_title(SDL_Renderer *renderer, const char *title);
bool create_description(SDL_Renderer *renderer, const char *description);
void create_list_item(int id, char *name, char * age);
void fill_item_list(void);
void destroy_font(void);


#endif
