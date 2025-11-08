#include "../../museum-object.h"

vector_3D pyramid_vertices_3d[18] = {
    {-0.5f,  0.5f,  0.5f},  /* 0 */
    { 0.5f,  0.5f,  0.5f},  /* 1 */
    { 0.5f,  0.5f, -0.5f},  /* 2 */
    {-0.5f,  0.5f, -0.5f},  /* 3 */
    
    /* Front face - triangle */
    {-0.5f,  0.5f,  0.5f},  /* 4 */
    { 0.5f,  0.5f,  0.5f},  /* 5 */
    { 0.0f, -0.5f,  0.0f},  /* 6 */
    
    /* Right face - triangle */
    { 0.5f,  0.5f,  0.5f},  /* 7 */
    { 0.5f,  0.5f, -0.5f},  /* 8 */
    { 0.0f, -0.5f,  0.0f},  /* 9 */
    
    /* Back face - triangle */
    { 0.5f,  0.5f, -0.5f},  /* 10 */
    {-0.5f,  0.5f, -0.5f},  /* 11 */
    { 0.0f, -0.5f,  0.0f},  /* 12 */
    
    /* Left face - triangle */
    {-0.5f,  0.5f, -0.5f},  /* 13 */
    {-0.5f,  0.5f,  0.5f},  /* 14 */
    { 0.0f, -0.5f,  0.0f},  /* 15 */
};

static SDL_Vertex pyramid_vertices[18] = {
    /* Base */
    { .position = {0.0f, 0.0f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.2f, 0.3f} },  /* 0 */
    { .position = {0.0f, 0.0f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.2f, 0.3f} },  /* 1 */
    { .position = {0.0f, 0.0f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.2f, 0.3f} },  /* 2 */
    { .position = {0.0f, 0.0f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.2f, 0.3f} },  /* 3 */
    
    /* Front face */
    { .position = {0.0f, 0.0f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.0f, 1.0f} },  /* 4 */
    { .position = {0.0f, 0.0f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {1.0f, 1.0f} },  /* 5 */
    { .position = {0.0f, 0.0f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.5f, 0.0f} },  /* 6 */
    
    /* Right face */
    { .position = {0.0f, 0.0f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.0f, 1.0f} },  /* 7 */
    { .position = {0.0f, 0.0f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {1.0f, 1.0f} },  /* 8 */
    { .position = {0.0f, 0.0f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.5f, 0.0f} },  /* 9 */
    
    /* Back face */
    { .position = {0.0f, 0.0f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.0f, 1.0f} },  /* 10 */
    { .position = {0.0f, 0.0f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {1.0f, 1.0f} },  /* 11 */
    { .position = {0.0f, 0.0f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.5f, 0.0f} },  /* 12 */
    
    /* Left face */
    { .position = {0.0f, 0.0f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.0f, 1.0f} },  /* 13 */
    { .position = {0.0f, 0.0f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {1.0f, 1.0f} },  /* 14 */
    { .position = {0.0f, 0.0f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}, .tex_coord = {0.5f, 0.0f} },  /* 15 */
};

static int pyramid_indices[18] = {
    /* Sets of 3 for drawing triangles */
    0, 2, 1,
    0, 3, 2,
    
    /* Front face */
    4, 5, 6,
    
    /* Right face */
    7, 8, 9,
    
    /* Back face */
    10, 11, 12,
    
    /* Left face */
    13, 14, 15,
};

selected_object pyramide_object = {
    .name = "pyramide",
    .vertices = pyramid_vertices,
    .vertices_3d = pyramid_vertices_3d,
    .vertex_count = 18,
    .indices = pyramid_indices,
    .index_count = 18,
    .pos = {
        .position = {0.0f, 0.0f, 0.0f},
        .rotation = {0.0f, 0.0f, 0.0f},
        .scale = {1.0f, 1.0f, 1.0f}
    }
};
