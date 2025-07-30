#include <shell.hpp>

#include <database.hpp>
#include <iostream>
#include <primordial.hpp>

Shell::Shell()
    : window { sf::VideoMode(), "treeviz", sf::Style::Fullscreen, sf::ContextSettings(0, 0, 4) }
{
    std::cout << "window created, size " << window.getSize().x << ", " << window.getSize().y;
    font.loadFromFile("adventpro-bold.ttf");

    view.setSize(sf::Vector2f(window.getSize()));
    view.setCenter(sf::Vector2f(window.getSize()) / 2.f);

    Database database;

    std::map<unsigned short int, Node_Data> nodes = database.getNodes();

    tree = Tree(font, nodes, window);
}

void Shell::run()
{
    while(window.isOpen()) {
        update();
        input();
        draw();
    }
}

void Shell::update()
{
    tree.update();
}

void Shell::input()
{
    while(window.pollEvent(event)) {
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            else if (event.key.code == sf::Keyboard::R) {
                randomColors();
            }
        }
        else {
            tree.checkMouse(event);
        }
    }
}

void Shell::randomColors()
{
    tree.setNodeFillColor(randomColor());
    tree.setNodeTextColor(randomColor());

    tree.setNodeHiFillColor(randomColor());
    tree.setNodeHiTextColor(randomColor());

    tree.setNodeSelFillColor(randomColor());
    tree.setNodeSelTextColor(randomColor());

    tree.setLineColor(randomColor());

    tree.setFrameColor(randomColor());
    tree.setTitleColor(randomColor());

    tree.setDisplayFrameColor(randomColor());
    tree.setDisplayTextColor(randomColor());
}

void Shell::draw()
{
    window.clear();
        window.setView(view);
        window.draw(tree);
    window.display();
}
