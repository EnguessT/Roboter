#include <filesystem>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/Widget.hpp>
#include <TGUI/Color.hpp>


class WindowUI {
public:
    WindowUI(sf::RenderWindow* window, tgui::Gui* gui);
    void update();
    void draw();
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