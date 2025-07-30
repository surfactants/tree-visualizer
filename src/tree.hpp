#pragma once

#include <SFML/Graphics.hpp>
#include <node_data.hpp>
#include <string>
#include <map>
#include <vector>
#include <tree_display.hpp>

class Tree : public sf::Drawable{
public:
    Tree() = default;
    Tree(sf::Font& font, std::map<unsigned short int, Node_Data> nodes, sf::RenderWindow& nwindow);

    void update();
    void checkMouse(sf::Event& event);

    void setFrameColor(const sf::Color& c);
    void setTitleColor(const sf::Color& c);

    void setNodeFillColor(const sf::Color& c);
    void setNodeTextColor(const sf::Color& c);

    void setNodeHiFillColor(const sf::Color& hc);
    void setNodeHiTextColor(const sf::Color& hc);

    void setNodeSelFillColor(const sf::Color& sc);
    void setNodeSelTextColor(const sf::Color& sc);

    void setLineColor(const sf::Color& c);

    void setDisplayFrameColor(const sf::Color& c);
    void setDisplayTextColor(const sf::Color& c);

    sf::Color node_color;

private:
    struct Node : public sf::Drawable{
        Node(sf::Font&, Node_Data ndata, std::map<unsigned short int, Node_Data>& nodes);

        void placeChildren(sf::Vector2f pos, float angle = 0.f, float slice = 360.f);
        void connectChildren();

        void checkMouse(const sf::Vector2f& mpos);
        void greedyCheck(const sf::Vector2f& mpos);

        Node* checkClick();

        void setFillColor();
        void setTextColor();

        void setHiFillColor();
        void setHiTextColor();

        void setSelFillColor();
        void setSelTextColor();

        void setLineColor();

        bool isHighlighted();

        unsigned short int id;

        sf::CircleShape circle;
        sf::Text text;

        std::vector<Node*> children;
        std::vector<sf::RectangleShape> child_lines;

        std::string data;

        static sf::Color fill_color;
        static sf::Color text_color;

        static sf::Color hi_fill_color;
        static sf::Color hi_text_color;

        static sf::Color sel_fill_color;
        static sf::Color sel_text_color;

        static sf::Color line_color;

    private:
        bool highlighted { false };
        bool selected { false };

        void highlight();
        void unhighlight();

        void select();
        void unselect();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };

    sf::RenderWindow* window { nullptr };

    Node* root;

    sf::RectangleShape frame;
    sf::Text title;

    sf::View view;

    float zoom_level;

    void zoom(float delta);

    bool dragging;
    sf::Vector2f drag_pos;

    void drag();

    Tree_Display display;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
