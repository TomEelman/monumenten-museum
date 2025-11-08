#include "main.h"
#include <math.h>

static SDL_Texture *obj_texture = NULL;
static char *current_texture_name = NULL;

SDL_AppResult init_object_texture(SDL_Renderer *renderer, selected_object *selected_obj){
    selected_object *obj = (selected_object *)selected_obj;
    if (obj_texture && current_texture_name && SDL_strcmp(current_texture_name, obj->name) == 0) {
        return SDL_APP_SUCCESS;
    }
    
    if (obj_texture) {
        SDL_DestroyTexture(obj_texture);
        obj_texture = NULL;
    }
    
    if (current_texture_name) {
        SDL_free(current_texture_name);
        current_texture_name = NULL;
    }
    
    char *obj_bmp_path = NULL;
    SDL_asprintf(&obj_bmp_path, "%ssrc/obj_faces/%s.bmp", SDL_GetBasePath(), obj->name);
    
    SDL_Surface *bmp_surface = SDL_LoadBMP(obj_bmp_path);
    if (!bmp_surface) {
        SDL_Log("Couldn't load bitmap: %s", SDL_GetError());
        SDL_free(obj_bmp_path);
        return SDL_APP_FAILURE;
    }
    
    obj_texture = SDL_CreateTextureFromSurface(renderer, bmp_surface);
    SDL_DestroySurface(bmp_surface);
    SDL_free(obj_bmp_path);
    
    if (!obj_texture) {
        SDL_Log("Couldn't create texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    current_texture_name = SDL_strdup(obj->name);
    
    return SDL_APP_SUCCESS;
}

void destroy_object_texture(void) {
    if (obj_texture) {
        SDL_DestroyTexture(obj_texture);
        obj_texture = NULL;
    }
    if (current_texture_name) {
        SDL_free(current_texture_name);
        current_texture_name = NULL;
    }
}

void plot_object(SDL_Window *window, SDL_Renderer *renderer, selected_object *selected_obj){
    selected_object *obj = (selected_object *)selected_obj;

    SDL_Vertex *screen_vertices = generate_geometery(window, obj);
    vector_3D camera_pos = {0.0f, 0.0f, -2.0f};    

    matrix3x3 rotation_pitch = rotation_matrix_pitch(obj->pos.rotation.x);
    matrix3x3 rotation_yaw = rotation_matrix_yaw(obj->pos.rotation.y);
    
    // Walk through indices 3 to extract the traingles
    for (int i = 0; i < obj->index_count; i += 3) {
        int corner_1 = obj->indices[i];
        int corner_2 = obj->indices[i + 1];
        int corner_3 = obj->indices[i + 2];
        
        vector_3D vector_1 = obj->vertices_3d[corner_1];
        vector_3D vector_2 = obj->vertices_3d[corner_2];
        vector_3D vector_3 = obj->vertices_3d[corner_3];
        
        // Apply rotation if added
        vector_1 = rotate_vertex(vector_1, rotation_pitch);
        vector_1 = rotate_vertex(vector_1, rotation_yaw);
        vector_2 = rotate_vertex(vector_2, rotation_pitch);
        vector_2 = rotate_vertex(vector_2, rotation_yaw);
        vector_3 = rotate_vertex(vector_3, rotation_pitch);
        vector_3 = rotate_vertex(vector_3, rotation_yaw);
        
        // Check if this face should not be displayed
        if (!triangle_in_camera_view(vector_1, vector_2, vector_3, camera_pos)) {
            int triangle_indices[3] = {0, 1, 2};
            SDL_Vertex valid_triangle[3] = {
                screen_vertices[corner_1],
                screen_vertices[corner_2],
                screen_vertices[corner_3]
            };
            
            SDL_RenderGeometry(renderer, 
                obj_texture, 
                valid_triangle, 
                3,
                triangle_indices, 
                3
            );
        }
    }
    
    SDL_free(screen_vertices);
}
