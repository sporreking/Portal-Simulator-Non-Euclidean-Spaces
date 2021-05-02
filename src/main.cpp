#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/vec3.hpp>

#include "buttons.h"
#include "config.h"
#include "input.h"
#include "registries.h"
#include "time.h"

int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Load GLAD */
    gladLoadGL();

    /* GL Config */
    glEnable(GL_DEPTH_TEST);

    /* Set clear color with GLM */
    glm::vec3 clearColor = BACKGROUND_COLOR;
    glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0);

    /* Register window callbacks */
    glfwSetKeyCallback(window, Input::keyCallback);
    glfwSetMouseButtonCallback(window, Input::mouseButtonCallback);
    glfwSetCursorPosCallback(window, Input::mousePosCallback);

    /* Initialize input */
    Input::init(window);

    /* Initialize registries */
    REG::init();

    /* Initialize Time */
    Time::init();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Update Time */
        Time::update();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Update input states */
        Input::update();

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}