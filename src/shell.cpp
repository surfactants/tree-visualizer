#include <shell.hpp>
#include <iostream>

Shell::Shell()
    : window{ sf::VideoMode(), "treeviz", sf::Style::Fullscreen }
{
        font.loadFromFile("adventpro-bold.ttf");

        std::map<unsigned short int, Node_Data> nodes;

        view.setSize(sf::Vector2f(window.getSize()));
        view.setCenter(sf::Vector2f(window.getSize()) / 2.f);

        nodes.insert(std::make_pair(0, Node_Data(0, "0", std::vector<unsigned short int>({ 100, 200, 300, 400, 500 }))));

        nodes.insert(std::make_pair(100, Node_Data(100, "100", std::vector<unsigned short int>({ 101, 102 }))));
            nodes.insert(std::make_pair(101, Node_Data(101, "101", std::vector<unsigned short int>())));
            nodes.insert(std::make_pair(102, Node_Data(102, "102", std::vector<unsigned short int>({ 103 }))));
            nodes.insert(std::make_pair(103, Node_Data(103, "103", std::vector<unsigned short int>())));

        nodes.insert(std::make_pair(200, Node_Data(200, "200", std::vector<unsigned short int>({ 201, 202, 203 }))));
            nodes.insert(std::make_pair(201, Node_Data(201, "201", std::vector<unsigned short int>({ 204, 205 }))));
            nodes.insert(std::make_pair(202, Node_Data(202, "202", std::vector<unsigned short int>({ 206 }))));
            nodes.insert(std::make_pair(203, Node_Data(203, "203", std::vector<unsigned short int>({ 207, 208 }))));
            nodes.insert(std::make_pair(204, Node_Data(204, "204", std::vector<unsigned short int>({ }))));
            nodes.insert(std::make_pair(205, Node_Data(205, "205", std::vector<unsigned short int>({ }))));
            nodes.insert(std::make_pair(206, Node_Data(206, "206", std::vector<unsigned short int>({ }))));
            nodes.insert(std::make_pair(207, Node_Data(207, "207", std::vector<unsigned short int>({ }))));
            nodes.insert(std::make_pair(208, Node_Data(208, "208", std::vector<unsigned short int>({ }))));

        nodes.insert(std::make_pair(300, Node_Data(300, "300", std::vector<unsigned short int>({ 301, 302, 303, 304}))));
            nodes.insert(std::make_pair(301, Node_Data(301, "301", std::vector<unsigned short int>({ }))));
            nodes.insert(std::make_pair(302, Node_Data(302, "302", std::vector<unsigned short int>({ }))));
            nodes.insert(std::make_pair(303, Node_Data(303, "303", std::vector<unsigned short int>({ }))));
            nodes.insert(std::make_pair(304, Node_Data(304, "304", std::vector<unsigned short int>({ }))));
            nodes.insert(std::make_pair(305, Node_Data(305, "305", std::vector<unsigned short int>({ }))));
            nodes.insert(std::make_pair(306, Node_Data(306, "306", std::vector<unsigned short int>({ }))));
            nodes.insert(std::make_pair(307, Node_Data(307, "307", std::vector<unsigned short int>({ }))));
            nodes.insert(std::make_pair(308, Node_Data(308, "308", std::vector<unsigned short int>({ }))));

        nodes.insert(std::make_pair(400, Node_Data(400, "400", std::vector<unsigned short int>())));

        nodes.insert(std::make_pair(500, Node_Data(500, "500", std::vector<unsigned short int>())));

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
