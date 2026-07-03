/**
 * @file ui_window.hpp
 * @brief Declaration of class UIWindow.
 *
 * Description: Declares the variables and methods of class UIWindow.
 * 
 * -------
 * @author EnguessT
 * @date July 02, 2026
 */
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
    /**
     * @brief construct the UIWindow object
     * @param[in] window the rendered window
     * @param[in] gui the tgui::GUI* object
     */
    WindowUI(sf::RenderWindow* window, tgui::Gui* gui);

    /**
     * @brief update the rendering of object on the canvas
     * @param[in] void
     * @return void
     */
    void update();

    /**
     * @brief add the object to draw on the canvas
     * @param[in] void
     * @return void
     */
    void draw();

    /**
     * @brief callback function to add draw a created car on the canvas
     * @param[in] gui: the tgui::Gui* object
     * @param[in] theme: the selected theme for UI 
     */
    void addCarcallback(tgui::Gui& gui, tgui::Theme& theme);

    /**
     * @brief create an EditBox 
     * @param[in] theme : the selected theme for UI
     * @param[in] width, height the size of the editbox
     * @param[in] xPos, yPos: the position of the editbox
     * @param[in] defaultText the default displayed text on the editbox
     * @param[in] max: the maximum value for the x, y position of the robot
     * @return tgui::EditBox::Ptr : created editbox     
     */
    tgui::EditBox::Ptr createEditBox(tgui::Theme& theme,float width, float height, 
            float xPos, float yPos, const tgui::String defaultText, float max);

    /**
     * @brief create Label
     * @param[in] theme : the selected theme for UI
     * @param[in] text the displayed text on the label
     * @param[in] xPos, yPos: the position of the editbox
     * @return tgui::Label::Ptr : created Label   
     */
    tgui::Label::Ptr createLabel(tgui::Theme& theme, const tgui::String text, 
                        float xPos, float yPos);

    /**
     * @brief create the Menubar of the GUI Window
     * @param[in] gui: the Tgui::Gui* object
     * @return void
     */
    void createMenuBar(tgui::Gui* gui);

    /**
     * @brief create the Toolbar of the GUI Window
     * @param[in] gui: the Tgui::Gui* object
     * @return void
     */
    void createToolBar(tgui::Gui *gui);

    /**
     * @brief create the Canvas for drawing objects on the GUI Window
     * @param[in] gui: the Tgui::Gui* object
     * @return void
     */
    void createCanvas(tgui::Gui *gui);

    /**
     * @brief create the Sidebar of the GUI Window
     * @param[in] gui: the Tgui::Gui* object
     * @return void
     */
    void createSideBar(tgui::Gui *gui);

    /**
     * @brief create and return a MenuItem panel
     * @param[in] iconPath: path to the icon image
     * @param[in] tipText: text to display when hoovering on the menuitem
     * @return tgui::Panel::Ptr: The created MenuItem
     */
    tgui::Panel::Ptr createMenuItem(const tgui::String& iconPath, 
                    const tgui::String& tipText);
    
    /**
     * @brief create and return an IconButton
     * @param[in] iconPath: path to the icon image
     * @param[in] tipText: text to display when hoovering on the menuitem
     * @return tgui::Button::Ptr: The created Button
     */
    tgui::Button::Ptr createIconButton(const tgui::String& iconPath, 
                    const tgui::String& tipText);
    

private:
    sf::RenderWindow* m_window;
    tgui::Gui* m_gui;
    std::filesystem::path dir_path;
    tgui::Theme m_theme;
    sf::Font m_font;
    tgui::CanvasSFML::Ptr m_canvas;
    Simulator m_sim;  // simulator
    sf::Color selectedColor;  // color of the robot
};


