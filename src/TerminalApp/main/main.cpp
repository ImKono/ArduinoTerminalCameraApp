#include <iostream>
#include "../include/MainWindow.h"

#define WIN32_LEAN_AND_MEAN

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << error << " - " << description;
}

namespace SerialTerminal {
    boost::asio::io_context io;
    boost::asio::serial_port port(io);

    bool openSerialPort(const std::string& device)
    {
        boost::system::error_code error;

        port.open(device, error);

        if (error) {
            std::cerr << "No se pudo abrir el puerto "
                      << device << ": "
                      << error.message()
                      << std::endl;

            return false;
        }

        //Setup
        port.set_option(boost::asio::serial_port_base::baud_rate(9600));
        port.set_option(boost::asio::serial_port_base::character_size(8));
        port.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
        port.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
        port.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));

        return true;
    }

    bool readSerialData()
    {
        char data[256];

        boost::system::error_code error;

        std::size_t length = port.read_some(
            boost::asio::buffer(data),
            error
        );

        if (error && error != boost::asio::error::eof) {
            std::cerr << "Error de lectura: "
                      << error.message()
                      << std::endl;

            return false;
        }

        std::cout << "Leídos "
                  << length
                  << " bytes."
                  << std::endl;

        std::cout.write(data, static_cast<std::streamsize>(length));
        std::cout << std::endl;

        return true;
    }
}

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
