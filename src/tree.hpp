#pragma once

#include <SFML/Graphics.hpp>
#include <node_data.hpp>
#include <string>
#include <map>
#include <vector>

class Tree_Display : public sf::Drawable{
public:
    Tree_Display() = default;
    Tree_Display(sf::Font& nfont, sf::RenderWindow& window);

    void set(std::string ntitle, std::string ntext);
    void unset();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::RectangleShape frame;

    sf::Font* font;
    sf::Text title;
    sf::Text text;
};

class Tree : public sf::Drawable{
public:
    Tree() = default;
    Tree(sf::Font& font, std::map<unsigned short int, Node_Data> nodes, sf::RenderWindow& nwindow);

    void checkMouse(sf::Event& event);

    void update();

private:
    struct Node : public sf::Drawable{
        Node(sf::Font&, Node_Data ndata, std::map<unsigned short int, Node_Data>& nodes);

        unsigned short int id;

        sf::CircleShape circle;
        sf::Text text;

        std::vector<Node*> children;
        std::vector<sf::RectangleShape> child_lines;

        std::string data;

        void placeChildren(sf::Vector2f pos, float angle = 0.f, float slice = 360.f);
        void connectChildren();

        void checkMouse(sf::Vector2f& mpos);

        bool isHighlighted();

        Node* checkClick();

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        bool highlighted{ false };

        void highlight();
        void unhighlight();

        bool selected{ false };

        void select();
        void unselect();
    };

    sf::RenderWindow* window{ nullptr };

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

    Tree_Display display;
};
