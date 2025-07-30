#pragma once

#include <SFML/Graphics.hpp>
#include <tree.hpp>

class Shell {
public:
    Shell();
    void run();

private:
    void update();
    void input();
    void draw();

    void randomColors();

    sf::RenderWindow window;
    sf::View view;
    sf::Event event;
    sf::Font font;

    Tree tree;
};
