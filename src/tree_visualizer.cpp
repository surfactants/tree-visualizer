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

#include <tree_visualizer.hpp>

//////////////////////////////////////////////
Tree_Visualizer::Tree_Visualizer(sf::Font& font, std::map<unsigned short int, Node_Data> nodes, sf::View view)
{
    title.setString("tree");
    title.setFont(font);

    zoom_level = 1.f;

    this->view = view;

    sf::Vector2f fsize(8192.f, 8192.f);

    frame.setSize(fsize);
    frame.setOrigin(fsize / 2.f);
    frame.setFillColor(sf::Color(40, 20, 30));
    frame.setPosition(16.f, 16.f);

    if (nodes.count(0)) {
        root = new Node(font, nodes.at(0), nodes);
    }
    else {
        return;
    }

    root->placeChildren(sf::Vector2f(0.f, 0.f));
    root->connectChildren();

    node_info_display = Node_Info_Display(font);
}

void Tree_Visualizer::update(const sf::Vector2f& translated_mpos)
{
    root->greedyCheck(translated_mpos);
}

void Tree_Visualizer::checkMouse(sf::Event& event)
{
    if (event.type == sf::Event::MouseWheelScrolled) {
        zoom(event.mouseWheelScroll.delta);
        return;
    }

    bool dragCheck = (sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Mouse::isButtonPressed(sf::Mouse::Middle));

    if (dragging) {
        if (!dragCheck) {
            dragging = false;
        }
        else {
            drag();
        }
    }
    else {
        if (dragCheck) {
            dragging = true;
            drag_pos = sf::Vector2f(sf::Mouse::getPosition());
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                Node* clicked = root->checkClick();
                if (clicked != nullptr) {
                    node_info_display.set(std::to_string(clicked->id), clicked->data);
                }
                else {
                    node_info_display.unset();
                }
            }
        }
    }
}

void Tree_Visualizer::setFrameColor(const sf::Color& cf)
{
    frame.setFillColor(cf);
}

void Tree_Visualizer::setTitleColor(const sf::Color& ct)
{
    title.setFillColor(ct);
}

void Tree_Visualizer::setNodeFillColor(const sf::Color& c)
{
    Node::fill_color = c;
    root->setFillColor();
}

void Tree_Visualizer::setNodeTextColor(const sf::Color& c)
{
    Node::text_color = c;
    root->setTextColor();
}

void Tree_Visualizer::setNodeHiFillColor(const sf::Color& hc)
{
    Node::hi_fill_color = hc;
    root->setHiFillColor();
}

void Tree_Visualizer::setNodeHiTextColor(const sf::Color& hc)
{
    Node::hi_text_color = hc;
    root->setHiTextColor();
}

void Tree_Visualizer::setNodeSelFillColor(const sf::Color& sc)
{
    Node::sel_fill_color = sc;
    root->setSelFillColor();
}

void Tree_Visualizer::setNodeSelTextColor(const sf::Color& sc)
{
    Node::sel_fill_color = sc;
    root->setSelTextColor();
}

void Tree_Visualizer::setLineColor(const sf::Color& c)
{
    Node::line_color = c;
    root->setLineColor();
}

void Tree_Visualizer::setDisplayFrameColor(const sf::Color& c)
{
    node_info_display.frame.setFillColor(c);
}

void Tree_Visualizer::setDisplayTextColor(const sf::Color& c)
{
    node_info_display.title.setFillColor(c);
    node_info_display.text.setFillColor(c);
}

void Tree_Visualizer::setDisplayPosition(const sf::Vector2f& pos)
{
    node_info_display.setPosition(pos);
}

void Tree_Visualizer::setDisplaySize(const sf::Vector2f& size)
{
    node_info_display.setSize(size);
}

void Tree_Visualizer::setView(sf::View view)
{
    this->view = view;
}

void Tree_Visualizer::zoom(float delta) {
    if (delta > 0) {
        delta = -0.2f;
    }
    else if (delta < 0) {
        delta = 0.2f;
    }
    else {
        return;
    }

    float target = zoom_level + delta;
    float factor = target / zoom_level;
    view.zoom(factor);
    zoom_level = factor;
}

void Tree_Visualizer::drag() {
    sf::Vector2f mpos(sf::Mouse::getPosition());
    view.move((drag_pos - mpos) * zoom_level);
    drag_pos = mpos;
}

void Tree_Visualizer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(title, states);
    target.draw(node_info_display, states);

    target.setView(view);
    target.draw(frame, states);
    target.draw(*root, states);
}
