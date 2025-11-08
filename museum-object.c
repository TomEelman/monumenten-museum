#include "main.h"
#include <math.h>

float fov = 200.0f;
float z_offset = 1.5f;

// https://en.wikipedia.org/wiki/Rotation_matrix => onder General 3D rotations
// https://msl.cs.uiuc.edu/planning/node101.html#fig:yawpitchroll
matrix3x3 rotation_matrix_yaw(float angle) {
    matrix3x3 result = {0};
    float cos_a = cosf(angle);
    float sin_a = sinf(angle);
    
    result.m[0][0] = 1;  result.m[0][1] = 0;      result.m[0][2] = 0;
    result.m[1][0] = 0;  result.m[1][1] = cos_a;  result.m[1][2] = -sin_a;
    result.m[2][0] = 0;  result.m[2][1] = sin_a;  result.m[2][2] = cos_a;
    
    return result;
}

matrix3x3 rotation_matrix_pitch(float angle) {
    matrix3x3 result = {0};
    float cos_a = cosf(angle);
    float sin_a = sinf(angle);
    
    result.m[0][0] = cos_a;    result.m[0][1] = 0;      result.m[0][2] = sin_a;
    result.m[1][0] = 0;        result.m[1][1] = 1;      result.m[1][2] = 0;
    result.m[2][0] = -sin_a;   result.m[2][1] = 0;      result.m[2][2] = cos_a;
    
    return result;
}

vector_3D rotate_vertex(vector_3D v, matrix3x3 rot) {
    return (vector_3D){
        rot.m[0][0] * v.x + rot.m[0][1] * v.y + rot.m[0][2] * v.z,
        rot.m[1][0] * v.x + rot.m[1][1] * v.y + rot.m[1][2] * v.z,
        rot.m[2][0] * v.x + rot.m[2][1] * v.y + rot.m[2][2] * v.z
    };
}

bool triangle_in_camera_view(vector_3D vector_1, vector_3D vector_2, vector_3D vector_3, vector_3D camera_pos) {
    vector_3D edge_1 = {vector_2.x - vector_1.x, vector_2.y - vector_1.y, vector_2.z - vector_1.z};
    vector_3D edge_2 = {vector_3.x - vector_1.x, vector_3.y - vector_1.y, vector_3.z - vector_1.z};
    
    vector_3D triangle_normal_vector = {
        edge_1.y * edge_2.z - edge_1.z * edge_2.y,
        edge_1.z * edge_2.x - edge_1.x * edge_2.z,
        edge_1.x * edge_2.y - edge_1.y * edge_2.x
    };
    
    vector_3D view_vector = {
        camera_pos.x - vector_1.x,
        camera_pos.y - vector_1.y,
        camera_pos.z - vector_1.z
    };
    float dot_product = triangle_normal_vector.x * view_vector.x + triangle_normal_vector.y * view_vector.y + triangle_normal_vector.z * view_vector.z;
    
    return dot_product > 0.0f;
}

SDL_Vertex* generate_geometery(SDL_Window *window, selected_object *selected_obj) {
    selected_object *obj = (selected_object *)selected_obj;
    
    matrix3x3 rotation_pitch = rotation_matrix_pitch(obj->pos.rotation.x);
    matrix3x3 rotation_yaw = rotation_matrix_yaw(obj->pos.rotation.y);
    
    SDL_Vertex *screen_vertices = SDL_malloc((size_t)obj->vertex_count * sizeof(SDL_Vertex));

    // Positioning of object
    SDL_GetWindowSize(window, &curr_screen_width, &curr_screen_height);
    float title_offset = (float)(curr_screen_height / 8);
    float description_offset = (float)(curr_screen_width / 4);
    float window_center_x = description_offset + (((float)curr_screen_width - description_offset) / 2.0f);
    float window_center_y = title_offset + (((float)curr_screen_height - title_offset) / 2.0f);

    for (int i = 0; i < obj->vertex_count; i++) {
        // Determining rotation of object
        vector_3D original = obj->vertices_3d[i];
        vector_3D rotated = rotate_vertex(original, rotation_pitch);
        rotated = rotate_vertex(rotated, rotation_yaw);
        
        float scale = fov / (rotated.z + z_offset);
        float screen_x = window_center_x + (rotated.x * scale);
        float screen_y = window_center_y + (rotated.y * scale);
        
        screen_vertices[i] = obj->vertices[i];
        screen_vertices[i].position.x = screen_x;
        screen_vertices[i].position.y = screen_y;
    }
    
    return screen_vertices;
}
