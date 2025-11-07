/* \brief The bgui manages the graphic user interface. The foccus is the simplicity and objectivity */
#pragma once
#include "utils.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum class theme {
    light,
    dark
};
class bgui {
private:
    theme m_theme;
    color m_clear_color;
public:
    bgui(theme gui_theme = theme::dark);
    ~bgui();

    static bgui& instance() {
        static bgui instance;
        return instance;
    }

    // \{ 
    // style management
    void set_theme(theme gui_theme);
    theme get_theme() const;
    // \}
    // \{
    // rendering
    void clear() const;
    void updateTree();
    void render();
    // \}
};