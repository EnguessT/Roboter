#include <iostream>
#include <chrono>
#include <filesystem>
#include "../include/differential_drive.hpp"
#include "../include/simulator.hpp"
#include "../include/logger.hpp"
#include "../include/recorder.hpp"
#include "../include/ui_window.hpp"


int main() {

    // SFML 3 window creation syntax
    sf::RenderWindow window{sf::VideoMode({1080, 720}), "TGUI + SFML 3"};
    // TGUI GUI object
    tgui::Gui gui{window};

    WindowUI window_ui(&window, &gui);

     while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {

            gui.handleEvent(*event);

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
        }

        window_ui.draw();

        window.clear();
        gui.draw();
        window.display();
    }

    return 0;
}