#ifndef MUSEUM_NAVIGATOR_H
#define MUSEUM_NAVIGATOR_H

enum user_position {
    HALL,
    MECCA,
    PYRAMIDE,
    POSITION_LENGTH
};

enum navigation_codes {
    hall,
    mecca,
    pyramide,
    CODE_LENGTH
};

struct navigation_handler {
    enum user_position   curr_pos;
    enum user_position   next_pos;
    enum navigation_codes next_nav;
};

enum user_position hall_navigate(void *app_state);
enum user_position mecca_navigate(void *app_state);
enum user_position pyramide_navigate(void *app_state);
extern enum user_position (*navigate[])(void *app_state);

#endif /* MUSEUM_NAVIGATOR_H */
