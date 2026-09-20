#include "../include/MainWindow.h"

namespace CustomWindow {
    void window(){
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);

        ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_MenuBar |
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoSavedSettings;

        ImGui::Begin("Ventana de ejemplo", nullptr, window_flags);
        
        if(ImGui::BeginMenuBar()) {

            if(ImGui::BeginMenu("File")) {
                ImGui::MenuItem("Open");
                ImGui::MenuItem("Save");
                ImGui::MenuItem("Exit");
                ImGui::EndMenu();
            }

            if(ImGui::BeginMenu("Connection")) {
                ImGui::MenuItem("Connect");
                ImGui::MenuItem("Disconnect");
                ImGui::EndMenu();
            }

            if(ImGui::BeginMenu("Tools")) {
                ImGui::MenuItem("Show Console");
                ImGui::EndMenu();
            }  

            ImGui::EndMenuBar();      
        }
        
        ImGui::Columns(2, "mycolumns", true);
        ImGui::Text("Image Output:");
        {
            ImGui::BeginChild("image_box", ImVec2(0, 600), ImGuiChildFlags_Borders | ImGuiChildFlags_AlwaysUseWindowPadding);
            
            ImGui::EndChild();
        }
        ImGui::Button("Save image");
        ImGui::SameLine();
        ImGui::Button("Record video");

        ImGui::NextColumn();
        ImGui::Text("Terminal Output:"); 
        {
            ImGui::BeginChild("terminal_box", ImVec2(800, 600), ImGuiChildFlags_Borders | ImGuiChildFlags_AlwaysUseWindowPadding);
            //Terminal output
            ImGui::Text("Terminal output goes here...");
            // SerialTerminal::readSerialData();
            ImGui::EndChild();
        }

        ImGui::Columns(2);
        ImGui::Button("Save log");
        ImVec2 mouse_pos = ImGui::GetMousePos();
        ImGui::Text("Mouse Position: (%.1f, %.1f)", mouse_pos.x, mouse_pos.y);
        ImGui::End();
    }
}