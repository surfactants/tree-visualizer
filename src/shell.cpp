#include <shell.hpp>
#include <database.hpp>

Shell::Shell()
    : window{ sf::VideoMode(), "treeviz", sf::Style::Fullscreen,
    sf::ContextSettings(0, 0, 4) }
{
        font.loadFromFile("adventpro-bold.ttf");

        view.setSize(sf::Vector2f(window.getSize()));
        view.setCenter(sf::Vector2f(window.getSize()) / 2.f);

        Database database;

        std::map<unsigned short int, Node_Data> nodes = database.getNodes();

        tree = Tree(font, nodes, window);
}

void Shell::run()
{
    while(window.isOpen()){
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

    while(window.pollEvent(event)){
        if(event.type == sf::Event::KeyReleased){
            if(event.key.code == sf::Keyboard::Escape){
                window.close();
            }
            else if(event.key.code == sf::Keyboard::R){
            }
        }
        else{
            tree.checkMouse(event);
        }
    }
}

void Shell::draw()
{
    window.clear();
        window.setView(view);
        window.draw(tree);
    window.display();
}
