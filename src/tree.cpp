#include <tree.hpp>
#include <iostream>
#include <primordial.hpp>

//////////////////////////////////////////////
Node_Data::Node_Data(unsigned short int nid, std::string ntval, std::vector<unsigned short int> nchildren)
: id{ nid }, tval{ ntval }, children{ nchildren }{}

//////////////////////////////////////////////

Tree::Tree(sf::Font& font, std::map<unsigned short int, Node_Data> nodes, sf::RenderWindow& window)
{
    title.setString("tree");
    title.setFont(font);

    zoom_level = 1.f;

    float xp = 0.1f,
          yp = 0.1f,
          xs = 0.8f,
          ys = 0.8f;

    view.setViewport(sf::FloatRect(xp,yp,xs,ys));
    view.setSize(sf::Vector2f(window.getSize().x*xs,window.getSize().y*ys));
    view.setCenter(sf::Vector2f(0.f, 0.f));

    sf::Vector2f fsize(4096.f, 4096.f);

    frame.setSize(fsize);
    frame.setOrigin(fsize / 2.f);
    frame.setFillColor(sf::Color(90, 10, 30));
    frame.setPosition(16.f, 16.f);

    if(nodes.count(0)){
        root = new Node(font, nodes.at(0), nodes);
    }
    else{
        std::cout << "no root node found!";
        return;
    }

    root->placeChildren(sf::Vector2f(0.f, 0.f));
    root->connectChildren();
}

void Tree::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(title, states);
    target.setView(view);
    target.draw(frame, states);
    target.draw(*root, states);
}

void Tree::checkMouse(sf::Event& event){
    bool dragCheck = (sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Mouse::isButtonPressed(sf::Mouse::Middle));

    if(dragging){
        if(!dragCheck){
            dragging = false;
        }
        else{
            drag();
        }
    }
    else{
        if(dragCheck){
            dragging = true;
            drag_pos = sf::Vector2f(sf::Mouse::getPosition());
        }
    }

    if(event.type == sf::Event::MouseButtonReleased){
        if(event.mouseButton.button == sf::Mouse::Left){
            //clickLeft();
        }
    }
    else if(event.type == sf::Event::MouseWheelScrolled){
        zoom(event.mouseWheelScroll.delta);
    }
}

void Tree::zoom(float delta){
    if(delta > 0) delta = -0.2f;
    else if(delta < 0) delta = 0.2f;
    else return;

    float target = zoom_level + delta;
    float factor = target / zoom_level;
    view.zoom(factor);
    zoom_level = factor;
}

void Tree::drag(){
    sf::Vector2f mpos(sf::Mouse::getPosition());
        //window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
    view.move(drag_pos - mpos);
    drag_pos = mpos;
}

//////////////////////////////////////////////
Tree::Node::Node(sf::Font& font, Node_Data data, std::map<unsigned short int, Node_Data>& nodes)
{
    id = data.id;
    text.setString(data.tval);
    text.setFont(font);
    centerText(text);
    text.setFillColor(sf::Color::Black);


    circle.setRadius(32.f);
    circle.setOrigin(32.f, 32.f);

    for(const auto& c : data.children){
        if(nodes.count(c)){
        children.push_back(new Node(font, nodes.at(c), nodes));
        child_lines.push_back(sf::RectangleShape());
        }
        else{
            std::cout << "no node data found for " << id << " child " << c << '\n';
        }
    }
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
