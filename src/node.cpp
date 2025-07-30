////////////////////////////////////////////////////////////
// NODE
// ----------
// Definitions for Tree_Visualizer::Node.
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

#include <tree_visualizer.hpp>

#include <primordial.hpp>

sf::Color Tree_Visualizer::Node::fill_color = sf::Color::Black;
sf::Color Tree_Visualizer::Node::text_color = sf::Color::White;

sf::Color Tree_Visualizer::Node::hi_fill_color = sf::Color::White;
sf::Color Tree_Visualizer::Node::hi_text_color = sf::Color::Black;

sf::Color Tree_Visualizer::Node::sel_fill_color = sf::Color(218, 188, 98);
sf::Color Tree_Visualizer::Node::sel_text_color = sf::Color::Black;

sf::Color Tree_Visualizer::Node::line_color = sf::Color(90, 60, 120);

Tree_Visualizer::Node::Node(sf::Font& font, Node_Data ndata, std::map<unsigned short int, Node_Data>& nodes)
{
    id = ndata.id;
    text.setString(std::to_string(id));
    text.setFont(font);
    centerText(text);
    text.setFillColor(text_color);

    circle.setFillColor(fill_color);
    circle.setRadius(32.f);
    circle.setOrigin(32.f, 32.f);

    for(const auto& child : ndata.children) {
        if (nodes.count(child)) {
        children.push_back(new Node(font, nodes.at(child), nodes));
        child_lines.push_back(sf::RectangleShape());
        }
    }

    data = ndata.tval;
}

void Tree_Visualizer::Node::placeChildren(sf::Vector2f pos, float angle, float slice)
{
    circle.setPosition(pos);
    text.setPosition(pos);

    float offset = 0.f;

    if (children.size() > 1) offset = slice/children.size();

    angle -= (offset / 2.f) * (children.size() / 2.f + 0.5f);

    if (angle < 0.f) angle += 360.f;

    for(auto* child : children) {
        sf::Vector2f v = calculateMoveVector(angle, (256.f));
        child->placeChildren(pos + v, angle, 90.f);
        angle += offset;
        if (angle >= 360.f) angle -= 360.f;
    }
}

void Tree_Visualizer::Node::connectChildren()
{
    sf::Vector2f p1 = circle.getPosition();

    for(unsigned int i = 0; i < children.size(); ++i) {
        sf::Vector2f p2 = children[i]->circle.getPosition();
        child_lines[i].setPosition(p1);
        child_lines[i].setSize(sf::Vector2f(4.f, scalarDistance(p2, p1)));
        child_lines[i].setOrigin(sf::Vector2f(2.f, 0.f));
        child_lines[i].setRotation(calculateAngle(p2, p1));
        child_lines[i].setFillColor(line_color);
        children[i]->connectChildren();
    }
}

void Tree_Visualizer::Node::checkMouse(const sf::Vector2f& mpos)
{
    bool contains = circle.getGlobalBounds().contains(mpos);

    if (!highlighted && contains) {
        highlight();
    }
    else if (highlighted && !contains) {
        unhighlight();
    }

    for(auto* child : children) {
        child->checkMouse(mpos);
    }
}

void Tree_Visualizer::Node::greedyCheck(const sf::Vector2f& mpos)
{
    bool contains = (scalarDistance(mpos, circle.getPosition()) <= circle.getRadius());
    if (!highlighted && contains) {
        highlight();
    }
    else if (highlighted && !contains) {
        unhighlight();
    }
    for (auto* child : children) {
        child->greedyCheck(mpos);
    }
}

Tree_Visualizer::Node* Tree_Visualizer::Node::checkClick()
{
    Node* node { nullptr };

    if (highlighted) {
        select();
        node = this;
    }
    else if (selected) {
        unselect();
    }

    for(auto* child : children) {
        Node* tnode = child->checkClick();
        if (node == nullptr && tnode != nullptr) node = tnode;
    }

    return node;
}

void Tree_Visualizer::Node::setFillColor()
{
    if (!highlighted && !selected) {
        circle.setFillColor(fill_color);
    }
    for (auto* child : children) {
        child->setFillColor();
    }
}

void Tree_Visualizer::Node::setTextColor()
{
    if (!highlighted && !selected) {
        text.setFillColor(text_color);
    }
    for (auto* child : children) {
    child->setTextColor();
    }
}

void Tree_Visualizer::Node::setHiFillColor()
{
    if (highlighted) {
        circle.setFillColor(hi_fill_color);
    }
    for (auto* child : children) {
        child->setHiFillColor();
    }
}

void Tree_Visualizer::Node::setHiTextColor()
{
    if (highlighted) {
        text.setFillColor(hi_text_color);
    }
    for (auto* child : children) {
        child->setHiTextColor();
    }
}

void Tree_Visualizer::Node::setSelFillColor()
{
    if (selected) {
        circle.setFillColor(sel_fill_color);
    }
    for (auto* child : children) {
        child->setSelFillColor();
    }
}

void Tree_Visualizer::Node::setSelTextColor()
{
    if (selected) {
        text.setFillColor(sel_text_color);
    }
    for (auto* child : children) {
        child->setSelTextColor();
    }
}

void Tree_Visualizer::Node::setLineColor()
{
    for (auto& line : child_lines) {
        line.setFillColor(line_color);
    }
    for (auto* child : children) {
        child->setLineColor();
    }
}

bool Tree_Visualizer::Node::isHighlighted()
{
    return highlighted;
}

void Tree_Visualizer::Node::highlight()
{
    highlighted = true;
    circle.setFillColor(hi_fill_color);
    text.setFillColor(hi_text_color);
}

void Tree_Visualizer::Node::unhighlight()
{
    highlighted = false;
    if (!selected) {
        circle.setFillColor(fill_color);
        text.setFillColor(text_color);
    }
    else {
        circle.setFillColor(sel_fill_color);
        text.setFillColor(sel_text_color);
    }
}

void Tree_Visualizer::Node::select()
{
    selected = true;
    circle.setFillColor(sel_fill_color);
    text.setFillColor(sel_text_color);
}

void Tree_Visualizer::Node::unselect()
{
    selected = false;
    if (highlighted) {
        highlight();
    }
    else {
        unhighlight();
    }
}

void Tree_Visualizer::Node::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(unsigned short int i = 0; i < children.size(); ++i) {
        target.draw(child_lines[i], states);
        target.draw(*children[i], states);
    }

    target.draw(circle, states);
    target.draw(text, states);
}
