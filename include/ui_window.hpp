#pragma once

#include <filesystem>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/Widget.hpp>
#include <TGUI/Color.hpp>
#include "simulator.hpp"


class WindowUI {
public:
    WindowUI(sf::RenderWindow* window, tgui::Gui* gui);
    void update();
    void draw();
    void addCarcallback(tgui::Gui& gui, tgui::Theme& theme);
    tgui::EditBox::Ptr createEditBox(tgui::Theme& theme,float width, float height, 
            float xPos, float yPos, const tgui::String defaultText, float max);
    tgui::Label::Ptr createLabel(tgui::Theme& theme, const tgui::String text, 
                        float xPos, float yPos);
    void createMenuBar(tgui::Gui* gui);
    void createToolBar(tgui::Gui *gui);
    void createCanvas(tgui::Gui *gui);
    void createSideBar(tgui::Gui *gui);
    tgui::Panel::Ptr createMenuItem(const tgui::String& iconPath, 
                    const tgui::String& tipText);
    tgui::Button::Ptr createIconButton(const tgui::String& iconPath, 
                    const tgui::String& tipText);
    

private:
    sf::RenderWindow* m_window;
    tgui::Gui* m_gui;
    std::filesystem::path dir_path;
    tgui::Theme m_theme;
    sf::Font m_font;
    tgui::CanvasSFML::Ptr m_canvas;
};


