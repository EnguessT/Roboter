#include <iostream>

#include "../include/ui_window.hpp"
#include "../include/rounded_rectangle.hpp"
#include "../include/two_wheel_robot.hpp"
#include "../include/four_wheel_robot.hpp"


WindowUI::WindowUI(sf::RenderWindow* window, tgui::Gui* gui)
: m_window (window)
, m_gui(gui) 
, dir_path(std::filesystem::current_path()) {

    std::filesystem::path theme_path {dir_path/"Assets/themes/Black.txt"};
    tgui::Theme theme{theme_path.string()};
    m_theme = theme;

    std::filesystem::path font_path {dir_path/"Assets/fonts/Verune/Verune.otf"};
    const sf::Font font{font_path.string()};
    m_font = font;

    createMenuBar(m_gui);
    createToolBar(m_gui);
    createSideBar(m_gui);
    createCanvas(m_gui);

}

// Create the menubar
void WindowUI::createMenuBar(tgui::Gui *gui) {
    auto menu = tgui::MenuBar::create();
    menu->setRenderer(m_theme.getRenderer("MenuBar"));
    auto menu_renderer = menu->getRenderer();
    menu_renderer->setSeparatorVerticalPadding(15);   
    menu_renderer->setSeparatorThickness(1);          
    menu_renderer->setDistanceToSide(15.f);
    menu->setHeight(30.f);

    menu->addMenu("File");
    menu->addMenuItem("Load");
    menu->addMenuItem("Save");
    menu->addMenuItem("Record");
    menu->addMenuItem("Exit");

    menu->addMenu("Create");
    menu->addMenuItem("Robot");
    menu->addMenuItem("Map");
    menu->addMenuItem("World");

    menu->addMenu("Edit");
    menu->addMenuItem("Robot");
    menu->addMenuItem("Map");
    menu->addMenuItem("World");

    menu->addMenu("Simulation");
    menu->addMenuItem("Path Planning");
    menu->addMenuItem("Navigation");
    menu->addMenuItem("Sensors");

    menu->addMenu("Plot");
    menu->addMenuItem("Position");
    menu->addMenuItem("Trajectory");
    menu->addMenuItem("Mapping");

    menu->addMenu("Examples");
    menu->addMenuItem("Example 1");
    menu->addMenuItem("Example 2");

    menu->addMenu("View");
    menu->addMenuItem("Zoom in");
    menu->addMenuItem("Zoom out");
    gui->add(menu);
}

// Create  the menu item icon button
tgui::Panel::Ptr WindowUI::createMenuItem(const tgui::String& iconPath, 
                const tgui::String& tipText) {

    auto item = tgui::Panel::create({"100%", "24px"});

    auto h = tgui::HorizontalLayout::create();
    h->setSize({"100%", "100%"});
    item->add(h);

    // icon
    auto icon = tgui::Picture::create(iconPath);
    icon->setSize(16, 16);
    h->add(icon, "16px");

    // spacing
    auto space = tgui::Panel::create({"6px", "1px"});
    h->add(space, "6px");

    // text
    auto label = tgui::Label::create(tipText);
    label->setTextSize(14);
    h->add(label, "1*");

    return item;
}

void WindowUI::createToolBar(tgui::Gui *gui) {
    auto toolbar = tgui::Panel::create({"100%", "32px"});
    toolbar->setPosition({"0", "30"});
    toolbar->getRenderer()->setBackgroundColor(tgui::Color(40, 40, 40));

    // bottom border
    auto bottomBorder = tgui::Panel::create({"100%", "1px"});
    bottomBorder->setPosition({"0", "31"});
    bottomBorder->getRenderer()->setBackgroundColor(tgui::Color(60, 60, 60));
    toolbar->add(bottomBorder);

    // layout
    auto hbox = tgui::GrowHorizontalLayout::create();
    hbox->setSize({"100%", "100%"});
    hbox->getRenderer()->setPadding(2);
    toolbar->add(hbox);


    // buttons
    auto robotBtn  = createIconButton("Assets/images/robot.png", "Add robot");
    robotBtn->onPress([](){
        std::cerr << "Button new was pressed\n";
    });
    auto mazeBtn = createIconButton("Assets/images/maze.png", "Add world");
    mazeBtn->onPress([](){
        std::cerr << "Button open was pressed\n";
    });
    auto saveBtn = createIconButton("Assets/images/box.png", "Add box");
    saveBtn->onPress([](){
        std::cerr << "Button save was pressed\n";
    });

    // add buttons with fixed width
    hbox->add(robotBtn,  "32px");
    hbox->add(mazeBtn, "32px");
    hbox->add(saveBtn, "32px");

    // separator
    auto space = tgui::Panel::create({"6px", "1px"});
    space->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
    auto sep = tgui::Panel::create({"10px", "60%"});
    sep->setPosition({"0", "20%"});
    sep->getRenderer()->setBackgroundColor(tgui::Color(80, 80, 80));
    hbox->add(space, "1px");

    // spacer (to push items left)
    auto spacer = tgui::Panel::create({"1px", "1px"});
    hbox->add(spacer, "1*");   // stretchable spacer

    gui->add(toolbar);
}

// Icon button factory
tgui::Button::Ptr WindowUI::createIconButton(const tgui::String& iconPath, 
                    const tgui::String& tipText) {

    auto btn = tgui::Button::create();
    btn->setWidth(32);
    btn->setHeight("100%");  // match toolbar height

    auto r = btn->getRenderer();
    r->setBackgroundColor(tgui::Color::Transparent);
    r->setBackgroundColorHover(tgui::Color(70,70,70));
    r->setBorderColor(tgui::Color::Transparent);
    r->setTexture(iconPath);

    // Tooltip
    auto tip = tgui::Label::create(tipText);
    tip->getRenderer()->setBackgroundColor(tgui::Color(50, 50, 50));
    tip->getRenderer()->setTextColor(tgui::Color::White);
    tip->getRenderer()->setPadding({4, 4, 4, 4});
    btn->setToolTip(tip);

    return btn;
}


void WindowUI::createCanvas(tgui::Gui *gui) {
    m_canvas = tgui::CanvasSFML::create({"80%", "100% - 60"});
    m_canvas->setPosition({"20%", "60"});
    
    gui->add(m_canvas);
}

void WindowUI::createSideBar(tgui::Gui *gui) {
    auto sidebar = tgui::Panel::create({"20%", "100% - 60"});
    sidebar->setPosition({"0%", "60"});
    sidebar->setRenderer(m_theme.getRenderer("Panel"));
    
    // Vertical Layout
    auto layout = tgui::GrowVerticalLayout::create();
    layout->setWidth("100%");
    layout->setVisible(true);
    sidebar->add(layout);

    // Espacement optionnel entre les boutons
    layout->getRenderer()->setPadding(10);

    // Buttons
    auto play = tgui::Button::create("Play");
    play->setRenderer(m_theme.getRenderer("Button"));
    play->setHeight(50);
    play->setWidth("80%");

    auto settings = tgui::Button::create("Settings");
    settings->setRenderer(m_theme.getRenderer("Button"));
    settings->setHeight(50);
    settings->setWidth("80%");

    // Add with fixed heights
    layout->add(play, "50px");
    layout->add(settings, "50px");
    
    gui->add(sidebar);
}

void WindowUI::draw() {
    m_canvas->clear(sf::Color(60, 60, 60));
    sf::Text text(m_font, "Hello SFML", 50);
    RoundedRectangleShape body({120.f, 70.f}, 15.f, 12);
    body.setFillColor(sf::Color::Blue);
    body.setPosition({300.f, 100.f});
    //body.setRotation(sf::Angle .f);

    TwoWheelRobot robot({80.f, 200.f}, sf::Color(35, 186, 153));
    FourWheelRobot fourRobot({200.f, 300.f}, sf::Color(35, 186, 153));
    

    m_canvas->draw(text);
    m_canvas->draw(body);
    m_canvas->draw(robot);
    m_canvas->draw(fourRobot);
    m_canvas->display();

}