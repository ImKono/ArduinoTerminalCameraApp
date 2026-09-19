cmake_minimum_required(VERSION 3.15)

# Evita el aviso de CMake 4.x relacionado con FindBoost
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 OLD)
endif()

project(HelloWorld LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Rutas locales de Boost ----
set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/libs/boost_1_92_0")
set(Boost_ROOT "${BOOST_ROOT}")
set(Boost_INCLUDE_DIR "${BOOST_ROOT}")
set(Boost_LIBRARY_DIR "${BOOST_ROOT}/stage/lib")

set(Boost_NO_SYSTEM_PATHS ON)
set(Boost_NO_BOOST_CMAKE ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

# ---- Dependencias ----
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)
find_package(Boost 1.92 REQUIRED COMPONENTS thread)

# ---- ImGui ----
add_library(imgui STATIC
    libs/imgui-master/imgui.cpp
    libs/imgui-master/imgui_demo.cpp
    libs/imgui-master/imgui_draw.cpp
    libs/imgui-master/imgui_tables.cpp
    libs/imgui-master/imgui_widgets.cpp
    libs/imgui-master/backends/imgui_impl_glfw.cpp
    libs/imgui-master/backends/imgui_impl_opengl2.cpp
)

target_include_directories(imgui PUBLIC
    ${CMAKE_SOURCE_DIR}/libs/imgui-master
    ${CMAKE_SOURCE_DIR}/libs/imgui-master/backends
)

# ---- GLFW ----
add_subdirectory(libs/glfw)

if(TARGET glfw)
    set(GLFW_TARGET glfw)
elseif(TARGET glfw3)
    set(GLFW_TARGET glfw3)
elseif(TARGET glfw3::glfw)
    set(GLFW_TARGET glfw3::glfw)
else()
    message(FATAL_ERROR
        "Could not find a GLFW target after add_subdirectory(libs/glfw)"
    )
endif()

target_link_libraries(imgui PUBLIC
    ${GLFW_TARGET}
    OpenGL::GL
)

# ---- Aplicación ----
add_executable(hello
    src/TerminalApp/main/main.cpp
    include/MainWindow.h
)

target_compile_definitions(hello PRIVATE
    BOOST_ERROR_CODE_HEADER_ONLY
    _WIN32_WINNT=0x0A00
)

target_link_libraries(hello PRIVATE
    imgui
    ${GLFW_TARGET}
    OpenGL::GL
    Boost::thread
    Threads::Threads
)
