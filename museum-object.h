#ifndef MUSEUM_OBJECT_H
#define MUSEUM_OBJECT_H

#include <SDL3/SDL.h>         
#include <SDL3/SDL_render.h>   
#include <math.h>         

typedef struct { float x, y, z; } vector_3D;
typedef struct { float x, y;   } vector_2D;

typedef struct {
    float m[3][3];
} matrix3x3;

typedef struct {
    vector_3D position;
    vector_3D rotation;
    vector_3D scale;
} obj_position;

typedef struct {
    char *name;
    SDL_Vertex *vertices;
    int vertex_count;
    vector_3D *vertices_3d;
    int *indices;
    int index_count;
    obj_position pos;
} selected_object;

extern selected_object mecca_object;

matrix3x3 rotation_matrix_yaw(float angle);
matrix3x3 rotation_matrix_pitch(float angle);
matrix3x3 rotation_matrix_roll(float angle);
SDL_Vertex *generate_geometery(SDL_Window *window, selected_object *selected_obj);
bool triangle_in_camera_view(vector_3D vector_1, vector_3D vector_2, vector_3D vector_3, vector_3D camera_pos);
vector_3D rotate_vertex(vector_3D v, matrix3x3 rot);

#endif /* MUSEUM_OBJECT_H */
