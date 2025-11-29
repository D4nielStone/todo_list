#include <bgui.hpp>
#include <iostream>

int main() {
    GLFWwindow* window = bkend::set_up_glfw(1280, 720, "BGUI Exemple");
    
    bkend::set_up_opengl3();
    bkend::set_up_freetype();

    bgui::set_up();

    auto* root = bgui::instance().get_layout();

    // Adding elements
    root->add<belem::text>("Hello World!", 2.f);

    while (!glfwWindowShouldClose(window)) {
        bkend::glfw_update();           // update events
        bgui::update();                 // update layout
        bkend::opengl3_render(
            bgui::get_draw_data()       // render the layout data
        );
        glfwSwapBuffers(window);
    }

    bgui::shutdown_lib();
    bkend::shutdown_opengl3();
    bkend::shutdown_freetype();
    bkend::shutdown_glfw();
    return 0;

    return 0;
}