#include "../../museum-object.h"

vector_3D cube_vertices_3d[24] = {
    /* Front face (z = -0.5) */
    {-0.5f, -0.5f, -0.5f},  /* 0 */
    { 0.5f, -0.5f, -0.5f},  /* 1 */
    { 0.5f,  0.5f, -0.5f},  /* 2 */
    {-0.5f,  0.5f, -0.5f},  /* 3 */
    
    /* Back face (z = 0.5) */
    { 0.5f, -0.5f,  0.5f},  /* 4 */
    {-0.5f, -0.5f,  0.5f},  /* 5 */
    {-0.5f,  0.5f,  0.5f},  /* 6 */
    { 0.5f,  0.5f,  0.5f},  /* 7 */
    
    /* Left face (x = -0.5) */
    {-0.5f, -0.5f,  0.5f},  /* 8 */
    {-0.5f, -0.5f, -0.5f},  /* 9 */
    {-0.5f,  0.5f, -0.5f},  /* 10 */
    {-0.5f,  0.5f,  0.5f},  /* 11 */
    
    /* Right face (x = 0.5) */
    { 0.5f, -0.5f, -0.5f},  /* 12 */
    { 0.5f, -0.5f,  0.5f},  /* 13 */
    { 0.5f,  0.5f,  0.5f},  /* 14 */
    { 0.5f,  0.5f, -0.5f},  /* 15 */
    
    /* Top face (y = 0.5) */
    {-0.5f,  0.5f, -0.5f},  /* 16 */
    { 0.5f,  0.5f, -0.5f},  /* 17 */
    { 0.5f,  0.5f,  0.5f},  /* 18 */
    {-0.5f,  0.5f,  0.5f},  /* 19 */
    
    /* Bottom face (y = -0.5) */
    {-0.5f, -0.5f,  0.5f},  /* 20 */
    { 0.5f, -0.5f,  0.5f},  /* 21 */
    { 0.5f, -0.5f, -0.5f},  /* 22 */
    {-0.5f, -0.5f, -0.5f},  /* 23 */
};

static SDL_Vertex cube_vertices[24] = {
    /* Front face */
    { .position = {-0.5f, -0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.0f, 0.0f} },  /* 0 */
    { .position = { 0.5f, -0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {1.0f, 0.0f} },  /* 1 */
    { .position = { 0.5f,  0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {1.0f, 1.0f} },  /* 2 */
    { .position = {-0.5f,  0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.0f, 1.0f} },  /* 3 */
    
    /* Back face */
    { .position = { 0.5f, -0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.0f, 0.0f} },  /* 4 */
    { .position = {-0.5f, -0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {1.0f, 0.0f} },  /* 5 */
    { .position = {-0.5f,  0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {1.0f, 1.0f} },  /* 6 */
    { .position = { 0.5f,  0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.0f, 1.0f} },  /* 7 */
    
    /* Left face */
    { .position = {-0.5f, -0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.0f, 0.0f} },  /* 8 */
    { .position = {-0.5f, -0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {1.0f, 0.0f} },  /* 9 */
    { .position = {-0.5f,  0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {1.0f, 1.0f} },  /* 10 */
    { .position = {-0.5f,  0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.0f, 1.0f} },  /* 11 */
    
    /* Right face */
    { .position = { 0.5f, -0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.0f, 0.0f} },  /* 12 */
    { .position = { 0.5f, -0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {1.0f, 0.0f} },  /* 13 */
    { .position = { 0.5f,  0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {1.0f, 1.0f} },  /* 14 */
    { .position = { 0.5f,  0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.0f, 1.0f} },  /* 15 */
    
    /* Top face */
    { .position = {-0.5f,  0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.2f, 0.3f} },  /* 16 */
    { .position = { 0.5f,  0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.2f, 0.3f} },  /* 17 */
    { .position = { 0.5f,  0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.2f, 0.3f} },  /* 18 */
    { .position = {-0.5f,  0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.2f, 0.3f} },  /* 19 */

    /* Bottom face */
    { .position = {-0.5f, -0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.2f, 0.3f} },  /* 20 */
    { .position = { 0.5f, -0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.2f, 0.3f} },  /* 21 */
    { .position = { 0.5f, -0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.2f, 0.3f} },  /* 22 */
    { .position = {-0.5f, -0.5f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.2f, 0.3f} },  /* 23 */
};

static int cube_indices[36] = {
    /* Sets of 3 for drawing triangles */
    /* Front face */
    0, 1, 2,
    0, 2, 3,
    
    /* Back face */
    4, 5, 6,
    4, 6, 7,
    
    /* Left face */
    8, 9, 10,
    8, 10, 11,
    
    /* Right face */
    12, 13, 14,
    12, 14, 15,
    
    /* Top face */
    16, 17, 18,
    16, 18, 19,
    
    /* Bottom face */
    20, 21, 22,
    20, 22, 23,
};

selected_object mecca_object = {
    .name = "kaaba",
    .vertices = cube_vertices,
    .vertices_3d = cube_vertices_3d, 
    .vertex_count = 24,
    .indices = cube_indices,
    .index_count = 36,
    .pos = {
        .position = {0.0f, 0.0f, 0.0f},
        .rotation = {0.0f, 0.0f, 0.0f},
        .scale = {1.0f, 1.0f, 1.0f}
    }
};
