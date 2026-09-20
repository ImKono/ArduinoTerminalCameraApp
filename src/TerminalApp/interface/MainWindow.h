#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl2.h>

class MainWindow {
    private:

    public:
        MainWindow() = default;
        ~MainWindow() = default;

        void Init();
        void NewFrame();
        void Update();
        void Render();
        void Close();
};