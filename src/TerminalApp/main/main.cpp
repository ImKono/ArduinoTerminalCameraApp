#include <iostream>
#include "../include/MainWindow.h"
#include "../SerialInterface/SerialTerminal.h"
#include "../interface/CustomWindow.h"

#define WIN32_LEAN_AND_MEAN

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << error << " - " << description;
}

int main(){

    MainWindow mainWindow;
    
    if (!SerialTerminal::openSerialPort("COM4")) {
        return 1;
    }

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

   mainWindow.Init();
    //Main loop
    while (!glfwWindowShouldClose(window))
    {
        mainWindow.Update();
        mainWindow.NewFrame();

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        CustomWindow::window();

        //Terminal
        SerialTerminal::readSerialData();

        mainWindow.Render();
    }

    mainWindow.Close();

    return 0;
}
