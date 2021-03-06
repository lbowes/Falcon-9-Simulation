#ifndef F9SIM_INPUT_H_
#define F9SIM_INPUT_H_
#pragma once


#include <glm/vec2.hpp>
#include <stdint.h>


typedef struct GLFWwindow GLFWwindow;


namespace F9Sim {


class Input {
private:
    static const uint16_t s_maxKeys = 512;
    static const uint8_t s_maxButtons = 16;
    static bool s_zeroMouseDelta;
    static bool s_cursorHidden;
    static glm::ivec2 s_mousePos_last;
    static glm::ivec2 s_mousePos;
    static glm::ivec2 s_mouseDelta;
    static GLFWwindow* s_window;
    static bool s_keysDown[s_maxKeys];
    static bool s_keysDown_last[s_maxKeys];
    static bool s_keysPressed[s_maxKeys];
    static bool s_keysReleased[s_maxKeys];
    static bool s_buttonsDown[s_maxButtons];
    static bool s_buttonsPressed[s_maxButtons];
    static bool s_buttonsReleased[s_maxButtons];
    static bool s_buttonsDown_last[s_maxButtons];

public:
    Input(const Input& other) = delete;
    Input(Input& other) = delete;
    void operator=(const Input& other) = delete;
    void operator=(Input& other) = delete;

    static void init(GLFWwindow& window);
    static void update();

    // Callbacks
    static void setCallbacks(GLFWwindow* win);
    static void keyCallback(GLFWwindow* win, int key, int scanCode, int action, int mods);
    static void buttonCallback(GLFWwindow* win, int button, int action, int mods);
    static void mousePosCallback(GLFWwindow* win, double x, double y);

    // Keyboard
    static bool isKeyDown(uint16_t key);
    static bool isKeyUp(uint16_t key);
    static bool isKeyPressed(uint16_t key);
    static bool isKeyReleased(uint16_t key);

    // Mouse
    static bool isMouseButtonDown(uint8_t button);
    static bool isMouseButtonUp(uint8_t button);
    static bool isMouseButtonPressed(uint8_t button);
    static bool isMouseButtonReleased(uint8_t button);
    static bool isCursorHidden();
    static glm::ivec2 getMousePos();
    static glm::ivec2 getMouseDelta();
    static void setCursorVisible(bool visibility);
    static void setCursorPos(glm::ivec2 pos);

private:
    Input() = delete;
    ~Input() = default;
};


} // namespace F9Sim


#endif // F9SIM_INPUT_H_

