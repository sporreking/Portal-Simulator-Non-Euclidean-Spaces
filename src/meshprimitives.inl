// Quad
GLfloat quadPos[12] = {-.5, -.5, .0, -.5, .5, .0, .5, .5, .0, .5, -.5, .0};
GLfloat quadNorm[12] = {.0, .0, 1.0, .0, .0, 1.0, .0, .0, 1.0, .0, .0, 1.0};
GLfloat quadTex[8] = {0, 0, 0, 1, 1, 1, 1, 0};
GLuint quadInd[6] = {0, 1, 2, 2, 3, 0};

// Cube
GLfloat cubePos[24 * 3] = {
    -.5, -.5, .5,  // Front: bottom left
    -.5, .5, .5,   // Front: top left
    .5, .5, .5,    // Front: top right
    .5, -.5, .5,   // Front: bottom right

    .5, -.5, .5,   // Right: bottom left
    .5, .5, .5,    // Right: top left
    .5, .5, -.5,   // Right: top right
    .5, -.5, -.5,  // Right: bottom right

    .5, -.5, -.5,   // Back: bottom left
    .5, .5, -.5,    // Back: top left
    -.5, .5, -.5,   // Back: top right
    -.5, -.5, -.5,  // Back: bottom right

    -.5, -.5, -.5,  // Left: bottom left
    -.5, .5, -.5,   // Left: top left
    -.5, .5, .5,    // Left: top right
    -.5, -.5, .5,   // Left: bottom right

    -.5, -.5, -.5,  // Bottom: bottom left
    -.5, -.5, .5,   // Bottom: top left
    .5, -.5, .5,    // Bottom: top right
    .5, -.5, -.5,   // Bottom: bottom right

    -.5, .5, .5,   // Top: bottom left
    -.5, .5, -.5,  // Top: top left
    .5, .5, -.5,   // Top: top right
    .5, .5, .5     // Top: bottom right
};

GLfloat cubeNorm[24 * 3] = {
    0, 0, 1,  // Front: bottom left
    0, 0, 1,  // Front: top left
    0, 0, 1,  // Front: top right
    0, 0, 1,  // Front: bottom right

    1, 0, 0,  // Right: bottom left
    1, 0, 0,  // Right: top left
    1, 0, 0,  // Right: top right
    1, 0, 0,  // Right: bottom right

    0, 0, -1,  // Back: bottom left
    0, 0, -1,  // Back: top left
    0, 0, -1,  // Back: top right
    0, 0, -1,  // Back: bottom right

    -1, 0, 0,  // Left: bottom left
    -1, 0, 0,  // Left: top left
    -1, 0, 0,  // Left: top right
    -1, 0, 0,  // Left: bottom right

    0, -1, 0,  // Bottom: bottom left
    0, -1, 0,  // Bottom: top left
    0, -1, 0,  // Bottom: top right
    0, -1, 0,  // Bottom: bottom right

    0, 1, 0,  // Top: bottom left
    0, 1, 0,  // Top: top left
    0, 1, 0,  // Top: top right
    0, 1, 0   // Top: bottom right
};

GLfloat cubeTex[24 * 2] = {
    0, 0,  // Front: bottom left
    0, 1,  // Front: top left
    1, 1,  // Front: top right
    1, 0,  // Front: bottom right

    0, 0,  // Right: bottom left
    0, 1,  // Right: top left
    1, 1,  // Right: top right
    1, 0,  // Right: bottom right

    0, 0,  // Back: bottom left
    0, 1,  // Back: top left
    1, 1,  // Back: top right
    1, 0,  // Back: bottom right

    0, 0,  // Left: bottom left
    0, 1,  // Left: top left
    1, 1,  // Left: top right
    1, 0,  // Left: bottom right

    0, 0,  // Bottom: bottom left
    0, 1,  // Bottom: top left
    1, 1,  // Bottom: top right
    1, 0,  // Bottom: bottom right

    0, 0,  // Top: bottom left
    0, 1,  // Top: top left
    1, 1,  // Top: top right
    1, 0   // Top: bottom right
};

GLuint cubeInd[6 * 6] = {
    0, 1, 2, 0, 2, 3,        // Front
    4, 5, 6, 4, 6, 7,        // Right
    8, 9, 10, 8, 10, 11,     // Back
    12, 13, 14, 12, 14, 15,  // Left
    16, 17, 18, 16, 18, 19,  // Bottom
    20, 21, 22, 20, 22, 23   // Top
};

// Skybox cube
GLfloat skyboxPos[8 * 3] = {
    -1, -1, 1,
    -1, 1, 1,
    1, 1, 1,
    1, -1, 1,
    1, -1, -1,
    1, 1, -1,
    -1, 1, -1,
    -1, -1, -1};

GLuint skyboxInd[6 * 6] = {
    0, 1, 2, 0, 2, 3,  // Front
    4, 5, 6, 4, 6, 7,  // Back
    0, 3, 4, 0, 4, 7,  // Bottom
    1, 6, 5, 1, 5, 2,  // Top
    7, 6, 1, 7, 1, 0,  // Left
    3, 2, 5, 3, 5, 4,  // Right
};