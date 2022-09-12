#include <tree.hpp>
#include <iostream>
#include <primordial.hpp>

Tree::Node::Node(sf::Font& font, Node_Data ndata, std::map<unsigned short int, Node_Data>& nodes)
{
    id = ndata.id;
    text.setString(std::to_string(id));
    text.setFont(font);
    centerText(text);
    text.setFillColor(sf::Color::Black);


    circle.setRadius(32.f);
    circle.setOrigin(32.f, 32.f);

    for(const auto& c : ndata.children){
        if(nodes.count(c)){
        children.push_back(new Node(font, nodes.at(c), nodes));
        child_lines.push_back(sf::RectangleShape());
        }
        else{
            std::cout << "no node data found for " << id << " child " << c << '\n';
        }
    }

    data = ndata.tval;
}

void Tree::Node::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(unsigned short int i = 0; i < children.size(); ++i){
        target.draw(child_lines[i], states);
        target.draw(*children[i], states);
    }

    target.draw(circle, states);
    target.draw(text, states);
}

void Tree::Node::placeChildren(sf::Vector2f pos, float angle, float slice){
    circle.setPosition(pos);
    text.setPosition(pos);
    std::cout << "setting node " << id << " to pos " << pos.x << ", " << pos.y << '\n';

    float offset = 0.f;

    if(children.size() > 1) offset = slice/children.size();

    angle -= (offset / 2.f) * (children.size() / 2.f);

    if(angle < 0.f) angle += 360.f;

    for(auto& c : children){
        sf::Vector2f v = calculateMoveVector(angle, (256.f));
        c->placeChildren(pos + v, angle, 90.f);
        angle += offset;
        if(angle >= 360.f) angle -= 360.f;
    }
}

void Tree::Node::connectChildren(){
    sf::Vector2f p1 = circle.getPosition();

    for(unsigned int i = 0; i < children.size(); ++i){
        std::cout << "\t\tconnecting node " << id << " from " << circle.getPosition().x << ", " << circle.getPosition().y;
        std::cout << " to child " << i << " (" << children[i]->id << ") at " << children[i]->circle.getPosition().x << ", " << children[i]->circle.getPosition().y << '\n';
        sf::Vector2f p2 = children[i]->circle.getPosition();
        child_lines[i].setPosition(p1);
        child_lines[i].setSize(sf::Vector2f(8.f, scalarDistance(p2, p1)));
        child_lines[i].setOrigin(sf::Vector2f(4.f, 0.f));
        child_lines[i].setRotation(calculateAngle(p2, p1));
        child_lines[i].setFillColor(sf::Color(120, 60, 150));
        children[i]->connectChildren();
    }
}

void Tree::Node::checkMouse(sf::Vector2f& mpos)
{
    bool contains = circle.getGlobalBounds().contains(mpos);
    if(!highlighted && contains) highlight();
    else if(highlighted && !contains) unhighlight();
    for(auto& c : children) c->checkMouse(mpos);
}

bool Tree::Node::isHighlighted()
{
    return highlighted;
}

void Tree::Node::highlight()
{
    highlighted = true;
    if(!selected){
        circle.setFillColor(sf::Color::Black);
        text.setFillColor(sf::Color::White);
    }
}

void Tree::Node::unhighlight()
{
    highlighted = false;
    if(!selected){
        circle.setFillColor(sf::Color::White);
        text.setFillColor(sf::Color::Black);
    }
}

Tree::Node* Tree::Node::checkClick()
{
    Node* node{ nullptr };
    if(highlighted){
        select();
        node = this;
    }
    else if(selected) unselect();

    for(const auto& c : children)
    {
        Node* tnode = c->checkClick();
        if(node == nullptr && tnode != nullptr) node = tnode;
    }

    return node;
}

void Tree::Node::select()
{
    selected = true;
    circle.setFillColor(sf::Color::Blue);
    text.setFillColor(sf::Color::Red);
}

void Tree::Node::unselect()
{
    selected = false;
    if(highlighted) highlight();
    else unhighlight();
}
