#include "buttons.h"

/* Bind Input */
void bindInput() {
    /* BUTTONS */
    Input::bindKeyToButton(BUTTON_JUMP, GLFW_KEY_SPACE);
    Input::bindMouseToButton(BUTTON_FIRE, GLFW_MOUSE_BUTTON_1);

    /* AXIS */
    Input::initAxis(AXIS_LOOK_VERTICAL, 0);
    Input::bindKeysToAxis(AXIS_LOOK_VERTICAL, GLFW_KEY_I, GLFW_KEY_K, 0.5);
    Input::bindMouseYToAxis(AXIS_LOOK_VERTICAL, 0.1, false);

    Input::initAxis(AXIS_LOOK_HORIZONTAL, 0);
    Input::bindKeysToAxis(AXIS_LOOK_HORIZONTAL, GLFW_KEY_L, GLFW_KEY_J, 0.5);
    Input::bindMouseXToAxis(AXIS_LOOK_HORIZONTAL, 0.1, false);

    Input::initAxis(AXIS_FORWARD, 1.0);
    Input::bindKeysToAxis(AXIS_FORWARD, GLFW_KEY_W, GLFW_KEY_S);

    Input::initAxis(AXIS_STRAFE, 1.0);
    Input::bindKeysToAxis(AXIS_STRAFE, GLFW_KEY_D, GLFW_KEY_A);
}