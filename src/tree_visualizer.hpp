////////////////////////////////////////////////////////////
// TREE_VISUALIZER
// ----------
// N-ary tree visualizer.
// Written by surfactants (https://github.com/surfactants).
//
// LICENSE: zlib (https://www.zlib.net/zlib_license.html)
// -------
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#pragma once

#include <node_data.hpp>
#include <node_info_display.hpp>

#include <SFML/Graphics.hpp>

#include <map>
#include <string>
#include <vector>

class Tree_Visualizer : public sf::Drawable{
public:
    Tree_Visualizer() = default;
    Tree_Visualizer(sf::Font& font, std::map<unsigned short int, Node_Data> nodes, sf::View view);

    void update(const sf::Vector2f& translated_mpos);
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

    void setDisplayPosition(const sf::Vector2f& pos);
    void setDisplaySize(const sf::Vector2f& size);

    void setView(sf::View view);

    sf::Color node_color;

    sf::View view;

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

    Node* root;

    sf::RectangleShape frame;
    sf::Text title;

    float zoom_level;

    void zoom(float delta);

    bool dragging;
    sf::Vector2f drag_pos;

    void drag();

    Node_Info_Display node_info_display;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
