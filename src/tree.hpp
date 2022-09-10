#pragma once

#include <SFML/Graphics.hpp>
#include <node_data.hpp>
#include <string>
#include <map>
#include <vector>

class Tree : public sf::Drawable{
public:
    Tree(){}
    Tree(sf::Font& font, std::map<unsigned short int, Node_Data> nodes, sf::RenderWindow& window);

    void checkMouse(sf::Event& event);

private:
    struct Node : public sf::Drawable{
        Node(sf::Font&, Node_Data data, std::map<unsigned short int, Node_Data>& nodes);

        unsigned short int id;

        sf::CircleShape circle;
        sf::Text text;

        std::vector<Node*> children;
        std::vector<sf::RectangleShape> child_lines;

        void placeChildren(sf::Vector2f pos, float angle = 0.f, float slice = 360.f);
        void connectChildren();

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };

    Node* root;

    sf::RectangleShape frame;
    sf::Text title;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::View view;

    float zoom_level;

    void zoom(float delta);

    bool dragging;
    sf::Vector2f drag_pos;

    void drag();

};
