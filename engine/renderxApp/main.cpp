#include "renderxApp.h"
#include <Windows.h>

int main()
{
	auto app = engine::app::RenderXApp::getInstance();
	app->init();
	app->run();

	return 0;
}

/*

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void cursor_position_callback(GLFWwindow* window, double x, double y);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

int cp_x;
int cp_y;
int offset_cpx;
int offset_cpy;
int w_posx;
int w_posy;
int buttonEvent;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_DECORATED, 0);
    GLFWwindow* window = glfwCreateWindow(640, 480, "Undecorated Resizable", 0, 0);

    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwMakeContextCurrent(window);


    while (!glfwWindowShouldClose(window)) {
        if (buttonEvent == 1) {
            glfwGetWindowPos(window, &w_posx, &w_posy);

            glfwSetWindowPos(window, w_posx + offset_cpx, w_posy + offset_cpy);
            offset_cpx = 0;
            offset_cpy = 0;
            cp_x += offset_cpx;
            cp_y += offset_cpy;

        }
       

        glfwSwapBuffers(window);

        glfwWaitEvents();
    }

    return 0;
}

void cursor_position_callback(GLFWwindow* window, double x, double y) {
    if (buttonEvent == 1) {
        offset_cpx = x - cp_x;
        offset_cpy = y - cp_y;
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        buttonEvent = 1;
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        cp_x = floor(x);
        cp_y = floor(y);
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        buttonEvent = 0;
        cp_x = 0;
        cp_y = 0;
    }
}
*/