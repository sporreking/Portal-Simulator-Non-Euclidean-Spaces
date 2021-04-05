#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/vec3.hpp>

#include "buttons.h"
#include "input.h"

int main(void) {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Load GLAD */
    gladLoadGL();

    /* Set clear color with GLM */
    glm::vec3 clearColor(1, 0, 1);

    glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0);

    /* Register window callbacks */
    glfwSetKeyCallback(window, Input::keyCallback);
    glfwSetMouseButtonCallback(window, Input::mouseButtonCallback);
    glfwSetCursorPosCallback(window, Input::mousePosCallback);

    /* Initialize input */
    Input::init();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* vv TEMP vv */
        if (Input::pressed(BUTTON_FIRE))
            std::cout << "FIRE!" << std::endl;
        else if (Input::released(BUTTON_FIRE))
            std::cout << "STOP!" << std::endl;
        double a = Input::axis(AXIS_LOOK_VERTICAL);
        if (a != 0)
            std::cout << "Look: " << a << std::endl;
        /* ^^ TEMP ^^ */

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