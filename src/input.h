#pragma once

#include <GLFW/glfw3.h>

#include <algorithm>
#include <iostream>
#include <map>

typedef unsigned int Button;

enum ButtonState {
    UP = 0,
    DOWN = 1,
    PRESSED = 2,
    RELEASED = 3
};

typedef unsigned int Axis;

struct AxisRef {
    Axis axis;
    double sensitivity;
    union {
        bool positive;
        bool invert;
    };
};

struct AxisState {
    double limit;
    double value;
};

void bindInput();

class Input {
   public:
    // Should be called once before class usage
    static void init(GLFWwindow *window);

    // Should be called at the end of every frame before event processing
    static void update();

    /* -- Callbacks -- */

    static void keyCallback(GLFWwindow *, int, int, int, int);
    static void mouseButtonCallback(GLFWwindow *, int, int, int);
    static void mousePosCallback(GLFWwindow *, double, double);

    /* -- State Checks -- */

    static inline ButtonState getState(Button b) { return _buttonStates[b]; }
    static inline bool up(Button b) { return _buttonStates.count(b) ? _buttonStates[b] == ButtonState::UP || _buttonStates[b] == ButtonState::RELEASED : true; }
    static inline bool down(Button b) { return _buttonStates.count(b) ? _buttonStates[b] == ButtonState::DOWN || _buttonStates[b] == ButtonState::PRESSED : false; }
    static inline bool pressed(Button b) { return _buttonStates.count(b) ? _buttonStates[b] == ButtonState::PRESSED : false; }
    static inline bool released(Button b) { return _buttonStates.count(b) ? _buttonStates[b] == ButtonState::RELEASED : false; }
    static double axis(Axis a);

    /* -- Binders -- */

    // Bind key to button
    static inline void bindKeyToButton(Button b, int key) { _keyButtonMap[key] = b; }

    // Bind mouse button
    static inline void bindMouseToButton(Button b, int mouseButton) { _mouseButtonMap[mouseButton] = b; }

    // Initialize an axis (use 'limit <= 0' for no limit)
    static inline void initAxis(Axis a, double limit) { _axisStates[a] = {limit, 0}; }

    // Bind keys to an axis (axis must be initialized first)
    static void bindKeysToAxis(Axis a, int pos, int neg, double sensitivity = 1.0);

    // Bind mouse buttons to axis (axis must be initialized first)
    static void bindMouseButtonsToAxis(Axis a, int pos, int neg, double sensitivity = 1.0);

    // Bind mouse X movement to axis (axis must be initialized first)
    static void bindMouseXToAxis(Axis a, double sensitivity, bool invert);

    // Bind mouse Y movement to axis (axis must be initialized first)
    static void bindMouseYToAxis(Axis a, double sensitivity, bool invert);

    /* -- Misc -- */
    static inline void grabMouse(bool grab) { glfwSetInputMode(_window, GLFW_CURSOR, grab ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL); }
    static inline bool mouseGrabbed() { return glfwGetInputMode(_window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED; }

   private:
    // Core
    static GLFWwindow *_window;

    // Mouse movement
    static double _mouseX, _mouseY;
    static double _mouseDX, _mouseDY;

    // Button mappings
    static std::map<int, Button> _keyButtonMap;
    static std::map<int, Button> _mouseButtonMap;
    static std::map<Button, ButtonState> _buttonStates;

    // Axis mappings
    static std::map<int, AxisRef> _keyAxisMap;
    static std::map<int, AxisRef> _mouseAxisMap;
    static std::map<Axis, AxisState> _axisStates;

    // Mouse movement axis mappings
    static std::map<Axis, AxisRef> _mouseMoveXMap;
    static std::map<Axis, AxisRef> _mouseMoveYMap;

    // Throws exception if specified axis is uninitialized
    static void _axisBindCheck(Axis a);

    // Calculates the axis value of the specified axis
    static double _axisValue(Axis a);
};