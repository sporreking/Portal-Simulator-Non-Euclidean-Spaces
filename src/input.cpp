#include "input.h"

void Input::init() {
    bindInput();
}

void Input::update() {
    // Update button states
    for (auto &pair : _buttonStates)
        if (pair.second == ButtonState::PRESSED)
            pair.second = ButtonState::DOWN;
        else if (pair.second == ButtonState::RELEASED)
            pair.second = ButtonState::UP;

    // Reset mouse delta
    _mouseDX = 0;
    _mouseDY = 0;
}

void Input::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Only react to press / release
    if (action == GLFW_REPEAT)
        return;

    // Check if key is bound to a button and register press / release if that's the case
    if (_keyButtonMap.count(key)) {
        ButtonState *state = &_buttonStates[_keyButtonMap[key]];
        switch (*state) {
            case UP:
                *state = (action == GLFW_PRESS ? ButtonState::PRESSED : ButtonState::UP);
                break;
            case DOWN:
                *state = (action == GLFW_PRESS ? ButtonState::DOWN : ButtonState::RELEASED);
                break;
            case PRESSED:
                *state = (action == GLFW_PRESS ? ButtonState::PRESSED : ButtonState::UP);
                break;
            case RELEASED:
                *state = (action == GLFW_PRESS ? ButtonState::DOWN : ButtonState::RELEASED);
                break;
        }
    }

    // Check if key is bound to an axis and update if that's the case
    if (_keyAxisMap.count(key)) {
        AxisRef &ref = _keyAxisMap[key];
        AxisState &state = _axisStates[ref.axis];
        state.value += (ref.positive == (action == GLFW_PRESS)) ? ref.sensitivity : -ref.sensitivity;
    }
}

void Input::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    // Check if mouse button is bound and register press / release if that's the case
    if (_mouseButtonMap.count(button)) {
        ButtonState *state = &_buttonStates[_mouseButtonMap[button]];
        switch (*state) {
            case UP:
                *state = (action == GLFW_PRESS ? ButtonState::PRESSED : ButtonState::UP);
                break;
            case DOWN:
                *state = (action == GLFW_PRESS ? ButtonState::DOWN : ButtonState::RELEASED);
                break;
            case PRESSED:
                *state = (action == GLFW_PRESS ? ButtonState::PRESSED : ButtonState::UP);
                break;
            case RELEASED:
                *state = (action == GLFW_PRESS ? ButtonState::DOWN : ButtonState::RELEASED);
                break;
        }
    }

    // Check if mouse button is bound to an axis and update if that's the case
    if (_mouseAxisMap.count(button)) {
        AxisRef &ref = _mouseAxisMap[button];
        AxisState &state = _axisStates[ref.axis];
        state.value += (ref.positive == (action == GLFW_PRESS)) ? ref.sensitivity : -ref.sensitivity;
    }
}

void Input::mousePosCallback(GLFWwindow *window, double posX, double posY) {
    _mouseDX = posX - _mouseX;
    _mouseDY = posY - _mouseY;
    _mouseX = posX;
    _mouseY = posY;
}

double Input::axis(Axis a) {
    if (_axisStates.count(a)) {
        AxisState &s = _axisStates[a];
        double v = _axisValue(a);
        return s.limit > 0 ? std::min(std::max(v, -s.limit), s.limit) : v;
    }
    return 0;
}

void Input::bindKeysToAxis(Axis a, int pos, int neg, double sensitivity) {
    _axisBindCheck(a);
    _keyAxisMap[pos] = {a, sensitivity, true};
    _keyAxisMap[neg] = {a, sensitivity, false};
}

void Input::bindMouseButtonsToAxis(Axis a, int pos, int neg, double sensitivity) {
    _axisBindCheck(a);
    _mouseAxisMap[pos] = {a, sensitivity, true};
    _mouseAxisMap[neg] = {a, sensitivity, false};
}

void Input::bindMouseXToAxis(Axis a, double sensitivity, bool invert) {
    _axisBindCheck(a);
    _mouseMoveXMap[a] = {a, sensitivity, invert};
}

void Input::bindMouseYToAxis(Axis a, double sensitivity, bool invert) {
    _axisBindCheck(a);
    _mouseMoveYMap[a] = {a, sensitivity, invert};
}

void Input::_axisBindCheck(Axis a) {
    if (!_axisStates.count(a)) {
        std::cerr << "Cannot bind to uninitialized axis." << std::endl;
        throw -1;
    }
}

double Input::_axisValue(Axis a) {
    double v = _axisStates[a].value;
    if (_mouseMoveXMap.count(a))
        v += _mouseDX * _mouseMoveXMap[a].sensitivity * (_mouseMoveXMap[a].invert ? -1 : 1);
    if (_mouseMoveYMap.count(a))
        v += _mouseDY * _mouseMoveYMap[a].sensitivity * (_mouseMoveYMap[a].invert ? -1 : 1);

    return v;
}

double Input::_mouseX = -1, Input::_mouseY = -1;
double Input::_mouseDX = 0, Input::_mouseDY = 0;

std::map<int, Button> Input::_keyButtonMap;
std::map<int, Button> Input::_mouseButtonMap;
std::map<Button, ButtonState> Input::_buttonStates;

std::map<int, AxisRef> Input::_keyAxisMap;
std::map<int, AxisRef> Input::_mouseAxisMap;
std::map<Axis, AxisState> Input::_axisStates;

std::map<Axis, AxisRef> Input::_mouseMoveXMap;
std::map<Axis, AxisRef> Input::_mouseMoveYMap;